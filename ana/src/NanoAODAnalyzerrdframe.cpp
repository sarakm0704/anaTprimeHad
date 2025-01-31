/*
 * NanoAODAnalyzerrdframe.cpp
 *
 *  Created on: Sep 30, 2018
 *      Author: suyong
 */

#include "NanoAODAnalyzerrdframe.h"
#include <iostream>
#include <algorithm>
#include <typeinfo>
#include <random>

#include "TCanvas.h"
#include "Math/GenVector/VectorUtil.h"
#include <vector>
#include <fstream>
#include "utility.h"
#include <regex>
#include "ROOT/RDFHelpers.hxx"

using namespace std;

NanoAODAnalyzerrdframe::NanoAODAnalyzerrdframe(TTree *atree, std::string outfilename)
:_rd(*atree), _jsonOK(false),_outfilename(outfilename)
    , _outrootfile(0), _rlm(_rd)
    , _rnt(&_rlm)
{
    _atree=atree;
    //cout<< " run year=====" << _year <<endl;



}

NanoAODAnalyzerrdframe::~NanoAODAnalyzerrdframe() {
    // TODO Auto-generated destructor stub
}

bool NanoAODAnalyzerrdframe::isDefined(string v)
{
    auto result = std::find(_originalvars.begin(), _originalvars.end(), v);
    if (result != _originalvars.end()) return true;
    else return false;
}

void NanoAODAnalyzerrdframe::setTree(TTree *t, std::string outfilename)
{
    _rd = ROOT::RDataFrame(*t);
    _rlm = RNode(_rd);
    _outfilename = outfilename;
    _hist1dinfovector.clear();
    _th1dhistos.clear();
    _varstostore.clear();
    _hist1dinfovector.clear();
    _selections.clear();
//  _hist2dinfovector.clear();
//  _th2dhistos.clear();

    this->setupAnalysis();
}


void NanoAODAnalyzerrdframe::setupCorrections(string goodjsonfname, string pufname, string putag, string btvfname, string btvtype, string fname_btagEff, string jercfname, string jerctag, string jercunctag, string jercsys_total)
{
    cout << "set up Corrections!" << endl;
    if (_isData) _jsonOK = readgoodjson(goodjsonfname); // read golden json file

    if (!_isData) {
        // using correctionlib

        // jets
        _jerc_fname = correction::CorrectionSet::from_file(jercfname);
        assert(_jerc_fname->validate());
        _jercptres_type = jerctag;
        _jercSF_type = jercunctag;
        _jercsys_total = jercsys_total;

        // btag corrections
        _correction_btag1 = correction::CorrectionSet::from_file(btvfname);
        _btvtype = btvtype;
        assert(_correction_btag1->validate());

        // load efficiency map
        _efficiency_btag1 = correction::CorrectionSet::from_file(fname_btagEff);
        assert(_efficiency_btag1->validate());

        // pile up weights
        _correction_pu = correction::CorrectionSet::from_file(pufname);
        assert(_correction_pu->validate());
        _putag = putag;
        auto punominal = [this](float x) { return pucorrection(_correction_pu, _putag, "nominal", x); };
        auto puplus = [this](float x) { return pucorrection(_correction_pu, _putag, "up", x); };
        auto puminus = [this](float x) { return pucorrection(_correction_pu, _putag, "down", x); };

        if (!isDefined("puWeight")) _rlm = _rlm.Define("puWeight", punominal, {"Pileup_nTrueInt"});
        if (!isDefined("puWeight_plus")) _rlm = _rlm.Define("puWeight_plus", puplus, {"Pileup_nTrueInt"});
        if (!isDefined("puWeight_minus")) _rlm = _rlm.Define("puWeight_minus", puminus, {"Pileup_nTrueInt"});

        if (!isDefined("pugenWeight"))
        {
            _rlm = _rlm.Define("pugenWeight", [this](float x, float y){
                    return x*y;
            }, {"genWeight", "puWeight"});
        }
    }
    _jerctag = jerctag;
    _jercunctag = jercunctag;

    //setupJetMETCorrection(jercfname, _jerctag);
    //applyJetMETCorrections();
}

//double NanoAODAnalyzerrdframe::getBTaggingEff(double hadflav, double eta, double pt){
//    double efficiency = 1.0;
//    int maxXBin = -1;
//    int maxYBin = -1;
//    int binX = -1;
//    int binY = -1;
//    if(hadflav!=0){
//      // Get the maximum bin number for x and y axes
//      maxXBin = hist_btagEff_bcflav->GetXaxis()->GetNbins();
//      maxYBin = hist_btagEff_bcflav->GetYaxis()->GetNbins();
//  
//      // Get the bin number corresponding to the provided x and y values
//      binX = hist_btagEff_bcflav->GetXaxis()->FindBin(eta);
//      binY = hist_btagEff_bcflav->GetYaxis()->FindBin(pt);
//  
//      efficiency = hist_btagEff_bcflav->GetBinContent(binX, binY);
//    }
//    else{
//      // Get the maximum bin number for x and y axes
//      maxXBin = hist_btagEff_lflav->GetXaxis()->GetNbins();
//      maxYBin = hist_btagEff_lflav->GetYaxis()->GetNbins();
//  
//      // Get the bin number corresponding to the provided x and y values
//      binX = hist_btagEff_lflav->GetXaxis()->FindBin(eta);
//      binY = hist_btagEff_lflav->GetYaxis()->FindBin(pt);
//  
//      efficiency = hist_btagEff_lflav->GetBinContent(binX, binY);
//    }
//  
//    return efficiency;
//}

