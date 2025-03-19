/*
 * TprimeHadAnalyzer.cpp: subclas -> inherited from main class NanoAODAnalyzerrdframe (Created on: Sep 30, 2018-Author: suyong)
 *
 *  Created on: Dec 18, 2021
 *    modified: Jieun
 */

#include "Math/GenVector/VectorUtil.h"
#include "TprimeHadAnalyzer.h"
#include <fstream>
#include "utility.h"
//#include "correction.h"

//from Di 
#include <TStopwatch.h>
//#include "ROOT/RVec.hxx"


TprimeHadAnalyzer::TprimeHadAnalyzer(TTree *t, std::string outfilename)
:NanoAODAnalyzerrdframe(t, outfilename)
{

    //initiliaze the HLT names in your analyzer class
    //HLT2018Names = {"HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94",
    //                "HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59",
    //                "HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5",
    //                "HLT_PFHT1050",
    //                "HLT_PFJet500",
    //                "HLT_PFJet550"
    //                };
    //HLT2017Names = {"HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2"
    //                "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2",
    //                "HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5",
    //                "HLT_PFHT1050",
    //                "HLT_PFJet500",
    //                };
    //HLT2016Names = {"HLT_PFHT400_SixJet30_DoubleBTagCSV_p056",
    //                "HLT_PFHT450_SixJet40_BTagCSV_p056"
    //                "HLT_PFHT900",
    //                "HLT_PFHT750_4JetPt70",
    //                "HLT_PFHT750_4JetPt80",
    //                "HLT_PFHT800_4JetPt50",
    //                "HLT_PFHT850_4JetPt50",
    //                "HLT_PFJet450"
    //                };
    //

}

void TprimeHadAnalyzer::defineCuts()
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

    if(_isTprime){
        addCuts("isHadProcess","0");
        addCuts("METfilter && HLT && nsel40Jets >= 6","00");
//    }else if(_isTT || _isQCD || _isData){
    }else{
        addCuts("METfilter && HLT","0");
        addCuts("nsel40Jets >= 6","00");
    }

    addCuts("selJet_pt[0] > 170 && selJet_pt[1] > 130 && selJet_pt[2] > 80 && goodHT > 500","000");

    if(_is2M1L){
        addCuts("nselMbJets == 2 && nselLbJets >= 3 && nselMbJets < 3","0000");
    }else if(_is3L){
        addCuts("nselLbJets >= 3","0000");
    }else if(_is3M){
        addCuts("nselMbJets >= 3 && nselTbJets < 3","0000");
    }else if(_is3T){
         addCuts("nselTbJets >= 3","0000");
    }else{
        cout << "no region defined, get efficiency Map" << endl;
    }

// Cut 0
//    addCuts("Chi2_min < 15","00000");
//    addCuts("invmass_2ndTop > 250","000000");
//    addCuts("H_mass > 100","0000000");

    //// Cut1-6 branch
    //addCuts("H_mass > 100",        "10001");
    //addCuts("RelHT > 0.4",         "100010");      //1
    //addCuts("Chi2_max < 3",        "1000100");     //2
    //addCuts("dRHbb_chi2 < 1.1",    "10001000");    //3
    //addCuts("Chi2_min_H < 1.5",    "100010000");   //4
    //addCuts("dRWjj_chi2 < 1.75",   "1000100000");  //5
    //addCuts("dRbW_chi2 < 1.2",     "10001000000"); //6
  
}

