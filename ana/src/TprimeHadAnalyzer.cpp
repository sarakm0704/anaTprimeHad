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

//    if(_isTprime){
//        addCuts("isHadProcess","0");
//        addCuts("METfilter && HLT && nsel40Jets >= 6","00");
//    }else if(_isTT || _isQCD || _isData){
//    }else{
//        addCuts("METfilter && HLT","0");
//        addCuts("nsel40Jets >= 6","00");
//    }
//
//    addCuts("METfilter","0");
//    addCuts("nsel40Jets >= 6","00");
//    addCuts("selJet_pt[0] > 170 && selJet_pt[1] > 130 && selJet_pt[2] > 80 && goodHT > 500","000");
//
//    if(_is2M1L){
//        addCuts("nselMbJets == 2 && nselLbJets >= 3 && nselMbJets < 3","0000");
//    }else if(_is3L){
//        addCuts("nselLbJets >= 3","0000");
//    }else if(_is3M){
//        addCuts("nselMbJets >= 3 && nselTbJets < 3","0000");
//    }else if(_is3T){
//         addCuts("nselTbJets >= 3","0000");
//    }else{
//        cout << "no region defined, get efficiency Map" << endl;
//    }
//
//    // syst interval
////    int c = 0;
////    if(_jecsys == "True" || _jersys == "True") c == 1;
////    else if(_jecsys == "True" && _jersys == "True") c == 2;
//
//    if(_jecsys == "True"){
//
//        addCuts("METfilter && HLT && nsel40Jets_jecTotalUp >= 6","01");
//        addCuts("METfilter && HLT && nsel40Jets_jecTotalDn >= 6","02");
//
//        addCuts("selJet_pt_jecTotalUp[0] > 170 && selJet_pt_jecTotalUp[1] > 130 && selJet_pt_jecTotalUp[2] > 80 && goodHT_jecTotalUp > 500","010");
//        addCuts("selJet_pt_jecTotalDn[0] > 170 && selJet_pt_jecTotalDn[1] > 130 && selJet_pt_jecTotalDn[2] > 80 && goodHT_jecTotalDn > 500","021");
//
//        if(_is2M1L){
//            addCuts("nselMbJets_jecTotalUp == 2 && nselLbJets_jecTotalUp >= 3 && nselMbJets_jecTotalUp < 3","0100");
//            addCuts("nselMbJets_jecTotalDn == 2 && nselLbJets_jecTotalDn >= 3 && nselMbJets_jecTotalDn < 3","0211");
//        }else if(_is3L){
//            addCuts("nselLbJets_jecTotalUp >= 3","0100");
//            addCuts("nselLbJets_jecTotalDn >= 3","0211");
//        }else if(_is3M){
//            addCuts("nselMbJets_jecTotalUp >= 3 && nselTbJets_jecTotalUp < 3","0100");
//            addCuts("nselMbJets_jecTotalDn >= 3 && nselTbJets_jecTotalDn < 3","0211");
//        }else if(_is3T){
//             addCuts("nselTbJets_jecTotalUp >= 3","0100");
//             addCuts("nselTbJets_jecTotalDn >= 3","0211");
//        }else{
//            cout << "no region defined, get efficiency Map" << endl;
//        }
//
//    }
//
//    if(_jersys == "True"){
//
//        addCuts("METfilter && HLT && nsel40Jets_jerUp >= 6","03");
//        addCuts("METfilter && HLT && nsel40Jets_jerDn >= 6","04");
//
//        addCuts("selJet_pt_jerUp[0] > 170 && selJet_pt_jerUp[1] > 130 && selJet_pt_jerUp[2] > 80 && goodHT_jerUp > 500","032");
//        addCuts("selJet_pt_jerDn[0] > 170 && selJet_pt_jerDn[1] > 130 && selJet_pt_jerDn[2] > 80 && goodHT_jerDn > 500","043");
//
//        if(_is2M1L){
//            addCuts("nselMbJets_jerUp == 2 && nselLbJets_jerUp >= 3 && nselMbJets_jerUp < 3","0322");
//            addCuts("nselMbJets_jerDn == 2 && nselLbJets_jerDn >= 3 && nselMbJets_jerDn < 3","0433");
//        }else if(_is3L){
//            addCuts("nselLbJets_jerUp >= 3","0322");
//            addCuts("nselLbJets_jerDn >= 3","0433");
//        }else if(_is3M){
//            addCuts("nselMbJets_jerUp >= 3 && nselTbJets_jerUp < 3","0322");
//            addCuts("nselMbJets_jerDn >= 3 && nselTbJets_jerDn < 3","0433");
//        }else if(_is3T){
//             addCuts("nselTbJets_jerUp >= 3","0322");
//             addCuts("nselTbJets_jerDn >= 3","0433");
//        }else{
//            cout << "no region defined, get efficiency Map" << endl;
//        }
//
//    }

        addCuts("METfilter && HLT && nsel40Jets_jecTotalUp >= 6","0");
        addCuts("selJet_pt_jecTotalUp[0] > 170 && selJet_pt_jecTotalUp[1] > 130 && selJet_pt_jecTotalUp[2] > 80 && goodHT_jecTotalUp > 500","00");
        addCuts("nselTbJets_jecTotalUp >= 3","000");

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
//    if(_is2M1L || _is3L || _is3M || _is3T){ 
// 
//        cout << "add variables for NN training" << endl;
// 
//        addVar({"Chi2_min_H","Chi2_Tprime[7]",""});
//        addVar({"Chi2_min_W","Chi2_Tprime[8]",""});
//        addVar({"Chi2_min_Top","Chi2_Tprime[9]",""});
//  
//        addVar({"H_mass","Chi2_Tprime[10]",""});
//        addVar({"W_mass","Chi2_Tprime[11]",""});
//        addVar({"Top_mass","Chi2_Tprime[12]",""});
//
//        addVar({"invmass_2ndTop","Chi2_Tprime[13]",""});
//        addVar({"invmass_2ndW","Chi2_Tprime[14]",""});
//        addVar({"invmass_WH","Chi2_Tprime[15]",""});
//        addVar({"invmass_Tprime","Chi2_Tprime[16]",""});
//
//        addVar({"R_TopH","(Top_mass - H_mass) / (Top_mass + H_mass)",""});
//        addVar({"R_2ndTopW","(invmass_2ndTop + invmass_2ndW) / H_mass",""});
//
//        defineVar("mindR_bb",::mindR_bb,{"bjet4vecs"});
//        defineVar("dRbb",::dR_bb,{"bjet4vecs"});
//        defineVar("mbb",::m_bb,{"bjet4vecs"});
//        addVar({"mindR_dRbb","mindR_bb[0]",""});
//        addVar({"mindR_mbb","mindR_bb[1]",""});
//  
//        addVar({"selJet1_pt","selJet_pt[0]",""});
//        addVar({"selJet1_pt_massnom","selJet1_pt/invmass_Tprime",""});
//        addVar({"selJet1_pt_htnom","selJet1_pt/goodHT",""});
//        addVar({"selJet1_eta","selJet_eta[0]",""});
//        addVar({"selJet1_phi","selJet_phi[0]",""});
//        addVar({"selJet1_mass","selJet_mass[0]",""});
//        addVar({"selJet1_btag","selJet_btagDeepFlavB[0]",""});
//        addVar({"selJet1_e","jet4vecs[0].E()",""});
//        addVar({"selJet1_px","jet4vecs[0].Px()",""});
//        addVar({"selJet1_py","jet4vecs[0].Py()",""});
//        addVar({"selJet1_pz","jet4vecs[0].Pz()",""});
//        addVar({"selJet1_e_massnom","selJet1_e/invmass_Tprime",""});
//        addVar({"selJet1_e_htnom","selJet1_e/goodHT",""});
//  
//        addVar({"selJet2_pt","selJet_pt[1]",""});
//        addVar({"selJet2_pt_massnom","selJet2_pt/invmass_Tprime",""});
//        addVar({"selJet2_pt_htnom","selJet2_pt/goodHT",""});
//        addVar({"selJet2_eta","selJet_eta[1]",""});
//        addVar({"selJet2_phi","selJet_phi[1]",""});
//        addVar({"selJet2_mass","selJet_mass[1]",""});
//        addVar({"selJet2_btag","selJet_btagDeepFlavB[1]",""});
//        addVar({"selJet2_e","jet4vecs[1].E()",""});
//        addVar({"selJet2_px","jet4vecs[1].Px()",""});
//        addVar({"selJet2_py","jet4vecs[1].Py()",""});
//        addVar({"selJet2_pz","jet4vecs[1].Pz()",""});
//        addVar({"selJet2_e_massnom","selJet2_e/invmass_Tprime",""});
//        addVar({"selJet2_e_htnom","selJet2_e/goodHT",""});
//  
//        addVar({"selJet3_pt","selJet_pt[2]",""});
//        addVar({"selJet3_pt_massnom","selJet3_pt/invmass_Tprime",""});
//        addVar({"selJet3_pt_htnom","selJet3_pt/goodHT",""});
//        addVar({"selJet3_eta","selJet_eta[2]",""});
//        addVar({"selJet3_phi","selJet_phi[2]",""});
//        addVar({"selJet3_mass","selJet_mass[2]",""});
//        addVar({"selJet3_btag","selJet_btagDeepFlavB[2]",""});
//        addVar({"selJet3_e","jet4vecs[2].E()",""});
//        addVar({"selJet3_px","jet4vecs[2].Px()",""});
//        addVar({"selJet3_py","jet4vecs[2].Py()",""});
//        addVar({"selJet3_pz","jet4vecs[2].Pz()",""});
//        addVar({"selJet3_e_massnom","selJet3_e/invmass_Tprime",""});
//        addVar({"selJet3_e_htnom","selJet3_e/goodHT",""});
//  
//        addVar({"selJet4_pt","selJet_pt[3]",""});
//        addVar({"selJet4_pt_massnom","selJet4_pt/invmass_Tprime",""});
//        addVar({"selJet4_pt_htnom","selJet4_pt/goodHT",""});
//        addVar({"selJet4_eta","selJet_eta[3]",""});
//        addVar({"selJet4_phi","selJet_phi[3]",""});
//        addVar({"selJet4_mass","selJet_mass[3]",""});
//        addVar({"selJet4_btag","selJet_btagDeepFlavB[3]",""});
//        addVar({"selJet4_e","jet4vecs[3].E()",""});
//        addVar({"selJet4_px","jet4vecs[3].Px()",""});
//        addVar({"selJet4_py","jet4vecs[3].Py()",""});
//        addVar({"selJet4_pz","jet4vecs[3].Pz()",""});
//        addVar({"selJet4_e_massnom","selJet4_e/invmass_Tprime",""});
//        addVar({"selJet4_e_htnom","selJet4_e/goodHT",""});
//  
//        addVar({"selJet5_pt","selJet_pt[4]",""});
//        addVar({"selJet5_pt_massnom","selJet5_pt/invmass_Tprime",""});
//        addVar({"selJet5_pt_htnom","selJet5_pt/goodHT",""});
//        addVar({"selJet5_eta","selJet_eta[4]",""});
//        addVar({"selJet5_phi","selJet_phi[4]",""});
//        addVar({"selJet5_mass","selJet_mass[4]",""});
//        addVar({"selJet5_btag","selJet_btagDeepFlavB[4]",""});
//        addVar({"selJet5_e","jet4vecs[4].E()",""});
//        addVar({"selJet5_px","jet4vecs[4].Px()",""});
//        addVar({"selJet5_py","jet4vecs[4].Py()",""});
//        addVar({"selJet5_pz","jet4vecs[4].Pz()",""});
//        addVar({"selJet5_e_massnom","selJet5_e/invmass_Tprime",""});
//        addVar({"selJet5_e_htnom","selJet5_e/goodHT",""});
//  
//        addVar({"selbJet1_pt","selbJet_pt[0]",""});
//        addVar({"selbJet1_pt_massnom","selbJet1_pt/invmass_Tprime",""});
//        addVar({"selbJet1_pt_htnom","selbJet1_pt/goodHT",""});
//        addVar({"selbJet1_eta","selbJet_eta[0]",""});
//        addVar({"selbJet1_phi","selbJet_phi[0]",""});
//        addVar({"selbJet1_mass","selbJet_mass[0]",""});
//        addVar({"selbJet1_btag","selbJet_btag[0]",""});
//        addVar({"selbJet1_e","bjet4vecs[0].E()",""});
//        addVar({"selbJet1_px","bjet4vecs[0].Px()",""});
//        addVar({"selbJet1_py","bjet4vecs[0].Py()",""});
//        addVar({"selbJet1_pz","bjet4vecs[0].Pz()",""});
//        addVar({"selbJet1_e_massnom","selbJet1_e/invmass_Tprime",""});
//        addVar({"selbJet1_e_htnom","selbJet1_e/goodHT",""});
//  
//        addVar({"selbJet2_pt","selbJet_pt[1]",""});
//        addVar({"selbJet2_pt_massnom","selbJet2_pt/invmass_Tprime",""});
//        addVar({"selbJet2_pt_htnom","selbJet2_pt/goodHT",""});
//        addVar({"selbJet2_eta","selbJet_eta[1]",""});
//        addVar({"selbJet2_phi","selbJet_phi[1]",""});
//        addVar({"selbJet2_mass","selbJet_mass[1]",""});
//        addVar({"selbJet2_btag","selbJet_btag[1]",""});
//        addVar({"selbJet2_e","bjet4vecs[1].E()",""});
//        addVar({"selbJet2_px","bjet4vecs[1].Px()",""});
//        addVar({"selbJet2_py","bjet4vecs[1].Py()",""});
//        addVar({"selbJet2_pz","bjet4vecs[1].Pz()",""});
//        addVar({"selbJet2_e_massnom","selbJet2_e/invmass_Tprime",""});
//        addVar({"selbJet2_e_htnom","selbJet2_e/goodHT",""});
//  
//        addVar({"goodHT_massnom","goodHT/invmass_Tprime",""});
//        addVar({"invmass_htnom","invmass_Tprime/goodHT",""});
//    }
//  
//    //================================Store variables in tree=======================================//
//    // define variables that you want to store
//    //==============================================================================================//
//    //addVartoStore("nJetFromW");
//    //addVartoStore("nJetFromTop");
//    //addVartoStore("nJetFromH");
//
//    addVartoStore("run");
//    addVartoStore("luminosityBlock");
//    addVartoStore("event");
//    addVartoStore("evWeight.*");
//    //addVartoStore("evWeight");
//
//    addVartoStore("genWeight");
//    addVartoStore("genEventSumw");
//
//    if(_year==2018){
//        addVartoStore("HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2");
//        addVartoStore("HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepCSV_4p5");
//        addVartoStore("HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5");
//        addVartoStore("HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5");
//        addVartoStore("HLT_PFHT1050");
//        addVartoStore("HLT_PFJet500");
//        addVartoStore("HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94");
//        addVartoStore("HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59");
//    }else if(_year == 2017){
//        addVartoStore("HLT_HT300PT30_QuadJet_75_60_45_40_TripleCSV_p07");
//        addVartoStore("HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0");
//        addVartoStore("HLT_PFHT380_SixJet32_DoubleBTagCSV_p075");
//        addVartoStore("HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2");
//        addVartoStore("HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2");
//        addVartoStore("HLT_PFHT430_SixJet40_BTagCSV_p080");
//        addVartoStore("HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5");
//        addVartoStore("HLT_PFHT1050");
//        addVartoStore("HLT_PFJet500");
//    }else if(_year == 2015 || _year == 2016){
//        addVartoStore("HLT_PFHT400_SixJet30_DoubleBTagCSV_p056");
//        addVartoStore("HLT_PFHT450_SixJet40_BTagCSV_p056");
//        addVartoStore("HLT_PFHT900");
//        addVartoStore("HLT_PFHT750_4JetPt70");
//        addVartoStore("HLT_PFHT750_4JetPt80");
//        addVartoStore("HLT_PFHT800_4JetPt50");
//        addVartoStore("HLT_PFHT850_4JetPt50");
//        addVartoStore("HLT_PFJet500");
//    }
//
//    addVartoStore("HLT_IsoMu24"); 
//    addVartoStore("HLT_Mu50"); 
//    addVartoStore("nMuons"); 
//  
//    if(!_is2M1L && !_is3L && !_is3M && !_is3T){ 
//
//        cout << "store variables for b-tagging effMap" << endl;
//    
//        addVartoStore("selJetsForbtag_pt");
//        addVartoStore("selJetsForbtag_eta");
//        addVartoStore("selJetsForbtag_phi");
//        addVartoStore("selJetsForbtag_mass");
//        addVartoStore("selJetsForbtag_btag");
//        addVartoStore("selJetsForbtag_hadronFlavour");
//        addVartoStore("nselJetsForbtag");
//
//    }else{
//
////        cout << "store variables for TF" << endl;
//////        // for TF
////        addVartoStore("jet4vecs");
////        addVartoStore("numJets4vecs");
////        addVartoStore("denJets4vecs");
////        addVartoStore("numJets_pt");
////        addVartoStore("numJets_eta");
////        addVartoStore("denJets_pt");
////        addVartoStore("denJets_eta");
//
//        cout << "store variables for NN training" << endl;
//
//        // DNN Study
//        // Cut0
//        addVartoStore("nselJets");
//        addVartoStore("nselbJets");
//        addVartoStore("nselLbJets");
//        addVartoStore("nselMbJets");
//        addVartoStore("nselTbJets");
//
//
//        // btag in binary
//        addVartoStore("is_deepJet_T");
//        addVartoStore("is_deepJet_M");
//        addVartoStore("is_deepJet_L");
//
//        addVartoStore("selJet1_pt");
//        addVartoStore("selJet1_pt_massnom");
//        addVartoStore("selJet1_eta");
//        addVartoStore("selJet1_phi");
//        addVartoStore("selJet1_e");
//        addVartoStore("selJet1_e_massnom");
//        addVartoStore("selJet1_btag");
//
//        addVartoStore("selJet2_pt");
//        addVartoStore("selJet2_pt_massnom");
//        addVartoStore("selJet2_eta");
//        addVartoStore("selJet2_phi");
//        addVartoStore("selJet2_e");
//        addVartoStore("selJet2_e_massnom");
//        addVartoStore("selJet2_btag");
//
//        addVartoStore("selJet3_pt");
//        addVartoStore("selJet3_pt_massnom");
//        addVartoStore("selJet3_eta");
//        addVartoStore("selJet3_phi");
//        addVartoStore("selJet3_e");
//        addVartoStore("selJet3_e_massnom");
//        addVartoStore("selJet3_btag");
//
//        addVartoStore("selJet4_pt");
//        addVartoStore("selJet4_pt_massnom");
//        addVartoStore("selJet4_eta");
//        addVartoStore("selJet4_phi");
//        addVartoStore("selJet4_e");
//        addVartoStore("selJet4_e_massnom");
//        addVartoStore("selJet4_btag");
//
//        addVartoStore("selJet5_pt");
//        addVartoStore("selJet5_pt_massnom");
//        addVartoStore("selJet5_eta");
//        addVartoStore("selJet5_phi");
//        addVartoStore("selJet5_e");
//        addVartoStore("selJet5_e_massnom");
//        addVartoStore("selJet5_btag");
//
//        addVartoStore("selbJet1_pt");
//        addVartoStore("selbJet1_pt_massnom");
//        addVartoStore("selbJet1_eta");
//        addVartoStore("selbJet1_phi");
//        addVartoStore("selbJet1_e");
//        addVartoStore("selbJet1_e_massnom");
//        addVartoStore("selbJet1_btag");
//
//        addVartoStore("selbJet2_pt");
//        addVartoStore("selbJet2_pt_massnom");
//        addVartoStore("selbJet2_eta");
//        addVartoStore("selbJet2_phi");
//        addVartoStore("selbJet2_e");
//        addVartoStore("selbJet2_e_massnom");
//        addVartoStore("selbJet2_btag");
//
//        addVartoStore("Chi2_min");
//        addVartoStore("goodHT");
//        addVartoStore("invmass_2ndTop");
//        addVartoStore("H_mass");
//
//        addVartoStore("RelHT");          // Cut 1
//        addVartoStore("Chi2_max");       // Cut 2
//        addVartoStore("dRHbb_chi2");     // Cut 3
//        addVartoStore("Chi2_min_H");     // Cut 4
//        addVartoStore("dRWjj_chi2");     // Cut 5
//        addVartoStore("dRbW_chi2");      // Cut 6
//
//        // Candidates
//        addVartoStore("Chi2_min_W");
//        addVartoStore("Chi2_min_Top");
//        addVartoStore("mindR_dRbb");
//        addVartoStore("mindR_mbb");
//        addVartoStore("Top_mass");
//        addVartoStore("W_mass");
//        addVartoStore("invmass_WH");
//        addVartoStore("invmass_Tprime");
//        addVartoStore("invmass_leadjets");//etc
//        addVartoStore("R_TopH");
//        addVartoStore("R_2ndTopW");
//        addVartoStore("newRelHT");
//        addVartoStore("dRTprimeoj_chi2");
//        addVartoStore("dRHTop_chi2");
//        addVartoStore("dEtaWH_chi2");
//        addVartoStore("dPhiHTop_chi2");
//        addVartoStore("Rpt_Top2ndTop");
//        addVartoStore("Rpt_HTopTprime");
//        addVartoStore("Rpt_TprimeHTprimeTop");
//
    if(_jecsys == "Total"){
        // DNN Study
        addVartoStore("nselJets_jecTotalUp");
        addVartoStore("nselbJets_jecTotalUp");
        addVartoStore("nselLbJets_jecTotalUp");
        addVartoStore("nselMbJets_jecTotalUp");
        addVartoStore("nselTbJets_jecTotalUp");
    
        addVartoStore("is_deepJet_T_jecTotalUp");
        addVartoStore("is_deepJet_M_jecTotalUp");
        addVartoStore("is_deepJet_L_jecTotalUp");
    
        addVartoStore("selJet1_pt_jecTotalUp");
        addVartoStore("selJet1_pt_massnom_jecTotalUp");
        addVartoStore("selJet1_eta_jecTotalUp");
        addVartoStore("selJet1_phi_jecTotalUp");
        addVartoStore("selJet1_e_jecTotalUp");
        addVartoStore("selJet1_e_massnom_jecTotalUp");
        addVartoStore("selJet1_btag_jecTotalUp");
    
        addVartoStore("selJet2_pt_jecTotalUp");
        addVartoStore("selJet2_pt_massnom_jecTotalUp");
        addVartoStore("selJet2_eta_jecTotalUp");
        addVartoStore("selJet2_phi_jecTotalUp");
        addVartoStore("selJet2_e_jecTotalUp");
        addVartoStore("selJet2_e_massnom_jecTotalUp");
        addVartoStore("selJet2_btag_jecTotalUp");
    
        addVartoStore("selJet3_pt_jecTotalUp");
        addVartoStore("selJet3_pt_massnom_jecTotalUp");
        addVartoStore("selJet3_eta_jecTotalUp");
        addVartoStore("selJet3_phi_jecTotalUp");
        addVartoStore("selJet3_e_jecTotalUp");
        addVartoStore("selJet3_e_massnom_jecTotalUp");
        addVartoStore("selJet3_btag_jecTotalUp");
    
        addVartoStore("selJet4_pt_jecTotalUp");
        addVartoStore("selJet4_pt_massnom_jecTotalUp");
        addVartoStore("selJet4_eta_jecTotalUp");
        addVartoStore("selJet4_phi_jecTotalUp");
        addVartoStore("selJet4_e_jecTotalUp");
        addVartoStore("selJet4_e_massnom_jecTotalUp");
        addVartoStore("selJet4_btag_jecTotalUp");
    
        addVartoStore("selJet5_pt_jecTotalUp");
        addVartoStore("selJet5_pt_massnom_jecTotalUp");
        addVartoStore("selJet5_eta_jecTotalUp");
        addVartoStore("selJet5_phi_jecTotalUp");
        addVartoStore("selJet5_e_jecTotalUp");
        addVartoStore("selJet5_e_massnom_jecTotalUp");
        addVartoStore("selJet5_btag_jecTotalUp");
    
        addVartoStore("selbJet1_pt_jecTotalUp");
        addVartoStore("selbJet1_pt_massnom_jecTotalUp");
        addVartoStore("selbJet1_eta_jecTotalUp");
        addVartoStore("selbJet1_phi_jecTotalUp");
        addVartoStore("selbJet1_e_jecTotalUp");
        addVartoStore("selbJet1_e_massnom_jecTotalUp");
        addVartoStore("selbJet1_btag_jecTotalUp");
    
        addVartoStore("selbJet2_pt_jecTotalUp");
        addVartoStore("selbJet2_pt_massnom_jecTotalUp");
        addVartoStore("selbJet2_eta_jecTotalUp");
        addVartoStore("selbJet2_phi_jecTotalUp");
        addVartoStore("selbJet2_e_jecTotalUp");
        addVartoStore("selbJet2_e_massnom_jecTotalUp");
        addVartoStore("selbJet2_btag_jecTotalUp");
    
        addVartoStore("Chi2_min_jecTotalUp");
        addVartoStore("goodHT_jecTotalUp");
        addVartoStore("invmass_2ndTop_jecTotalUp");
        addVartoStore("H_mass_jecTotalUp");
    
        addVartoStore("RelHT_jecTotalUp");          // Cut 1
        addVartoStore("Chi2_max_jecTotalUp");       // Cut 2
        addVartoStore("dRHbb_chi2_jecTotalUp");     // Cut 3
        addVartoStore("Chi2_min_H_jecTotalUp");     // Cut 4
        addVartoStore("dRWjj_chi2_jecTotalUp");     // Cut 5
        addVartoStore("dRbW_chi2_jecTotalUp");      // Cut 6
    
        // Candidates
        addVartoStore("Chi2_min_W_jecTotalUp");
        addVartoStore("Chi2_min_Top_jecTotalUp");
        addVartoStore("mindR_dRbb_jecTotalUp");
        addVartoStore("mindR_mbb_jecTotalUp");
        addVartoStore("Top_mass_jecTotalUp");
        addVartoStore("W_mass_jecTotalUp");
        addVartoStore("invmass_WH_jecTotalUp");
        addVartoStore("invmass_Tprime_jecTotalUp");
        addVartoStore("invmass_leadjets_jecTotalUp");//etc
        addVartoStore("R_TopH_jecTotalUp");
        addVartoStore("R_2ndTopW_jecTotalUp");
        addVartoStore("newRelHT_jecTotalUp");
        addVartoStore("dRTprimeoj_chi2_jecTotalUp");
        addVartoStore("dRHTop_chi2_jecTotalUp");
        addVartoStore("Rpt_Top2ndTop_jecTotalUp");
        addVartoStore("Rpt_HTopTprime_jecTotalUp");
        addVartoStore("Rpt_TprimeHTprimeTop_jecTotalUp");

    //    addVartoStore("nselJets_jecTotalDown");
    //    addVartoStore("nselbJets_jecTotalDown");
    //    addVartoStore("nselLbJets_jecTotalDown");
    //    addVartoStore("nselMbJets_jecTotalDown");
    //    addVartoStore("nselTbJets_jecTotalDown");
    //
    //    addVartoStore("is_deepJet_T_jecTotalDown");
    //    addVartoStore("is_deepJet_M_jecTotalDown");
    //    addVartoStore("is_deepJet_L_jecTotalDown");
    //
    //    addVartoStore("selJet1_pt_jecTotalDown");
    //    addVartoStore("selJet1_pt_massnom_jecTotalDown");
    //    addVartoStore("selJet1_eta_jecTotalDown");
    //    addVartoStore("selJet1_phi_jecTotalDown");
    //    addVartoStore("selJet1_e_jecTotalDown");
    //    addVartoStore("selJet1_e_massnom_jecTotalDown");
    //    addVartoStore("selJet1_btag_jecTotalDown");
    //
    //    addVartoStore("selJet2_pt_jecTotalDown");
    //    addVartoStore("selJet2_pt_massnom_jecTotalDown");
    //    addVartoStore("selJet2_eta_jecTotalDown");
    //    addVartoStore("selJet2_phi_jecTotalDown");
    //    addVartoStore("selJet2_e_jecTotalDown");
    //    addVartoStore("selJet2_e_massnom_jecTotalDown");
    //    addVartoStore("selJet2_btag_jecTotalDown");
    //
    //    addVartoStore("selJet3_pt_jecTotalDown");
    //    addVartoStore("selJet3_pt_massnom_jecTotalDown");
    //    addVartoStore("selJet3_eta_jecTotalDown");
    //    addVartoStore("selJet3_phi_jecTotalDown");
    //    addVartoStore("selJet3_e_jecTotalDown");
    //    addVartoStore("selJet3_e_massnom_jecTotalDown");
    //    addVartoStore("selJet3_btag_jecTotalDown");
    //
    //    addVartoStore("selJet4_pt_jecTotalDown");
    //    addVartoStore("selJet4_pt_massnom_jecTotalDown");
    //    addVartoStore("selJet4_eta_jecTotalDown");
    //    addVartoStore("selJet4_phi_jecTotalDown");
    //    addVartoStore("selJet4_e_jecTotalDown");
    //    addVartoStore("selJet4_e_massnom_jecTotalDown");
    //    addVartoStore("selJet4_btag_jecTotalDown");
    //
    //    addVartoStore("selJet5_pt_jecTotalDown");
    //    addVartoStore("selJet5_pt_massnom_jecTotalDown");
    //    addVartoStore("selJet5_eta_jecTotalDown");
    //    addVartoStore("selJet5_phi_jecTotalDown");
    //    addVartoStore("selJet5_e_jecTotalDown");
    //    addVartoStore("selJet5_e_massnom_jecTotalDown");
    //    addVartoStore("selJet5_btag_jecTotalDown");
    //
    //    addVartoStore("selbJet1_pt_jecTotalDown");
    //    addVartoStore("selbJet1_pt_massnom_jecTotalDown");
    //    addVartoStore("selbJet1_eta_jecTotalDown");
    //    addVartoStore("selbJet1_phi_jecTotalDown");
    //    addVartoStore("selbJet1_e_jecTotalDown");
    //    addVartoStore("selbJet1_e_massnom_jecTotalDown");
    //    addVartoStore("selbJet1_btag_jecTotalDown");
    //
    //    addVartoStore("selbJet2_pt_jecTotalDown");
    //    addVartoStore("selbJet2_pt_massnom_jecTotalDown");
    //    addVartoStore("selbJet2_eta_jecTotalDown");
    //    addVartoStore("selbJet2_phi_jecTotalDown");
    //    addVartoStore("selbJet2_e_jecTotalDown");
    //    addVartoStore("selbJet2_e_massnom_jecTotalDown");
    //    addVartoStore("selbJet2_btag_jecTotalDown");
    //
    //    addVartoStore("Chi2_min_jecTotalDown");
    //    addVartoStore("goodHT_jecTotalDown");
    //    addVartoStore("invmass_2ndTop_jecTotalDown");
    //    addVartoStore("H_mass_jecTotalDown");
    //
    //    addVartoStore("RelHT_jecTotalDown");          // Cut 1
    //    addVartoStore("Chi2_max_jecTotalDown");       // Cut 2
    //    addVartoStore("dRHbb_chi2_jecTotalDown");     // Cut 3
    //    addVartoStore("Chi2_min_H_jecTotalDown");     // Cut 4
    //    addVartoStore("dRWjj_chi2_jecTotalDown");     // Cut 5
    //    addVartoStore("dRbW_chi2_jecTotalDown");      // Cut 6
    //
    //    // Candidates
    //    addVartoStore("Chi2_min_W_jecTotalDown");
    //    addVartoStore("Chi2_min_Top_jecTotalDown");
    //    addVartoStore("mindR_dRbb_jecTotalDown");
    //    addVartoStore("mindR_mbb_jecTotalDown");
    //    addVartoStore("Top_mass_jecTotalDown");
    //    addVartoStore("W_mass_jecTotalDown");
    //    addVartoStore("invmass_WH_jecTotalDown");
    //    addVartoStore("invmass_Tprime_jecTotalDown");
    //    addVartoStore("invmass_leadjets_jecTotalDown");//etc
    //    addVartoStore("R_TopH_jecTotalDown");
    //    addVartoStore("R_2ndTopW_jecTotalDown");
    //    addVartoStore("newRelHT_jecTotalDown");
    //    addVartoStore("dRTprimeoj_chi2_jecTotalDown");
    //    addVartoStore("dRHTop_chi2_jecTotalDown");
    //    addVartoStore("Rpt_Top2ndTop_jecTotalDown");
    //    addVartoStore("Rpt_HTopTprime_jecTotalDown");
    //    addVartoStore("Rpt_TprimeHTprimeTop_jecTotalDown");
    }

    //if(_jersys == "True"){

    //    // DNN Study
    //    addVartoStore("nselJets_jerUp");
    //    addVartoStore("nselbJets_jerUp");
    //    addVartoStore("nselLbJets_jerUp");
    //    addVartoStore("nselMbJets_jerUp");
    //    addVartoStore("nselTbJets_jerUp");
    //
    //    // btag in binary
    //    addVartoStore("is_deepJet_T_jerUp");
    //    addVartoStore("is_deepJet_M_jerUp");
    //    addVartoStore("is_deepJet_L_jerUp");
    //
    //    addVartoStore("selJet1_pt_jerUp");
    //    addVartoStore("selJet1_pt_massnom_jerUp");
    //    addVartoStore("selJet1_eta_jerUp");
    //    addVartoStore("selJet1_phi_jerUp");
    //    addVartoStore("selJet1_e_jerUp");
    //    addVartoStore("selJet1_e_massnom_jerUp");
    //    addVartoStore("selJet1_btag_jerUp");
    //
    //    addVartoStore("selJet2_pt_jerUp");
    //    addVartoStore("selJet2_pt_massnom_jerUp");
    //    addVartoStore("selJet2_eta_jerUp");
    //    addVartoStore("selJet2_phi_jerUp");
    //    addVartoStore("selJet2_e_jerUp");
    //    addVartoStore("selJet2_e_massnom_jerUp");
    //    addVartoStore("selJet2_btag_jerUp");
    //
    //    addVartoStore("selJet3_pt_jerUp");
    //    addVartoStore("selJet3_pt_massnom_jerUp");
    //    addVartoStore("selJet3_eta_jerUp");
    //    addVartoStore("selJet3_phi_jerUp");
    //    addVartoStore("selJet3_e_jerUp");
    //    addVartoStore("selJet3_e_massnom_jerUp");
    //    addVartoStore("selJet3_btag_jerUp");
    //
    //    addVartoStore("selJet4_pt_jerUp");
    //    addVartoStore("selJet4_pt_massnom_jerUp");
    //    addVartoStore("selJet4_eta_jerUp");
    //    addVartoStore("selJet4_phi_jerUp");
    //    addVartoStore("selJet4_e_jerUp");
    //    addVartoStore("selJet4_e_massnom_jerUp");
    //    addVartoStore("selJet4_btag_jerUp");
    //
    //    addVartoStore("selJet5_pt_jerUp");
    //    addVartoStore("selJet5_pt_massnom_jerUp");
    //    addVartoStore("selJet5_eta_jerUp");
    //    addVartoStore("selJet5_phi_jerUp");
    //    addVartoStore("selJet5_e_jerUp");
    //    addVartoStore("selJet5_e_massnom_jerUp");
    //    addVartoStore("selJet5_btag_jerUp");
    //
    //    addVartoStore("selbJet1_pt_jerUp");
    //    addVartoStore("selbJet1_pt_massnom_jerUp");
    //    addVartoStore("selbJet1_eta_jerUp");
    //    addVartoStore("selbJet1_phi_jerUp");
    //    addVartoStore("selbJet1_e_jerUp");
    //    addVartoStore("selbJet1_e_massnom_jerUp");
    //    addVartoStore("selbJet1_btag_jerUp");
    //
    //    addVartoStore("selbJet2_pt_jerUp");
    //    addVartoStore("selbJet2_pt_massnom_jerUp");
    //    addVartoStore("selbJet2_eta_jerUp");
    //    addVartoStore("selbJet2_phi_jerUp");
    //    addVartoStore("selbJet2_e_jerUp");
    //    addVartoStore("selbJet2_e_massnom_jerUp");
    //    addVartoStore("selbJet2_btag_jerUp");
    //
    //    addVartoStore("Chi2_min_jerUp");
    //    addVartoStore("goodHT_jerUp");
    //    addVartoStore("invmass_2ndTop_jerUp");
    //    addVartoStore("H_mass_jerUp");

    //    addVartoStore("RelHT_jerUp");          // Cut 1
    //    addVartoStore("Chi2_max_jerUp");       // Cut 2
    //    addVartoStore("dRHbb_chi2_jerUp");     // Cut 3
    //    addVartoStore("Chi2_min_H_jerUp");     // Cut 4
    //    addVartoStore("dRWjj_chi2_jerUp");     // Cut 5
    //    addVartoStore("dRbW_chi2_jerUp");      // Cut 6

    //    // Candidates
    //    addVartoStore("Chi2_min_W_jerUp");
    //    addVartoStore("Chi2_min_Top_jerUp");
    //    addVartoStore("mindR_dRbb_jerUp");
    //    addVartoStore("mindR_mbb_jerUp");
    //    addVartoStore("Top_mass_jerUp");
    //    addVartoStore("W_mass_jerUp");
    //    addVartoStore("invmass_WH_jerUp");
    //    addVartoStore("invmass_Tprime_jerUp");
    //    addVartoStore("invmass_leadjets_jerUp");//etc
    //    addVartoStore("R_TopH_jerUp");
    //    addVartoStore("R_2ndTopW_jerUp");
    //    addVartoStore("newRelHT_jerUp");
    //    addVartoStore("dRTprimeoj_chi2_jerUp");
    //    addVartoStore("dRHTop_chi2_jerUp");
    //    addVartoStore("Rpt_Top2ndTop_jerUp");
    //    addVartoStore("Rpt_HTopTprime_jerUp");
    //    addVartoStore("Rpt_TprimeHTprimeTop_jerUp");

    //    addVartoStore("nselJets_jerDown");
    //    addVartoStore("nselbJets_jerDown");
    //    addVartoStore("nselLbJets_jerDown");
    //    addVartoStore("nselMbJets_jerDown");
    //    addVartoStore("nselTbJets_jerDown");
    //
    //    // btag in binary
    //    addVartoStore("is_deepJet_T_jerDown");
    //    addVartoStore("is_deepJet_M_jerDown");
    //    addVartoStore("is_deepJet_L_jerDown");
    //
    //    addVartoStore("selJet1_pt_jerDown");
    //    addVartoStore("selJet1_pt_massnom_jerDown");
    //    addVartoStore("selJet1_eta_jerDown");
    //    addVartoStore("selJet1_phi_jerDown");
    //    addVartoStore("selJet1_e_jerDown");
    //    addVartoStore("selJet1_e_massnom_jerDown");
    //    addVartoStore("selJet1_btag_jerDown");
    //
    //    addVartoStore("selJet2_pt_jerDown");
    //    addVartoStore("selJet2_pt_massnom_jerDown");
    //    addVartoStore("selJet2_eta_jerDown");
    //    addVartoStore("selJet2_phi_jerDown");
    //    addVartoStore("selJet2_e_jerDown");
    //    addVartoStore("selJet2_e_massnom_jerDown");
    //    addVartoStore("selJet2_btag_jerDown");
    //
    //    addVartoStore("selJet3_pt_jerDown");
    //    addVartoStore("selJet3_pt_massnom_jerDown");
    //    addVartoStore("selJet3_eta_jerDown");
    //    addVartoStore("selJet3_phi_jerDown");
    //    addVartoStore("selJet3_e_jerDown");
    //    addVartoStore("selJet3_e_massnom_jerDown");
    //    addVartoStore("selJet3_btag_jerDown");
    //
    //    addVartoStore("selJet4_pt_jerDown");
    //    addVartoStore("selJet4_pt_massnom_jerDown");
    //    addVartoStore("selJet4_eta_jerDown");
    //    addVartoStore("selJet4_phi_jerDown");
    //    addVartoStore("selJet4_e_jerDown");
    //    addVartoStore("selJet4_e_massnom_jerDown");
    //    addVartoStore("selJet4_btag_jerDown");
    //
    //    addVartoStore("selJet5_pt_jerDown");
    //    addVartoStore("selJet5_pt_massnom_jerDown");
    //    addVartoStore("selJet5_eta_jerDown");
    //    addVartoStore("selJet5_phi_jerDown");
    //    addVartoStore("selJet5_e_jerDown");
    //    addVartoStore("selJet5_e_massnom_jerDown");
    //    addVartoStore("selJet5_btag_jerDown");
    //
    //    addVartoStore("selbJet1_pt_jerDown");
    //    addVartoStore("selbJet1_pt_massnom_jerDown");
    //    addVartoStore("selbJet1_eta_jerDown");
    //    addVartoStore("selbJet1_phi_jerDown");
    //    addVartoStore("selbJet1_e_jerDown");
    //    addVartoStore("selbJet1_e_massnom_jerDown");
    //    addVartoStore("selbJet1_btag_jerDown");
    //
    //    addVartoStore("selbJet2_pt_jerDown");
    //    addVartoStore("selbJet2_pt_massnom_jerDown");
    //    addVartoStore("selbJet2_eta_jerDown");
    //    addVartoStore("selbJet2_phi_jerDown");
    //    addVartoStore("selbJet2_e_jerDown");
    //    addVartoStore("selbJet2_e_massnom_jerDown");
    //    addVartoStore("selbJet2_btag_jerDown");
    //
    //    addVartoStore("Chi2_min_jerDown");
    //    addVartoStore("goodHT_jerDown");
    //    addVartoStore("invmass_2ndTop_jerDown");
    //    addVartoStore("H_mass_jerDown");

    //    addVartoStore("RelHT_jerDown");          // Cut 1
    //    addVartoStore("Chi2_max_jerDown");       // Cut 2
    //    addVartoStore("dRHbb_chi2_jerDown");     // Cut 3
    //    addVartoStore("Chi2_min_H_jerDown");     // Cut 4
    //    addVartoStore("dRWjj_chi2_jerDown");     // Cut 5
    //    addVartoStore("dRbW_chi2_jerDown");      // Cut 6

    //    // Candidates
    //    addVartoStore("Chi2_min_W_jerDown");
    //    addVartoStore("Chi2_min_Top_jerDown");
    //    addVartoStore("mindR_dRbb_jerDown");
    //    addVartoStore("mindR_mbb_jerDown");
    //    addVartoStore("Top_mass_jerDown");
    //    addVartoStore("W_mass_jerDown");
    //    addVartoStore("invmass_WH_jerDown");
    //    addVartoStore("invmass_Tprime_jerDown");
    //    addVartoStore("invmass_leadjets_jerDown");//etc
    //    addVartoStore("R_TopH_jerDown");
    //    addVartoStore("R_2ndTopW_jerDown");
    //    addVartoStore("newRelHT_jerDown");
    //    addVartoStore("dRTprimeoj_chi2_jerDown");
    //    addVartoStore("dRHTop_chi2_jerDown");
    //    addVartoStore("Rpt_Top2ndTop_jerDown");
    //    addVartoStore("Rpt_HTopTprime_jerDown");
    //    addVartoStore("Rpt_TprimeHTprimeTop_jerDown");

    //}// if jersys end

    //} // if region defined end

} // defineMoreVars end 
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
  // 2016
  if (!isDefined("HLT_PFHT400_SixJet30_DoubleBTagCSV_p056")) _rlm = _rlm.Define("HLT_PFHT400_SixJet30_DoubleBTagCSV_p056", "false");
  if (!isDefined("HLT_PFHT450_SixJet40_BTagCSV_p056")) _rlm = _rlm.Define("HLT_PFHT450_SixJet40_BTagCSV_p056", "false");
  if (!isDefined("HLT_PFHT900")) _rlm = _rlm.Define("HLT_PFHT900", "false");
  if (!isDefined("HLT_PFHT750_4JetPt70")) _rlm = _rlm.Define("HLT_PFHT750_4JetPt70", "false");
  if (!isDefined("HLT_PFHT750_4JetPt80")) _rlm = _rlm.Define("HLT_PFHT750_4JetPt80", "false");
  if (!isDefined("HLT_PFHT800_4JetPt50")) _rlm = _rlm.Define("HLT_PFHT800_4JetPt50", "false");
  if (!isDefined("HLT_PFHT850_4JetPt50")) _rlm = _rlm.Define("HLT_PFHT850_4JetPt50", "false");
  if (!isDefined("HLT_PFJet450")) _rlm = _rlm.Define("HLT_PFJet450", "false");
  if (!isDefined("HLT_PFJet500")) _rlm = _rlm.Define("HLT_PFJet500", "false");


  // 2017
  if (!isDefined("HLT_HT300PT30_QuadJet_75_60_45_40_TripleCSV_p07")) _rlm = _rlm.Define("HLT_HT300PT30_QuadJet_75_60_45_40_TripleCSV_p07", "false");
  if (!isDefined("HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0")) _rlm = _rlm.Define("HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0","false");
  if (!isDefined("HLT_PFHT380_SixJet32_DoubleBTagCSV_p075")) _rlm = _rlm.Define("HLT_PFHT380_SixJet32_DoubleBTagCSV_p075", "false");
  if (!isDefined("HLT_PFHT430_SixJet40_BTagCSV_p080")) _rlm = _rlm.Define("HLT_PFHT430_SixJet40_BTagCSV_p080", "false");
  if (!isDefined("HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2")) _rlm = _rlm.Define("HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2", "false");
  if (!isDefined("HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5")) _rlm = _rlm.Define("HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5", "false"); 
  if (!isDefined("HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2")) _rlm = _rlm.Define("HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2", "false");

  // 2018
  if (!isDefined("HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepCSV_4p5")) _rlm = _rlm.Define("HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepCSV_4p5", "false"); 
  if (!isDefined("HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5")) _rlm = _rlm.Define("HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5", "false"); 
  if (!isDefined("HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5")) _rlm = _rlm.Define("HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5", "false"); 

  if (!isDefined("HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94")) _rlm = _rlm.Define("HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94", "false"); 
  if (!isDefined("HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59")) _rlm = _rlm.Define("HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59", "false"); 
  // ^ huh it wasnt used

  if(_year==2015 || _year==2016){        //2016era

      _rlm = _rlm.Define("METfilter","Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_BadPFMuonDzFilter && Flag_eeBadScFilter");

      _rlm = _rlm.Define("HLT","HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 || HLT_PFHT450_SixJet40_BTagCSV_p056 || HLT_PFHT900 || HLT_PFHT750_4JetPt70 || HLT_PFHT750_4JetPt80 || HLT_PFHT800_4JetPt50 || HLT_PFHT850_4JetPt50 || HLT_PFJet450");

  }
  else if (_year==2017 || _year==2018){

      _rlm = _rlm.Define("METfilter","Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_BadPFMuonDzFilter && Flag_eeBadScFilter && Flag_ecalBadCalibFilter");

      if (_year==2017){
          _rlm = _rlm.Define("HLT", "HLT_HT300PT30_QuadJet_75_60_45_40_TripleCSV_p07 || HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0 || HLT_PFHT380_SixJet32_DoubleBTagCSV_p075 || HLT_PFHT430_SixJet40_BTagCSV_p080 || HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2 || HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 || HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 || HLT_PFHT1050 || HLT_PFJet500");

// hm? HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 is prescaled
// HLT_PFHT380_SixJet32_DoubleBTagCSV_p075 HLT_PFHT430_SixJet40_BTagCSV_p080 has 4.8 lumi, only
// paths from AN2021-140, not reliable, though. names wrong
// "HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2 || HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 || HLT_PFHT430_SixPFJet40_BTagCSV_p080 || HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 || HLT_HT300PT30_QuadJet_75_60_45_40_TripleCSV_p07 || HLT_HT300PT30_QuadJet_75_60_45_40_TriplePFBTagCSV_3p0 || HLT_PFHT1050 || HLT_PFJet500");

      }else if(_year==2018){
//          _rlm = _rlm.Define("HLT","HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 || HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepCSV_4p5 || HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 || HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5 || HLT_PFHT1050 || HLT_PFJet500");
          _rlm = _rlm.Define("HLT","HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 || HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepCSV_4p5 || HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 || HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5 || HLT_PFHT1050 || HLT_PFJet500 || HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 || HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59");
      }
  }

  _rlm = _rlm.Define("aMuons", "Muon_pt > 30 && abs(Muon_eta) < 2.4 && Muon_tightId")
             .Define("aMuons_pt", "Muon_pt[aMuons]")
             .Define("nMuons", "int(aMuons_pt.size())");

}

