# ROOT imports
import pandas as pd 
import os, ROOT
import cmsstyle as CMS

# python imports 
import matplotlib.pyplot as plt  # matplotlib library
import mplhep as hep  # HEP (CMS) extensions/styling on top of mpl

# For constructing examples
import hist  # histogramming library
from hist.intervals import ratio_uncertainty

import numpy as np 
import uproot
import math

from scipy.stats import beta

regions = ['2M1L','3M','3T']
myc = ['#016fb9','#67A239','#847E2B','#345325','#ef8a17','#D81200','#8029BD','#FF007B','#999999','#000000']

nbins = 25

def cut0 (d):
    d = d.loc[(d['Chi2_min'] < 15) & (d['mass_secondtop'] > 250) & (d['mass_h'] > 100)]
    return d

def cut_sideband (d):
    d = d.loc[(d['mass_tprime'] < 600) | (d['mass_tprime'] > 1200 )]
    return d

def cleaningNeg (h):
    for i in range(len(h)):
        if h[i] < 0:
            print(f"negative bin={i}, value={h[i]}")
            print("cleaning negative into ... 0")
            h[i] = 0.
    return h

# treat overflow underflow
def wrap_hist (h):
    # quick aid
    h = cleaningNeg(h)

    h[1] += h[0]
    h[-2] += h[-1]
    h = h[1:-1]
    return h

def cut_Mu (d):
    d = d.loc[( (d['HLT_IsoMu24']==1) | (d['HLT_Mu50']==1) ) & ( d['nMuons']>0 )]
    return d

def cut_HLT1 (d):
    d = d.loc[(d['HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5']==1)]
    return d

def cut_HLT2 (d):
    d = d.loc[(d['HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2']==1)]
    return d

def cut_HLT3 (d):
    d = d.loc[(d['HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepCSV_4p5']==1)]
    return d

def cut_HLT4 (d):
    d = d.loc[(d['HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5']==1)]
    return d

def cut_HLT5 (d):
    d = d.loc[(d['HLT_PFJet500']==1)]
    return d

def cut_HLT6 (d):
    d = d.loc[(d['HLT_PFHT1050']==1)]
    return d

def cut_HLT7 (d):
    d = d.loc[(d['HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94']==1)]
    return d

def cut_HLT8 (d):
    d = d.loc[(d['HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59']==1)]
    return d

def cut_HLTcur (d):
    d = d.loc[ (d['HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5']==1) | (d['HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2']==1) | (d['HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepCSV_4p5']==1) | (d['HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5']==1) | (d['HLT_PFJet500']==1) | (d['HLT_PFHT1050']==1) ]
    return d

def cut_HLTall (d):
    d = d.loc[ (d['HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5']==1) | (d['HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2']==1) | (d['HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepCSV_4p5']==1) | (d['HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5']==1) | (d['HLT_PFJet500']==1) | (d['HLT_PFHT1050']==1) | (d['HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94']==1) | (d['HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59']==1) ]
    return d

for r in regions:
    print(f'running on region {r}')

    loc = f'/Users/jieun/WORK/vlq/dnn/training/array/woHLT/Jet45/{r}/'
    outloc = f'/Users/jieun/WORK/vlq/plot/quickDraw/trigEff/data/Jet45/{r}'
    if not os.path.exists(f'{outloc}'): os.makedirs(f'{outloc}')
        
    # load dataset
    df = pd.read_hdf(f'{loc}/array_SingleMuon.h5')

    df = cut_Mu(df)

    df_hlt1 = cut_HLT1(df)
    df_hlt2 = cut_HLT2(df)
    df_hlt3 = cut_HLT3(df)
    df_hlt4 = cut_HLT4(df)
    df_hlt5 = cut_HLT5(df)
    df_hlt6 = cut_HLT6(df)
    df_hlt7 = cut_HLT7(df)
    df_hlt8 = cut_HLT8(df)
    df_hltcur = cut_HLTcur(df)
    df_hltall = cut_HLTall(df)

    input_var = ['nseljets', 'nselbjets', 'goodht', 'relht', 'mindR_dRbb', 'mindR_mbb', 'Chi2_max', 'Chi2_min', 'Chi2_min_H', 'Chi2_min_W', 'Chi2_min_Top', 'mass_h', 'mass_w', 'mass_top', 'mass_wh', 'mass_secondtop', 'mass_leadjets', 'dR_hbb', 'dR_wjj', 'dR_bw', 'dR_tprimeoj', 'ratio_mass_topH', 'ratio_mass_secondtopW', 'ratio_pt_topsecondtop', 'ratio_pt_htoptprime', 'ratio_pt_tprimehtprimetop', 'jet1_eta', 'jet1_e_massnom', 'jet2_eta', 'jet2_e_massnom', 'jet3_eta', 'jet3_e_massnom', 'jet4_eta', 'jet4_e_massnom', 'jet5_eta', 'jet5_e_massnom','mass_tprime']