void TprimeHadAnalyzer::defineMoreVars()
{

    //defineVar("isHadTprime",::isHadWHiggs,{"p4_GenPart","GenPart_pdgId","GenPart_genPartIdxMother"});
    if(_is2M1L || _is3L || _is3M || _is3T){ 
  
    addVar({"Chi2_min_H","Chi2_Tprime[7]",""});
    addVar({"Chi2_min_W","Chi2_Tprime[8]",""});
    addVar({"Chi2_min_Top","Chi2_Tprime[9]",""});
  
    addVar({"H_mass","Chi2_Tprime[10]",""});
    addVar({"W_mass","Chi2_Tprime[11]",""});
    addVar({"Top_mass","Chi2_Tprime[12]",""});
   
    addVar({"invmass_2ndTop","Chi2_Tprime[13]",""});
    addVar({"invmass_2ndW","Chi2_Tprime[14]",""});
    addVar({"invmass_WH","Chi2_Tprime[15]",""});
    addVar({"invmass_Tprime","Chi2_Tprime[16]",""});

    addVar({"R_TopH","(Top_mass - H_mass) / (Top_mass + H_mass)",""});
    addVar({"R_2ndTopW","(invmass_2ndTop + invmass_2ndW) / H_mass",""});

    defineVar("mindR_bb",::mindR_bb,{"bjet4vecs"});
    defineVar("dRbb",::dR_bb,{"bjet4vecs"});
    defineVar("mbb",::m_bb,{"bjet4vecs"});
    addVar({"mindR_dRbb","mindR_bb[0]",""});
    addVar({"mindR_mbb","mindR_bb[1]",""});
  
    addVar({"selJet1_pt","selJet_pt[0]",""});
    addVar({"selJet1_pt_massnom","selJet1_pt/invmass_Tprime",""});
    addVar({"selJet1_pt_htnom","selJet1_pt/goodHT",""});
    addVar({"selJet1_eta","selJet_eta[0]",""});
    addVar({"selJet1_phi","selJet_phi[0]",""});
    addVar({"selJet1_mass","selJet_mass[0]",""});
    addVar({"selJet1_btag","selJet_btagDeepFlavB[0]",""});
    addVar({"selJet1_e","jet4vecs[0].E()",""});
    addVar({"selJet1_px","jet4vecs[0].Px()",""});
    addVar({"selJet1_py","jet4vecs[0].Py()",""});
    addVar({"selJet1_pz","jet4vecs[0].Pz()",""});
    addVar({"selJet1_e_massnom","selJet1_e/invmass_Tprime",""});
    addVar({"selJet1_e_htnom","selJet1_e/goodHT",""});
  
    addVar({"selJet2_pt","selJet_pt[1]",""});
    addVar({"selJet2_pt_massnom","selJet2_pt/invmass_Tprime",""});
    addVar({"selJet2_pt_htnom","selJet2_pt/goodHT",""});
    addVar({"selJet2_eta","selJet_eta[1]",""});
    addVar({"selJet2_phi","selJet_phi[1]",""});
    addVar({"selJet2_mass","selJet_mass[1]",""});
    addVar({"selJet2_btag","selJet_btagDeepFlavB[1]",""});
    addVar({"selJet2_e","jet4vecs[1].E()",""});
    addVar({"selJet2_px","jet4vecs[1].Px()",""});
    addVar({"selJet2_py","jet4vecs[1].Py()",""});
    addVar({"selJet2_pz","jet4vecs[1].Pz()",""});
    addVar({"selJet2_e_massnom","selJet2_e/invmass_Tprime",""});
    addVar({"selJet2_e_htnom","selJet2_e/goodHT",""});
  
    addVar({"selJet3_pt","selJet_pt[2]",""});
    addVar({"selJet3_pt_massnom","selJet3_pt/invmass_Tprime",""});
    addVar({"selJet3_pt_htnom","selJet3_pt/goodHT",""});
    addVar({"selJet3_eta","selJet_eta[2]",""});
    addVar({"selJet3_phi","selJet_phi[2]",""});
    addVar({"selJet3_mass","selJet_mass[2]",""});
    addVar({"selJet3_btag","selJet_btagDeepFlavB[2]",""});
    addVar({"selJet3_e","jet4vecs[2].E()",""});
    addVar({"selJet3_px","jet4vecs[2].Px()",""});
    addVar({"selJet3_py","jet4vecs[2].Py()",""});
    addVar({"selJet3_pz","jet4vecs[2].Pz()",""});
    addVar({"selJet3_e_massnom","selJet3_e/invmass_Tprime",""});
    addVar({"selJet3_e_htnom","selJet3_e/goodHT",""});
  
    addVar({"selJet4_pt","selJet_pt[3]",""});
    addVar({"selJet4_pt_massnom","selJet4_pt/invmass_Tprime",""});
    addVar({"selJet4_pt_htnom","selJet4_pt/goodHT",""});
    addVar({"selJet4_eta","selJet_eta[3]",""});
    addVar({"selJet4_phi","selJet_phi[3]",""});
    addVar({"selJet4_mass","selJet_mass[3]",""});
    addVar({"selJet4_btag","selJet_btagDeepFlavB[3]",""});
    addVar({"selJet4_e","jet4vecs[3].E()",""});
    addVar({"selJet4_px","jet4vecs[3].Px()",""});
    addVar({"selJet4_py","jet4vecs[3].Py()",""});
    addVar({"selJet4_pz","jet4vecs[3].Pz()",""});
    addVar({"selJet4_e_massnom","selJet4_e/invmass_Tprime",""});
    addVar({"selJet4_e_htnom","selJet4_e/goodHT",""});
  
    addVar({"selJet5_pt","selJet_pt[4]",""});
    addVar({"selJet5_pt_massnom","selJet5_pt/invmass_Tprime",""});
    addVar({"selJet5_pt_htnom","selJet5_pt/goodHT",""});
    addVar({"selJet5_eta","selJet_eta[4]",""});
    addVar({"selJet5_phi","selJet_phi[4]",""});
    addVar({"selJet5_mass","selJet_mass[4]",""});
    addVar({"selJet5_btag","selJet_btagDeepFlavB[4]",""});
    addVar({"selJet5_e","jet4vecs[4].E()",""});
    addVar({"selJet5_px","jet4vecs[4].Px()",""});
    addVar({"selJet5_py","jet4vecs[4].Py()",""});
    addVar({"selJet5_pz","jet4vecs[4].Pz()",""});
    addVar({"selJet5_e_massnom","selJet5_e/invmass_Tprime",""});
    addVar({"selJet5_e_htnom","selJet5_e/goodHT",""});
  
    addVar({"selbJet1_pt","selbJet_pt[0]",""});
    addVar({"selbJet1_pt_massnom","selbJet1_pt/invmass_Tprime",""});
    addVar({"selbJet1_pt_htnom","selbJet1_pt/goodHT",""});
    addVar({"selbJet1_eta","selbJet_eta[0]",""});
    addVar({"selbJet1_phi","selbJet_phi[0]",""});
    addVar({"selbJet1_mass","selbJet_mass[0]",""});
    addVar({"selbJet1_btag","selbJet_btag[0]",""});
    addVar({"selbJet1_e","bjet4vecs[0].E()",""});
    addVar({"selbJet1_px","bjet4vecs[0].Px()",""});
    addVar({"selbJet1_py","bjet4vecs[0].Py()",""});
    addVar({"selbJet1_pz","bjet4vecs[0].Pz()",""});
    addVar({"selbJet1_e_massnom","selbJet1_e/invmass_Tprime",""});
    addVar({"selbJet1_e_htnom","selbJet1_e/goodHT",""});
  
    addVar({"selbJet2_pt","selbJet_pt[1]",""});
    addVar({"selbJet2_pt_massnom","selbJet2_pt/invmass_Tprime",""});
    addVar({"selbJet2_pt_htnom","selbJet2_pt/goodHT",""});
    addVar({"selbJet2_eta","selbJet_eta[1]",""});
    addVar({"selbJet2_phi","selbJet_phi[1]",""});
    addVar({"selbJet2_mass","selbJet_mass[1]",""});
    addVar({"selbJet2_btag","selbJet_btag[1]",""});
    addVar({"selbJet2_e","bjet4vecs[1].E()",""});
    addVar({"selbJet2_px","bjet4vecs[1].Px()",""});
    addVar({"selbJet2_py","bjet4vecs[1].Py()",""});
    addVar({"selbJet2_pz","bjet4vecs[1].Pz()",""});
    addVar({"selbJet2_e_massnom","selbJet2_e/invmass_Tprime",""});
    addVar({"selbJet2_e_htnom","selbJet2_e/goodHT",""});
  
    addVar({"goodHT_massnom","goodHT/invmass_Tprime",""});
    addVar({"invmass_htnom","invmass_Tprime/goodHT",""});
    }
  
    //================================Store variables in tree=======================================//
    // define variables that you want to store
    //==============================================================================================//
    //addVartoStore("nJetFromW");
    //addVartoStore("nJetFromTop");
    //addVartoStore("nJetFromH");

    addVartoStore("run");
    addVartoStore("luminosityBlock");
    addVartoStore("event");
    addVartoStore("evWeight.*");
    //addVartoStore("evWeight");

    addVartoStore("genWeight");
    addVartoStore("genEventSumw");

//    addVartoStore("HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2");
//    addVartoStore("HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepCSV_4p5");
//    addVartoStore("HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5");
//    addVartoStore("HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5");
//    addVartoStore("HLT_PFHT1050");
//    addVartoStore("HLT_PFJet500");
//    addVartoStore("HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94");
//    addVartoStore("HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59");
//  
    if(!_is2M1L && !_is3L && !_is3M && !_is3T){ 
    
    addVartoStore("selJetsForbtag_pt");
    addVartoStore("selJetsForbtag_eta");
    addVartoStore("selJetsForbtag_phi");
    addVartoStore("selJetsForbtag_mass");
    addVartoStore("selJetsForbtag_btag");
    addVartoStore("selJetsForbtag_hadronFlavour");
    addVartoStore("nselJetsForbtag");

    }else{

    // DNN Study
    // Cut0
    addVartoStore("nselJets");
    addVartoStore("nselbJets");
    addVartoStore("nselLbJets");
    addVartoStore("nselMbJets");
    addVartoStore("nselTbJets");

    // for TF
    addVartoStore("jet4vecs");
    addVartoStore("numJets4vecs");
    addVartoStore("denJets4vecs");
    addVartoStore("numJets_pt");
    addVartoStore("numJets_eta");
    addVartoStore("denJets_pt");
    addVartoStore("denJets_eta");

    // btag in binary
    addVartoStore("is_deepJet_T");
    addVartoStore("is_deepJet_M");
    addVartoStore("is_deepJet_L");

//    addVartoStore("selJet1_pt");
//    addVartoStore("selJet1_pt_massnom");
//    addVartoStore("selJet1_eta");
//    addVartoStore("selJet1_phi");
//    addVartoStore("selJet1_e");
//    addVartoStore("selJet1_e_massnom");
//    addVartoStore("selJet1_btag");
//
//    addVartoStore("selJet2_pt");
//    addVartoStore("selJet2_pt_massnom");
//    addVartoStore("selJet2_eta");
//    addVartoStore("selJet2_phi");
//    addVartoStore("selJet2_e");
//    addVartoStore("selJet2_e_massnom");
//    addVartoStore("selJet2_btag");
//
//    addVartoStore("selJet3_pt");
//    addVartoStore("selJet3_pt_massnom");
//    addVartoStore("selJet3_eta");
//    addVartoStore("selJet3_phi");
//    addVartoStore("selJet3_e");
//    addVartoStore("selJet3_e_massnom");
//    addVartoStore("selJet3_btag");
//
//    addVartoStore("selJet4_pt");
//    addVartoStore("selJet4_pt_massnom");
//    addVartoStore("selJet4_eta");
//    addVartoStore("selJet4_phi");
//    addVartoStore("selJet4_e");
//    addVartoStore("selJet4_e_massnom");
//    addVartoStore("selJet4_btag");
//
//    addVartoStore("selJet5_pt");
//    addVartoStore("selJet5_pt_massnom");
//    addVartoStore("selJet5_eta");
//    addVartoStore("selJet5_phi");
//    addVartoStore("selJet5_e");
//    addVartoStore("selJet5_e_massnom");
//    addVartoStore("selJet5_btag");
//
//    addVartoStore("selbJet1_pt");
//    addVartoStore("selbJet1_pt_massnom");
//    addVartoStore("selbJet1_eta");
//    addVartoStore("selbJet1_phi");
//    addVartoStore("selbJet1_e");
//    addVartoStore("selbJet1_e_massnom");
//    addVartoStore("selbJet1_btag");
//
//    addVartoStore("selbJet2_pt");
//    addVartoStore("selbJet2_pt_massnom");
//    addVartoStore("selbJet2_eta");
//    addVartoStore("selbJet2_phi");
//    addVartoStore("selbJet2_e");
//    addVartoStore("selbJet2_e_massnom");
//    addVartoStore("selbJet2_btag");
//
//    addVartoStore("Chi2_min");
//    addVartoStore("goodHT");
//    addVartoStore("invmass_2ndTop");
//    addVartoStore("H_mass");
//
//    addVartoStore("RelHT");          // Cut 1
//    addVartoStore("Chi2_max");       // Cut 2
//    addVartoStore("dRHbb_chi2");     // Cut 3
//    addVartoStore("Chi2_min_H");     // Cut 4
//    addVartoStore("dRWjj_chi2");     // Cut 5
//    addVartoStore("dRbW_chi2");      // Cut 6
//
//    // Candidates
//    addVartoStore("Chi2_min_W");
//    addVartoStore("Chi2_min_Top");
//    addVartoStore("mindR_dRbb");
//    addVartoStore("mindR_mbb");
//    addVartoStore("Top_mass");
//    addVartoStore("W_mass");
//    addVartoStore("invmass_WH");
//    addVartoStore("invmass_Tprime");
//    addVartoStore("invmass_leadjets");//etc
//    addVartoStore("R_TopH");
//    addVartoStore("R_2ndTopW");
//    addVartoStore("newRelHT");
//    addVartoStore("dRTprimeoj_chi2");
//    addVartoStore("dRHTop_chi2");
//    addVartoStore("dEtaWH_chi2");
//    addVartoStore("dPhiHTop_chi2");
//    addVartoStore("Rpt_Top2ndTop");
//    addVartoStore("Rpt_HTopTprime");
//    addVartoStore("Rpt_TprimeHTprimeTop");
//
    }

}
//.================================Histogram Definitions===========================================//
// _hist1dinfovector contains the information of histogram definitions (as TH1DModel)
// the variable to be used for filling and the minimum cutstep for which the histogram should be filled
//dd1DHist(TH1DModel histdef, std::string variable, std::string weight, string mincutstep="");
//=================================================================================================//
void TprimeHadAnalyzer::bookHists()
{

  add1DHist( {"h_nevents", "Number of Events", 2, -0.5, 1.5}, "one", "genWeight", "");
  add1DHist( {"h_nevents_pugen", "Number of Events", 2, -0.5, 1.5}, "one", "pugenWeight", "");
  add1DHist( {"h_nevents_weighted", "Number of Events", 2, -0.5, 1.5}, "one", "evWeight_L1btag_topPt", "0000");

}