void TprimeHadAnalyzer::selectLeptons()
{

// align with B2G-24-020
//
//    _rlm = _rlm.Define("goodMuons", "Muon_pt > 20 && abs(Muon_eta) < 2.4 && Muon_tightId && Muon_miniPFRelIso_all < 0.05 && Muon_sip3d < 3 && Muon_tightCharge == 2");
    _rlm = _rlm.Define("goodMuons", "Muon_pt > 30 && abs(Muon_eta) < 2.4 && Muon_tightId && Muon_miniPFRelIso_all < 0.05 && Muon_sip3d < 3");
    _rlm = _rlm.Define("goodMuons_pt", "Muon_pt[goodMuons]") 
               .Define("goodMuons_eta", "Muon_eta[goodMuons]")
               .Define("goodMuons_phi", "Muon_phi[goodMuons]")
               .Define("goodMuons_mass", "Muon_mass[goodMuons]");

//    _rlm = _rlm.Define("goodElectrons", "Electron_pt > 25 && abs(Electron_eta) < 2.5 && Electron_miniPFRelIso_all < 0.05 && Electron_sip3d < 2 && Electron_tightCharge == 2 && Electron_cutBased == 4");
    _rlm = _rlm.Define("goodElectrons", "Electron_pt > 35 && abs(Electron_eta) < 2.5 && ( ( abs(Electron_eta + Electron_deltaEtaSC) < 1.4442 ) || abs(Electron_eta + Electron_deltaEtaSC) > 1.566 ) && ( ( (abs(Electron_eta + Electron_deltaEtaSC) <= 1.479) && abs(Electron_dxy) < 0.05 && abs(Electron_dz) < 0.10 ) || ( (abs(Electron_eta + Electron_deltaEtaSC)>1.479) && abs(Electron_dxy) < 0.10 && abs(Electron_dz) < 0.20) ) && Electron_cutBased == 4");

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

              auto getJERCSFup=[this](floats &etas)->floats
              {
                      return ::JERCSF(_jerc_fname, _jercSF_type,"up", etas);
              };
        
              auto getJERCSFdown=[this](floats &etas)->floats
              {
                      return ::JERCSF(_jerc_fname, _jercSF_type,"down", etas);
              };
        
      _rlm = _rlm.Define("JERCptResolution", getJERCptResolution, {"Jet_eta","Jet_pt","fixedGridRhoFastjetAll"});
      _rlm = _rlm.Define("JERCSF", getJERCSF, {"Jet_eta"});
      _rlm = _rlm.Define("GenMatchJetPtvars", ::GenMatchJetPt, {"Jet_pt", "Jet_eta", "Jet_phi", "Jet_mass", "GenJet_pt", "GenJet_eta", "GenJet_phi", "GenJet_mass", "JERCptResolution"});
      _rlm = _rlm.Define("c_JER", ::getcJER, {"Jet_pt", "GenMatchJetPtvars", "JERCSF", "JERCptResolution"});
      _rlm = _rlm.Define("Jet_pt_smear_nom", "c_JER*Jet_pt");
//      _rlm = _rlm.Define("corrmet_pt_nom", ::getmetsmear, {"corrmetjson_pt", "corrmet_phi", "Jet_pt", "Jet_pt_smear_nom", "Jet_phi"}); // this is the good one
      _rlm = _rlm.Define("rawmet_pt", "MET_pt");
      _rlm = _rlm.Define("rawmet_phi", "MET_phi");

      if(_jecsys == "Total"){

           auto getJECSFs = [this](floats &pts, floats &etas)->floats
           {       
                   return ::getsysJERC(_jerc_fname, pts, etas, _jercsys_total);
           };

           _rlm = _rlm.Define("jecTotal",getJECSFs, {"Jet_pt","Jet_eta"});
           GetJetsys("jecTotal");
      
      }

      if(_jersys == "True"){

          _rlm = _rlm.Define("JERCSFUp", getJERCSFup, {"Jet_eta"})
                     .Define("JERCSFUp2Sig", "JERCSF+2*(JERCSFUp-JERCSF)");
          _rlm = _rlm.Define("c_JERUp", ::getcJER, {"Jet_pt", "GenMatchJetPtvars", "JERCSFUp", "JERCptResolution"});
          _rlm = _rlm.Define("JERCSFDn", getJERCSFdown, {"Jet_eta"})
                     .Define("JERCSFDn2Sig", "JERCSF+2*(JERCSFDn-JERCSF)");
          _rlm = _rlm.Define("c_JERDn", ::getcJER, {"Jet_pt", "GenMatchJetPtvars", "JERCSFDn", "JERCptResolution"});

          _rlm = _rlm.Define("Jet_pt_smear_Up", "c_JERUp*Jet_pt");
          _rlm = _rlm.Define("Jet_pt_smear_Dn", "c_JERDn*Jet_pt");

      }

  }else{ //if its data
      _rlm = _rlm.Define("MCorData", "1.0");
      _rlm = _rlm.Define("Jet_pt_smear_nom", "Jet_pt");
      _rlm = _rlm.Define("run_numbers", "float(run)");
      _rlm = _rlm.Define("rawmet_pt", "MET_pt");
      _rlm = _rlm.Define("rawmet_phi", "MET_phi");
  }
  
  //presel for overlap