//BTagEff
ROOT::RDF::RNode NanoAODAnalyzerrdframe::calculateBTagSF(RNode _rlm, std::vector<std::string> Jets_vars_names, int _case, const double btag_cut, std::string _BTaggingWP, std::string output_var)
{

    //case1 : fixedWP correction with mujets (here medium WP) # evaluate('systematic', 'working_point', 'flavor', 'abseta', 'pt')
    //for case 1  use one of the btvtype = "deepJet_mujets " , deepJet_comb" for b/c , deepJet_incl" for lightjets 
    if(_case==1){
  
        //======================================================================================================================================
        //>>>> function to calculate event weights for MC events, incorporating fixedWP correction with mujets (here medium WP)and systematics with
        //all variations seperately (up/down/correlated/uncorrelated/)
        //The weight for each variation is stored in separate columns (btag_SF_central,btag_SF_up, btag_SF_down, etc.). 
        // btagWeight_case1_central  is used to recalculate the eventweight. Other variations are intended for systematics calculations.
        //======================================================================================================================================
 
        auto btagweightgenerator_bcflav_case1 = [this](const ROOT::VecOps::RVec<int>& hadflav, const ROOT::VecOps::RVec<float>& etas, const ROOT::VecOps::RVec<float>& pts, const ROOT::VecOps::RVec<float>& btag_scores, const double btag_cut, std::string _BTagWP, const std::string& variation) -> float {
            double btagWeight_bcflav = 1.0;
            for (std::size_t i = 0; i < pts.size(); i++) {
                //std::cout<<"The BTag flavor"<< hadflav[i]<< " BTagJet eta:"<< etas[i]<<" BTagJet pt"<< pts[i]<<std::endl;
                if(std::abs(etas[i])>2.4999 || pts[i]<30.000001 || hadflav[i]==0) continue;
                //double selection_cut = _correction_btag1->("deepJet_wp_values")->evaluate(_BTagWP);
                if(btag_scores[i]>=btag_cut){
                    double bcjets_weights = _correction_btag1->at("deepJet_mujets")->evaluate({variation, _BTagWP, hadflav[i], std::fabs(etas[i]), pts[i]});
                    btagWeight_bcflav *= bcjets_weights;
                }
                else{
                    double bcjets_weights = _correction_btag1->at("deepJet_mujets")->evaluate({variation, _BTagWP, hadflav[i], std::fabs(etas[i]), pts[i]});
                    //double eff = getBTaggingEff(hadflav[i], etas[i], pts[i]);
                    double eff = 1.0;
                    btagWeight_bcflav *= (1 - bcjets_weights*eff)/(1-eff);
                }
            }
            return btagWeight_bcflav;
      };
  
      auto btagweightgenerator_lflav_case1 = [this](const ROOT::VecOps::RVec<int>& hadflav, const ROOT::VecOps::RVec<float>& etas, const ROOT::VecOps::RVec<float>& pts, const ROOT::VecOps::RVec<float>& btag_scores, const double btag_cut, std::string _BTagWP, const std::string& variation) -> float {
            double btagWeight_lflav = 1.0;
            for (std::size_t i = 0; i < pts.size(); i++) {
                //std::cout<<"The BTag flavor"<< hadflav[i]<< " BTagJet eta:"<< etas[i]<<" BTagJet pt"<< pts[i]<<std::endl;
                if(std::abs(etas[i])>2.4999 || pts[i]<30.000001 || hadflav[i]!=0) continue;
                //double selection_cut = _correction_btag1->("deepJet_wp_values")->evaluate(_BTagWP);
                if(btag_scores[i]>=btag_cut){
                  double lightjets_weights = _correction_btag1->at("deepJet_incl")->evaluate({variation, _BTagWP, hadflav[i], std::fabs(etas[i]), pts[i]});
                  btagWeight_lflav *= lightjets_weights;
                }
                else{
                  double lightjets_weights = _correction_btag1->at("deepJet_incl")->evaluate({variation, _BTagWP, hadflav[i], std::fabs(etas[i]), pts[i]});
                  //double eff = getBTaggingEff(hadflav[i], etas[i], pts[i]);
                  double eff = 1.0;
                  btagWeight_lflav *= (1 - lightjets_weights*eff)/(1-eff);
                }
            }
            return btagWeight_lflav;
      };
      // btag weight for each variation individually
      std::vector<std::string> variations = {"central", "up", "down", "up_correlated", "down_correlated", "up_uncorrelated", "down_uncorrelated", "up_statistic", "down_statistic"}; 
      for (const std::string& variation : variations) {
          std::string column_name_bcflav = output_var + "bcflav_" +variation;
          _rlm = _rlm.Define(column_name_bcflav, [btagweightgenerator_bcflav_case1, variation, btag_cut, _BTaggingWP](const ROOT::VecOps::RVec<int>& hadflav, const ROOT::VecOps::RVec<float>& etas, const ROOT::VecOps::RVec<float>& pts, const ROOT::VecOps::RVec<float>& btag_scores) {
          float weight = btagweightgenerator_bcflav_case1(hadflav, etas, pts, btag_scores, btag_cut, _BTaggingWP, variation);// Get the weight for the corresponding variation
          return weight;
          }, Jets_vars_names); //after all cuts, remove overlapped
  
          std::string column_name_lflav = output_var + "lflav_" +variation;
          _rlm = _rlm.Define(column_name_lflav, [btagweightgenerator_lflav_case1, variation, btag_cut, _BTaggingWP](const ROOT::VecOps::RVec<int>& hadflav, const ROOT::VecOps::RVec<float>& etas, const ROOT::VecOps::RVec<float>& pts, const ROOT::VecOps::RVec<float>& btag_scores) {
          float weight = btagweightgenerator_lflav_case1(hadflav, etas, pts, btag_scores, btag_cut, _BTaggingWP, variation);// Get the weight for the corresponding variation
          return weight;
          }, Jets_vars_names); //after all cuts, remove overlapped
          std::cout<< "BJet SF column name: " << column_name_bcflav<< " and " << column_name_lflav  << std::endl;
          if(isDefined("column_name_bcflav")){
          std::cout<< "BJet SF column: " << column_name_bcflav << " is saved in the Node."<< std::endl;
          }
          if(isDefined("column_name_lflav")){
          std::cout<< "BJet SF column: " << column_name_lflav << " is saved in the Node."<< std::endl;
          }
      }
    }
    else if(_case==3){
        //======================================================================================================================================
        //case3 - Shape correction
        //for case 3 : use btvtype': 'deepJet_shape' in jobconfiganalysis.py
        cout<<"case 3 Shape correction B tagging SF for MC "<<endl;
        //======================================================================================================================================
        //>>>> function to calculate event weights for MC events,based on DeepJet algorithm, incorporating shape correction with central variation
        //======================================================================================================================================
        auto btagweightgenerator3= [this](ints &hadflav, floats &etas, floats &pts, floats &btags)->float{
            double bweight=1.0;
      
            for (auto i=0; i<int(pts.size()); i++){
                if(std::abs(etas[i])>2.5 || pts[i]<30.000001) continue;
                double w = _correction_btag1->at(_btvtype)->evaluate({"central", int(hadflav[i]), fabs(float(etas[i])), float(pts[i]), float(btags[i])});
                bweight *= w;
            }
            return bweight;
        };
        
        cout<<"Generate case3 b-tagging weight"<<endl;
        std::string column_name = output_var + "case3";
        _rlm = _rlm.Define(column_name, btagweightgenerator3, Jets_vars_names);
        //Total event weight after shape correction
        //_rlm = _rlm.Define("evWeight", "pugenWeight*btagWeight_case3");
        std::cout<< "BJet SF column name: " << column_name << std::endl;
  
    }
    return _rlm;
}

void NanoAODAnalyzerrdframe::setupObjects()
{
    // Object selection will be defined in sequence.
    // Selected objects will be stored in new vectors.
    //selectJets();
    setHLT();
    removeOverlaps();
    selectFatJets();
}

void NanoAODAnalyzerrdframe::setupAnalysis()
{
    // Event weight for data it's always one. For MC, it depends on the sign
    //cout<<"year===="<< _year<< "==runtype=== " <<  _runtype <<endl;
    _rlm = _rlm.Define("one", "1.0");
    if (_isData && !isDefined("evWeight"))
    {
        _rlm = _rlm.Define("evWeight", [](){
                return 1.0;
            }, {} );
    }
    /*if (_isData && !isDefined("pugenWeight"))
    {
        _rlm = _rlm.Define("pugenWeight", [](){
                return 1.0;
            }, {} );
    }*/


    //defineMoreVars();
    //defineCuts();
    //bookHists();
    setupCuts_and_Hists();
    setupTree();
}


bool NanoAODAnalyzerrdframe::readgoodjson(string goodjsonfname)
{
    auto isgoodjsonevent = [this](unsigned int runnumber, unsigned int lumisection)
        {
            auto key = std::to_string(runnumber).c_str();

            bool goodeventflag = false;


            if (jsonroot.contains(key))
            {
                for (auto &v: jsonroot[key])
                {
                    if (v[0]<=lumisection && lumisection <=v[1]) goodeventflag = true;
                }
            }
            return goodeventflag;
        };

    if (goodjsonfname != "")
    {
        std::ifstream jsoninfile;
        jsoninfile.open(goodjsonfname);

        if (jsoninfile.good())
        {
            //using rapidjson
            //rapidjson::IStreamWrapper s(jsoninfile);
            //jsonroot.ParseStream(s);

            //using jsoncpp
            jsoninfile >> jsonroot;
            _rlm = _rlm.Define("goodjsonevent", isgoodjsonevent, {"run", "luminosityBlock"}).Filter("goodjsonevent");
            _jsonOK = true;
            return true;
        }
        else
        {
            cout << "Problem reading json file " << goodjsonfname << endl;
            return false;
        }
    }
    else
    {
        cout << "no JSON file given" << endl;
        return true;
    }
}

//HERE
//void NanoAODAnalyzerrdframe::setupJetMETCorrection(string fname, string jettag)
//{
//    // read from file 
//    _correction_jerc = correction::CorrectionSet::from_file(fname);
//    assert(_correction_jerc->validate());
//    // correction type(jobconfiganalysis.py)
//    _jetCorrector = _correction_jerc->compound().at(jettag);
//    _jetCorrectionUnc = _correction_jerc->at(_jercunctag);
//}
//
//
//// Adapted from https://github.com/cms-nanoAOD/nanoAOD-tools/blob/master/python/postprocessing/modules/jme/jetRecalib.py
//// and https://github.com/cms-nanoAOD/nanoAOD-tools/blob/master/python/postprocessing/modules/jme/JetRecalibrator.py
//void NanoAODAnalyzerrdframe::applyJetMETCorrections()
//{
//
//    auto appcorrlambdaf = [this](floats jetpts, floats jetetas, floats jetAreas, floats jetrawf, float rho)->floats
//    {
//        floats corrfactors;
//        corrfactors.reserve(jetpts.size());
//        for (unsigned int i =0; i<jetpts.size(); i++)
//        {
//            float rawjetpt = jetpts[i]*(1.0-jetrawf[i]);
//            float corrfactor = _jetCorrector->evaluate({jetAreas[i], jetetas[i], rawjetpt, rho});
//            corrfactors.emplace_back(rawjetpt * corrfactor);
//
//        }
//        return corrfactors;
//    };
//
//    auto jecuncertaintylambdaf= [this](floats jetpts, floats jetetas, floats jetAreas, floats jetrawf, float rho)->floats
//        {
//            floats uncertainties;
//            uncertainties.reserve(jetpts.size());
//            for (unsigned int i =0; i<jetpts.size(); i++)
//            {
//                float rawjetpt = jetpts[i]*(1.0-jetrawf[i]);
//                float corrfactor = _jetCorrector->evaluate({jetAreas[i], jetetas[i], rawjetpt, rho});
//                float unc = _jetCorrectionUnc->evaluate({corrfactor*rawjetpt, jetetas[i]});
//                uncertainties.emplace_back(unc);
//
//            }
//            return uncertainties;
//        };
//
//    auto metcorrlambdaf = [](float met, float metphi, floats jetptsbefore, floats jetptsafter, floats jetphis)->float
//    {
//        auto metx = met * cos(metphi);
//        auto mety = met * sin(metphi);
//        for (unsigned int i=0; i<jetphis.size(); i++)
//        {
//            if (jetptsafter[i]>15.0)
//            {
//                metx -= (jetptsafter[i] - jetptsbefore[i])*cos(jetphis[i]);
//                mety -= (jetptsafter[i] - jetptsbefore[i])*sin(jetphis[i]);
//            }
//        }
//        return float(sqrt(metx*metx + mety*mety));
//    };
//
//    auto metphicorrlambdaf = [](float met, float metphi, floats jetptsbefore, floats jetptsafter, floats jetphis)->float
//    {
//        auto metx = met * cos(metphi);
//        auto mety = met * sin(metphi);
//        for (unsigned int i=0; i<jetphis.size(); i++)
//        {
//            if (jetptsafter[i]>15.0)
//            {
//                metx -= (jetptsafter[i] - jetptsbefore[i])*cos(jetphis[i]);
//                mety -= (jetptsafter[i] - jetptsbefore[i])*sin(jetphis[i]);
//            }
//        }
//        return float(atan2(mety, metx));
//    };
//
//    if (_jetCorrector != 0)
//    {
//        _rlm = _rlm.Define("Jet_pt_corr", appcorrlambdaf, {"Jet_pt", "Jet_eta", "Jet_area", "Jet_rawFactor", "fixedGridRhoFastjetAll"});
//        _rlm = _rlm.Define("Jet_pt_relerror", jecuncertaintylambdaf, {"Jet_pt", "Jet_eta", "Jet_area", "Jet_rawFactor", "fixedGridRhoFastjetAll"});
//        _rlm = _rlm.Define("Jet_pt_corr_up", "Jet_pt_corr*(1.0f + Jet_pt_relerror)");
//        _rlm = _rlm.Define("Jet_pt_corr_down", "Jet_pt_corr*(1.0f - Jet_pt_relerror)");
//        _rlm = _rlm.Define("MET_pt_corr", metcorrlambdaf, {"MET_pt", "MET_phi", "Jet_pt", "Jet_pt_corr", "Jet_phi"});
//        _rlm = _rlm.Define("MET_phi_corr", metphicorrlambdaf, {"MET_pt", "MET_phi", "Jet_pt", "Jet_pt_corr", "Jet_phi"});
//        _rlm = _rlm.Define("MET_pt_corr_up", metcorrlambdaf, {"MET_pt", "MET_phi", "Jet_pt", "Jet_pt_corr_up", "Jet_phi"});
//        _rlm = _rlm.Define("MET_phi_corr_up", metphicorrlambdaf, {"MET_pt", "MET_phi", "Jet_pt", "Jet_pt_corr_up", "Jet_phi"});
//        _rlm = _rlm.Define("MET_pt_corr_down", metcorrlambdaf, {"MET_pt", "MET_phi", "Jet_pt", "Jet_pt_corr_down", "Jet_phi"});
//        _rlm = _rlm.Define("MET_phi_corr_down", metphicorrlambdaf, {"MET_pt", "MET_phi", "Jet_pt", "Jet_pt_corr_down", "Jet_phi"});
//    }
//
//}

