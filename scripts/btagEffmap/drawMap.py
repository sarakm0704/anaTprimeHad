import ROOT

flist = ['TTToHadronic','Tprime','QCD']

for name in flist:

    f = ROOT.TFile.Open(f"effMaps/map_{name}.root")
    
    hlist = ['h_eff_T_b','h_eff_T_c','h_eff_T_l','h_eff_M_b','h_eff_M_c','h_eff_M_l','h_eff_L_b','h_eff_L_c','h_eff_L_l']
    
    for hname in hlist:
        c = ROOT.TCanvas("c","c",1000,800)
        h = f.Get(hname)
        h.GetZaxis().SetRangeUser(0,1)
        h.GetYaxis().SetBinLabel(1,"Barrel")
        h.GetYaxis().SetBinLabel(2,"Endcap")
        h.Draw("COLZ TEXT90")
        ROOT.gStyle.SetOptStat(0)
        ROOT.gStyle.SetPaintTextFormat("0.2f")
        ROOT.gPad.Update()
        c.SaveAs(f"map_png/{hname}_{name}.png")