void TprimeHadAnalyzer::genStudy()
{

  if(!_isData){
      _rlm = _rlm.Define("isGenQ","abs(GenPart_pdgId)<9")
                 .Define("GenQmom","GenPart_genPartIdxMother[isGenQ]")
                 .Define("GenQmom_pdgId","Take(GenPart_pdgId,GenQmom)")
                 .Define("isQFromW","abs(GenQmom_pdgId)==24")
    
                 .Define("isGenb","abs(GenPart_pdgId)==5")
                 .Define("Genbmom","GenPart_genPartIdxMother[isGenb]")
                 .Define("Genbmom_pdgId","Take(GenPart_pdgId,Genbmom)")
                 .Define("isbFromH","abs(Genbmom_pdgId)==25");
    
      _rlm = _rlm.Define("isHadProcess","Sum(isQFromW) > 1 && Sum(isbFromH) > 1");
  }

  // HLT
  // from AN 2021_140/v4 + additional
  if (!isDefined("HLT_PFHT400_SixJet30_DoubleBTagCSV_p056")) _rlm = _rlm.Define("HLT_PFHT400_SixJet30_DoubleBTagCSV_p056", "false");
  if (!isDefined("HLT_PFHT450_SixJet40_BTagCSV_p056")) _rlm = _rlm.Define("HLT_PFHT450_SixJet40_BTagCSV_p056", "false");
  if (!isDefined("HLT_PFHT900")) _rlm = _rlm.Define("HLT_PFHT900", "false");
  if (!isDefined("HLT_PFHT750_4JetPt70")) _rlm = _rlm.Define("HLT_PFHT750_4JetPt70", "false");
  if (!isDefined("HLT_PFHT750_4JetPt80")) _rlm = _rlm.Define("HLT_PFHT750_4JetPt80", "false");
  if (!isDefined("HLT_PFHT800_4JetPt50")) _rlm = _rlm.Define("HLT_PFHT800_4JetPt50", "false");
  if (!isDefined("HLT_PFHT850_4JetPt50")) _rlm = _rlm.Define("HLT_PFHT850_4JetPt50", "false");
  if (!isDefined("HLT_PFJet450")) _rlm = _rlm.Define("HLT_PFJet450", "false");

  if (!isDefined("HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2")) _rlm = _rlm.Define("HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2", "false");
  if (!isDefined("HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2")) _rlm = _rlm.Define("HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2", "false");
  if (!isDefined("HLT_PFHT430_SixPFJet40_BTagCSV_p080")) _rlm = _rlm.Define("HLT_PFHT430_SixPFJet40_BTagCSV_p080", "false"); 
  if (!isDefined("HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5")) _rlm = _rlm.Define("HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5", "false"); 

  if (!isDefined("HLT_HT300PT30_QuadJet_75_60_45_40_TripleCSV_p07")) _rlm = _rlm.Define("HLT_HT300PT30_QuadJet_75_60_45_40_TripleCSV_p07", "false");
  if (!isDefined("HLT_HT300PT30_QuadJet_75_60_45_40_TriplePFBTagCSV_3p0")) _rlm = _rlm.Define("HLT_HT300PT30_QuadJet_75_60_45_40_TriplePFBTagCSV_3p0", "false");

  if (!isDefined("HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepCSV_4p5")) _rlm = _rlm.Define("HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepCSV_4p5", "false"); 
  if (!isDefined("HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5")) _rlm = _rlm.Define("HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5", "false"); 
  if (!isDefined("HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5")) _rlm = _rlm.Define("HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5", "false"); 

  if (!isDefined("HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94")) _rlm = _rlm.Define("HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94", "false"); 
  if (!isDefined("HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59")) _rlm = _rlm.Define("HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59", "false"); 
  // ^ huh it wasnt used

  if(_year==2015 || _year==2016){        //2016era

      _rlm = _rlm.Define("METfilter","Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_BadPFMuonDzFilter && Flag_eeBadScFilter");

      if(_year==2015){        //2016preVFP - APV: but for hard coded
          _rlm = _rlm.Define("HLT","HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 || HLT_PFHT450_SixJet40_BTagCSV_p056 || HLT_PFHT900 || HLT_PFHT750_4JetPt70 || HLT_PFHT750_4JetPt80 || HLT_PFHT800_4JetPt50 || HLT_PFHT850_4JetPt50 || HLT_PFJet450");

      }else if(_year==2016){  //2016postVFP: well its the same HLT
          _rlm = _rlm.Define("HLT","HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 || HLT_PFHT450_SixJet40_BTagCSV_p056 || HLT_PFHT900 || HLT_PFHT750_4JetPt70 || HLT_PFHT750_4JetPt80 || HLT_PFHT800_4JetPt50 || HLT_PFHT850_4JetPt50 || HLT_PFJet450");
      }
  }
  else if (_year==2017 || _year==2018){

      _rlm = _rlm.Define("METfilter","Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_BadPFMuonDzFilter && Flag_eeBadScFilter && Flag_ecalBadCalibFilter");

      if (_year==2017){
          _rlm = _rlm.Define("HLT","HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2 || HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 || HLT_PFHT430_SixPFJet40_BTagCSV_p080 || HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 || HLT_HT300PT30_QuadJet_75_60_45_40_TripleCSV_p07 || HLT_HT300PT30_QuadJet_75_60_45_40_TriplePFBTagCSV_3p0 || HLT_PFHT1050 || HLT_PFJet500");

      }else if(_year==2018){
//          _rlm = _rlm.Define("HLT","HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 || HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepCSV_4p5 || HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 || HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5 || HLT_PFHT1050 || HLT_PFJet500");
          _rlm = _rlm.Define("HLT","HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 || HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepCSV_4p5 || HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 || HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5 || HLT_PFHT1050 || HLT_PFJet500 || HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 || HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59");
      }
  }

}

