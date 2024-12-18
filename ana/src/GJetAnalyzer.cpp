/*
 * GJetAnalyzer.cpp: subclas -> inherited from main class NanoAODAnalyzerrdframe (Created on: Sep 30, 2018-Author: suyong)
 *
 *  Created on: Dec 18, 2021
 *    modified: Jieun
 */

#include "Math/GenVector/VectorUtil.h"
#include "GJetAnalyzer.h"
#include "utility.h"

//GJetAnalyzer::GJetAnalyzer(TTree *t, std::string outfilename, std::string year, std::string runtype,std::string syst, std::string jsonfname, string globaltag, int nthreads,int isDATA)
//:NanoAODAnalyzerrdframe(t, outfilename, year, runtype,syst, jsonfname, globaltag, nthreads, isDATA)
GJetAnalyzer::GJetAnalyzer(TTree *t, std::string outfilename)
:NanoAODAnalyzerrdframe(t, outfilename)
{

    //initiliaze the HLT names in your analyzer class
    HLT2018Names = {"HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94",
                    "HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59",
                    "HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5",
                    "HLT_PFHT1050","HLT_PFJet500","HLT_PFJet550"};
    HLT2016Names= {"Name1","Name2"};
    HLT2017Names= {"Name1","Name2"};

}

void GJetAnalyzer::defineCuts()
{  
    if (debug){
        std::cout<< "================================//=================================" << std::endl;
        std::cout<< "Line : "<< __LINE__ << " Function : " << __FUNCTION__ << std::endl;
        std::cout<< "================================//=================================" << std::endl;
    }

    auto Nentry = _rlm.Count();
    // This is how you can express a range of the first 100 entries
      //_rlm = _rlm.Range(0, 100);
      //auto Nentry_100 = _rlm.Count();
    std::cout<< "-------------------------------------------------------------------" << std::endl;
    cout << "Usage of ranges:\n" << " - All entries: " << *Nentry << endl;
    //<< " - Entries from 0 to 100: " << *Nentry_100 << endl;
    std::cout<< "-------------------------------------------------------------------" << std::endl;

    addCuts("metFilter","0");
    //addCuts("HLT && metFilter","0");
    addCuts("nselPhotons == 1 && nselJets >= 1 && nvetoLeptons == 0","00");
    //addCuts("nselPhotons == 1 && nselJets >= 1","00");

}

void GJetAnalyzer::defineMoreVars()
{
    //addVar({"HLT","HLT_Photon30_HoverELoose",""});
    addVar({"metFilter","Flag_goodVertices || Flag_globalSuperTightHalo2016Filter || Flag_HBHENoiseFilter || Flag_HBHENoiseIsoFilter || Flag_EcalDeadCellTriggerPrimitiveFilter || Flag_BadPFMuonFilter || Flag_BadPFMuonFilter || Flag_eeBadScFilter || Flag_ecalBadCalibFilter",""});

    addVartoStore("run");
    addVartoStore("luminosityBlock");
    addVartoStore("event");
    addVartoStore("evWeight.*");

    //addVartoStore("HLT");
    addVartoStore("metFilter");
    addVartoStore("nvetoMuons");
    addVartoStore("nvetoElectrons");
    addVartoStore("selPhoton_pt");
    addVartoStore("selPhoton_eta");
 
}
//.================================Histogram Definitions===========================================//
// _hist1dinfovector contains the information of histogram definitions (as TH1DModel)
// the variable to be used for filling and the minimum cutstep for which the histogram should be filled
//dd1DHist(TH1DModel histdef, std::string variable, std::string weight, string mincutstep="");
//=================================================================================================//
void GJetAnalyzer::bookHists()
{

    add1DHist( {"hnevents", "Number of Events", 2, -0.5, 1.5}, "one", "evWeight", "");
    add1DHist( {"h_photon_pt", "pT of selected Photon", 30, 50, 120}, "selPhoton_pt", "evWeight", "0");
    add1DHist( {"h_photon_eta", "eta of selected Photon", 30, -1.5, 1.5}, "selPhoton_eta", "evWeight", "0");
    //add2DHist( {"h_photon_pTEta", "Photon pT eta ", 30, 50, 120, 30, -1.5, 1.5}, "selPhoton_eta", "evWeight", "0");

}

