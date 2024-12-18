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
    }else if(_isTT || _isQCD || _isData){
        addCuts("METfilter && HLT","0");
        addCuts("nsel40Jets >= 6","00");
    }

    addCuts("selJet_pt[0] > 170 && selJet_pt[1] > 130 && selJet_pt[2] > 80 && goodHT > 500","000");

    if(_is2M1L){
        addCuts("nselMbJets == 2 && nselLbJets >= 3 && nselMbJets < 3","0000");
    }else if(_is3M){
        addCuts("nselMbJets >= 3 && nselTbJets < 3","0000");
    }else if(_is3T){
         addCuts("nselTbJets >= 3","0000");
    }else{
        cout << "no region defined" << endl;
        return;
    }

//    addCuts("isHadProcess","0");
//    addCuts("METfilter && HLT && nsel40Jets >= 6","00");
//    addCuts("selJet_pt[0] > 170 && selJet_pt[1] > 130 && selJet_pt[2] > 80 && goodHT > 500","000");
//    addCuts("nselMbJets == 2 && nselLbJets >= 3 && nselMbJets < 3","0000");

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
    //addVartoStore("btagSF_deepJet_fixedL_central");

    addVartoStore("genWeight");
    //addVartoStore("genEventSumw");
  
    //addVartoStore("selJet5_pt");

    //addVartoStore("Chi2_Tprime");

    ////addVartoStore("invmass_trueTprime");

    ////addVartoStore("chi2true_matched_Tprime");
    //////addVartoStore("chi2true_matched_H");
    //////addVartoStore("chi2true_matched_Top");
    //////addVartoStore("chi2true_matched_W");
  
    ////addVartoStore("synch_evt");
    ////addVartoStore("Hb1_pt");
    ////addVartoStore("Hb2_pt");
    ////addVartoStore("Wj1_pt");
    ////addVartoStore("Wj2_pt");
    ////addVartoStore("Tbj_pt");

    ////addVartoStore("qFromTop_eta");
    //addVartoStore("gJetFromTop_pt");
    //addVartoStore("gJetFromTop_eta");
    //addVartoStore("gJetFromTop_phi");
    ////addVartoStore("JetFromTop_eta");
  
    ////addVartoStore("qFromW_eta");
    //addVartoStore("gJetFromW_pt");
    //addVartoStore("gJetFromW_eta");
    //addVartoStore("gJetFromW_phi");
    ////addVartoStore("JetFromW_eta");
  
    ////addVartoStore("bFromH_eta");
    //addVartoStore("gJetFromH_pt");
    //addVartoStore("gJetFromH_eta");
    //addVartoStore("gJetFromH_phi");
    ////addVartoStore("JetFromH_eta"); // problem
  
    ////addVartoStore("JetFromTprime_eta");
    ////addVartoStore("JetFromH_eta");
    ////addVartoStore("JetFromW_eta");