//  _rlm = _rlm.Define("pre_goodJets", "Jet_jetId > 1 && Jet_pt_smear_nom >= 30 && abs(Jet_eta) <= 4.5 && (Jet_pt_smear_nom > 50 || Jet_puId > 0)");
  _rlm = _rlm.Define("pre_goodJets", "Jet_jetId > 1 && Jet_pt_smear_nom >= 30 && abs(Jet_eta) <= 2.5 && (Jet_pt_smear_nom > 50 || Jet_puId > 0)");
  
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
             .Define("recob2_Higgs_cand_eta","float(bjet4vecs[Chi2_Tprime[1]].Eta())")
             .Define("recob2_Higgs_cand_phi","float(bjet4vecs[Chi2_Tprime[1]].Phi())")
             .Define("recob2_Higgs_cand_pt","float(bjet4vecs[Chi2_Tprime[1]].Pt())")
             .Define("recob2_Higgs_cand_p","float(bjet4vecs[Chi2_Tprime[1]].P())")

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

             .Define("reco_otherj_cand_eta","float(jet4vecs[Chi2_Tprime[5]].Eta())")
             .Define("reco_otherj_cand_phi","float(jet4vecs[Chi2_Tprime[5]].Phi())")
             .Define("reco_otherj_cand_pt","float(jet4vecs[Chi2_Tprime[5]].Pt())")
             .Define("reco_otherj_cand_p","float(jet4vecs[Chi2_Tprime[5]].P())")
             .Define("reco_otherj_cand_btag","selJet_btagDeepFlavB[Chi2_Tprime[5]]");

  if(_year==2015){        //2016preVFP - APV
      _rlm = _rlm.Define("recob1_Higgs_cand_isT","bool(selbJet_btag[Chi2_Tprime[0]] > 0.6502)")
                 .Define("recob1_Higgs_cand_isM","bool(selbJet_btag[Chi2_Tprime[0]] > 0.2598)")
                 .Define("recob1_Higgs_cand_isL","bool(selbJet_btag[Chi2_Tprime[0]] > 0.0508)")
                 .Define("recob2_Higgs_cand_isT","bool(selbJet_btag[Chi2_Tprime[1]] > 0.6502)")
                 .Define("recob2_Higgs_cand_isM","bool(selbJet_btag[Chi2_Tprime[1]] > 0.2598)")
                 .Define("recob2_Higgs_cand_isL","bool(selbJet_btag[Chi2_Tprime[1]] > 0.0508)")
                 .Define("recoj_bFromTop_cand_isT","bool(selbJet_btag[Chi2_Tprime[4]] > 0.6502)")
                 .Define("recoj_bFromTop_cand_isM","bool(selbJet_btag[Chi2_Tprime[4]] > 0.2598)")
                 .Define("recoj_bFromTop_cand_isL","bool(selbJet_btag[Chi2_Tprime[4]] > 0.0508)");
  }else if (_year==2016){ //postVFP
      _rlm = _rlm.Define("recob1_Higgs_cand_isT","bool(selbJet_btag[Chi2_Tprime[0]] > 0.6377)")
                 .Define("recob1_Higgs_cand_isM","bool(selbJet_btag[Chi2_Tprime[0]] > 0.2489)")
                 .Define("recob1_Higgs_cand_isL","bool(selbJet_btag[Chi2_Tprime[0]] > 0.0480)")
                 .Define("recob2_Higgs_cand_isT","bool(selbJet_btag[Chi2_Tprime[1]] > 0.6377)")
                 .Define("recob2_Higgs_cand_isM","bool(selbJet_btag[Chi2_Tprime[1]] > 0.2489)")
                 .Define("recob2_Higgs_cand_isL","bool(selbJet_btag[Chi2_Tprime[1]] > 0.0480)")
                 .Define("recoj_bFromTop_cand_isT","bool(selbJet_btag[Chi2_Tprime[4]] > 0.6377)")
                 .Define("recoj_bFromTop_cand_isM","bool(selbJet_btag[Chi2_Tprime[4]] > 0.2489)")
                 .Define("recoj_bFromTop_cand_isL","bool(selbJet_btag[Chi2_Tprime[4]] > 0.0480)");
  }else if (_year==2017){
      _rlm = _rlm.Define("recob1_Higgs_cand_isT","bool(selbJet_btag[Chi2_Tprime[0]] > 0.7476)")
                 .Define("recob1_Higgs_cand_isM","bool(selbJet_btag[Chi2_Tprime[0]] > 0.3040)")
                 .Define("recob1_Higgs_cand_isL","bool(selbJet_btag[Chi2_Tprime[0]] > 0.0532)")
                 .Define("recob2_Higgs_cand_isT","bool(selbJet_btag[Chi2_Tprime[1]] > 0.7476)")
                 .Define("recob2_Higgs_cand_isM","bool(selbJet_btag[Chi2_Tprime[1]] > 0.3040)")
                 .Define("recob2_Higgs_cand_isL","bool(selbJet_btag[Chi2_Tprime[1]] > 0.0532)")
                 .Define("recoj_bFromTop_cand_isT","bool(selbJet_btag[Chi2_Tprime[4]] > 0.7476)")
                 .Define("recoj_bFromTop_cand_isM","bool(selbJet_btag[Chi2_Tprime[4]] > 0.3040)")
                 .Define("recoj_bFromTop_cand_isL","bool(selbJet_btag[Chi2_Tprime[4]] > 0.0532)");
  }else if(_year==2018){
      _rlm = _rlm.Define("recob1_Higgs_cand_isT","bool(selbJet_btag[Chi2_Tprime[0]] > 0.7100)")
                 .Define("recob1_Higgs_cand_isM","bool(selbJet_btag[Chi2_Tprime[0]] > 0.2783)")
                 .Define("recob1_Higgs_cand_isL","bool(selbJet_btag[Chi2_Tprime[0]] > 0.0490)")
                 .Define("recob2_Higgs_cand_isT","bool(selbJet_btag[Chi2_Tprime[1]] > 0.7100)")
                 .Define("recob2_Higgs_cand_isM","bool(selbJet_btag[Chi2_Tprime[1]] > 0.2783)")
                 .Define("recob2_Higgs_cand_isL","bool(selbJet_btag[Chi2_Tprime[1]] > 0.0490)")
                 .Define("recoj_bFromTop_cand_isT","bool(selbJet_btag[Chi2_Tprime[4]] > 0.7100)")
                 .Define("recoj_bFromTop_cand_isM","bool(selbJet_btag[Chi2_Tprime[4]] > 0.2783)")
                 .Define("recoj_bFromTop_cand_isL","bool(selbJet_btag[Chi2_Tprime[4]] > 0.0490)");
  }

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

