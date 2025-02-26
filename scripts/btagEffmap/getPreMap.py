import sys,os
import ROOT
import numpy as np
import array
import os

sample_list = []

# read all necessary files - no btagging required
for l in os.listdir("/Users/jieun/WORK/vlq/build_macro/btagweight/file/"):
    if ".root" in l: continue
    if "pre" in l: continue
    if "sh" in l: continue
    sample_list.append(l)

print(sample_list)

for s in sample_list:

    nf = ROOT.TFile(f"map/map_{s}.root","RECREATE")
    
    ptBins = [20,30,50,70,100,140,200,300,600]
    ptArr = array.array('d',ptBins)
    
    #etaBins = [-2.5,-1.479,0,1.479,2.5]
    etaBins = [0,1.479,2.5]
    etaArr = array.array('d',etaBins)
    
    h_pteta = ROOT.TH2D("h_pteta","",len(ptArr)-1,ptArr,len(etaArr)-1,etaArr)
    h_pteta.GetXaxis().SetTitle("Jet pT [GeV]")
    h_pteta.GetYaxis().SetTitle("Jet |#eta|")
    #h_pteta.GetYaxis().SetBinLabel(1,"Barrel")
    #h_pteta.GetYaxis().SetBinLabel(2,"Endcap")

    h_L_bc_pteta = h_pteta.Clone("h_L_bc_pteta")
    h_M_bc_pteta = h_pteta.Clone("h_M_bc_pteta")
    h_T_bc_pteta = h_pteta.Clone("h_T_bc_pteta")    
    
    h_L_b_pteta = h_pteta.Clone("h_L_b_pteta")
    h_M_b_pteta = h_pteta.Clone("h_M_b_pteta")
    h_T_b_pteta = h_pteta.Clone("h_T_b_pteta")
    
    h_L_c_pteta = h_pteta.Clone("h_L_c_pteta")
    h_M_c_pteta = h_pteta.Clone("h_M_c_pteta")
    h_T_c_pteta = h_pteta.Clone("h_T_c_pteta")
    
    h_L_l_pteta = h_pteta.Clone("h_L_l_pteta")
    h_M_l_pteta = h_pteta.Clone("h_M_l_pteta")
    h_T_l_pteta = h_pteta.Clone("h_T_l_pteta")
    
    h_bc_pteta = h_pteta.Clone("h_bc_pteta")
    h_b_pteta = h_pteta.Clone("h_b_pteta")
    h_c_pteta = h_pteta.Clone("h_c_pteta")
    h_l_pteta = h_pteta.Clone("h_l_pteta")
    h_else_pteta = h_pteta.Clone("h_else_pteta")
    
    for in_file in os.listdir(f"file/{s}"):
        print(f"{in_file}")
    
        f = ROOT.TFile.Open(f"file/{s}/{in_file}")
        t = f.Get("outputTree")
    
        for i in range(t.GetEntries()):
            t.GetEntry(i)
    
            genw = t.genWeight
    
            njets = t.nselJetsForbtag
            for j in range(njets):
                pt = t.selJetsForbtag_pt[j]
                eta = abs(t.selJetsForbtag_eta[j])
                hflav = t.selJetsForbtag_hadronFlavour[j]
                wp = t.selJetsForbtag_btag[j]
    
                h_pteta.Fill(pt,eta,genw)
    
                if hflav == 5:
                    h_b_pteta.Fill(pt,eta,genw)
                    if wp > 0.7100 : h_T_b_pteta.Fill(pt,eta,genw)
                    if wp > 0.2783 : h_M_b_pteta.Fill(pt,eta,genw)
                    if wp > 0.0490 : h_L_b_pteta.Fill(pt,eta,genw)
                elif hflav == 4:
                    h_c_pteta.Fill(pt,eta,genw)
                    if wp > 0.7100 : h_T_c_pteta.Fill(pt,eta,genw)
                    if wp > 0.2783 : h_M_c_pteta.Fill(pt,eta,genw)
                    if wp > 0.0490 : h_L_c_pteta.Fill(pt,eta,genw)
                elif hflav == 0:
                    h_l_pteta.Fill(pt,eta,genw)
                    if wp > 0.7100 : h_T_l_pteta.Fill(pt,eta,genw)
                    if wp > 0.2783 : h_M_l_pteta.Fill(pt,eta,genw)
                    if wp > 0.0490 : h_L_l_pteta.Fill(pt,eta,genw)
                else:
                    h_else_pteta.Fill(pt,eta,genw) 
    
    nf.cd()
    
    h_pteta.Write()
    h_b_pteta.Write()
    h_c_pteta.Write()
    h_l_pteta.Write()
    h_L_b_pteta.Write()
    h_L_c_pteta.Write()
    h_L_l_pteta.Write()
    h_M_b_pteta.Write()
    h_M_c_pteta.Write()
    h_M_l_pteta.Write()
    h_T_b_pteta.Write()
    h_T_c_pteta.Write()
    h_T_l_pteta.Write()
    h_else_pteta.Write()
    
    nf.Close()