//void NanoAODAnalyzerrdframe::GetJetsys(string sys){
//
//                auto getJERCptResolution=[this](floats &etas, floats &pts, floats &rhos)->floats
//                {
//                        return ::JERCptResolution(_jerc_fname, _jercptres_type, etas, pts, rhos);
//                };
//
//        //_rlm = _rlm.Define(sys, ::getsysJerc, {_jerc_fname, "Jet_pt_smear", "Jet_eta", _jercsys_total})
//        _rlm = _rlm.Define("Jet_pt_"+sys+"Up", sys+"*2*Jet_pt+Jet_pt")
//               .Define("Jet_pt_"+sys+"Down", "-"+sys+"*2*Jet_pt+Jet_pt")
//               .Define("Jet_mass_"+sys+"Up", sys+"*Jet_mass+Jet_mass")
//               .Define("Jet_mass_"+sys+"Down", "-"+sys+"*Jet_mass+Jet_mass");
//                _rlm = _rlm.Define("JERCptResolution"+sys+"Up", getJERCptResolution, {"Jet_eta","Jet_pt_"+sys+"Up","fixedGridRhoFastjetAll"});
//                _rlm = _rlm.Define("JERCptResolution"+sys+"Down", getJERCptResolution, {"Jet_eta","Jet_pt_"+sys+"Down","fixedGridRhoFastjetAll"});
//                _rlm = _rlm.Define("GenMatchJetPtvars"+sys+"Up", ::GenMatchJetPt, {"Jet_pt_"+sys+"Up", "Jet_eta", "Jet_phi", "Jet_mass_"+sys+"Up", "GenJet_pt", "GenJet_eta", "GenJet_phi", "GenJet_mass", "JERCptResolution"+sys+"Up"});
//                _rlm = _rlm.Define("GenMatchJetPtvars"+sys+"Down", ::GenMatchJetPt, {"Jet_pt_"+sys+"Down", "Jet_eta", "Jet_phi", "Jet_mass_"+sys+"Down", "GenJet_pt", "GenJet_eta", "GenJet_phi", "GenJet_mass", "JERCptResolution"+sys+"Down"});
//                _rlm = _rlm.Define("c_JER"+sys+"Up", ::getcJER, {"Jet_pt_"+sys+"Up", "GenMatchJetPtvars"+sys+"Up", "JERCSF", "JERCptResolution"+sys+"Up"});
//                _rlm = _rlm.Define("c_JER"+sys+"Down", ::getcJER, {"Jet_pt_"+sys+"Down", "GenMatchJetPtvars"+sys+"Down", "JERCSF", "JERCptResolution"+sys+"Down"});
//                _rlm = _rlm.Define("Jet_pt_smear_"+sys+"Up", "c_JER"+sys+"Up*Jet_pt_"+sys+"Up");
//                _rlm = _rlm.Define("Jet_pt_smear_"+sys+"Down", "c_JER"+sys+"Down*Jet_pt_"+sys+"Down");
//                _rlm = _rlm.Define("corrmet_pt_"+sys+"Up", ::getmetsmear, {"corrmetjson_pt", "corrmet_phi", "Jet_pt_"+sys+"Up", "Jet_pt_smear_"+sys+"Up", "Jet_phi"});
//                _rlm = _rlm.Define("corrmet_pt_"+sys+"Down", ::getmetsmear, {"corrmetjson_pt", "corrmet_phi", "Jet_pt_"+sys+"Down", "Jet_pt_smear_"+sys+"Down", "Jet_phi"});
//
//        _rlm = _rlm.Define("goodJets_"+sys+"Up", "goodJetsID && Jet_pt_smear_"+sys+"Up>30.0 && abs(Jet_eta)<2.5");
//        _rlm = _rlm.Define("goodJets_pt_"+sys+"Up", "Jet_pt_smear_"+sys+"Up[goodJets_"+sys+"Up]")
//               .Define("goodJets_eta_"+sys+"Up", "Jet_eta[goodJets_"+sys+"Up]")
//               .Define("goodJets_phi_"+sys+"Up", "Jet_phi[goodJets_"+sys+"Up]")
//               .Define("goodJets_mass_"+sys+"Up", "Jet_mass[goodJets_"+sys+"Up]")
//               .Define("goodJetsHT_"+sys+"Up", "Sum(goodJets_pt_"+sys+"Up)")
//               .Define("goodJets_deepjetbtag_"+sys+"Up", "Jet_btagDeepFlavB[goodJets_"+sys+"Up]")
//               .Define("goodJets_hadflav_"+sys+"Up", "Jet_hadronFlavour[goodJets_"+sys+"Up]")
//               .Define("goodJets_4vecs_"+sys+"Up", ::generate_4vec, {"goodJets_pt_"+sys+"Up", "goodJets_eta_"+sys+"Up", "goodJets_phi_"+sys+"Up", "goodJets_mass_"+sys+"Up"});
//
//        _rlm = _rlm.Define("goodJets_"+sys+"Down", "goodJetsID && Jet_pt_smear_"+sys+"Down>30.0 && abs(Jet_eta)<2.5");
//        _rlm = _rlm.Define("goodJets_pt_"+sys+"Down", "Jet_pt_smear_"+sys+"Down[goodJets_"+sys+"Down]")
//               .Define("goodJets_eta_"+sys+"Down", "Jet_eta[goodJets_"+sys+"Down]")
//               .Define("goodJets_phi_"+sys+"Down", "Jet_phi[goodJets_"+sys+"Down]")
//               .Define("goodJets_mass_"+sys+"Down", "Jet_mass[goodJets_"+sys+"Down]")
//               .Define("goodJetsHT_"+sys+"Down", "Sum(goodJets_pt_"+sys+"Down)")
//               .Define("goodJets_deepjetbtag_"+sys+"Down", "Jet_btagDeepFlavB[goodJets_"+sys+"Down]")
//               .Define("goodJets_hadflav_"+sys+"Down", "Jet_hadronFlavour[goodJets_"+sys+"Down]")
//               .Define("goodJets_4vecs_"+sys+"Down", ::generate_4vec, {"goodJets_pt_"+sys+"Down", "goodJets_eta_"+sys+"Down", "goodJets_phi_"+sys+"Down", "goodJets_mass_"+sys+"Down"});
//}
//
//void NanoAODAnalyzerrdframe::setupJetMETCorrection(string fname, string jettag){
//  
//    cout << "setup JETMET correction" << endl;
//    // read from file 
//    _correction_jerc = correction::CorrectionSet::from_file(fname);//jercfname=json
//    assert(_correction_jerc->validate()); //the assert functionality : check if the parameters passed to a function are valid =1:true
//    // correction type(jobconfiganalysis.py)
//    cout<<"json file=="<<fname<<endl;
//    _jetCorrector = _correction_jerc->compound().at(jettag);//jerctag#JSON (JEC,compound)compoundLevel="L1L2L3Res"
//    cout<<"jettag =="<<jettag<<endl;
//    _jetCorrectionUnc = _correction_jerc->at(_jercunctag);
//}
//
//void NanoAODAnalyzerrdframe::applyJetMETCorrections(){
//
//    cout << "apply JETMET correction" << endl;
//  
//    auto appcorrlambdaf = [this](floats jetpts, floats jetetas, floats jetAreas, floats jetrawf, float rho)->floats
//    {
//        floats corrfactors;
//        corrfactors.reserve(jetpts.size());
//        for (unsigned int i =0; i<jetpts.size(); i++)
//        {
//            float rawjetpt = jetpts[i]*(1.0-jetrawf[i]);
//            //std::cout<<"jetpt===="<< jetpts[i] <<std::endl;
//            //float jet_rawmass = jet_mass * (1 - jet.rawFactor)
//            //std::cout<<"rawjetpt===="<< rawjetpt <<std::endl;
//            float corrfactor = _jetCorrector->evaluate({jetAreas[i], jetetas[i], rawjetpt, rho});
//            //std::cout<<"correction factor===="<< corrfactor <<std::endl;
//            corrfactors.emplace_back(rawjetpt * corrfactor);
//            //std::cout<<"rawjetpt* corrfactor ===="<< rawjetpt * corrfactor <<std::endl;
//  
//        }
//        //std::cout<<"Facsss===="<< corrfactors <<std::endl;
//        return corrfactors;
//      
//    };
//  
//    auto jecuncertaintylambdaf= [this](floats jetpts, floats jetetas, floats jetAreas, floats jetrawf, float rho)->floats
//      {
//          floats uncertainties;
//          uncertainties.reserve(jetpts.size());
//          for (unsigned int i =0; i<jetpts.size(); i++){
//                float rawjetpt = jetpts[i]*(1.0-jetrawf[i]);
//                        
//                float corrfactor = _jetCorrector->evaluate({jetAreas[i], jetetas[i], rawjetpt, rho});
//                //print("\njet SF for shape correction:")
//                //print(f"SF: {corrfactor}")
//                float unc = _jetCorrectionUnc->evaluate({corrfactor*rawjetpt, jetetas[i]});
//                uncertainties.emplace_back(unc);
//  
//          }
//          return uncertainties;
//      };
//  
//    auto metcorrlambdaf = [](float met, float metphi, floats jetptsbefore, floats jetptsafter, floats jetphis)->float
//    {
//        auto metx = met * cos(metphi);
//        auto mety = met * sin(metphi);
//        for (unsigned int i=0; i<jetphis.size(); i++){
//            if (jetptsafter[i]>15.0){
//                metx -= (jetptsafter[i] - jetptsbefore[i])*cos(jetphis[i]);
//                mety -= (jetptsafter[i] - jetptsbefore[i])*sin(jetphis[i]);
//            }
//        }
//        return float(sqrt(metx*metx + mety*mety));
//    };
//  
//    auto metphicorrlambdaf = [](float met, float metphi, floats jetptsbefore, floats jetptsafter, floats jetphis)->float
//    {
//        auto metx = met * cos(metphi);
//        auto mety = met * sin(metphi);
//        for (unsigned int i=0; i<jetphis.size(); i++){
//
//            if (jetptsafter[i]>15.0){
//                metx -= (jetptsafter[i] - jetptsbefore[i])*cos(jetphis[i]);
//                mety -= (jetptsafter[i] - jetptsbefore[i])*sin(jetphis[i]);
//            }
//        }
//        return float(atan2(mety, metx));
//    };
//  
//    if (_jetCorrector != 0)
//    {
//          //cout << "jetcorrector==" <<_jetCorrector << endl;
//  
//      _rlm = _rlm.Define("Jet_pt_corr", appcorrlambdaf, {"Jet_pt", "Jet_eta", "Jet_area", "Jet_rawFactor", "fixedGridRhoFastjetAll"});
//      _rlm = _rlm.Define("Jet_pt_relerror", jecuncertaintylambdaf, {"Jet_pt", "Jet_eta", "Jet_area", "Jet_rawFactor", "fixedGridRhoFastjetAll"});
//      _rlm = _rlm.Define("Jet_pt_corr_up", "Jet_pt_corr*(1.0f + Jet_pt_relerror)");
//      _rlm = _rlm.Define("Jet_pt_corr_down", "Jet_pt_corr*(1.0f - Jet_pt_relerror)");
//      _rlm = _rlm.Define("MET_pt_corr", metcorrlambdaf, {"MET_pt", "MET_phi", "Jet_pt", "Jet_pt_corr", "Jet_phi"});
//      _rlm = _rlm.Define("MET_phi_corr", metphicorrlambdaf, {"MET_pt", "MET_phi", "Jet_pt", "Jet_pt_corr", "Jet_phi"});
//      _rlm = _rlm.Define("MET_pt_corr_up", metcorrlambdaf, {"MET_pt", "MET_phi", "Jet_pt", "Jet_pt_corr_up", "Jet_phi"});
//      _rlm = _rlm.Define("MET_phi_corr_up", metphicorrlambdaf, {"MET_pt", "MET_phi", "Jet_pt", "Jet_pt_corr_up", "Jet_phi"});
//      _rlm = _rlm.Define("MET_pt_corr_down", metcorrlambdaf, {"MET_pt", "MET_phi", "Jet_pt", "Jet_pt_corr_down", "Jet_phi"});
//      _rlm = _rlm.Define("MET_phi_corr_down", metphicorrlambdaf, {"MET_pt", "MET_phi", "Jet_pt", "Jet_pt_corr_down", "Jet_phi"});
//    }
//
//    if(!_isData){
//                _rlm = _rlm.Define("MCorData", "-1.0");
//                auto getJERCptResolution=[this](floats &etas, floats &pts, floats &rhos)->floats
//                {
//                        return ::JERCptResolution(_jerc_fname, _jercptres_type, etas, pts, rhos);
//                };
//
//                auto getJERCSF=[this](floats &etas)->floats
//                {
//                        return ::JERCSF(_jerc_fname, _jercSF_type,"nom", etas);
//                };
//
//        //auto getmetptmc=[this](float &pts, float &phis, int &npv, unsigned int &runnumber)->float
//        //{
//        //                if(pts > 0.0 && pts < 6500.0 && abs(phis) < 3.15){
//        //            float w = _met_fname->at(_metptmctag)->evaluate({float(pts),float(phis), float(npv), float(runnumber)});
//        //                        return w;
//        //                }
//        //                else{
//        //                        return float(pts);
//        //                }
//        //                //return float(pts);
//        //};
//
//        //auto getmetphimc=[this](float &pts, float &phis, int &npv, unsigned int &runnumber)->float
//        //{
//        //                if(pts > 0.0 && pts < 6500.0 && abs(phis) < 3.15){
//        //            float w = _met_fname->at(_metphimctag)->evaluate({float(pts),float(phis), float(npv), float(runnumber)});
//        //                        return w;
//        //                }
//        //                else{
//        //            return float(phis);
//        //                }
//        //         //       return float(phis);
//        //};
//
//        _rlm = _rlm.Define("JERCptResolution", getJERCptResolution, {"Jet_eta","Jet_pt","fixedGridRhoFastjetAll"});
//        _rlm = _rlm.Define("JERCSF", getJERCSF, {"Jet_eta"});
//        _rlm = _rlm.Define("GenMatchJetPtvars", ::GenMatchJetPt, {"Jet_pt", "Jet_eta", "Jet_phi", "Jet_mass", "GenJet_pt", "GenJet_eta", "GenJet_phi", "GenJet_mass", "JERCptResolution"});
//        _rlm = _rlm.Define("c_JER", ::getcJER, {"Jet_pt", "GenMatchJetPtvars", "JERCSF", "JERCptResolution"});
//        _rlm = _rlm.Define("Jet_pt_smear_nom", "c_JER*Jet_pt");
//        //_rlm = _rlm.Define("corrmet_phi", getmetphimc, {"MET_pt", "MET_phi", "PV_npvs", "run"}); // this is the good one
//        //_rlm = _rlm.Define("corrmetjson_pt", getmetptmc, {"MET_pt", "MET_phi", "PV_npvs", "run"}); // this is the good one
//
//        _rlm = _rlm.Define("corrmet_pt_nom", ::getmetsmear, {"corrmetjson_pt", "corrmet_phi", "Jet_pt", "Jet_pt_smear_nom", "Jet_phi"}); // this is the good one
//
//        _rlm = _rlm.Define("rawmet_pt", "MET_pt");
//        _rlm = _rlm.Define("rawmet_phi", "MET_phi");
//
//    }
//    else{
//                _rlm = _rlm.Define("MCorData", "1.0");
//        _rlm = _rlm.Define("Jet_pt_smear_nom", "Jet_pt");
//        _rlm = _rlm.Define("run_numbers", "float(run)");
//
//        //if(_year == 2018){
//        //    _rlm = _rlm.Define("corrmet_ptphi", ::calmetptphidata, {"MET_pt", "MET_phi", "PV_npvs", "run_numbers"})
//        //        .Define("corrmet_pt_nom", "corrmet_ptphi[0]")
//        //        .Define("corrmet_phi", "corrmet_ptphi[1]");
//        //}
//        //if(_year == 2017){
//        //    _rlm = _rlm.Define("corrmet_ptphi", ::calmetptphidata17, {"MET_pt", "MET_phi", "PV_npvs", "run_numbers"})
//        //        .Define("corrmet_pt_nom", "corrmet_ptphi[0]")
//        //        .Define("corrmet_phi", "corrmet_ptphi[1]");
//        //}
//        //if(_year == 2016 && _runtype == "preVFP_UL"){
//        //    _rlm = _rlm.Define("corrmet_ptphi", ::calmetptphidata16pre, {"MET_pt", "MET_phi", "PV_npvs", "run_numbers"})
//        //        .Define("corrmet_pt_nom", "corrmet_ptphi[0]")
//        //        .Define("corrmet_phi", "corrmet_ptphi[1]");
//        //}
//        //if(_year == 2016 && _runtype == "postVFP_UL"){
//        //    _rlm = _rlm.Define("corrmet_ptphi", ::calmetptphidata16post, {"MET_pt", "MET_phi", "PV_npvs", "run_numbers"})
//        //        .Define("corrmet_pt_nom", "corrmet_ptphi[0]")
//        //        .Define("corrmet_phi_nom", "corrmet_ptphi[1]");
//        //}
//        _rlm = _rlm.Define("rawmet_pt", "MET_pt");
//        _rlm = _rlm.Define("rawmet_phi", "MET_phi");
//    }
//
//    _rlm = _rlm.Define("goodJetsID", JetID(6)); //without pt-eta cuts
//    //     _rlm = _rlm.Define("goodJets", "goodJetsID && Jet_pt_smear>30.0 && abs(Jet_eta)<2.5");
//    _rlm = _rlm.Define("goodJets", "goodJetsID && Jet_pt_smear_nom>30.0 && abs(Jet_eta)<2.5");
//    _rlm = _rlm.Define("goodJets_pt", "Jet_pt_smear_nom[goodJets]")
//        .Define("goodJets_eta", "Jet_eta[goodJets]")
//        .Define("goodJets_phi", "Jet_phi[goodJets]")
//        .Define("goodJets_mass", "Jet_mass[goodJets]")
//        .Define("goodJets_deepjetbtag", "Jet_btagDeepFlavB[goodJets]")
//        .Define("NgoodJets", "int(goodJets_pt.size())")
//        .Define("goodJetsHT_nom", "Sum(goodJets_pt)")
//        .Define("goodJets_4vecs", ::generate_4vec, {"goodJets_pt", "goodJets_eta", "goodJets_phi", "goodJets_mass"});
//
//    if(!_isData){
//
//                auto getJERCSFup=[this](floats &etas)->floats
//                {
//                        return ::JERCSF(_jerc_fname, _jercSF_type,"up", etas);
//                };
//
//                auto getJERCSFdown=[this](floats &etas)->floats
//                {
//                        return ::JERCSF(_jerc_fname, _jercSF_type,"down", etas);
//                };
//
//        _rlm = _rlm.Define("goodJets_hadflav", "Jet_hadronFlavour[goodJets]");
//                if(_jecsys == "Total"){ // HERE!
//                auto getJECSFs = [this](floats &pts, floats &etas)->floats
//                {
//                        return ::getsysJERC(_jerc_fname, pts, etas, _jercsys_total);
//                };
//                _rlm = _rlm.Define("JecTotal",getJECSFs, {"Jet_pt","Jet_eta"});
//
//                        GetJetsys("JecTotal");
//                }
//
//                if(_jersys == "True"){
//                        _rlm = _rlm.Define("JERCSFUp", getJERCSFup, {"Jet_eta"})
//                                  .Define("JERCSFUp2Sig", "JERCSF+2*(JERCSFUp-JERCSF)");
//                        _rlm = _rlm.Define("JERCSFDown", getJERCSFdown, {"Jet_eta"})
//                                  .Define("JERCSFDown2Sig", "JERCSF+2*(JERCSFDown-JERCSF)");
//                        _rlm = _rlm.Define("c_JERUp", ::getcJER, {"Jet_pt", "GenMatchJetPtvars", "JERCSFUp2Sig", "JERCptResolution"});
//                        _rlm = _rlm.Define("c_JERDown", ::getcJER, {"Jet_pt", "GenMatchJetPtvars", "JERCSFDown2Sig", "JERCptResolution"});
//                        _rlm = _rlm.Define("Jet_pt_smear_JERUp", "c_JERUp*Jet_pt");
//                        _rlm = _rlm.Define("Jet_pt_smear_JERDown", "c_JERDown*Jet_pt");
//                        _rlm = _rlm.Define("corrmet_pt_JERUp", ::getmetsmear, {"corrmetjson_pt", "corrmet_phi", "Jet_pt", "Jet_pt_smear_JERUp", "Jet_phi"});
//                        _rlm = _rlm.Define("corrmet_pt_JERDown", ::getmetsmear, {"corrmetjson_pt", "corrmet_phi", "Jet_pt", "Jet_pt_smear_JERDown", "Jet_phi"});
//                        _rlm = _rlm.Define("goodJets_JERUp", "goodJetsID && Jet_pt_smear_JERUp>30.0 && abs(Jet_eta)<2.5");
//                        _rlm = _rlm.Define("goodJets_JERDown", "goodJetsID && Jet_pt_smear_JERDown>30.0 && abs(Jet_eta)<2.5");
//                        _rlm = _rlm.Define("goodJets_pt_JERUp", "Jet_pt_smear_JERUp[goodJets_JERUp]")
//                                .Define("goodJets_eta_JERUp", "Jet_eta[goodJets_JERUp]")
//                                .Define("goodJets_phi_JERUp", "Jet_phi[goodJets_JERUp]")
//                                .Define("goodJets_mass_JERUp", "Jet_mass[goodJets_JERUp]")
//                                .Define("goodJets_deepjetbtag_JERUp", "Jet_btagDeepFlavB[goodJets_JERUp]")
//                                .Define("goodJets_hadflav_JERUp", "Jet_hadronFlavour[goodJets_JERUp]")
//                                .Define("NgoodJets_JERUp", "int(goodJets_pt_JERUp.size())")
//                                .Define("goodJetsHT_JERUp", "Sum(goodJets_pt_JERUp)")
//                                .Define("goodJets_4vecs_JERUp", ::generate_4vec, {"goodJets_pt_JERUp", "goodJets_eta_JERUp", "goodJets_phi_JERUp", "goodJets_mass_JERUp"});
//
//                        _rlm = _rlm.Define("goodJets_pt_JERDown", "Jet_pt_smear_JERDown[goodJets_JERDown]")
//                                .Define("goodJets_eta_JERDown", "Jet_eta[goodJets_JERDown]")
//                                .Define("goodJets_phi_JERDown", "Jet_phi[goodJets_JERDown]")
//                                .Define("goodJets_mass_JERDown", "Jet_mass[goodJets_JERDown]")
//                                .Define("goodJets_deepjetbtag_JERDown", "Jet_btagDeepFlavB[goodJets_JERDown]")
//                                .Define("goodJets_hadflav_JERDown", "Jet_hadronFlavour[goodJets_JERDown]")
//                                .Define("NgoodJets_JERDown", "int(goodJets_pt_JERDown.size())")
//                                .Define("goodJetsHT_JERDown", "Sum(goodJets_pt_JERDown)")
//                                .Define("goodJets_4vecs_JERDown", ::generate_4vec, {"goodJets_pt_JERDown", "goodJets_eta_JERDown", "goodJets_phi_JERDown", "goodJets_mass_JERDown"});
//                }
//
//    }
//
//  
//}
                        