//    addVartoStore("recob1_Higgs_cand_eta");
//    addVartoStore("recob1_Higgs_cand_phi");
//    addVartoStore("recob1_Higgs_cand_pt");
//    addVartoStore("recob1_Higgs_cand_p");
//    addVartoStore("recob1_Higgs_cand_btag");
//  
//    addVartoStore("recob2_Higgs_cand_eta");
//    addVartoStore("recob2_Higgs_cand_phi");
//    addVartoStore("recob2_Higgs_cand_pt");
//    addVartoStore("recob2_Higgs_cand_p");
//    addVartoStore("recob2_Higgs_cand_btag");
//  
//    addVartoStore("recoj1_W_cand_eta");
//    addVartoStore("recoj1_W_cand_phi");
//    addVartoStore("recoj1_W_cand_pt");
//    addVartoStore("recoj1_W_cand_p");
//    addVartoStore("recoj1_W_cand_btag");
//  
//    addVartoStore("recoj2_W_cand_eta");
//    addVartoStore("recoj2_W_cand_phi");
//    addVartoStore("recoj2_W_cand_pt");
//    addVartoStore("recoj2_W_cand_p");
//    addVartoStore("recoj2_W_cand_btag");
//
//    addVartoStore("recoj_bFromTop_cand_eta");
//    addVartoStore("recoj_bFromTop_cand_phi");
//    addVartoStore("recoj_bFromTop_cand_pt");
//    addVartoStore("recoj_bFromTop_cand_p");
//    addVartoStore("recoj_bFromTop_cand_btag");
//  
//    addVartoStore("reco_otherj_cand_eta");
//    addVartoStore("reco_otherj_cand_phi");
//    addVartoStore("reco_otherj_cand_pt");
//    addVartoStore("reco_otherj_cand_p");
//    addVartoStore("reco_otherj_cand_btag");

    ////addVartoStore("W_chi2_eta");
    ////addVartoStore("W_chi2_phi");
  
    ////addVartoStore("dRbb");
    ////addVartoStore("mbb");

    // DNN Study
    // Cut0
    addVartoStore("nselJets");
    addVartoStore("nselbJets");

    // btag in binary
    addVartoStore("is_deepJet_T");
    addVartoStore("is_deepJet_M");
    addVartoStore("is_deepJet_L");

    addVartoStore("selJetsForbtag_pt");
    addVartoStore("selJetsForbtag_eta");
    addVartoStore("selJetsForbtag_phi");
    addVartoStore("selJetsForbtag_mass");
    addVartoStore("selJetsForbtag_btag");
    addVartoStore("selJetsForbtag_hadronFlavour");
    addVartoStore("nselJetsForbtag");

    addVartoStore("selJet1_pt");
    addVartoStore("selJet1_pt_massnom");
    addVartoStore("selJet1_eta");
    addVartoStore("selJet1_phi");
    addVartoStore("selJet1_e");
    addVartoStore("selJet1_e_massnom");
    addVartoStore("selJet1_btag");

    addVartoStore("selJet2_pt");
    addVartoStore("selJet2_pt_massnom");
    addVartoStore("selJet2_eta");
    addVartoStore("selJet2_phi");
    addVartoStore("selJet2_e");
    addVartoStore("selJet2_e_massnom");
    addVartoStore("selJet2_btag");

    addVartoStore("selJet3_pt");
    addVartoStore("selJet3_pt_massnom");
    addVartoStore("selJet3_eta");
    addVartoStore("selJet3_phi");
    addVartoStore("selJet3_e");
    addVartoStore("selJet3_e_massnom");
    addVartoStore("selJet3_btag");

    addVartoStore("selJet4_pt");
    addVartoStore("selJet4_pt_massnom");
    addVartoStore("selJet4_eta");
    addVartoStore("selJet4_phi");
    addVartoStore("selJet4_e");
    addVartoStore("selJet4_e_massnom");
    addVartoStore("selJet4_btag");

    addVartoStore("selJet5_pt");
    addVartoStore("selJet5_pt_massnom");
    addVartoStore("selJet5_eta");
    addVartoStore("selJet5_phi");
    addVartoStore("selJet5_e");
    addVartoStore("selJet5_e_massnom");
    addVartoStore("selJet5_btag");

    addVartoStore("selbJet1_pt");
    addVartoStore("selbJet1_pt_massnom");
    addVartoStore("selbJet1_eta");
    addVartoStore("selbJet1_phi");
    addVartoStore("selbJet1_e");
    addVartoStore("selbJet1_e_massnom");
    addVartoStore("selbJet1_btag");

    addVartoStore("selbJet2_pt");
    addVartoStore("selbJet2_pt_massnom");
    addVartoStore("selbJet2_eta");
    addVartoStore("selbJet2_phi");
    addVartoStore("selbJet2_e");
    addVartoStore("selbJet2_e_massnom");
    addVartoStore("selbJet2_btag");

    addVartoStore("Chi2_min");
    addVartoStore("goodHT");
    addVartoStore("invmass_2ndTop");
    addVartoStore("H_mass");

    addVartoStore("RelHT");          // Cut 1
    addVartoStore("Chi2_max");       // Cut 2
    addVartoStore("dRHbb_chi2");     // Cut 3
    addVartoStore("Chi2_min_H");     // Cut 4
    addVartoStore("dRWjj_chi2");     // Cut 5
    addVartoStore("dRbW_chi2");      // Cut 6

    // Candidates
    addVartoStore("Chi2_min_W");
    addVartoStore("Chi2_min_Top");
    addVartoStore("mindR_dRbb");
    addVartoStore("mindR_mbb");
    addVartoStore("Top_mass");
    addVartoStore("W_mass");
    addVartoStore("invmass_WH");
    addVartoStore("invmass_Tprime");
    addVartoStore("invmass_leadjets");//etc
    addVartoStore("R_TopH");
    addVartoStore("R_2ndTopW");
    addVartoStore("newRelHT");
    addVartoStore("dRTprimeoj_chi2");
    addVartoStore("dRHTop_chi2");
    addVartoStore("dEtaWH_chi2");
    addVartoStore("dPhiHTop_chi2");
    addVartoStore("Rpt_Top2ndTop");
    addVartoStore("Rpt_HTopTprime");
    addVartoStore("Rpt_TprimeHTprimeTop");

}
//.================================Histogram Definitions===========================================//
// _hist1dinfovector contains the information of histogram definitions (as TH1DModel)
// the variable to be used for filling and the minimum cutstep for which the histogram should be filled
//dd1DHist(TH1DModel histdef, std::string variable, std::string weight, string mincutstep="");
//=================================================================================================//
void TprimeHadAnalyzer::bookHists()
{

  add1DHist( {"hnevents", "Number of Events", 2, -0.5, 1.5}, "one", "evWeight", "");
  //add2DHist( {"h_btagEff", "Jet pT", "Jet eta", 2, -0.5, 1.5}, "one", "evWeight", "");

  //add1DHist( {"h_nJets", "Number of Jets", 10, 5, 15}, "nselJets", "evWeight", "000");
  //add1DHist( {"h_nbJets", "Number of b-tagged Jets", 5, 2, 8}, "nselbJets", "evWeight", "000");
  //add1DHist( {"h_invmass_Tprime", "invariant mass of 5 jets from chi2: dnn cut", 100, 0, 1800}, "invmass_Tprime", "evWeight", "00");
  //add1DHist( {"h_invmass_Tprime", "invariant mass of 5 jets from chi2: cut 0", 100, 0, 1800}, "invmass_Tprime", "evWeight", "10000");
  //// cut0
  //add1DHist( {"h_invmass_Tprime", "invariant mass of 5 jets from chi2: cut 1", 100, 0, 1800}, "invmass_Tprime", "evWeight", "100010");
  //add1DHist( {"h_invmass_Tprime", "invariant mass of 5 jets from chi2: cut 2", 100, 0, 1800}, "invmass_Tprime", "evWeight", "1000100");
  //add1DHist( {"h_invmass_Tprime", "invariant mass of 5 jets from chi2: cut 3", 100, 0, 1800}, "invmass_Tprime", "evWeight", "10001000");
  //add1DHist( {"h_invmass_Tprime", "invariant mass of 5 jets from chi2: cut 4", 100, 0, 1800}, "invmass_Tprime", "evWeight", "100010000");
  //add1DHist( {"h_invmass_Tprime", "invariant mass of 5 jets from chi2: cut 5", 100, 0, 1800}, "invmass_Tprime", "evWeight", "1000100000");
  //// cut6
  //add1DHist( {"h_invmass_Tprime", "invariant mass of 5 jets from chi2: cut 6", 100, 0, 1800}, "invmass_Tprime", "evWeight", "10001000000");

  //add1DHist( {"h_H_mass", "in cut 1", 100, 0, 1800}, "H_mass", "evWeight", "100010");
  //add1DHist( {"h_H_mass", "in cut 2", 100, 0, 1800}, "H_mass", "evWeight", "1000100");
  //add1DHist( {"h_H_mass", "in cut 3", 100, 0, 1800}, "H_mass", "evWeight", "10001000");
  //add1DHist( {"h_H_mass", "in cut 4", 100, 0, 1800}, "H_mass", "evWeight", "100010000");
  //add1DHist( {"h_H_mass", "in cut 5", 100, 0, 1800}, "H_mass", "evWeight", "1000100000");
  //add1DHist( {"h_H_mass", "in cut 6", 100, 0, 1800}, "H_mass", "evWeight", "10001000000");

  //add1DHist( {"h_RelHT", "cut 1", 100, 0, 1800}, "RelHT", "evWeight", "100010");
  //add1DHist( {"h_RelHT", "cut 2", 100, 0, 1800}, "RelHT", "evWeight", "1000100");
  //add1DHist( {"h_RelHT", "cut 3", 100, 0, 1800}, "RelHT", "evWeight", "10001000");
  //add1DHist( {"h_RelHT", "cut 4", 100, 0, 1800}, "RelHT", "evWeight", "100010000");
  //add1DHist( {"h_RelHT", "cut 5", 100, 0, 1800}, "RelHT", "evWeight", "1000100000");
  //add1DHist( {"h_RelHT", "cut 6", 100, 0, 1800}, "RelHT", "evWeight", "10001000000");

  //add1DHist( {"h_Chi2_max", "cut 1", 100, 0, 1800}, "Chi2_max", "evWeight", "100010");
  //add1DHist( {"h_Chi2_max", "cut 2", 100, 0, 1800}, "Chi2_max", "evWeight", "1000100");
  //add1DHist( {"h_Chi2_max", "cut 3", 100, 0, 1800}, "Chi2_max", "evWeight", "10001000");
  //add1DHist( {"h_Chi2_max", "cut 4", 100, 0, 1800}, "Chi2_max", "evWeight", "100010000");
  //add1DHist( {"h_Chi2_max", "cut 5", 100, 0, 1800}, "Chi2_max", "evWeight", "1000100000");
  //add1DHist( {"h_Chi2_max", "cut 6", 100, 0, 1800}, "Chi2_max", "evWeight", "10001000000");

  //add1DHist( {"h_dRHbb_chi2", "cut 1", 100, 0, 1800}, "dRHbb_chi2", "evWeight", "100010");
  //add1DHist( {"h_dRHbb_chi2", "cut 2", 100, 0, 1800}, "dRHbb_chi2", "evWeight", "1000100");
  //add1DHist( {"h_dRHbb_chi2", "cut 3", 100, 0, 1800}, "dRHbb_chi2", "evWeight", "10001000");
  //add1DHist( {"h_dRHbb_chi2", "cut 4", 100, 0, 1800}, "dRHbb_chi2", "evWeight", "100010000");
  //add1DHist( {"h_dRHbb_chi2", "cut 5", 100, 0, 1800}, "dRHbb_chi2", "evWeight", "1000100000");
  //add1DHist( {"h_dRHbb_chi2", "cut 6", 100, 0, 1800}, "dRHbb_chi2", "evWeight", "10001000000");

  //add1DHist( {"h_Chi2_min_H", "cut 1", 100, 0, 1800}, "Chi2_min_H", "evWeight", "100010");
  //add1DHist( {"h_Chi2_min_H", "cut 2", 100, 0, 1800}, "Chi2_min_H", "evWeight", "1000100");
  //add1DHist( {"h_Chi2_min_H", "cut 3", 100, 0, 1800}, "Chi2_min_H", "evWeight", "10001000");
  //add1DHist( {"h_Chi2_min_H", "cut 4", 100, 0, 1800}, "Chi2_min_H", "evWeight", "100010000");
  //add1DHist( {"h_Chi2_min_H", "cut 5", 100, 0, 1800}, "Chi2_min_H", "evWeight", "1000100000");
  //add1DHist( {"h_Chi2_min_H", "cut 6", 100, 0, 1800}, "Chi2_min_H", "evWeight", "10001000000");

  //add1DHist( {"h_dRWjj_chi2", "cut 1", 100, 0, 1800}, "dRWjj_chi2", "evWeight", "100010");
  //add1DHist( {"h_dRWjj_chi2", "cut 2", 100, 0, 1800}, "dRWjj_chi2", "evWeight", "1000100");
  //add1DHist( {"h_dRWjj_chi2", "cut 3", 100, 0, 1800}, "dRWjj_chi2", "evWeight", "10001000");
  //add1DHist( {"h_dRWjj_chi2", "cut 4", 100, 0, 1800}, "dRWjj_chi2", "evWeight", "100010000");
  //add1DHist( {"h_dRWjj_chi2", "cut 5", 100, 0, 1800}, "dRWjj_chi2", "evWeight", "1000100000");
  //add1DHist( {"h_dRWjj_chi2", "cut 6", 100, 0, 1800}, "dRWjj_chi2", "evWeight", "10001000000");

  //add1DHist( {"h_dRbW_chi2", "iut 1", 100, 0, 1800}, "dRbW_chi2", "evWeight", "100010");
  //add1DHist( {"h_dRbW_chi2", "iut 2", 100, 0, 1800}, "dRbW_chi2", "evWeight", "1000100");
  //add1DHist( {"h_dRbW_chi2", "iut 3", 100, 0, 1800}, "dRbW_chi2", "evWeight", "10001000");
  //add1DHist( {"h_dRbW_chi2", "iut 4", 100, 0, 1800}, "dRbW_chi2", "evWeight", "100010000");
  //add1DHist( {"h_dRbW_chi2", "iut 5", 100, 0, 1800}, "dRbW_chi2", "evWeight", "1000100000");
  //add1DHist( {"h_dRbW_chi2", "iut 6", 100, 0, 1800}, "dRbW_chi2", "evWeight", "10001000000");
/*
  add1DHist( {"h_Jet_pt", "pT of selected Jets", 100, 30, 300}, "selJet_pt", "evWeight", "0");
  add1DHist( {"h_Jet_eta", "eta of selected Jets", 100, -5, 5}, "selJet_eta", "evWeight", "0");
  add1DHist( {"h_Jet_phi", "phi of selected Jets", 100, -3.5, 3.5}, "selJet_phi", "evWeight", "0");
  add1DHist( {"h_Jet_mass", "mass of selected Jets", 100, 0, 200}, "selJet_mass", "evWeight", "0");
  add1DHist( {"h_Jet_btagDeepB", "DeepCSV value of selected Jets", 100, 0, 1}, "selJet_btagDeepB", "evWeight", "0");
  add1DHist( {"h_Jet_e", "energy of selected Jets", 100, 0, 200}, "selJet_e", "evWeight", "0");

  add1DHist( {"h_Jet1_pt", "pT of selected 1st Jets", 100, 30, 800}, "selJet1_pt", "evWeight", "0");
  add1DHist( {"h_Jet1_eta", "eta of selected 1st Jets", 100, -5, 5}, "selJet1_eta", "evWeight", "0");
  add1DHist( {"h_Jet1_phi", "phi of selected 1st Jets", 100, -3.5, 3.5}, "selJet1_phi", "evWeight", "0");
  add1DHist( {"h_Jet1_mass", "mass of selected 1st Jets", 100, 0, 200}, "selJet1_mass", "evWeight", "0");
  add1DHist( {"h_Jet1_btagDeepB", "DeepCSV value of selected 1st Jets", 100, 0, 1}, "selJet1_btagDeepB", "evWeight", "0");
  add1DHist( {"h_Jet1_e", "e of selected 1st Jets", 100, 50, 1000}, "selJet1_e", "evWeight", "0");

  add1DHist( {"h_Jet2_pt", "pT of selected 2nd Jets", 100, 30, 600}, "selJet2_pt", "evWeight", "0");
  add1DHist( {"h_Jet2_eta", "eta of selected 2nd Jets", 100, -5, 5}, "selJet2_eta", "evWeight", "0");
  add1DHist( {"h_Jet2_phi", "phi of selected 2nd Jets", 100, -3.5, 3.5}, "selJet2_phi", "evWeight", "0");
  add1DHist( {"h_Jet2_mass", "mass of selected 2nd Jets", 100, 0, 150}, "selJet2_mass", "evWeight", "0");
  add1DHist( {"h_Jet2_btagDeepB", "DeepCSV value of selected 2nd Jets", 100, 0, 1}, "selJet2_btagDeepB", "evWeight", "0");
  add1DHist( {"h_Jet2_e", "e of selected 2nd Jets", 100, 30, 600}, "selJet2_e", "evWeight", "0");

  add1DHist( {"h_Jet3_pt", "pT of selected 3nd Jets", 100, 30, 400}, "selJet3_pt", "evWeight", "0");
  add1DHist( {"h_Jet3_eta", "eta of selected 3nd Jets", 100, -5, 5}, "selJet3_eta", "evWeight", "0");
  add1DHist( {"h_Jet3_phi", "phi of selected 3nd Jets", 100, -3.5, 3.5}, "selJet3_phi", "evWeight", "0");
  add1DHist( {"h_Jet3_mass", "mass of selected 3nd Jets", 100, 0, 50}, "selJet3_mass", "evWeight", "0");
  add1DHist( {"h_Jet3_btagDeepB", "DeepCSV value of selected 3nd Jets", 100, 0, 1}, "selJet3_btagDeepB", "evWeight", "0");
  add1DHist( {"h_Jet3_e", "e of selected 3nd Jets", 100, 30, 400}, "selJet3_e", "evWeight", "0");

  add1DHist( {"h_Jet4_pt", "pT of selected 4nd Jets", 100, 40, 200}, "selJet4_pt", "evWeight", "0");
  add1DHist( {"h_Jet4_eta", "eta of selected 4nd Jets", 100, -5, 5}, "selJet4_eta", "evWeight", "0");
  add1DHist( {"h_Jet4_phi", "phi of selected 4nd Jets", 100, -3.5, 3.5}, "selJet4_phi", "evWeight", "0");
  add1DHist( {"h_Jet4_mass", "mass of selected 4nd Jets", 100, 0, 50}, "selJet4_mass", "evWeight", "0");
  add1DHist( {"h_Jet4_btagDeepB", "DeepCSV value of selected 4nd Jets", 100, 0, 1}, "selJet4_btagDeepB", "evWeight", "0");
  add1DHist( {"h_Jet4_e", "e of selected 4th Jets", 100, 30, 300}, "selJet4_e", "evWeight", "0");

  add1DHist( {"h_Jet5_pt", "pT of selected 5nd Jets", 100, 50, 200}, "selJet5_pt", "evWeight", "0");
  add1DHist( {"h_Jet5_eta", "eta of selected 5nd Jets", 100, -5, 5}, "selJet5_eta", "evWeight", "0");
  add1DHist( {"h_Jet5_phi", "phi of selected 5nd Jets", 100, -3.5, 3.5}, "selJet5_phi", "evWeight", "0");
  add1DHist( {"h_Jet5_mass", "mass of selected 5nd Jets", 100, 0, 50}, "selJet5_mass", "evWeight", "0");
  add1DHist( {"h_Jet5_btagDeepB", "DeepCSV value of selected 5nd Jets", 100, 0, 1}, "selJet5_btagDeepB", "evWeight", "0");
  add1DHist( {"h_Jet5_e", "e of selected 5th Jets", 100, 30, 300}, "selJet5_e", "evWeight", "0");

//  add1DHist( {"h_bJet_pt", "pT of selected bJets", 100, 30, 300}, "selbJet_pt", "evWeight", "0");
//  add1DHist( {"h_bJet_eta", "eta of selected bJets", 100, -5, 5}, "selbJet_eta", "evWeight", "0");
//  add1DHist( {"h_bJet_phi", "phi of selected bJets", 100, -3.5, 3.5}, "selbJet_phi", "evWeight", "0");
//  add1DHist( {"h_bJet_mass", "mass of selected bJets", 100, 0, 200}, "selbJet_mass", "evWeight", "0");
//  add1DHist( {"h_bJet_btagDeepB", "DeepCSV value of selected 1st bJets", 100, 0, 1}, "selbJet_btagDeepB", "evWeight", "0");
//  add1DHist( {"h_bJet_e", "e of selected bJets", 100, 0, 200}, "selbJet_e", "evWeight", "0");

  add1DHist( {"h_bJet1_pt", "pT of selected 1st bJets", 100, 30, 700}, "selbJet1_pt", "evWeight", "0");
  add1DHist( {"h_bJet1_eta", "eta of selected 1st bJets", 100, -5, 5}, "selbJet1_eta", "evWeight", "0");
  add1DHist( {"h_bJet1_phi", "phi of selected 1st bJets", 100, -3.5, 3.5}, "selbJet1_phi", "evWeight", "0");
  add1DHist( {"h_bJet1_mass", "mass of selected 1st bJets", 100, 0, 200}, "selbJet1_mass", "evWeight", "0");
  add1DHist( {"h_bJet1_btagDeepB", "DeepCSV value of selected 1st bJets", 100, 0, 1}, "selbJet1_btagDeepB", "evWeight", "0");
  add1DHist( {"h_bJet1_e", "energy of selected 1st bJets", 100, 30, 500}, "selbJet1_e", "evWeight", "0");

  add1DHist( {"h_bJet2_pt", "pT of selected 2nd bJets", 100, 30, 500}, "selbJet2_pt", "evWeight", "0");
  add1DHist( {"h_bJet2_eta", "eta of selected 2nd bJets", 100, -5, 5}, "selbJet2_eta", "evWeight", "0");
  add1DHist( {"h_bJet2_phi", "phi of selected 2nd bJets", 100, -3.5, 3.5}, "selbJet2_phi", "evWeight", "0");
  add1DHist( {"h_bJet2_mass", "mass of selected 2nd bJets", 100, 0, 50}, "selbJet2_mass", "evWeight", "0");
  add1DHist( {"h_bJet2_btagDeepB", "DeepCSV value of selected 2nd bJets", 100, 0, 1}, "selbJet2_btagDeepB", "evWeight", "0");
  add1DHist( {"h_bJet2_e", "energy of selected 2nd bJets", 100, 30, 300}, "selbJet2_e", "evWeight", "0");

//  add1DHist( {"h_bJet3_pt", "pT of selected 3nd bJets", 100, 30, 300}, "selbJet3_pt", "evWeight", "0");
//  add1DHist( {"h_bJet3_eta", "eta of selected 3nd bJets", 100, -5, 5}, "selbJet3_eta", "evWeight", "0");
//  add1DHist( {"h_bJet3_phi", "phi of selected 3nd bJets", 100, -3.5, 3.5}, "selbJet3_phi", "evWeight", "0");
//  add1DHist( {"h_bJet3_mass", "mass of selected 3nd bJets", 100, 0, 30}, "selbJet3_mass", "evWeight", "0");
//  add1DHist( {"h_bJet3_btagDeepB", "DeepCSV value of selected 3nd bJets", 100, 0, 1}, "selbJet3_btagDeepB", "evWeight", "0");
//  add1DHist( {"h_bJet3_e", "e of selected 3nd bJets", 100, 0, 30}, "selbJet3_e", "evWeight", "0");

//  add1DHist( {"h_bJet4_pt", "pT of selected 4nd bJets", 100, 40, 200}, "selbJet4_pt", "evWeight", "0");
//  add1DHist( {"h_bJet4_eta", "eta of selected 4nd bJets", 100, -5, 5}, "selbJet4_eta", "evWeight", "0");
//  add1DHist( {"h_bJet4_phi", "phi of selected 4nd bJets", 100, -4.5, 4.5}, "selbJet4_phi", "evWeight", "0");
//  add1DHist( {"h_bJet4_mass", "mass of selected 4nd bJets", 100, 0, 30}, "selbJet4_mass", "evWeight", "0");
//  add1DHist( {"h_bJet4_btagDeepB", "DeepCSV value of selected 4nd bJets", 100, 0, 1}, "selbJet4_btagDeepB", "evWeight", "0");

  add1DHist( {"h_dR_Hbb", "Delta R between two b jets from H Chi2", 100, 0, 6}, "dRHbb_chi2", "evWeight", "0");
  add1DHist( {"h_dR_Wjj", "Delta R between two jets from W Chi2", 100, 0.1, 6}, "dRWjj_chi2", "evWeight", "0");
  
  add1DHist( {"h_mindR_dRbb", "Delta R between two b jets having mininum Delta R", 100, 0, 5}, "mindR_dRbb", "evWeight", "0");
  add1DHist( {"h_mindR_mbb", "invariant mass of two b jets having mininum Delta R", 100, 0, 500}, "mindR_mbb", "evWeight", "0");

  add1DHist( {"h_goodHT", "HT of jets pT over 30", 100, 0, 2500}, "goodHT", "evWeight", "0");

  add1DHist( {"h_Jet1_pt_massnom", "pT of selected 1st Jets", 100, 0, 2.5}, "selJet1_pt_massnom", "evWeight", "0");
  add1DHist( {"h_Jet2_pt_massnom", "pT of selected 2nd Jets", 100, 0, 1.5}, "selJet2_pt_massnom", "evWeight", "0");
  add1DHist( {"h_Jet3_pt_massnom", "pT of selected 3rd Jets", 100, 0, 1}, "selJet3_pt_massnom", "evWeight", "0");
  add1DHist( {"h_Jet4_pt_massnom", "pT of selected 4th Jets", 100, 0, 0.7}, "selJet4_pt_massnom", "evWeight", "0");
  add1DHist( {"h_Jet5_pt_massnom", "pT of selected 5th Jets", 100, 0, 0.4}, "selJet5_pt_massnom", "evWeight", "0");
  add1DHist( {"h_bJet1_pt_massnom", "pT of selected 1st bJets", 100, 0, 1.2}, "selbJet1_pt_massnom", "evWeight", "0");
  add1DHist( {"h_bJet2_pt_massnom", "pT of selected 2nd bJets", 100, 0, 0.5}, "selbJet2_pt_massnom", "evWeight", "0");

  add1DHist( {"h_Jet1_e_massnom", "energy of selected 1st Jets", 100, 0, 4}, "selJet1_e_massnom", "evWeight", "0");
  add1DHist( {"h_Jet2_e_massnom", "energy of selected 2nd Jets", 100, 0, 4}, "selJet2_e_massnom", "evWeight", "0");
  add1DHist( {"h_Jet3_e_massnom", "energy of selected 3rd Jets", 100, 0, 4}, "selJet3_e_massnom", "evWeight", "0");
  add1DHist( {"h_Jet4_e_massnom", "energy of selected 4th Jets", 100, 0, 4}, "selJet4_e_massnom", "evWeight", "0");
  add1DHist( {"h_Jet5_e_massnom", "energy of selected 5th Jets", 100, 0, 4}, "selJet5_e_massnom", "evWeight", "0");
  add1DHist( {"h_bJet1_e_massnom", "energy of selected 1st bJets", 100, 0, 2}, "selbJet1_e_massnom", "evWeight", "0");
  add1DHist( {"h_bJet2_e_massnom", "energy of selected 2nd bJets", 100, 0, 2}, "selbJet2_e_massnom", "evWeight", "0");

  add1DHist( {"h_Jet1_pt_htnom", "pT of selected 1st Jets", 100, 0, 0.8}, "selJet1_pt_htnom", "evWeight", "0");
  add1DHist( {"h_Jet2_pt_htnom", "pT of selected 2nd Jets", 100, 0, 0.8}, "selJet2_pt_htnom", "evWeight", "0");
  add1DHist( {"h_Jet3_pt_htnom", "pT of selected 3rd Jets", 100, 0, 0.3}, "selJet3_pt_htnom", "evWeight", "0");
  add1DHist( {"h_Jet4_pt_htnom", "pT of selected 4th Jets", 100, 0, 0.3}, "selJet4_pt_htnom", "evWeight", "0");
  add1DHist( {"h_Jet5_pt_htnom", "pT of selected 5th Jets", 100, 0, 0.2}, "selJet5_pt_htnom", "evWeight", "0");
  add1DHist( {"h_bJet1_pt_htnom", "pT of selected 1st bJets", 100, 0, 0.8}, "selbJet1_pt_htnom", "evWeight", "0");
  add1DHist( {"h_bJet2_pt_htnom", "pT of selected 2nd bJets", 100, 0, 0.5}, "selbJet2_pt_htnom", "evWeight", "0");

  add1DHist( {"h_Jet1_e_htnom", "energy of selected 1st Jets", 100, 0, 2.5}, "selJet1_e_htnom", "evWeight", "0");
  add1DHist( {"h_Jet2_e_htnom", "energy of selected 2nd Jets", 100, 0, 2.5}, "selJet2_e_htnom", "evWeight", "0");
  add1DHist( {"h_Jet3_e_htnom", "energy of selected 3rd Jets", 100, 0, 2.5}, "selJet3_e_htnom", "evWeight", "0");
  add1DHist( {"h_Jet4_e_htnom", "energy of selected 4th Jets", 100, 0, 2.5}, "selJet4_e_htnom", "evWeight", "0");
  add1DHist( {"h_Jet5_e_htnom", "energy of selected 5th Jets", 100, 0, 2.5}, "selJet5_e_htnom", "evWeight", "0");
  add1DHist( {"h_bJet1_e_htnom", "energy of selected 1st bJets", 100, 0, 1.5}, "selbJet1_e_htnom", "evWeight", "0");
  add1DHist( {"h_bJet2_e_htnom", "energy of selected 2nd bJets", 100, 0, 1}, "selbJet2_e_htnom", "evWeight", "0");

  add1DHist( {"h_goodHT_massnom", "HT of jets pT over 30", 100, 0, 7}, "goodHT_massnom", "evWeight", "0");
  add1DHist( {"h_invmass_htnom", "invariant mass of 5 jets from chi2", 100, 0, 3}, "invmass_htnom", "evWeight", "0");

  add1DHist( {"h_Chi2_min", "minimum Chi2", 100, 0, 100}, "Chi2_min", "evWeight", "0");
  add1DHist( {"h_Chi2_minH", "minimum Chi2 for Higgs", 100, 0, 100}, "Chi2_min_H", "evWeight", "0");
  add1DHist( {"h_Chi2_minW", "minimum Chi2 for W", 100, 10, 100}, "Chi2_min_W", "evWeight", "0");
  add1DHist( {"h_Chi2_minTop", "minimum Chi2 for Top", 100, 0, 100}, "Chi2_min_Top", "evWeight", "0");

  add1DHist( {"h_H_mass", "mass of the Higgs from minChi2", 100, 50, 200}, "H_mass", "evWeight", "0");
  add1DHist( {"h_W_mass", "mass of the W from minChi2", 100, 10, 300}, "W_mass", "evWeight", "0");
  add1DHist( {"h_Top_mass", "mass of the Top from minChi2", 100, 50, 400}, "Top_mass", "evWeight", "0");

  add1DHist( {"h_invmass_leadjets", "invariant mass of 5 leading jets", 100, 0, 3000}, "invmass_leadjets", "evWeight", "0");
  add1DHist( {"h_invmass_Tprime", "invariant mass of 5 jets from chi2", 100, 0, 1700}, "invmass_Tprime", "evWeight", "0");
  //add1DHist( {"h_invmass_trueTprime", "invariant mass of 5 jets from trueTprime", 200, 0, 1300}, "invmass_trueTprime", "evWeight", "00000");
  add1DHist( {"h_invmass_2ndTop", "invariant mass of 2nd Top", 100, 0, 1000}, "invmass_2ndTop", "evWeight", "0");
  add1DHist( {"h_invmass_Higgs", "invariant mass of Higgs", 100, 0, 400}, "invmass_Higgs", "evWeight", "0");

  add1DHist( {"h_RelHT", "Relative HT", 100, 0, 1}, "RelHT", "evWeight", "0");
  add1DHist( {"h_chi2_trueTprime", "number of matched chi2 jets with true Tprime", 6, 0, 6}, "chi2true_matched_Tprime", "evWeight", "000");
  add1DHist( {"h_chi2_trueH", "number of matched chi2 jets with true Higgs", 3, 0, 3}, "chi2true_matched_H", "evWeight", "000");
  add1DHist( {"h_chi2_trueTop", "number of matched chi2 jets with true Top", 4, 0, 4}, "chi2true_matched_Top", "evWeight", "000");
  add1DHist( {"h_chi2_trueW", "number of matched chi2 jets with true W", 3, 0, 3}, "chi2true_matched_W", "evWeight", "000");
*/

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
  // from AN 2021_140/v4
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

  // huh
  //if (!isDefined("HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94")) _rlm = _rlm.Define("HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94", "false"); 
  //if (!isDefined("HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59")) _rlm = _rlm.Define("HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59", "false"); 
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
          _rlm = _rlm.Define("HLT","HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 || HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepCSV_4p5 || HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 || HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5 || HLT_PFHT1050 || HLT_PFJet500");
      }
  }

