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
#myc = ['#0051FF','#403DDE','#6033CE','#8029BD','#C0159C','#E00B8C','#FF007B']
#myc = ['#185358','#016fb9','#02abba','#0051FF','#ef8a17','#ef2918','#8029BD','#E00B8C','#999999','#000000']
myc = ['#016fb9','#67A239','#847E2B','#345325','#ef8a17','#D81200','#8029BD','#FF007B','#999999','#000000']
nbins = 25

def binom_int(num, den, confint=0.68):
    quant = (1 - confint)/ 2.
    low = beta.ppf(quant, num, den - num + 1)
    high = beta.ppf(1 - quant, num + 1, den - num)
    return (np.nan_to_num(low), np.where(np.isnan(high), 1, high))

def getEfficiency(h_num, h_den):

    h_eff = np.nan_to_num(h_num/h_den)

    band_low, band_high = binom_int(h_num, h_den)

    error_low = h_eff - band_low
    error_high = band_high - h_eff

    error_low[error_low == 1] = 0
    error_high[error_high == 1] = 0

    error = np.concatenate((error_low.reshape(error_low.shape[0], 1), error_high.reshape(error_high.shape[0], 1)), axis=1)
    yerr = error.T

    yerr[yerr < 0] = 0.

    return h_eff, yerr

def cut0 (d):
    d = d.loc[(d['Chi2_min'] < 15) & (d['mass_secondtop'] > 250) & (d['mass_h'] > 100)]
    return d

def cut_sideband (d):
    d = d.loc[(d['mass_tprime'] < 600) | (d['mass_tprime'] > 1200 )]
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

# treat overflow underflow
def wrap_hist (h):
    h[1] += h[0]
    h[-2] += h[-1]
    h = h[1:-1]
    return h