/*void NanoAODAnalyzerrdframe::selectJets()
{
    // apparently size() returns long int, which ROOT doesn't recognized for branch types
    // , so it must be cast into int if you want to save them later into a TTree
    _rlm = _rlm.Define("jetcuts", "Jet_pt>30.0 && abs(Jet_eta)<2.4 && Jet_jetId>0")
            .Define("Sel_jetpt", "Jet_pt[jetcuts]")
            .Define("Sel_jeteta", "Jet_eta[jetcuts]")
            .Define("Sel_jetphi", "Jet_phi[jetcuts]")
            .Define("Sel_jetmass", "Jet_mass[jetcuts]")
            .Define("Sel_jetbtag", "Jet_btagCSVV2[jetcuts]")
            .Define("njetspass", "int(Sel_jetpt.size())")
            .Define("jet4vecs", ::generate_4vec, {"Sel_jetpt", "Sel_jeteta", "Sel_jetphi", "Sel_jetmass"});


    _rlm = _rlm.Define("btagcuts", "Sel_jetbtag>0.8")
            .Define("Sel_bjetpt", "Sel_jetpt[btagcuts]")
            .Define("Sel_bjeteta", "Sel_jeteta[btagcuts]")
            .Define("Sel_bjetphi", "Sel_jetphi[btagcuts]")
            .Define("Sel_bjetm", "Sel_jetmass[btagcuts]")
            .Define("bnjetspass", "int(Sel_bjetpt.size())")
            .Define("bjet4vecs", ::generate_4vec, {"Sel_bjetpt", "Sel_bjeteta", "Sel_bjetphi", "Sel_bjetm"});
            ;

            // calculate event weight for MC only
    if (!_isData && !isDefined("evWeight"))
    {
        _rlm = _rlm.Define("jetcutsforsf", "Jet_pt>25.0 && abs(Jet_eta)<2.4 ")
                .Define("Sel_jetforsfpt", "Jet_pt[jetcutsforsf]")
                .Define("Sel_jetforsfeta", "Jet_eta[jetcutsforsf]")
                .Define("Sel_jetforsfhad", "Jet_hadronFlavour[jetcutsforsf]")
                .Define("Sel_jetcsvv2", "Jet_btagCSVV2[jetcutsforsf]")
                .Define("Sel_jetdeepb", "Jet_btagDeepB[jetcutsforsf]");

        auto btvcentral = [this](floats &pts, floats &etas, ints &hadflav, floats &btags)->floats
        {
            return ::btvcorrection(_correction_btag1, _btvtype, "central", pts, etas, hadflav, btags); // defined in utility.cpp
        };


        _rlm = _rlm.Define("Sel_jet_deepJet_shape_central", btvcentral, {"Sel_jetforsfpt", "Sel_jetforsfeta", "Sel_jetforsfhad", "Sel_jetdeepb"});
        //_rlm = _rlm.Define("Sel_jet_deepJet_shape_central",[this](floats &pts, floats &etas, ints &hadflav, floats &btags){return ::btvcorrection(_correction_btag1, "deepJet_shape", "central", pts, etas, hadflav, btags);}
            //              , {"Sel_jetforsfpt", "Sel_jetforsfeta", "Sel_jetforsfhad", "Sel_jetdeepb"});

        // function to calculate event weight for MC events based on DeepCSV algorithm
        auto btagweightgenerator3= [this](floats &pts, floats &etas, ints &hadflav, floats &btags)->float
        {
            double bweight=1.0;

            for (auto i=0; i<pts.size(); i++)
            {
                double w = _correction_btag1->at(_btvtype)->evaluate({"central", int(hadflav[i]), fabs(float(etas[i])), float(pts[i]), float(btags[i])});
                bweight *= w;
            }
            return bweight;
        };
        _rlm = _rlm.Define("btagWeight_DeepJetrecalc", btagweightgenerator3, {"Sel_jetforsfpt", "Sel_jetforsfeta", "Sel_jetforsfhad", "Sel_jetdeepb"});
        _rlm = _rlm.Define("evWeight", "pugenWeight * btagWeight_DeepJetrecalc");
    }

}*/