void TprimeHadAnalyzer::selectLeptons()
{

    _rlm = _rlm.Define("goodMuons", "Muon_pt > 20 && abs(Muon_eta) < 2.4 && Muon_tightId && Muon_miniPFRelIso_all < 0.05 && Muon_sip3d < 3 && Muon_tightCharge == 2");
    _rlm = _rlm.Define("goodMuons_pt", "Muon_pt[goodMuons]") 
               .Define("goodMuons_eta", "Muon_eta[goodMuons]")
               .Define("goodMuons_phi", "Muon_phi[goodMuons]")
               .Define("goodMuons_mass", "Muon_mass[goodMuons]");

    _rlm = _rlm.Define("goodElectrons", "Electron_pt > 25 && abs(Electron_eta) < 2.5 && Electron_miniPFRelIso_all < 0.05 && Electron_sip3d < 2 && Electron_tightCharge == 2 && Electron_cutBased == 4");
    _rlm = _rlm.Define("goodElectrons_pt", "Electron_pt[goodElectrons]") 
               .Define("goodElectrons_eta", "Electron_eta[goodElectrons]")
               .Define("goodElectrons_phi", "Electron_phi[goodElectrons]")
               .Define("goodElectrons_mass", "Electron_mass[goodElectrons]");

    _rlm = _rlm.Define("goodMuons_4vecs", ::generate_4vec, {"goodMuons_pt", "goodMuons_eta", "goodMuons_phi", "goodMuons_mass"});
    _rlm = _rlm.Define("goodElectrons_4vecs", ::generate_4vec, {"goodElectrons_pt", "goodElectrons_eta", "goodElectrons_phi", "goodElectrons_mass"});

}