for r in regions:
    print(f'running on region {r}')

    loc = f'/Users/jieun/WORK/vlq/dnn/training/array/woHLT/{r}/'
    outloc = f'/Users/jieun/WORK/vlq/plot/quickDraw/trigEff/signal/{r}'
    if not os.path.exists(f'{outloc}'): os.makedirs(f'{outloc}')
        
    signals = ['Tprime600','Tprime700','Tprime800','Tprime900','Tprime1000','Tprime1100','Tprime1200']

    h_hlt0 = []
    h_hlt1 = []
    h_hlt2 = []
    h_hlt3 = []
    h_hlt4 = []
    h_hlt5 = []
    h_hlt6 = []
    h_hlt7 = []
    h_hlt8 = []
    h_hltcur = []
    h_hltall = []

    input_var=['nseljets', 'nselbjets', 'goodht', 'relht', 'mindR_dRbb', 'mindR_mbb', 'jet1_eta', 'jet2_eta', 'jet3_eta', 'jet4_eta', 'jet5_eta', 'bjet1_eta', 'bjet2_eta', 'jet1_e_massnom', 'jet2_e_massnom', 'jet3_e_massnom', 'jet4_e_massnom', 'jet5_e_massnom', 'bjet1_e_massnom', 'bjet2_e_massnom', 'Chi2_max', 'Chi2_min', 'Chi2_min_H', 'Chi2_min_W', 'Chi2_min_Top', 'mass_h', 'mass_w', 'mass_top', 'mass_wh', 'mass_secondtop', 'mass_leadjets', 'dR_hbb', 'dR_wjj', 'dR_bw', 'dR_tprimeoj', 'ratio_mass_topH', 'ratio_mass_secondtopW', 'ratio_pt_topsecondtop', 'ratio_pt_htoptprime', 'ratio_pt_tprimehtprimetop']

    # load dataset
    for s in signals:
        print(f"signal mass = {s}")
        if "600" in s: w  = 0.026345781
        elif "700" in s: w = 0.013232631
        elif "800" in s: w = 0.006907082
        elif "900" in s: w = 0.003748747
        elif "1000" in s: w = 0.002165611
        elif "1100" in s: w = 0.001284431
        elif "1200" in s: w = 0.001426249
        else: print(f"signal = {s}")

        df = pd.read_hdf(f'{loc}/array_{s}.h5')

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
    
        for v in range(len(input_var)):

            var = input_var[v]
            print(f"running on var = {var}")

            # styling
            hep.style.use("CMS")
            fig, ax = plt.subplots()
            hep.cms.label("Preliminary", com = 13, lumi = 59.7, data = True, loc=0, ax=ax);
            ax.set_ylabel("Efficiency")
            name = var

            dat = df[var].dropna()
            dat_hlt1 = df_hlt1[var].dropna()
            dat_hlt2 = df_hlt2[var].dropna()
            dat_hlt3 = df_hlt3[var].dropna()
            dat_hlt4 = df_hlt4[var].dropna()
            dat_hlt5 = df_hlt5[var].dropna()
            dat_hlt6 = df_hlt6[var].dropna()
            dat_hlt7 = df_hlt7[var].dropna()
            dat_hlt8 = df_hlt8[var].dropna()
            dat_hltcur = df_hltcur[var].dropna()
            dat_hltall = df_hltall[var].dropna()

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
    
            ax.set_xlabel(f"{name}")
    
            if "nsel" in var:
                binning = np.arange(xmin, xmax, step=1)
            else:
                binning = [ edge for edge in np.arange(xmin, xmax+(xmax-xmin)/nbins, (xmax-xmin)/nbins) ]
    
            # treat under/overflow
            infBins = [np.array([-np.inf]), binning, np.array([np.inf])]
            infBins = np.concatenate(infBins)

            #weight
            h_nohlt, bins_nohlt = np.histogram(dat, bins=infBins, weights=df['evWeight_all']*w)
            h_whlt1, bins_whlt1 = np.histogram(dat_hlt1, bins=infBins, weights=df_hlt1['evWeight_all']*w)
            h_whlt2, bins_whlt2 = np.histogram(dat_hlt2, bins=infBins, weights=df_hlt2['evWeight_all']*w)
            h_whlt3, bins_whlt3 = np.histogram(dat_hlt3, bins=infBins, weights=df_hlt3['evWeight_all']*w)
            h_whlt4, bins_whlt4 = np.histogram(dat_hlt4, bins=infBins, weights=df_hlt4['evWeight_all']*w)
            h_whlt5, bins_whlt5 = np.histogram(dat_hlt5, bins=infBins, weights=df_hlt5['evWeight_all']*w)
            h_whlt6, bins_whlt6 = np.histogram(dat_hlt6, bins=infBins, weights=df_hlt6['evWeight_all']*w)
            h_whlt7, bins_whlt7 = np.histogram(dat_hlt7, bins=infBins, weights=df_hlt7['evWeight_all']*w)
            h_whlt8, bins_whlt8 = np.histogram(dat_hlt8, bins=infBins, weights=df_hlt8['evWeight_all']*w)
            h_whltcur, bins_whltcur = np.histogram(dat_hltcur, bins=infBins, weights=df_hltcur['evWeight_all']*w)
            h_whltall, bins_whltall = np.histogram(dat_hltall, bins=infBins, weights=df_hltall['evWeight_all']*w)

            # treat under/overflow
            h_nohlt = wrap_hist(h_nohlt)
            h_whlt1 = wrap_hist(h_whlt1)
            h_whlt2 = wrap_hist(h_whlt2)
            h_whlt3 = wrap_hist(h_whlt3)
            h_whlt4 = wrap_hist(h_whlt4)
            h_whlt5 = wrap_hist(h_whlt5)
            h_whlt6 = wrap_hist(h_whlt6)
            h_whlt7 = wrap_hist(h_whlt7)
            h_whlt8 = wrap_hist(h_whlt8)
            h_whltcur = wrap_hist(h_whltcur)
            h_whltall = wrap_hist(h_whltall)

            h_eff_hlt1, yerr_hlt1 = getEfficiency(h_whlt1, h_nohlt)
            h_eff_hlt2, yerr_hlt2 = getEfficiency(h_whlt2, h_nohlt)
            h_eff_hlt3, yerr_hlt3 = getEfficiency(h_whlt3, h_nohlt)
            h_eff_hlt4, yerr_hlt4 = getEfficiency(h_whlt4, h_nohlt)
            h_eff_hlt5, yerr_hlt5 = getEfficiency(h_whlt5, h_nohlt)
            h_eff_hlt6, yerr_hlt6 = getEfficiency(h_whlt6, h_nohlt)
            h_eff_hlt7, yerr_hlt7 = getEfficiency(h_whlt7, h_nohlt)
            h_eff_hlt8, yerr_hlt8 = getEfficiency(h_whlt8, h_nohlt)
            h_eff_hltcur, yerr_hltcur = getEfficiency(h_whltcur, h_nohlt)
            h_eff_hltall, yerr_hltall = getEfficiency(h_whltall, h_nohlt)

            y_errs = [yerr_hlt1,yerr_hlt2,yerr_hlt3,yerr_hlt4,yerr_hlt5,yerr_hlt6,yerr_hlt7,yerr_hlt8,yerr_hltcur,yerr_hltall]
            
            # main plot
            # standard
            hep.histplot([h_eff_hlt1, h_eff_hlt2, h_eff_hlt3, h_eff_hlt4, h_eff_hlt5, h_eff_hlt6, h_eff_hlt7, h_eff_hlt8, h_eff_hltcur, h_eff_hltall], binning, ax=ax, histtype='errorbar', color=myc, capsize=2, xerr=True, yerr=y_errs, label=["HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5","HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2","HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepCSV_4p5","HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5","HLT_PFJet500","HLT_PFHT1050","HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94","HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59","Current all OR","additional OR"])
        
            ax.set_xlabel(f"{name}")
            ax.set_xlim(xmin, xmax)
            ax.set_ylim(0, 1.4)
            ax.legend();
            handles, labels = ax.get_legend_handles_labels()
            ax.legend(handles[::-1], labels[::-1])
            ax.legend(fontsize=13.5)

            fig.subplots_adjust(left=0.15, right=0.95, top=0.95, bottom=0.12)
            fig.savefig(f"{outloc}/{s}_{var}.png")
            fig.savefig(f"{outloc}/{s}_{var}.pdf")
            plt.close()

            h_hlt0.append(h_nohlt)
            h_hlt1.append(h_whlt1)
            h_hlt2.append(h_whlt2)
            h_hlt3.append(h_whlt3)
            h_hlt4.append(h_whlt4)
            h_hlt5.append(h_whlt5)
            h_hlt6.append(h_whlt6)
            h_hlt7.append(h_whlt7)
            h_hlt8.append(h_whlt8)
            h_hltcur.append(h_whltcur)
            h_hltall.append(h_whltall)

    # for all mass point wrt cross section 
    for v in range(len(input_var)):
        var = input_var[v]
        print(f"running on var = {var}")

        # styling
        hep.style.use("CMS")
        fig, ax = plt.subplots()
        hep.cms.label("preliminary", com = 13, lumi = 59.7, data = True, loc=0, ax=ax);
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
    
        ax.set_xlabel(f"{name}")
    
        if "nsel" in var:
            binning = np.arange(xmin, xmax, step=1)
        else:
            binning = [ edge for edge in np.arange(xmin, xmax+(xmax-xmin)/nbins, (xmax-xmin)/nbins) ]

        h_all_eff_hlt1, yerr_all_hlt1 = getEfficiency(h_hlt1[v], h_hlt0[v])
        h_all_eff_hlt2, yerr_all_hlt2 = getEfficiency(h_hlt2[v], h_hlt0[v])
        h_all_eff_hlt3, yerr_all_hlt3 = getEfficiency(h_hlt3[v], h_hlt0[v])
        h_all_eff_hlt4, yerr_all_hlt4 = getEfficiency(h_hlt4[v], h_hlt0[v])
        h_all_eff_hlt5, yerr_all_hlt5 = getEfficiency(h_hlt5[v], h_hlt0[v])
        h_all_eff_hlt6, yerr_all_hlt6 = getEfficiency(h_hlt6[v], h_hlt0[v])
        h_all_eff_hlt7, yerr_all_hlt7 = getEfficiency(h_hlt7[v], h_hlt0[v])
        h_all_eff_hlt8, yerr_all_hlt8 = getEfficiency(h_hlt8[v], h_hlt0[v])
        h_all_eff_hltcur, yerr_all_hltcur = getEfficiency(h_hltcur[v], h_hlt0[v])
        h_all_eff_hltall, yerr_all_hltall = getEfficiency(h_hltall[v], h_hlt0[v])

        y_all_errs = [yerr_all_hlt1,yerr_all_hlt2,yerr_all_hlt3,yerr_all_hlt4,yerr_all_hlt5,yerr_all_hlt6,yerr_all_hlt7,yerr_all_hlt8,yerr_all_hltcur,yerr_all_hltall]
        
        # Main plot
        # Standard
        hep.histplot([h_all_eff_hlt1, h_all_eff_hlt2, h_all_eff_hlt3, h_all_eff_hlt4, h_all_eff_hlt5, h_all_eff_hlt6, h_all_eff_hlt7, h_all_eff_hlt8, h_all_eff_hltcur, h_all_eff_hltall], binning, ax=ax, histtype='errorbar', color=myc, capsize=2, xerr=True, yerr=y_all_errs, label=["HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5","HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2","HLT_PFHT400_FivePFJet_100_100_60_30_30_DoublePFBTagDeepCSV_4p5","HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5","HLT_PFJet500","HLT_PFHT1050","HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94","HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59","Current all OR","additional OR"])

        ax.set_xlabel(f"{name}")
        ax.set_xlim(xmin, xmax)
        ax.set_ylim(0, 1.4)
        ax.legend();
        handles, labels = ax.get_legend_handles_labels()
        ax.legend(handles[::-1], labels[::-1])
        ax.legend(fontsize=13.5)

        fig.subplots_adjust(left=0.15, right=0.95, top=0.95, bottom=0.12)
        fig.savefig(f"{outloc}/All_{var}.png")
        fig.savefig(f"{outloc}/All_{var}.pdf")
        plt.close()