void NanoAODAnalyzerrdframe::removeOverlaps()
{
    // lambda function
    // for checking overlapped jets with electrons
    auto checkoverlap = [](FourVectorVec &seljets, FourVectorVec &selele)
        {
            doubles mindrlepton;
            //cout << "selected jets size" << seljets.size() << endl;
            //cout << "selected electrons size" << selele.size() << endl;

            for (auto ajet: seljets)
            {
                std::vector<double> drelejet(selele.size());
                for (auto alepton: selele)
                {
                    auto dr = ROOT::Math::VectorUtil::DeltaR(ajet, alepton);
                    drelejet.emplace_back(dr);
                }
                auto mindr = selele.size()==0 ? 6.0 : *std::min_element(drelejet.begin(), drelejet.end());
                mindrlepton.emplace_back(mindr);
            }

            return mindrlepton;
        };
    //cout << "overlap removal" << endl;
    _rlm = _rlm.Define("mindrlepton", checkoverlap, {"jet4vecs","ele4vecs"});

    //cout << "redefine cleaned jets" << endl;
    _rlm = _rlm.Define("overlapcheck", "mindrlepton>0.4");

    _rlm =  _rlm.Define("Sel2_jetpt", "Sel_jetpt[overlapcheck]")
        .Define("Sel2_jeteta", "Sel_jeteta[overlapcheck]")
        .Define("Sel2_jetphi", "Sel_jetphi[overlapcheck]")
        .Define("Sel2_jetmass", "Sel_jetmass[overlapcheck]")
        .Define("Sel2_jetbtag", "Sel_jetbtag[overlapcheck]")
        .Define("ncleanjetspass", "int(Sel2_jetpt.size())")
        .Define("cleanjet4vecs", ::generate_4vec, {"Sel2_jetpt", "Sel2_jeteta", "Sel2_jetphi", "Sel2_jetmass"})
        .Define("Sel2_jetHT", "Sum(Sel2_jetpt)")
        .Define("Sel2_jetweight", "std::vector<double>(ncleanjetspass, evWeight)"); //


    _rlm = _rlm.Define("btagcuts2", "Sel2_jetbtag>0.8")
            .Define("Sel2_bjetpt", "Sel2_jetpt[btagcuts2]")
            .Define("Sel2_bjeteta", "Sel2_jeteta[btagcuts2]")
            .Define("Sel2_bjetphi", "Sel2_jetphi[btagcuts2]")
            .Define("Sel2_bjetmass", "Sel2_jetmass[btagcuts2]")
            .Define("ncleanbjetspass", "int(Sel2_bjetpt.size())")
            .Define("Sel2_bjetHT", "Sum(Sel2_bjetpt)")
            .Define("cleanbjet4vecs", ::generate_4vec, {"Sel2_bjetpt", "Sel2_bjeteta", "Sel2_bjetphi", "Sel2_bjetmass"});

}

