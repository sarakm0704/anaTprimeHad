/*
 * TprimeHadAnalyzer.cpp: subclas -> inherited from main class NanoAODAnalyzerrdframe (Created on: Sep 30, 2018-Author: suyong)
 *
 *  Created on: Dec 18, 2021
 *    modified: Jieun
 */

#include "TprimeHadAnalyzer.h"
#include "utility.h"
#include "Math/GenVector/VectorUtil.h"
//#include "Math/Math.h"

TprimeHadAnalyzer::TprimeHadAnalyzer(TTree *t, std::string outfilename, std::string year, std::string runtype,std::string syst, std::string jsonfname, string globaltag, int nthreads,int isDATA)
:NanoAODAnalyzerrdframe(t, outfilename, year, runtype,syst, jsonfname, globaltag, nthreads, isDATA)
{

}
//=============================Event Selection==================================================//
//Perform a selection on the minimal requirements of an event
// Define your base selection cuts in the "defineCuts()" function
// Cuts to be applied in order
// These will be passed to Filter method of RDF
//==============================================================================================//
void TprimeHadAnalyzer::defineCuts()
{  //cut on number of good muons/electrons/jets in an event/ && triggers/ etc..
  
  // for DNN
  //addCuts("isHadTprime","0");
  //addCuts("HLT && nselJets >= 6 && nselbJets >= 3","00");

  // Purity
  //addCuts("(nJetFromW + nJetFromH + nJetFromTop) > 4","00");


  // Cut 0
  addCuts("HLT && nsel40Jets >= 6 && nsel80Jets >= 3 && nselbJets >= 3","0");
  addCuts("selJet_pt[0] > 170 && selJet_pt[1] > 130 && selJet_pt[2] > 80 && goodHT > 500","00");
  //addCuts("HLT && nsel40Jets >= 6 && nsel80Jets >= 3 && nselbJets >= 3 && selJet_pt[0] > 170 && selJet_pt[1] > 130 && selJet_pt[2] > 80 && goodHT > 500","00");
  addCuts("Chi2_min < 15 && invmass_2ndTop > 250 && H_mass > 100","000");
  ////addCuts("HLT && nsel40Jets >= 6 && nsel80Jets >= 3 && nselbJets >= 3 && selJet_pt[0] > 170 && selJet_pt[1] > 130 && selJet_pt[2] > 80 && goodHT > 500 && Chi2_min < 15 && invmass_2ndTop > 250 && H_mass > 100","00");
  ////addCuts("(nJetFromW + nJetFromH + nJetFromTop) > 4","000");


  //// Cut1-6
  ////addCuts("RelHT > 0.4",         "0000");      //1
  ////addCuts("Chi2_max < 3",        "00000");     //2
  ////addCuts("dRHbb_chi2 < 1.1",    "000000");    //3
  ////addCuts("Chi2_min_H < 1.5",    "0000000");   //4
  ////addCuts("dRWjj_chi2 < 1.75",   "00000000");  //5
  ////addCuts("dRbW_chi2 < 1.2",     "000000000"); //6

}
//.=============================define variables==================================================//
//define your higher level variables here   
// :final state particle variables (muon/electron/jet/tau/etc.)-> mass/pt/eta/phi
// :reconstructed pair variables (dijet/w/top/dimuon/etc..)-> invariant mass/DR/Deta/Dphi
//==============================================================================================//
void TprimeHadAnalyzer::defineMoreVars()
{
  addVar({"HLT","HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 || HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 || HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5 || HLT_PFHT1050 || HLT_PFJet500 || HLT_PFJet550",""});
 
  //defineVar("Chi2_Tprime",::Tprime_reconstruction,{"jet4vecs","bjet4vecs"});

  //addVar({"invmass_chi2jets", "(abs(gate) < 10E+20) ? -1 : gate"});

  addVar({"Chi2_min_H","Chi2_Tprime[7]",""});
  addVar({"Chi2_min_W","Chi2_Tprime[8]",""});
  addVar({"Chi2_min_Top","Chi2_Tprime[9]",""});

  addVar({"H_mass","Chi2_Tprime[10]",""});
  addVar({"W_mass","Chi2_Tprime[11]",""});
  addVar({"Top_mass","Chi2_Tprime[12]",""});

  addVar({"Chi2_max_H","Chi2_Tprime[14]",""});
  addVar({"Chi2_max_W","Chi2_Tprime[15]",""});
  addVar({"Chi2_max_Top","Chi2_Tprime[16]",""});
  
  defineVar("mindR_bb",::mindR_bb,{"bjet4vecs"});
  defineVar("dRbb",::dR_bb,{"bjet4vecs"});
  defineVar("mbb",::m_bb,{"bjet4vecs"});
  addVar({"mindR_dRbb","mindR_bb[0]",""});
  addVar({"mindR_mbb","mindR_bb[1]",""});

  addVar({"selJet1_pt","selJet_pt[0]",""});
  addVar({"selJet1_pt_massnom","selJet1_pt/invmass_chi2jets",""});
  addVar({"selJet1_pt_htnom","selJet1_pt/goodHT",""});
  addVar({"selJet1_eta","selJet_eta[0]",""});
  addVar({"selJet1_phi","selJet_phi[0]",""});
  addVar({"selJet1_mass","selJet_mass[0]",""});
  addVar({"selJet1_btagDeepB","selJet_btagDeepB[0]",""});
  addVar({"selJet1_e","jet4vecs[0].E()",""});
  addVar({"selJet1_e_massnom","selJet1_e/invmass_chi2jets",""});
  addVar({"selJet1_e_htnom","selJet1_e/goodHT",""});

  addVar({"selJet2_pt","selJet_pt[1]",""});
  addVar({"selJet2_pt_massnom","selJet2_pt/invmass_chi2jets",""});
  addVar({"selJet2_pt_htnom","selJet2_pt/goodHT",""});
  addVar({"selJet2_eta","selJet_eta[1]",""});
  addVar({"selJet2_phi","selJet_phi[1]",""});
  addVar({"selJet2_mass","selJet_mass[1]",""});
  addVar({"selJet2_btagDeepB","selJet_btagDeepB[1]",""});
  addVar({"selJet2_e","jet4vecs[1].E()",""});
  addVar({"selJet2_e_massnom","selJet2_e/invmass_chi2jets",""});
  addVar({"selJet2_e_htnom","selJet2_e/goodHT",""});

  addVar({"selJet3_pt","selJet_pt[2]",""});
  addVar({"selJet3_pt_massnom","selJet3_pt/invmass_chi2jets",""});
  addVar({"selJet3_pt_htnom","selJet3_pt/goodHT",""});
  addVar({"selJet3_eta","selJet_eta[2]",""});
  addVar({"selJet3_phi","selJet_phi[2]",""});
  addVar({"selJet3_mass","selJet_mass[2]",""});
  addVar({"selJet3_btagDeepB","selJet_btagDeepB[2]",""});
  addVar({"selJet3_e","jet4vecs[2].E()",""});
  addVar({"selJet3_e_massnom","selJet3_e/invmass_chi2jets",""});
  addVar({"selJet3_e_htnom","selJet3_e/goodHT",""});

  addVar({"selJet4_pt","selJet_pt[3]",""});
  addVar({"selJet4_pt_massnom","selJet4_pt/invmass_chi2jets",""});
  addVar({"selJet4_pt_htnom","selJet4_pt/goodHT",""});
  addVar({"selJet4_eta","selJet_eta[3]",""});
  addVar({"selJet4_phi","selJet_phi[3]",""});
  addVar({"selJet4_mass","selJet_mass[3]",""});
  addVar({"selJet4_btagDeepB","selJet_btagDeepB[3]",""});
  addVar({"selJet4_e","jet4vecs[3].E()",""});
  addVar({"selJet4_e_massnom","selJet4_e/invmass_chi2jets",""});
  addVar({"selJet4_e_htnom","selJet4_e/goodHT",""});

  addVar({"selJet5_pt","selJet_pt[4]",""});
  addVar({"selJet5_pt_massnom","selJet5_pt/invmass_chi2jets",""});
  addVar({"selJet5_pt_htnom","selJet5_pt/goodHT",""});
  addVar({"selJet5_eta","selJet_eta[4]",""});
  addVar({"selJet5_phi","selJet_phi[4]",""});
  addVar({"selJet5_mass","selJet_mass[4]",""});
  addVar({"selJet5_btagDeepB","selJet_btagDeepB[4]",""});
  addVar({"selJet5_e","jet4vecs[4].E()",""});
  addVar({"selJet5_e_massnom","selJet5_e/invmass_chi2jets",""});
  addVar({"selJet5_e_htnom","selJet5_e/goodHT",""});

  addVar({"selbJet1_pt","selbJet_pt[0]",""});
  addVar({"selbJet1_pt_massnom","selbJet1_pt/invmass_chi2jets",""});
  addVar({"selbJet1_pt_htnom","selbJet1_pt/goodHT",""});
  addVar({"selbJet1_eta","selbJet_eta[0]",""});
  addVar({"selbJet1_phi","selbJet_phi[0]",""});
  addVar({"selbJet1_mass","selbJet_mass[0]",""});
  addVar({"selbJet1_btagDeepB","selbJet_btagDeepB[0]",""});
  addVar({"selbJet1_e","bjet4vecs[0].E()",""});
  addVar({"selbJet1_e_massnom","selbJet1_e/invmass_chi2jets",""});
  addVar({"selbJet1_e_htnom","selbJet1_e/goodHT",""});

  addVar({"selbJet2_pt","selbJet_pt[1]",""});
  addVar({"selbJet2_pt_massnom","selbJet2_pt/invmass_chi2jets",""});
  addVar({"selbJet2_pt_htnom","selbJet2_pt/goodHT",""});
  addVar({"selbJet2_eta","selbJet_eta[1]",""});
  addVar({"selbJet2_phi","selbJet_phi[1]",""});
  addVar({"selbJet2_mass","selbJet_mass[1]",""});
  addVar({"selbJet2_btagDeepB","selbJet_btagDeepB[1]",""});
  addVar({"selbJet2_e","bjet4vecs[1].E()",""});
  addVar({"selbJet2_e_massnom","selbJet2_e/invmass_chi2jets",""});
  addVar({"selbJet2_e_htnom","selbJet2_e/goodHT",""});

  addVar({"goodHT_massnom","goodHT/invmass_chi2jets",""});
  addVar({"invmass_htnom","invmass_chi2jets/goodHT",""});

  //addVar({"selbJet4_pt","selbJet_pt[3]",""});
  //addVar({"selbJet4_eta","selbJet_eta[3]",""});
  //addVar({"selbJet4_phi","selbJet_phi[3]",""});
  //addVar({"selbJet4_mass","selbJet_mass[3]",""});
  //addVar({"selbJet4_btagDeepB","selbJet_btagDeepB[3]",""});
  //addVar({"selbJet3_e","bjet4vecs[2].E()",""});

  //================================Store variables in tree=======================================//
  // define variables that you want to store
  //==============================================================================================//
  addVartoStore("nJetFromW");
  addVartoStore("nJetFromTop");
  addVartoStore("nJetFromH");

  addVartoStore("run");
  addVartoStore("luminosityBlock");
  addVartoStore("event");
  addVartoStore("evWeight.*");

  addVartoStore("HLT");

  addVartoStore("Chi2_max");
  addVartoStore("Chi2_min");
  addVartoStore("Chi2_min_H");
  addVartoStore("Chi2_min_W");
  addVartoStore("Chi2_min_Top");
  
  addVartoStore("H_mass");
  addVartoStore("W_mass");
  addVartoStore("Top_mass");
  //addVartoStore("invmass_leadjets");
  addVartoStore("invmass_chi2jets");
  addVartoStore("invmass_2ndTop");
  //addVartoStore("invmass_trueTprime");
  //addVartoStore("chi2true_matched_Tprime");
  ////addVartoStore("chi2true_matched_H");
  ////addVartoStore("chi2true_matched_Top");
  ////addVartoStore("chi2true_matched_W");

  //addVartoStore("synch_evt");
  //addVartoStore("Hb1_pt");
  //addVartoStore("Hb2_pt");
  //addVartoStore("Wj1_pt");
  //addVartoStore("Wj2_pt");
  //addVartoStore("Tbj_pt");
  addVartoStore("selJet1_pt");
  addVartoStore("selJet1_pt_massnom");
  addVartoStore("selJet1_eta");
  addVartoStore("selJet1_e");
  addVartoStore("selJet1_e_massnom");
  addVartoStore("selJet1_btagDeepB");

  addVartoStore("selJet2_pt");
  addVartoStore("selJet2_pt_massnom");
  addVartoStore("selJet2_eta");
  addVartoStore("selJet2_e");
  addVartoStore("selJet2_e_massnom");
  addVartoStore("selJet2_btagDeepB");

  addVartoStore("selJet3_pt");
  addVartoStore("selJet3_pt_massnom");
  addVartoStore("selJet3_eta");
  addVartoStore("selJet3_e");
  addVartoStore("selJet3_e_massnom");
  addVartoStore("selJet3_btagDeepB");

  addVartoStore("selJet4_pt");
  addVartoStore("selJet4_pt_massnom");
  addVartoStore("selJet4_eta");
  addVartoStore("selJet4_e");
  addVartoStore("selJet4_e_massnom");
  addVartoStore("selJet4_btagDeepB");

  addVartoStore("selJet5_pt");
  addVartoStore("selJet5_pt_massnom");
  addVartoStore("selJet5_eta");
  addVartoStore("selJet5_e");
  addVartoStore("selJet5_e_massnom");
  addVartoStore("selJet5_btagDeepB");

  addVartoStore("selbJet1_pt");
  addVartoStore("selbJet1_pt_massnom");
  addVartoStore("selbJet1_eta");
  addVartoStore("selbJet1_e");
  addVartoStore("selbJet1_e_massnom");
  addVartoStore("selbJet1_btagDeepB");

  addVartoStore("selbJet2_pt");
  addVartoStore("selbJet2_pt_massnom");
  addVartoStore("selbJet2_eta");
  addVartoStore("selbJet2_e");
  addVartoStore("selbJet2_e_massnom");
  addVartoStore("selbJet2_btagDeepB");

  //addVartoStore("selJet_pt");
  //addVartoStore("selJet_eta");
  //addVartoStore("selJet_phi");
  //addVartoStore("selJet_mass");
  //addVartoStore("selJet_btagDeepB");
  addVartoStore("nselJets");

  //addVartoStore("selbJet_pt");
  //addVartoStore("selbJet_eta");
  //addVartoStore("selbJet_phi");
  //addVartoStore("selbJet_mass");
  //addVartoStore("selbJet_btagDeepB");
  addVartoStore("nselbJets");

  //addVartoStore("qFromTop_eta");
  //addVartoStore("gJetFromTop_pt");
  //addVartoStore("JetFromTop_eta");

  //addVartoStore("qFromW_eta");
  //addVartoStore("gJetFromW_pt");
  //addVartoStore("JetFromW_eta");

  //addVartoStore("bFromH_eta");
  //addVartoStore("gJetFromH_pt");
  //addVartoStore("JetFromH_eta"); // problem

  //addVartoStore("JetFromTprime_eta");
  //addVartoStore("JetFromH_eta");
  //addVartoStore("JetFromW_eta");

  addVartoStore("RelHT");
  addVartoStore("dRHbb_chi2");
  addVartoStore("dRWjj_chi2");
  addVartoStore("goodHT");
  addVartoStore("dRbW_chi2");
  //addVartoStore("chib1eta");
  //addVartoStore("chib1phi");

  //addVartoStore("chib2eta");
  //addVartoStore("chib2phi");

  //addVartoStore("chij1eta");
  //addVartoStore("chij1phi");

  //addVartoStore("chij2eta");
  //addVartoStore("chij2phi");

  //addVartoStore("chiojeta");
  //addVartoStore("chiojphi");
  //addVartoStore("W_chi2_eta");
  //addVartoStore("W_chi2_phi");

  //addVartoStore("dRbb");
  //addVartoStore("mbb");

  addVartoStore("mindR_dRbb");
  addVartoStore("mindR_mbb");
  
}
//.================================Histogram Definitions===========================================//
// _hist1dinfovector contains the information of histogram definitions (as TH1DModel)
// the variable to be used for filling and the minimum cutstep for which the histogram should be filled
//dd1DHist(TH1DModel histdef, std::string variable, std::string weight, string mincutstep="");
//=================================================================================================//
void TprimeHadAnalyzer::bookHists()
{

  add1DHist( {"hnevents", "Number of Events", 2, -0.5, 1.5}, "one", "evWeight", "");
//  add1DHist( {"h_nJets", "Number of selected Jets", 9, 6, 14}, "nselJets", "evWeight", "0");
//  add1DHist( {"h_nbJets", "Number of selected b Jets", 5, 2, 7}, "nselbJets", "evWeight", "0");

//  add1DHist( {"h_Jet_pt", "pT of selected Jets", 100, 30, 300}, "selJet_pt", "evWeight", "0");
//  add1DHist( {"h_Jet_eta", "eta of selected Jets", 100, -5, 5}, "selJet_eta", "evWeight", "0");
//  add1DHist( {"h_Jet_phi", "phi of selected Jets", 100, -3.5, 3.5}, "selJet_phi", "evWeight", "0");
//  add1DHist( {"h_Jet_mass", "mass of selected Jets", 100, 0, 200}, "selJet_mass", "evWeight", "0");
//  add1DHist( {"h_Jet_btagDeepB", "DeepCSV value of selected Jets", 100, 0, 1}, "selJet_btagDeepB", "evWeight", "0");
//  add1DHist( {"h_Jet_e", "energy of selected Jets", 100, 0, 200}, "selJet_e", "evWeight", "0");

//  add1DHist( {"h_Jet1_pt", "pT of selected 1st Jets", 100, 30, 800}, "selJet1_pt", "evWeight", "0");
//  add1DHist( {"h_Jet1_eta", "eta of selected 1st Jets", 100, -5, 5}, "selJet1_eta", "evWeight", "0");
//  add1DHist( {"h_Jet1_phi", "phi of selected 1st Jets", 100, -3.5, 3.5}, "selJet1_phi", "evWeight", "0");
//  add1DHist( {"h_Jet1_mass", "mass of selected 1st Jets", 100, 0, 200}, "selJet1_mass", "evWeight", "0");
//  add1DHist( {"h_Jet1_btagDeepB", "DeepCSV value of selected 1st Jets", 100, 0, 1}, "selJet1_btagDeepB", "evWeight", "0");
//  add1DHist( {"h_Jet1_e", "e of selected 1st Jets", 100, 50, 1000}, "selJet1_e", "evWeight", "0");
//
//  add1DHist( {"h_Jet2_pt", "pT of selected 2nd Jets", 100, 30, 600}, "selJet2_pt", "evWeight", "0");
//  add1DHist( {"h_Jet2_eta", "eta of selected 2nd Jets", 100, -5, 5}, "selJet2_eta", "evWeight", "0");
//  add1DHist( {"h_Jet2_phi", "phi of selected 2nd Jets", 100, -3.5, 3.5}, "selJet2_phi", "evWeight", "0");
//  add1DHist( {"h_Jet2_mass", "mass of selected 2nd Jets", 100, 0, 150}, "selJet2_mass", "evWeight", "0");
//  add1DHist( {"h_Jet2_btagDeepB", "DeepCSV value of selected 2nd Jets", 100, 0, 1}, "selJet2_btagDeepB", "evWeight", "0");
//  add1DHist( {"h_Jet2_e", "e of selected 2nd Jets", 100, 30, 600}, "selJet2_e", "evWeight", "0");
//
//  add1DHist( {"h_Jet3_pt", "pT of selected 3nd Jets", 100, 30, 400}, "selJet3_pt", "evWeight", "0");
//  add1DHist( {"h_Jet3_eta", "eta of selected 3nd Jets", 100, -5, 5}, "selJet3_eta", "evWeight", "0");
//  add1DHist( {"h_Jet3_phi", "phi of selected 3nd Jets", 100, -3.5, 3.5}, "selJet3_phi", "evWeight", "0");
//  add1DHist( {"h_Jet3_mass", "mass of selected 3nd Jets", 100, 0, 50}, "selJet3_mass", "evWeight", "0");
//  add1DHist( {"h_Jet3_btagDeepB", "DeepCSV value of selected 3nd Jets", 100, 0, 1}, "selJet3_btagDeepB", "evWeight", "0");
//  add1DHist( {"h_Jet3_e", "e of selected 3nd Jets", 100, 30, 400}, "selJet3_e", "evWeight", "0");
//
//  add1DHist( {"h_Jet4_pt", "pT of selected 4nd Jets", 100, 40, 200}, "selJet4_pt", "evWeight", "0");
//  add1DHist( {"h_Jet4_eta", "eta of selected 4nd Jets", 100, -5, 5}, "selJet4_eta", "evWeight", "0");
//  add1DHist( {"h_Jet4_phi", "phi of selected 4nd Jets", 100, -3.5, 3.5}, "selJet4_phi", "evWeight", "0");
//  add1DHist( {"h_Jet4_mass", "mass of selected 4nd Jets", 100, 0, 50}, "selJet4_mass", "evWeight", "0");
//  add1DHist( {"h_Jet4_btagDeepB", "DeepCSV value of selected 4nd Jets", 100, 0, 1}, "selJet4_btagDeepB", "evWeight", "0");
//  add1DHist( {"h_Jet4_e", "e of selected 4th Jets", 100, 30, 300}, "selJet4_e", "evWeight", "0");
//
//  add1DHist( {"h_Jet5_pt", "pT of selected 5nd Jets", 100, 50, 200}, "selJet5_pt", "evWeight", "0");
//  add1DHist( {"h_Jet5_eta", "eta of selected 5nd Jets", 100, -5, 5}, "selJet5_eta", "evWeight", "0");
//  add1DHist( {"h_Jet5_phi", "phi of selected 5nd Jets", 100, -3.5, 3.5}, "selJet5_phi", "evWeight", "0");
//  add1DHist( {"h_Jet5_mass", "mass of selected 5nd Jets", 100, 0, 50}, "selJet5_mass", "evWeight", "0");
//  add1DHist( {"h_Jet5_btagDeepB", "DeepCSV value of selected 5nd Jets", 100, 0, 1}, "selJet5_btagDeepB", "evWeight", "0");
//  add1DHist( {"h_Jet5_e", "e of selected 5th Jets", 100, 30, 300}, "selJet5_e", "evWeight", "0");
//
////  add1DHist( {"h_bJet_pt", "pT of selected bJets", 100, 30, 300}, "selbJet_pt", "evWeight", "0");
////  add1DHist( {"h_bJet_eta", "eta of selected bJets", 100, -5, 5}, "selbJet_eta", "evWeight", "0");
////  add1DHist( {"h_bJet_phi", "phi of selected bJets", 100, -3.5, 3.5}, "selbJet_phi", "evWeight", "0");
////  add1DHist( {"h_bJet_mass", "mass of selected bJets", 100, 0, 200}, "selbJet_mass", "evWeight", "0");
////  add1DHist( {"h_bJet_btagDeepB", "DeepCSV value of selected 1st bJets", 100, 0, 1}, "selbJet_btagDeepB", "evWeight", "0");
////  add1DHist( {"h_bJet_e", "e of selected bJets", 100, 0, 200}, "selbJet_e", "evWeight", "0");
//
//  add1DHist( {"h_bJet1_pt", "pT of selected 1st bJets", 100, 30, 700}, "selbJet1_pt", "evWeight", "0");
//  add1DHist( {"h_bJet1_eta", "eta of selected 1st bJets", 100, -5, 5}, "selbJet1_eta", "evWeight", "0");
//  add1DHist( {"h_bJet1_phi", "phi of selected 1st bJets", 100, -3.5, 3.5}, "selbJet1_phi", "evWeight", "0");
//  add1DHist( {"h_bJet1_mass", "mass of selected 1st bJets", 100, 0, 200}, "selbJet1_mass", "evWeight", "0");
//  add1DHist( {"h_bJet1_btagDeepB", "DeepCSV value of selected 1st bJets", 100, 0, 1}, "selbJet1_btagDeepB", "evWeight", "0");
//  add1DHist( {"h_bJet1_e", "energy of selected 1st bJets", 100, 30, 500}, "selbJet1_e", "evWeight", "0");
//
//  add1DHist( {"h_bJet2_pt", "pT of selected 2nd bJets", 100, 30, 500}, "selbJet2_pt", "evWeight", "0");
//  add1DHist( {"h_bJet2_eta", "eta of selected 2nd bJets", 100, -5, 5}, "selbJet2_eta", "evWeight", "0");
//  add1DHist( {"h_bJet2_phi", "phi of selected 2nd bJets", 100, -3.5, 3.5}, "selbJet2_phi", "evWeight", "0");
//  add1DHist( {"h_bJet2_mass", "mass of selected 2nd bJets", 100, 0, 50}, "selbJet2_mass", "evWeight", "0");
//  add1DHist( {"h_bJet2_btagDeepB", "DeepCSV value of selected 2nd bJets", 100, 0, 1}, "selbJet2_btagDeepB", "evWeight", "0");
//  add1DHist( {"h_bJet2_e", "energy of selected 2nd bJets", 100, 30, 300}, "selbJet2_e", "evWeight", "0");
//
////  add1DHist( {"h_bJet3_pt", "pT of selected 3nd bJets", 100, 30, 300}, "selbJet3_pt", "evWeight", "0");
////  add1DHist( {"h_bJet3_eta", "eta of selected 3nd bJets", 100, -5, 5}, "selbJet3_eta", "evWeight", "0");
////  add1DHist( {"h_bJet3_phi", "phi of selected 3nd bJets", 100, -3.5, 3.5}, "selbJet3_phi", "evWeight", "0");
////  add1DHist( {"h_bJet3_mass", "mass of selected 3nd bJets", 100, 0, 30}, "selbJet3_mass", "evWeight", "0");
////  add1DHist( {"h_bJet3_btagDeepB", "DeepCSV value of selected 3nd bJets", 100, 0, 1}, "selbJet3_btagDeepB", "evWeight", "0");
////  add1DHist( {"h_bJet3_e", "e of selected 3nd bJets", 100, 0, 30}, "selbJet3_e", "evWeight", "0");
//
////  add1DHist( {"h_bJet4_pt", "pT of selected 4nd bJets", 100, 40, 200}, "selbJet4_pt", "evWeight", "0");
////  add1DHist( {"h_bJet4_eta", "eta of selected 4nd bJets", 100, -5, 5}, "selbJet4_eta", "evWeight", "0");
////  add1DHist( {"h_bJet4_phi", "phi of selected 4nd bJets", 100, -4.5, 4.5}, "selbJet4_phi", "evWeight", "0");
////  add1DHist( {"h_bJet4_mass", "mass of selected 4nd bJets", 100, 0, 30}, "selbJet4_mass", "evWeight", "0");
////  add1DHist( {"h_bJet4_btagDeepB", "DeepCSV value of selected 4nd bJets", 100, 0, 1}, "selbJet4_btagDeepB", "evWeight", "0");
//
//  add1DHist( {"h_dR_Hbb", "Delta R between two b jets from H Chi2", 100, 0, 6}, "dRHbb_chi2", "evWeight", "0");
//  add1DHist( {"h_dR_Wjj", "Delta R between two jets from W Chi2", 100, 0.1, 6}, "dRWjj_chi2", "evWeight", "0");
//  
//  add1DHist( {"h_mindR_dRbb", "Delta R between two b jets having mininum Delta R", 100, 0, 5}, "mindR_dRbb", "evWeight", "0");
//  add1DHist( {"h_mindR_mbb", "invariant mass of two b jets having mininum Delta R", 100, 0, 500}, "mindR_mbb", "evWeight", "0");
//
//  add1DHist( {"h_goodHT", "HT of jets pT over 30", 100, 0, 2500}, "goodHT", "evWeight", "0");
//
//  add1DHist( {"h_Jet1_pt_massnom", "pT of selected 1st Jets", 100, 0, 2.5}, "selJet1_pt_massnom", "evWeight", "0");
//  add1DHist( {"h_Jet2_pt_massnom", "pT of selected 2nd Jets", 100, 0, 1.5}, "selJet2_pt_massnom", "evWeight", "0");
//  add1DHist( {"h_Jet3_pt_massnom", "pT of selected 3rd Jets", 100, 0, 1}, "selJet3_pt_massnom", "evWeight", "0");
//  add1DHist( {"h_Jet4_pt_massnom", "pT of selected 4th Jets", 100, 0, 0.7}, "selJet4_pt_massnom", "evWeight", "0");
//  add1DHist( {"h_Jet5_pt_massnom", "pT of selected 5th Jets", 100, 0, 0.4}, "selJet5_pt_massnom", "evWeight", "0");
//  add1DHist( {"h_bJet1_pt_massnom", "pT of selected 1st bJets", 100, 0, 1.2}, "selbJet1_pt_massnom", "evWeight", "0");
//  add1DHist( {"h_bJet2_pt_massnom", "pT of selected 2nd bJets", 100, 0, 0.5}, "selbJet2_pt_massnom", "evWeight", "0");
//
//  add1DHist( {"h_Jet1_e_massnom", "energy of selected 1st Jets", 100, 0, 4}, "selJet1_e_massnom", "evWeight", "0");
//  add1DHist( {"h_Jet2_e_massnom", "energy of selected 2nd Jets", 100, 0, 4}, "selJet2_e_massnom", "evWeight", "0");
//  add1DHist( {"h_Jet3_e_massnom", "energy of selected 3rd Jets", 100, 0, 4}, "selJet3_e_massnom", "evWeight", "0");
//  add1DHist( {"h_Jet4_e_massnom", "energy of selected 4th Jets", 100, 0, 4}, "selJet4_e_massnom", "evWeight", "0");
//  add1DHist( {"h_Jet5_e_massnom", "energy of selected 5th Jets", 100, 0, 4}, "selJet5_e_massnom", "evWeight", "0");
//  add1DHist( {"h_bJet1_e_massnom", "energy of selected 1st bJets", 100, 0, 2}, "selbJet1_e_massnom", "evWeight", "0");
//  add1DHist( {"h_bJet2_e_massnom", "energy of selected 2nd bJets", 100, 0, 2}, "selbJet2_e_massnom", "evWeight", "0");
//
//  add1DHist( {"h_Jet1_pt_htnom", "pT of selected 1st Jets", 100, 0, 0.8}, "selJet1_pt_htnom", "evWeight", "0");
//  add1DHist( {"h_Jet2_pt_htnom", "pT of selected 2nd Jets", 100, 0, 0.8}, "selJet2_pt_htnom", "evWeight", "0");
//  add1DHist( {"h_Jet3_pt_htnom", "pT of selected 3rd Jets", 100, 0, 0.3}, "selJet3_pt_htnom", "evWeight", "0");
//  add1DHist( {"h_Jet4_pt_htnom", "pT of selected 4th Jets", 100, 0, 0.3}, "selJet4_pt_htnom", "evWeight", "0");
//  add1DHist( {"h_Jet5_pt_htnom", "pT of selected 5th Jets", 100, 0, 0.2}, "selJet5_pt_htnom", "evWeight", "0");
//  add1DHist( {"h_bJet1_pt_htnom", "pT of selected 1st bJets", 100, 0, 0.8}, "selbJet1_pt_htnom", "evWeight", "0");
//  add1DHist( {"h_bJet2_pt_htnom", "pT of selected 2nd bJets", 100, 0, 0.5}, "selbJet2_pt_htnom", "evWeight", "0");
//
//  add1DHist( {"h_Jet1_e_htnom", "energy of selected 1st Jets", 100, 0, 2.5}, "selJet1_e_htnom", "evWeight", "0");
//  add1DHist( {"h_Jet2_e_htnom", "energy of selected 2nd Jets", 100, 0, 2.5}, "selJet2_e_htnom", "evWeight", "0");
//  add1DHist( {"h_Jet3_e_htnom", "energy of selected 3rd Jets", 100, 0, 2.5}, "selJet3_e_htnom", "evWeight", "0");
//  add1DHist( {"h_Jet4_e_htnom", "energy of selected 4th Jets", 100, 0, 2.5}, "selJet4_e_htnom", "evWeight", "0");
//  add1DHist( {"h_Jet5_e_htnom", "energy of selected 5th Jets", 100, 0, 2.5}, "selJet5_e_htnom", "evWeight", "0");
//  add1DHist( {"h_bJet1_e_htnom", "energy of selected 1st bJets", 100, 0, 1.5}, "selbJet1_e_htnom", "evWeight", "0");
//  add1DHist( {"h_bJet2_e_htnom", "energy of selected 2nd bJets", 100, 0, 1}, "selbJet2_e_htnom", "evWeight", "0");
//
//  add1DHist( {"h_goodHT_massnom", "HT of jets pT over 30", 100, 0, 7}, "goodHT_massnom", "evWeight", "0");
//  add1DHist( {"h_invmass_htnom", "invariant mass of 5 jets from chi2", 100, 0, 3}, "invmass_htnom", "evWeight", "0");
//
//  add1DHist( {"h_Chi2_min", "minimum Chi2", 100, 0, 100}, "Chi2_min", "evWeight", "0");
//  add1DHist( {"h_Chi2_minH", "minimum Chi2 for Higgs", 100, 0, 100}, "Chi2_min_H", "evWeight", "0");
//  add1DHist( {"h_Chi2_minW", "minimum Chi2 for W", 100, 10, 100}, "Chi2_min_W", "evWeight", "0");
//  add1DHist( {"h_Chi2_minTop", "minimum Chi2 for Top", 100, 0, 100}, "Chi2_min_Top", "evWeight", "0");
//
//  add1DHist( {"h_H_mass", "mass of the Higgs from minChi2", 100, 50, 200}, "H_mass", "evWeight", "0");
//  add1DHist( {"h_W_mass", "mass of the W from minChi2", 100, 10, 300}, "W_mass", "evWeight", "0");
//  add1DHist( {"h_Top_mass", "mass of the Top from minChi2", 100, 50, 400}, "Top_mass", "evWeight", "0");
//
//  add1DHist( {"h_invmass_leadjets", "invariant mass of 5 leading jets", 100, 0, 3000}, "invmass_leadjets", "evWeight", "0");
//  add1DHist( {"h_invmass_chi2jets", "invariant mass of 5 jets from chi2", 100, 0, 1700}, "invmass_chi2jets", "evWeight", "0");
//  //add1DHist( {"h_invmass_trueTprime", "invariant mass of 5 jets from trueTprime", 200, 0, 1300}, "invmass_trueTprime", "evWeight", "00000");
//  add1DHist( {"h_invmass_2ndTop", "invariant mass of 2nd Top", 100, 0, 1000}, "invmass_2ndTop", "evWeight", "0");
//  add1DHist( {"h_invmass_Higgs", "invariant mass of Higgs", 100, 0, 400}, "invmass_Higgs", "evWeight", "0");
//
//  add1DHist( {"h_RelHT", "Relative HT", 100, 0, 1}, "RelHT", "evWeight", "0");
//  add1DHist( {"h_chi2_trueTprime", "number of matched chi2 jets with true Tprime", 6, 0, 6}, "chi2true_matched_Tprime", "evWeight", "000");
//  add1DHist( {"h_chi2_trueH", "number of matched chi2 jets with true Higgs", 3, 0, 3}, "chi2true_matched_H", "evWeight", "000");
//  add1DHist( {"h_chi2_trueTop", "number of matched chi2 jets with true Top", 4, 0, 4}, "chi2true_matched_Top", "evWeight", "000");
//  add1DHist( {"h_chi2_trueW", "number of matched chi2 jets with true W", 3, 0, 3}, "chi2true_matched_W", "evWeight", "000");

}

