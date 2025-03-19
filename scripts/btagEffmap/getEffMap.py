import sys,os
import ROOT
import numpy as np
import array
import os

inputDir = "/Users/jieun/WORK/vlq/build_macro/btagweight/scaled_map/"

for s in os.listdir(inputDir):

    if "pre" in s: continue

    f = ROOT.TFile(inputDir+s)
    nf = ROOT.TFile(f"effMaps/{s}","RECREATE")

    h_pteta = f.Get("h_pteta") 
    h_else_pteta = f.Get("h_else_pteta") 

    h_b_pteta = f.Get("h_b_pteta") 
    h_b_pteta = f.Get("h_b_pteta") 
    h_b_pteta = f.Get("h_b_pteta") 

    h_c_pteta = f.Get("h_c_pteta") 
    h_c_pteta = f.Get("h_c_pteta") 
    h_c_pteta = f.Get("h_c_pteta") 

    h_l_pteta = f.Get("h_l_pteta") 
    h_l_pteta = f.Get("h_l_pteta") 
    h_l_pteta = f.Get("h_l_pteta") 
   
    h_L_b_pteta = f.Get("h_L_b_pteta") 
    h_M_b_pteta = f.Get("h_M_b_pteta") 
    h_T_b_pteta = f.Get("h_T_b_pteta") 

    h_L_c_pteta = f.Get("h_L_c_pteta") 
    h_M_c_pteta = f.Get("h_M_c_pteta") 
    h_T_c_pteta = f.Get("h_T_c_pteta") 

    h_L_l_pteta = f.Get("h_L_l_pteta") 
    h_M_l_pteta = f.Get("h_M_l_pteta") 
    h_T_l_pteta = f.Get("h_T_l_pteta") 

    h_eff_L_b = h_L_b_pteta.Clone("h_eff_L_b")
    h_eff_L_b.Divide(h_b_pteta)
    h_eff_M_b = h_M_b_pteta.Clone("h_eff_M_b")
    h_eff_M_b.Divide(h_b_pteta)
    h_eff_T_b = h_T_b_pteta.Clone("h_eff_T_b")
    h_eff_T_b.Divide(h_b_pteta)
    
    h_eff_L_c = h_L_c_pteta.Clone("h_eff_L_c")
    h_eff_L_c.Divide(h_c_pteta)
    h_eff_M_c = h_M_c_pteta.Clone("h_eff_M_c")
    h_eff_M_c.Divide(h_c_pteta)
    h_eff_T_c = h_T_c_pteta.Clone("h_eff_T_c")
    h_eff_T_c.Divide(h_c_pteta)
    
    h_eff_L_l = h_L_l_pteta.Clone("h_eff_L_l")
    h_eff_L_l.Divide(h_l_pteta)
    h_eff_M_l = h_M_l_pteta.Clone("h_eff_M_l")
    h_eff_M_l.Divide(h_l_pteta)
    h_eff_T_l = h_T_l_pteta.Clone("h_eff_T_l")
    h_eff_T_l.Divide(h_l_pteta)
   
    nf.cd()
 
    h_eff_T_b.Write()
    h_eff_T_c.Write()
    h_eff_T_l.Write()
    h_eff_M_b.Write()
    h_eff_M_c.Write()
    h_eff_M_l.Write()
    h_eff_L_b.Write()
    h_eff_L_c.Write()
    h_eff_L_l.Write()

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