void NanoAODAnalyzerrdframe::selectFatJets()
{
    _rlm = _rlm.Define("fatjetcuts", "FatJet_pt>400.0 && abs(FatJet_eta)<2.4 && FatJet_tau1>0.0 && FatJet_tau2>0.0 && FatJet_tau3>0.0 && FatJet_tau3/FatJet_tau2<0.5")
                .Define("Sel_fatjetpt", "FatJet_pt[fatjetcuts]")
                .Define("Sel_fatjeteta", "FatJet_eta[fatjetcuts]")
                .Define("Sel_fatjetphi", "FatJet_phi[fatjetcuts]")
                .Define("Sel_fatjetmass", "FatJet_mass[fatjetcuts]")
                .Define("nfatjetspass", "int(Sel_fatjetpt.size())")
                .Define("Sel_fatjetweight", "std::vector<double>(nfatjetspass, evWeight)")
                .Define("Sel_fatjet4vecs", ::generate_4vec, {"Sel_fatjetpt", "Sel_fatjeteta", "Sel_fatjetphi", "Sel_fatjetmass"});
}


bool NanoAODAnalyzerrdframe::helper_1DHistCreator(std::string hname, std::string title, const int nbins, const double xlow, const double xhi, std::string rdfvar, std::string evWeight, RNode *anode)
{
    //cout << "1DHistCreator " << hname  << endl;

    RDF1DHist histojets = anode->Histo1D({hname.c_str(), title.c_str(), nbins, xlow, xhi}, rdfvar, evWeight); // Fill with weight given by evWeight
    _th1dhistos[hname] = histojets;
    //histojets.GetPtr()->Print("all");
    return true;
}

//for 2D histograms//
//bool NanoAODAnalyzerrdframe::helper_2DHistCreator(std::string hname, std::string title, const int nbinsx, const double xlow, const double xhi, const int nbinsy, const double ylow, const double yhi,std::string rdfvarx,std::string rdfvary, std::string evWeight, RNode *anode)
//{
//  //cout << "2DHistCreator " << hname  << endl;
//
//  RDF2DHist histojets = anode->Histo2D({hname.c_str(), title.c_str(), nbinsx, xlow, xhi,nbinsy, ylow, yhi}, rdfvarx,rdfvary, evWeight); // Fill with weight given by evWeight
//  _th2dhistos[hname] = histojets;
//  histojets.GetPtr()->Print("all");
//  return true;
//}