void TprimeHadAnalyzer::setTree(TTree *t, std::string outfilename)
{
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
//.================================Selected Object Definitions====================================//
// Setupanalysis function:  where all object selection functions must be defined in sequence
// Selected objects will be stored in new vectors.
//==============================================================================================//
void TprimeHadAnalyzer::setupAnalysis()
{
/* Must sequentially define objects.*/

  if (_isData) _jsonOK = readjson();
  // Event weight for data it's always one. For MC, it depends on the sign

  _rlm = _rlm.Define("one", "1.0");

  _rlm = _rlm.Define("evWeight","one")
              .Define("unitGenWeight","one")
              .Define("pugenWeight","one");

//=================initiliaze object selection functions in setupAnalysis() function=============================//
  // Object selection will be defined in sequence.
  // Selected objects will be stored in new vectors.
  //selectElectrons();
  //selectMuons();
  applyJetMETCorrections();
  genStudy();
  selectJets();
  //removeOverlaps();
  //synch();
  defineCuts();
  defineMoreVars();
  bookHists();
  setupCuts_and_Hists();
  setupTree();
}
//=======================Lepton selection criteria==============================================//
//selectElectrons()/selectMuons() functions will add a new column to the Rdataframe that defines 
// a “good muon” or "good electron" for the purpose of your analysis.
//For any physics object, the selection criteria typically include:
//1-kinematic constraints (momentum, pseudorapidity, masses of object pairs, etc)
//2-identification requirements (loose, medium, tight quality levels). We have stored all of these labels as boolean pass/fail variables.
//3-isolations requirements (loose, medium, tight isolation levels).
//==============================================================================================//

//2.=======================Electron identification requirements==================================//
//to find ElectronId working points for the purpose of  your analysis-check the twiki pages :
//Run II recommendation: https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaRunIIRecommendations
// Run II recomendation - cutbased: https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2
//https://cms-nanoaod-integration.web.cern.ch/integration/master-106X/mc102X_doc.html
//=============================================================================================//

//3.===============================Find Good Electrons===========================================//
//: Define Good Electrons in rdata frame
//=============================================================================================//

void TprimeHadAnalyzer::selectElectrons()
{
  //cout << "select good electrons" << endl;
  _rlm = _rlm.Define("goodElectrons", ElectronID(2)); 
  //define new variables: selected electron pt, eta, phi, mass,etc..within goodElectrons definition
  _rlm = _rlm.Define("Selected_electron_pt", "Electron_pt[goodElectrons]") 
              .Define("Selected_electron_eta", "Electron_eta[goodElectrons]")
              .Define("Selected_electron_phi", "Electron_phi[goodElectrons]")
              .Define("Selected_electron_mass", "Electron_mass[goodElectrons]")
              .Define("Selected_electron_idx", ::good_idx, {"goodElectrons"})
              .Define("numberof_electron_pass", "int(Selected_electron_pt.size())");
  //-------------------------------------------------------
  //generate electron 4vector 
  //-------------------------------------------------------
  _rlm = _rlm.Define("electron_4vecs", ::generate_4vec, {"Selected_electron_pt", "Selected_electron_eta", "Selected_electron_phi", "Selected_electron_mass"});

    //-------------------------------------------------------
    // veto Electron cuts
    //-------------------------------------------------------
    //string veto_electron_str = Form ("Electron_pt>%f && abs(Electron_eta)<%f && %s",cutdb->Md_Electron_pT,cutdb->Md_Electron_eta, ElectronID(2).c_str());
    //_rlm = _rlm.Define("goodElectrons", veto_electron_str.c_str());


}

// add alternate muon IDs and isolation corrections
//Find the interesting muons in the muon collection

//6.=================================JETMET Correction============================================//
//void TprimeHadAnalyzer::applyJetMETCorrections()
//{
  // Adapted from https://github.com/cms-nanoAOD/nanoAOD-tools/blob/master/python/postprocessing/modules/jme/jetRecalib.py
  // and https://github.com/cms-nanoAOD/nanoAOD-tools/blob/master/python/postprocessing/modules/jme/JetRecalibrator.py

//    _rlm = _rlm.Define("corrected_Jet_pt", appcorrlambdaf, {"Jet_pt", "Jet_eta", "Jet_area", "Jet_rawFactor", "fixedGridRhoFastjetAll"});

//    _rlm = _rlm.Define("");

//}
//=============================================================================================//

void TprimeHadAnalyzer::genStudy()
{

  //Generator level information
  _rlm = _rlm.Define("p4_GenJet",::generate_4vec, {"GenJet_pt","GenJet_eta","GenJet_phi","GenJet_mass"})
             .Define("p4_GenPart",::generate_4vec, {"GenPart_pt","GenPart_eta","GenPart_phi","GenPart_mass"});

  auto isQfromTopHTprime = [](FourVectorVec &p, ints &pdgId, ints &midx)
  {
  
      bools out;
      unsigned int np = p.size();
      bool flag = false;
  
      // GenParticle loop 
      for( unsigned int i = 0; i < np; i++ ){
          flag = false;
  
          // make sure hadronic channel
          if( abs( pdgId[i] ) == 13 || abs( pdgId[i] ) == 11 ){
              out.emplace_back(flag);
              continue;
          }
  
          // tracking the mother of this particle...
          int moid = midx[i];
          for( unsigned int j = 0; j < np-1; j++ ){ //mother loop

            //just to be sure if it is not out of the range...
            if ( moid > int(pdgId.size()) || moid < -1 ) break;
  
            // if its mother is either Top or Higgs
            if( abs( pdgId[ moid ] ) == 6 || abs( pdgId[ moid ] ) == 25 ){
  
                // track the grandmother
                int gmoid = midx[moid];
                for( unsigned int k = 0; k < np-2; k++ ){
  
                    //just to be sure if it is not out of the range...
                    if ( gmoid > int(pdgId.size()) || gmoid < -1 ) break;

                    // is it from Tprime
                    if( abs( pdgId[ gmoid ] ) == 8000001 ){
                      flag = true;
                      break;
                    }
                    gmoid = midx[gmoid]; // update the index
                } // grandma loop
            }
            moid = midx[ moid ]; // update the index
          } // mother loop
          out.emplace_back(flag);
      }
      return out;
  };

  auto isLastbfromH = [](FourVectorVec &p, ints &pdgId, ints &midx, ints &status)
  {
      bools out;
      unsigned int np = p.size();
      bool flag = false;
  
      // GenParticle loop 
      for( unsigned int i = 0; i < np; i++ ){
          flag = false;
          // isLast bquark
          if( (status[i] & (1<<13)) && abs( pdgId[i] ) == 5){
              // tracking the mother of this particle...
              int moid = midx[i];
              for( unsigned int j = 0; j < np-1; j++ ){  //mother loop

                if ( moid > int(pdgId.size()) || moid < -1 ) break;  //just to be sure if it is not out of the range...
                // if its mother is Higgs
                if( abs( pdgId[ moid ] ) == 25 ){
                    flag = true;
                    break;
                }
                moid = midx[ moid ]; // update the index
              } // mother loop
          }
          out.emplace_back(flag);
      } // GenParticle loop
      return out;
  };

  auto isLastQfromTop = [](FourVectorVec &p, ints &pdgId, ints &midx, ints &status)
  {
      bools out;
      unsigned int np = p.size();
      bool flag = false;
  
      // GenParticle loop 
      for( unsigned int i = 0; i < np; i++ ){
          flag = false;
  
          // isLast quark
          if( (status[i] & (1<<13))  && abs( pdgId[i] ) <= 6 ){
  
              // tracking the mother of this particle...
              int moid = midx[i];
              for( unsigned int j = 0; j < np-1; j++ ){ //mother loop

                //just to be sure if it is not out of the range...
                if ( moid > int(pdgId.size()) || moid < -1 ) break;
  
                // if its mother is Top
                if( abs( pdgId[ moid ] ) == 6 ){
                    flag = true;
                    break;
                }
                moid = midx[ moid ]; // update the index
              } // mother loop
          }
          out.emplace_back(flag);
      } // GenParticle loop
      return out;
  };

  auto isLastQfromW = [](FourVectorVec &p, ints &pdgId, ints &midx, ints &status)
  {
  
      bools out;
      unsigned int np = p.size();
      bool flag = false;
  
      // GenParticle loop 
      for( unsigned int i = 0; i < np; i++ ){
          flag = false;
  
          // isLast quark
          if( ( status[i] & (1<<13) ) || abs( pdgId[i] ) <= 6){
  
              // tracking the mother of this particle...
              int moid = midx[i];
              for( unsigned int j = 0; j < np-1; j++ ){ //mother loop

                //just to be sure if it is not out of the range...
                if ( moid > int(pdgId.size()) || moid < -1 ) break;
  
                // if its mother is W
                if( abs( pdgId[ moid ] ) == 24 ){
                    flag = true;
                    break;
                }
                moid = midx[ moid ]; // update the index
              } // mother loop
          }
          out.emplace_back(flag);
      } // GenParticle loop
      return out;
  };

  auto isdR04 = [](floats eta1, floats eta2, floats phi1, floats phi2)
  {
  
      bools out;
      for( unsigned int i = 0; i < eta1.size(); i++ ){
          bool isless04 = false;
          float mindr = FLT_MAX;
          for( unsigned int j = 0; j < eta2.size(); j++ ){
              auto dr = ROOT::VecOps::DeltaR(eta1[i],eta2[j],phi1[i],phi2[j]);
              if( dr < mindr ) mindr = dr;
          }
          if( mindr < 0.4 ) isless04 = true;
          out.emplace_back(isless04);
      }
      return out;
  }; 
 
  auto isJetFromgJet = [](floats jet_pt, floats gjet_pt, floats gjetTarget_pt, ints jet_gidx)
  {
  
      bools out;
      for( unsigned int i = 0; i < jet_pt.size(); i++ ){
          bool isFromTruth = false;
          //index of genJet matched with Jet i
          int gIdx = jet_gidx[i];
          if ( gIdx <= int(gjet_pt.size()) && gIdx > -1 ) for( unsigned int j = 0; j < gjetTarget_pt.size(); j++ ) if( gjet_pt[gIdx] == gjetTarget_pt[j] ) isFromTruth = true;
  
          out.emplace_back(isFromTruth);
      }
      return out;
  };

  _rlm = _rlm.Define("isHadTprime",::isHadWHiggs,{"p4_GenPart","GenPart_pdgId","GenPart_genPartIdxMother"});

  _rlm  = _rlm.Define("sel_genpTprime",isQfromTopHTprime,{"p4_GenPart","GenPart_pdgId","GenPart_genPartIdxMother"})
              .Define("pFromTprime_eta","GenPart_eta[sel_genpTprime]")
              .Define("pFromTprime_phi","GenPart_phi[sel_genpTprime]");

  _rlm  = _rlm.Define("sel_genjTprime",isdR04,{"GenJet_eta","pFromTprime_eta","GenJet_phi","pFromTprime_phi"})
              .Define("gJetFromTprime_pt","GenJet_pt[sel_genjTprime]");

  _rlm  = _rlm.Define("sel_jetTprime",isJetFromgJet,{"Jet_pt","GenJet_pt","gJetFromTprime_pt","Jet_genJetIdx"})
              .Define("JetFromTprime_pt","Jet_pt[sel_jetTprime]")
              .Define("JetFromTprime_eta","Jet_eta[sel_jetTprime]")
              .Define("JetFromTprime_phi","Jet_phi[sel_jetTprime]")
              .Define("JetFromTprime_mass","Jet_mass[sel_jetTprime]")
              .Define("p4_JetFromTprime",::generate_4vec, {"JetFromTprime_pt","JetFromTprime_eta","JetFromTprime_phi","JetFromTprime_mass"})
              .Define("invmass_trueTprime", "(p4_JetFromTprime[0]+p4_JetFromTprime[1]+p4_JetFromTprime[2]+p4_JetFromTprime[3]+p4_JetFromTprime[4]).M()");

  _rlm = _rlm.Define("sel_genbH",isLastbfromH,{"p4_GenPart","GenPart_pdgId","GenPart_genPartIdxMother","GenPart_statusFlags"})
             .Define("bFromH_eta","GenPart_eta[sel_genbH]")
             .Define("bFromH_phi","GenPart_phi[sel_genbH]");

  _rlm  = _rlm.Define("sel_genbjH",isdR04,{"GenJet_eta","bFromH_eta","GenJet_phi","bFromH_phi"})
              .Define("gJetFromH_pt","GenJet_pt[sel_genbjH]");

  _rlm  = _rlm.Define("sel_bjetH",isJetFromgJet,{"Jet_pt","GenJet_pt","gJetFromH_pt","Jet_genJetIdx"})
              .Define("JetFromH_pt","Jet_pt[sel_bjetH]")
              .Define("JetFromH_eta","Jet_eta[sel_bjetH]")
              .Define("JetFromH_phi","Jet_phi[sel_bjetH]")
              .Define("nJetFromH","int(JetFromH_pt.size())");

  _rlm = _rlm.Define("sel_genWq",isLastQfromW,{"p4_GenPart","GenPart_pdgId","GenPart_genPartIdxMother","GenPart_statusFlags"})
             .Define("qFromW_eta","GenPart_eta[sel_genWq]")
             .Define("qFromW_phi","GenPart_phi[sel_genWq]");

  _rlm  = _rlm.Define("sel_genWj",isdR04,{"GenJet_eta","qFromW_eta","GenJet_phi","qFromW_phi"})
              .Define("gJetFromW_pt","GenJet_pt[sel_genWj]");

  _rlm  = _rlm.Define("sel_jetW",isJetFromgJet,{"Jet_pt","GenJet_pt","gJetFromW_pt","Jet_genJetIdx"})
              .Define("JetFromW_pt","Jet_pt[sel_jetW]")
              .Define("JetFromW_eta","Jet_eta[sel_jetW]")
              .Define("JetFromW_phi","Jet_phi[sel_jetW]")
              .Define("nJetFromW","int(JetFromW_pt.size())");

  _rlm = _rlm.Define("sel_genqTop",isLastQfromTop,{"p4_GenPart","GenPart_pdgId","GenPart_genPartIdxMother","GenPart_statusFlags"})
             .Define("qFromTop_eta","GenPart_eta[sel_genqTop]")
             .Define("qFromTop_phi","GenPart_phi[sel_genqTop]");

  _rlm  = _rlm.Define("sel_genjTop",isdR04,{"GenJet_eta","qFromTop_eta","GenJet_phi","qFromTop_phi"})
              .Define("gJetFromTop_pt","GenJet_pt[sel_genjTop]");

  _rlm  = _rlm.Define("sel_jetTop",isJetFromgJet,{"Jet_pt","GenJet_pt","gJetFromTop_pt","Jet_genJetIdx"})
              .Define("JetFromTop_pt","Jet_pt[sel_jetTop]")
              .Define("JetFromTop_eta","Jet_eta[sel_jetTop]")
              .Define("JetFromTop_phi","Jet_phi[sel_jetTop]")
              .Define("nJetFromTop","int(JetFromTop_pt.size())");
}

//7.=================================Select Jets=================================================//

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

  _rlm = _rlm.Define("goodJets", "Jet_jetId > 1 && Jet_pt >= 30 && abs(Jet_eta) <= 4.5")
             .Define("good40Jets", "goodJets && Jet_pt >= 40")
             .Define("good80Jets", "good40Jets && Jet_pt >= 80");
  
  _rlm = _rlm.Define("nselJets","Sum(goodJets)")
             .Define("nsel40Jets","Sum(good40Jets)")
             .Define("nsel80Jets","Sum(good80Jets)")
             .Define("selJet_pt","Jet_pt[goodJets]")
             .Define("selJet_eta","Jet_eta[goodJets]")
             .Define("selJet_phi","Jet_phi[goodJets]")
             .Define("selJet_mass","Jet_mass[goodJets]")
             .Define("selJet_btagDeepB","Jet_btagDeepB[goodJets]")
             .Define("jet4vecs", ::generate_4vec, {"selJet_pt", "selJet_eta", "selJet_phi", "selJet_mass"});

  // DeepJet Medium
  _rlm = _rlm.Define("goodbJets", "goodJets && abs(Jet_eta) < 2.5 && Jet_btagDeepFlavB > 0.2783");
  // DeepCSV Tight
  //_rlm = _rlm.Define("goodbJets", "goodJets && abs(Jet_eta) < 2.5 && Jet_btagDeepB > 0.7665");

  _rlm = _rlm.Define("nselbJets","Sum(goodbJets)")
             .Define("selbJet_pt","Jet_pt[goodbJets]")
             .Define("selbJet_eta","Jet_eta[goodbJets]")
             .Define("selbJet_phi","Jet_phi[goodbJets]")
             .Define("selbJet_mass","Jet_mass[goodbJets]")
             .Define("selbJet_btagDeepB","Jet_btagDeepB[goodbJets]")
             .Define("bjet4vecs", ::generate_4vec, {"selbJet_pt", "selbJet_eta", "selbJet_phi", "selbJet_mass"});

  // Function for kinematic reconstruction
  _rlm = _rlm.Define("Chi2_Tprime",::Tprime_reconstruction,{"jet4vecs","bjet4vecs"})
             .Define("Chi2_min","Chi2_Tprime[6]")
             .Define("Chi2_max","Chi2_Tprime[13]")

             .Define("chib1eta","(Chi2_Tprime[0] < 0) ? FLT_MIN : selbJet_eta[Chi2_Tprime[0]]")
             .Define("chib1phi","(Chi2_Tprime[0] < 0) ? FLT_MIN : selbJet_phi[Chi2_Tprime[0]]")
             .Define("chib2eta","(Chi2_Tprime[1] < 0) ? FLT_MIN : selbJet_eta[Chi2_Tprime[1]]")
             .Define("chib2phi","(Chi2_Tprime[1] < 0) ? FLT_MIN : selbJet_phi[Chi2_Tprime[1]]")

             .Define("chij1eta","(Chi2_Tprime[2] < 0) ? FLT_MIN : selJet_eta[Chi2_Tprime[2]]")
             .Define("chij1phi","(Chi2_Tprime[2] < 0) ? FLT_MIN : selJet_phi[Chi2_Tprime[2]]")
             .Define("chij1_4vecs","jet4vecs[Chi2_Tprime[2]]")

             .Define("chij2eta","(Chi2_Tprime[3] < 0) ? FLT_MIN : selJet_eta[Chi2_Tprime[3]]")
             .Define("chij2phi","(Chi2_Tprime[3] < 0) ? FLT_MIN : selJet_phi[Chi2_Tprime[3]]")
             .Define("chij2_4vecs","jet4vecs[Chi2_Tprime[3]]")

             .Define("chiojeta","(Chi2_Tprime[4] < 0) ? FLT_MIN : selJet_eta[Chi2_Tprime[4]]")
             .Define("chiojphi","(Chi2_Tprime[4] < 0) ? FLT_MIN : selJet_phi[Chi2_Tprime[4]]")
             //matching with gen Level
             .Define("chi2true_matched_Tprime",::count5s,{"JetFromTprime_eta","chib1eta","chib2eta","chij1eta","chij2eta","chiojeta"})
             .Define("chi2true_matched_H",::count2s,{"JetFromH_eta","chib1eta","chib2eta"})
             .Define("chi2true_matched_Top",::count3s,{"JetFromTop_eta","chij1eta","chij2eta","chiojeta"})
             .Define("chi2true_matched_W",::count2s,{"JetFromW_eta","chij1eta","chij2eta"});

  _rlm = _rlm.Define("W_chi2_eta","float((chij1_4vecs+chij2_4vecs).Eta())")
             .Define("W_chi2_phi","float((chij1_4vecs+chij2_4vecs).Phi())");

  _rlm = _rlm.Define("dRHbb_chi2","ROOT::VecOps::DeltaR(chib1eta,chib2eta,chib1phi,chib2phi)");
  _rlm = _rlm.Define("dRWjj_chi2","ROOT::VecOps::DeltaR(chij1eta,chij2eta,chij1phi,chij2phi)");
  _rlm = _rlm.Define("dRbW_chi2","ROOT::VecOps::DeltaR(W_chi2_eta,chiojeta,W_chi2_phi,chiojphi)"); 

  // Kinematic reconstructions
  _rlm = _rlm.Define("invmass_2ndTop","(bjet4vecs[Chi2_Tprime[0]]+bjet4vecs[Chi2_Tprime[1]]+jet4vecs[Chi2_Tprime[5]]).M()");
  _rlm = _rlm.Define("invmass_Higgs","(bjet4vecs[Chi2_Tprime[0]]+bjet4vecs[Chi2_Tprime[1]]).M()");

  _rlm = _rlm.Define("invmass_leadjets", "(jet4vecs[0]+jet4vecs[1]+jet4vecs[2]+jet4vecs[3]+jet4vecs[4]).M()")
             .Define("gate", "(bjet4vecs[Chi2_Tprime[0]]+bjet4vecs[Chi2_Tprime[1]]+jet4vecs[Chi2_Tprime[2]]+jet4vecs[Chi2_Tprime[3]]+bjet4vecs[Chi2_Tprime[4]]).M()")
             .Define("invmass_chi2jets", "(abs(gate) < 10E+20) ? isnan(gate) ? -1 : gate : -1");

  // Extra Variables for analysis
  _rlm = _rlm.Define("Higgs4vecs","(bjet4vecs[Chi2_Tprime[0]]+bjet4vecs[Chi2_Tprime[1]])")
             .Define("W4vecs","(jet4vecs[Chi2_Tprime[2]]+jet4vecs[Chi2_Tprime[3]])")
             .Define("Top4vecs","(W4vecs+bjet4vecs[Chi2_Tprime[4]])")
             .Define("TopWvecs","W4vecs+Top4vecs")
             .Define("Tprime4vecs","(bjet4vecs[Chi2_Tprime[0]]+bjet4vecs[Chi2_Tprime[1]]+jet4vecs[Chi2_Tprime[2]]+jet4vecs[Chi2_Tprime[3]]+bjet4vecs[Chi2_Tprime[4]])");

  _rlm = _rlm.Define("HT6","(selJet_pt[0]+selJet_pt[1]+selJet_pt[2]+selJet_pt[3]+selJet_pt[4]+selJet_pt[5])") 
             .Define("goodHT",::calculate_goodHT, {"selJet_pt"})
             .Define("RelHT",::calculate_RelHT, {"Top4vecs","Higgs4vecs","goodHT"});
}


//=============================================================================================//
//=================================Synchronization=============================================//
//=============================================================================================//
void TprimeHadAnalyzer::synch()
{

  auto checkcontents = [](unsigned int run, unsigned long long evt, unsigned int LS, double invM, float ht, float relHT, floats chi2, FourVectorVec &jet4vecs, FourVector &h4vecs, FourVector &w4vecs, FourVector &t4vecs, FourVector tprime4vecs, FourVector topWvecs)
      {
          floats out;

          cout << "Run Number " << run << " Evt Num " << evt << " LS " << LS << " M 5j " << invM << " HT " << ht << " chi2 " << chi2[6] << endl;
          out.emplace_back(evt);

          return out;
      };

  _rlm = _rlm.Define("synch_evt", checkcontents, {"run","event","luminosityBlock","invmass_chi2jets","goodHT","RelHT","Chi2_Tprime","jet4vecs","Higgs4vecs","W4vecs","Top4vecs","Tprime4vecs","TopWvecs"});

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
//=============================================================================================//
