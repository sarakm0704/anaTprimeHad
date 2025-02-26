# ROOT imports
import pandas as pd 
import os, ROOT
import cmsstyle as CMS

# python imports 
import matplotlib.pyplot as plt  # matplotlib library
import mplhep as hep  # HEP (CMS) extensions/styling on top of mpl

# For constructing examples
import hist  # histogramming library
import numpy as np 
import uproot
import math

regions = ['2M1L','3M','3T']
myc = ['#185358','#02ABBA','#c6c015','#FFD639','#ef8a17','#016fb9']
nbins = 25

def cut0 (d):
    d = d.loc[(d['Chi2_min'] < 15) & (d['mass_secondtop'] > 250) & (d['mass_h'] > 100)]
    return d

def cutNN_qcd (d):
    d = d.loc[(d['pred_QCD'] > 0.1)]
    return d

def cutNN_tt (d):
    d = d.loc[(d['pred_TTbar'] > 0.9)]
    return d

def cut_sideband (d):
    d = d.loc[(d['mass_tprime'] < 600) | (d['mass_tprime'] > 1200 )]
    return d

# treat overflow underflow
def wrap_hist (h):
    h[1] += h[0]
    h[-2] += h[-1]
    h = h[1:-1]
    return h

for r in regions:
    print(f'running on region {r}')

    loc = f'/Users/jieun/WORK/vlq/dnn/training/array/{r}/'
    outloc = f'/Users/jieun/WORK/vlq/plot/mytool/mplhep/output/{r}/'
    if not os.path.exists(f'{outloc}'): os.makedirs(f'{outloc}')
        
    # load dataset
    df_data = pd.read_hdf(f'{loc}/array_JetHT.h5')
    df_tt = pd.read_hdf(f'{loc}/array_TTToHadronic.h5')
    
    df_qcd_BGenFilter_1 = pd.read_hdf(f'{loc}/array_QCD_HT300to500_BGenFilter.h5') 
    df_qcd_BGenFilter_2 = pd.read_hdf(f'{loc}/array_QCD_HT500to700_BGenFilter.h5') 
    df_qcd_BGenFilter_3 = pd.read_hdf(f'{loc}/array_QCD_HT700to1000_BGenFilter.h5') 
    df_qcd_BGenFilter_4 = pd.read_hdf(f'{loc}/array_QCD_HT1000to1500_BGenFilter.h5') 
    df_qcd_BGenFilter_5 = pd.read_hdf(f'{loc}/array_QCD_HT1500to2000_BGenFilter.h5') 
    df_qcd_BGenFilter_6 = pd.read_hdf(f'{loc}/array_QCD_HT2000toInf_BGenFilter.h5') 
    
    df_qcd_bEnriched_1 = pd.read_hdf(f'{loc}/array_QCD_bEnriched_HT300to500.h5')
    df_qcd_bEnriched_2 = pd.read_hdf(f'{loc}/array_QCD_bEnriched_HT500to700.h5')
    df_qcd_bEnriched_3 = pd.read_hdf(f'{loc}/array_QCD_bEnriched_HT700to1000.h5')
    df_qcd_bEnriched_4 = pd.read_hdf(f'{loc}/array_QCD_bEnriched_HT1000to1500.h5')
    df_qcd_bEnriched_5 = pd.read_hdf(f'{loc}/array_QCD_bEnriched_HT1500to2000.h5')
    df_qcd_bEnriched_6 = pd.read_hdf(f'{loc}/array_QCD_bEnriched_HT2000toInf.h5')

    df_wjets_1 = pd.read_hdf(f'{loc}/array_WJets_HT400to600.h5')
    df_wjets_2 = pd.read_hdf(f'{loc}/array_WJets_HT600to800.h5')
    df_wjets_3 = pd.read_hdf(f'{loc}/array_WJets_HT800toInf.h5')

    df_zjets_1 = pd.read_hdf(f'{loc}/array_ZJets_HT400to600.h5')
    df_zjets_2 = pd.read_hdf(f'{loc}/array_ZJets_HT600to800.h5')
    df_zjets_3 = pd.read_hdf(f'{loc}/array_ZJets_HT800toInf.h5')

    df_st_s = pd.read_hdf(f'{loc}/array_ST_s.h5')    
    df_st_t = pd.read_hdf(f'{loc}/array_ST_t_top.h5')    
    df_st_ant = pd.read_hdf(f'{loc}/array_ST_t_antitop.h5')    
    df_st_tW = pd.read_hdf(f'{loc}/array_ST_tW_top.h5')    
    df_st_antW = pd.read_hdf(f'{loc}/array_ST_tW_antitop.h5')    

    df_tth = pd.read_hdf(f'{loc}/array_ttHTobb.h5')    

    df_data = cut_sideband(df_data)
    df_tt = cut_sideband(df_tt)
    df_qcd_BGenFilter_1 = cut_sideband(df_qcd_BGenFilter_1)
    df_qcd_BGenFilter_2 = cut_sideband(df_qcd_BGenFilter_2)
    df_qcd_BGenFilter_3 = cut_sideband(df_qcd_BGenFilter_3)
    df_qcd_BGenFilter_4 = cut_sideband(df_qcd_BGenFilter_4)
    df_qcd_BGenFilter_5 = cut_sideband(df_qcd_BGenFilter_5)
    df_qcd_BGenFilter_6 = cut_sideband(df_qcd_BGenFilter_6)

    df_qcd_bEnriched_1 = cut_sideband(df_qcd_bEnriched_1)
    df_qcd_bEnriched_2 = cut_sideband(df_qcd_bEnriched_2)
    df_qcd_bEnriched_3 = cut_sideband(df_qcd_bEnriched_3)
    df_qcd_bEnriched_4 = cut_sideband(df_qcd_bEnriched_4)
    df_qcd_bEnriched_5 = cut_sideband(df_qcd_bEnriched_5)
    df_qcd_bEnriched_6 = cut_sideband(df_qcd_bEnriched_6)

    df_st_s = cut_sideband(df_st_s)
    df_st_t = cut_sideband(df_st_t)
    df_st_ant = cut_sideband(df_st_ant)
    df_st_tW = cut_sideband(df_st_tW)
    df_st_antW = cut_sideband(df_st_antW)
                
    df_tth = cut_sideband(df_tth)

    # normalization w/ only genWeight
    # scale 2018 lumi, xsecs from xsdb
    wtt =  0.000213165716054138
               
    wqcd_BGen_1 = 1937.29849628
    wqcd_BGen_2 = 355.177976291
    wqcd_BGen_3 = 144.676258504
    wqcd_BGen_4 = 80.4483146147
    wqcd_BGen_5 = 10.0225103394
    wqcd_BGen_6 = 1.98606789537
                
    wqcd_bEnr_1 = 88.5627094510
    wqcd_bEnr_2 = 9.71036157206
    wqcd_bEnr_3 = 9.63415605436
    wqcd_bEnr_4 = 2.15831431386
    wqcd_bEnr_5 = 0.16491600442
    wqcd_bEnr_6 = 0.03062018169

    wwjets_1 = 10.4933385838918
    wwjets_2 = 1.76241523302202
    wwjets_3 = 0.26094898962285
    wwjets_4 = 0.12800376958302

    wzjets_1 = 3.98996544435132
    wzjets_2 = 0.49918275573393
    wzjets_3 = 0.12648924598489
    wzjets_4 = 0.08015637109086

    wst_s = 0.00366945043679460
    wst_t = 0.00035738739049725
    wst_ant = 0.000663653238754
    wst_tW = 0.0075099362368493
    wst_antW = 0.00752382209737

    wtth = 0.006498987796108047

    from hist.intervals import ratio_uncertainty
    
    input_var = ['nseljets', 'nselbjets', 'goodht', 'relht', 'mindR_dRbb', 'mindR_mbb', 'Chi2_max', 'Chi2_min', 'Chi2_min_H', 'Chi2_min_W', 'Chi2_min_Top', 'mass_h', 'mass_w', 'mass_top', 'mass_wh', 'mass_secondtop', 'mass_leadjets', 'dR_hbb', 'dR_wjj', 'dR_bw', 'dR_tprimeoj', 'ratio_mass_topH', 'ratio_mass_secondtopW', 'ratio_pt_topsecondtop', 'ratio_pt_htoptprime', 'ratio_pt_tprimehtprimetop', 'jet1_eta', 'jet1_e_massnom', 'jet2_eta', 'jet2_e_massnom', 'jet3_eta', 'jet3_e_massnom', 'jet4_eta', 'jet4_e_massnom', 'jet5_eta', 'jet5_e_massnom']
    for var in input_var:
        print(f"running on var = {var}")

        # Styling
        hep.style.use("CMS")
        fig, (ax, rax) = plt.subplots(2, 1, gridspec_kw=dict(height_ratios=[3, 1], hspace=0.1), sharex=True)
        hep.cms.label("Preliminary", com = 13, lumi = 59.7, data = True, loc=0, ax=ax);
        ax.set_ylabel("Events")
        name = var
    
        dat = df_data[var].dropna()
        tt = df_tt[var].dropna()

        print(f"tt length = {len(tt)}")
    
        qcd_BGenFilter_1 = df_qcd_BGenFilter_1[var].dropna()
        qcd_BGenFilter_2 = df_qcd_BGenFilter_2[var].dropna()
        qcd_BGenFilter_3 = df_qcd_BGenFilter_3[var].dropna()
        qcd_BGenFilter_4 = df_qcd_BGenFilter_4[var].dropna()
        qcd_BGenFilter_5 = df_qcd_BGenFilter_5[var].dropna()
        qcd_BGenFilter_6 = df_qcd_BGenFilter_6[var].dropna()
    
        qcd_bEnriched_1 = df_qcd_bEnriched_1[var].dropna()
        qcd_bEnriched_2 = df_qcd_bEnriched_2[var].dropna()
        qcd_bEnriched_3 = df_qcd_bEnriched_3[var].dropna()
        qcd_bEnriched_4 = df_qcd_bEnriched_4[var].dropna()
        qcd_bEnriched_5 = df_qcd_bEnriched_5[var].dropna()
        qcd_bEnriched_6 = df_qcd_bEnriched_6[var].dropna()

        wjets_1 = df_wjets_1[var].dropna()
        wjets_2 = df_wjets_2[var].dropna()
        wjets_3 = df_wjets_3[var].dropna()
        zjets_1 = df_zjets_1[var].dropna()
        zjets_2 = df_zjets_2[var].dropna()
        zjets_3 = df_zjets_3[var].dropna()

        st_s = df_st_s[var].dropna()
        st_t = df_st_t[var].dropna()
        st_ant = df_st_ant[var].dropna()
        st_tW = df_st_tW[var].dropna()
        st_antW = df_st_antW[var].dropna()

        tth = df_tth[var].dropna()

        if "pred" in var:
            (xmin, xmax) = (0, 1)
            if "TTbar" in var: name = r"$t\bar{t}$ Score"
            elif "QCD" in var: name = "QCD Score"
            elif "prime" in var: name = r"$T\prime$ Score"

        elif "nsel" in var:
            if "selj" in var:
                name = "Number of jets"
                (xmin, xmax) = (4.5, 14.5)
            elif "selbj" in var:
                name = "Number of b-tagged jets"
                (xmin, xmax) = (1.5, 6.5)

        elif "Chi2" in var:
                (xmin, xmax) = (0,50)
                if "min" in var:
                    if "H" in var: name = r'$H\ \chi^{2}_{min}$'
                    elif "Top" in var: name = r'$t\ \chi^{2}_{min}$'
                    elif "W" in var: name = r'$W\ \chi^{2}_{min}$'
                    else: name = r'$\chi^{2}_{min}$'
                elif "max" in var: name = r'$\chi^{2}_{max}$'

        elif "_btag" in var:
            (xmin, xmax) = (0,1)
            if "bjet" in var:
                if '1' in var: name = r'$b-tagged\ jet_{1}\ DeepJet disc.$'
                elif '2' in var: name = r'$b-tagged\ jet_{2}\ DeepJet disc.$'
            else:
                if '1' in var: name = r'$jet_{1}\ DeepJet\ disc.$'
                elif '2' in var: name = r'$jet_{2}\ DeepJet\ disc.$'
                elif '3' in var: name = r'$jet_{3}\ DeepJet\ disc.$'
                elif '4' in var: name = r'$jet_{4}\ DeepJet\ disc.$'
                elif '5' in var: name = r'$jet_{5}\ DeepJet\ disc.$'

        elif "_eta" in var:
            if "bjet" in var:
                (xmin, xmax) = (-2.5,2.5)
                if '1' in var: name = r'$b-tagged\ jet_{1}\ \eta$'
                elif '2' in var: name = r'$b-tagged\ jet_{2}\ \eta$'
            else:
                (xmin, xmax) = (-4.5,4.5)
                if '1' in var: name = r'$jet_{1}\ \eta$'
                elif '2' in var: name = r'$jet_{2}\ \eta$'
                elif '3' in var: name = r'$jet_{3}\ \eta$'
                elif '4' in var: name = r'$jet_{4}\ \eta$'
                elif '5' in var: name = r'$jet_{5}\ \eta$'

        elif "_phi" in var:
            (xmin, xmax) = (-3.5,3.5)
            if "bjet" in var:
                if '1' in var: name = r'$b-tagged\ jet_{1}\ \eta$'
                elif '2' in var: name = r'$b-tagged\ jet_{2}\ \eta$'
            else:
                if '1' in var: name = r'$jet_{1}\ \phi$'
                elif '2' in var: name = r'$jet_{2}\ \phi$'
                elif '3' in var: name = r'$jet_{3}\ \phi$'
                elif '4' in var: name = r'$jet_{4}\ \phi$'
                elif '5' in var: name = r'$jet_{5}\ \phi$'

        elif "_e" in var and not "massnom" in var:
            if "bjet" in var:
                (xmin, xmax) = (0,1500)
                if '1' in var: name = r'$b-tagged\ jet_{1}\ energy\ [GeV]$'
                elif '2' in var: name = r'$b-tagged\ jet_{2}\ energy\ [GeV]$'

            else:
                (xmin, xmax) = (0,2000)
                if '1' in var: name = r'$jet_{1}\ energy\ [GeV]$'
                elif '2' in var: name = r'$jet_{2}\ energy\ [GeV]$'
                elif '3' in var: name = r'$jet_{3}\ energy\ [GeV]$'
                elif '4' in var: name = r'$jet_{4}\ energy\ [GeV]$'
                elif '5' in var: name = r'$jet_{5}\ energy\ [GeV]$'

        elif "e_massnom" in var:
            (xmin, xmax) = (0,2)
            if "bjet" in var:
                if '1' in var: name = r'$\frac{b-tagged\ jet_{1}\ energy}{M_{reco.\ T\prime}}$'
                elif '2' in var: name = r'$\frac{b-tagged\ jet_{2}\ energy}{M_{reco.\ T\prime}}$'

            else:
                if '1' in var: name = r'$\frac{jet_{1}\ energy}{M_{reco.\ T\prime}}$'
                elif '2' in var: name = r'$\frac{jet_{2}\ energy}{M_{reco.\ T\prime}}$'
                elif '3' in var: name = r'$\frac{jet_{3}\ energy}{M_{reco.\ T\prime}}$'
                elif '4' in var: name = r'$\frac{jet_{4}\ energy}{M_{reco.\ T\prime}}$'
                elif '5' in var: name = r'$\frac{jet_{5}\ energy}{M_{reco.\ T\prime}}$'
        elif "_pt" in var and not "massnom" in var and not "ratio" in var:
            if "bjet" in var:
                (xmin, xmax) = (30,500)
                if '1' in var: name = r'$b-tagged\ jet_{1}\ p_{T}\ [GeV]$'
                elif '2' in var: name = r'$b-tagged\ jet_{2}\ p_{T}\ [GeV]$'

            else:
                (xmin, xmax) = (30,500)
                if '1' in var:
                    (xmin, xmax) = (150,500)
                    name = r'$jet_{1}\ p_{T}\ [GeV]$'
                elif '2' in var:
                    (xmin, xmax) = (100,500)
                    name = r'$jet_{2}\ p_{T}\ [GeV]$'
                elif '3' in var:
                    (xmin, xmax) = (50,500)
                    name = r'$jet_{3}\ p_{T}\ [GeV]$'
                elif '4' in var: name = r'$jet_{4}\ p_{T}\ [GeV]$'
                elif '5' in var: name = r'$jet_{5}\ p_{T}\ [GeV]$'

        elif "pt_massnom" in var:
            (xmin, xmax) = (0,1)
            if "bjet" in var:
                if '1' in var: name = r'$\frac{bjet_{1}\ p_{T}}{M_{reco.\ T\prime}}$'
                elif '2' in var: name = r'$\frac{bjet_{2}\ p_{T}}{M_{reco.\ T\prime}}$'

            else:
                if '1' in var: name = r'$\frac{jet_{1}\ p_{T}}{M_{reco.\ T\prime}}$'
                elif '2' in var: name = r'$\frac{jet_{2}\ p_{T}}{M_{reco.\ T\prime}}$'
                elif '3' in var: name = r'$\frac{jet_{3}\ p_{T}}{M_{reco.\ T\prime}}$'
                elif '4' in var: name = r'$\frac{jet_{4}\ p_{T}}{M_{reco.\ T\prime}}$'
                elif '5' in var: name = r'$\frac{jet_{5}\ p_{T}}{M_{reco.\ T\prime}}$'

        elif "dR" in var and not "mindR" in var:
            if "hbb" in var:
                name = r'$\Delta R_{b_{H},b_{H}}$'
                (xmin, xmax) = (0, 4)
            elif "oj" in var:
                name = r'$\Delta R_{T\prime,j^{other}_{\chi^{2}}}$'
                (xmin, xmax) = (0, 8) 
            elif "bw" in var:
                name = r'$\Delta R_{b_{t},W_{t}}$'
                (xmin, xmax) = (0, 8)
            elif "wjj" in var:
                name = r'$\Delta R_{j_{W},j_{W}}$'
                (xmin, xmax) = (0, 6)

        elif "mindR" in var:
            if "mbb" in var:
                name = r'$M_{min. \Delta R_{bb}}$'
                (xmin, xmax) = (0, 600)
            elif "dRbb" in var:
                name = r'$min. \Delta R_{b,b}$'
                (xmin, xmax) = (0, 4)

        elif "goodht" in var:
                name = r'$H_{T}$ [GeV]'
                (xmin, xmax) = (450, 2000)

        elif "relht" in var:
                name = r'$\frac{t_{pT} + H_{pT}}{H_{T}}$'
                (xmin, xmax) = (0, 1.0)

        elif "mass" in var and not "ratio" in var:
            if "_w" in var and not "_wh" in var:
                name = r'$M_{W}\ [GeV]$'
                (xmin, xmax) = (30,250)
            elif "_wh" in var:
                name = r'$M_{W+H}\ [GeV]$'
                (xmin, xmax) = (0,1200)
            elif "secondtop" in var:
                name = r'$M_{2^{nd} t}\ [GeV]$'
                (xmin, xmax) = (100,1500)
                # AN2017-310
                #(xmin, xmax) = (100,300)
            elif "_top" in var:
                name = r'$M_{t}\ [GeV]$'
                (xmin, xmax) = (50,500)
            elif "_h" in var:
                name = r'$M_{H}\ [GeV]$'
                (xmin, xmax) = (30,330)
            elif "_leadjets" in var:
                name = r'$M_{6\ leading\ jets}\ [GeV]$'
                (xmin, xmax) = (300,3300)
            elif "_tprime" in var:
                name = r'$M_{t+H}\ [GeV]$'
                (xmin, xmax) = (300,1800)    

        elif "ratio" in var:
            if "mass" in var:
                if "_secondtopW" in var:
                    name = r'$\frac{ M_{2^{nd}t} + M_{2^{nd}W} }{ M_{H} }$'
                    (xmin, xmax) = (0, 15)
                elif "_topH" in var:
                    name = r'$\frac{ M_{t} - M_{H} }{ M_{t} + M_{H} }$'
                    (xmin, xmax) = (-0.5, 1)
            elif "pt" in var:
                if "_htoptprime" in var:
                    name = r'$\frac{ pT_{H} - pT_{t} }{ pT_{T\prime} }$'
                    (xmin, xmax) = (-1, 1)
                elif "_topsecondtop" in var:
                    name = r'$\frac{ pT_{2^{nd}t} - pT_{t} }{ pT_{2^{nd}t} }$'
                    (xmin, xmax) = (-3, 2)
                elif "_tprimehtprimetop" in var:
                    name = r'$\frac{pT_{T\prime}}{pT_{H}} - \frac{pT_{T\prime}}{pT_{t}}$'
                    (xmin, xmax) = (-5, 5)

        else:
            (xmin, xmax) = (dat.min(), dat.max())

        rax.set_xlabel(f"{name}")
    
        if "nsel" in var:
            binning = np.arange(xmin, xmax, step=1)
        else: 
            binning = [ edge for edge in np.arange(xmin, xmax+(xmax-xmin)/nbins, (xmax-xmin)/nbins) ]

        # treat under/overflow
        infBins = [np.array([-np.inf]), binning, np.array([np.inf])]
        infBins = np.concatenate(infBins)

        #weight
        h_dat, bins_dat = np.histogram(dat, bins=infBins)

        h_tt, bins_tt = np.histogram(tt, bins=infBins, weights = df_tt['evWeight_all']*wtt)

        h_qcdm_1, bins_qcdm_1 = np.histogram(qcd_BGenFilter_1, bins=infBins, weights = df_qcd_BGenFilter_1['evWeight_all']*wqcd_BGen_1)
        h_qcdm_2, bins_qcdm_2 = np.histogram(qcd_BGenFilter_2, bins=infBins, weights = df_qcd_BGenFilter_2['evWeight_all']*wqcd_BGen_2)
        h_qcdm_3, bins_qcdm_3 = np.histogram(qcd_BGenFilter_3, bins=infBins, weights = df_qcd_BGenFilter_3['evWeight_all']*wqcd_BGen_3)
        h_qcdm_4, bins_qcdm_4 = np.histogram(qcd_BGenFilter_4, bins=infBins, weights = df_qcd_BGenFilter_4['evWeight_all']*wqcd_BGen_4)
        h_qcdm_5, bins_qcdm_5 = np.histogram(qcd_BGenFilter_5, bins=infBins, weights = df_qcd_BGenFilter_5['evWeight_all']*wqcd_BGen_5)
        h_qcdm_6, bins_qcdm_6 = np.histogram(qcd_BGenFilter_6, bins=infBins, weights = df_qcd_BGenFilter_6['evWeight_all']*wqcd_BGen_6)

        h_qcdp_1, bins_qcdp_1 = np.histogram(qcd_bEnriched_1, bins=infBins, weights = df_qcd_bEnriched_1['evWeight_all']*wqcd_bEnr_1)
        h_qcdp_2, bins_qcdp_2 = np.histogram(qcd_bEnriched_2, bins=infBins, weights = df_qcd_bEnriched_2['evWeight_all']*wqcd_bEnr_2)
        h_qcdp_3, bins_qcdp_3 = np.histogram(qcd_bEnriched_3, bins=infBins, weights = df_qcd_bEnriched_3['evWeight_all']*wqcd_bEnr_3)
        h_qcdp_4, bins_qcdp_4 = np.histogram(qcd_bEnriched_4, bins=infBins, weights = df_qcd_bEnriched_4['evWeight_all']*wqcd_bEnr_4)
        h_qcdp_5, bins_qcdp_5 = np.histogram(qcd_bEnriched_5, bins=infBins, weights = df_qcd_bEnriched_5['evWeight_all']*wqcd_bEnr_5)
        h_qcdp_6, bins_qcdp_6 = np.histogram(qcd_bEnriched_6, bins=infBins, weights = df_qcd_bEnriched_6['evWeight_all']*wqcd_bEnr_6)

        h_wjets_1, bins_wjets_1 = np.histogram(wjets_1, bins=infBins, weights = df_wjets_1['evWeight_all']*wwjets_1)
        h_wjets_2, bins_wjets_2 = np.histogram(wjets_2, bins=infBins, weights = df_wjets_2['evWeight_all']*wwjets_2)
        h_wjets_3, bins_wjets_3 = np.histogram(wjets_3, bins=infBins, weights = df_wjets_3['evWeight_all']*wwjets_3)

        h_zjets_1, bins_zjets_1 = np.histogram(zjets_1, bins=infBins, weights = df_zjets_1['evWeight_all']*wzjets_1)
        h_zjets_2, bins_zjets_2 = np.histogram(zjets_2, bins=infBins, weights = df_zjets_2['evWeight_all']*wzjets_2)
        h_zjets_3, bins_zjets_3 = np.histogram(zjets_3, bins=infBins, weights = df_zjets_3['evWeight_all']*wzjets_3)

        h_st_s, bins_st_s = np.histogram(st_s, bins=infBins, weights = df_st_s['evWeight_all']*wst_s)
        h_st_t, bins_st_t = np.histogram(st_t, bins=infBins, weights = df_st_t['evWeight_all']*wst_t)
        h_st_ant, bins_st_ant = np.histogram(st_ant, bins=infBins, weights = df_st_ant['evWeight_all']*wst_ant)
        h_st_tW, bins_st_tW = np.histogram(st_tW, bins=infBins, weights = df_st_tW['evWeight_all']*wst_tW)
        h_st_antW, bins_st_antW = np.histogram(st_antW, bins=infBins, weights = df_st_antW['evWeight_all']*wst_antW)

        h_tth, bins_tth = np.histogram(tth, bins=infBins, weights = df_tth['evWeight_all']*wtth)

        # treat under/overflow

        #print(f"after sel {np.sum(h_tt)}")

        h_dat = wrap_hist(h_dat)
        h_tt = wrap_hist(h_tt)
        h_qcdm_1 = wrap_hist(h_qcdm_1)
        h_qcdm_2 = wrap_hist(h_qcdm_2)
        h_qcdm_3 = wrap_hist(h_qcdm_3)
        h_qcdm_4 = wrap_hist(h_qcdm_4)
        h_qcdm_5 = wrap_hist(h_qcdm_5)
        h_qcdm_6 = wrap_hist(h_qcdm_6)
        h_qcdp_1 = wrap_hist(h_qcdp_1)
        h_qcdp_2 = wrap_hist(h_qcdp_2)
        h_qcdp_3 = wrap_hist(h_qcdp_3)
        h_qcdp_4 = wrap_hist(h_qcdp_4)
        h_qcdp_5 = wrap_hist(h_qcdp_5)
        h_qcdp_6 = wrap_hist(h_qcdp_6)

        h_wjets_1 = wrap_hist(h_wjets_1)
        h_wjets_2 = wrap_hist(h_wjets_2)
        h_wjets_3 = wrap_hist(h_wjets_3)
        h_zjets_1 = wrap_hist(h_zjets_1)
        h_zjets_2 = wrap_hist(h_zjets_2)
        h_zjets_3 = wrap_hist(h_zjets_3)

        h_st_s = wrap_hist(h_st_s)
        h_st_t = wrap_hist(h_st_t)
        h_st_ant = wrap_hist(h_st_ant)
        h_st_tW = wrap_hist(h_st_tW)
        h_st_antW = wrap_hist(h_st_antW)

        h_tth = wrap_hist(h_tth)

        h_qcdm = h_qcdm_1+h_qcdm_2+h_qcdm_3+h_qcdm_4+h_qcdm_5+h_qcdm_6
        h_qcdp = h_qcdp_1+h_qcdp_2+h_qcdp_3+h_qcdp_4+h_qcdp_5+h_qcdp_6

        h_vjets = h_wjets_1 + h_wjets_2 + h_wjets_3 + h_zjets_1 + h_zjets_2 + h_zjets_3

        h_st = h_st_s + h_st_t + h_st_tW + h_st_ant + h_st_antW

        h_qcdsum = h_qcdp + h_qcdm

        # scale fits
        # scale choices for tt