// Automatically loop to create
void NanoAODAnalyzerrdframe::setupCuts_and_Hists()
{
    cout << "setting up definitions, cuts, and histograms" <<endl;

    for ( auto &c : _varinfovector)
    {
        if (c.mincutstep.length()==0) _rlm = _rlm.Define(c.varname, c.vardefinition);
    }

    for (auto &x : _hist1dinfovector)
    {
        std::string hpost = "_nocut";

        if (x.mincutstep.length()==0)
        {
            helper_1DHistCreator(std::string(x.hmodel.fName)+hpost,  std::string(x.hmodel.fTitle)+hpost, x.hmodel.fNbinsX, x.hmodel.fXLow, x.hmodel.fXUp, x.varname, x.weightname, &_rlm);
        }
    }

//    //for 2D histograms
//    for (auto &x : _hist2dinfovector)
//    {
//        std::string hpost = "_nocut";
//
//        if (x.mincutstep.length()==0)
//        {
//            helper_2DHistCreator(std::string(x.hmodel.fName)+hpost,  std::string(x.hmodel.fTitle)+hpost, x.hmodel.fNbinsX, x.hmodel.fXLow, x.hmodel.fXUp, x.hmodel.fNbinsY, x.hmodel.fYLow, x.hmodel.fYUp, x.varname1, x.varname2, x.weightname, &_rlm);
//        }
//    }

    _rnt.setRNode(&_rlm);

    for (auto acut : _cutinfovector)
    {
        std::string cutname = "cut"+ acut.idx;
        std::string hpost = "_"+cutname;
        RNode *r = _rnt.getParent(acut.idx)->getRNode();
        auto rnext = new RNode(r->Define(cutname, acut.cutdefinition));
        *rnext = rnext->Filter(cutname);

        for ( auto &c : _varinfovector)
        {
            if (acut.idx.compare(c.mincutstep)==0) *rnext = rnext->Define(c.varname, c.vardefinition);
        }
        for (auto &x : _hist1dinfovector)
        {
            if (acut.idx.compare(0, x.mincutstep.length(), x.mincutstep)==0)
            {
                helper_1DHistCreator(std::string(x.hmodel.fName)+hpost,  std::string(x.hmodel.fTitle)+hpost, x.hmodel.fNbinsX, x.hmodel.fXLow, x.hmodel.fXUp, x.varname, x.weightname, rnext);
            }
        }

//        //for 2DHistograms
//        for (auto &x : _hist2dinfovector)
//        {
//            if (acut.idx.compare(0, x.mincutstep.length(), x.mincutstep)==0)
//            {
//                helper_2DHistCreator(std::string(x.hmodel.fName)+hpost,  std::string(x.hmodel.fTitle)+hpost, x.hmodel.fNbinsX, x.hmodel.fXLow, x.hmodel.fXUp, x.hmodel.fNbinsY, x.hmodel.fYLow, x.hmodel.fYUp, x.varname1, x.varname2, x.weightname, rnext);
//            }
//        }
        _rnt.addDaughter(rnext, acut.idx);

    }
}

void NanoAODAnalyzerrdframe::add1DHist(TH1DModel histdef, std::string variable, std::string weight,string mincutstep)
{
    _hist1dinfovector.push_back({histdef, variable, weight, mincutstep});
}

//for 2DHistograms
//void NanoAODAnalyzerrdframe::add2DHist(TH2DModel histdef, std::string variable1,std::string variable2, std::string weight,string mincutstep)
//{
//    _hist2dinfovector.push_back({histdef, variable1,variable2, weight, mincutstep});
//}

void NanoAODAnalyzerrdframe::drawHists(RNode t)
{
    cout << "processing" <<endl;
    t.Count();
}

void NanoAODAnalyzerrdframe::addVar(varinfo v)
{
    _varinfovector.push_back(v);
}

void NanoAODAnalyzerrdframe::addVartoStore(string varname)
{
    // varname is assumed to be a regular expression.
    // e.g. if varname is "Muon_eta" then "Muon_eta" will be stored
    // if varname=="Muon_.*", then any branch name that starts with "Muon_" string will
    // be saved
    _varstostore.push_back(varname);

}

void NanoAODAnalyzerrdframe::setupTree()
{
    vector<RNodeTree *> rntends;
    _rnt.getRNodeLeafs(rntends);
    for (auto arnt: rntends)
    {
        RNode *arnode = arnt->getRNode();
        string nodename = arnt->getIndex();
        vector<string> varforthistree;
        std::map<string, int> varused;

        for (auto varname: _varstostore)
        {
            bool foundmatch = false;
            std::regex b(varname);
            for (auto a: arnode->GetColumnNames())
            {
                if (std::regex_match(a, b) && varused[a]==0)
                {
                    varforthistree.push_back(a);
                    varused[a]++;
                    foundmatch = true;
                }
            }
            if (!foundmatch)
            {
                cout << varname << " not found at "<< nodename << endl;
            }

        }
        _varstostorepertree[nodename]  = varforthistree;
    }

}

void NanoAODAnalyzerrdframe::addCuts(string cut, string idx)
{
    _cutinfovector.push_back({cut, idx});
}


void NanoAODAnalyzerrdframe::run(bool saveAll, string outtreename)
{


    vector<RNodeTree *> rntends;
    _rnt.getRNodeLeafs(rntends);

    //_rnt.Print();
    //cout << rntends.size() << endl;
   // std::cout<< "-------------------------------------------------------------------" << std::endl;
    // on master, regex_replace doesn't work somehow
    //std::regex rootextension("\\.root");

    for (auto arnt: rntends)
    {
        string nodename = arnt->getIndex();
        //string outname = std::regex_replace(_outfilename, rootextension, "_"+nodename+".root");
        string outname = _outfilename;
        // if producing many root files due to branched selection criteria,  each root file will get a different name
        if (rntends.size()>1) outname.replace(outname.find(".root"), 5, "_"+nodename+".root");
        _outrootfilenames.push_back(outname);
        RNode *arnode = arnt->getRNode();
        std::cout<< "-------------------------------------------------------------------" << std::endl;
                cout<<"cut : " ;
                cout << arnt->getIndex();
        //cout << ROOT::RDF::SaveGraph(_rlm) << endl;
        if (saveAll) {
            arnode->Snapshot(outtreename, outname);
        }
        else {
            // use the following if you want to store only a few variables
            //arnode->Snapshot(outtreename, outname, _varstostore);
            cout << " --writing branches" << endl;
            std::cout<< "-------------------------------------------------------------------" << std::endl;
            for (auto bname: _varstostorepertree[nodename])
            {
                cout << bname << endl;
            }
            arnode->Snapshot(outtreename, outname, _varstostorepertree[nodename]);
        }
        std::cout<< "-------------------------------------------------------------------" << std::endl;
        cout << "Creating output root file :  " << endl;
        cout << outname << " ";
        cout<<endl;
        std::cout<< "-------------------------------------------------------------------" << std::endl;
        _outrootfile = new TFile(outname.c_str(), "UPDATE");
        cout << "Writing histograms...   " << endl;
        std::cout<< "-------------------------------------------------------------------" << std::endl;
        for (auto &h : _th1dhistos)
        {
            if (h.second.GetPtr() != nullptr) {
                h.second.GetPtr()->Print();
                h.second.GetPtr()->Write();
            }
        }

        _outrootfile->Write(0, TObject::kOverwrite);
        _outrootfile->Close();
    }
    std::cout<< "-------------------------------------------------------------------" << std::endl;
    std::cout << "END...  :) " << std::endl; 

}