//  _rlm = _rlm.Define("isHadTprime",::isHadWHiggs,{"p4_GenPart","GenPart_pdgId","GenPart_genPartIdxMother"});
//
//  _rlm  = _rlm.Define("sel_genpTprime",isQfromTopHTprime,{"p4_GenPart","GenPart_pdgId","GenPart_genPartIdxMother"})
//              .Define("pFromTprime_eta","GenPart_eta[sel_genpTprime]")
//              .Define("pFromTprime_phi","GenPart_phi[sel_genpTprime]");
//
//  _rlm  = _rlm.Define("sel_genjTprime",isdR04,{"GenJet_eta","pFromTprime_eta","GenJet_phi","pFromTprime_phi"})
//              .Define("gJetFromTprime_pt","GenJet_pt[sel_genjTprime]");
//
//  _rlm  = _rlm.Define("sel_jetTprime",isJetFromgJet,{"Jet_pt","GenJet_pt","gJetFromTprime_pt","Jet_genJetIdx"})
//              .Define("JetFromTprime_pt","Jet_pt[sel_jetTprime]")
//              .Define("JetFromTprime_eta","Jet_eta[sel_jetTprime]")
//              .Define("JetFromTprime_phi","Jet_phi[sel_jetTprime]")
//              .Define("JetFromTprime_mass","Jet_mass[sel_jetTprime]")
//              .Define("p4_JetFromTprime",::generate_4vec, {"JetFromTprime_pt","JetFromTprime_eta","JetFromTprime_phi","JetFromTprime_mass"})
//              .Define("invmass_trueTprime", "(p4_JetFromTprime[0]+p4_JetFromTprime[1]+p4_JetFromTprime[2]+p4_JetFromTprime[3]+p4_JetFromTprime[4]).M()");
//
//  _rlm = _rlm.Define("sel_genbH",isLastbfromH,{"p4_GenPart","GenPart_pdgId","GenPart_genPartIdxMother","GenPart_statusFlags"})
//             .Define("bFromH_eta","GenPart_eta[sel_genbH]")
//             .Define("bFromH_phi","GenPart_phi[sel_genbH]");
//
//  _rlm  = _rlm.Define("sel_genbjH",isdR04,{"GenJet_eta","bFromH_eta","GenJet_phi","bFromH_phi"})
//              .Define("gJetFromH_pt","GenJet_pt[sel_genbjH]")
//              .Define("gJetFromH_eta","GenJet_eta[sel_genbjH]")
//              .Define("gJetFromH_phi","GenJet_phi[sel_genbjH]");
//
//  _rlm  = _rlm.Define("sel_bjetH",isJetFromgJet,{"Jet_pt","GenJet_pt","gJetFromH_pt","Jet_genJetIdx"})
//              .Define("JetFromH_pt","Jet_pt[sel_bjetH]")
//              .Define("JetFromH_eta","Jet_eta[sel_bjetH]")
//              .Define("JetFromH_phi","Jet_phi[sel_bjetH]")
//              .Define("nJetFromH","int(JetFromH_pt.size())");
//
//  _rlm = _rlm.Define("sel_genWq",isLastQfromW,{"p4_GenPart","GenPart_pdgId","GenPart_genPartIdxMother","GenPart_statusFlags"})
//             .Define("qFromW_eta","GenPart_eta[sel_genWq]")
//             .Define("qFromW_phi","GenPart_phi[sel_genWq]");
//
//  _rlm  = _rlm.Define("sel_genWj",isdR04,{"GenJet_eta","qFromW_eta","GenJet_phi","qFromW_phi"})
//              .Define("gJetFromW_pt","GenJet_pt[sel_genWj]")
//              .Define("gJetFromW_eta","GenJet_eta[sel_genWj]")
//              .Define("gJetFromW_phi","GenJet_phi[sel_genWj]");
//
//  _rlm  = _rlm.Define("sel_jetW",isJetFromgJet,{"Jet_pt","GenJet_pt","gJetFromW_pt","Jet_genJetIdx"})
//              .Define("JetFromW_pt","Jet_pt[sel_jetW]")
//              .Define("JetFromW_eta","Jet_eta[sel_jetW]")
//              .Define("JetFromW_phi","Jet_phi[sel_jetW]")
//              .Define("nJetFromW","int(JetFromW_pt.size())");
//
//  _rlm = _rlm.Define("sel_genqTop",isLastQfromTop,{"p4_GenPart","GenPart_pdgId","GenPart_genPartIdxMother","GenPart_statusFlags"})
//             .Define("qFromTop_eta","GenPart_eta[sel_genqTop]")
//             .Define("qFromTop_phi","GenPart_phi[sel_genqTop]");
//
//  _rlm  = _rlm.Define("sel_genjTop",isdR04,{"GenJet_eta","qFromTop_eta","GenJet_phi","qFromTop_phi"})
//              .Define("gJetFromTop_pt","GenJet_pt[sel_genjTop]")
//              .Define("gJetFromTop_eta","GenJet_eta[sel_genjTop]")
//              .Define("gJetFromTop_phi","GenJet_phi[sel_genjTop]");
//
//  _rlm  = _rlm.Define("sel_jetTop",isJetFromgJet,{"Jet_pt","GenJet_pt","gJetFromTop_pt","Jet_genJetIdx"})
//              .Define("JetFromTop_pt","Jet_pt[sel_jetTop]")
//              .Define("JetFromTop_eta","Jet_eta[sel_jetTop]")
//              .Define("JetFromTop_phi","Jet_phi[sel_jetTop]")
//              .Define("nJetFromTop","int(JetFromTop_pt.size())");
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
  
  //presel for overlap
  _rlm = _rlm.Define("pre_goodJets", "Jet_jetId > 1 && Jet_pt >= 30 && abs(Jet_eta) <= 4.5");
  
  _rlm = _rlm.Define("pre_nselJets","Sum(pre_goodJets)")
             .Define("pre_selJet_pt","Jet_pt[pre_goodJets]")
             .Define("pre_selJet_eta","Jet_eta[pre_goodJets]")
             .Define("pre_selJet_phi","Jet_phi[pre_goodJets]")
             .Define("pre_selJet_mass","Jet_mass[pre_goodJets]")
             .Define("pre_selJet_btagDeepFlavB","Jet_btagDeepFlavB[pre_goodJets]")
             .Define("pre_selJet_hadronFlavour", "Jet_hadronFlavour[pre_goodJets]")
             .Define("pre_jet4vecs", ::generate_4vec, {"pre_selJet_pt", "pre_selJet_eta", "pre_selJet_phi", "pre_selJet_mass"});
  
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
          //int out = mindr > 0.4 ? 1 : 0;
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
               .Define("selJet_hadronFlavour","pre_selJet_btagDeepFlavB[goodJets]")

               .Define("nselJets","int(selJet_pt.size())")
               .Define("nsel40Jets","int(selJet40_pt.size())")
               .Define("nsel80Jets","int(selJet80_pt.size())")
              
               .Define("jet4vecs", ::generate_4vec, {"selJet_pt", "selJet_eta", "selJet_phi", "selJet_mass"});

  //float WP_deepJet_T = 0;
  //float WP_deepJet_M = 0;
  //float WP_deepJet_L = 0;

  //if(_year==2015){        //2016preVFP - APV
  //     WP_deepJet_T = 0.6502;
  //     WP_deepJet_M = 0.2598;
  //     WP_deepJet_L = 0.0508;
  //}else if (_year==2016){ //postVFP
  //     WP_deepJet_T = 0.6377;
  //     WP_deepJet_M = 0.2489;
  //     WP_deepJet_L = 0.0480;  
  //}else if (_year==2017){
  //     WP_deepJet_T = 0.7476;
  //     WP_deepJet_M = 0.3040;
  //     WP_deepJet_L = 0.0532;
  //}else if(_year==2018){
  //     WP_deepJet_T = 0.7100;
  //     WP_deepJet_M = 0.2783;
  //     WP_deepJet_L = 0.0490;
  //}

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

  // for Chi2 reco
  _rlm = _rlm.Define("goodbJets", "goodJets && abs(pre_selJet_eta) < 2.5 && is_deepJet_L");
  //_rlm = _rlm.Define("goodbJets", "goodJets && abs(pre_selJet_eta) < 2.5 && is_deepJet_M");
  //_rlm = _rlm.Define("goodbJets", "goodJets && abs(pre_selJet_eta) < 2.5 && is_deepJet_T");

  _rlm = _rlm.Define("goodLbJets", "goodJets && abs(pre_selJet_eta) < 2.5 && is_deepJet_L");
  _rlm = _rlm.Define("goodMbJets", "goodJets && abs(pre_selJet_eta) < 2.5 && is_deepJet_M");
  _rlm = _rlm.Define("goodTbJets", "goodJets && abs(pre_selJet_eta) < 2.5 && is_deepJet_T");

  _rlm = _rlm.Define("selbJet_pt","pre_selJet_pt[goodbJets]")
             .Define("selbJet_eta","pre_selJet_eta[goodbJets]")
             .Define("selbJet_phi","pre_selJet_phi[goodbJets]")
             .Define("selbJet_mass","pre_selJet_mass[goodbJets]")
             .Define("selbJet_btag","pre_selJet_btagDeepFlavB[goodbJets]")
             .Define("selbJet_hadronFlavour","pre_selJet_hadronFlavour[goodbJets]")
             .Define("nselbJets","int(selbJet_pt.size())")
             .Define("bjet4vecs", ::generate_4vec, {"selbJet_pt", "selbJet_eta", "selbJet_phi", "selbJet_mass"});

  _rlm = _rlm.Define("selLbJet_pt","pre_selJet_pt[goodLbJets]")
             .Define("selLbJet_eta","pre_selJet_eta[goodLbJets]")
             .Define("selLbJet_phi","pre_selJet_phi[goodLbJets]")
             .Define("selLbJet_mass","pre_selJet_mass[goodLbJets]")
             .Define("selLbJet_btag","pre_selJet_btagDeepFlavB[goodLbJets]")
             .Define("selLbJet_hadronFlavour","pre_selJet_hadronFlavour[goodLbJets]")
             .Define("nselLbJets","int(selLbJet_pt.size())")
             .Define("Lbjet4vecs", ::generate_4vec, {"selLbJet_pt", "selLbJet_eta", "selLbJet_phi", "selLbJet_mass"});

  _rlm = _rlm.Define("selMbJet_pt","pre_selJet_pt[goodMbJets]")
             .Define("selMbJet_eta","pre_selJet_eta[goodMbJets]")
             .Define("selMbJet_phi","pre_selJet_phi[goodMbJets]")
             .Define("selMbJet_mass","pre_selJet_mass[goodMbJets]")
             .Define("selMbJet_btag","pre_selJet_btagDeepFlavB[goodMbJets]")
             .Define("selMbJet_hadronFlavour","pre_selJet_hadronFlavour[goodMbJets]")
             .Define("nselMbJets","int(selMbJet_pt.size())")
             .Define("Mbjet4vecs", ::generate_4vec, {"selMbJet_pt", "selMbJet_eta", "selMbJet_phi", "selMbJet_mass"});

  _rlm = _rlm.Define("selTbJet_pt","pre_selJet_pt[goodTbJets]")
             .Define("selTbJet_eta","pre_selJet_eta[goodTbJets]")
             .Define("selTbJet_phi","pre_selJet_phi[goodTbJets]")
             .Define("selTbJet_mass","pre_selJet_mass[goodTbJets]")
             .Define("selTbJet_btag","pre_selJet_btagDeepFlavB[goodTbJets]")
             .Define("selTbJet_hadronFlavour","pre_selJet_hadronFlavour[goodTbJets]")
             .Define("nselTbJets","int(selTbJet_pt.size())")
             .Define("Tbjet4vecs", ::generate_4vec, {"selTbJet_pt", "selTbJet_eta", "selTbJet_phi", "selTbJet_mass"});

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