void GJetAnalyzer::selectLeptons()
{
    _rlm = _rlm.Define("vetoElectrons", "Electron_cutBased >= 1 && Electron_pt > 10")
               .Define("vetoMuons","Muon_looseId && Muon_pt > 10");
  
    _rlm = _rlm.Define("nvetoElectrons","Sum(vetoElectrons)")
               .Define("nvetoMuons","Sum(vetoMuons)")
               .Define("nvetoLeptons","(nvetoElectrons + nvetoMuons)");
  
}

void GJetAnalyzer::selectPhotons()
{
  //TightID TightIso based on CutBased ID V2 after 94X
  //https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedPhotonIdentificationRun2#Working_points_for_94X_and_later
  //_rlm = _rlm.Define("goodPhotons", "Photon_pt > 50 && abs(Photon_eta) < 1.44 && Photon_cutBased == 3"); 
  _rlm = _rlm.Define("goodPhotons", "Photon_pt > 30 && abs(Photon_eta) < 1.44 && Photon_cutBased == 3"); 
  _rlm = _rlm.Define("nselPhotons", "Sum(goodPhotons)")
             .Define("selPhoton_pt", "Photon_pt[goodPhotons]")
             .Define("selPhoton_eta", "Photon_eta[goodPhotons]");

}

void GJetAnalyzer::selectJets()
{ 
  _rlm = _rlm.Define("goodJets", "Jet_pt >= 40 && abs(Jet_eta) < 2.5 && Jet_jetId == 6");
  
  _rlm = _rlm.Define("nselJets","Sum(goodJets)")
             .Define("selJet_pt","Jet_pt[goodJets]")
             .Define("selJet_eta","Jet_eta[goodJets]");

}

void GJetAnalyzer::setTree(TTree *t, std::string outfilename)
{
  
    if (debug){
          std::cout<< "================================//=================================" << std::endl;
          std::cout<< "Line : "<< __LINE__ << " Function : " << __FUNCTION__ << std::endl;
          std::cout<< "================================//=================================" << std::endl;
      }
  
    _rd = ROOT::RDataFrame(*t);
    _rlm = RNode(_rd);
    _outfilename = outfilename;
    _hist1dinfovector.clear();
    _th1dhistos.clear();
    _varstostore.clear();
    _hist1dinfovector.clear();
    _selections.clear();
  
    this->setupAnalysis();
}

void GJetAnalyzer::setupObjects()
{
    // Object selection will be defined in sequence.
    // Selected objects will be stored in new vectors.
    selectLeptons();
    selectPhotons();
    selectJets();
}

void GJetAnalyzer::setupAnalysis()
{
  
    if (debug){
          std::cout<< "================================//=================================" << std::endl;
          std::cout<< "Line : "<< __LINE__ << " Function : " << __FUNCTION__ << std::endl;
          std::cout<< "================================//=================================" << std::endl;
      }

    // Event weight for data it's always one. For MC, it depends on the sign

    _rlm = _rlm.Define("one", "1.0");
    _rlm = _rlm.Define("evWeight","one");
                 //.Define("unitGenWeight","one")
                 //.Define("pugenWeight","one");
  
      //for correction define evWeights as fallows
      /*
      if(_isData){
          _rlm = _rlm.Define("unitGenWeight","one")
                  .Define("pugenWeight","one"); // if setupcorrection in processnanoad.py then don't define here. 
          _rlm = _rlm.Define("evWeight","one");
      }
      if (_isData && !isDefined("evWeight"))
      {
        _rlm = _rlm.Define("evWeight", [](){
            return 1.0;
          }, {} );
      }
      */
  
    applyJetMETCorrections();
    defineCuts();
    defineMoreVars();
    bookHists();
    setupCuts_and_Hists();
    setupTree();

}