//void NanoAODAnalyzerrdframe::setParams(int year, string runtype, int datatype)
//void NanoAODAnalyzerrdframe::setParams(int year, string runtype, int datatype,string CutOnNom, string GENsig, string topPtReweight, string topPtReweightsys, string jecsys, string jersys, string btagsys, string btagsysuncorr, string lepidsys, string lepisosys, string leprecosys, string channels)
void NanoAODAnalyzerrdframe::setParams(int year, string runtype, int datatype, string sampletype, string region, string topPtReweight, string topPtReweightsys, string jecsys, string jersys, string btagsys, string btagsysuncorr)
{
    /*if(debug){
        std::cout<< "================================//=================================" << std::endl;
        std::cout<< "Line : "<< __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout<< "================================//=================================" << std::endl;
    }*/
    _year=year;
    _runtype=runtype;
    _datatype=datatype;
    _sampletype=sampletype;
    _region=region;

    _topPtReweight=topPtReweight;
    _topPtReweightsys=topPtReweightsys;

    _jecsys=jecsys;
    _jersys=jersys; 

    if(_year==2016) {
        cout << "Analysing through Run 2016" << endl;
    }else if(_year==2017) {
        cout << "Analysing through Run 2017" << endl;
    }else if(_year==2018){
        cout << "Analysing through Run 2018" << endl;
    }

    if(_sampletype == "Tprime"){
        _isTprime = true;
        cout << "Running Tprime signal sample" << endl;
    }else if(_sampletype == "TTToHadronic"){
        _isTT = true;
        cout << "Running background sample TTToHadronic" << endl;
    }else if(_sampletype == "QCD"){
        _isQCD = true;
        cout << "Running background sample QCD" << endl;
    }else if(_sampletype == "Data"){
        _isData = true;
        cout << "Running Data" << endl;
    }

    if(_region == "2M1L"){
        _is2M1L = true;
        cout << "Running in 2M1L region" << endl;
    }else if(_region == "3M"){
        _is3M = true;
        cout << "Running in 3M region" << endl;
    }else if(_region == "3T"){
        _is3T = true;
        cout << "Running in 3T region" << endl;
    }

    if(_runtype.find("UL") != std::string::npos){
        _isUL = true;
        cout << "Ultra Legacy Selected " << endl;
        std::cout<< "-------------------------------------------------------------------" << std::endl;
    }else if(_runtype.find("ReReco") != std::string::npos){
        _isReReco = true;
        cout << " ReReco  Selected!" << endl;
        std::cout<< "-------------------------------------------------------------------" << std::endl;
    }
    if (!_isUL && !_isReReco){
        std::cout<< "Default run version : UL or ReReco is not selected! "<< std::endl;
        std::cout<< "-------------------------------------------------------------------" << std::endl;
    }


    if (_datatype==0){
        _isData = false;
        std::cout << " MC input files Selected!! "<<std::endl;
        std::cout<< "-------------------------------------------------------------------" << std::endl;

    }else if(_datatype==1){
        _isData = true;
        std::cout << " DATA input files Selected!!" <<std::endl;
        std::cout<< "-------------------------------------------------------------------" << std::endl;
    }if(_datatype==-1){
        std::cout<< "Default root version :checking out gen branches! "<< std::endl;
        std::cout<< "-------------------------------------------------------------------" << std::endl;

        if (_atree->GetBranch("genWeight") == nullptr) {
            _isData = true;
            cout << "input file is DATA" <<endl;
        }
        else
        {
            _isData = false;
            cout << "input file is MC" <<endl;
        }
    }
    TObjArray *allbranches = _atree->GetListOfBranches();
    for (int i =0; i<allbranches->GetSize(); i++)
    {
        TBranch *abranch = dynamic_cast<TBranch *>(allbranches->At(i));
        if (abranch!= nullptr){
            //cout << abranch->GetName() << endl;
            _originalvars.push_back(abranch->GetName());
        }
    }


}
//Checking HLTs in the input root file
//void NanoAODAnalyzerrdframe::setHLT(){
std::string NanoAODAnalyzerrdframe::setHLT(std::string str_HLT){
    if(debug){
    std::cout<< "================================//=================================" << std::endl;
    std::cout<< "Line : "<< __LINE__ << " Function : " << __FUNCTION__ << std::endl;
    std::cout<< "================================//=================================" << std::endl;
    }

    if(str_HLT != "" ){

        bool ctrl_HLT =isDefined(str_HLT);
        std::string output;
        if(ctrl_HLT){
            output=str_HLT;
            std::cout<<"HLT : " <<  str_HLT  << " : SUCCESSFULLY FOUND!!"<< std::endl;
        }else{
            std::cout<<"HLT : " <<  str_HLT  << " : CAN NOT BE FOUND "<< std::endl;
            std::cout<< "Check HLT branches in the input root file!!" << std::endl;
            std::cout<< "EXITING PROGRAM!!" << std::endl;

            exit(1);
        }
        return output;

    }else{ // fill the HLT names in a vector according to each year
            std::vector<string> V_output;


            //loop on HLTs
            for (size_t i = 0; i < HLTGlobalNames.size(); i++)
            {
                /* code */
                bool ctrl_HLT = isDefined(HLTGlobalNames[i]);
                if(ctrl_HLT){
                    V_output.push_back(HLTGlobalNames[i]);
                }

            }
            std::string output_HLT;
            if(!V_output.empty()){
                for (size_t i = 0; i < V_output.size() ; i++)
                {
                    if(i!=V_output.size()-1){
                    output_HLT += V_output[i] + "==1 || " ;
                    }else{
                        output_HLT += V_output[i] + "==1 " ;
                    }
                }
            }else{
                std::cout<< " Not matched with any HLT Triggers! Please check the HLT Names in the inputfile " << std::endl;
                std::cout<< "EXITING PROGRAM!!" << std::endl;
                exit(1);
            }
            std::cout<< " HLT names =  " <<  output_HLT  << std::endl;
            return output_HLT;

    }

}
//control all branch names using in the addCuts function
std::string NanoAODAnalyzerrdframe::ctrlBranchName(std::string str_Branch){

    if(debug){
        std::cout<< "================================//=================================" << std::endl;
        std::cout<< "Line : "<< __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout<< "================================//=================================" << std::endl;
    }

    bool ctrl_Branch =isDefined(str_Branch);
    std::string output;
    if(ctrl_Branch){
        output=str_Branch;
    }else{
        std::cout<< "Branch : " <<  str_Branch  << " : CAN NOT BE FOUND "<< std::endl;
        std::cout<< "Check your branches in the input root file!!" << std::endl;
        std::cout<< "EXITING PROGRAM!!" << std::endl;

        exit(1);
    }
    return output;
}



//cut-based ID Fall17 V2 (0:fail, 1:veto, 2:loose, 3:medium, 4:tight)
std::string NanoAODAnalyzerrdframe::ElectronID(int cutbasedID){

    if(debug){
        std::cout<< "================================//=================================" << std::endl;
        std::cout<< "Line : "<< __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout<< "================================//=================================" << std::endl;
    }
    //double Electron_eta;
    //double Electron_pt;
    if (cutbasedID==1)std::cout<< " VETO Electron ID requested    == " << cutbasedID <<std::endl;
    if (cutbasedID==2)std::cout<< " LOOSE Electron ID requested   == " << cutbasedID <<std::endl;
    if (cutbasedID==3)std::cout<< " MEDIUM Electron ID requested  == " << cutbasedID <<std::endl;
    if (cutbasedID==4)std::cout<< " TIGHT Electron ID requested   == " << cutbasedID <<std::endl;
    std::cout<< "-------------------------------------------------------------------" << std::endl;

    if (cutbasedID<0 || cutbasedID>4){
        std::cout<< "ERROR!! Wrong Electron ID requested  == " << cutbasedID << "!! Can't be applied" <<std::endl;
        std::cout<< "Please select ElectronID from 1 to 4 " <<std::endl;
        std::cout<< "-------------------------------------------------------------------" << std::endl;
        std::cout<< "EXITING PROGRAM!!" << std::endl;
        exit(1);
    }
    /*if(_year==2018 && _isUL){
        if(cutbasedID==2 ){
            Electron_eta=2.5;
            Electron_pt=10;
        }else if (cutbasedID==3){
            Electron_eta=2.4;
            Electron_pt=10;
        }
    }*/

//Rdataframe look for the variables in the intput Ttree..
std::string output = Form("Electron_cutBased == %d ",cutbasedID);
//std::string output = Form("Electron_cutBased == %d &&  abs(Electron_eta)<%f && Electron_pt<%f",cutbasedID,  Electron_eta, Electron_pt);

return output;
}

std::string NanoAODAnalyzerrdframe::MuonID(int cutbasedID){
    
    if(debug){
        std::cout<< "================================//=================================" << std::endl;
        std::cout<< "Line : "<< __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout<< "================================//=================================" << std::endl;
    }
    
    //  cut-based ID Fall17 V2 (0:fail, 1:veto, 2:loose, 3:medium, 4:tight)
    if (cutbasedID==1)std::cout<< " Veto Muon ID requested   == " << cutbasedID <<std::endl;
    if (cutbasedID==2)std::cout<< " LOOSE Muon ID requested  == " << cutbasedID <<std::endl;
    if (cutbasedID==3)std::cout<< " MEDIUM Muon ID requested == " << cutbasedID <<std::endl;
    if (cutbasedID==4)std::cout<< " TIGHT Muon ID requested as == " << cutbasedID <<std::endl;
    std::cout<< "-------------------------------------------------------------------" << std::endl;

    if (cutbasedID<1 || cutbasedID>4){
        std::cout<< "ERROR!! Wrong Muon ID requested  == " << cutbasedID << "!! Can't be applied" <<std::endl;
        std::cout<< "Please select Muon ID from 2 to 4 " <<std::endl;
        std::cout<< "-------------------------------------------------------------------" << std::endl;
        std::cout<< "EXITING PROGRAM!!" << std::endl;

        exit(1);
    }

    string Muon_cutBased_ID;
    
    if (cutbasedID==1){
        Muon_cutBased_ID = "Muon_looseId";
        std::cout<< " VETO Muon ID requested == " << cutbasedID <<", but it doesn't exist in the nanoAOD branches. It is moved to loose MuonID. " << cutbasedID <<std::endl;
    }
    if (cutbasedID == 2){
        Muon_cutBased_ID = "Muon_looseId";
    
    }else if(cutbasedID == 3){
        Muon_cutBased_ID = "Muon_mediumId";

    }else if(cutbasedID == 4){
        Muon_cutBased_ID = "Muon_tightId";
    }
    string output;
    output = Form ("%s==true",Muon_cutBased_ID.c_str());
    return output;
}


std::string NanoAODAnalyzerrdframe::JetID(int cutbasedID){

    if(debug){
        std::cout<< "================================//=================================" << std::endl;
        std::cout<< "Line : "<< __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout<< "================================//=================================" << std::endl;
    }

    if(cutbasedID<1 || cutbasedID>7){
        std::cout<< "Error Wrong JET ID requested == " << cutbasedID << "!! Can't be applied" <<std::endl;
        std::cout<< "Please select number from 1 to 7 " <<std::endl;

    }else{
        std::cout<< " JET ID requested  == " << cutbasedID <<std::endl;
    }

    string output;
    output = Form ("Jet_jetId==%d",cutbasedID);
    return output;
}