void TprimeHadAnalyzer::selectJets()
{ 
  //check the twiki page :    https://twiki.cern.ch/twiki/bin/view/CMS/JetID
  //to find jetId working points for the purpose of  your analysis.
  
  //cout << "select good jets" << endl;
  //-------------------------------------------------------
  //1-define good jets
  //-------------------------------------------------------
  // external JER Jet_pt -> Jet_pt_nom
  // and need to resort by new pt: _rlm = _rlm.Define("sorted_Jet_pt", ::sort_discriminant, {"Jet_pt_nom","Jet_pt_nom"})
  //_rlm = _rlm.Define("Jet_idx","")

  if(!_isData){
              _rlm = _rlm.Define("MCorData", "-1.0");
              auto getJERCptResolution=[this](floats &etas, floats &pts, floats &rhos)->floats
              {
                      return ::JERCptResolution(_jerc_fname, _jercptres_type, etas, pts, rhos);
              };

              auto getJERCSF=[this](floats &etas)->floats
              {
                      return ::JERCSF(_jerc_fname, _jercSF_type,"nom", etas);
              };

      _rlm = _rlm.Define("JERCptResolution", getJERCptResolution, {"Jet_eta","Jet_pt","fixedGridRhoFastjetAll"});
      _rlm = _rlm.Define("JERCSF", getJERCSF, {"Jet_eta"});
      _rlm = _rlm.Define("GenMatchJetPtvars", ::GenMatchJetPt, {"Jet_pt", "Jet_eta", "Jet_phi", "Jet_mass", "GenJet_pt", "GenJet_eta", "GenJet_phi", "GenJet_mass", "JERCptResolution"});
      _rlm = _rlm.Define("c_JER", ::getcJER, {"Jet_pt", "GenMatchJetPtvars", "JERCSF", "JERCptResolution"});
      _rlm = _rlm.Define("Jet_pt_smear_nom", "c_JER*Jet_pt");
//      _rlm = _rlm.Define("corrmet_pt_nom", ::getmetsmear, {"corrmetjson_pt", "corrmet_phi", "Jet_pt", "Jet_pt_smear_nom", "Jet_phi"}); // this is the good one
      _rlm = _rlm.Define("rawmet_pt", "MET_pt");
      _rlm = _rlm.Define("rawmet_phi", "MET_phi");

  }
  else{
      _rlm = _rlm.Define("MCorData", "1.0");
      _rlm = _rlm.Define("Jet_pt_smear_nom", "Jet_pt");
      _rlm = _rlm.Define("run_numbers", "float(run)");
      _rlm = _rlm.Define("rawmet_pt", "MET_pt");
      _rlm = _rlm.Define("rawmet_phi", "MET_phi");
  }
  
  //presel for overlap
  _rlm = _rlm.Define("pre_goodJets", "Jet_jetId > 1 && Jet_pt_smear_nom >= 30 && abs(Jet_eta) <= 2.5 && (Jet_pt_smear_nom > 50 || Jet_puId > 0)");
//  _rlm = _rlm.Define("pre_goodJets", "Jet_jetId > 1 && Jet_pt_smear_nom >= 30 && abs(Jet_eta) <= 4.5 && (Jet_pt_smear_nom > 50 || Jet_puId > 0)");
  
  _rlm = _rlm.Define("pre_nselJets","Sum(pre_goodJets)")
             .Define("pre_selJet_pt","Jet_pt_smear_nom[pre_goodJets]")
             .Define("pre_selJet_eta","Jet_eta[pre_goodJets]")
             .Define("pre_selJet_phi","Jet_phi[pre_goodJets]")
             .Define("pre_selJet_mass","Jet_mass[pre_goodJets]")
             .Define("pre_selJet_btagDeepFlavB","Jet_btagDeepFlavB[pre_goodJets]")
             .Define("pre_jet4vecs", ::generate_4vec, {"pre_selJet_pt", "pre_selJet_eta", "pre_selJet_phi", "pre_selJet_mass"});

  if(!_isData) _rlm = _rlm.Define("pre_selJet_hadronFlavour", "Jet_hadronFlavour[pre_goodJets]");
  
  // lambda function
  // for checking overlapped jets with leptons
  auto checkoverlap = [](FourVectorVec &goodjets, FourVectorVec &goodmu, FourVectorVec &goodel)
  {
      doubles mindrlepton;
      FourVectorVec sellep = goodmu;
      sellep.insert(sellep.end(), goodel.begin(), goodel.end());
      for (auto ajet: goodjets)
      {
          auto mindr = FLT_MAX;
          for (auto alepton: sellep)
          {
              auto dr = ROOT::Math::VectorUtil::DeltaR(ajet, alepton);
              if (dr < mindr) mindr = dr;
          }
          mindrlepton.emplace_back(mindr);
      }
      return mindrlepton;
  };

  _rlm = _rlm.Define("mindrlepton",checkoverlap,{"pre_jet4vecs","goodMuons_4vecs","goodElectrons_4vecs"});

  _rlm = _rlm.Define("goodJets", "mindrlepton > 0.4")
             .Define("good40Jets", "goodJets && pre_selJet_pt >= 40")
             .Define("good80Jets", "good40Jets && pre_selJet_pt >= 80");
  
  _rlm = _rlm.Define("selJet_pt","pre_selJet_pt[goodJets]")
             .Define("selJet40_pt","pre_selJet_pt[good40Jets]")
             .Define("selJet80_pt","pre_selJet_pt[good80Jets]")
            
             .Define("selJet_eta","pre_selJet_eta[goodJets]")
             .Define("selJet_phi","pre_selJet_phi[goodJets]")
             .Define("selJet_mass","pre_selJet_mass[goodJets]")
             .Define("selJet_btagDeepFlavB","pre_selJet_btagDeepFlavB[goodJets]")

             .Define("nselJets","int(selJet_pt.size())")
             .Define("nsel40Jets","int(selJet40_pt.size())")
             .Define("nsel80Jets","int(selJet80_pt.size())")
            
             .Define("jet4vecs", ::generate_4vec, {"selJet_pt", "selJet_eta", "selJet_phi", "selJet_mass"});

  if(_year==2015){        //2016preVFP - APV
      _rlm = _rlm.Define("is_deepJet_T","pre_selJet_btagDeepFlavB > 0.6502");
      _rlm = _rlm.Define("is_deepJet_M","pre_selJet_btagDeepFlavB > 0.2598");
      _rlm = _rlm.Define("is_deepJet_L","pre_selJet_btagDeepFlavB > 0.0508");
  }else if (_year==2016){ //postVFP
      _rlm = _rlm.Define("is_deepJet_T","pre_selJet_btagDeepFlavB > 0.6377");
      _rlm = _rlm.Define("is_deepJet_M","pre_selJet_btagDeepFlavB > 0.2489");
      _rlm = _rlm.Define("is_deepJet_L","pre_selJet_btagDeepFlavB > 0.0480");
  }else if (_year==2017){
      _rlm = _rlm.Define("is_deepJet_T","pre_selJet_btagDeepFlavB > 0.7476");
      _rlm = _rlm.Define("is_deepJet_M","pre_selJet_btagDeepFlavB > 0.3040");
      _rlm = _rlm.Define("is_deepJet_L","pre_selJet_btagDeepFlavB > 0.0532");
  }else if(_year==2018){
      _rlm = _rlm.Define("is_deepJet_T","pre_selJet_btagDeepFlavB > 0.7100");
      _rlm = _rlm.Define("is_deepJet_M","pre_selJet_btagDeepFlavB > 0.2783");
      _rlm = _rlm.Define("is_deepJet_L","pre_selJet_btagDeepFlavB > 0.0490");
  }

  if(!_isData){
  // you dont measure btag efficiency in data
      _rlm = _rlm.Define("goodJetsForbtag", "goodJets && abs(pre_selJet_eta) < 2.5")
                 .Define("selJetsForbtag_pt","pre_selJet_pt[goodJetsForbtag]")
                 .Define("selJetsForbtag_eta","pre_selJet_eta[goodJetsForbtag]")
                 .Define("selJetsForbtag_phi","pre_selJet_phi[goodJetsForbtag]")
                 .Define("selJetsForbtag_mass","pre_selJet_mass[goodJetsForbtag]")
                 .Define("selJetsForbtag_btag","pre_selJet_btagDeepFlavB[goodJetsForbtag]")
                 .Define("selJetsForbtag_hadronFlavour","pre_selJet_hadronFlavour[goodJetsForbtag]")
                 .Define("nselJetsForbtag","int(selJetsForbtag_pt.size())");
    
      if(_year==2015){        //2016preVFP - APV
          _rlm = _rlm.Define("WP_deepJet_T","selJetsForbtag_btag > 0.6502");
          _rlm = _rlm.Define("WP_deepJet_M","selJetsForbtag_btag > 0.2598");
          _rlm = _rlm.Define("WP_deepJet_L","selJetsForbtag_btag > 0.0508");
      }else if (_year==2016){ //postVFP
          _rlm = _rlm.Define("WP_deepJet_T","selJetsForbtag_btag > 0.6377");
          _rlm = _rlm.Define("WP_deepJet_M","selJetsForbtag_btag > 0.2489");
          _rlm = _rlm.Define("WP_deepJet_L","selJetsForbtag_btag > 0.0480");
      }else if (_year==2017){
          _rlm = _rlm.Define("WP_deepJet_T","selJetsForbtag_btag > 0.7476");
          _rlm = _rlm.Define("WP_deepJet_M","selJetsForbtag_btag > 0.3040");
          _rlm = _rlm.Define("WP_deepJet_L","selJetsForbtag_btag > 0.0532");
      }else if(_year==2018){
          _rlm = _rlm.Define("WP_deepJet_T","selJetsForbtag_btag > 0.7100");
          _rlm = _rlm.Define("WP_deepJet_M","selJetsForbtag_btag > 0.2783");
          _rlm = _rlm.Define("WP_deepJet_L","selJetsForbtag_btag > 0.0490");
      }

  }

  // for Chi2 reco
  if(_is3M){
      _rlm = _rlm.Define("goodbJets", "goodJets && abs(pre_selJet_eta) < 2.5 && is_deepJet_M");
  }else if(_is3T){
      _rlm = _rlm.Define("goodbJets", "goodJets && abs(pre_selJet_eta) < 2.5 && is_deepJet_T");
  }else{
      std::cout << "is 2M1L ?" << _is2M1L << std::endl;
      std::cout << "is 3L ?" << _is3L << std::endl;
      _rlm = _rlm.Define("goodbJets", "goodJets && abs(pre_selJet_eta) < 2.5 && is_deepJet_L");
  }

  _rlm = _rlm.Define("selbJet_pt","pre_selJet_pt[goodbJets]")
             .Define("selbJet_eta","pre_selJet_eta[goodbJets]")
             .Define("selbJet_phi","pre_selJet_phi[goodbJets]")
             .Define("selbJet_mass","pre_selJet_mass[goodbJets]")
             .Define("selbJet_btag","pre_selJet_btagDeepFlavB[goodbJets]")
             .Define("nselbJets","int(selbJet_pt.size())")
             .Define("bjet4vecs", ::generate_4vec, {"selbJet_pt", "selbJet_eta", "selbJet_phi", "selbJet_mass"});

  _rlm = _rlm.Define("goodLbJets", "goodJets && abs(pre_selJet_eta) < 2.5 && is_deepJet_L");
  _rlm = _rlm.Define("goodMbJets", "goodJets && abs(pre_selJet_eta) < 2.5 && is_deepJet_M");
  _rlm = _rlm.Define("goodTbJets", "goodJets && abs(pre_selJet_eta) < 2.5 && is_deepJet_T");

  _rlm = _rlm.Define("selLbJet_pt","pre_selJet_pt[goodLbJets]")
             .Define("selLbJet_eta","pre_selJet_eta[goodLbJets]")
             .Define("selLbJet_phi","pre_selJet_phi[goodLbJets]")
             .Define("selLbJet_mass","pre_selJet_mass[goodLbJets]")
             .Define("selLbJet_btag","pre_selJet_btagDeepFlavB[goodLbJets]")
             .Define("nselLbJets","int(selLbJet_pt.size())")
             .Define("Lbjet4vecs", ::generate_4vec, {"selLbJet_pt", "selLbJet_eta", "selLbJet_phi", "selLbJet_mass"});

  _rlm = _rlm.Define("selMbJet_pt","pre_selJet_pt[goodMbJets]")
             .Define("selMbJet_eta","pre_selJet_eta[goodMbJets]")
             .Define("selMbJet_phi","pre_selJet_phi[goodMbJets]")
             .Define("selMbJet_mass","pre_selJet_mass[goodMbJets]")
             .Define("selMbJet_btag","pre_selJet_btagDeepFlavB[goodMbJets]")
             .Define("nselMbJets","int(selMbJet_pt.size())")
             .Define("Mbjet4vecs", ::generate_4vec, {"selMbJet_pt", "selMbJet_eta", "selMbJet_phi", "selMbJet_mass"});

  _rlm = _rlm.Define("selTbJet_pt","pre_selJet_pt[goodTbJets]")
             .Define("selTbJet_eta","pre_selJet_eta[goodTbJets]")
             .Define("selTbJet_phi","pre_selJet_phi[goodTbJets]")
             .Define("selTbJet_mass","pre_selJet_mass[goodTbJets]")
             .Define("selTbJet_btag","pre_selJet_btagDeepFlavB[goodTbJets]")
             .Define("nselTbJets","int(selTbJet_pt.size())")
             .Define("Tbjet4vecs", ::generate_4vec, {"selTbJet_pt", "selTbJet_eta", "selTbJet_phi", "selTbJet_mass"});

  if(_is2M1L){
      _rlm = _rlm.Define("numJets4vecs","Mbjet4vecs")
                 .Define("numJets_pt","selMbJet_pt")
                 .Define("numJets_eta","selMbJet_eta");

      _rlm = _rlm.Define("denJets4vecs","Lbjet4vecs")
                 .Define("denJets_pt","selLbJet_pt")
                 .Define("denJets_eta","selLbJet_eta");
  }else if(_is3M){
      _rlm = _rlm.Define("numJets4vecs","Tbjet4vecs")
                 .Define("numJets_pt","selTbJet_pt")
                 .Define("numJets_eta","selTbJet_eta");

      _rlm = _rlm.Define("denJets4vecs","Mbjet4vecs")
                 .Define("denJets_pt","selMbJet_pt")
                 .Define("denJets_eta","selMbJet_eta");
  }else if(_is3T){
      _rlm = _rlm.Define("numJets4vecs","Tbjet4vecs")
                 .Define("numJets_pt","selTbJet_pt")
                 .Define("numJets_eta","selTbJet_eta");

      _rlm = _rlm.Define("denJets4vecs","Mbjet4vecs")
                 .Define("denJets_pt","selMbJet_pt")
                 .Define("denJets_eta","selMbJet_eta");
  }
  

  // Function for kinematic reconstruction
  _rlm = _rlm.Define("Chi2_Tprime",::Tprime_reconstruction,{"jet4vecs","bjet4vecs"})
             .Define("Chi2_min","Chi2_Tprime[6]")
             .Define("Chi2_max","Chi2_Tprime[17]");

  // Extra Variables for analysis
  _rlm = _rlm.Define("Higgs4vecs","(bjet4vecs[Chi2_Tprime[0]]+bjet4vecs[Chi2_Tprime[1]])")
             .Define("W4vecs","(jet4vecs[Chi2_Tprime[2]]+jet4vecs[Chi2_Tprime[3]])")
             .Define("Top4vecs","(W4vecs+bjet4vecs[Chi2_Tprime[4]])")
             .Define("secondTop4vecs","(bjet4vecs[Chi2_Tprime[0]]+bjet4vecs[Chi2_Tprime[1]]+jet4vecs[Chi2_Tprime[5]])")
             .Define("TopWvecs","W4vecs+Top4vecs")
             .Define("Tprime4vecs","(bjet4vecs[Chi2_Tprime[0]]+bjet4vecs[Chi2_Tprime[1]]+jet4vecs[Chi2_Tprime[2]]+jet4vecs[Chi2_Tprime[3]]+bjet4vecs[Chi2_Tprime[4]])");

  // materials...
  _rlm = _rlm.Define("recoTprime_cand_eta","float(Tprime4vecs.Eta())")
             .Define("recoTprime_cand_phi","float(Tprime4vecs.Phi())")
             .Define("recoTprime_cand_pt","float(Tprime4vecs.Pt())")

             .Define("recoHiggs_cand_eta","float(Higgs4vecs.Eta())")
             .Define("recoHiggs_cand_phi","float(Higgs4vecs.Phi())")
             .Define("recoHiggs_cand_pt","float(Higgs4vecs.Pt())")

             .Define("recoTop_cand_eta","float(Top4vecs.Eta())")
             .Define("recoTop_cand_phi","float(Top4vecs.Phi())")
             .Define("recoTop_cand_pt","float(Top4vecs.Pt())")

             .Define("recosecondTop_cand_pt","float(secondTop4vecs.Pt())")

             .Define("recoW_cand_eta","float(W4vecs.Eta())")
             .Define("recoW_cand_phi","float(W4vecs.Phi())")
             .Define("recoW_cand_pt","float(W4vecs.Pt())");

  _rlm = _rlm.Define("recob1_Higgs_cand_eta","float(bjet4vecs[Chi2_Tprime[0]].Eta())")
             .Define("recob1_Higgs_cand_phi","float(bjet4vecs[Chi2_Tprime[0]].Phi())")
             .Define("recob1_Higgs_cand_pt","float(bjet4vecs[Chi2_Tprime[0]].Pt())")
             .Define("recob1_Higgs_cand_p","float(bjet4vecs[Chi2_Tprime[0]].P())")
             .Define("recob1_Higgs_cand_btag","selbJet_btag[Chi2_Tprime[0]]")
             .Define("recob2_Higgs_cand_eta","float(bjet4vecs[Chi2_Tprime[1]].Eta())")
             .Define("recob2_Higgs_cand_phi","float(bjet4vecs[Chi2_Tprime[1]].Phi())")
             .Define("recob2_Higgs_cand_pt","float(bjet4vecs[Chi2_Tprime[1]].Pt())")
             .Define("recob2_Higgs_cand_p","float(bjet4vecs[Chi2_Tprime[1]].P())")
             .Define("recob2_Higgs_cand_btag","selbJet_btag[Chi2_Tprime[1]]")

             .Define("recoj1_W_cand_eta","float(jet4vecs[Chi2_Tprime[2]].Eta())")
             .Define("recoj1_W_cand_phi","float(jet4vecs[Chi2_Tprime[2]].Phi())")
             .Define("recoj1_W_cand_pt","float(jet4vecs[Chi2_Tprime[2]].Pt())")
             .Define("recoj1_W_cand_p","float(jet4vecs[Chi2_Tprime[2]].P())")
             .Define("recoj1_W_cand_btag","selJet_btagDeepFlavB[Chi2_Tprime[2]]")
             .Define("recoj2_W_cand_eta","float(jet4vecs[Chi2_Tprime[3]].Eta())")
             .Define("recoj2_W_cand_phi","float(jet4vecs[Chi2_Tprime[3]].Phi())")
             .Define("recoj2_W_cand_pt","float(jet4vecs[Chi2_Tprime[3]].Pt())")
             .Define("recoj2_W_cand_p","float(jet4vecs[Chi2_Tprime[3]].P())")
             .Define("recoj2_W_cand_btag","selJet_btagDeepFlavB[Chi2_Tprime[3]]")

             .Define("recoj_bFromTop_cand_eta","float(bjet4vecs[Chi2_Tprime[4]].Eta())")
             .Define("recoj_bFromTop_cand_phi","float(bjet4vecs[Chi2_Tprime[4]].Phi())")
             .Define("recoj_bFromTop_cand_pt","float(bjet4vecs[Chi2_Tprime[4]].Pt())")
             .Define("recoj_bFromTop_cand_p","float(bjet4vecs[Chi2_Tprime[4]].P())")
             .Define("recoj_bFromTop_cand_btag","selbJet_btag[Chi2_Tprime[4]]")

             .Define("reco_otherj_cand_eta","float(jet4vecs[Chi2_Tprime[5]].Eta())")
             .Define("reco_otherj_cand_phi","float(jet4vecs[Chi2_Tprime[5]].Phi())")
             .Define("reco_otherj_cand_pt","float(jet4vecs[Chi2_Tprime[5]].Pt())")
             .Define("reco_otherj_cand_p","float(jet4vecs[Chi2_Tprime[5]].P())")
             .Define("reco_otherj_cand_btag","selJet_btagDeepFlavB[Chi2_Tprime[5]]");

  // Kinematic reconstructions
  _rlm = _rlm.Define("invmass_leadjets", "(jet4vecs[0]+jet4vecs[1]+jet4vecs[2]+jet4vecs[3]+jet4vecs[4]).M()");

  _rlm = _rlm.Define("HT6","(selJet_pt[0]+selJet_pt[1]+selJet_pt[2]+selJet_pt[3]+selJet_pt[4]+selJet_pt[5])") 
             .Define("goodHT",::calculate_goodHT, {"selJet_pt"})
             .Define("RelHT",::calculate_RelHT, {"Top4vecs","Higgs4vecs","goodHT"})
             .Define("sixthJet_pt","selJet_pt[5]")
             .Define("newRelHT",::calculate_newRelHT, {"Top4vecs","Higgs4vecs","sixthJet_pt","goodHT"});

  _rlm = _rlm.Define("dRHbb_chi2","ROOT::VecOps::DeltaR(recob1_Higgs_cand_eta,recob2_Higgs_cand_eta,recob1_Higgs_cand_phi,recob2_Higgs_cand_phi)")
             .Define("dRWjj_chi2","ROOT::VecOps::DeltaR(recoj1_W_cand_eta,recoj2_W_cand_eta,recoj1_W_cand_phi,recoj2_W_cand_phi)")
//             .Define("dRbW_chi2","ROOT::VecOps::DeltaR(recoW_cand_eta,reco_otherj_cand_eta,recoW_cand_phi,reco_otherj_cand_phi)"); 
             .Define("dRbW_chi2","ROOT::VecOps::DeltaR(recoW_cand_eta,recoj_bFromTop_cand_eta,recoW_cand_phi,recoj_bFromTop_cand_phi)"); 

  _rlm = _rlm.Define("dRTprimeoj_chi2","ROOT::VecOps::DeltaR(recoTprime_cand_eta,reco_otherj_cand_eta,recoTprime_cand_phi,reco_otherj_cand_phi)")
             .Define("dRHTop_chi2","ROOT::VecOps::DeltaR(recoHiggs_cand_eta,recoTop_cand_eta,recoHiggs_cand_phi,recoTop_cand_phi)")
             .Define("dEtaWH_chi2","abs(recoW_cand_eta - recoHiggs_cand_eta)")
             .Define("dPhiHTop_chi2","abs(recoHiggs_cand_phi - recoTop_cand_phi)");

  _rlm = _rlm.Define("Rpt_Top2ndTop","(recosecondTop_cand_pt - recoTop_cand_pt) / recosecondTop_cand_pt")
             .Define("Rpt_HTopTprime","(recoHiggs_cand_pt - recoTop_cand_pt) / recoTprime_cand_pt")
             .Define("Rpt_TprimeHTprimeTop","(recoTprime_cand_pt / recoHiggs_cand_pt) - (recoTprime_cand_pt / recoTop_cand_pt)");

}