//  _rlm = _rlm.Define("recob1_Higgs_cand_eta","(Chi2_Tprime[0] < 0) ? FLT_MIN : selbJet_eta[Chi2_Tprime[0]]")
//             .Define("recob1_Higgs_cand_phi","(Chi2_Tprime[0] < 0) ? FLT_MIN : selbJet_phi[Chi2_Tprime[0]]")
//             .Define("recob1_Higgs_cand_pt","(Chi2_Tprime[0] < 0) ? FLT_MIN : selbJet_pt[Chi2_Tprime[0]]")
//             .Define("recob2_Higgs_cand_eta","(Chi2_Tprime[1] < 0) ? FLT_MIN : selbJet_eta[Chi2_Tprime[1]]")
//             .Define("recob2_Higgs_cand_phi","(Chi2_Tprime[1] < 0) ? FLT_MIN : selbJet_phi[Chi2_Tprime[1]]")
//             .Define("recob2_Higgs_cand_pt","(Chi2_Tprime[1] < 0) ? FLT_MIN : selbJet_pt[Chi2_Tprime[1]]")
//
//             .Define("recoj1_W_cand_eta","(Chi2_Tprime[2] < 0) ? FLT_MIN : selJet_eta[Chi2_Tprime[2]]")
//             .Define("recoj1_W_cand_phi","(Chi2_Tprime[2] < 0) ? FLT_MIN : selJet_phi[Chi2_Tprime[2]]")
//             .Define("recoj1_W_cand_pt","(Chi2_Tprime[2] < 0) ? FLT_MIN : selJet_pt[Chi2_Tprime[2]]")
//
//             .Define("recoj2_W_cand_eta","(Chi2_Tprime[3] < 0) ? FLT_MIN : selJet_eta[Chi2_Tprime[3]]")
//             .Define("recoj2_W_cand_phi","(Chi2_Tprime[3] < 0) ? FLT_MIN : selJet_phi[Chi2_Tprime[3]]")
//             .Define("recoj2_W_cand_pt","(Chi2_Tprime[3] < 0) ? FLT_MIN : selJet_pt[Chi2_Tprime[3]]")
//
//             .Define("reco_bFromTop_cand_eta","(Chi2_Tprime[4] < 0) ? FLT_MIN : selbJet_eta[Chi2_Tprime[4]]")
//             .Define("reco_bFromTop_cand_phi","(Chi2_Tprime[4] < 0) ? FLT_MIN : selbJet_phi[Chi2_Tprime[4]]")
//             .Define("reco_bFromTop_cand_pt","(Chi2_Tprime[4] < 0) ? FLT_MIN : selbJet_pt[Chi2_Tprime[4]]")
//
//             .Define("reco_otherj_cand_eta","(Chi2_Tprime[5] < 0) ? FLT_MIN : selJet_eta[Chi2_Tprime[5]]")
//             .Define("reco_otherj_cand_phi","(Chi2_Tprime[5] < 0) ? FLT_MIN : selJet_phi[Chi2_Tprime[5]]")
//             .Define("reco_otherj_cand_pt","(Chi2_Tprime[5] < 0) ? FLT_MIN : selJet_pt[Chi2_Tprime[5]]");