#        tt_scales = np.arange(0.1, 2, 0.1)
#        # scale choices for qcd
#        qcd_scales = np.arange(0.1, 10, 0.1)
#
#        h_rest = h_dat - (h_vjets + h_st + h_tth)        
##        print(f'rest = {h_rest}')
#
#        min_chisq = 1e99
#        best_s_tt = 1
#        best_s_qcd = 1
#
#        # looping over tt scale options
#        for s_tt in tt_scales:
#            # looping over qcd scale options
#            for s_qcd in qcd_scales:
#                # scaling both histograms
#                h_sum = h_tt*s_tt + h_qcdsum*s_qcd
#                # calculate chi square value
#                chi = (h_sum - h_rest)**2 / h_rest
#                chi = [0 if math.isnan(x) else x for x in chi]
#                chi_sq = np.sum(chi)
#                # set new minimum
#                if chi_sq < min_chisq:
#                    min_chisq = chi_sq
#                    best_s_tt = s_tt
#                    best_s_qcd = s_qcd
#
#        print(f"tt scale = {best_s_tt}")
#        print(f"qcd scale = {best_s_qcd}")

        # quick sacle
#        h_datt = h_dat - h_tt
        h_datt = h_dat - h_tt - h_vjets - h_st - h_tth

        scale = round(sum(h_datt)/sum(h_qcdsum),2)
        print(f'scale = {scale}')

        h_qcdm = h_qcdm * scale
        h_qcdp = h_qcdp * scale

        h_tot = h_tt + h_qcdm + h_qcdp + h_vjets + h_st + h_tth
        
        # Main plot
        # standard
        hep.histplot([h_tt,h_vjets,h_qcdm,h_qcdp,h_st,h_tth], binning, ax=ax, stack=True, histtype='fill', label=["tt","V+Jets","QCD b@PS-filterd","QCD b@ME-filterd","SingleTop","ttH"], color=myc, edgecolor="black")
        hep.histplot(h_dat, binning, ax=ax, histtype='errorbar', color='k', capsize=2, yerr=True, label="Data")
    
        # Error band
        errps = {'hatch':'////', 'facecolor':'none', 'lw': 0, 'edgecolor': 'k', 'alpha': 0.5}
        hep.histplot(sum([h_tt,h_qcdm,h_qcdp,h_st,h_vjets,h_tth]), binning, histtype='band', ax=ax, **errps)
        
        # Ratio panel
        if np.any(h_tot) < 0: h_tot = [0.0001 if x < 0 else x for x in h_tot]

        hep.histplot(h_dat/h_tot, binning, yerr=np.sqrt(h_dat)/h_tot, ax=rax, histtype='errorbar', color='k', capsize=2, label="Data/MC")
        # Error band
        yerr = ratio_uncertainty(h_dat, h_tot, 'poisson-ratio')

        rax.stairs(1+yerr[1], edges=binning, baseline=1-yerr[0], **errps)
        
        # Final styling
        rax.axhline(1, ls='--', color='k')
        rax.set_ylim(0.5, 1.5)
#        rax.set_ylim(0.7, 1.3)
        ax.set_xlabel("")
        ax.set_xlim(xmin, xmax)
        ax.legend();
        handles, labels = ax.get_legend_handles_labels()
        ax.legend(handles[::-1], labels[::-1])

        fig.subplots_adjust(left=0.15, right=0.95, top=0.95, bottom=0.12)
        fig.savefig(f"{outloc}/{var}.png")
        fig.savefig(f"{outloc}/{var}.pdf")
        plt.close()