void TprimeHadAnalyzer::calculateEvWeight()
{

    // calculate event weight for MC only
    if (!_isData){
        std::cout <<"b tagging SF"<< std::endl;

        auto btagWeight = [this](ints &hadflav, floats &etas, floats &pts, floats &discs, ints &wpL, ints &wpM, ints &wpT)->float
        {
            return ::producer_btagWeight(_correction_btag1, _efficiency_btag1, "central", "central", hadflav, etas, pts, discs, wpL, wpM, wpT, _isTprime, _isTT, _isQCD, _isST, _isVJets, _isttH); // defined in utility.cpp
        };

        _rlm = _rlm.Define("btagWeight", btagWeight, {"selJetsForbtag_hadronFlavour","selJetsForbtag_eta","selJetsForbtag_pt","selJetsForbtag_btag", "WP_deepJet_L", "WP_deepJet_M", "WP_deepJet_T"});

    }else{
        std::cout <<"its data, no b tagging SF applied"<< std::endl;
        _rlm = _rlm.Define("btagWeight", "1.0");
    }

    int _case = 1;
    std::vector<std::string> Jets_vars_names = {"selJetsForbtag_hadronFlavour", "selJetsForbtag_eta", "selJetsForbtag_pt", "selJetsForbtag_btag"};  
    if(_case !=1){
      Jets_vars_names.emplace_back("selJetsForbtag_btag");
    }

    if(_topPtReweight == "True"){
        _rlm = _rlm.Define("evWeight_topPtSF", ::topPtWeight, {"GenPart_pt", "GenPart_pdgId", "GenPart_statusFlags"});
            if(_topPtReweightsys == "True"){
                _rlm = _rlm.Define("evWeight_topPtSFUp", "evWeight_topPtSF*evWeight_topPtSF");
                _rlm = _rlm.Define("evWeight_topPtSFDown", "1.0");
            }
    }else{
        _rlm = _rlm.Define("evWeight_topPtSF", "1.0");
    }

    // previously
    //_rlm = _rlm.Define("evWeight", "pugenWeight * btagWeight_DeepJetrecalc");
    _rlm = _rlm.Define("evWeight", "pugenWeight");
    _rlm = _rlm.Define("evWeight_L1", "pugenWeight * L1PreFiringWeight_Nom");
    _rlm = _rlm.Define("evWeight_L1btag", "pugenWeight * btagWeight * L1PreFiringWeight_Nom");
    _rlm = _rlm.Define("evWeight_L1_topPt", "pugenWeight * L1PreFiringWeight_Nom * evWeight_topPtSF");
    _rlm = _rlm.Define("evWeight_L1btag_topPt", "pugenWeight * btagWeight * L1PreFiringWeight_Nom * evWeight_topPtSF");

}