//  // JERC syst
  if(_jersys == "True"){

      _rlm = _rlm.Define("pre_goodJets_jerUp", "Jet_jetId > 1 && Jet_pt_smear_Up >= 30 && abs(Jet_eta) <= 2.5 && (Jet_pt_smear_Up > 50 || Jet_puId > 0)");
    
      _rlm = _rlm.Define("pre_nselJets_jerUp","Sum(pre_goodJets_jerUp)")
                 .Define("pre_selJet_pt_jerUp","Jet_pt_smear_nom[pre_goodJets_jerUp]")
                 .Define("pre_selJet_eta_jerUp","Jet_eta[pre_goodJets_jerUp]")
                 .Define("pre_selJet_phi_jerUp","Jet_phi[pre_goodJets_jerUp]")
                 .Define("pre_selJet_mass_jerUp","Jet_mass[pre_goodJets_jerUp]")
                 .Define("pre_selJet_btagDeepFlavB_jerUp","Jet_btagDeepFlavB[pre_goodJets_jerUp]")
                 .Define("pre_jet4vecs_jerUp", ::generate_4vec, {"pre_selJet_pt_jerUp", "pre_selJet_eta_jerUp", "pre_selJet_phi_jerUp", "pre_selJet_mass_jerUp"});
    
      _rlm = _rlm.Define("mindrlepton_jerUp",checkoverlap,{"pre_jet4vecs_jerUp","goodMuons_4vecs","goodElectrons_4vecs"});
      
      _rlm = _rlm.Define("goodJets_jerUp", "mindrlepton_jerUp > 0.4")
                 .Define("good40Jets_jerUp", "goodJets_jerUp && pre_selJet_pt_jerUp >= 40")
                 .Define("good80Jets_jerUp", "good40Jets_jerUp && pre_selJet_pt_jerUp >= 80");
      
      _rlm = _rlm.Define("selJet_pt_jerUp","pre_selJet_pt_jerUp[goodJets_jerUp]")
                 .Define("selJet40_pt_jerUp","pre_selJet_pt_jerUp[good40Jets_jerUp]")
                 .Define("selJet80_pt_jerUp","pre_selJet_pt_jerUp[good80Jets_jerUp]")
                
                 .Define("selJet_eta_jerUp","pre_selJet_eta_jerUp[goodJets_jerUp]")
                 .Define("selJet_phi_jerUp","pre_selJet_phi_jerUp[goodJets_jerUp]")
                 .Define("selJet_mass_jerUp","pre_selJet_mass_jerUp[goodJets_jerUp]")
                 .Define("selJet_btagDeepFlavB_jerUp","pre_selJet_btagDeepFlavB_jerUp[goodJets_jerUp]")
                 .Define("nselJets_jerUp","int(selJet_pt_jerUp.size())")
                 .Define("nsel40Jets_jerUp","int(selJet40_pt_jerUp.size())")
                 .Define("nsel80Jets_jerUp","int(selJet80_pt_jerUp.size())")                   
                 .Define("jet4vecs_jerUp", ::generate_4vec, {"selJet_pt_jerUp", "selJet_eta_jerUp", "selJet_phi_jerUp", "selJet_mass_jerUp"});
    
          if(_year==2015){        //2016preVFP - APV
              _rlm = _rlm.Define("is_deepJet_T_jerUp","pre_selJet_btagDeepFlavB_jerUp > 0.6502");
              _rlm = _rlm.Define("is_deepJet_M_jerUp","pre_selJet_btagDeepFlavB_jerUp > 0.2598");
              _rlm = _rlm.Define("is_deepJet_L_jerUp","pre_selJet_btagDeepFlavB_jerUp > 0.0508");
          }else if (_year==2016){ //postVFP
              _rlm = _rlm.Define("is_deepJet_T_jerUp","pre_selJet_btagDeepFlavB_jerUp > 0.6377");
              _rlm = _rlm.Define("is_deepJet_M_jerUp","pre_selJet_btagDeepFlavB_jerUp > 0.2489");
              _rlm = _rlm.Define("is_deepJet_L_jerUp","pre_selJet_btagDeepFlavB_jerUp > 0.0480");
          }else if (_year==2017){
              _rlm = _rlm.Define("is_deepJet_T_jerUp","pre_selJet_btagDeepFlavB_jerUp > 0.7476");
              _rlm = _rlm.Define("is_deepJet_M_jerUp","pre_selJet_btagDeepFlavB_jerUp > 0.3040");
              _rlm = _rlm.Define("is_deepJet_L_jerUp","pre_selJet_btagDeepFlavB_jerUp > 0.0532");
          }else if(_year==2018){
              _rlm = _rlm.Define("is_deepJet_T_jerUp","pre_selJet_btagDeepFlavB_jerUp > 0.7100");
              _rlm = _rlm.Define("is_deepJet_M_jerUp","pre_selJet_btagDeepFlavB_jerUp > 0.2783");
              _rlm = _rlm.Define("is_deepJet_L_jerUp","pre_selJet_btagDeepFlavB_jerUp > 0.0490");
          }
    
          // for Chi2 reco
          if(_is3M){
              _rlm = _rlm.Define("goodbJets_jerUp", "goodJets_jerUp && abs(pre_selJet_eta_jerUp) < 2.5 && is_deepJet_M_jerUp");
          }else if(_is3T){
              _rlm = _rlm.Define("goodbJets_jerUp", "goodJets_jerUp && abs(pre_selJet_eta_jerUp) < 2.5 && is_deepJet_T_jerUp");
          }else{
              std::cout << "is 2M1L ?" << _is2M1L << std::endl;
              std::cout << "is 3L ?" << _is3L << std::endl;
              _rlm = _rlm.Define("goodbJets_jerUp", "goodJets_jerUp && abs(pre_selJet_eta_jerUp) < 2.5 && is_deepJet_L_jerUp");
          }
        
          _rlm = _rlm.Define("selbJet_pt_jerUp","pre_selJet_pt_jerUp[goodbJets_jerUp]")
                     .Define("selbJet_eta_jerUp","pre_selJet_eta_jerUp[goodbJets_jerUp]")
                     .Define("selbJet_phi_jerUp","pre_selJet_phi_jerUp[goodbJets_jerUp]")
                     .Define("selbJet_mass_jerUp","pre_selJet_mass_jerUp[goodbJets_jerUp]")
                     .Define("selbJet_btag_jerUp","pre_selJet_btagDeepFlavB_jerUp[goodbJets_jerUp]")
                     .Define("nselbJets_jerUp","int(selbJet_pt_jerUp.size())")
                     .Define("bjet4vecs_jerUp", ::generate_4vec, {"selbJet_pt_jerUp", "selbJet_eta_jerUp", "selbJet_phi_jerUp", "selbJet_mass_jerUp"});

          _rlm = _rlm.Define("goodLbJets_jerUp", "goodJets_jerUp && abs(pre_selJet_eta_jerUp) < 2.5 && is_deepJet_L_jerUp");
          _rlm = _rlm.Define("goodMbJets_jerUp", "goodJets_jerUp && abs(pre_selJet_eta_jerUp) < 2.5 && is_deepJet_M_jerUp");
          _rlm = _rlm.Define("goodTbJets_jerUp", "goodJets_jerUp && abs(pre_selJet_eta_jerUp) < 2.5 && is_deepJet_T_jerUp");
        
          _rlm = _rlm.Define("selLbJet_pt_jerUp","pre_selJet_pt_jerUp[goodLbJets_jerUp]")
                     .Define("selLbJet_eta_jerUp","pre_selJet_eta_jerUp[goodLbJets_jerUp]")
                     .Define("selLbJet_phi_jerUp","pre_selJet_phi_jerUp[goodLbJets_jerUp]")
                     .Define("selLbJet_mass_jerUp","pre_selJet_mass_jerUp[goodLbJets_jerUp]")
                     .Define("selLbJet_btag_jerUp","pre_selJet_btagDeepFlavB_jerUp[goodLbJets_jerUp]")
                     .Define("nselLbJets_jerUp","int(selLbJet_pt_jerUp.size())")
                     .Define("Lbjet4vecs_jerUp", ::generate_4vec, {"selLbJet_pt_jerUp", "selLbJet_eta_jerUp", "selLbJet_phi_jerUp", "selLbJet_mass_jerUp"});
        
          _rlm = _rlm.Define("selMbJet_pt_jerUp","pre_selJet_pt_jerUp[goodMbJets_jerUp]")
                     .Define("selMbJet_eta_jerUp","pre_selJet_eta_jerUp[goodMbJets_jerUp]")
                     .Define("selMbJet_phi_jerUp","pre_selJet_phi_jerUp[goodMbJets_jerUp]")
                     .Define("selMbJet_mass_jerUp","pre_selJet_mass_jerUp[goodMbJets_jerUp]")
                     .Define("selMbJet_btag_jerUp","pre_selJet_btagDeepFlavB_jerUp[goodMbJets_jerUp]")
                     .Define("nselMbJets_jerUp","int(selMbJet_pt_jerUp.size())")
                     .Define("Mbjet4vecs_jerUp", ::generate_4vec, {"selMbJet_pt_jerUp", "selMbJet_eta_jerUp", "selMbJet_phi_jerUp", "selMbJet_mass_jerUp"});
        
          _rlm = _rlm.Define("selTbJet_pt_jerUp","pre_selJet_pt_jerUp[goodTbJets_jerUp]")
                     .Define("selTbJet_eta_jerUp","pre_selJet_eta_jerUp[goodTbJets_jerUp]")
                     .Define("selTbJet_phi_jerUp","pre_selJet_phi_jerUp[goodTbJets_jerUp]")
                     .Define("selTbJet_mass_jerUp","pre_selJet_mass_jerUp[goodTbJets_jerUp]")
                     .Define("selTbJet_btag_jerUp","pre_selJet_btagDeepFlavB_jerUp[goodTbJets_jerUp]")
                     .Define("nselTbJets_jerUp","int(selTbJet_pt_jerUp.size())")
                     .Define("Tbjet4vecs_jerUp", ::generate_4vec, {"selTbJet_pt_jerUp", "selTbJet_eta_jerUp", "selTbJet_phi_jerUp", "selTbJet_mass_jerUp"});
    
          // Function for kinematic reconstruction
          _rlm = _rlm.Define("Chi2_Tprime_jerUp",::Tprime_reconstruction,{"jet4vecs_jerUp","bjet4vecs_jerUp"})
                     .Define("Chi2_min_jerUp","Chi2_Tprime_jerUp[6]")
                     .Define("Chi2_max_jerUp","Chi2_Tprime_jerUp[17]");
        
          // Extra Variables for analysis
          _rlm = _rlm.Define("Higgs4vecs_jerUp","(bjet4vecs_jerUp[Chi2_Tprime_jerUp[0]]+bjet4vecs_jerUp[Chi2_Tprime_jerUp[1]])")
                     .Define("W4vecs_jerUp","(jet4vecs_jerUp[Chi2_Tprime_jerUp[2]]+jet4vecs_jerUp[Chi2_Tprime_jerUp[3]])")
                     .Define("Top4vecs_jerUp","(W4vecs_jerUp+bjet4vecs_jerUp[Chi2_Tprime_jerUp[4]])")
                     .Define("secondTop4vecs_jerUp","(bjet4vecs_jerUp[Chi2_Tprime_jerUp[0]]+bjet4vecs_jerUp[Chi2_Tprime_jerUp[1]]+jet4vecs_jerUp[Chi2_Tprime_jerUp[5]])")
                     .Define("TopWvecs_jerUp","W4vecs_jerUp+Top4vecs_jerUp")
                     .Define("Tprime4vecs_jerUp","(bjet4vecs_jerUp[Chi2_Tprime_jerUp[0]]+bjet4vecs_jerUp[Chi2_Tprime_jerUp[1]]+jet4vecs_jerUp[Chi2_Tprime_jerUp[2]]+jet4vecs_jerUp[Chi2_Tprime_jerUp[3]]+bjet4vecs_jerUp[Chi2_Tprime_jerUp[4]])");
        
          // materials...
          _rlm = _rlm.Define("recoTprime_cand_eta_jerUp","float(Tprime4vecs_jerUp.Eta())")
                     .Define("recoTprime_cand_phi_jerUp","float(Tprime4vecs_jerUp.Phi())")
                     .Define("recoTprime_cand_pt_jerUp","float(Tprime4vecs_jerUp.Pt())")
        
                     .Define("recoHiggs_cand_eta_jerUp","float(Higgs4vecs_jerUp.Eta())")
                     .Define("recoHiggs_cand_phi_jerUp","float(Higgs4vecs_jerUp.Phi())")
                     .Define("recoHiggs_cand_pt_jerUp","float(Higgs4vecs_jerUp.Pt())")
        
                     .Define("recoTop_cand_eta_jerUp","float(Top4vecs_jerUp.Eta())")
                     .Define("recoTop_cand_phi_jerUp","float(Top4vecs_jerUp.Phi())")
                     .Define("recoTop_cand_pt_jerUp","float(Top4vecs_jerUp.Pt())")
        
                     .Define("recosecondTop_cand_pt_jerUp","float(secondTop4vecs_jerUp.Pt())")
        
                     .Define("recoW_cand_eta_jerUp","float(W4vecs_jerUp.Eta())")
                     .Define("recoW_cand_phi_jerUp","float(W4vecs_jerUp.Phi())")
                     .Define("recoW_cand_pt_jerUp","float(W4vecs_jerUp.Pt())");
        
          _rlm = _rlm.Define("recob1_Higgs_cand_eta_jerUp","float(bjet4vecs_jerUp[Chi2_Tprime[0]].Eta())")
                     .Define("recob1_Higgs_cand_phi_jerUp","float(bjet4vecs_jerUp[Chi2_Tprime[0]].Phi())")
                     .Define("recob1_Higgs_cand_pt_jerUp","float(bjet4vecs_jerUp[Chi2_Tprime[0]].Pt())")
                     .Define("recob2_Higgs_cand_eta_jerUp","float(bjet4vecs_jerUp[Chi2_Tprime[1]].Eta())")
                     .Define("recob2_Higgs_cand_phi_jerUp","float(bjet4vecs_jerUp[Chi2_Tprime[1]].Phi())")
                     .Define("recob2_Higgs_cand_pt_jerUp","float(bjet4vecs_jerUp[Chi2_Tprime[1]].Pt())")
        
                     .Define("recoj1_W_cand_eta_jerUp","float(jet4vecs_jerUp[Chi2_Tprime[2]].Eta())")
                     .Define("recoj1_W_cand_phi_jerUp","float(jet4vecs_jerUp[Chi2_Tprime[2]].Phi())")
                     .Define("recoj1_W_cand_pt_jerUp","float(jet4vecs_jerUp[Chi2_Tprime[2]].Pt())")
                     .Define("recoj2_W_cand_eta_jerUp","float(jet4vecs_jerUp[Chi2_Tprime[3]].Eta())")
                     .Define("recoj2_W_cand_phi_jerUp","float(jet4vecs_jerUp[Chi2_Tprime[3]].Phi())")
                     .Define("recoj2_W_cand_pt_jerUp","float(jet4vecs_jerUp[Chi2_Tprime[3]].Pt())")
        
                     .Define("recoj_bFromTop_cand_eta_jerUp","float(bjet4vecs_jerUp[Chi2_Tprime[4]].Eta())")
                     .Define("recoj_bFromTop_cand_phi_jerUp","float(bjet4vecs_jerUp[Chi2_Tprime[4]].Phi())")
                     .Define("recoj_bFromTop_cand_pt_jerUp","float(bjet4vecs_jerUp[Chi2_Tprime[4]].Pt())")
        
                     .Define("reco_otherj_cand_eta_jerUp","float(jet4vecs_jerUp[Chi2_Tprime[5]].Eta())")
                     .Define("reco_otherj_cand_phi_jerUp","float(jet4vecs_jerUp[Chi2_Tprime[5]].Phi())")
                     .Define("reco_otherj_cand_pt_jerUp","float(jet4vecs_jerUp[Chi2_Tprime[5]].Pt())");
        
          // Kinematic reconstructions
          _rlm = _rlm.Define("invmass_leadjets_jerUp", "(jet4vecs_jerUp[0]+jet4vecs_jerUp[1]+jet4vecs_jerUp[2]+jet4vecs_jerUp[3]+jet4vecs_jerUp[4]).M()");
        
          _rlm = _rlm.Define("HT6_jerUp","(selJet_pt_jerUp[0]+selJet_pt_jerUp[1]+selJet_pt_jerUp[2]+selJet_pt_jerUp[3]+selJet_pt_jerUp[4]+selJet_pt_jerUp[5])") 
                     .Define("goodHT_jerUp",::calculate_goodHT, {"selJet_pt_jerUp"})
                     .Define("RelHT_jerUp",::calculate_RelHT, {"Top4vecs_jerUp","Higgs4vecs_jerUp","goodHT"})
                     .Define("sixthJet_pt_jerUp","selJet_pt_jerUp[5]")
                     .Define("newRelHT_jerUp", ::calculate_newRelHT, {"Top4vecs_jerUp","Higgs4vecs_jerUp","sixthJet_pt_jerUp","goodHT_jerUp"});
        
          _rlm = _rlm.Define("dRHbb_chi2_jerUp","ROOT::VecOps::DeltaR(recob1_Higgs_cand_eta_jerUp,recob2_Higgs_cand_eta_jerUp,recob1_Higgs_cand_phi_jerUp,recob2_Higgs_cand_phi_jerUp)")
                     .Define("dRWjj_chi2_jerUp","ROOT::VecOps::DeltaR(recoj1_W_cand_eta_jerUp,recoj2_W_cand_eta_jerUp,recoj1_W_cand_phi_jerUp,recoj2_W_cand_phi_jerUp)")
                     .Define("dRbW_chi2_jerUp","ROOT::VecOps::DeltaR(recoW_cand_eta_jerUp,recoj_bFromTop_cand_eta_jerUp,recoW_cand_phi_jerUp,recoj_bFromTop_cand_phi_jerUp)"); 
        
          _rlm = _rlm.Define("dRTprimeoj_chi2_jerUp","ROOT::VecOps::DeltaR(recoTprime_cand_eta_jerUp,reco_otherj_cand_eta_jerUp,recoTprime_cand_phi_jerUp,reco_otherj_cand_phi_jerUp)")
                     .Define("dRHTop_chi2_jerUp","ROOT::VecOps::DeltaR(recoHiggs_cand_eta_jerUp,recoTop_cand_eta_jerUp,recoHiggs_cand_phi_jerUp,recoTop_cand_phi_jerUp)");
        
          _rlm = _rlm.Define("Rpt_Top2ndTop_jerUp","(recosecondTop_cand_pt_jerUp - recoTop_cand_pt_jerUp) / recosecondTop_cand_pt_jerUp")
                     .Define("Rpt_HTopTprime_jerUp","(recoHiggs_cand_pt_jerUp - recoTop_cand_pt_jerUp) / recoTprime_cand_pt_jerUp")
                     .Define("Rpt_TprimeHTprimeTop_jerUp","(recoTprime_cand_pt_jerUp / recoHiggs_cand_pt_jerUp) - (recoTprime_cand_pt_jerUp / recoTop_cand_pt_jerUp)");


      _rlm = _rlm.Define("pre_goodJets_jerDn", "Jet_jetId > 1 && Jet_pt_smear_Dn >= 30 && abs(Jet_eta) <= 2.5 && (Jet_pt_smear_Dn > 50 || Jet_puId > 0)");
    
      _rlm = _rlm.Define("pre_nselJets_jerDn","Sum(pre_goodJets_jerDn)")
                 .Define("pre_selJet_pt_jerDn","Jet_pt_smear_nom[pre_goodJets_jerDn]")
                 .Define("pre_selJet_eta_jerDn","Jet_eta[pre_goodJets_jerDn]")
                 .Define("pre_selJet_phi_jerDn","Jet_phi[pre_goodJets_jerDn]")
                 .Define("pre_selJet_mass_jerDn","Jet_mass[pre_goodJets_jerDn]")
                 .Define("pre_selJet_btagDeepFlavB_jerDn","Jet_btagDeepFlavB[pre_goodJets_jerDn]")
                 .Define("pre_jet4vecs_jerDn", ::generate_4vec, {"pre_selJet_pt_jerDn", "pre_selJet_eta_jerDn", "pre_selJet_phi_jerDn", "pre_selJet_mass_jerDn"});
    
      _rlm = _rlm.Define("mindrlepton_jerDn",checkoverlap,{"pre_jet4vecs_jerDn","goodMuons_4vecs","goodElectrons_4vecs"});
      
      _rlm = _rlm.Define("goodJets_jerDn", "mindrlepton_jerDn > 0.4")
                 .Define("good40Jets_jerDn", "goodJets_jerDn && pre_selJet_pt_jerDn >= 40")
                 .Define("good80Jets_jerDn", "good40Jets_jerDn && pre_selJet_pt_jerDn >= 80");
      
      _rlm = _rlm.Define("selJet_pt_jerDn","pre_selJet_pt_jerDn[goodJets_jerDn]")
                 .Define("selJet40_pt_jerDn","pre_selJet_pt_jerDn[good40Jets_jerDn]")
                 .Define("selJet80_pt_jerDn","pre_selJet_pt_jerDn[good80Jets_jerDn]")
                
                 .Define("selJet_eta_jerDn","pre_selJet_eta_jerDn[goodJets_jerDn]")
                 .Define("selJet_phi_jerDn","pre_selJet_phi_jerDn[goodJets_jerDn]")
                 .Define("selJet_mass_jerDn","pre_selJet_mass_jerDn[goodJets_jerDn]")
                 .Define("selJet_btagDeepFlavB_jerDn","pre_selJet_btagDeepFlavB_jerDn[goodJets_jerDn]")
                 .Define("nselJets_jerDn","int(selJet_pt_jerDn.size())")
                 .Define("nsel40Jets_jerDn","int(selJet40_pt_jerDn.size())")
                 .Define("nsel80Jets_jerDn","int(selJet80_pt_jerDn.size())")                   
                 .Define("jet4vecs_jerDn", ::generate_4vec, {"selJet_pt_jerDn", "selJet_eta_jerDn", "selJet_phi_jerDn", "selJet_mass_jerDn"});
    
          if(_year==2015){        //2016preVFP - APV
              _rlm = _rlm.Define("is_deepJet_T_jerDn","pre_selJet_btagDeepFlavB_jerDn > 0.6502");
              _rlm = _rlm.Define("is_deepJet_M_jerDn","pre_selJet_btagDeepFlavB_jerDn > 0.2598");
              _rlm = _rlm.Define("is_deepJet_L_jerDn","pre_selJet_btagDeepFlavB_jerDn > 0.0508");
          }else if (_year==2016){ //postVFP
              _rlm = _rlm.Define("is_deepJet_T_jerDn","pre_selJet_btagDeepFlavB_jerDn > 0.6377");
              _rlm = _rlm.Define("is_deepJet_M_jerDn","pre_selJet_btagDeepFlavB_jerDn > 0.2489");
              _rlm = _rlm.Define("is_deepJet_L_jerDn","pre_selJet_btagDeepFlavB_jerDn > 0.0480");
          }else if (_year==2017){
              _rlm = _rlm.Define("is_deepJet_T_jerDn","pre_selJet_btagDeepFlavB_jerDn > 0.7476");
              _rlm = _rlm.Define("is_deepJet_M_jerDn","pre_selJet_btagDeepFlavB_jerDn > 0.3040");
              _rlm = _rlm.Define("is_deepJet_L_jerDn","pre_selJet_btagDeepFlavB_jerDn > 0.0532");
          }else if(_year==2018){
              _rlm = _rlm.Define("is_deepJet_T_jerDn","pre_selJet_btagDeepFlavB_jerDn > 0.7100");
              _rlm = _rlm.Define("is_deepJet_M_jerDn","pre_selJet_btagDeepFlavB_jerDn > 0.2783");
              _rlm = _rlm.Define("is_deepJet_L_jerDn","pre_selJet_btagDeepFlavB_jerDn > 0.0490");
          }
    
          // for Chi2 reco
          if(_is3M){
              _rlm = _rlm.Define("goodbJets_jerDn", "goodJets_jerDn && abs(pre_selJet_eta_jerDn) < 2.5 && is_deepJet_M_jerDn");
          }else if(_is3T){
              _rlm = _rlm.Define("goodbJets_jerDn", "goodJets_jerDn && abs(pre_selJet_eta_jerDn) < 2.5 && is_deepJet_T_jerDn");
          }else{
              std::cout << "is 2M1L ?" << _is2M1L << std::endl;
              std::cout << "is 3L ?" << _is3L << std::endl;
              _rlm = _rlm.Define("goodbJets_jerDn", "goodJets_jerDn && abs(pre_selJet_eta_jerDn) < 2.5 && is_deepJet_L_jerDn");
          }
        
          _rlm = _rlm.Define("selbJet_pt_jerDn","pre_selJet_pt_jerDn[goodbJets_jerDn]")
                     .Define("selbJet_eta_jerDn","pre_selJet_eta_jerDn[goodbJets_jerDn]")
                     .Define("selbJet_phi_jerDn","pre_selJet_phi_jerDn[goodbJets_jerDn]")
                     .Define("selbJet_mass_jerDn","pre_selJet_mass_jerDn[goodbJets_jerDn]")
                     .Define("selbJet_btag_jerDn","pre_selJet_btagDeepFlavB_jerDn[goodbJets_jerDn]")
                     .Define("nselbJets_jerDn","int(selbJet_pt_jerDn.size())")
                     .Define("bjet4vecs_jerDn", ::generate_4vec, {"selbJet_pt_jerDn", "selbJet_eta_jerDn", "selbJet_phi_jerDn", "selbJet_mass_jerDn"});

          _rlm = _rlm.Define("goodLbJets_jerDn", "goodJets_jerDn && abs(pre_selJet_eta_jerDn) < 2.5 && is_deepJet_L_jerDn");
          _rlm = _rlm.Define("goodMbJets_jerDn", "goodJets_jerDn && abs(pre_selJet_eta_jerDn) < 2.5 && is_deepJet_M_jerDn");
          _rlm = _rlm.Define("goodTbJets_jerDn", "goodJets_jerDn && abs(pre_selJet_eta_jerDn) < 2.5 && is_deepJet_T_jerDn");
        
          _rlm = _rlm.Define("selLbJet_pt_jerDn","pre_selJet_pt_jerDn[goodLbJets_jerDn]")
                     .Define("selLbJet_eta_jerDn","pre_selJet_eta_jerDn[goodLbJets_jerDn]")
                     .Define("selLbJet_phi_jerDn","pre_selJet_phi_jerDn[goodLbJets_jerDn]")
                     .Define("selLbJet_mass_jerDn","pre_selJet_mass_jerDn[goodLbJets_jerDn]")
                     .Define("selLbJet_btag_jerDn","pre_selJet_btagDeepFlavB_jerDn[goodLbJets_jerDn]")
                     .Define("nselLbJets_jerDn","int(selLbJet_pt_jerDn.size())")
                     .Define("Lbjet4vecs_jerDn", ::generate_4vec, {"selLbJet_pt_jerDn", "selLbJet_eta_jerDn", "selLbJet_phi_jerDn", "selLbJet_mass_jerDn"});
        
          _rlm = _rlm.Define("selMbJet_pt_jerDn","pre_selJet_pt_jerDn[goodMbJets_jerDn]")
                     .Define("selMbJet_eta_jerDn","pre_selJet_eta_jerDn[goodMbJets_jerDn]")
                     .Define("selMbJet_phi_jerDn","pre_selJet_phi_jerDn[goodMbJets_jerDn]")
                     .Define("selMbJet_mass_jerDn","pre_selJet_mass_jerDn[goodMbJets_jerDn]")
                     .Define("selMbJet_btag_jerDn","pre_selJet_btagDeepFlavB_jerDn[goodMbJets_jerDn]")
                     .Define("nselMbJets_jerDn","int(selMbJet_pt_jerDn.size())")
                     .Define("Mbjet4vecs_jerDn", ::generate_4vec, {"selMbJet_pt_jerDn", "selMbJet_eta_jerDn", "selMbJet_phi_jerDn", "selMbJet_mass_jerDn"});
        
          _rlm = _rlm.Define("selTbJet_pt_jerDn","pre_selJet_pt_jerDn[goodTbJets_jerDn]")
                     .Define("selTbJet_eta_jerDn","pre_selJet_eta_jerDn[goodTbJets_jerDn]")
                     .Define("selTbJet_phi_jerDn","pre_selJet_phi_jerDn[goodTbJets_jerDn]")
                     .Define("selTbJet_mass_jerDn","pre_selJet_mass_jerDn[goodTbJets_jerDn]")
                     .Define("selTbJet_btag_jerDn","pre_selJet_btagDeepFlavB_jerDn[goodTbJets_jerDn]")
                     .Define("nselTbJets_jerDn","int(selTbJet_pt_jerDn.size())")
                     .Define("Tbjet4vecs_jerDn", ::generate_4vec, {"selTbJet_pt_jerDn", "selTbJet_eta_jerDn", "selTbJet_phi_jerDn", "selTbJet_mass_jerDn"});
    
          // Function for kinematic reconstruction
          _rlm = _rlm.Define("Chi2_Tprime_jerDn",::Tprime_reconstruction,{"jet4vecs_jerDn","bjet4vecs_jerDn"})
                     .Define("Chi2_min_jerDn","Chi2_Tprime_jerDn[6]")
                     .Define("Chi2_max_jerDn","Chi2_Tprime_jerDn[17]");
        
          // Extra Variables for analysis
          _rlm = _rlm.Define("Higgs4vecs_jerDn","(bjet4vecs_jerDn[Chi2_Tprime_jerDn[0]]+bjet4vecs_jerDn[Chi2_Tprime_jerDn[1]])")
                     .Define("W4vecs_jerDn","(jet4vecs_jerDn[Chi2_Tprime_jerDn[2]]+jet4vecs_jerDn[Chi2_Tprime_jerDn[3]])")
                     .Define("Top4vecs_jerDn","(W4vecs_jerDn+bjet4vecs_jerDn[Chi2_Tprime_jerDn[4]])")
                     .Define("secondTop4vecs_jerDn","(bjet4vecs_jerDn[Chi2_Tprime_jerDn[0]]+bjet4vecs_jerDn[Chi2_Tprime_jerDn[1]]+jet4vecs_jerDn[Chi2_Tprime_jerDn[5]])")
                     .Define("TopWvecs_jerDn","W4vecs_jerDn+Top4vecs_jerDn")
                     .Define("Tprime4vecs_jerDn","(bjet4vecs_jerDn[Chi2_Tprime_jerDn[0]]+bjet4vecs_jerDn[Chi2_Tprime_jerDn[1]]+jet4vecs_jerDn[Chi2_Tprime_jerDn[2]]+jet4vecs_jerDn[Chi2_Tprime_jerDn[3]]+bjet4vecs_jerDn[Chi2_Tprime_jerDn[4]])");
        
          // materials...
          _rlm = _rlm.Define("recoTprime_cand_eta_jerDn","float(Tprime4vecs_jerDn.Eta())")
                     .Define("recoTprime_cand_phi_jerDn","float(Tprime4vecs_jerDn.Phi())")
                     .Define("recoTprime_cand_pt_jerDn","float(Tprime4vecs_jerDn.Pt())")
        
                     .Define("recoHiggs_cand_eta_jerDn","float(Higgs4vecs_jerDn.Eta())")
                     .Define("recoHiggs_cand_phi_jerDn","float(Higgs4vecs_jerDn.Phi())")
                     .Define("recoHiggs_cand_pt_jerDn","float(Higgs4vecs_jerDn.Pt())")
        
                     .Define("recoTop_cand_eta_jerDn","float(Top4vecs_jerDn.Eta())")
                     .Define("recoTop_cand_phi_jerDn","float(Top4vecs_jerDn.Phi())")
                     .Define("recoTop_cand_pt_jerDn","float(Top4vecs_jerDn.Pt())")
        
                     .Define("recosecondTop_cand_pt_jerDn","float(secondTop4vecs_jerDn.Pt())")
        
                     .Define("recoW_cand_eta_jerDn","float(W4vecs_jerDn.Eta())")
                     .Define("recoW_cand_phi_jerDn","float(W4vecs_jerDn.Phi())")
                     .Define("recoW_cand_pt_jerDn","float(W4vecs_jerDn.Pt())");
        
          _rlm = _rlm.Define("recob1_Higgs_cand_eta_jerDn","float(bjet4vecs_jerDn[Chi2_Tprime[0]].Eta())")
                     .Define("recob1_Higgs_cand_phi_jerDn","float(bjet4vecs_jerDn[Chi2_Tprime[0]].Phi())")
                     .Define("recob1_Higgs_cand_pt_jerDn","float(bjet4vecs_jerDn[Chi2_Tprime[0]].Pt())")
                     .Define("recob2_Higgs_cand_eta_jerDn","float(bjet4vecs_jerDn[Chi2_Tprime[1]].Eta())")
                     .Define("recob2_Higgs_cand_phi_jerDn","float(bjet4vecs_jerDn[Chi2_Tprime[1]].Phi())")
                     .Define("recob2_Higgs_cand_pt_jerDn","float(bjet4vecs_jerDn[Chi2_Tprime[1]].Pt())")
        
                     .Define("recoj1_W_cand_eta_jerDn","float(jet4vecs_jerDn[Chi2_Tprime[2]].Eta())")
                     .Define("recoj1_W_cand_phi_jerDn","float(jet4vecs_jerDn[Chi2_Tprime[2]].Phi())")
                     .Define("recoj1_W_cand_pt_jerDn","float(jet4vecs_jerDn[Chi2_Tprime[2]].Pt())")
                     .Define("recoj2_W_cand_eta_jerDn","float(jet4vecs_jerDn[Chi2_Tprime[3]].Eta())")
                     .Define("recoj2_W_cand_phi_jerDn","float(jet4vecs_jerDn[Chi2_Tprime[3]].Phi())")
                     .Define("recoj2_W_cand_pt_jerDn","float(jet4vecs_jerDn[Chi2_Tprime[3]].Pt())")
        
                     .Define("recoj_bFromTop_cand_eta_jerDn","float(bjet4vecs_jerDn[Chi2_Tprime[4]].Eta())")
                     .Define("recoj_bFromTop_cand_phi_jerDn","float(bjet4vecs_jerDn[Chi2_Tprime[4]].Phi())")
                     .Define("recoj_bFromTop_cand_pt_jerDn","float(bjet4vecs_jerDn[Chi2_Tprime[4]].Pt())")
        
                     .Define("reco_otherj_cand_eta_jerDn","float(jet4vecs_jerDn[Chi2_Tprime[5]].Eta())")
                     .Define("reco_otherj_cand_phi_jerDn","float(jet4vecs_jerDn[Chi2_Tprime[5]].Phi())")
                     .Define("reco_otherj_cand_pt_jerDn","float(jet4vecs_jerDn[Chi2_Tprime[5]].Pt())");
        
          // Kinematic reconstructions
          _rlm = _rlm.Define("invmass_leadjets_jerDn", "(jet4vecs_jerDn[0]+jet4vecs_jerDn[1]+jet4vecs_jerDn[2]+jet4vecs_jerDn[3]+jet4vecs_jerDn[4]).M()");
        
          _rlm = _rlm.Define("HT6_jerDn","(selJet_pt_jerDn[0]+selJet_pt_jerDn[1]+selJet_pt_jerDn[2]+selJet_pt_jerDn[3]+selJet_pt_jerDn[4]+selJet_pt_jerDn[5])") 
                     .Define("goodHT_jerDn",::calculate_goodHT, {"selJet_pt_jerDn"})
                     .Define("RelHT_jerDn",::calculate_RelHT, {"Top4vecs_jerDn","Higgs4vecs_jerDn","goodHT"})
                     .Define("sixthJet_pt_jerDn","selJet_pt_jerDn[5]")
                     .Define("newRelHT_jerDn", ::calculate_newRelHT, {"Top4vecs_jerDn","Higgs4vecs_jerDn","sixthJet_pt_jerDn","goodHT_jerDn"});
        
          _rlm = _rlm.Define("dRHbb_chi2_jerDn","ROOT::VecOps::DeltaR(recob1_Higgs_cand_eta_jerDn,recob2_Higgs_cand_eta_jerDn,recob1_Higgs_cand_phi_jerDn,recob2_Higgs_cand_phi_jerDn)")
                     .Define("dRWjj_chi2_jerDn","ROOT::VecOps::DeltaR(recoj1_W_cand_eta_jerDn,recoj2_W_cand_eta_jerDn,recoj1_W_cand_phi_jerDn,recoj2_W_cand_phi_jerDn)")
                     .Define("dRbW_chi2_jerDn","ROOT::VecOps::DeltaR(recoW_cand_eta_jerDn,recoj_bFromTop_cand_eta_jerDn,recoW_cand_phi_jerDn,recoj_bFromTop_cand_phi_jerDn)"); 
        
          _rlm = _rlm.Define("dRTprimeoj_chi2_jerDn","ROOT::VecOps::DeltaR(recoTprime_cand_eta_jerDn,reco_otherj_cand_eta_jerDn,recoTprime_cand_phi_jerDn,reco_otherj_cand_phi_jerDn)")
                     .Define("dRHTop_chi2_jerDn","ROOT::VecOps::DeltaR(recoHiggs_cand_eta_jerDn,recoTop_cand_eta_jerDn,recoHiggs_cand_phi_jerDn,recoTop_cand_phi_jerDn)");
        
          _rlm = _rlm.Define("Rpt_Top2ndTop_jerDn","(recosecondTop_cand_pt_jerDn - recoTop_cand_pt_jerDn) / recosecondTop_cand_pt_jerDn")
                     .Define("Rpt_HTopTprime_jerDn","(recoHiggs_cand_pt_jerDn - recoTop_cand_pt_jerDn) / recoTprime_cand_pt_jerDn")
                     .Define("Rpt_TprimeHTprimeTop_jerDn","(recoTprime_cand_pt_jerDn / recoHiggs_cand_pt_jerDn) - (recoTprime_cand_pt_jerDn / recoTop_cand_pt_jerDn)");

  } // jersys end
    
    
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

        auto btagWeight_hUp = [this](ints &hadflav, floats &etas, floats &pts, floats &discs, ints &wpL, ints &wpM, ints &wpT)->float
        {
            return ::producer_btagWeight(_correction_btag1, _efficiency_btag1, "up_correlated", "central", hadflav, etas, pts, discs, wpL, wpM, wpT, _isTprime, _isTT, _isQCD, _isST, _isVJets, _isttH); // defined in utility.cpp
        };

        auto btagWeight_hUpuncorr = [this](ints &hadflav, floats &etas, floats &pts, floats &discs, ints &wpL, ints &wpM, ints &wpT)->float
        {
            return ::producer_btagWeight(_correction_btag1, _efficiency_btag1, "up_uncorrelated", "central", hadflav, etas, pts, discs, wpL, wpM, wpT, _isTprime, _isTT, _isQCD, _isST, _isVJets, _isttH); // defined in utility.cpp
        };

        auto btagWeight_lUp = [this](ints &hadflav, floats &etas, floats &pts, floats &discs, ints &wpL, ints &wpM, ints &wpT)->float
        {
            return ::producer_btagWeight(_correction_btag1, _efficiency_btag1, "central", "up_correlated", hadflav, etas, pts, discs, wpL, wpM, wpT, _isTprime, _isTT, _isQCD, _isST, _isVJets, _isttH); // defined in utility.cpp
        };

        auto btagWeight_lUpuncorr = [this](ints &hadflav, floats &etas, floats &pts, floats &discs, ints &wpL, ints &wpM, ints &wpT)->float
        {
            return ::producer_btagWeight(_correction_btag1, _efficiency_btag1, "central", "up_uncorrelated", hadflav, etas, pts, discs, wpL, wpM, wpT, _isTprime, _isTT, _isQCD, _isST, _isVJets, _isttH); // defined in utility.cpp
        };

        auto btagWeight_hDn = [this](ints &hadflav, floats &etas, floats &pts, floats &discs, ints &wpL, ints &wpM, ints &wpT)->float
        {
            return ::producer_btagWeight(_correction_btag1, _efficiency_btag1, "down_correlated", "central", hadflav, etas, pts, discs, wpL, wpM, wpT, _isTprime, _isTT, _isQCD, _isST, _isVJets, _isttH); // defined in utility.cpp
        };

        auto btagWeight_hDnuncorr = [this](ints &hadflav, floats &etas, floats &pts, floats &discs, ints &wpL, ints &wpM, ints &wpT)->float
        {
            return ::producer_btagWeight(_correction_btag1, _efficiency_btag1, "down_uncorrelated", "central", hadflav, etas, pts, discs, wpL, wpM, wpT, _isTprime, _isTT, _isQCD, _isST, _isVJets, _isttH); // defined in utility.cpp
        };

        auto btagWeight_lDn = [this](ints &hadflav, floats &etas, floats &pts, floats &discs, ints &wpL, ints &wpM, ints &wpT)->float
        {
            return ::producer_btagWeight(_correction_btag1, _efficiency_btag1, "central", "down_correlated", hadflav, etas, pts, discs, wpL, wpM, wpT, _isTprime, _isTT, _isQCD, _isST, _isVJets, _isttH); // defined in utility.cpp
        };

        auto btagWeight_lDnuncorr = [this](ints &hadflav, floats &etas, floats &pts, floats &discs, ints &wpL, ints &wpM, ints &wpT)->float
        {
            return ::producer_btagWeight(_correction_btag1, _efficiency_btag1, "central", "down_uncorrelated", hadflav, etas, pts, discs, wpL, wpM, wpT, _isTprime, _isTT, _isQCD, _isST, _isVJets, _isttH); // defined in utility.cpp
        };

        _rlm = _rlm.Define("btagWeight", btagWeight, {"selJetsForbtag_hadronFlavour","selJetsForbtag_eta","selJetsForbtag_pt","selJetsForbtag_btag", "WP_deepJet_L", "WP_deepJet_M", "WP_deepJet_T"});
        _rlm = _rlm.Define("btagWeight_hUp", btagWeight_hUp, {"selJetsForbtag_hadronFlavour","selJetsForbtag_eta","selJetsForbtag_pt","selJetsForbtag_btag", "WP_deepJet_L", "WP_deepJet_M", "WP_deepJet_T"});
        _rlm = _rlm.Define("btagWeight_hUpuncorr", btagWeight_hUpuncorr, {"selJetsForbtag_hadronFlavour","selJetsForbtag_eta","selJetsForbtag_pt","selJetsForbtag_btag", "WP_deepJet_L", "WP_deepJet_M", "WP_deepJet_T"});
        _rlm = _rlm.Define("btagWeight_lUp", btagWeight_lUp, {"selJetsForbtag_hadronFlavour","selJetsForbtag_eta","selJetsForbtag_pt","selJetsForbtag_btag", "WP_deepJet_L", "WP_deepJet_M", "WP_deepJet_T"});
        _rlm = _rlm.Define("btagWeight_lUpuncorr", btagWeight_lUpuncorr, {"selJetsForbtag_hadronFlavour","selJetsForbtag_eta","selJetsForbtag_pt","selJetsForbtag_btag", "WP_deepJet_L", "WP_deepJet_M", "WP_deepJet_T"});
        _rlm = _rlm.Define("btagWeight_hDn", btagWeight_hDn, {"selJetsForbtag_hadronFlavour","selJetsForbtag_eta","selJetsForbtag_pt","selJetsForbtag_btag", "WP_deepJet_L", "WP_deepJet_M", "WP_deepJet_T"});
        _rlm = _rlm.Define("btagWeight_hDnuncorr", btagWeight_hDnuncorr, {"selJetsForbtag_hadronFlavour","selJetsForbtag_eta","selJetsForbtag_pt","selJetsForbtag_btag", "WP_deepJet_L", "WP_deepJet_M", "WP_deepJet_T"});
        _rlm = _rlm.Define("btagWeight_lDn", btagWeight_lDn, {"selJetsForbtag_hadronFlavour","selJetsForbtag_eta","selJetsForbtag_pt","selJetsForbtag_btag", "WP_deepJet_L", "WP_deepJet_M", "WP_deepJet_T"});
        _rlm = _rlm.Define("btagWeight_lDnuncorr", btagWeight_lDnuncorr, {"selJetsForbtag_hadronFlavour","selJetsForbtag_eta","selJetsForbtag_pt","selJetsForbtag_btag", "WP_deepJet_L", "WP_deepJet_M", "WP_deepJet_T"});

    }else{
        std::cout <<"its data, no b tagging SF applied"<< std::endl;
        _rlm = _rlm.Define("btagWeight", "1.0");
//        _rlm = _rlm.Define("btagTFWeight", "1.0");

//        std::cout <<"b tagging TF"<< std::endl;
//
//        auto btagTFWeight = [this](float p1, float p2, float p3, float eta1, float eta2, float eta3, bool is1bM, bool is1bL, bool is2bM, bool is2bL, bool is3bM, bool is3bL)->float
//        {
//            return ::producer_btagTFWeight(_ratio_btag, p1, p2, p3, eta1, eta2, eta3, is1bM, is1bL, is2bM, is2bL, is3bM, is3bL, _is2M1L, _is3M, _is3T); // defined in utility.cpp
//        };
//
//        _rlm = _rlm.Define("btagTFWeight", btagTFWeight, {"recob1_Higgs_cand_p","recob2_Higgs_cand_p","recoj_bFromTop_cand_p","recob1_Higgs_cand_eta","recob2_Higgs_cand_eta","recoj_bFromTop_cand_eta","recob1_Higgs_cand_isM","recob1_Higgs_cand_isL","recob2_Higgs_cand_isM","recob2_Higgs_cand_isL","recoj_bFromTop_cand_isM","recoj_bFromTop_cand_isL"});
//        _rlm = _rlm.Define("btagTFWeight", btagTFWeight, {"recob1_Higgs_cand_pt","recob2_Higgs_cand_pt","recoj_bFromTop_cand_pt","recob1_Higgs_cand_eta","recob2_Higgs_cand_eta","recoj_bFromTop_cand_eta","recob1_Higgs_cand_isM","recob1_Higgs_cand_isL","recob2_Higgs_cand_isM","recob2_Higgs_cand_isL","recoj_bFromTop_cand_isM","recoj_bFromTop_cand_isL"});

    }

    // here OUT
    std::cout <<"b tagging TF"<< std::endl;

    auto btagTFWeight = [this](float p1, float p2, float p3, float eta1, float eta2, float eta3, bool is1bM, bool is1bL, bool is2bM, bool is2bL, bool is3bM, bool is3bL)->float
    {
        return ::producer_btagTFWeight(_ratio_btag, p1, p2, p3, eta1, eta2, eta3, is1bM, is1bL, is2bM, is2bL, is3bM, is3bL, _is2M1L, _is3M, _is3T); // defined in utility.cpp
    };

    // apply TF anyway
    _rlm = _rlm.Define("btagTFWeight", btagTFWeight, {"recob1_Higgs_cand_p","recob2_Higgs_cand_p","recoj_bFromTop_cand_p","recob1_Higgs_cand_eta","recob2_Higgs_cand_eta","recoj_bFromTop_cand_eta","recob1_Higgs_cand_isM","recob1_Higgs_cand_isL","recob2_Higgs_cand_isM","recob2_Higgs_cand_isL","recoj_bFromTop_cand_isM","recoj_bFromTop_cand_isL"});