//             //matching with gen Level
//  _rlm = _rlm.Define("chi2true_matched_Tprime",::count5s,{"JetFromTprime_eta","recob1_Higgs_cand_eta","recob2_Higgs_cand_eta","recoj1_W_cand_eta","recoj2_W_cand_eta","reco_otherj_cand_eta"})
//             .Define("chi2true_matched_H",::count2s,{"JetFromH_eta","recob1_Higgs_cand_eta","recob2_Higgs_cand_eta"})
//             .Define("chi2true_matched_Top",::count3s,{"JetFromTop_eta","recoj1_W_cand_eta","recoj2_W_cand_eta","reco_otherj_cand_eta"})
//             .Define("chi2true_matched_W",::count2s,{"JetFromW_eta","recoj1_W_cand_eta","recoj2_W_cand_eta"});

  // Kinematic reconstructions
  _rlm = _rlm.Define("invmass_leadjets", "(jet4vecs[0]+jet4vecs[1]+jet4vecs[2]+jet4vecs[3]+jet4vecs[4]).M()");

  _rlm = _rlm.Define("HT6","(selJet_pt[0]+selJet_pt[1]+selJet_pt[2]+selJet_pt[3]+selJet_pt[4]+selJet_pt[5])") 
             .Define("goodHT",::calculate_goodHT, {"selJet_pt"})
             .Define("RelHT",::calculate_RelHT, {"Top4vecs","Higgs4vecs","goodHT"})
             .Define("sixthJet_pt","selJet_pt[5]")
             .Define("newRelHT",::calculate_newRelHT, {"Top4vecs","Higgs4vecs","sixthJet_pt","goodHT"});

  _rlm = _rlm.Define("dRHbb_chi2","ROOT::VecOps::DeltaR(recob1_Higgs_cand_eta,recob2_Higgs_cand_eta,recob1_Higgs_cand_phi,recob2_Higgs_cand_phi)")
             .Define("dRWjj_chi2","ROOT::VecOps::DeltaR(recoj1_W_cand_eta,recoj2_W_cand_eta,recoj1_W_cand_phi,recoj2_W_cand_phi)")
             .Define("dRbW_chi2","ROOT::VecOps::DeltaR(recoW_cand_eta,reco_otherj_cand_eta,recoW_cand_phi,reco_otherj_cand_phi)"); 

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
    //if (!_isData && !isDefined("evWeight")){
    if (!_isData){
        std::cout <<"b tagging SF"<< std::endl;

        //auto btv_shape_central = [this](floats &pts, floats &etas, ints &hadflav, floats &btags)->floats
        //{
        //    return ::btv_shape_correction(_correction_btag1, _btvtype, "central", pts, etas, hadflav, btags); // defined in utility.cpp
        //};
        auto effMap_L_central = [this](ints &hadflav, floats &etas, floats &pts)->float
        {
            return ::btv_effMap(_efficiency_btag1, "L", hadflav, etas, pts); // defined in utility.cpp
        };

        auto btagSF_fixedWP_L_central = [this](ints &hadflav, floats &etas, floats &pts)->float
        {
            return ::btv_case1(_correction_btag1, _btvtype, "central", "central", "L", hadflav, etas, pts); // defined in utility.cpp
        };

        auto btagSF_fixedWP_M_central = [this](ints &hadflav, floats &etas, floats &pts)->float
        {
            return ::btv_case1(_correction_btag1, _btvtype, "central", "central", "M", hadflav, etas, pts); // defined in utility.cpp
        };

        auto btagSF_fixedWP_T_central = [this](ints &hadflav, floats &etas, floats &pts)->float
        {
            return ::btv_case1(_correction_btag1, _btvtype, "central", "central", "T", hadflav, etas, pts); // defined in utility.cpp
        };

        //_rlm = _rlm.Define("selbJet_deepJet_shape_central", btv_shape_central, {"selbJet_pt", "selbJet_eta", "selbJet_hadronFlavour", "selbJet_btag"});

//        _rlm = _rlm.Define("btagSF_deepJet_fixedL_central", btagSF_fixedWP_L_central, {"selLbJet_hadronFlavour", "selLbJet_eta", "selLbJet_pt"});
//        _rlm = _rlm.Define("btagSF_deepJet_fixedM_central", btagSF_fixedWP_M_central, {"selMbJet_hadronFlavour", "selMbJet_eta", "selMbJet_pt"});
//        _rlm = _rlm.Define("btagSF_deepJet_fixedT_central", btagSF_fixedWP_T_central, {"selTbJet_hadronFlavour", "selTbJet_eta", "selTbJet_pt"});

        // function to calculate event weight for MC events based on DeepJet algorithm
//        auto btagweightgenerator3= [this](floats &pts, floats &etas, ints &hadflav)->float
//        {
//            double bweight=1.0;
//            cout << "hi?" << endl;
//            for (unsigned int i=0; i<pts.size(); i++)
//            {
//              if (hadflav[i] != 4) continue;
//              cout << "jet " << i << "?" << endl;
//              double w = _correction_btag1->at("deepJet_mujet")->evaluate({"central", "T", int(hadflav[i]), fabs(float(etas[i])), float(pts[i])});
//              cout << "w? " << w << endl;
//              bweight *= w;
//            }
//            return bweight;
//        };
//
//        _rlm = _rlm.Define("btagWeight_DeepJetrecalc", btagweightgenerator3, {"selJetsForbtag_pt", "selJetsForbtag_eta", "selJetsForbtag_hadronFlavour"});

        auto btagWeight = [this](ints &hadflav, floats &etas, floats &pts, floats &discs, ints &wpL, ints &wpM, ints &wpT)->float
        {
//            return ::producer_btagWeight(_correction_btag1, _efficiency_btag1, _btvtype, "central", "central", hadflav, etas, pts, discs, wpL, wpM, wpT); // defined in utility.cpp
            return ::producer_btagWeight(_correction_btag1, _efficiency_btag1, _btvtype, "central", "central", hadflav, etas, pts, discs, wpL, wpM, wpT, _isTprime, _isTT, _isQCD); // defined in utility.cpp
        };

        _rlm = _rlm.Define("btagWeight", btagWeight, {"selJetsForbtag_hadronFlavour","selJetsForbtag_eta","selJetsForbtag_pt","selJetsForbtag_btag", "WP_deepJet_L", "WP_deepJet_M", "WP_deepJet_T"});

    }

    int _case = 1;
    std::vector<std::string> Jets_vars_names = {"selJetsForbtag_hadronFlavour", "selJetsForbtag_eta", "selJetsForbtag_pt", "selJetsForbtag_btag"};  
    if(_case !=1){
      Jets_vars_names.emplace_back("selJetsForbtag_btag");
    }

    //std::string output_btag_column_name = "btag_SF_";
    //_rlm = calculateBTagSF(_rlm, Jets_vars_names, _case, 0.0490, "L", output_btag_column_name);
    //_rlm = calculateBTagSF(_rlm, Jets_vars_names, _case, 0.2783, "M", output_btag_column_name);
    //_rlm = calculateBTagSF(_rlm, Jets_vars_names, _case, 0.7100, "T", output_btag_column_name);

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
    //_rlm = _rlm.Define("evWeight", "pugenWeight * L1PreFiringWeight_Nom");
    _rlm = _rlm.Define("evWeight", "pugenWeight");
    _rlm = _rlm.Define("evWeight_btag", "pugenWeight * btagWeight");
    _rlm = _rlm.Define("evWeight_btagL1", "pugenWeight * btagWeight * L1PreFiringWeight_Nom");

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
    //removeOverlaps();
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
                _rlm = _rlm.Define("corrmet_pt_"+sys+"Up", ::getmetsmear, {"corrmetjson_pt", "corrmet_phi", "Jet_pt_"+sys+"Up", "Jet_pt_smear_"+sys+"Up", "Jet_phi"});
                _rlm = _rlm.Define("corrmet_pt_"+sys+"Down", ::getmetsmear, {"corrmetjson_pt", "corrmet_phi", "Jet_pt_"+sys+"Down", "Jet_pt_smear_"+sys+"Down", "Jet_phi"});

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