void TprimeHadAnalyzer::synch()
{

  auto checkcontents = [](unsigned int run, unsigned long long evt, unsigned int LS, double invM, float ht, float relHT, floats chi2, FourVectorVec &jet4vecs, FourVector &h4vecs, FourVector &w4vecs, FourVector &t4vecs, FourVector tprime4vecs, FourVector topWvecs)
      {
          floats out;

          cout << "Run Number " << run << " Evt Num " << evt << " LS " << LS << " M 5j " << invM << " HT " << ht << " chi2 " << chi2[6] << endl;
          out.emplace_back(evt);

          return out;
      };

  _rlm = _rlm.Define("synch_evt", checkcontents, {"run","event","luminosityBlock","invmass_Tprime","goodHT","RelHT","Chi2_Tprime","jet4vecs","Higgs4vecs","W4vecs","Top4vecs","Tprime4vecs","TopWvecs"});

  _rlm = _rlm.Define("Hb1_pt","selbJet_pt[Chi2_Tprime[0]]")
             .Define("Hb1_eta","selbJet_eta[Chi2_Tprime[0]]")
             .Define("Hb2_pt","selbJet_pt[Chi2_Tprime[1]]")
             .Define("Hb2_eta","selbJet_eta[Chi2_Tprime[1]]")
             .Define("Wj1_pt","selJet_pt[Chi2_Tprime[2]]")
             .Define("Wj1_eta","selJet_eta[Chi2_Tprime[2]]")
             .Define("Wj2_pt","selJet_pt[Chi2_Tprime[3]]")
             .Define("Wj2_eta","selJet_eta[Chi2_Tprime[3]]")
             .Define("Tbj_pt","selbJet_pt[Chi2_Tprime[4]]")
             .Define("Tbj_eta","selbJet_eta[Chi2_Tprime[4]]");

}

