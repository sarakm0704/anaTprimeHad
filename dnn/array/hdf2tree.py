#! /usr/bin/env python
import sys, os
import numpy as np
import ROOT
import pandas as pd

regions = ["2M1L", "3M", "3T"]

for r in range(len(regions)):
    print(f"Im in region {regions[r]}")
    model_name = "model_long_cnn_"+regions[r]+"model1"
    DIR = "/pbs/home/j/jechoi/work/vlq/nn/models/"+model_name+"/pred/"
    outputDir = "/sps/lyon/jechoi/tprimeHad/2018/"+regions[r]+"/cnnpred/"

    for p in os.listdir(DIR):
        if not "h5" in p: continue
        print(p)
        df = pd.read_hdf(DIR+p)
    
        selEvent = df
        nf = ROOT.TFile.Open(f"{outputDir}/hist{p[10:-3]}.root","RECREATE")
        
        h_njets = ROOT.TH1D("h_njets","",10,5,15)
        h_njets.GetXaxis().SetTitle("Number of jets")
        h_njets.GetYaxis().SetTitle("Number of Events")
    
        h_dnncut_mtprime = ROOT.TH1D("h_dnncut_mtprime","",25,300,1300)
        h_dnncut_mtprime.GetXaxis().SetTitle("M (top+H) [GeV]")
        h_dnncut_mtprime.GetYaxis().SetTitle("Number of Events")

        h_cut2_2d = ROOT.TH2D("h_cut2_2d","",25,300,1300,25,0,5)
        h_cut2_2d.GetXaxis().SetTitle("M (top+H) [GeV]")
        h_cut2_2d.GetYaxis().SetTitle("#Delta R of Higgs b candidates")

        h_2d_mqcd = ROOT.TH2D("h_2d_mqcd","",25,300,1300,25,0,1)
        h_2d_mqcd.GetXaxis().SetTitle("M (top+H) [GeV]")
        h_2d_mqcd.GetYaxis().SetTitle("QCD score")

        h_2d_mttbar = ROOT.TH2D("h_2d_mttbar","",25,300,1300,25,0,1)
        h_2d_mttbar.GetXaxis().SetTitle("M (top+H) [GeV]")
        h_2d_mttbar.GetYaxis().SetTitle("ttbar score")

        h_2d_msignal = ROOT.TH2D("h_2d_msignal","",25,300,1300,25,0,1)
        h_2d_msignal.GetXaxis().SetTitle("M (top+H) [GeV]")
        h_2d_msignal.GetYaxis().SetTitle("Tprime score")

        h_cut0_mtprime = h_dnncut_mtprime.Clone("h_cut0_mtprime")
        h_cut1_mtprime = h_dnncut_mtprime.Clone("h_cut1_mtprime")
        h_cut2_mtprime = h_dnncut_mtprime.Clone("h_cut2_mtprime")
        h_cut3_mtprime = h_dnncut_mtprime.Clone("h_cut3_mtprime")
        h_cut4_mtprime = h_dnncut_mtprime.Clone("h_cut4_mtprime")
        h_cut5_mtprime = h_dnncut_mtprime.Clone("h_cut5_mtprime")
        h_cut6_mtprime = h_dnncut_mtprime.Clone("h_cut6_mtprime")
    
        h_disc_qcd = ROOT.TH1D("h_disc_qcd","",1000,0,1)
        h_disc_qcd.GetXaxis().SetTitle("QCD score")
        h_disc_qcd.GetYaxis().SetTitle("Number of Events")
    
        h_disc_ttbar = ROOT.TH1D("h_disc_ttbar","",100,0,1)
        h_disc_ttbar.GetXaxis().SetTitle("TTbar score")
        h_disc_ttbar.GetYaxis().SetTitle("Number of Events")
    
        h_disc_signal = ROOT.TH1D("h_disc_signal","",100,0,1)
        h_disc_signal.GetXaxis().SetTitle("Signal score")
        h_disc_signal.GetYaxis().SetTitle("Number of Events")

        h_tp_01_njets = h_njets.Clone("h_tp_01_njets") 
        h_tp_01_mtprime = h_dnncut_mtprime.Clone("h_tp_01_mtprime")
        h_tp_01_disc_qcd = h_disc_qcd.Clone("h_tp_01_disc_qcd")
        h_tp_01_disc_ttbar = h_disc_ttbar.Clone("h_tp_01_disc_ttbar")
        h_tp_01_disc_signal = h_disc_signal.Clone("h_tp_01_disc_signal")
    
        h_tp_02_njets = h_njets.Clone("h_tp_02_njets") 
        h_tp_02_mtprime = h_dnncut_mtprime.Clone("h_tp_02_mtprime")
        h_tp_02_disc_qcd = h_disc_qcd.Clone("h_tp_02_disc_qcd")
        h_tp_02_disc_ttbar = h_disc_ttbar.Clone("h_tp_02_disc_ttbar")
        h_tp_02_disc_signal = h_disc_signal.Clone("h_tp_02_disc_signal")
    
        h_tp_03_njets = h_njets.Clone("h_tp_03_njets") 
        h_tp_03_mtprime = h_dnncut_mtprime.Clone("h_tp_03_mtprime")
        h_tp_03_disc_qcd = h_disc_qcd.Clone("h_tp_03_disc_qcd")
        h_tp_03_disc_ttbar = h_disc_ttbar.Clone("h_tp_03_disc_ttbar")
        h_tp_03_disc_signal = h_disc_signal.Clone("h_tp_03_disc_signal")
    
        h_tp_04_njets = h_njets.Clone("h_tp_04_njets") 
        h_tp_04_mtprime = h_dnncut_mtprime.Clone("h_tp_04_mtprime")
        h_tp_04_disc_qcd = h_disc_qcd.Clone("h_tp_04_disc_qcd")
        h_tp_04_disc_ttbar = h_disc_ttbar.Clone("h_tp_04_disc_ttbar")
        h_tp_04_disc_signal = h_disc_signal.Clone("h_tp_04_disc_signal")
    
        h_tp_05_njets = h_njets.Clone("h_tp_05_njets") 
        h_tp_05_mtprime = h_dnncut_mtprime.Clone("h_tp_05_mtprime")
        h_tp_05_disc_qcd = h_disc_qcd.Clone("h_tp_05_disc_qcd")
        h_tp_05_disc_ttbar = h_disc_ttbar.Clone("h_tp_05_disc_ttbar")
        h_tp_05_disc_signal = h_disc_signal.Clone("h_tp_05_disc_signal")
    
        h_tp_06_njets = h_njets.Clone("h_tp_06_njets") 
        h_tp_06_mtprime = h_dnncut_mtprime.Clone("h_tp_06_mtprime")
        h_tp_06_disc_qcd = h_disc_qcd.Clone("h_tp_06_disc_qcd")
        h_tp_06_disc_ttbar = h_disc_ttbar.Clone("h_tp_06_disc_ttbar")
        h_tp_06_disc_signal = h_disc_signal.Clone("h_tp_06_disc_signal")
    
        h_tp_07_njets = h_njets.Clone("h_tp_07_njets") 
        h_tp_07_mtprime = h_dnncut_mtprime.Clone("h_tp_07_mtprime")
        h_tp_07_disc_qcd = h_disc_qcd.Clone("h_tp_07_disc_qcd")
        h_tp_07_disc_ttbar = h_disc_ttbar.Clone("h_tp_07_disc_ttbar")
        h_tp_07_disc_signal = h_disc_signal.Clone("h_tp_07_disc_signal")
    
        h_tp_08_njets = h_njets.Clone("h_tp_08_njets") 
        h_tp_08_mtprime = h_dnncut_mtprime.Clone("h_tp_08_mtprime")
        h_tp_08_disc_qcd = h_disc_qcd.Clone("h_tp_08_disc_qcd")
        h_tp_08_disc_ttbar = h_disc_ttbar.Clone("h_tp_08_disc_ttbar")
        h_tp_08_disc_signal = h_disc_signal.Clone("h_tp_08_disc_signal")
    
        h_tp_09_njets = h_njets.Clone("h_tp_09_njets") 
        h_tp_09_mtprime = h_dnncut_mtprime.Clone("h_tp_09_mtprime")
        h_tp_09_disc_qcd = h_disc_qcd.Clone("h_tp_09_disc_qcd")
        h_tp_09_disc_ttbar = h_disc_ttbar.Clone("h_tp_09_disc_ttbar")
        h_tp_09_disc_signal = h_disc_signal.Clone("h_tp_09_disc_signal")

        h_tt_01_njets = h_njets.Clone("h_tt_01_njets") 
        h_tt_01_mtprime = h_dnncut_mtprime.Clone("h_tt_01_mtprime")
        h_tt_01_disc_qcd = h_disc_qcd.Clone("h_tt_01_disc_qcd")
        h_tt_01_disc_ttbar = h_disc_ttbar.Clone("h_tt_01_disc_ttbar")
        h_tt_01_disc_signal = h_disc_signal.Clone("h_tt_01_disc_signal")
    
        h_tt_02_njets = h_njets.Clone("h_tt_02_njets") 
        h_tt_02_mtprime = h_dnncut_mtprime.Clone("h_tt_02_mtprime")
        h_tt_02_disc_qcd = h_disc_qcd.Clone("h_tt_02_disc_qcd")
        h_tt_02_disc_ttbar = h_disc_ttbar.Clone("h_tt_02_disc_ttbar")
        h_tt_02_disc_signal = h_disc_signal.Clone("h_tt_02_disc_signal")
    
        h_tt_03_njets = h_njets.Clone("h_tt_03_njets") 
        h_tt_03_mtprime = h_dnncut_mtprime.Clone("h_tt_03_mtprime")
        h_tt_03_disc_qcd = h_disc_qcd.Clone("h_tt_03_disc_qcd")
        h_tt_03_disc_ttbar = h_disc_ttbar.Clone("h_tt_03_disc_ttbar")
        h_tt_03_disc_signal = h_disc_signal.Clone("h_tt_03_disc_signal")
    
        h_tt_04_njets = h_njets.Clone("h_tt_04_njets") 
        h_tt_04_mtprime = h_dnncut_mtprime.Clone("h_tt_04_mtprime")
        h_tt_04_disc_qcd = h_disc_qcd.Clone("h_tt_04_disc_qcd")
        h_tt_04_disc_ttbar = h_disc_ttbar.Clone("h_tt_04_disc_ttbar")
        h_tt_04_disc_signal = h_disc_signal.Clone("h_tt_04_disc_signal")
    
        h_tt_05_njets = h_njets.Clone("h_tt_05_njets") 
        h_tt_05_mtprime = h_dnncut_mtprime.Clone("h_tt_05_mtprime")
        h_tt_05_disc_qcd = h_disc_qcd.Clone("h_tt_05_disc_qcd")
        h_tt_05_disc_ttbar = h_disc_ttbar.Clone("h_tt_05_disc_ttbar")
        h_tt_05_disc_signal = h_disc_signal.Clone("h_tt_05_disc_signal")
    
        h_tt_06_njets = h_njets.Clone("h_tt_06_njets") 
        h_tt_06_mtprime = h_dnncut_mtprime.Clone("h_tt_06_mtprime")
        h_tt_06_disc_qcd = h_disc_qcd.Clone("h_tt_06_disc_qcd")
        h_tt_06_disc_ttbar = h_disc_ttbar.Clone("h_tt_06_disc_ttbar")
        h_tt_06_disc_signal = h_disc_signal.Clone("h_tt_06_disc_signal")
    
        h_tt_07_njets = h_njets.Clone("h_tt_07_njets") 
        h_tt_07_mtprime = h_dnncut_mtprime.Clone("h_tt_07_mtprime")
        h_tt_07_disc_qcd = h_disc_qcd.Clone("h_tt_07_disc_qcd")
        h_tt_07_disc_ttbar = h_disc_ttbar.Clone("h_tt_07_disc_ttbar")
        h_tt_07_disc_signal = h_disc_signal.Clone("h_tt_07_disc_signal")
    
        h_tt_08_njets = h_njets.Clone("h_tt_08_njets") 
        h_tt_08_mtprime = h_dnncut_mtprime.Clone("h_tt_08_mtprime")
        h_tt_08_disc_qcd = h_disc_qcd.Clone("h_tt_08_disc_qcd")
        h_tt_08_disc_ttbar = h_disc_ttbar.Clone("h_tt_08_disc_ttbar")
        h_tt_08_disc_signal = h_disc_signal.Clone("h_tt_08_disc_signal")
    
        h_tt_09_njets = h_njets.Clone("h_tt_09_njets") 
        h_tt_09_mtprime = h_dnncut_mtprime.Clone("h_tt_09_mtprime")
        h_tt_09_disc_qcd = h_disc_qcd.Clone("h_tt_09_disc_qcd")
        h_tt_09_disc_ttbar = h_disc_ttbar.Clone("h_tt_09_disc_ttbar")
        h_tt_09_disc_signal = h_disc_signal.Clone("h_tt_09_disc_signal")

        h_qcd_001_njets = h_njets.Clone("h_qcd_001_njets") 
        h_qcd_001_mtprime = h_dnncut_mtprime.Clone("h_qcd_001_mtprime")
        h_qcd_001_disc_qcd = h_disc_qcd.Clone("h_qcd_001_disc_qcd")
        h_qcd_001_disc_ttbar = h_disc_ttbar.Clone("h_qcd_001_disc_ttbar")
        h_qcd_001_disc_signal = h_disc_signal.Clone("h_qcd_001_disc_signal")

        h_qcd_005_njets = h_njets.Clone("h_qcd_005_njets") 
        h_qcd_005_mtprime = h_dnncut_mtprime.Clone("h_qcd_005_mtprime")
        h_qcd_005_disc_qcd = h_disc_qcd.Clone("h_qcd_005_disc_qcd")
        h_qcd_005_disc_ttbar = h_disc_ttbar.Clone("h_qcd_005_disc_ttbar")
        h_qcd_005_disc_signal = h_disc_signal.Clone("h_qcd_005_disc_signal")

        h_qcd_005_tt_01_njets = h_qcd_005_njets.Clone("h_qcd_005_tt_01_njets") 
        h_qcd_005_tt_01_mtprime = h_dnncut_mtprime.Clone("h_qcd_005_tt_01_mtprime")
        h_qcd_005_tt_01_disc_qcd = h_qcd_005_disc_qcd.Clone("h_qcd_005_tt_01_disc_qcd")
        h_qcd_005_tt_01_disc_ttbar = h_qcd_005_disc_ttbar.Clone("h_qcd_005_tt_01_disc_ttbar")
        h_qcd_005_tt_01_disc_signal = h_qcd_005_disc_signal.Clone("h_qcd_005_tt_01_disc_signal")
    
        h_qcd_005_tt_02_njets = h_qcd_005_njets.Clone("h_qcd_005_tt_02_njets") 
        h_qcd_005_tt_02_mtprime = h_dnncut_mtprime.Clone("h_qcd_005_tt_02_mtprime")
        h_qcd_005_tt_02_disc_qcd = h_qcd_005_disc_qcd.Clone("h_qcd_005_tt_02_disc_qcd")
        h_qcd_005_tt_02_disc_ttbar = h_qcd_005_disc_ttbar.Clone("h_qcd_005_tt_02_disc_ttbar")
        h_qcd_005_tt_02_disc_signal = h_qcd_005_disc_signal.Clone("h_qcd_005_tt_02_disc_signal")
    
        h_qcd_005_tt_03_njets = h_qcd_005_njets.Clone("h_qcd_005_tt_03_njets") 
        h_qcd_005_tt_03_mtprime = h_dnncut_mtprime.Clone("h_qcd_005_tt_03_mtprime")
        h_qcd_005_tt_03_disc_qcd = h_qcd_005_disc_qcd.Clone("h_qcd_005_tt_03_disc_qcd")
        h_qcd_005_tt_03_disc_ttbar = h_qcd_005_disc_ttbar.Clone("h_qcd_005_tt_03_disc_ttbar")
        h_qcd_005_tt_03_disc_signal = h_qcd_005_disc_signal.Clone("h_qcd_005_tt_03_disc_signal")
    
        h_qcd_005_tt_04_njets = h_qcd_005_njets.Clone("h_qcd_005_tt_04_njets") 
        h_qcd_005_tt_04_mtprime = h_dnncut_mtprime.Clone("h_qcd_005_tt_04_mtprime")
        h_qcd_005_tt_04_disc_qcd = h_qcd_005_disc_qcd.Clone("h_qcd_005_tt_04_disc_qcd")
        h_qcd_005_tt_04_disc_ttbar = h_qcd_005_disc_ttbar.Clone("h_qcd_005_tt_04_disc_ttbar")
        h_qcd_005_tt_04_disc_signal = h_qcd_005_disc_signal.Clone("h_qcd_005_tt_04_disc_signal")
    
        h_qcd_005_tt_05_njets = h_qcd_005_njets.Clone("h_qcd_005_tt_05_njets") 
        h_qcd_005_tt_05_mtprime = h_dnncut_mtprime.Clone("h_qcd_005_tt_05_mtprime")
        h_qcd_005_tt_05_disc_qcd = h_qcd_005_disc_qcd.Clone("h_qcd_005_tt_05_disc_qcd")
        h_qcd_005_tt_05_disc_ttbar = h_qcd_005_disc_ttbar.Clone("h_qcd_005_tt_05_disc_ttbar")
        h_qcd_005_tt_05_disc_signal = h_qcd_005_disc_signal.Clone("h_qcd_005_tt_05_disc_signal")
    
        h_qcd_005_tt_06_njets = h_qcd_005_njets.Clone("h_qcd_005_tt_06_njets") 
        h_qcd_005_tt_06_mtprime = h_dnncut_mtprime.Clone("h_qcd_005_tt_06_mtprime")
        h_qcd_005_tt_06_disc_qcd = h_qcd_005_disc_qcd.Clone("h_qcd_005_tt_06_disc_qcd")
        h_qcd_005_tt_06_disc_ttbar = h_qcd_005_disc_ttbar.Clone("h_qcd_005_tt_06_disc_ttbar")
        h_qcd_005_tt_06_disc_signal = h_qcd_005_disc_signal.Clone("h_qcd_005_tt_06_disc_signal")
    
        h_qcd_005_tt_07_njets = h_qcd_005_njets.Clone("h_qcd_005_tt_07_njets") 
        h_qcd_005_tt_07_mtprime = h_dnncut_mtprime.Clone("h_qcd_005_tt_07_mtprime")
        h_qcd_005_tt_07_disc_qcd = h_qcd_005_disc_qcd.Clone("h_qcd_005_tt_07_disc_qcd")
        h_qcd_005_tt_07_disc_ttbar = h_qcd_005_disc_ttbar.Clone("h_qcd_005_tt_07_disc_ttbar")
        h_qcd_005_tt_07_disc_signal = h_qcd_005_disc_signal.Clone("h_qcd_005_tt_07_disc_signal")
    
        h_qcd_005_tt_08_njets = h_qcd_005_njets.Clone("h_qcd_005_tt_08_njets") 
        h_qcd_005_tt_08_mtprime = h_dnncut_mtprime.Clone("h_qcd_005_tt_08_mtprime")
        h_qcd_005_tt_08_disc_qcd = h_qcd_005_disc_qcd.Clone("h_qcd_005_tt_08_disc_qcd")
        h_qcd_005_tt_08_disc_ttbar = h_qcd_005_disc_ttbar.Clone("h_qcd_005_tt_08_disc_ttbar")
        h_qcd_005_tt_08_disc_signal = h_qcd_005_disc_signal.Clone("h_qcd_005_tt_08_disc_signal")

        h_qcd_005_tt_09_njets = h_qcd_005_njets.Clone("h_qcd_005_tt_09_njets") 
        h_qcd_005_tt_09_mtprime = h_dnncut_mtprime.Clone("h_qcd_005_tt_09_mtprime")
        h_qcd_005_tt_09_disc_qcd = h_qcd_005_disc_qcd.Clone("h_qcd_005_tt_09_disc_qcd")
        h_qcd_005_tt_09_disc_ttbar = h_qcd_005_disc_ttbar.Clone("h_qcd_005_tt_09_disc_ttbar")
        h_qcd_005_tt_09_disc_signal = h_qcd_005_disc_signal.Clone("h_qcd_005_tt_09_disc_signal")
    
        h_qcd_01_njets = h_njets.Clone("h_qcd_01_njets") 
        h_qcd_01_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_mtprime")
        h_qcd_01_disc_qcd = h_disc_qcd.Clone("h_qcd_01_disc_qcd")
        h_qcd_01_disc_ttbar = h_disc_ttbar.Clone("h_qcd_01_disc_ttbar")
        h_qcd_01_disc_signal = h_disc_signal.Clone("h_qcd_01_disc_signal")
    
        h_qcd_02_njets = h_njets.Clone("h_qcd_02_njets") 
        h_qcd_02_mtprime = h_dnncut_mtprime.Clone("h_qcd_02_mtprime")
        h_qcd_02_disc_qcd = h_disc_qcd.Clone("h_qcd_02_disc_qcd")
        h_qcd_02_disc_ttbar = h_disc_ttbar.Clone("h_qcd_02_disc_ttbar")
        h_qcd_02_disc_signal = h_disc_signal.Clone("h_qcd_02_disc_signal")
    
        h_qcd_03_njets = h_njets.Clone("h_qcd_03_njets") 
        h_qcd_03_mtprime = h_dnncut_mtprime.Clone("h_qcd_03_mtprime")
        h_qcd_03_disc_qcd = h_disc_qcd.Clone("h_qcd_03_disc_qcd")
        h_qcd_03_disc_ttbar = h_disc_ttbar.Clone("h_qcd_03_disc_ttbar")
        h_qcd_03_disc_signal = h_disc_signal.Clone("h_qcd_03_disc_signal")
    
        h_qcd_04_njets = h_njets.Clone("h_qcd_04_njets") 
        h_qcd_04_mtprime = h_dnncut_mtprime.Clone("h_qcd_04_mtprime")
        h_qcd_04_disc_qcd = h_disc_qcd.Clone("h_qcd_04_disc_qcd")
        h_qcd_04_disc_ttbar = h_disc_ttbar.Clone("h_qcd_04_disc_ttbar")
        h_qcd_04_disc_signal = h_disc_signal.Clone("h_qcd_04_disc_signal")
    
        h_qcd_05_njets = h_njets.Clone("h_qcd_05_njets") 
        h_qcd_05_mtprime = h_dnncut_mtprime.Clone("h_qcd_05_mtprime")
        h_qcd_05_disc_qcd = h_disc_qcd.Clone("h_qcd_05_disc_qcd")
        h_qcd_05_disc_ttbar = h_disc_ttbar.Clone("h_qcd_05_disc_ttbar")
        h_qcd_05_disc_signal = h_disc_signal.Clone("h_qcd_05_disc_signal")
    
        h_qcd_06_njets = h_njets.Clone("h_qcd_06_njets") 
        h_qcd_06_mtprime = h_dnncut_mtprime.Clone("h_qcd_06_mtprime")
        h_qcd_06_disc_qcd = h_disc_qcd.Clone("h_qcd_06_disc_qcd")
        h_qcd_06_disc_ttbar = h_disc_ttbar.Clone("h_qcd_06_disc_ttbar")
        h_qcd_06_disc_signal = h_disc_signal.Clone("h_qcd_06_disc_signal")
    
        h_qcd_07_njets = h_njets.Clone("h_qcd_07_njets") 
        h_qcd_07_mtprime = h_dnncut_mtprime.Clone("h_qcd_07_mtprime")
        h_qcd_07_disc_qcd = h_disc_qcd.Clone("h_qcd_07_disc_qcd")
        h_qcd_07_disc_ttbar = h_disc_ttbar.Clone("h_qcd_07_disc_ttbar")
        h_qcd_07_disc_signal = h_disc_signal.Clone("h_qcd_07_disc_signal")
    
        h_qcd_08_njets = h_njets.Clone("h_qcd_08_njets") 
        h_qcd_08_mtprime = h_dnncut_mtprime.Clone("h_qcd_08_mtprime")
        h_qcd_08_disc_qcd = h_disc_qcd.Clone("h_qcd_08_disc_qcd")
        h_qcd_08_disc_ttbar = h_disc_ttbar.Clone("h_qcd_08_disc_ttbar")
        h_qcd_08_disc_signal = h_disc_signal.Clone("h_qcd_08_disc_signal")
    
        h_qcd_09_njets = h_njets.Clone("h_qcd_09_njets") 
        h_qcd_09_mtprime = h_dnncut_mtprime.Clone("h_qcd_09_mtprime")
        h_qcd_09_disc_qcd = h_disc_qcd.Clone("h_qcd_09_disc_qcd")
        h_qcd_09_disc_ttbar = h_disc_ttbar.Clone("h_qcd_09_disc_ttbar")
        h_qcd_09_disc_signal = h_disc_signal.Clone("h_qcd_09_disc_signal")

        h_qcd_01_tp_01_njets = h_qcd_01_njets.Clone("h_qcd_01_tp_01_njets") 
        h_qcd_01_tp_01_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tp_01_mtprime")
        h_qcd_01_tp_01_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tp_01_disc_qcd")
        h_qcd_01_tp_01_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tp_01_disc_ttbar")
        h_qcd_01_tp_01_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tp_01_disc_signal")
    
        h_qcd_01_tp_02_njets = h_qcd_01_njets.Clone("h_qcd_01_tp_02_njets") 
        h_qcd_01_tp_02_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tp_02_mtprime")
        h_qcd_01_tp_02_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tp_02_disc_qcd")
        h_qcd_01_tp_02_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tp_02_disc_ttbar")
        h_qcd_01_tp_02_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tp_02_disc_signal")
    
        h_qcd_01_tp_03_njets = h_qcd_01_njets.Clone("h_qcd_01_tp_03_njets") 
        h_qcd_01_tp_03_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tp_03_mtprime")
        h_qcd_01_tp_03_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tp_03_disc_qcd")
        h_qcd_01_tp_03_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tp_03_disc_ttbar")
        h_qcd_01_tp_03_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tp_03_disc_signal")
    
        h_qcd_01_tp_04_njets = h_qcd_01_njets.Clone("h_qcd_01_tp_04_njets") 
        h_qcd_01_tp_04_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tp_04_mtprime")
        h_qcd_01_tp_04_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tp_04_disc_qcd")
        h_qcd_01_tp_04_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tp_04_disc_ttbar")
        h_qcd_01_tp_04_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tp_04_disc_signal")
    
        h_qcd_01_tp_05_njets = h_qcd_01_njets.Clone("h_qcd_01_tp_05_njets") 
        h_qcd_01_tp_05_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tp_05_mtprime")
        h_qcd_01_tp_05_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tp_05_disc_qcd")
        h_qcd_01_tp_05_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tp_05_disc_ttbar")
        h_qcd_01_tp_05_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tp_05_disc_signal")
    
        h_qcd_01_tp_06_njets = h_qcd_01_njets.Clone("h_qcd_01_tp_06_njets") 
        h_qcd_01_tp_06_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tp_06_mtprime")
        h_qcd_01_tp_06_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tp_06_disc_qcd")
        h_qcd_01_tp_06_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tp_06_disc_ttbar")
        h_qcd_01_tp_06_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tp_06_disc_signal")
    
        h_qcd_01_tp_07_njets = h_qcd_01_njets.Clone("h_qcd_01_tp_07_njets") 
        h_qcd_01_tp_07_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tp_07_mtprime")
        h_qcd_01_tp_07_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tp_07_disc_qcd")
        h_qcd_01_tp_07_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tp_07_disc_ttbar")
        h_qcd_01_tp_07_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tp_07_disc_signal")
    
        h_qcd_01_tp_08_njets = h_qcd_01_njets.Clone("h_qcd_01_tp_08_njets") 
        h_qcd_01_tp_08_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tp_08_mtprime")
        h_qcd_01_tp_08_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tp_08_disc_qcd")
        h_qcd_01_tp_08_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tp_08_disc_ttbar")
        h_qcd_01_tp_08_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tp_08_disc_signal")
    
        h_qcd_01_tp_09_njets = h_qcd_01_njets.Clone("h_qcd_01_tp_09_njets") 
        h_qcd_01_tp_09_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tp_09_mtprime")
        h_qcd_01_tp_09_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tp_09_disc_qcd")
        h_qcd_01_tp_09_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tp_09_disc_ttbar")
        h_qcd_01_tp_09_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tp_09_disc_signal")

        h_qcd_01_tt_01_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_01_njets") 
        h_qcd_01_tt_01_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_01_mtprime")
        h_qcd_01_tt_01_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_01_disc_qcd")
        h_qcd_01_tt_01_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_01_disc_ttbar")
        h_qcd_01_tt_01_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_01_disc_signal")
    
        h_qcd_01_tt_02_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_02_njets") 
        h_qcd_01_tt_02_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_02_mtprime")
        h_qcd_01_tt_02_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_02_disc_qcd")
        h_qcd_01_tt_02_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_02_disc_ttbar")
        h_qcd_01_tt_02_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_02_disc_signal")
    
        h_qcd_01_tt_03_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_03_njets") 
        h_qcd_01_tt_03_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_03_mtprime")
        h_qcd_01_tt_03_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_03_disc_qcd")
        h_qcd_01_tt_03_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_03_disc_ttbar")
        h_qcd_01_tt_03_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_03_disc_signal")
    
        h_qcd_01_tt_04_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_04_njets") 
        h_qcd_01_tt_04_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_04_mtprime")
        h_qcd_01_tt_04_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_04_disc_qcd")
        h_qcd_01_tt_04_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_04_disc_ttbar")
        h_qcd_01_tt_04_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_04_disc_signal")
    
        h_qcd_01_tt_05_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_05_njets") 
        h_qcd_01_tt_05_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_05_mtprime")
        h_qcd_01_tt_05_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_05_disc_qcd")
        h_qcd_01_tt_05_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_05_disc_ttbar")
        h_qcd_01_tt_05_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_05_disc_signal")
    
        h_qcd_01_tt_06_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_06_njets") 
        h_qcd_01_tt_06_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_06_mtprime")
        h_qcd_01_tt_06_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_06_disc_qcd")
        h_qcd_01_tt_06_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_06_disc_ttbar")
        h_qcd_01_tt_06_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_06_disc_signal")
    
        h_qcd_01_tt_07_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_07_njets") 
        h_qcd_01_tt_07_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_07_mtprime")
        h_qcd_01_tt_07_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_07_disc_qcd")
        h_qcd_01_tt_07_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_07_disc_ttbar")
        h_qcd_01_tt_07_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_07_disc_signal")
    
        h_qcd_01_tt_08_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_08_njets") 
        h_qcd_01_tt_08_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_08_mtprime")
        h_qcd_01_tt_08_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_08_disc_qcd")
        h_qcd_01_tt_08_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_08_disc_ttbar")
        h_qcd_01_tt_08_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_08_disc_signal")

        h_qcd_01_tt_081_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_081_njets") 
        h_qcd_01_tt_081_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_081_mtprime")
        h_qcd_01_tt_081_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_081_disc_qcd")
        h_qcd_01_tt_081_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_081_disc_ttbar")
        h_qcd_01_tt_081_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_081_disc_signal")

        h_qcd_01_tt_082_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_082_njets") 
        h_qcd_01_tt_082_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_082_mtprime")
        h_qcd_01_tt_082_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_082_disc_qcd")
        h_qcd_01_tt_082_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_082_disc_ttbar")
        h_qcd_01_tt_082_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_082_disc_signal")
    
        h_qcd_01_tt_083_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_083_njets") 
        h_qcd_01_tt_083_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_083_mtprime")
        h_qcd_01_tt_083_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_083_disc_qcd")
        h_qcd_01_tt_083_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_083_disc_ttbar")
        h_qcd_01_tt_083_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_083_disc_signal")

        h_qcd_01_tt_084_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_084_njets") 
        h_qcd_01_tt_084_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_084_mtprime")
        h_qcd_01_tt_084_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_084_disc_qcd")
        h_qcd_01_tt_084_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_084_disc_ttbar")
        h_qcd_01_tt_084_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_084_disc_signal")

        h_qcd_01_tt_085_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_085_njets") 
        h_qcd_01_tt_085_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_085_mtprime")
        h_qcd_01_tt_085_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_085_disc_qcd")
        h_qcd_01_tt_085_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_085_disc_ttbar")
        h_qcd_01_tt_085_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_085_disc_signal")

        h_qcd_01_tt_086_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_086_njets") 
        h_qcd_01_tt_086_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_086_mtprime")
        h_qcd_01_tt_086_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_086_disc_qcd")
        h_qcd_01_tt_086_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_086_disc_ttbar")
        h_qcd_01_tt_086_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_086_disc_signal")

        h_qcd_01_tt_086_tp_01_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_086_tp_01_njets") 
        h_qcd_01_tt_086_tp_01_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_086_tp_01_mtprime")
        h_qcd_01_tt_086_tp_01_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_086_tp_01_disc_qcd")
        h_qcd_01_tt_086_tp_01_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_086_tp_01_disc_ttbar")
        h_qcd_01_tt_086_tp_01_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_086_tp_01_disc_signal")
        h_qcd_01_tt_086_tp_015_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_086_tp_015_njets") 
        h_qcd_01_tt_086_tp_015_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_086_tp_015_mtprime")
        h_qcd_01_tt_086_tp_015_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_086_tp_015_disc_qcd")
        h_qcd_01_tt_086_tp_015_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_086_tp_015_disc_ttbar")
        h_qcd_01_tt_086_tp_015_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_086_tp_015_disc_signal")

        h_qcd_01_tt_086_tp_02_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_086_tp_02_njets") 
        h_qcd_01_tt_086_tp_02_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_086_tp_02_mtprime")
        h_qcd_01_tt_086_tp_02_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_086_tp_02_disc_qcd")
        h_qcd_01_tt_086_tp_02_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_086_tp_02_disc_ttbar")
        h_qcd_01_tt_086_tp_02_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_086_tp_02_disc_signal")

        h_qcd_01_tt_086_tp_03_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_086_tp_03_njets") 
        h_qcd_01_tt_086_tp_03_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_086_tp_03_mtprime")
        h_qcd_01_tt_086_tp_03_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_086_tp_03_disc_qcd")
        h_qcd_01_tt_086_tp_03_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_086_tp_03_disc_ttbar")
        h_qcd_01_tt_086_tp_03_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_086_tp_03_disc_signal")

        h_qcd_01_tt_086_tp_04_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_086_tp_04_njets") 
        h_qcd_01_tt_086_tp_04_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_086_tp_04_mtprime")
        h_qcd_01_tt_086_tp_04_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_086_tp_04_disc_qcd")
        h_qcd_01_tt_086_tp_04_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_086_tp_04_disc_ttbar")
        h_qcd_01_tt_086_tp_04_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_086_tp_04_disc_signal")

        h_qcd_01_tt_086_tp_05_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_086_tp_05_njets") 
        h_qcd_01_tt_086_tp_05_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_086_tp_05_mtprime")
        h_qcd_01_tt_086_tp_05_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_086_tp_05_disc_qcd")
        h_qcd_01_tt_086_tp_05_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_086_tp_05_disc_ttbar")
        h_qcd_01_tt_086_tp_05_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_086_tp_05_disc_signal")

        h_qcd_01_tt_086_tp_06_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_086_tp_06_njets") 
        h_qcd_01_tt_086_tp_06_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_086_tp_06_mtprime")
        h_qcd_01_tt_086_tp_06_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_086_tp_06_disc_qcd")
        h_qcd_01_tt_086_tp_06_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_086_tp_06_disc_ttbar")
        h_qcd_01_tt_086_tp_06_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_086_tp_06_disc_signal")

        h_qcd_01_tt_086_tp_07_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_086_tp_07_njets") 
        h_qcd_01_tt_086_tp_07_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_086_tp_07_mtprime")
        h_qcd_01_tt_086_tp_07_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_086_tp_07_disc_qcd")
        h_qcd_01_tt_086_tp_07_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_086_tp_07_disc_ttbar")
        h_qcd_01_tt_086_tp_07_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_086_tp_07_disc_signal")

        h_qcd_01_tt_086_tp_08_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_086_tp_08_njets") 
        h_qcd_01_tt_086_tp_08_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_086_tp_08_mtprime")
        h_qcd_01_tt_086_tp_08_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_086_tp_08_disc_qcd")
        h_qcd_01_tt_086_tp_08_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_086_tp_08_disc_ttbar")
        h_qcd_01_tt_086_tp_08_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_086_tp_08_disc_signal")

        h_qcd_01_tt_086_tp_09_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_086_tp_09_njets") 
        h_qcd_01_tt_086_tp_09_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_086_tp_09_mtprime")
        h_qcd_01_tt_086_tp_09_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_086_tp_09_disc_qcd")
        h_qcd_01_tt_086_tp_09_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_086_tp_09_disc_ttbar")
        h_qcd_01_tt_086_tp_09_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_086_tp_09_disc_signal")

        h_qcd_01_tt_087_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_087_njets") 
        h_qcd_01_tt_087_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_087_mtprime")
        h_qcd_01_tt_087_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_087_disc_qcd")
        h_qcd_01_tt_087_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_087_disc_ttbar")
        h_qcd_01_tt_087_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_087_disc_signal")

        h_qcd_01_tt_088_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_088_njets") 
        h_qcd_01_tt_088_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_088_mtprime")
        h_qcd_01_tt_088_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_088_disc_qcd")
        h_qcd_01_tt_088_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_088_disc_ttbar")
        h_qcd_01_tt_088_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_088_disc_signal")

        h_qcd_01_tt_089_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_089_njets") 
        h_qcd_01_tt_089_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_089_mtprime")
        h_qcd_01_tt_089_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_089_disc_qcd")
        h_qcd_01_tt_089_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_089_disc_ttbar")
        h_qcd_01_tt_089_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_089_disc_signal")

        h_qcd_01_tt_09_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_09_njets") 
        h_qcd_01_tt_09_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_09_mtprime")
        h_qcd_01_tt_09_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_09_disc_qcd")
        h_qcd_01_tt_09_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_09_disc_ttbar")
        h_qcd_01_tt_09_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_09_disc_signal")

        h_qcd_01_tt_095_njets = h_qcd_01_njets.Clone("h_qcd_01_tt_095_njets") 
        h_qcd_01_tt_095_mtprime = h_dnncut_mtprime.Clone("h_qcd_01_tt_095_mtprime")
        h_qcd_01_tt_095_disc_qcd = h_qcd_01_disc_qcd.Clone("h_qcd_01_tt_095_disc_qcd")
        h_qcd_01_tt_095_disc_ttbar = h_qcd_01_disc_ttbar.Clone("h_qcd_01_tt_095_disc_ttbar")
        h_qcd_01_tt_095_disc_signal = h_qcd_01_disc_signal.Clone("h_qcd_01_tt_095_disc_signal")

        for index, event in selEvent.iterrows():
    
            evWeight = event['evWeight']
    
            njets = event['nseljets']
            mtprime = event['mass_tprime']
            disc_signal = event['pred_Tprime']
            disc_qcd = event['pred_QCD']
            disc_ttbar = event['pred_TTbar']

            chi2_min = event['Chi2_min']
            secondtop = event['mass_secondtop']
            hmass = event['mass_h']

            relHT = event['relht']
            chi2 = event['Chi2_max']
            dRHbb = event['dR_hbb']
            Hchi2 = event['Chi2_min_H']
            dRWjj = event['dR_wjj']
            dRbW = event['dR_bw']
    
            h_njets.Fill(njets,evWeight)
            h_dnncut_mtprime.Fill(mtprime,evWeight)
            h_disc_signal.Fill(disc_signal,evWeight)
            h_disc_ttbar.Fill(disc_ttbar,evWeight)
            h_disc_qcd.Fill(disc_qcd,evWeight)

            h_2d_mqcd.Fill(mtprime,disc_qcd,evWeight)
            h_2d_mttbar.Fill(mtprime,disc_ttbar,evWeight)
            h_2d_msignal.Fill(mtprime,disc_signal,evWeight)

            # for additional selection
            # cut 0
            if chi2_min < 15 and secondtop > 250 and hmass > 100: 
                h_cut0_mtprime.Fill(mtprime,evWeight)
                if relHT > 0.4:
                    h_cut1_mtprime.Fill(mtprime,evWeight)
                    if chi2 < 3:
                        h_cut2_mtprime.Fill(mtprime,evWeight)
                        h_cut2_2d.Fill(mtprime,dRHbb,evWeight)
                        if dRHbb < 1.1:
                            h_cut3_mtprime.Fill(mtprime,evWeight)
                            if Hchi2 < 1.5:
                                h_cut4_mtprime.Fill(mtprime,evWeight)
                                if dRWjj < 1.75:
                                    h_cut5_mtprime.Fill(mtprime,evWeight)
                                    if dRbW < 1.2:
                                        h_cut6_mtprime.Fill(mtprime,evWeight)
            if disc_signal > 0.1:
                h_tp_01_njets.Fill(njets,evWeight)
                h_tp_01_mtprime.Fill(mtprime,evWeight)
                h_tp_01_disc_qcd.Fill(disc_qcd,evWeight)
                h_tp_01_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_tp_01_disc_signal.Fill(disc_signal,evWeight)

            if disc_signal > 0.2:
                h_tp_02_njets.Fill(njets,evWeight)
                h_tp_02_mtprime.Fill(mtprime,evWeight)
                h_tp_02_disc_qcd.Fill(disc_qcd,evWeight)
                h_tp_02_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_tp_02_disc_signal.Fill(disc_signal,evWeight)

            if disc_signal > 0.3:
                h_tp_03_njets.Fill(njets,evWeight)
                h_tp_03_mtprime.Fill(mtprime,evWeight)
                h_tp_03_disc_qcd.Fill(disc_qcd,evWeight)
                h_tp_03_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_tp_03_disc_signal.Fill(disc_signal,evWeight)

            if disc_signal > 0.4:
                h_tp_04_njets.Fill(njets,evWeight)
                h_tp_04_mtprime.Fill(mtprime,evWeight)
                h_tp_04_disc_qcd.Fill(disc_qcd,evWeight)
                h_tp_04_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_tp_04_disc_signal.Fill(disc_signal,evWeight)

            if disc_signal > 0.5:
                h_tp_05_njets.Fill(njets,evWeight)
                h_tp_05_mtprime.Fill(mtprime,evWeight)
                h_tp_05_disc_qcd.Fill(disc_qcd,evWeight)
                h_tp_05_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_tp_05_disc_signal.Fill(disc_signal,evWeight)

            if disc_signal > 0.6:
                h_tp_06_njets.Fill(njets,evWeight)
                h_tp_06_mtprime.Fill(mtprime,evWeight)
                h_tp_06_disc_qcd.Fill(disc_qcd,evWeight)
                h_tp_06_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_tp_06_disc_signal.Fill(disc_signal,evWeight)

            if disc_signal > 0.7:
                h_tp_07_njets.Fill(njets,evWeight)
                h_tp_07_mtprime.Fill(mtprime,evWeight)
                h_tp_07_disc_qcd.Fill(disc_qcd,evWeight)
                h_tp_07_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_tp_07_disc_signal.Fill(disc_signal,evWeight)

            if disc_signal > 0.8:
                h_tp_08_njets.Fill(njets,evWeight)
                h_tp_08_mtprime.Fill(mtprime,evWeight)
                h_tp_08_disc_qcd.Fill(disc_qcd,evWeight)
                h_tp_08_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_tp_08_disc_signal.Fill(disc_signal,evWeight)

            if disc_signal > 0.9:
                h_tp_09_njets.Fill(njets,evWeight)
                h_tp_09_mtprime.Fill(mtprime,evWeight)
                h_tp_09_disc_qcd.Fill(disc_qcd,evWeight)
                h_tp_09_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_tp_09_disc_signal.Fill(disc_signal,evWeight)

            if disc_ttbar <  0.1:
                h_tt_01_njets.Fill(njets,evWeight)
                h_tt_01_mtprime.Fill(mtprime,evWeight)
                h_tt_01_disc_qcd.Fill(disc_qcd,evWeight)
                h_tt_01_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_tt_01_disc_signal.Fill(disc_signal,evWeight)
    
            if disc_ttbar <  0.2:
                h_tt_02_njets.Fill(njets,evWeight)
                h_tt_02_mtprime.Fill(mtprime,evWeight)
                h_tt_02_disc_qcd.Fill(disc_qcd,evWeight)
                h_tt_02_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_tt_02_disc_signal.Fill(disc_signal,evWeight)
    
            if disc_ttbar <  0.3:
                h_tt_03_njets.Fill(njets,evWeight)
                h_tt_03_mtprime.Fill(mtprime,evWeight)
                h_tt_03_disc_qcd.Fill(disc_qcd,evWeight)
                h_tt_03_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_tt_03_disc_signal.Fill(disc_signal,evWeight)
    
            if disc_ttbar <  0.4:
                h_tt_04_njets.Fill(njets,evWeight)
                h_tt_04_mtprime.Fill(mtprime,evWeight)
                h_tt_04_disc_qcd.Fill(disc_qcd,evWeight)
                h_tt_04_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_tt_04_disc_signal.Fill(disc_signal,evWeight)

            if disc_ttbar <  0.5:
                h_tt_05_njets.Fill(njets,evWeight)
                h_tt_05_mtprime.Fill(mtprime,evWeight)
                h_tt_05_disc_qcd.Fill(disc_qcd,evWeight)
                h_tt_05_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_tt_05_disc_signal.Fill(disc_signal,evWeight)
    
            if disc_ttbar <  0.6:
                h_tt_06_njets.Fill(njets,evWeight)
                h_tt_06_mtprime.Fill(mtprime,evWeight)
                h_tt_06_disc_qcd.Fill(disc_qcd,evWeight)
                h_tt_06_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_tt_06_disc_signal.Fill(disc_signal,evWeight)
    
            if disc_ttbar <  0.7:
                h_tt_07_njets.Fill(njets,evWeight)
                h_tt_07_mtprime.Fill(mtprime,evWeight)
                h_tt_07_disc_qcd.Fill(disc_qcd,evWeight)
                h_tt_07_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_tt_07_disc_signal.Fill(disc_signal,evWeight)
    
            if disc_ttbar <  0.8:
                h_tt_08_njets.Fill(njets,evWeight)
                h_tt_08_mtprime.Fill(mtprime,evWeight)
                h_tt_08_disc_qcd.Fill(disc_qcd,evWeight)
                h_tt_08_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_tt_08_disc_signal.Fill(disc_signal,evWeight)
    
            if disc_ttbar <  0.9:
                h_tt_09_njets.Fill(njets,evWeight)
                h_tt_09_mtprime.Fill(mtprime,evWeight)
                h_tt_09_disc_qcd.Fill(disc_qcd,evWeight)
                h_tt_09_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_tt_09_disc_signal.Fill(disc_signal,evWeight)

            if disc_qcd <  0.01:
                h_qcd_001_njets.Fill(njets,evWeight)
                h_qcd_001_mtprime.Fill(mtprime,evWeight)
                h_qcd_001_disc_qcd.Fill(disc_qcd,evWeight)
                h_qcd_001_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_qcd_001_disc_signal.Fill(disc_signal,evWeight)

            if disc_qcd <  0.05:
                h_qcd_005_njets.Fill(njets,evWeight)
                h_qcd_005_mtprime.Fill(mtprime,evWeight)
                h_qcd_005_disc_qcd.Fill(disc_qcd,evWeight)
                h_qcd_005_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_qcd_005_disc_signal.Fill(disc_signal,evWeight)

                if disc_ttbar <  0.1:
                    h_qcd_005_tt_01_njets.Fill(njets,evWeight)
                    h_qcd_005_tt_01_mtprime.Fill(mtprime,evWeight)
                    h_qcd_005_tt_01_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_005_tt_01_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_005_tt_01_disc_signal.Fill(disc_signal,evWeight)
    
                if disc_ttbar <  0.2:
                    h_qcd_005_tt_02_njets.Fill(njets,evWeight)
                    h_qcd_005_tt_02_mtprime.Fill(mtprime,evWeight)
                    h_qcd_005_tt_02_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_005_tt_02_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_005_tt_02_disc_signal.Fill(disc_signal,evWeight)
    
                if disc_ttbar <  0.3:
                    h_qcd_005_tt_03_njets.Fill(njets,evWeight)
                    h_qcd_005_tt_03_mtprime.Fill(mtprime,evWeight)
                    h_qcd_005_tt_03_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_005_tt_03_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_005_tt_03_disc_signal.Fill(disc_signal,evWeight)
    
                if disc_ttbar <  0.4:
                    h_qcd_005_tt_04_njets.Fill(njets,evWeight)
                    h_qcd_005_tt_04_mtprime.Fill(mtprime,evWeight)
                    h_qcd_005_tt_04_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_005_tt_04_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_005_tt_04_disc_signal.Fill(disc_signal,evWeight)

                if disc_ttbar <  0.5:
                    h_qcd_005_tt_05_njets.Fill(njets,evWeight)
                    h_qcd_005_tt_05_mtprime.Fill(mtprime,evWeight)
                    h_qcd_005_tt_05_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_005_tt_05_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_005_tt_05_disc_signal.Fill(disc_signal,evWeight)
    
                if disc_ttbar <  0.6:
                    h_qcd_005_tt_06_njets.Fill(njets,evWeight)
                    h_qcd_005_tt_06_mtprime.Fill(mtprime,evWeight)
                    h_qcd_005_tt_06_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_005_tt_06_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_005_tt_06_disc_signal.Fill(disc_signal,evWeight)
    
                if disc_ttbar <  0.7:
                    h_qcd_005_tt_07_njets.Fill(njets,evWeight)
                    h_qcd_005_tt_07_mtprime.Fill(mtprime,evWeight)
                    h_qcd_005_tt_07_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_005_tt_07_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_005_tt_07_disc_signal.Fill(disc_signal,evWeight)
    
                if disc_ttbar <  0.8:
                    h_qcd_005_tt_08_njets.Fill(njets,evWeight)
                    h_qcd_005_tt_08_mtprime.Fill(mtprime,evWeight)
                    h_qcd_005_tt_08_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_005_tt_08_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_005_tt_08_disc_signal.Fill(disc_signal,evWeight)
    
                if disc_ttbar <  0.9:
                    h_qcd_005_tt_09_njets.Fill(njets,evWeight)
                    h_qcd_005_tt_09_mtprime.Fill(mtprime,evWeight)
                    h_qcd_005_tt_09_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_005_tt_09_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_005_tt_09_disc_signal.Fill(disc_signal,evWeight)

            if disc_qcd <  0.1:
                h_qcd_01_njets.Fill(njets,evWeight)
                h_qcd_01_mtprime.Fill(mtprime,evWeight)
                h_qcd_01_disc_qcd.Fill(disc_qcd,evWeight)
                h_qcd_01_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_qcd_01_disc_signal.Fill(disc_signal,evWeight)
                
                if disc_signal > 0.1:
                    h_qcd_01_tp_01_njets.Fill(njets,evWeight)
                    h_qcd_01_tp_01_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tp_01_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tp_01_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tp_01_disc_signal.Fill(disc_signal,evWeight)

                if disc_signal > 0.2:
                    h_qcd_01_tp_02_njets.Fill(njets,evWeight)
                    h_qcd_01_tp_02_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tp_02_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tp_02_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tp_02_disc_signal.Fill(disc_signal,evWeight)

                if disc_signal > 0.3:
                    h_qcd_01_tp_03_njets.Fill(njets,evWeight)
                    h_qcd_01_tp_03_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tp_03_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tp_03_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tp_03_disc_signal.Fill(disc_signal,evWeight)

                if disc_signal > 0.4:
                    h_qcd_01_tp_04_njets.Fill(njets,evWeight)
                    h_qcd_01_tp_04_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tp_04_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tp_04_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tp_04_disc_signal.Fill(disc_signal,evWeight)

                if disc_signal > 0.5:
                    h_qcd_01_tp_05_njets.Fill(njets,evWeight)
                    h_qcd_01_tp_05_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tp_05_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tp_05_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tp_05_disc_signal.Fill(disc_signal,evWeight)

                if disc_signal > 0.6:
                    h_qcd_01_tp_06_njets.Fill(njets,evWeight)
                    h_qcd_01_tp_06_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tp_06_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tp_06_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tp_06_disc_signal.Fill(disc_signal,evWeight)

                if disc_signal > 0.7:
                    h_qcd_01_tp_07_njets.Fill(njets,evWeight)
                    h_qcd_01_tp_07_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tp_07_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tp_07_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tp_07_disc_signal.Fill(disc_signal,evWeight)

                if disc_signal > 0.8:
                    h_qcd_01_tp_08_njets.Fill(njets,evWeight)
                    h_qcd_01_tp_08_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tp_08_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tp_08_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tp_08_disc_signal.Fill(disc_signal,evWeight)

                if disc_signal > 0.9:
                    h_qcd_01_tp_09_njets.Fill(njets,evWeight)
                    h_qcd_01_tp_09_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tp_09_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tp_09_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tp_09_disc_signal.Fill(disc_signal,evWeight)

                if disc_ttbar <  0.1:
                    h_qcd_01_tt_01_njets.Fill(njets,evWeight)
                    h_qcd_01_tt_01_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tt_01_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tt_01_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tt_01_disc_signal.Fill(disc_signal,evWeight)
    
                if disc_ttbar <  0.2:
                    h_qcd_01_tt_02_njets.Fill(njets,evWeight)
                    h_qcd_01_tt_02_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tt_02_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tt_02_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tt_02_disc_signal.Fill(disc_signal,evWeight)
    
                if disc_ttbar <  0.3:
                    h_qcd_01_tt_03_njets.Fill(njets,evWeight)
                    h_qcd_01_tt_03_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tt_03_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tt_03_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tt_03_disc_signal.Fill(disc_signal,evWeight)
    
                if disc_ttbar <  0.4:
                    h_qcd_01_tt_04_njets.Fill(njets,evWeight)
                    h_qcd_01_tt_04_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tt_04_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tt_04_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tt_04_disc_signal.Fill(disc_signal,evWeight)

                if disc_ttbar <  0.5:
                    h_qcd_01_tt_05_njets.Fill(njets,evWeight)
                    h_qcd_01_tt_05_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tt_05_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tt_05_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tt_05_disc_signal.Fill(disc_signal,evWeight)
    
                if disc_ttbar <  0.6:
                    h_qcd_01_tt_06_njets.Fill(njets,evWeight)
                    h_qcd_01_tt_06_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tt_06_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tt_06_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tt_06_disc_signal.Fill(disc_signal,evWeight)
    
                if disc_ttbar <  0.7:
                    h_qcd_01_tt_07_njets.Fill(njets,evWeight)
                    h_qcd_01_tt_07_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tt_07_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tt_07_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tt_07_disc_signal.Fill(disc_signal,evWeight)
    
                if disc_ttbar <  0.8:
                    h_qcd_01_tt_08_njets.Fill(njets,evWeight)
                    h_qcd_01_tt_08_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tt_08_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tt_08_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tt_08_disc_signal.Fill(disc_signal,evWeight)
    
                if disc_ttbar <  0.81:
                    h_qcd_01_tt_081_njets.Fill(njets,evWeight)
                    h_qcd_01_tt_081_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tt_081_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tt_081_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tt_081_disc_signal.Fill(disc_signal,evWeight)

                if disc_ttbar <  0.82:
                    h_qcd_01_tt_082_njets.Fill(njets,evWeight)
                    h_qcd_01_tt_082_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tt_082_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tt_082_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tt_082_disc_signal.Fill(disc_signal,evWeight)

                if disc_ttbar <  0.83:
                    h_qcd_01_tt_083_njets.Fill(njets,evWeight)
                    h_qcd_01_tt_083_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tt_083_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tt_083_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tt_083_disc_signal.Fill(disc_signal,evWeight)

                if disc_ttbar <  0.84:
                    h_qcd_01_tt_084_njets.Fill(njets,evWeight)
                    h_qcd_01_tt_084_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tt_084_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tt_084_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tt_084_disc_signal.Fill(disc_signal,evWeight)
    
                if disc_ttbar <  0.85:
                    h_qcd_01_tt_085_njets.Fill(njets,evWeight)
                    h_qcd_01_tt_085_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tt_085_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tt_085_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tt_085_disc_signal.Fill(disc_signal,evWeight)

                if disc_ttbar <  0.86:
                    h_qcd_01_tt_086_njets.Fill(njets,evWeight)
                    h_qcd_01_tt_086_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tt_086_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tt_086_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tt_086_disc_signal.Fill(disc_signal,evWeight)

                    if disc_signal > 0.1:
                        h_qcd_01_tt_086_tp_01_njets.Fill(njets,evWeight)
                        h_qcd_01_tt_086_tp_01_mtprime.Fill(mtprime,evWeight)
                        h_qcd_01_tt_086_tp_01_disc_qcd.Fill(disc_qcd,evWeight)
                        h_qcd_01_tt_086_tp_01_disc_ttbar.Fill(disc_ttbar,evWeight)
                        h_qcd_01_tt_086_tp_01_disc_signal.Fill(disc_signal,evWeight)

                    if disc_signal > 0.15:
                        h_qcd_01_tt_086_tp_015_njets.Fill(njets,evWeight)
                        h_qcd_01_tt_086_tp_015_mtprime.Fill(mtprime,evWeight)
                        h_qcd_01_tt_086_tp_015_disc_qcd.Fill(disc_qcd,evWeight)
                        h_qcd_01_tt_086_tp_015_disc_ttbar.Fill(disc_ttbar,evWeight)
                        h_qcd_01_tt_086_tp_015_disc_signal.Fill(disc_signal,evWeight)

                    if disc_signal > 0.2:
                        h_qcd_01_tt_086_tp_02_njets.Fill(njets,evWeight)
                        h_qcd_01_tt_086_tp_02_mtprime.Fill(mtprime,evWeight)
                        h_qcd_01_tt_086_tp_02_disc_qcd.Fill(disc_qcd,evWeight)
                        h_qcd_01_tt_086_tp_02_disc_ttbar.Fill(disc_ttbar,evWeight)
                        h_qcd_01_tt_086_tp_02_disc_signal.Fill(disc_signal,evWeight)

                    if disc_signal > 0.3:
                        h_qcd_01_tt_086_tp_03_njets.Fill(njets,evWeight)
                        h_qcd_01_tt_086_tp_03_mtprime.Fill(mtprime,evWeight)
                        h_qcd_01_tt_086_tp_03_disc_qcd.Fill(disc_qcd,evWeight)
                        h_qcd_01_tt_086_tp_03_disc_ttbar.Fill(disc_ttbar,evWeight)
                        h_qcd_01_tt_086_tp_03_disc_signal.Fill(disc_signal,evWeight)

                    if disc_signal > 0.4:
                        h_qcd_01_tt_086_tp_04_njets.Fill(njets,evWeight)
                        h_qcd_01_tt_086_tp_04_mtprime.Fill(mtprime,evWeight)
                        h_qcd_01_tt_086_tp_04_disc_qcd.Fill(disc_qcd,evWeight)
                        h_qcd_01_tt_086_tp_04_disc_ttbar.Fill(disc_ttbar,evWeight)
                        h_qcd_01_tt_086_tp_04_disc_signal.Fill(disc_signal,evWeight)

                    if disc_signal > 0.5:
                        h_qcd_01_tt_086_tp_05_njets.Fill(njets,evWeight)
                        h_qcd_01_tt_086_tp_05_mtprime.Fill(mtprime,evWeight)
                        h_qcd_01_tt_086_tp_05_disc_qcd.Fill(disc_qcd,evWeight)
                        h_qcd_01_tt_086_tp_05_disc_ttbar.Fill(disc_ttbar,evWeight)
                        h_qcd_01_tt_086_tp_05_disc_signal.Fill(disc_signal,evWeight)

                    if disc_signal > 0.6:
                        h_qcd_01_tt_086_tp_06_njets.Fill(njets,evWeight)
                        h_qcd_01_tt_086_tp_06_mtprime.Fill(mtprime,evWeight)
                        h_qcd_01_tt_086_tp_06_disc_qcd.Fill(disc_qcd,evWeight)
                        h_qcd_01_tt_086_tp_06_disc_ttbar.Fill(disc_ttbar,evWeight)
                        h_qcd_01_tt_086_tp_06_disc_signal.Fill(disc_signal,evWeight)

                    if disc_signal > 0.7:
                        h_qcd_01_tt_086_tp_07_njets.Fill(njets,evWeight)
                        h_qcd_01_tt_086_tp_07_mtprime.Fill(mtprime,evWeight)
                        h_qcd_01_tt_086_tp_07_disc_qcd.Fill(disc_qcd,evWeight)
                        h_qcd_01_tt_086_tp_07_disc_ttbar.Fill(disc_ttbar,evWeight)
                        h_qcd_01_tt_086_tp_07_disc_signal.Fill(disc_signal,evWeight)

                    if disc_signal > 0.8:
                        h_qcd_01_tt_086_tp_08_njets.Fill(njets,evWeight)
                        h_qcd_01_tt_086_tp_08_mtprime.Fill(mtprime,evWeight)
                        h_qcd_01_tt_086_tp_08_disc_qcd.Fill(disc_qcd,evWeight)
                        h_qcd_01_tt_086_tp_08_disc_ttbar.Fill(disc_ttbar,evWeight)
                        h_qcd_01_tt_086_tp_08_disc_signal.Fill(disc_signal,evWeight)

                    if disc_signal > 0.9:
                        h_qcd_01_tt_086_tp_09_njets.Fill(njets,evWeight)
                        h_qcd_01_tt_086_tp_09_mtprime.Fill(mtprime,evWeight)
                        h_qcd_01_tt_086_tp_09_disc_qcd.Fill(disc_qcd,evWeight)
                        h_qcd_01_tt_086_tp_09_disc_ttbar.Fill(disc_ttbar,evWeight)
                        h_qcd_01_tt_086_tp_09_disc_signal.Fill(disc_signal,evWeight)

                if disc_ttbar <  0.87:
                    h_qcd_01_tt_087_njets.Fill(njets,evWeight)
                    h_qcd_01_tt_087_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tt_087_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tt_087_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tt_087_disc_signal.Fill(disc_signal,evWeight)

                if disc_ttbar <  0.88:
                    h_qcd_01_tt_088_njets.Fill(njets,evWeight)
                    h_qcd_01_tt_088_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tt_088_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tt_088_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tt_088_disc_signal.Fill(disc_signal,evWeight)

                if disc_ttbar <  0.89:
                    h_qcd_01_tt_089_njets.Fill(njets,evWeight)
                    h_qcd_01_tt_089_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tt_089_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tt_089_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tt_089_disc_signal.Fill(disc_signal,evWeight)

                if disc_ttbar <  0.9:
                    h_qcd_01_tt_09_njets.Fill(njets,evWeight)
                    h_qcd_01_tt_09_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tt_09_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tt_09_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tt_09_disc_signal.Fill(disc_signal,evWeight)

                if disc_ttbar <  0.95:
                    h_qcd_01_tt_095_njets.Fill(njets,evWeight)
                    h_qcd_01_tt_095_mtprime.Fill(mtprime,evWeight)
                    h_qcd_01_tt_095_disc_qcd.Fill(disc_qcd,evWeight)
                    h_qcd_01_tt_095_disc_ttbar.Fill(disc_ttbar,evWeight)
                    h_qcd_01_tt_095_disc_signal.Fill(disc_signal,evWeight)
    
            if disc_qcd <  0.2:
                h_qcd_02_njets.Fill(njets,evWeight)
                h_qcd_02_mtprime.Fill(mtprime,evWeight)
                h_qcd_02_disc_qcd.Fill(disc_qcd,evWeight)
                h_qcd_02_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_qcd_02_disc_signal.Fill(disc_signal,evWeight)
    
            if disc_qcd <  0.3:
                h_qcd_03_njets.Fill(njets,evWeight)
                h_qcd_03_mtprime.Fill(mtprime,evWeight)
                h_qcd_03_disc_qcd.Fill(disc_qcd,evWeight)
                h_qcd_03_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_qcd_03_disc_signal.Fill(disc_signal,evWeight)
    
            if disc_qcd <  0.4:
                h_qcd_04_njets.Fill(njets,evWeight)
                h_qcd_04_mtprime.Fill(mtprime,evWeight)
                h_qcd_04_disc_qcd.Fill(disc_qcd,evWeight)
                h_qcd_04_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_qcd_04_disc_signal.Fill(disc_signal,evWeight)

            if disc_qcd <  0.5:
                h_qcd_05_njets.Fill(njets,evWeight)
                h_qcd_05_mtprime.Fill(mtprime,evWeight)
                h_qcd_05_disc_qcd.Fill(disc_qcd,evWeight)
                h_qcd_05_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_qcd_05_disc_signal.Fill(disc_signal,evWeight)
    
            if disc_qcd <  0.6:
                h_qcd_06_njets.Fill(njets,evWeight)
                h_qcd_06_mtprime.Fill(mtprime,evWeight)
                h_qcd_06_disc_qcd.Fill(disc_qcd,evWeight)
                h_qcd_06_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_qcd_06_disc_signal.Fill(disc_signal,evWeight)
    
            if disc_qcd <  0.7:
                h_qcd_07_njets.Fill(njets,evWeight)
                h_qcd_07_mtprime.Fill(mtprime,evWeight)
                h_qcd_07_disc_qcd.Fill(disc_qcd,evWeight)
                h_qcd_07_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_qcd_07_disc_signal.Fill(disc_signal,evWeight)
    
            if disc_qcd <  0.8:
                h_qcd_08_njets.Fill(njets,evWeight)
                h_qcd_08_mtprime.Fill(mtprime,evWeight)
                h_qcd_08_disc_qcd.Fill(disc_qcd,evWeight)
                h_qcd_08_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_qcd_08_disc_signal.Fill(disc_signal,evWeight)
    
            if disc_qcd <  0.9:
                h_qcd_09_njets.Fill(njets,evWeight)
                h_qcd_09_mtprime.Fill(mtprime,evWeight)
                h_qcd_09_disc_qcd.Fill(disc_qcd,evWeight)
                h_qcd_09_disc_ttbar.Fill(disc_ttbar,evWeight)
                h_qcd_09_disc_signal.Fill(disc_signal,evWeight)
    
        #outtree.Fill()
   
        h_dnncut_mtprime.Write()
        h_cut0_mtprime.Write()
        h_cut1_mtprime.Write()
        h_cut2_mtprime.Write()
        h_cut3_mtprime.Write()
        h_cut4_mtprime.Write()
        h_cut5_mtprime.Write()
        h_cut6_mtprime.Write()

        h_cut2_2d.Write()
        h_2d_mqcd.Write()
        h_2d_mttbar.Write()
        h_2d_msignal.Write()

        h_njets.Write() 
        h_disc_qcd.Write()
        h_disc_ttbar.Write()
        h_disc_signal.Write()

        h_tp_01_njets.Write() 
        h_tp_01_mtprime.Write()
        h_tp_01_disc_qcd.Write()
        h_tp_01_disc_ttbar.Write()
        h_tp_01_disc_signal.Write()

        h_tp_02_njets.Write() 
        h_tp_02_mtprime.Write()
        h_tp_02_disc_qcd.Write()
        h_tp_02_disc_ttbar.Write()
        h_tp_02_disc_signal.Write()

        h_tp_03_njets.Write() 
        h_tp_03_mtprime.Write()
        h_tp_03_disc_qcd.Write()
        h_tp_03_disc_ttbar.Write()
        h_tp_03_disc_signal.Write()

        h_tp_04_njets.Write() 
        h_tp_04_mtprime.Write()
        h_tp_04_disc_qcd.Write()
        h_tp_04_disc_ttbar.Write()
        h_tp_04_disc_signal.Write()

        h_tp_05_njets.Write() 
        h_tp_05_mtprime.Write()
        h_tp_05_disc_qcd.Write()
        h_tp_05_disc_ttbar.Write()
        h_tp_05_disc_signal.Write()

        h_tp_06_njets.Write() 
        h_tp_06_mtprime.Write()
        h_tp_06_disc_qcd.Write()
        h_tp_06_disc_ttbar.Write()
        h_tp_06_disc_signal.Write()

        h_tp_07_njets.Write() 
        h_tp_07_mtprime.Write()
        h_tp_07_disc_qcd.Write()
        h_tp_07_disc_ttbar.Write()
        h_tp_07_disc_signal.Write()

        h_tp_08_njets.Write() 
        h_tp_08_mtprime.Write()
        h_tp_08_disc_qcd.Write()
        h_tp_08_disc_ttbar.Write()
        h_tp_08_disc_signal.Write()

        h_tp_09_njets.Write() 
        h_tp_09_mtprime.Write()
        h_tp_09_disc_qcd.Write()
        h_tp_09_disc_ttbar.Write()
        h_tp_09_disc_signal.Write()

        h_tt_01_njets.Write() 
        h_tt_01_mtprime.Write()
        h_tt_01_disc_qcd.Write()
        h_tt_01_disc_ttbar.Write()
        h_tt_01_disc_signal.Write()

        h_tt_02_njets.Write() 
        h_tt_02_mtprime.Write()
        h_tt_02_disc_qcd.Write()
        h_tt_02_disc_ttbar.Write()
        h_tt_02_disc_signal.Write()

        h_tt_03_njets.Write() 
        h_tt_03_mtprime.Write()
        h_tt_03_disc_qcd.Write()
        h_tt_03_disc_ttbar.Write()
        h_tt_03_disc_signal.Write()

        h_tt_04_njets.Write() 
        h_tt_04_mtprime.Write()
        h_tt_04_disc_qcd.Write()
        h_tt_04_disc_ttbar.Write()
        h_tt_04_disc_signal.Write()

        h_tt_05_njets.Write() 
        h_tt_05_mtprime.Write()
        h_tt_05_disc_qcd.Write()
        h_tt_05_disc_ttbar.Write()
        h_tt_05_disc_signal.Write()

        h_tt_06_njets.Write() 
        h_tt_06_mtprime.Write()
        h_tt_06_disc_qcd.Write()
        h_tt_06_disc_ttbar.Write()
        h_tt_06_disc_signal.Write()

        h_tt_07_njets.Write() 
        h_tt_07_mtprime.Write()
        h_tt_07_disc_qcd.Write()
        h_tt_07_disc_ttbar.Write()
        h_tt_07_disc_signal.Write()

        h_tt_08_njets.Write() 
        h_tt_08_mtprime.Write()
        h_tt_08_disc_qcd.Write()
        h_tt_08_disc_ttbar.Write()
        h_tt_08_disc_signal.Write()

        h_tt_09_njets.Write() 
        h_tt_09_mtprime.Write()
        h_tt_09_disc_qcd.Write()
        h_tt_09_disc_ttbar.Write()
        h_tt_09_disc_signal.Write()

        h_qcd_001_njets.Write() 
        h_qcd_001_mtprime.Write()
        h_qcd_001_disc_qcd.Write()
        h_qcd_001_disc_ttbar.Write()
        h_qcd_001_disc_signal.Write()

        h_qcd_005_njets.Write() 
        h_qcd_005_mtprime.Write()
        h_qcd_005_disc_qcd.Write()
        h_qcd_005_disc_ttbar.Write()
        h_qcd_005_disc_signal.Write()

        h_qcd_005_tt_01_njets.Write() 
        h_qcd_005_tt_01_mtprime.Write()
        h_qcd_005_tt_01_disc_qcd.Write()
        h_qcd_005_tt_01_disc_ttbar.Write()
        h_qcd_005_tt_01_disc_signal.Write()

        h_qcd_005_tt_02_njets.Write() 
        h_qcd_005_tt_02_mtprime.Write()
        h_qcd_005_tt_02_disc_qcd.Write()
        h_qcd_005_tt_02_disc_ttbar.Write()
        h_qcd_005_tt_02_disc_signal.Write()

        h_qcd_005_tt_03_njets.Write() 
        h_qcd_005_tt_03_mtprime.Write()
        h_qcd_005_tt_03_disc_qcd.Write()
        h_qcd_005_tt_03_disc_ttbar.Write()
        h_qcd_005_tt_03_disc_signal.Write()

        h_qcd_005_tt_04_njets.Write() 
        h_qcd_005_tt_04_mtprime.Write()
        h_qcd_005_tt_04_disc_qcd.Write()
        h_qcd_005_tt_04_disc_ttbar.Write()
        h_qcd_005_tt_04_disc_signal.Write()

        h_qcd_005_tt_05_njets.Write() 
        h_qcd_005_tt_05_mtprime.Write()
        h_qcd_005_tt_05_disc_qcd.Write()
        h_qcd_005_tt_05_disc_ttbar.Write()
        h_qcd_005_tt_05_disc_signal.Write()

        h_qcd_005_tt_06_njets.Write() 
        h_qcd_005_tt_06_mtprime.Write()
        h_qcd_005_tt_06_disc_qcd.Write()
        h_qcd_005_tt_06_disc_ttbar.Write()
        h_qcd_005_tt_06_disc_signal.Write()

        h_qcd_005_tt_07_njets.Write() 
        h_qcd_005_tt_07_mtprime.Write()
        h_qcd_005_tt_07_disc_qcd.Write()
        h_qcd_005_tt_07_disc_ttbar.Write()
        h_qcd_005_tt_07_disc_signal.Write()

        h_qcd_005_tt_08_njets.Write() 
        h_qcd_005_tt_08_mtprime.Write()
        h_qcd_005_tt_08_disc_qcd.Write()
        h_qcd_005_tt_08_disc_ttbar.Write()
        h_qcd_005_tt_08_disc_signal.Write()

        h_qcd_005_tt_09_njets.Write() 
        h_qcd_005_tt_09_mtprime.Write()
        h_qcd_005_tt_09_disc_qcd.Write()
        h_qcd_005_tt_09_disc_ttbar.Write()
        h_qcd_005_tt_09_disc_signal.Write()

        h_qcd_01_njets.Write() 
        h_qcd_01_mtprime.Write()
        h_qcd_01_disc_qcd.Write()
        h_qcd_01_disc_ttbar.Write()
        h_qcd_01_disc_signal.Write()

        h_qcd_02_njets.Write() 
        h_qcd_02_mtprime.Write()
        h_qcd_02_disc_qcd.Write()
        h_qcd_02_disc_ttbar.Write()
        h_qcd_02_disc_signal.Write()

        h_qcd_03_njets.Write() 
        h_qcd_03_mtprime.Write()
        h_qcd_03_disc_qcd.Write()
        h_qcd_03_disc_ttbar.Write()
        h_qcd_03_disc_signal.Write()

        h_qcd_04_njets.Write() 
        h_qcd_04_mtprime.Write()
        h_qcd_04_disc_qcd.Write()
        h_qcd_04_disc_ttbar.Write()
        h_qcd_04_disc_signal.Write()

        h_qcd_05_njets.Write() 
        h_qcd_05_mtprime.Write()
        h_qcd_05_disc_qcd.Write()
        h_qcd_05_disc_ttbar.Write()
        h_qcd_05_disc_signal.Write()

        h_qcd_06_njets.Write() 
        h_qcd_06_mtprime.Write()
        h_qcd_06_disc_qcd.Write()
        h_qcd_06_disc_ttbar.Write()
        h_qcd_06_disc_signal.Write()

        h_qcd_07_njets.Write() 
        h_qcd_07_mtprime.Write()
        h_qcd_07_disc_qcd.Write()
        h_qcd_07_disc_ttbar.Write()
        h_qcd_07_disc_signal.Write()

        h_qcd_08_njets.Write() 
        h_qcd_08_mtprime.Write()
        h_qcd_08_disc_qcd.Write()
        h_qcd_08_disc_ttbar.Write()
        h_qcd_08_disc_signal.Write()

        h_qcd_09_njets.Write() 
        h_qcd_09_mtprime.Write()
        h_qcd_09_disc_qcd.Write()
        h_qcd_09_disc_ttbar.Write()
        h_qcd_09_disc_signal.Write()

        h_qcd_01_tp_01_njets.Write() 
        h_qcd_01_tp_01_mtprime.Write()
        h_qcd_01_tp_01_disc_qcd.Write()
        h_qcd_01_tp_01_disc_ttbar.Write()
        h_qcd_01_tp_01_disc_signal.Write()

        h_qcd_01_tp_02_njets.Write() 
        h_qcd_01_tp_02_mtprime.Write()
        h_qcd_01_tp_02_disc_qcd.Write()
        h_qcd_01_tp_02_disc_ttbar.Write()
        h_qcd_01_tp_02_disc_signal.Write()

        h_qcd_01_tp_03_njets.Write() 
        h_qcd_01_tp_03_mtprime.Write()
        h_qcd_01_tp_03_disc_qcd.Write()
        h_qcd_01_tp_03_disc_ttbar.Write()
        h_qcd_01_tp_03_disc_signal.Write()

        h_qcd_01_tp_04_njets.Write() 
        h_qcd_01_tp_04_mtprime.Write()
        h_qcd_01_tp_04_disc_qcd.Write()
        h_qcd_01_tp_04_disc_ttbar.Write()
        h_qcd_01_tp_04_disc_signal.Write()

        h_qcd_01_tp_05_njets.Write() 
        h_qcd_01_tp_05_mtprime.Write()
        h_qcd_01_tp_05_disc_qcd.Write()
        h_qcd_01_tp_05_disc_ttbar.Write()
        h_qcd_01_tp_05_disc_signal.Write()

        h_qcd_01_tp_06_njets.Write() 
        h_qcd_01_tp_06_mtprime.Write()
        h_qcd_01_tp_06_disc_qcd.Write()
        h_qcd_01_tp_06_disc_ttbar.Write()
        h_qcd_01_tp_06_disc_signal.Write()

        h_qcd_01_tp_07_njets.Write() 
        h_qcd_01_tp_07_mtprime.Write()
        h_qcd_01_tp_07_disc_qcd.Write()
        h_qcd_01_tp_07_disc_ttbar.Write()
        h_qcd_01_tp_07_disc_signal.Write()

        h_qcd_01_tp_08_njets.Write() 
        h_qcd_01_tp_08_mtprime.Write()
        h_qcd_01_tp_08_disc_qcd.Write()
        h_qcd_01_tp_08_disc_ttbar.Write()
        h_qcd_01_tp_08_disc_signal.Write()

        h_qcd_01_tp_09_njets.Write() 
        h_qcd_01_tp_09_mtprime.Write()
        h_qcd_01_tp_09_disc_qcd.Write()
        h_qcd_01_tp_09_disc_ttbar.Write()
        h_qcd_01_tp_09_disc_signal.Write()

        h_qcd_01_tt_01_njets.Write() 
        h_qcd_01_tt_01_mtprime.Write()
        h_qcd_01_tt_01_disc_qcd.Write()
        h_qcd_01_tt_01_disc_ttbar.Write()
        h_qcd_01_tt_01_disc_signal.Write()

        h_qcd_01_tt_02_njets.Write() 
        h_qcd_01_tt_02_mtprime.Write()
        h_qcd_01_tt_02_disc_qcd.Write()
        h_qcd_01_tt_02_disc_ttbar.Write()
        h_qcd_01_tt_02_disc_signal.Write()

        h_qcd_01_tt_03_njets.Write() 
        h_qcd_01_tt_03_mtprime.Write()
        h_qcd_01_tt_03_disc_qcd.Write()
        h_qcd_01_tt_03_disc_ttbar.Write()
        h_qcd_01_tt_03_disc_signal.Write()

        h_qcd_01_tt_04_njets.Write() 
        h_qcd_01_tt_04_mtprime.Write()
        h_qcd_01_tt_04_disc_qcd.Write()
        h_qcd_01_tt_04_disc_ttbar.Write()
        h_qcd_01_tt_04_disc_signal.Write()

        h_qcd_01_tt_05_njets.Write() 
        h_qcd_01_tt_05_mtprime.Write()
        h_qcd_01_tt_05_disc_qcd.Write()
        h_qcd_01_tt_05_disc_ttbar.Write()
        h_qcd_01_tt_05_disc_signal.Write()

        h_qcd_01_tt_06_njets.Write() 
        h_qcd_01_tt_06_mtprime.Write()
        h_qcd_01_tt_06_disc_qcd.Write()
        h_qcd_01_tt_06_disc_ttbar.Write()
        h_qcd_01_tt_06_disc_signal.Write()

        h_qcd_01_tt_07_njets.Write() 
        h_qcd_01_tt_07_mtprime.Write()
        h_qcd_01_tt_07_disc_qcd.Write()
        h_qcd_01_tt_07_disc_ttbar.Write()
        h_qcd_01_tt_07_disc_signal.Write()

        h_qcd_01_tt_08_njets.Write() 
        h_qcd_01_tt_08_mtprime.Write()
        h_qcd_01_tt_08_disc_qcd.Write()
        h_qcd_01_tt_08_disc_ttbar.Write()
        h_qcd_01_tt_08_disc_signal.Write()

        h_qcd_01_tt_081_njets.Write() 
        h_qcd_01_tt_081_mtprime.Write()
        h_qcd_01_tt_081_disc_qcd.Write()
        h_qcd_01_tt_081_disc_ttbar.Write()
        h_qcd_01_tt_081_disc_signal.Write()

        h_qcd_01_tt_082_njets.Write() 
        h_qcd_01_tt_082_mtprime.Write()
        h_qcd_01_tt_082_disc_qcd.Write()
        h_qcd_01_tt_082_disc_ttbar.Write()
        h_qcd_01_tt_082_disc_signal.Write()

        h_qcd_01_tt_083_njets.Write() 
        h_qcd_01_tt_083_mtprime.Write()
        h_qcd_01_tt_083_disc_qcd.Write()
        h_qcd_01_tt_083_disc_ttbar.Write()
        h_qcd_01_tt_083_disc_signal.Write()

        h_qcd_01_tt_084_njets.Write() 
        h_qcd_01_tt_084_mtprime.Write()
        h_qcd_01_tt_084_disc_qcd.Write()
        h_qcd_01_tt_084_disc_ttbar.Write()
        h_qcd_01_tt_084_disc_signal.Write()

        h_qcd_01_tt_085_njets.Write() 
        h_qcd_01_tt_085_mtprime.Write()
        h_qcd_01_tt_085_disc_qcd.Write()
        h_qcd_01_tt_085_disc_ttbar.Write()
        h_qcd_01_tt_085_disc_signal.Write()

        h_qcd_01_tt_086_njets.Write() 
        h_qcd_01_tt_086_mtprime.Write()
        h_qcd_01_tt_086_disc_qcd.Write()
        h_qcd_01_tt_086_disc_ttbar.Write()
        h_qcd_01_tt_086_disc_signal.Write()

        h_qcd_01_tt_086_tp_01_njets.Write() 
        h_qcd_01_tt_086_tp_01_mtprime.Write()
        h_qcd_01_tt_086_tp_01_disc_qcd.Write()
        h_qcd_01_tt_086_tp_01_disc_ttbar.Write()
        h_qcd_01_tt_086_tp_01_disc_signal.Write()

        h_qcd_01_tt_086_tp_015_njets.Write() 
        h_qcd_01_tt_086_tp_015_mtprime.Write()
        h_qcd_01_tt_086_tp_015_disc_qcd.Write()
        h_qcd_01_tt_086_tp_015_disc_ttbar.Write()
        h_qcd_01_tt_086_tp_015_disc_signal.Write()

        h_qcd_01_tt_086_tp_02_njets.Write() 
        h_qcd_01_tt_086_tp_02_mtprime.Write()
        h_qcd_01_tt_086_tp_02_disc_qcd.Write()
        h_qcd_01_tt_086_tp_02_disc_ttbar.Write()
        h_qcd_01_tt_086_tp_02_disc_signal.Write()

        h_qcd_01_tt_086_tp_03_njets.Write() 
        h_qcd_01_tt_086_tp_03_mtprime.Write()
        h_qcd_01_tt_086_tp_03_disc_qcd.Write()
        h_qcd_01_tt_086_tp_03_disc_ttbar.Write()
        h_qcd_01_tt_086_tp_03_disc_signal.Write()

        h_qcd_01_tt_086_tp_04_njets.Write() 
        h_qcd_01_tt_086_tp_04_mtprime.Write()
        h_qcd_01_tt_086_tp_04_disc_qcd.Write()
        h_qcd_01_tt_086_tp_04_disc_ttbar.Write()
        h_qcd_01_tt_086_tp_04_disc_signal.Write()

        h_qcd_01_tt_086_tp_05_njets.Write() 
        h_qcd_01_tt_086_tp_05_mtprime.Write()
        h_qcd_01_tt_086_tp_05_disc_qcd.Write()
        h_qcd_01_tt_086_tp_05_disc_ttbar.Write()
        h_qcd_01_tt_086_tp_05_disc_signal.Write()

        h_qcd_01_tt_086_tp_06_njets.Write() 
        h_qcd_01_tt_086_tp_06_mtprime.Write()
        h_qcd_01_tt_086_tp_06_disc_qcd.Write()
        h_qcd_01_tt_086_tp_06_disc_ttbar.Write()
        h_qcd_01_tt_086_tp_06_disc_signal.Write()

        h_qcd_01_tt_086_tp_07_njets.Write() 
        h_qcd_01_tt_086_tp_07_mtprime.Write()
        h_qcd_01_tt_086_tp_07_disc_qcd.Write()
        h_qcd_01_tt_086_tp_07_disc_ttbar.Write()
        h_qcd_01_tt_086_tp_07_disc_signal.Write()

        h_qcd_01_tt_086_tp_08_njets.Write() 
        h_qcd_01_tt_086_tp_08_mtprime.Write()
        h_qcd_01_tt_086_tp_08_disc_qcd.Write()
        h_qcd_01_tt_086_tp_08_disc_ttbar.Write()
        h_qcd_01_tt_086_tp_08_disc_signal.Write()

        h_qcd_01_tt_086_tp_09_njets.Write() 
        h_qcd_01_tt_086_tp_09_mtprime.Write()
        h_qcd_01_tt_086_tp_09_disc_qcd.Write()
        h_qcd_01_tt_086_tp_09_disc_ttbar.Write()
        h_qcd_01_tt_086_tp_09_disc_signal.Write()

        h_qcd_01_tt_087_njets.Write() 
        h_qcd_01_tt_087_mtprime.Write()
        h_qcd_01_tt_087_disc_qcd.Write()
        h_qcd_01_tt_087_disc_ttbar.Write()
        h_qcd_01_tt_087_disc_signal.Write()

        h_qcd_01_tt_088_njets.Write() 
        h_qcd_01_tt_088_mtprime.Write()
        h_qcd_01_tt_088_disc_qcd.Write()
        h_qcd_01_tt_088_disc_ttbar.Write()
        h_qcd_01_tt_088_disc_signal.Write()

        h_qcd_01_tt_089_njets.Write() 
        h_qcd_01_tt_089_mtprime.Write()
        h_qcd_01_tt_089_disc_qcd.Write()
        h_qcd_01_tt_089_disc_ttbar.Write()
        h_qcd_01_tt_089_disc_signal.Write()

        h_qcd_01_tt_09_njets.Write() 
        h_qcd_01_tt_09_mtprime.Write()
        h_qcd_01_tt_09_disc_qcd.Write()
        h_qcd_01_tt_09_disc_ttbar.Write()
        h_qcd_01_tt_09_disc_signal.Write()

        h_qcd_01_tt_095_njets.Write() 
        h_qcd_01_tt_095_mtprime.Write()
        h_qcd_01_tt_095_disc_qcd.Write()
        h_qcd_01_tt_095_disc_ttbar.Write()
        h_qcd_01_tt_095_disc_signal.Write()

        nf.Write()
        nf.Close()