#    input_var = ['goodht','jet1_pt','jet2_pt','jet3_pt','jet4_pt','jet5_pt','jet1_btag','jet2_btag','jet3_btag','mass_leadjets','mass_w','mass_h','mass_top','mass_wh','mass_secondtop','mass_tprime']
    for var in input_var:
        print(f"running on var = {var}")

        # Styling
        hep.style.use("CMS")
        fig, ax = plt.subplots()
        hep.cms.label("Preliminary", com = 13, lumi = 59.7, data = True, loc=0, ax=ax);
        ax.set_ylabel("Efficiency")
        name = var
    
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
    
        if "nsel" in var:
            binning = np.arange(xmin, xmax, step=1)
        else: 
            binning = [ edge for edge in np.arange(xmin, xmax+(xmax-xmin)/nbins, (xmax-xmin)/nbins) ]

        # treat under/overflow
        infBins = [np.array([-np.inf]), binning, np.array([np.inf])]
        infBins = np.concatenate(infBins)

        #weight
        h_nohlt, bins = np.histogram(df[var], bins=infBins)
        h_whlt1, bins = np.histogram(df_hlt1[var], bins=infBins)
        h_whlt2, bins = np.histogram(df_hlt2[var], bins=infBins)
        h_whlt3, bins = np.histogram(df_hlt3[var], bins=infBins)
        h_whlt4, bins = np.histogram(df_hlt4[var], bins=infBins)
        h_whlt5, bins = np.histogram(df_hlt5[var], bins=infBins)
        h_whlt6, bins = np.histogram(df_hlt6[var], bins=infBins)
        h_whlt7, bins = np.histogram(df_hlt7[var], bins=infBins)
        h_whlt8, bins = np.histogram(df_hlt8[var], bins=infBins)
        h_whltcur, bins = np.histogram(df_hltcur[var], bins=infBins)
        h_whltall, bins = np.histogram(df_hltall[var], bins=infBins)

        # treat under/overflow
        h_hlt0 = wrap_hist(h_nohlt)
        h_hlt1 = wrap_hist(h_whlt1)
        h_hlt2 = wrap_hist(h_whlt2)
        h_hlt3 = wrap_hist(h_whlt3)
        h_hlt4 = wrap_hist(h_whlt4)
        h_hlt5 = wrap_hist(h_whlt5)
        h_hlt6 = wrap_hist(h_whlt6)
        h_hlt7 = wrap_hist(h_whlt7)
        h_hlt8 = wrap_hist(h_whlt8)
        h_hltcur = wrap_hist(h_whltcur)
        h_hltall = wrap_hist(h_whltall)

        h_hlt0 = np.round(h_hlt0,3)
        h_hlt1 = np.round(h_hlt1,3)
        h_hlt2 = np.round(h_hlt2,3)
        h_hlt3 = np.round(h_hlt3,3)
        h_hlt4 = np.round(h_hlt4,3)
        h_hlt5 = np.round(h_hlt5,3)
        h_hlt6 = np.round(h_hlt6,3)
        h_hlt7 = np.round(h_hlt7,3)
        h_hlt8 = np.round(h_hlt8,3)
        h_hltcur = np.round(h_hltcur,3)
        h_hltall = np.round(h_hltall,3)

        h_eff_hlt1 = h_hlt1 / h_hlt0
        h_eff_hlt2 = h_hlt2 / h_hlt0
        h_eff_hlt3 = h_hlt3 / h_hlt0
        h_eff_hlt4 = h_hlt4 / h_hlt0
        h_eff_hlt5 = h_hlt5 / h_hlt0
        h_eff_hlt6 = h_hlt6 / h_hlt0
        h_eff_hlt7 = h_hlt7 / h_hlt0
        h_eff_hlt8 = h_hlt8 / h_hlt0
        h_eff_hltcur = h_hltcur / h_hlt0
        h_eff_hltall = h_hltall / h_hlt0

        hlt1_err = ratio_uncertainty(h_hlt1, h_hlt0, 'efficiency')
        hlt2_err = ratio_uncertainty(h_hlt2, h_hlt0, 'efficiency')
        hlt3_err = ratio_uncertainty(h_hlt3, h_hlt0, 'efficiency')
        hlt4_err = ratio_uncertainty(h_hlt4, h_hlt0, 'efficiency')
        hlt5_err = ratio_uncertainty(h_hlt5, h_hlt0, 'efficiency')
        hlt6_err = ratio_uncertainty(h_hlt6, h_hlt0, 'efficiency')
        hlt7_err = ratio_uncertainty(h_hlt7, h_hlt0, 'efficiency')
        hlt8_err = ratio_uncertainty(h_hlt8, h_hlt0, 'efficiency')
        hltcur_err = ratio_uncertainty(h_hltcur, h_hlt0, 'efficiency')
        hltall_err = ratio_uncertainty(h_hltall, h_hlt0, 'efficiency')

        hlt_errs = [hlt1_err,hlt2_err,hlt3_err,hlt4_err,hlt5_err,hlt6_err,hlt7_err,hlt8_err,hltcur_err,hltall_err]

        # Main plot
        # standard
        hep.histplot([h_eff_hlt1, h_eff_hlt2, h_eff_hlt3, h_eff_hlt4, h_eff_hlt5, h_eff_hlt6, h_eff_hlt7, h_eff_hlt8, h_eff_hltcur, h_eff_hltall], binning, ax=ax, histtype='errorbar', color=myc, capsize=2, xerr=True, yerr=hlt_errs, label=["HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5","HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2","HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepCSV_4p5","HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5","HLT_PFJet500","HLT_PFHT1050","HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94","HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59","Previous (B2G-19-001) all OR","all possible OR"])

        ax.set_xlabel(f"{name}")
        ax.set_xlim(xmin, xmax)
        ax.set_ylim(0, 1.4)
        ax.legend();
        handles, labels = ax.get_legend_handles_labels()
        ax.legend(handles[::-1], labels[::-1])
        ax.legend(fontsize=13)

        fig.subplots_adjust(left=0.15, right=0.95, top=0.95, bottom=0.12)
        fig.savefig(f"{outloc}/SingleMu_{var}.png")
        fig.savefig(f"{outloc}/SingleMu_{var}.pdf")
        plt.close()