void TprimeHadAnalyzer::setTree(TTree *t, std::string outfilename)
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
//    _hist2dinfovector.clear();
//    _th2dhistos.clear();
    _varstostore.clear();
    _selections.clear();
  
    this->setupAnalysis();
}

void TprimeHadAnalyzer::setupObjects()
{
    // Object selection will be defined in sequence.
    // Selected objects will be stored in new vectors.
    genStudy();
    selectLeptons();
    selectJets();
    calculateEvWeight();
    //synch();
}

bool TprimeHadAnalyzer::readgoodjson(string goodjsonfname)
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

void TprimeHadAnalyzer::GetJetsys(string sys){

                auto getJERCptResolution=[this](floats &etas, floats &pts, floats &rhos)->floats
                {
                        return ::JERCptResolution(_jerc_fname, _jercptres_type, etas, pts, rhos);
                };

        //_rlm = _rlm.Define(sys, ::getsysJerc, {_jerc_fname, "Jet_pt_smear", "Jet_eta", _jercsys_total})
        _rlm = _rlm.Define("Jet_pt_"+sys+"Up", sys+"*2*Jet_pt+Jet_pt")
               .Define("Jet_pt_"+sys+"Down", "-"+sys+"*2*Jet_pt+Jet_pt")
               .Define("Jet_mass_"+sys+"Up", sys+"*Jet_mass+Jet_mass")
               .Define("Jet_mass_"+sys+"Down", "-"+sys+"*Jet_mass+Jet_mass");
                _rlm = _rlm.Define("JERCptResolution"+sys+"Up", getJERCptResolution, {"Jet_eta","Jet_pt_"+sys+"Up","fixedGridRhoFastjetAll"});
                _rlm = _rlm.Define("JERCptResolution"+sys+"Down", getJERCptResolution, {"Jet_eta","Jet_pt_"+sys+"Down","fixedGridRhoFastjetAll"});
                _rlm = _rlm.Define("GenMatchJetPtvars"+sys+"Up", ::GenMatchJetPt, {"Jet_pt_"+sys+"Up", "Jet_eta", "Jet_phi", "Jet_mass_"+sys+"Up", "GenJet_pt", "GenJet_eta", "GenJet_phi", "GenJet_mass", "JERCptResolution"+sys+"Up"});
                _rlm = _rlm.Define("GenMatchJetPtvars"+sys+"Down", ::GenMatchJetPt, {"Jet_pt_"+sys+"Down", "Jet_eta", "Jet_phi", "Jet_mass_"+sys+"Down", "GenJet_pt", "GenJet_eta", "GenJet_phi", "GenJet_mass", "JERCptResolution"+sys+"Down"});
                _rlm = _rlm.Define("c_JER"+sys+"Up", ::getcJER, {"Jet_pt_"+sys+"Up", "GenMatchJetPtvars"+sys+"Up", "JERCSF", "JERCptResolution"+sys+"Up"});
                _rlm = _rlm.Define("c_JER"+sys+"Down", ::getcJER, {"Jet_pt_"+sys+"Down", "GenMatchJetPtvars"+sys+"Down", "JERCSF", "JERCptResolution"+sys+"Down"});
                _rlm = _rlm.Define("Jet_pt_smear_"+sys+"Up", "c_JER"+sys+"Up*Jet_pt_"+sys+"Up");
                _rlm = _rlm.Define("Jet_pt_smear_"+sys+"Down", "c_JER"+sys+"Down*Jet_pt_"+sys+"Down");
//                _rlm = _rlm.Define("corrmet_pt_"+sys+"Up", ::getmetsmear, {"corrmetjson_pt", "corrmet_phi", "Jet_pt_"+sys+"Up", "Jet_pt_smear_"+sys+"Up", "Jet_phi"});
//                _rlm = _rlm.Define("corrmet_pt_"+sys+"Down", ::getmetsmear, {"corrmetjson_pt", "corrmet_phi", "Jet_pt_"+sys+"Down", "Jet_pt_smear_"+sys+"Down", "Jet_phi"});

        _rlm = _rlm.Define("goodJets_"+sys+"Up", "goodJetsID && Jet_pt_smear_"+sys+"Up>30.0 && abs(Jet_eta)<2.5");
        _rlm = _rlm.Define("goodJets_pt_"+sys+"Up", "Jet_pt_smear_"+sys+"Up[goodJets_"+sys+"Up]")
               .Define("goodJets_eta_"+sys+"Up", "Jet_eta[goodJets_"+sys+"Up]")
               .Define("goodJets_phi_"+sys+"Up", "Jet_phi[goodJets_"+sys+"Up]")
               .Define("goodJets_mass_"+sys+"Up", "Jet_mass[goodJets_"+sys+"Up]")
               .Define("goodJetsHT_"+sys+"Up", "Sum(goodJets_pt_"+sys+"Up)")
               .Define("goodJets_deepjetbtag_"+sys+"Up", "Jet_btagDeepFlavB[goodJets_"+sys+"Up]")
               .Define("goodJets_hadflav_"+sys+"Up", "Jet_hadronFlavour[goodJets_"+sys+"Up]")
               .Define("goodJets_4vecs_"+sys+"Up", ::generate_4vec, {"goodJets_pt_"+sys+"Up", "goodJets_eta_"+sys+"Up", "goodJets_phi_"+sys+"Up", "goodJets_mass_"+sys+"Up"});

        _rlm = _rlm.Define("goodJets_"+sys+"Down", "goodJetsID && Jet_pt_smear_"+sys+"Down>30.0 && abs(Jet_eta)<2.5");
        _rlm = _rlm.Define("goodJets_pt_"+sys+"Down", "Jet_pt_smear_"+sys+"Down[goodJets_"+sys+"Down]")
               .Define("goodJets_eta_"+sys+"Down", "Jet_eta[goodJets_"+sys+"Down]")
               .Define("goodJets_phi_"+sys+"Down", "Jet_phi[goodJets_"+sys+"Down]")
               .Define("goodJets_mass_"+sys+"Down", "Jet_mass[goodJets_"+sys+"Down]")
               .Define("goodJetsHT_"+sys+"Down", "Sum(goodJets_pt_"+sys+"Down)")
               .Define("goodJets_deepjetbtag_"+sys+"Down", "Jet_btagDeepFlavB[goodJets_"+sys+"Down]")
               .Define("goodJets_hadflav_"+sys+"Down", "Jet_hadronFlavour[goodJets_"+sys+"Down]")
               .Define("goodJets_4vecs_"+sys+"Down", ::generate_4vec, {"goodJets_pt_"+sys+"Down", "goodJets_eta_"+sys+"Down", "goodJets_phi_"+sys+"Down", "goodJets_mass_"+sys+"Down"});
}

void TprimeHadAnalyzer::setupAnalysis()
{
  
    if (debug){
          std::cout<< "================================//=================================" << std::endl;
          std::cout<< "Line : "<< __LINE__ << " Function : " << __FUNCTION__ << std::endl;
          std::cout<< "================================//=================================" << std::endl;
      }


    // Event weight for data it's always one. For MC, it depends on the sign
    //=====================================================================================================//
    _rlm = _rlm.Define("one", "1.0");
  
    //==========================================sum of gen weight==========================================//
    //   store sum of gen weight in outputtree. 
    //   PS:"genweight" stored in "Events" tree and "genEventSumw" stored in "Runs" tree in the inputfile
    //=====================================================================================================//

    if(!_isData){

        auto sumgenweight = _rd.Sum("genWeight");

        //cout<<"sum of gen weight "<< *sumgenweight <<endl;
        
        string sumofgenweight = Form("%f",*sumgenweight);

        _rlm = _rlm.Define("genEventSumw",sumofgenweight.c_str());

        std::cout<<"Not Data! Using genWeight"<<std::endl;
    }
    
    defineCuts();
    defineMoreVars();
    bookHists();
    setupCuts_and_Hists();
    setupTree();

}