void TprimeHadAnalyzer::setupJetMETCorrection(string fname, string jettag){
  
    cout << "setup JETMET correction" << endl;
    // read from file 
    _correction_jerc = correction::CorrectionSet::from_file(fname);//jercfname=json
    assert(_correction_jerc->validate()); //the assert functionality : check if the parameters passed to a function are valid =1:true
    // correction type(jobconfiganalysis.py)
    cout<<"json file=="<<fname<<endl;
    _jetCorrector = _correction_jerc->compound().at(jettag);//jerctag#JSON (JEC,compound)compoundLevel="L1L2L3Res"
    cout<<"jettag =="<<jettag<<endl;
    _jetCorrectionUnc = _correction_jerc->at(_jercunctag);
}

void TprimeHadAnalyzer::applyJetMETCorrections(){

    cout << "apply JETMET correction" << endl;
  
    auto appcorrlambdaf = [this](floats jetpts, floats jetetas, floats jetAreas, floats jetrawf, float rho)->floats
    {
        floats corrfactors;
        corrfactors.reserve(jetpts.size());
        for (unsigned int i =0; i<jetpts.size(); i++)
        {
            float rawjetpt = jetpts[i]*(1.0-jetrawf[i]);
            //std::cout<<"jetpt===="<< jetpts[i] <<std::endl;
            //float jet_rawmass = jet_mass * (1 - jet.rawFactor)
            //std::cout<<"rawjetpt===="<< rawjetpt <<std::endl;
            float corrfactor = _jetCorrector->evaluate({jetAreas[i], jetetas[i], rawjetpt, rho});
            //std::cout<<"correction factor===="<< corrfactor <<std::endl;
            corrfactors.emplace_back(rawjetpt * corrfactor);
            //std::cout<<"rawjetpt* corrfactor ===="<< rawjetpt * corrfactor <<std::endl;
  
        }
        //std::cout<<"Facsss===="<< corrfactors <<std::endl;
        return corrfactors;
      
    };
  
    auto jecuncertaintylambdaf= [this](floats jetpts, floats jetetas, floats jetAreas, floats jetrawf, float rho)->floats
      {
          floats uncertainties;
          uncertainties.reserve(jetpts.size());
          for (unsigned int i =0; i<jetpts.size(); i++){
                float rawjetpt = jetpts[i]*(1.0-jetrawf[i]);
                        
                float corrfactor = _jetCorrector->evaluate({jetAreas[i], jetetas[i], rawjetpt, rho});
                //print("\njet SF for shape correction:")
                //print(f"SF: {corrfactor}")
                        
                float unc = _jetCorrectionUnc->evaluate({corrfactor*rawjetpt, jetetas[i]});
                uncertainties.emplace_back(unc);
  
          }
          return uncertainties;
      };
  
    auto metcorrlambdaf = [](float met, float metphi, floats jetptsbefore, floats jetptsafter, floats jetphis)->float
    {
        auto metx = met * cos(metphi);
        auto mety = met * sin(metphi);
        for (unsigned int i=0; i<jetphis.size(); i++){
            if (jetptsafter[i]>15.0){
                metx -= (jetptsafter[i] - jetptsbefore[i])*cos(jetphis[i]);
                mety -= (jetptsafter[i] - jetptsbefore[i])*sin(jetphis[i]);
            }
        }
        return float(sqrt(metx*metx + mety*mety));
    };
  
    auto metphicorrlambdaf = [](float met, float metphi, floats jetptsbefore, floats jetptsafter, floats jetphis)->float
    {
        auto metx = met * cos(metphi);
        auto mety = met * sin(metphi);
        for (unsigned int i=0; i<jetphis.size(); i++){

            if (jetptsafter[i]>15.0){
                metx -= (jetptsafter[i] - jetptsbefore[i])*cos(jetphis[i]);
                mety -= (jetptsafter[i] - jetptsbefore[i])*sin(jetphis[i]);
            }
        }
        return float(atan2(mety, metx));
    };
  
    if (_jetCorrector != 0)
    {
          //cout << "jetcorrector==" <<_jetCorrector << endl;
  
      _rlm = _rlm.Define("Jet_pt_corr", appcorrlambdaf, {"Jet_pt", "Jet_eta", "Jet_area", "Jet_rawFactor", "fixedGridRhoFastjetAll"});
      _rlm = _rlm.Define("Jet_pt_relerror", jecuncertaintylambdaf, {"Jet_pt", "Jet_eta", "Jet_area", "Jet_rawFactor", "fixedGridRhoFastjetAll"});
      _rlm = _rlm.Define("Jet_pt_corr_up", "Jet_pt_corr*(1.0f + Jet_pt_relerror)");
      _rlm = _rlm.Define("Jet_pt_corr_down", "Jet_pt_corr*(1.0f - Jet_pt_relerror)");
      _rlm = _rlm.Define("MET_pt_corr", metcorrlambdaf, {"MET_pt", "MET_phi", "Jet_pt", "Jet_pt_corr", "Jet_phi"});
      _rlm = _rlm.Define("MET_phi_corr", metphicorrlambdaf, {"MET_pt", "MET_phi", "Jet_pt", "Jet_pt_corr", "Jet_phi"});
      _rlm = _rlm.Define("MET_pt_corr_up", metcorrlambdaf, {"MET_pt", "MET_phi", "Jet_pt", "Jet_pt_corr_up", "Jet_phi"});
      _rlm = _rlm.Define("MET_phi_corr_up", metphicorrlambdaf, {"MET_pt", "MET_phi", "Jet_pt", "Jet_pt_corr_up", "Jet_phi"});
      _rlm = _rlm.Define("MET_pt_corr_down", metcorrlambdaf, {"MET_pt", "MET_phi", "Jet_pt", "Jet_pt_corr_down", "Jet_phi"});
      _rlm = _rlm.Define("MET_phi_corr_down", metphicorrlambdaf, {"MET_pt", "MET_phi", "Jet_pt", "Jet_pt_corr_down", "Jet_phi"});
    }

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

        //auto getmetptmc=[this](float &pts, float &phis, int &npv, unsigned int &runnumber)->float
        //{
        //                if(pts > 0.0 && pts < 6500.0 && abs(phis) < 3.15){
        //            float w = _met_fname->at(_metptmctag)->evaluate({float(pts),float(phis), float(npv), float(runnumber)});
        //                        return w;
        //                }
        //                else{
        //                        return float(pts);
        //                }
        //                //return float(pts);
        //};

        //auto getmetphimc=[this](float &pts, float &phis, int &npv, unsigned int &runnumber)->float
        //{
        //                if(pts > 0.0 && pts < 6500.0 && abs(phis) < 3.15){
        //            float w = _met_fname->at(_metphimctag)->evaluate({float(pts),float(phis), float(npv), float(runnumber)});
        //                        return w;
        //                }
        //                else{
        //            return float(phis);
        //                }
        //         //       return float(phis);
        //};

        _rlm = _rlm.Define("JERCptResolution", getJERCptResolution, {"Jet_eta","Jet_pt","fixedGridRhoFastjetAll"});
        _rlm = _rlm.Define("JERCSF", getJERCSF, {"Jet_eta"});
        _rlm = _rlm.Define("GenMatchJetPtvars", ::GenMatchJetPt, {"Jet_pt", "Jet_eta", "Jet_phi", "Jet_mass", "GenJet_pt", "GenJet_eta", "GenJet_phi", "GenJet_mass", "JERCptResolution"});
        _rlm = _rlm.Define("c_JER", ::getcJER, {"Jet_pt", "GenMatchJetPtvars", "JERCSF", "JERCptResolution"});
        _rlm = _rlm.Define("Jet_pt_smear_nom", "c_JER*Jet_pt");
        //_rlm = _rlm.Define("corrmet_phi", getmetphimc, {"MET_pt", "MET_phi", "PV_npvs", "run"}); // this is the good one
        //_rlm = _rlm.Define("corrmetjson_pt", getmetptmc, {"MET_pt", "MET_phi", "PV_npvs", "run"}); // this is the good one

        _rlm = _rlm.Define("corrmet_pt_nom", ::getmetsmear, {"corrmetjson_pt", "corrmet_phi", "Jet_pt", "Jet_pt_smear_nom", "Jet_phi"}); // this is the good one

        _rlm = _rlm.Define("rawmet_pt", "MET_pt");
        _rlm = _rlm.Define("rawmet_phi", "MET_phi");

    }
    else{
                _rlm = _rlm.Define("MCorData", "1.0");
        _rlm = _rlm.Define("Jet_pt_smear_nom", "Jet_pt");
        _rlm = _rlm.Define("run_numbers", "float(run)");

        //if(_year == 2018){
        //    _rlm = _rlm.Define("corrmet_ptphi", ::calmetptphidata, {"MET_pt", "MET_phi", "PV_npvs", "run_numbers"})
        //        .Define("corrmet_pt_nom", "corrmet_ptphi[0]")
        //        .Define("corrmet_phi", "corrmet_ptphi[1]");
        //}
        //if(_year == 2017){
        //    _rlm = _rlm.Define("corrmet_ptphi", ::calmetptphidata17, {"MET_pt", "MET_phi", "PV_npvs", "run_numbers"})
        //        .Define("corrmet_pt_nom", "corrmet_ptphi[0]")
        //        .Define("corrmet_phi", "corrmet_ptphi[1]");
        //}
        //if(_year == 2016 && _runtype == "preVFP_UL"){
        //    _rlm = _rlm.Define("corrmet_ptphi", ::calmetptphidata16pre, {"MET_pt", "MET_phi", "PV_npvs", "run_numbers"})
        //        .Define("corrmet_pt_nom", "corrmet_ptphi[0]")
        //        .Define("corrmet_phi", "corrmet_ptphi[1]");
        //}
        //if(_year == 2016 && _runtype == "postVFP_UL"){
        //    _rlm = _rlm.Define("corrmet_ptphi", ::calmetptphidata16post, {"MET_pt", "MET_phi", "PV_npvs", "run_numbers"})
        //        .Define("corrmet_pt_nom", "corrmet_ptphi[0]")
        //        .Define("corrmet_phi_nom", "corrmet_ptphi[1]");
        //}
        _rlm = _rlm.Define("rawmet_pt", "MET_pt");
        _rlm = _rlm.Define("rawmet_phi", "MET_phi");
    }

    _rlm = _rlm.Define("goodJetsID", JetID(6)); //without pt-eta cuts
    //     _rlm = _rlm.Define("goodJets", "goodJetsID && Jet_pt_smear>30.0 && abs(Jet_eta)<2.5");
    _rlm = _rlm.Define("goodJets", "goodJetsID && Jet_pt_smear_nom>30.0 && abs(Jet_eta)<2.5");
    _rlm = _rlm.Define("goodJets_pt", "Jet_pt_smear_nom[goodJets]")
        .Define("goodJets_eta", "Jet_eta[goodJets]")
        .Define("goodJets_phi", "Jet_phi[goodJets]")
        .Define("goodJets_mass", "Jet_mass[goodJets]")
        .Define("goodJets_deepjetbtag", "Jet_btagDeepFlavB[goodJets]")
        .Define("NgoodJets", "int(goodJets_pt.size())")
        .Define("goodJetsHT_nom", "Sum(goodJets_pt)")
        .Define("goodJets_4vecs", ::generate_4vec, {"goodJets_pt", "goodJets_eta", "goodJets_phi", "goodJets_mass"});

    if(!_isData){

                auto getJERCSFup=[this](floats &etas)->floats
                {
                        return ::JERCSF(_jerc_fname, _jercSF_type,"up", etas);
                };

                auto getJERCSFdown=[this](floats &etas)->floats
                {
                        return ::JERCSF(_jerc_fname, _jercSF_type,"down", etas);
                };

        _rlm = _rlm.Define("goodJets_hadflav", "Jet_hadronFlavour[goodJets]");
                if(_jecsys == "Total"){ // HERE!
                auto getJECSFs = [this](floats &pts, floats &etas)->floats
                {
                        return ::getsysJERC(_jerc_fname, pts, etas, _jercsys_total);
                };
                _rlm = _rlm.Define("JecTotal",getJECSFs, {"Jet_pt","Jet_eta"});

                        GetJetsys("JecTotal");
                }

/*                if(_jecsys == "All"){
                {
                        return ::getsysJerc(_jerc_fname, pts, etas, JECAbsolute);
                };
                _rlm = _rlm.Define("JecAbsolute",getJECSFs, {"Jet_pt","Jet_eta"});
                        GetJetsys("JecAbsolute");
                }*/

                if(_jersys == "True"){
                        _rlm = _rlm.Define("JERCSFUp", getJERCSFup, {"Jet_eta"})
                                  .Define("JERCSFUp2Sig", "JERCSF+2*(JERCSFUp-JERCSF)");
                        _rlm = _rlm.Define("JERCSFDown", getJERCSFdown, {"Jet_eta"})
                                  .Define("JERCSFDown2Sig", "JERCSF+2*(JERCSFDown-JERCSF)");
                        _rlm = _rlm.Define("c_JERUp", ::getcJER, {"Jet_pt", "GenMatchJetPtvars", "JERCSFUp2Sig", "JERCptResolution"});
                        _rlm = _rlm.Define("c_JERDown", ::getcJER, {"Jet_pt", "GenMatchJetPtvars", "JERCSFDown2Sig", "JERCptResolution"});
//                        _rlm = _rlm.Define("c_JERUp", ::getcJER, {"Jet_pt", "GenMatchJetPtvars", "JERCSFUp", "JERCptResolution"});
//                        _rlm = _rlm.Define("c_JERDown", ::getcJER, {"Jet_pt", "GenMatchJetPtvars", "JERCSFDown", "JERCptResolution"});
                        _rlm = _rlm.Define("Jet_pt_smear_JERUp", "c_JERUp*Jet_pt");
                        _rlm = _rlm.Define("Jet_pt_smear_JERDown", "c_JERDown*Jet_pt");
                        _rlm = _rlm.Define("corrmet_pt_JERUp", ::getmetsmear, {"corrmetjson_pt", "corrmet_phi", "Jet_pt", "Jet_pt_smear_JERUp", "Jet_phi"});
                        _rlm = _rlm.Define("corrmet_pt_JERDown", ::getmetsmear, {"corrmetjson_pt", "corrmet_phi", "Jet_pt", "Jet_pt_smear_JERDown", "Jet_phi"});
                        _rlm = _rlm.Define("goodJets_JERUp", "goodJetsID && Jet_pt_smear_JERUp>30.0 && abs(Jet_eta)<2.5");
                        _rlm = _rlm.Define("goodJets_JERDown", "goodJetsID && Jet_pt_smear_JERDown>30.0 && abs(Jet_eta)<2.5");
                        _rlm = _rlm.Define("goodJets_pt_JERUp", "Jet_pt_smear_JERUp[goodJets_JERUp]")
                                .Define("goodJets_eta_JERUp", "Jet_eta[goodJets_JERUp]")
                                .Define("goodJets_phi_JERUp", "Jet_phi[goodJets_JERUp]")
                                .Define("goodJets_mass_JERUp", "Jet_mass[goodJets_JERUp]")
                                .Define("goodJets_deepjetbtag_JERUp", "Jet_btagDeepFlavB[goodJets_JERUp]")
                                .Define("goodJets_hadflav_JERUp", "Jet_hadronFlavour[goodJets_JERUp]")
                                .Define("NgoodJets_JERUp", "int(goodJets_pt_JERUp.size())")
                                .Define("goodJetsHT_JERUp", "Sum(goodJets_pt_JERUp)")
                                .Define("goodJets_4vecs_JERUp", ::generate_4vec, {"goodJets_pt_JERUp", "goodJets_eta_JERUp", "goodJets_phi_JERUp", "goodJets_mass_JERUp"});

                        _rlm = _rlm.Define("goodJets_pt_JERDown", "Jet_pt_smear_JERDown[goodJets_JERDown]")
                                .Define("goodJets_eta_JERDown", "Jet_eta[goodJets_JERDown]")
                                .Define("goodJets_phi_JERDown", "Jet_phi[goodJets_JERDown]")
                                .Define("goodJets_mass_JERDown", "Jet_mass[goodJets_JERDown]")
                                .Define("goodJets_deepjetbtag_JERDown", "Jet_btagDeepFlavB[goodJets_JERDown]")
                                .Define("goodJets_hadflav_JERDown", "Jet_hadronFlavour[goodJets_JERDown]")
                                .Define("NgoodJets_JERDown", "int(goodJets_pt_JERDown.size())")
                                .Define("goodJetsHT_JERDown", "Sum(goodJets_pt_JERDown)")
                                .Define("goodJets_4vecs_JERDown", ::generate_4vec, {"goodJets_pt_JERDown", "goodJets_eta_JERDown", "goodJets_phi_JERDown", "goodJets_mass_JERDown"});
                }

    }

  
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
    //if (_isData && !isDefined("evWeight"))
    //{
    //    _rlm = _rlm.Define("evWeight", [](){
    //        return 1.0;
    //    }, {} );
    //}
  
    //==========================================sum of gen weight==========================================//
    //   store sum of gen weight in outputtree. 
    //   PS:"genweight" stored in "Events" tree and "genEventSumw" stored in "Runs" tree in the inputfile
    //=====================================================================================================//

    if(!_isData){

        auto sumgenweight = _rd.Sum("genWeight");

        //cout<<"sum of gen weight "<< *sumgenweight <<endl;
        
        string sumofgenweight = Form("%f",*sumgenweight);

        _rlm = _rlm.Define("genEventSumw",sumofgenweight.c_str());

        //_rlm = _rlm.Define("genWeight","genWeight");
        std::cout<<"Not Data! Using genWeight"<<std::endl;
    }
    //

    //for correction define evWeights as fallows
    
    if  (_isData){
        _rlm = _rlm.Define("unitGenWeight","one")
                   .Define("pugenWeight","one"); // if setupcorrection in processnanoad.py then don't define here. 
        _rlm = _rlm.Define("evWeight","one");
    }
    //if (_isData && !isDefined("evWeight")){
 
    //    _rlm = _rlm.Define("evWeight", [](){
    //        return 1.0;
    //    }, {} );
    //}
    
  
    defineCuts();
    defineMoreVars();
    bookHists();
    setupCuts_and_Hists();
    setupTree();

}