//    again once I get TF

    int _case = 1;
    std::vector<std::string> Jets_vars_names = {"selJetsForbtag_hadronFlavour", "selJetsForbtag_eta", "selJetsForbtag_pt", "selJetsForbtag_btag"};  
    if(_case !=1){
      Jets_vars_names.emplace_back("selJetsForbtag_btag");
    }

    if(_topPtReweight == "True"){
        _rlm = _rlm.Define("evWeight_topPtSF", ::topPtWeight, {"GenPart_pt", "GenPart_pdgId", "GenPart_statusFlags"});
            if(_topPtReweightsys == "True"){
                _rlm = _rlm.Define("evWeight_topPtSFUp", "evWeight_topPtSF*evWeight_topPtSF");
                _rlm = _rlm.Define("evWeight_topPtSFDn", "1.0");
            }
    }else{
        _rlm = _rlm.Define("evWeight_topPtSF", "1.0");
    }

    // previously
    _rlm = _rlm.Define("evWeight", "pugenWeight");
    _rlm = _rlm.Define("evWeight_L1", "pugenWeight * L1PreFiringWeight_Nom");
    _rlm = _rlm.Define("evWeight_L1btag", "pugenWeight * btagWeight * L1PreFiringWeight_Nom");
    _rlm = _rlm.Define("evWeight_L1_topPt", "pugenWeight * L1PreFiringWeight_Nom * evWeight_topPtSF");
    _rlm = _rlm.Define("evWeight_L1btag_topPt", "pugenWeight * btagWeight * L1PreFiringWeight_Nom * evWeight_topPtSF");
    _rlm = _rlm.Define("evWeight_L1btag_topPt_TF", "pugenWeight * btagWeight * L1PreFiringWeight_Nom * evWeight_topPtSF * btagTFWeight");

    _rlm = _rlm.Define("evWeight_L1Up", "pugenWeight * btagWeight * L1PreFiringWeight_Up * evWeight_topPtSF");
    _rlm = _rlm.Define("evWeight_L1Dn", "pugenWeight * btagWeight * L1PreFiringWeight_Dn * evWeight_topPtSF");

    if(_btagsys == "True"){
    _rlm = _rlm.Define("evWeight_btaghUp", "pugenWeight * btagWeight_hUp * L1PreFiringWeight_Nom * evWeight_topPtSF");
    _rlm = _rlm.Define("evWeight_btaglUp", "pugenWeight * btagWeight_lUp * L1PreFiringWeight_Nom * evWeight_topPtSF");
    _rlm = _rlm.Define("evWeight_btaghDn", "pugenWeight * btagWeight_hDn * L1PreFiringWeight_Nom * evWeight_topPtSF");
    _rlm = _rlm.Define("evWeight_btaglDn", "pugenWeight * btagWeight_lDn * L1PreFiringWeight_Nom * evWeight_topPtSF");

        if(_btagsysuncorr == "True"){
            _rlm = _rlm.Define("evWeight_btaghUpuncorr", "pugenWeight * btagWeight_hUpuncorr * L1PreFiringWeight_Nom * evWeight_topPtSF");
            _rlm = _rlm.Define("evWeight_btaglUpuncorr", "pugenWeight * btagWeight_lUpuncorr * L1PreFiringWeight_Nom * evWeight_topPtSF");
            _rlm = _rlm.Define("evWeight_btaghDnuncorr", "pugenWeight * btagWeight_hDnuncorr * L1PreFiringWeight_Nom * evWeight_topPtSF");
            _rlm = _rlm.Define("evWeight_btaglDnuncorr", "pugenWeight * btagWeight_lDnuncorr * L1PreFiringWeight_Nom * evWeight_topPtSF");

        }

    }
    if(_topPtReweightsys == "True"){
        _rlm = _rlm.Define("evWeight_topPtUp", "pugenWeight * L1PreFiringWeight_Nom * btagWeight * evWeight_topPtSFUp");
        _rlm = _rlm.Define("evWeight_topPtDn", "pugenWeight * L1PreFiringWeight_Nom * btagWeight * evWeight_topPtSFDn");
    }

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

    auto getJERCptResolution=[this](floats &etas, floats &pts, floats &rhos)->floats
    {
            return ::JERCptResolution(_jerc_fname, _jercptres_type, etas, pts, rhos);
    };

    _rlm = _rlm.Define("Jet_pt_"+sys+"Up", sys+"*2*Jet_pt+Jet_pt")
           .Define("Jet_pt_"+sys+"Dn", "-"+sys+"*2*Jet_pt+Jet_pt")
           .Define("Jet_mass_"+sys+"Up", sys+"*Jet_mass+Jet_mass")
           .Define("Jet_mass_"+sys+"Dn", "-"+sys+"*Jet_mass+Jet_mass");

    _rlm = _rlm.Define("JERCptResolution"+sys+"Up", getJERCptResolution, {"Jet_eta","Jet_pt_"+sys+"Up","fixedGridRhoFastjetAll"})
               .Define("JERCptResolution"+sys+"Dn", getJERCptResolution, {"Jet_eta","Jet_pt_"+sys+"Dn","fixedGridRhoFastjetAll"})
               .Define("GenMatchJetPtvars"+sys+"Up", ::GenMatchJetPt, {"Jet_pt_"+sys+"Up", "Jet_eta", "Jet_phi", "Jet_mass_"+sys+"Up", "GenJet_pt", "GenJet_eta", "GenJet_phi", "GenJet_mass", "JERCptResolution"+sys+"Up"})
               .Define("GenMatchJetPtvars"+sys+"Dn", ::GenMatchJetPt, {"Jet_pt_"+sys+"Dn", "Jet_eta", "Jet_phi", "Jet_mass_"+sys+"Dn", "GenJet_pt", "GenJet_eta", "GenJet_phi", "GenJet_mass", "JERCptResolution"+sys+"Dn"})
               .Define("c_JER"+sys+"Up", ::getcJER, {"Jet_pt_"+sys+"Up", "GenMatchJetPtvars"+sys+"Up", "JERCSF", "JERCptResolution"+sys+"Up"})
               .Define("c_JER"+sys+"Dn", ::getcJER, {"Jet_pt_"+sys+"Dn", "GenMatchJetPtvars"+sys+"Dn", "JERCSF", "JERCptResolution"+sys+"Dn"});

    _rlm = _rlm.Define("Jet_pt_smear_"+sys+"Up", "c_JER"+sys+"Up*Jet_pt_"+sys+"Up")
               .Define("Jet_pt_smear_"+sys+"Dn", "c_JER"+sys+"Dn*Jet_pt_"+sys+"Dn");

    // Up
    _rlm = _rlm.Define("pre_goodJets_"+sys+"Up", "Jet_jetId > 1 && Jet_pt_smear_"+sys+"Up >= 30 && abs(Jet_eta) <= 2.5 && (Jet_pt_smear_"+sys+"Up > 50 || Jet_puId > 0)");
    
    _rlm = _rlm.Define("pre_nselJets_"+sys+"Up","Sum(pre_goodJets_"+sys+"Up)")
               .Define("pre_selJet_pt_"+sys+"Up","Jet_pt_smear_"+sys+"Up[pre_goodJets_"+sys+"Up]")
               .Define("pre_selJet_eta_"+sys+"Up","Jet_eta[pre_goodJets_"+sys+"Up]")
               .Define("pre_selJet_phi_"+sys+"Up","Jet_phi[pre_goodJets_"+sys+"Up]")
               .Define("pre_selJet_mass_"+sys+"Up","Jet_mass[pre_goodJets_"+sys+"Up]")
               .Define("pre_selJet_btagDeepFlavB_"+sys+"Up","Jet_btagDeepFlavB[pre_goodJets_"+sys+"Up]")
               .Define("pre_jet4vecs_"+sys+"Up", ::generate_4vec, {"pre_selJet_pt_"+sys+"Up", "pre_selJet_eta_"+sys+"Up", "pre_selJet_phi_"+sys+"Up", "pre_selJet_mass_"+sys+"Up"});
    
    _rlm = _rlm.Define("mindrlepton_"+sys+"Up",checkoverlap,{"pre_jet4vecs_"+sys+"Up","goodMuons_4vecs","goodElectrons_4vecs"});
    
    _rlm = _rlm.Define("goodJets_"+sys+"Up", "mindrlepton_"+sys+"Up > 0.4")
               .Define("good40Jets_"+sys+"Up", "goodJets_"+sys+"Up && pre_selJet_pt_"+sys+"Up >= 40")
               .Define("good80Jets_"+sys+"Up", "good40Jets_"+sys+"Up && pre_selJet_pt_"+sys+"Up >= 80");
    
    _rlm = _rlm.Define("selJet_pt_"+sys+"Up","pre_selJet_pt_"+sys+"Up[goodJets_"+sys+"Up]")
               .Define("selJet40_pt_"+sys+"Up","pre_selJet_pt_"+sys+"Up[good40Jets_"+sys+"Up]")
               .Define("selJet80_pt_"+sys+"Up","pre_selJet_pt_"+sys+"Up[good80Jets_"+sys+"Up]")
              
               .Define("selJet_eta_"+sys+"Up","pre_selJet_eta_"+sys+"Up[goodJets_"+sys+"Up]")
               .Define("selJet_phi_"+sys+"Up","pre_selJet_phi_"+sys+"Up[goodJets_"+sys+"Up]")
               .Define("selJet_mass_"+sys+"Up","pre_selJet_mass_"+sys+"Up[goodJets_"+sys+"Up]")
               .Define("selJet_btagDeepFlavB_"+sys+"Up","pre_selJet_btagDeepFlavB_"+sys+"Up[goodJets_"+sys+"Up]")
    
               .Define("nselJets_"+sys+"Up","int(selJet_pt_"+sys+"Up.size())")
               .Define("nsel40Jets_"+sys+"Up","int(selJet40_pt_"+sys+"Up.size())")
               .Define("nsel80Jets_"+sys+"Up","int(selJet80_pt_"+sys+"Up.size())")
              
               .Define("jet4vecs_"+sys+"Up", ::generate_4vec, {"selJet_pt_"+sys+"Up", "selJet_eta_"+sys+"Up", "selJet_phi_"+sys+"Up", "selJet_mass_"+sys+"Up"});
    
    if(_year==2015){        //2016preVFP - APV
        _rlm = _rlm.Define("is_deepJet_T_"+sys+"Up","pre_selJet_btagDeepFlavB_"+sys+"Up > 0.6502");
        _rlm = _rlm.Define("is_deepJet_M_"+sys+"Up","pre_selJet_btagDeepFlavB_"+sys+"Up > 0.2598");
        _rlm = _rlm.Define("is_deepJet_L_"+sys+"Up","pre_selJet_btagDeepFlavB_"+sys+"Up > 0.0508");
    }else if (_year==2016){ //postVFP
        _rlm = _rlm.Define("is_deepJet_T_"+sys+"Up","pre_selJet_btagDeepFlavB_"+sys+"Up > 0.6377");
        _rlm = _rlm.Define("is_deepJet_M_"+sys+"Up","pre_selJet_btagDeepFlavB_"+sys+"Up > 0.2489");
        _rlm = _rlm.Define("is_deepJet_L_"+sys+"Up","pre_selJet_btagDeepFlavB_"+sys+"Up > 0.0480");
    }else if (_year==2017){
        _rlm = _rlm.Define("is_deepJet_T_"+sys+"Up","pre_selJet_btagDeepFlavB_"+sys+"Up > 0.7476");
        _rlm = _rlm.Define("is_deepJet_M_"+sys+"Up","pre_selJet_btagDeepFlavB_"+sys+"Up > 0.3040");
        _rlm = _rlm.Define("is_deepJet_L_"+sys+"Up","pre_selJet_btagDeepFlavB_"+sys+"Up > 0.0532");
    }else if(_year==2018){
        _rlm = _rlm.Define("is_deepJet_T_"+sys+"Up","pre_selJet_btagDeepFlavB_"+sys+"Up > 0.7100");
        _rlm = _rlm.Define("is_deepJet_M_"+sys+"Up","pre_selJet_btagDeepFlavB_"+sys+"Up > 0.2783");
        _rlm = _rlm.Define("is_deepJet_L_"+sys+"Up","pre_selJet_btagDeepFlavB_"+sys+"Up > 0.0490");
    }
    
    // for Chi2 reco
    if(_is3M){
        _rlm = _rlm.Define("goodbJets_"+sys+"Up", "goodJets_"+sys+"Up && abs(pre_selJet_eta_"+sys+"Up) < 2.5 && is_deepJet_M_"+sys+"Up");
    }else if(_is3T){
        _rlm = _rlm.Define("goodbJets_"+sys+"Up", "goodJets_"+sys+"Up && abs(pre_selJet_eta_"+sys+"Up) < 2.5 && is_deepJet_T_"+sys+"Up");
    }else{
        std::cout << "is 2M1L ?" << _is2M1L << std::endl;
        std::cout << "is 3L ?" << _is3L << std::endl;
        _rlm = _rlm.Define("goodbJets_"+sys+"Up", "goodJets_"+sys+"Up && abs(pre_selJet_eta_"+sys+"Up) < 2.5 && is_deepJet_L_"+sys+"Up");
    }
    
    _rlm = _rlm.Define("selbJet_pt_"+sys+"Up","pre_selJet_pt_"+sys+"Up[goodbJets_"+sys+"Up]")
               .Define("selbJet_eta_"+sys+"Up","pre_selJet_eta_"+sys+"Up[goodbJets_"+sys+"Up]")
               .Define("selbJet_phi_"+sys+"Up","pre_selJet_phi_"+sys+"Up[goodbJets_"+sys+"Up]")
               .Define("selbJet_mass_"+sys+"Up","pre_selJet_mass_"+sys+"Up[goodbJets_"+sys+"Up]")
               .Define("selbJet_btag_"+sys+"Up","pre_selJet_btagDeepFlavB_"+sys+"Up[goodbJets_"+sys+"Up]")
               .Define("nselbJets_"+sys+"Up","int(selbJet_pt_"+sys+"Up.size())")
               .Define("bjet4vecs_"+sys+"Up", ::generate_4vec, {"selbJet_pt_"+sys+"Up", "selbJet_eta_"+sys+"Up", "selbJet_phi_"+sys+"Up", "selbJet_mass_"+sys+"Up"});

    _rlm = _rlm.Define("goodLbJets_"+sys+"Up", "goodJets_"+sys+"Up && abs(pre_selJet_eta_"+sys+"Up) < 2.5 && is_deepJet_L_"+sys+"Up");
    _rlm = _rlm.Define("goodMbJets_"+sys+"Up", "goodJets_"+sys+"Up && abs(pre_selJet_eta_"+sys+"Up) < 2.5 && is_deepJet_M_"+sys+"Up");
    _rlm = _rlm.Define("goodTbJets_"+sys+"Up", "goodJets_"+sys+"Up && abs(pre_selJet_eta_"+sys+"Up) < 2.5 && is_deepJet_T_"+sys+"Up");
    
    _rlm = _rlm.Define("selLbJet_pt_"+sys+"Up","pre_selJet_pt_"+sys+"Up[goodLbJets_"+sys+"Up]")
               .Define("selLbJet_eta_"+sys+"Up","pre_selJet_eta_"+sys+"Up[goodLbJets_"+sys+"Up]")
               .Define("selLbJet_phi_"+sys+"Up","pre_selJet_phi_"+sys+"Up[goodLbJets_"+sys+"Up]")
               .Define("selLbJet_mass_"+sys+"Up","pre_selJet_mass_"+sys+"Up[goodLbJets_"+sys+"Up]")
               .Define("selLbJet_btag_"+sys+"Up","pre_selJet_btagDeepFlavB_"+sys+"Up[goodLbJets_"+sys+"Up]")
               .Define("nselLbJets_"+sys+"Up","int(selLbJet_pt_"+sys+"Up.size())")
               .Define("Lbjet4vecs_"+sys+"Up", ::generate_4vec, {"selLbJet_pt_"+sys+"Up", "selLbJet_eta_"+sys+"Up", "selLbJet_phi_"+sys+"Up", "selLbJet_mass_"+sys+"Up"});
    
    _rlm = _rlm.Define("selMbJet_pt_"+sys+"Up","pre_selJet_pt_"+sys+"Up[goodMbJets_"+sys+"Up]")
               .Define("selMbJet_eta_"+sys+"Up","pre_selJet_eta_"+sys+"Up[goodMbJets_"+sys+"Up]")
               .Define("selMbJet_phi_"+sys+"Up","pre_selJet_phi_"+sys+"Up[goodMbJets_"+sys+"Up]")
               .Define("selMbJet_mass_"+sys+"Up","pre_selJet_mass_"+sys+"Up[goodMbJets_"+sys+"Up]")
               .Define("selMbJet_btag_"+sys+"Up","pre_selJet_btagDeepFlavB_"+sys+"Up[goodMbJets_"+sys+"Up]")
               .Define("nselMbJets_"+sys+"Up","int(selMbJet_pt_"+sys+"Up.size())")
               .Define("Mbjet4vecs_"+sys+"Up", ::generate_4vec, {"selMbJet_pt_"+sys+"Up", "selMbJet_eta_"+sys+"Up", "selMbJet_phi_"+sys+"Up", "selMbJet_mass_"+sys+"Up"});
    
    _rlm = _rlm.Define("selTbJet_pt_"+sys+"Up","pre_selJet_pt_"+sys+"Up[goodTbJets_"+sys+"Up]")
               .Define("selTbJet_eta_"+sys+"Up","pre_selJet_eta_"+sys+"Up[goodTbJets_"+sys+"Up]")
               .Define("selTbJet_phi_"+sys+"Up","pre_selJet_phi_"+sys+"Up[goodTbJets_"+sys+"Up]")
               .Define("selTbJet_mass_"+sys+"Up","pre_selJet_mass_"+sys+"Up[goodTbJets_"+sys+"Up]")
               .Define("selTbJet_btag_"+sys+"Up","pre_selJet_btagDeepFlavB_"+sys+"Up[goodTbJets_"+sys+"Up]")
               .Define("nselTbJets_"+sys+"Up","int(selTbJet_pt_"+sys+"Up.size())")
               .Define("Tbjet4vecs_"+sys+"Up", ::generate_4vec, {"selTbJet_pt_"+sys+"Up", "selTbJet_eta_"+sys+"Up", "selTbJet_phi_"+sys+"Up", "selTbJet_mass_"+sys+"Up"});

    // Function for kinematic reconstruction
    _rlm = _rlm.Define("Chi2_Tprime_"+sys+"Up",::Tprime_reconstruction,{"jet4vecs_"+sys+"Up","bjet4vecs_"+sys+"Up"})
               .Define("Chi2_min_"+sys+"Up","Chi2_Tprime_"+sys+"Up[6]")
               .Define("Chi2_max_"+sys+"Up","Chi2_Tprime_"+sys+"Up[17]");
    
    // Extra Variables for analysis
    _rlm = _rlm.Define("Higgs4vecs_"+sys+"Up","(bjet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[0]]+bjet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[1]])")
               .Define("W4vecs_"+sys+"Up","(jet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[2]]+jet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[3]])")
               .Define("Top4vecs_"+sys+"Up","(W4vecs_"+sys+"Up+bjet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[4]])")
               .Define("secondTop4vecs_"+sys+"Up","(bjet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[0]]+bjet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[1]]+jet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[5]])")
               .Define("TopWvecs_"+sys+"Up","W4vecs_"+sys+"Up+Top4vecs_"+sys+"Up")
               .Define("Tprime4vecs_"+sys+"Up","(bjet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[0]]+bjet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[1]]+jet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[2]]+jet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[3]]+bjet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[4]])");
    
    // materials...
    _rlm = _rlm.Define("recoTprime_cand_eta_"+sys+"Up","float(Tprime4vecs_"+sys+"Up.Eta())")
               .Define("recoTprime_cand_phi_"+sys+"Up","float(Tprime4vecs_"+sys+"Up.Phi())")
               .Define("recoTprime_cand_pt_"+sys+"Up","float(Tprime4vecs_"+sys+"Up.Pt())")
    
               .Define("recoHiggs_cand_eta_"+sys+"Up","float(Higgs4vecs_"+sys+"Up.Eta())")
               .Define("recoHiggs_cand_phi_"+sys+"Up","float(Higgs4vecs_"+sys+"Up.Phi())")
               .Define("recoHiggs_cand_pt_"+sys+"Up","float(Higgs4vecs_"+sys+"Up.Pt())")
    
               .Define("recoTop_cand_eta_"+sys+"Up","float(Top4vecs_"+sys+"Up.Eta())")
               .Define("recoTop_cand_phi_"+sys+"Up","float(Top4vecs_"+sys+"Up.Phi())")
               .Define("recoTop_cand_pt_"+sys+"Up","float(Top4vecs_"+sys+"Up.Pt())")
    
               .Define("recosecondTop_cand_pt_"+sys+"Up","float(secondTop4vecs_"+sys+"Up.Pt())")
    
               .Define("recoW_cand_eta_"+sys+"Up","float(W4vecs_"+sys+"Up.Eta())")
               .Define("recoW_cand_phi_"+sys+"Up","float(W4vecs_"+sys+"Up.Phi())")
               .Define("recoW_cand_pt_"+sys+"Up","float(W4vecs_"+sys+"Up.Pt())");
    
    _rlm = _rlm.Define("recob1_Higgs_cand_eta_"+sys+"Up","float(bjet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[0]].Eta())")
               .Define("recob1_Higgs_cand_phi_"+sys+"Up","float(bjet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[0]].Phi())")
               .Define("recob1_Higgs_cand_pt_"+sys+"Up","float(bjet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[0]].Pt())")
               .Define("recob2_Higgs_cand_eta_"+sys+"Up","float(bjet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[1]].Eta())")
               .Define("recob2_Higgs_cand_phi_"+sys+"Up","float(bjet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[1]].Phi())")
               .Define("recob2_Higgs_cand_pt_"+sys+"Up","float(bjet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[1]].Pt())")
    
               .Define("recoj1_W_cand_eta_"+sys+"Up","float(jet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[2]].Eta())")
               .Define("recoj1_W_cand_phi_"+sys+"Up","float(jet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[2]].Phi())")
               .Define("recoj1_W_cand_pt_"+sys+"Up","float(jet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[2]].Pt())")
               .Define("recoj2_W_cand_eta_"+sys+"Up","float(jet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[3]].Eta())")
               .Define("recoj2_W_cand_phi_"+sys+"Up","float(jet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[3]].Phi())")
               .Define("recoj2_W_cand_pt_"+sys+"Up","float(jet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[3]].Pt())")
    
               .Define("recoj_bFromTop_cand_eta_"+sys+"Up","float(bjet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[4]].Eta())")
               .Define("recoj_bFromTop_cand_phi_"+sys+"Up","float(bjet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[4]].Phi())")
               .Define("recoj_bFromTop_cand_pt_"+sys+"Up","float(bjet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[4]].Pt())")
    
               .Define("reco_otherj_cand_eta_"+sys+"Up","float(jet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[5]].Eta())")
               .Define("reco_otherj_cand_phi_"+sys+"Up","float(jet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[5]].Phi())")
               .Define("reco_otherj_cand_pt_"+sys+"Up","float(jet4vecs_"+sys+"Up[Chi2_Tprime_"+sys+"Up[5]].Pt())");
    
    // Kinematic reconstructions
    _rlm = _rlm.Define("invmass_leadjets_"+sys+"Up", "(jet4vecs_"+sys+"Up[0]+jet4vecs_"+sys+"Up[1]+jet4vecs_"+sys+"Up[2]+jet4vecs_"+sys+"Up[3]+jet4vecs_"+sys+"Up[4]).M()");
    
    _rlm = _rlm.Define("HT6_"+sys+"Up","(selJet_pt_"+sys+"Up[0]+selJet_pt_"+sys+"Up[1]+selJet_pt_"+sys+"Up[2]+selJet_pt_"+sys+"Up[3]+selJet_pt_"+sys+"Up[4]+selJet_pt_"+sys+"Up[5])") 
               .Define("goodHT_"+sys+"Up",::calculate_goodHT, {"selJet_pt_"+sys+"Up"})
               .Define("RelHT_"+sys+"Up",::calculate_RelHT, {"Top4vecs_"+sys+"Up","Higgs4vecs_"+sys+"Up","goodHT_"+sys+"Up"})
               .Define("sixthJet_pt_"+sys+"Up","selJet_pt_"+sys+"Up[5]")
               .Define("newRelHT_"+sys+"Up", ::calculate_newRelHT, {"Top4vecs_"+sys+"Up","Higgs4vecs_"+sys+"Up","sixthJet_pt_"+sys+"Up","goodHT_"+sys+"Up"});
    
    _rlm = _rlm.Define("dRHbb_chi2_"+sys+"Up","ROOT::VecOps::DeltaR(recob1_Higgs_cand_eta_"+sys+"Up,recob2_Higgs_cand_eta_"+sys+"Up,recob1_Higgs_cand_phi_"+sys+"Up,recob2_Higgs_cand_phi_"+sys+"Up)")
               .Define("dRWjj_chi2_"+sys+"Up","ROOT::VecOps::DeltaR(recoj1_W_cand_eta_"+sys+"Up,recoj2_W_cand_eta_"+sys+"Up,recoj1_W_cand_phi_"+sys+"Up,recoj2_W_cand_phi_"+sys+"Up)")
               .Define("dRbW_chi2_"+sys+"Up","ROOT::VecOps::DeltaR(recoW_cand_eta_"+sys+"Up,recoj_bFromTop_cand_eta_"+sys+"Up,recoW_cand_phi_"+sys+"Up,recoj_bFromTop_cand_phi_"+sys+"Up)"); 
    
    _rlm = _rlm.Define("dRTprimeoj_chi2_"+sys+"Up","ROOT::VecOps::DeltaR(recoTprime_cand_eta_"+sys+"Up,reco_otherj_cand_eta_"+sys+"Up,recoTprime_cand_phi_"+sys+"Up,reco_otherj_cand_phi_"+sys+"Up)")
               .Define("dRHTop_chi2_"+sys+"Up","ROOT::VecOps::DeltaR(recoHiggs_cand_eta_"+sys+"Up,recoTop_cand_eta_"+sys+"Up,recoHiggs_cand_phi_"+sys+"Up,recoTop_cand_phi_"+sys+"Up)");
    
    _rlm = _rlm.Define("Rpt_Top2ndTop_"+sys+"Up","(recosecondTop_cand_pt_"+sys+"Up - recoTop_cand_pt_"+sys+"Up) / recosecondTop_cand_pt_"+sys+"Up")
               .Define("Rpt_HTopTprime_"+sys+"Up","(recoHiggs_cand_pt_"+sys+"Up - recoTop_cand_pt_"+sys+"Up) / recoTprime_cand_pt_"+sys+"Up")
               .Define("Rpt_TprimeHTprimeTop_"+sys+"Up","(recoTprime_cand_pt_"+sys+"Up / recoHiggs_cand_pt_"+sys+"Up) - (recoTprime_cand_pt_"+sys+"Up / recoTop_cand_pt_"+sys+"Up)");


    // Down..
    _rlm = _rlm.Define("pre_goodJets_"+sys+"Dn", "Jet_jetId > 1 && Jet_pt_smear_"+sys+"Dn >= 30 && abs(Jet_eta) <= 2.5 && (Jet_pt_smear_"+sys+"Dn > 50 || Jet_puId > 0)");
    
    _rlm = _rlm.Define("pre_nselJets_"+sys+"Dn","Sum(pre_goodJets_"+sys+"Dn)")
               .Define("pre_selJet_pt_"+sys+"Dn","Jet_pt_smear_"+sys+"Dn[pre_goodJets_"+sys+"Dn]")
               .Define("pre_selJet_eta_"+sys+"Dn","Jet_eta[pre_goodJets_"+sys+"Dn]")
               .Define("pre_selJet_phi_"+sys+"Dn","Jet_phi[pre_goodJets_"+sys+"Dn]")
               .Define("pre_selJet_mass_"+sys+"Dn","Jet_mass[pre_goodJets_"+sys+"Dn]")
               .Define("pre_selJet_btagDeepFlavB_"+sys+"Dn","Jet_btagDeepFlavB[pre_goodJets_"+sys+"Dn]")
               .Define("pre_jet4vecs_"+sys+"Dn", ::generate_4vec, {"pre_selJet_pt_"+sys+"Dn", "pre_selJet_eta_"+sys+"Dn", "pre_selJet_phi_"+sys+"Dn", "pre_selJet_mass_"+sys+"Dn"});
    
    _rlm = _rlm.Define("mindrlepton_"+sys+"Dn",checkoverlap,{"pre_jet4vecs_"+sys+"Dn","goodMuons_4vecs","goodElectrons_4vecs"});
    
    _rlm = _rlm.Define("goodJets_"+sys+"Dn", "mindrlepton_"+sys+"Dn > 0.4")
               .Define("good40Jets_"+sys+"Dn", "goodJets_"+sys+"Dn && pre_selJet_pt_"+sys+"Dn >= 40")
               .Define("good80Jets_"+sys+"Dn", "good40Jets_"+sys+"Dn && pre_selJet_pt_"+sys+"Dn >= 80");
    
    _rlm = _rlm.Define("selJet_pt_"+sys+"Dn","pre_selJet_pt_"+sys+"Dn[goodJets_"+sys+"Dn]")
               .Define("selJet40_pt_"+sys+"Dn","pre_selJet_pt_"+sys+"Dn[good40Jets_"+sys+"Dn]")
               .Define("selJet80_pt_"+sys+"Dn","pre_selJet_pt_"+sys+"Dn[good80Jets_"+sys+"Dn]")
              
               .Define("selJet_eta_"+sys+"Dn","pre_selJet_eta_"+sys+"Dn[goodJets_"+sys+"Dn]")
               .Define("selJet_phi_"+sys+"Dn","pre_selJet_phi_"+sys+"Dn[goodJets_"+sys+"Dn]")
               .Define("selJet_mass_"+sys+"Dn","pre_selJet_mass_"+sys+"Dn[goodJets_"+sys+"Dn]")
               .Define("selJet_btagDeepFlavB_"+sys+"Dn","pre_selJet_btagDeepFlavB_"+sys+"Dn[goodJets_"+sys+"Dn]")
    
               .Define("nselJets_"+sys+"Dn","int(selJet_pt_"+sys+"Dn.size())")
               .Define("nsel40Jets_"+sys+"Dn","int(selJet40_pt_"+sys+"Dn.size())")
               .Define("nsel80Jets_"+sys+"Dn","int(selJet80_pt_"+sys+"Dn.size())")
              
               .Define("jet4vecs_"+sys+"Dn", ::generate_4vec, {"selJet_pt_"+sys+"Dn", "selJet_eta_"+sys+"Dn", "selJet_phi_"+sys+"Dn", "selJet_mass_"+sys+"Dn"});
    
    if(_year==2015){        //2016preVFP - APV
        _rlm = _rlm.Define("is_deepJet_T_"+sys+"Dn","pre_selJet_btagDeepFlavB_"+sys+"Dn > 0.6502");
        _rlm = _rlm.Define("is_deepJet_M_"+sys+"Dn","pre_selJet_btagDeepFlavB_"+sys+"Dn > 0.2598");
        _rlm = _rlm.Define("is_deepJet_L_"+sys+"Dn","pre_selJet_btagDeepFlavB_"+sys+"Dn > 0.0508");
    }else if (_year==2016){ //postVFP
        _rlm = _rlm.Define("is_deepJet_T_"+sys+"Dn","pre_selJet_btagDeepFlavB_"+sys+"Dn > 0.6377");
        _rlm = _rlm.Define("is_deepJet_M_"+sys+"Dn","pre_selJet_btagDeepFlavB_"+sys+"Dn > 0.2489");
        _rlm = _rlm.Define("is_deepJet_L_"+sys+"Dn","pre_selJet_btagDeepFlavB_"+sys+"Dn > 0.0480");
    }else if (_year==2017){
        _rlm = _rlm.Define("is_deepJet_T_"+sys+"Dn","pre_selJet_btagDeepFlavB_"+sys+"Dn > 0.7476");
        _rlm = _rlm.Define("is_deepJet_M_"+sys+"Dn","pre_selJet_btagDeepFlavB_"+sys+"Dn > 0.3040");
        _rlm = _rlm.Define("is_deepJet_L_"+sys+"Dn","pre_selJet_btagDeepFlavB_"+sys+"Dn > 0.0532");
    }else if(_year==2018){
        _rlm = _rlm.Define("is_deepJet_T_"+sys+"Dn","pre_selJet_btagDeepFlavB_"+sys+"Dn > 0.7100");
        _rlm = _rlm.Define("is_deepJet_M_"+sys+"Dn","pre_selJet_btagDeepFlavB_"+sys+"Dn > 0.2783");
        _rlm = _rlm.Define("is_deepJet_L_"+sys+"Dn","pre_selJet_btagDeepFlavB_"+sys+"Dn > 0.0490");
    }
    
    // for Chi2 reco
    if(_is3M){
        _rlm = _rlm.Define("goodbJets_"+sys+"Dn", "goodJets_"+sys+"Dn && abs(pre_selJet_eta_"+sys+"Dn) < 2.5 && is_deepJet_M_"+sys+"Dn");
    }else if(_is3T){
        _rlm = _rlm.Define("goodbJets_"+sys+"Dn", "goodJets_"+sys+"Dn && abs(pre_selJet_eta_"+sys+"Dn) < 2.5 && is_deepJet_T_"+sys+"Dn");
    }else{
        std::cout << "is 2M1L ?" << _is2M1L << std::endl;
        std::cout << "is 3L ?" << _is3L << std::endl;
        _rlm = _rlm.Define("goodbJets_"+sys+"Dn", "goodJets_"+sys+"Dn && abs(pre_selJet_eta_"+sys+"Dn) < 2.5 && is_deepJet_L_"+sys+"Dn");
    }

    _rlm = _rlm.Define("selbJet_pt_"+sys+"Dn","pre_selJet_pt_"+sys+"Dn[goodbJets_"+sys+"Dn]")
               .Define("selbJet_eta_"+sys+"Dn","pre_selJet_eta_"+sys+"Dn[goodbJets_"+sys+"Dn]")
               .Define("selbJet_phi_"+sys+"Dn","pre_selJet_phi_"+sys+"Dn[goodbJets_"+sys+"Dn]")
               .Define("selbJet_mass_"+sys+"Dn","pre_selJet_mass_"+sys+"Dn[goodbJets_"+sys+"Dn]")
               .Define("selbJet_btag_"+sys+"Dn","pre_selJet_btagDeepFlavB_"+sys+"Dn[goodbJets_"+sys+"Dn]")
               .Define("nselbJets_"+sys+"Dn","int(selbJet_pt_"+sys+"Dn.size())")
               .Define("bjet4vecs_"+sys+"Dn", ::generate_4vec, {"selbJet_pt_"+sys+"Dn", "selbJet_eta_"+sys+"Dn", "selbJet_phi_"+sys+"Dn", "selbJet_mass_"+sys+"Dn"});

    // Function for kinematic reconstruction
    _rlm = _rlm.Define("Chi2_Tprime_"+sys+"Dn",::Tprime_reconstruction,{"jet4vecs_"+sys+"Dn","bjet4vecs_"+sys+"Dn"})
               .Define("Chi2_min_"+sys+"Dn","Chi2_Tprime_"+sys+"Dn[6]")
               .Define("Chi2_max_"+sys+"Dn","Chi2_Tprime_"+sys+"Dn[17]");
    
    // Extra Variables for analysis
    _rlm = _rlm.Define("Higgs4vecs_"+sys+"Dn","(bjet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[0]]+bjet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[1]])")
               .Define("W4vecs_"+sys+"Dn","(jet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[2]]+jet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[3]])")
               .Define("Top4vecs_"+sys+"Dn","(W4vecs_"+sys+"Dn+bjet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[4]])")
               .Define("secondTop4vecs_"+sys+"Dn","(bjet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[0]]+bjet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[1]]+jet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[5]])")
               .Define("TopWvecs_"+sys+"Dn","W4vecs_"+sys+"Dn+Top4vecs_"+sys+"Dn")
               .Define("Tprime4vecs_"+sys+"Dn","(bjet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[0]]+bjet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[1]]+jet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[2]]+jet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[3]]+bjet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[4]])");
    
    // materials...
    _rlm = _rlm.Define("recoTprime_cand_eta_"+sys+"Dn","float(Tprime4vecs_"+sys+"Dn.Eta())")
               .Define("recoTprime_cand_phi_"+sys+"Dn","float(Tprime4vecs_"+sys+"Dn.Phi())")
               .Define("recoTprime_cand_pt_"+sys+"Dn","float(Tprime4vecs_"+sys+"Dn.Pt())")
    
               .Define("recoHiggs_cand_eta_"+sys+"Dn","float(Higgs4vecs_"+sys+"Dn.Eta())")
               .Define("recoHiggs_cand_phi_"+sys+"Dn","float(Higgs4vecs_"+sys+"Dn.Phi())")
               .Define("recoHiggs_cand_pt_"+sys+"Dn","float(Higgs4vecs_"+sys+"Dn.Pt())")
    
               .Define("recoTop_cand_eta_"+sys+"Dn","float(Top4vecs_"+sys+"Dn.Eta())")
               .Define("recoTop_cand_phi_"+sys+"Dn","float(Top4vecs_"+sys+"Dn.Phi())")
               .Define("recoTop_cand_pt_"+sys+"Dn","float(Top4vecs_"+sys+"Dn.Pt())")
    
               .Define("recosecondTop_cand_pt_"+sys+"Dn","float(secondTop4vecs_"+sys+"Dn.Pt())")
    
               .Define("recoW_cand_eta_"+sys+"Dn","float(W4vecs_"+sys+"Dn.Eta())")
               .Define("recoW_cand_phi_"+sys+"Dn","float(W4vecs_"+sys+"Dn.Phi())")
               .Define("recoW_cand_pt_"+sys+"Dn","float(W4vecs_"+sys+"Dn.Pt())");
    
    _rlm = _rlm.Define("recob1_Higgs_cand_eta_"+sys+"Dn","float(bjet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[0]].Eta())")
               .Define("recob1_Higgs_cand_phi_"+sys+"Dn","float(bjet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[0]].Phi())")
               .Define("recob1_Higgs_cand_pt_"+sys+"Dn","float(bjet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[0]].Pt())")
               .Define("recob2_Higgs_cand_eta_"+sys+"Dn","float(bjet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[1]].Eta())")
               .Define("recob2_Higgs_cand_phi_"+sys+"Dn","float(bjet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[1]].Phi())")
               .Define("recob2_Higgs_cand_pt_"+sys+"Dn","float(bjet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[1]].Pt())")
    
               .Define("recoj1_W_cand_eta_"+sys+"Dn","float(jet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[2]].Eta())")
               .Define("recoj1_W_cand_phi_"+sys+"Dn","float(jet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[2]].Phi())")
               .Define("recoj1_W_cand_pt_"+sys+"Dn","float(jet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[2]].Pt())")
               .Define("recoj2_W_cand_eta_"+sys+"Dn","float(jet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[3]].Eta())")
               .Define("recoj2_W_cand_phi_"+sys+"Dn","float(jet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[3]].Phi())")
               .Define("recoj2_W_cand_pt_"+sys+"Dn","float(jet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[3]].Pt())")
    
               .Define("recoj_bFromTop_cand_eta_"+sys+"Dn","float(bjet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[4]].Eta())")
               .Define("recoj_bFromTop_cand_phi_"+sys+"Dn","float(bjet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[4]].Phi())")
               .Define("recoj_bFromTop_cand_pt_"+sys+"Dn","float(bjet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[4]].Pt())")
    
               .Define("reco_otherj_cand_eta_"+sys+"Dn","float(jet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[5]].Eta())")
               .Define("reco_otherj_cand_phi_"+sys+"Dn","float(jet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[5]].Phi())")
               .Define("reco_otherj_cand_pt_"+sys+"Dn","float(jet4vecs_"+sys+"Dn[Chi2_Tprime_"+sys+"Dn[5]].Pt())");
    
    // Kinematic reconstructions
    _rlm = _rlm.Define("invmass_leadjets_"+sys+"Dn", "(jet4vecs_"+sys+"Dn[0]+jet4vecs_"+sys+"Dn[1]+jet4vecs_"+sys+"Dn[2]+jet4vecs_"+sys+"Dn[3]+jet4vecs_"+sys+"Dn[4]).M()");
    
    _rlm = _rlm.Define("HT6_"+sys+"Dn","(selJet_pt_"+sys+"Dn[0]+selJet_pt_"+sys+"Dn[1]+selJet_pt_"+sys+"Dn[2]+selJet_pt_"+sys+"Dn[3]+selJet_pt_"+sys+"Dn[4]+selJet_pt_"+sys+"Dn[5])") 
               .Define("goodHT_"+sys+"Dn",::calculate_goodHT, {"selJet_pt_"+sys+"Dn"})
               .Define("RelHT_"+sys+"Dn",::calculate_RelHT, {"Top4vecs_"+sys+"Dn","Higgs4vecs_"+sys+"Dn","goodHT_"+sys+"Dn"})
               .Define("sixthJet_pt_"+sys+"Dn","selJet_pt_"+sys+"Dn[5]")
               .Define("newRelHT_"+sys+"Dn", ::calculate_newRelHT, {"Top4vecs_"+sys+"Dn","Higgs4vecs_"+sys+"Dn","sixthJet_pt_"+sys+"Dn","goodHT_"+sys+"Dn"});
    
    _rlm = _rlm.Define("dRHbb_chi2_"+sys+"Dn","ROOT::VecOps::DeltaR(recob1_Higgs_cand_eta_"+sys+"Dn,recob2_Higgs_cand_eta_"+sys+"Dn,recob1_Higgs_cand_phi_"+sys+"Dn,recob2_Higgs_cand_phi_"+sys+"Dn)")
               .Define("dRWjj_chi2_"+sys+"Dn","ROOT::VecOps::DeltaR(recoj1_W_cand_eta_"+sys+"Dn,recoj2_W_cand_eta_"+sys+"Dn,recoj1_W_cand_phi_"+sys+"Dn,recoj2_W_cand_phi_"+sys+"Dn)")
               .Define("dRbW_chi2_"+sys+"Dn","ROOT::VecOps::DeltaR(recoW_cand_eta_"+sys+"Dn,recoj_bFromTop_cand_eta_"+sys+"Dn,recoW_cand_phi_"+sys+"Dn,recoj_bFromTop_cand_phi_"+sys+"Dn)"); 
    
    _rlm = _rlm.Define("dRTprimeoj_chi2_"+sys+"Dn","ROOT::VecOps::DeltaR(recoTprime_cand_eta_"+sys+"Dn,reco_otherj_cand_eta_"+sys+"Dn,recoTprime_cand_phi_"+sys+"Dn,reco_otherj_cand_phi_"+sys+"Dn)")
               .Define("dRHTop_chi2_"+sys+"Dn","ROOT::VecOps::DeltaR(recoHiggs_cand_eta_"+sys+"Dn,recoTop_cand_eta_"+sys+"Dn,recoHiggs_cand_phi_"+sys+"Dn,recoTop_cand_phi_"+sys+"Dn)");
    
    _rlm = _rlm.Define("Rpt_Top2ndTop_"+sys+"Dn","(recosecondTop_cand_pt_"+sys+"Dn - recoTop_cand_pt_"+sys+"Dn) / recosecondTop_cand_pt_"+sys+"Dn")
               .Define("Rpt_HTopTprime_"+sys+"Dn","(recoHiggs_cand_pt_"+sys+"Dn - recoTop_cand_pt_"+sys+"Dn) / recoTprime_cand_pt_"+sys+"Dn")
               .Define("Rpt_TprimeHTprimeTop_"+sys+"Dn","(recoTprime_cand_pt_"+sys+"Dn / recoHiggs_cand_pt_"+sys+"Dn) - (recoTprime_cand_pt_"+sys+"Dn / recoTop_cand_pt_"+sys+"Dn)");

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
