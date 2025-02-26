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
# T' mass from 600 GeV to 1200 GeV
#myc = ['#0051FF','#403DDE','#6033CE','#8029BD','#C0159C','#E00B8C','#FF007B']
#myc = ['#0051FF','#FF007B']
# MC
#myc = ['#185358','#02ABBA','#c6c015','#FFD639','#ef8a17','#016fb9']
#myc = ['#016fb9','#67A239','#847E2B','#345325','#ef8a17','#D81200','#8029BD','#FF007B','#999999','#000000']
# Data, MC
myc = ['#EF2918','#000000']

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

# treat overflow underflow
def wrap_hist (h):
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

    loc = f'/Users/jieun/WORK/vlq/dnn/training/array/woHLT/{r}/'
    outloc = f'/Users/jieun/WORK/vlq/plot/quickDraw/trigEff/sf/{r}'
    if not os.path.exists(f'{outloc}'): os.makedirs(f'{outloc}')

    df_dat = pd.read_hdf(f'{loc}/array_SingleMuon.h5')
    df_dat = cut_Mu(df_dat)
    
    # load dataset
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

    df_hlt1_dat = cut_HLT1(df_dat)
    df_hlt2_dat = cut_HLT2(df_dat)
    df_hlt3_dat = cut_HLT3(df_dat)
    df_hlt4_dat = cut_HLT4(df_dat)
    df_hlt5_dat = cut_HLT5(df_dat)
    df_hlt6_dat = cut_HLT6(df_dat)
    df_hlt7_dat = cut_HLT7(df_dat)
    df_hlt8_dat = cut_HLT8(df_dat)
    df_hltcur_dat = cut_HLTcur(df_dat)
    df_hltall_dat = cut_HLTall(df_dat)

    df_hlt1_tt = cut_HLT1(df_tt)
    df_hlt2_tt = cut_HLT2(df_tt)
    df_hlt3_tt = cut_HLT3(df_tt)
    df_hlt4_tt = cut_HLT4(df_tt)
    df_hlt5_tt = cut_HLT5(df_tt)
    df_hlt6_tt = cut_HLT6(df_tt)
    df_hlt7_tt = cut_HLT7(df_tt)
    df_hlt8_tt = cut_HLT8(df_tt)
    df_hltcur_tt = cut_HLTcur(df_tt)
    df_hltall_tt = cut_HLTall(df_tt)

    df_hlt1_qcd_BGenFilter_1 = cut_HLT1(df_qcd_BGenFilter_1)
    df_hlt2_qcd_BGenFilter_1 = cut_HLT2(df_qcd_BGenFilter_1)
    df_hlt3_qcd_BGenFilter_1 = cut_HLT3(df_qcd_BGenFilter_1)
    df_hlt4_qcd_BGenFilter_1 = cut_HLT4(df_qcd_BGenFilter_1)
    df_hlt5_qcd_BGenFilter_1 = cut_HLT5(df_qcd_BGenFilter_1)
    df_hlt6_qcd_BGenFilter_1 = cut_HLT6(df_qcd_BGenFilter_1)
    df_hlt7_qcd_BGenFilter_1 = cut_HLT7(df_qcd_BGenFilter_1)
    df_hlt8_qcd_BGenFilter_1 = cut_HLT8(df_qcd_BGenFilter_1)
    df_hltcur_qcd_BGenFilter_1 = cut_HLTcur(df_qcd_BGenFilter_1)
    df_hltall_qcd_BGenFilter_1 = cut_HLTall(df_qcd_BGenFilter_1)

    df_hlt1_qcd_BGenFilter_2 = cut_HLT1(df_qcd_BGenFilter_2)
    df_hlt2_qcd_BGenFilter_2 = cut_HLT2(df_qcd_BGenFilter_2)
    df_hlt3_qcd_BGenFilter_2 = cut_HLT3(df_qcd_BGenFilter_2)
    df_hlt4_qcd_BGenFilter_2 = cut_HLT4(df_qcd_BGenFilter_2)
    df_hlt5_qcd_BGenFilter_2 = cut_HLT5(df_qcd_BGenFilter_2)
    df_hlt6_qcd_BGenFilter_2 = cut_HLT6(df_qcd_BGenFilter_2)
    df_hlt7_qcd_BGenFilter_2 = cut_HLT7(df_qcd_BGenFilter_2)
    df_hlt8_qcd_BGenFilter_2 = cut_HLT8(df_qcd_BGenFilter_2)
    df_hltcur_qcd_BGenFilter_2 = cut_HLTcur(df_qcd_BGenFilter_2)
    df_hltall_qcd_BGenFilter_2 = cut_HLTall(df_qcd_BGenFilter_2)

    df_hlt1_qcd_BGenFilter_3 = cut_HLT1(df_qcd_BGenFilter_3)
    df_hlt2_qcd_BGenFilter_3 = cut_HLT2(df_qcd_BGenFilter_3)
    df_hlt3_qcd_BGenFilter_3 = cut_HLT3(df_qcd_BGenFilter_3)
    df_hlt4_qcd_BGenFilter_3 = cut_HLT4(df_qcd_BGenFilter_3)
    df_hlt5_qcd_BGenFilter_3 = cut_HLT5(df_qcd_BGenFilter_3)
    df_hlt6_qcd_BGenFilter_3 = cut_HLT6(df_qcd_BGenFilter_3)
    df_hlt7_qcd_BGenFilter_3 = cut_HLT7(df_qcd_BGenFilter_3)
    df_hlt8_qcd_BGenFilter_3 = cut_HLT8(df_qcd_BGenFilter_3)
    df_hltcur_qcd_BGenFilter_3 = cut_HLTcur(df_qcd_BGenFilter_3)
    df_hltall_qcd_BGenFilter_3 = cut_HLTall(df_qcd_BGenFilter_3)

    df_hlt1_qcd_BGenFilter_4 = cut_HLT1(df_qcd_BGenFilter_4)
    df_hlt2_qcd_BGenFilter_4 = cut_HLT2(df_qcd_BGenFilter_4)
    df_hlt3_qcd_BGenFilter_4 = cut_HLT3(df_qcd_BGenFilter_4)
    df_hlt4_qcd_BGenFilter_4 = cut_HLT4(df_qcd_BGenFilter_4)
    df_hlt5_qcd_BGenFilter_4 = cut_HLT5(df_qcd_BGenFilter_4)
    df_hlt6_qcd_BGenFilter_4 = cut_HLT6(df_qcd_BGenFilter_4)
    df_hlt7_qcd_BGenFilter_4 = cut_HLT7(df_qcd_BGenFilter_4)
    df_hlt8_qcd_BGenFilter_4 = cut_HLT8(df_qcd_BGenFilter_4)
    df_hltcur_qcd_BGenFilter_4 = cut_HLTcur(df_qcd_BGenFilter_4)
    df_hltall_qcd_BGenFilter_4 = cut_HLTall(df_qcd_BGenFilter_4)

    df_hlt1_qcd_BGenFilter_5 = cut_HLT1(df_qcd_BGenFilter_5)
    df_hlt2_qcd_BGenFilter_5 = cut_HLT2(df_qcd_BGenFilter_5)
    df_hlt3_qcd_BGenFilter_5 = cut_HLT3(df_qcd_BGenFilter_5)
    df_hlt4_qcd_BGenFilter_5 = cut_HLT4(df_qcd_BGenFilter_5)
    df_hlt5_qcd_BGenFilter_5 = cut_HLT5(df_qcd_BGenFilter_5)
    df_hlt6_qcd_BGenFilter_5 = cut_HLT6(df_qcd_BGenFilter_5)
    df_hlt7_qcd_BGenFilter_5 = cut_HLT7(df_qcd_BGenFilter_5)
    df_hlt8_qcd_BGenFilter_5 = cut_HLT8(df_qcd_BGenFilter_5)
    df_hltcur_qcd_BGenFilter_5 = cut_HLTcur(df_qcd_BGenFilter_5)
    df_hltall_qcd_BGenFilter_5 = cut_HLTall(df_qcd_BGenFilter_5)

    df_hlt1_qcd_BGenFilter_6 = cut_HLT1(df_qcd_BGenFilter_6)
    df_hlt2_qcd_BGenFilter_6 = cut_HLT2(df_qcd_BGenFilter_6)
    df_hlt3_qcd_BGenFilter_6 = cut_HLT3(df_qcd_BGenFilter_6)
    df_hlt4_qcd_BGenFilter_6 = cut_HLT4(df_qcd_BGenFilter_6)
    df_hlt5_qcd_BGenFilter_6 = cut_HLT5(df_qcd_BGenFilter_6)
    df_hlt6_qcd_BGenFilter_6 = cut_HLT6(df_qcd_BGenFilter_6)
    df_hlt7_qcd_BGenFilter_6 = cut_HLT7(df_qcd_BGenFilter_6)
    df_hlt8_qcd_BGenFilter_6 = cut_HLT8(df_qcd_BGenFilter_6)
    df_hltcur_qcd_BGenFilter_6 = cut_HLTcur(df_qcd_BGenFilter_6)
    df_hltall_qcd_BGenFilter_6 = cut_HLTall(df_qcd_BGenFilter_6)

    df_hlt1_qcd_bEnriched_1 = cut_HLT1(df_qcd_bEnriched_1)
    df_hlt2_qcd_bEnriched_1 = cut_HLT2(df_qcd_bEnriched_1)
    df_hlt3_qcd_bEnriched_1 = cut_HLT3(df_qcd_bEnriched_1)
    df_hlt4_qcd_bEnriched_1 = cut_HLT4(df_qcd_bEnriched_1)
    df_hlt5_qcd_bEnriched_1 = cut_HLT5(df_qcd_bEnriched_1)
    df_hlt6_qcd_bEnriched_1 = cut_HLT6(df_qcd_bEnriched_1)
    df_hlt7_qcd_bEnriched_1 = cut_HLT7(df_qcd_bEnriched_1)
    df_hlt8_qcd_bEnriched_1 = cut_HLT8(df_qcd_bEnriched_1)
    df_hltcur_qcd_bEnriched_1 = cut_HLTcur(df_qcd_bEnriched_1)
    df_hltall_qcd_bEnriched_1 = cut_HLTall(df_qcd_bEnriched_1)

    df_hlt1_qcd_bEnriched_2 = cut_HLT1(df_qcd_bEnriched_2)
    df_hlt2_qcd_bEnriched_2 = cut_HLT2(df_qcd_bEnriched_2)
    df_hlt3_qcd_bEnriched_2 = cut_HLT3(df_qcd_bEnriched_2)
    df_hlt4_qcd_bEnriched_2 = cut_HLT4(df_qcd_bEnriched_2)
    df_hlt5_qcd_bEnriched_2 = cut_HLT5(df_qcd_bEnriched_2)
    df_hlt6_qcd_bEnriched_2 = cut_HLT6(df_qcd_bEnriched_2)
    df_hlt7_qcd_bEnriched_2 = cut_HLT7(df_qcd_bEnriched_2)
    df_hlt8_qcd_bEnriched_2 = cut_HLT8(df_qcd_bEnriched_2)
    df_hltcur_qcd_bEnriched_2 = cut_HLTcur(df_qcd_bEnriched_2)
    df_hltall_qcd_bEnriched_2 = cut_HLTall(df_qcd_bEnriched_2)

    df_hlt1_qcd_bEnriched_3 = cut_HLT1(df_qcd_bEnriched_3)
    df_hlt2_qcd_bEnriched_3 = cut_HLT2(df_qcd_bEnriched_3)
    df_hlt3_qcd_bEnriched_3 = cut_HLT3(df_qcd_bEnriched_3)
    df_hlt4_qcd_bEnriched_3 = cut_HLT4(df_qcd_bEnriched_3)
    df_hlt5_qcd_bEnriched_3 = cut_HLT5(df_qcd_bEnriched_3)
    df_hlt6_qcd_bEnriched_3 = cut_HLT6(df_qcd_bEnriched_3)
    df_hlt7_qcd_bEnriched_3 = cut_HLT7(df_qcd_bEnriched_3)
    df_hlt8_qcd_bEnriched_3 = cut_HLT8(df_qcd_bEnriched_3)
    df_hltcur_qcd_bEnriched_3 = cut_HLTcur(df_qcd_bEnriched_3)
    df_hltall_qcd_bEnriched_3 = cut_HLTall(df_qcd_bEnriched_3)

    df_hlt1_qcd_bEnriched_4 = cut_HLT1(df_qcd_bEnriched_4)
    df_hlt2_qcd_bEnriched_4 = cut_HLT2(df_qcd_bEnriched_4)
    df_hlt3_qcd_bEnriched_4 = cut_HLT3(df_qcd_bEnriched_4)
    df_hlt4_qcd_bEnriched_4 = cut_HLT4(df_qcd_bEnriched_4)
    df_hlt5_qcd_bEnriched_4 = cut_HLT5(df_qcd_bEnriched_4)
    df_hlt6_qcd_bEnriched_4 = cut_HLT6(df_qcd_bEnriched_4)
    df_hlt7_qcd_bEnriched_4 = cut_HLT7(df_qcd_bEnriched_4)
    df_hlt8_qcd_bEnriched_4 = cut_HLT8(df_qcd_bEnriched_4)
    df_hltcur_qcd_bEnriched_4 = cut_HLTcur(df_qcd_bEnriched_4)
    df_hltall_qcd_bEnriched_4 = cut_HLTall(df_qcd_bEnriched_4)

    df_hlt1_qcd_bEnriched_5 = cut_HLT1(df_qcd_bEnriched_5)
    df_hlt2_qcd_bEnriched_5 = cut_HLT2(df_qcd_bEnriched_5)
    df_hlt3_qcd_bEnriched_5 = cut_HLT3(df_qcd_bEnriched_5)
    df_hlt4_qcd_bEnriched_5 = cut_HLT4(df_qcd_bEnriched_5)
    df_hlt5_qcd_bEnriched_5 = cut_HLT5(df_qcd_bEnriched_5)
    df_hlt6_qcd_bEnriched_5 = cut_HLT6(df_qcd_bEnriched_5)
    df_hlt7_qcd_bEnriched_5 = cut_HLT7(df_qcd_bEnriched_5)
    df_hlt8_qcd_bEnriched_5 = cut_HLT8(df_qcd_bEnriched_5)
    df_hltcur_qcd_bEnriched_5 = cut_HLTcur(df_qcd_bEnriched_5)
    df_hltall_qcd_bEnriched_5 = cut_HLTall(df_qcd_bEnriched_5)

    df_hlt1_qcd_bEnriched_6 = cut_HLT1(df_qcd_bEnriched_6)
    df_hlt2_qcd_bEnriched_6 = cut_HLT2(df_qcd_bEnriched_6)
    df_hlt3_qcd_bEnriched_6 = cut_HLT3(df_qcd_bEnriched_6)
    df_hlt4_qcd_bEnriched_6 = cut_HLT4(df_qcd_bEnriched_6)
    df_hlt5_qcd_bEnriched_6 = cut_HLT5(df_qcd_bEnriched_6)
    df_hlt6_qcd_bEnriched_6 = cut_HLT6(df_qcd_bEnriched_6)
    df_hlt7_qcd_bEnriched_6 = cut_HLT7(df_qcd_bEnriched_6)
    df_hlt8_qcd_bEnriched_6 = cut_HLT8(df_qcd_bEnriched_6)
    df_hltcur_qcd_bEnriched_6 = cut_HLTcur(df_qcd_bEnriched_6)
    df_hltall_qcd_bEnriched_6 = cut_HLTall(df_qcd_bEnriched_6)

    df_hlt1_wjets_1 = cut_HLT1(df_wjets_1)
    df_hlt2_wjets_1 = cut_HLT2(df_wjets_1)
    df_hlt3_wjets_1 = cut_HLT3(df_wjets_1)
    df_hlt4_wjets_1 = cut_HLT4(df_wjets_1)
    df_hlt5_wjets_1 = cut_HLT5(df_wjets_1)
    df_hlt6_wjets_1 = cut_HLT6(df_wjets_1)
    df_hlt7_wjets_1 = cut_HLT7(df_wjets_1)
    df_hlt8_wjets_1 = cut_HLT8(df_wjets_1)
    df_hltcur_wjets_1 = cut_HLTcur(df_wjets_1)
    df_hltall_wjets_1 = cut_HLTall(df_wjets_1)

    df_hlt1_wjets_2 = cut_HLT1(df_wjets_2)
    df_hlt2_wjets_2 = cut_HLT2(df_wjets_2)
    df_hlt3_wjets_2 = cut_HLT3(df_wjets_2)
    df_hlt4_wjets_2 = cut_HLT4(df_wjets_2)
    df_hlt5_wjets_2 = cut_HLT5(df_wjets_2)
    df_hlt6_wjets_2 = cut_HLT6(df_wjets_2)
    df_hlt7_wjets_2 = cut_HLT7(df_wjets_2)
    df_hlt8_wjets_2 = cut_HLT8(df_wjets_2)
    df_hltcur_wjets_2 = cut_HLTcur(df_wjets_2)
    df_hltall_wjets_2 = cut_HLTall(df_wjets_2)

    df_hlt1_wjets_3 = cut_HLT1(df_wjets_3)
    df_hlt2_wjets_3 = cut_HLT2(df_wjets_3)
    df_hlt3_wjets_3 = cut_HLT3(df_wjets_3)
    df_hlt4_wjets_3 = cut_HLT4(df_wjets_3)
    df_hlt5_wjets_3 = cut_HLT5(df_wjets_3)
    df_hlt6_wjets_3 = cut_HLT6(df_wjets_3)
    df_hlt7_wjets_3 = cut_HLT7(df_wjets_3)
    df_hlt8_wjets_3 = cut_HLT8(df_wjets_3)
    df_hltcur_wjets_3 = cut_HLTcur(df_wjets_3)
    df_hltall_wjets_3 = cut_HLTall(df_wjets_3)

    df_hlt1_zjets_1 = cut_HLT1(df_zjets_1)
    df_hlt2_zjets_1 = cut_HLT2(df_zjets_1)
    df_hlt3_zjets_1 = cut_HLT3(df_zjets_1)
    df_hlt4_zjets_1 = cut_HLT4(df_zjets_1)
    df_hlt5_zjets_1 = cut_HLT5(df_zjets_1)
    df_hlt6_zjets_1 = cut_HLT6(df_zjets_1)
    df_hlt7_zjets_1 = cut_HLT7(df_zjets_1)
    df_hlt8_zjets_1 = cut_HLT8(df_zjets_1)
    df_hltcur_zjets_1 = cut_HLTcur(df_zjets_1)
    df_hltall_zjets_1 = cut_HLTall(df_zjets_1)

    df_hlt1_zjets_2 = cut_HLT1(df_zjets_2)
    df_hlt2_zjets_2 = cut_HLT2(df_zjets_2)
    df_hlt3_zjets_2 = cut_HLT3(df_zjets_2)
    df_hlt4_zjets_2 = cut_HLT4(df_zjets_2)
    df_hlt5_zjets_2 = cut_HLT5(df_zjets_2)
    df_hlt6_zjets_2 = cut_HLT6(df_zjets_2)
    df_hlt7_zjets_2 = cut_HLT7(df_zjets_2)
    df_hlt8_zjets_2 = cut_HLT8(df_zjets_2)
    df_hltcur_zjets_2 = cut_HLTcur(df_zjets_2)
    df_hltall_zjets_2 = cut_HLTall(df_zjets_2)

    df_hlt1_zjets_3 = cut_HLT1(df_zjets_3)
    df_hlt2_zjets_3 = cut_HLT2(df_zjets_3)
    df_hlt3_zjets_3 = cut_HLT3(df_zjets_3)
    df_hlt4_zjets_3 = cut_HLT4(df_zjets_3)
    df_hlt5_zjets_3 = cut_HLT5(df_zjets_3)
    df_hlt6_zjets_3 = cut_HLT6(df_zjets_3)
    df_hlt7_zjets_3 = cut_HLT7(df_zjets_3)
    df_hlt8_zjets_3 = cut_HLT8(df_zjets_3)
    df_hltcur_zjets_3 = cut_HLTcur(df_zjets_3)
    df_hltall_zjets_3 = cut_HLTall(df_zjets_3)

    df_hlt1_st_s = cut_HLT1(df_st_s)
    df_hlt2_st_s = cut_HLT2(df_st_s)
    df_hlt3_st_s = cut_HLT3(df_st_s)
    df_hlt4_st_s = cut_HLT4(df_st_s)
    df_hlt5_st_s = cut_HLT5(df_st_s)
    df_hlt6_st_s = cut_HLT6(df_st_s)
    df_hlt7_st_s = cut_HLT7(df_st_s)
    df_hlt8_st_s = cut_HLT8(df_st_s)
    df_hltcur_st_s = cut_HLTcur(df_st_s)
    df_hltall_st_s = cut_HLTall(df_st_s)

    df_hlt1_st_t = cut_HLT1(df_st_t)
    df_hlt2_st_t = cut_HLT2(df_st_t)
    df_hlt3_st_t = cut_HLT3(df_st_t)
    df_hlt4_st_t = cut_HLT4(df_st_t)
    df_hlt5_st_t = cut_HLT5(df_st_t)
    df_hlt6_st_t = cut_HLT6(df_st_t)
    df_hlt7_st_t = cut_HLT7(df_st_t)
    df_hlt8_st_t = cut_HLT8(df_st_t)
    df_hltcur_st_t = cut_HLTcur(df_st_t)
    df_hltall_st_t = cut_HLTall(df_st_t)

    df_hlt1_st_ant = cut_HLT1(df_st_ant)
    df_hlt2_st_ant = cut_HLT2(df_st_ant)
    df_hlt3_st_ant = cut_HLT3(df_st_ant)
    df_hlt4_st_ant = cut_HLT4(df_st_ant)
    df_hlt5_st_ant = cut_HLT5(df_st_ant)
    df_hlt6_st_ant = cut_HLT6(df_st_ant)
    df_hlt7_st_ant = cut_HLT7(df_st_ant)
    df_hlt8_st_ant = cut_HLT8(df_st_ant)
    df_hltcur_st_ant = cut_HLTcur(df_st_ant)
    df_hltall_st_ant = cut_HLTall(df_st_ant)

    df_hlt1_st_tW = cut_HLT1(df_st_tW)
    df_hlt2_st_tW = cut_HLT2(df_st_tW)
    df_hlt3_st_tW = cut_HLT3(df_st_tW)
    df_hlt4_st_tW = cut_HLT4(df_st_tW)
    df_hlt5_st_tW = cut_HLT5(df_st_tW)
    df_hlt6_st_tW = cut_HLT6(df_st_tW)
    df_hlt7_st_tW = cut_HLT7(df_st_tW)
    df_hlt8_st_tW = cut_HLT8(df_st_tW)
    df_hltcur_st_tW = cut_HLTcur(df_st_tW)
    df_hltall_st_tW = cut_HLTall(df_st_tW)

    df_hlt1_st_antW = cut_HLT1(df_st_antW)
    df_hlt2_st_antW = cut_HLT2(df_st_antW)
    df_hlt3_st_antW = cut_HLT3(df_st_antW)
    df_hlt4_st_antW = cut_HLT4(df_st_antW)
    df_hlt5_st_antW = cut_HLT5(df_st_antW)
    df_hlt6_st_antW = cut_HLT6(df_st_antW)
    df_hlt7_st_antW = cut_HLT7(df_st_antW)
    df_hlt8_st_antW = cut_HLT8(df_st_antW)
    df_hltcur_st_antW = cut_HLTcur(df_st_antW)
    df_hltall_st_antW = cut_HLTall(df_st_antW)

    df_hlt1_tth = cut_HLT1(df_tth)
    df_hlt2_tth = cut_HLT2(df_tth)
    df_hlt3_tth = cut_HLT3(df_tth)
    df_hlt4_tth = cut_HLT4(df_tth)
    df_hlt5_tth = cut_HLT5(df_tth)
    df_hlt6_tth = cut_HLT6(df_tth)
    df_hlt7_tth = cut_HLT7(df_tth)
    df_hlt8_tth = cut_HLT8(df_tth)
    df_hltcur_tth = cut_HLTcur(df_tth)
    df_hltall_tth = cut_HLTall(df_tth)

    # normalization w/ only genWeight
    # scale 2018 lumi, xsecs from xsdb
    wtt =  0.000213165716054138

    wqcd_BGenFilter_1 = 1937.29849628
    wqcd_BGenFilter_2 = 355.177976291
    wqcd_BGenFilter_3 = 144.676258504
    wqcd_BGenFilter_4 = 80.4483146147
    wqcd_BGenFilter_5 = 10.0225103394
    wqcd_BGenFilter_6 = 1.98606789537

    wqcd_bEnriched_1 = 88.5627094510
    wqcd_bEnriched_2 = 9.71036157206
    wqcd_bEnriched_3 = 9.63415605436
    wqcd_bEnriched_4 = 2.15831431386
    wqcd_bEnriched_5 = 0.16491600442
    wqcd_bEnriched_6 = 0.03062018169

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

    input_var = ['nseljets', 'nselbjets', 'goodht', 'relht', 'mindR_dRbb', 'mindR_mbb', 'Chi2_max', 'Chi2_min', 'Chi2_min_H', 'Chi2_min_W', 'Chi2_min_Top', 'mass_h', 'mass_w', 'mass_top', 'mass_wh', 'mass_secondtop', 'mass_leadjets', 'dR_hbb', 'dR_wjj', 'dR_bw', 'dR_tprimeoj', 'ratio_mass_topH', 'ratio_mass_secondtopW', 'ratio_pt_topsecondtop', 'ratio_pt_htoptprime', 'ratio_pt_tprimehtprimetop', 'jet1_eta', 'jet1_e_massnom', 'jet2_eta', 'jet2_e_massnom', 'jet3_eta', 'jet3_e_massnom', 'jet4_eta', 'jet4_e_massnom', 'jet5_eta', 'jet5_e_massnom']
#    input_var = ['goodht','jet1_pt','jet2_pt','jet3_pt','jet4_pt','jet5_pt','jet1_btag','jet2_btag','jet3_btag','mass_leadjets','mass_w','mass_h','mass_top','mass_wh','mass_secondtop','mass_tprime']
    for var in input_var:
        print(f"running on var = {var}")

        # Styling
        hep.style.use("CMS")
        fig, (ax, rax) = plt.subplots(2, 1, gridspec_kw=dict(height_ratios=[3, 1], hspace=0.1), sharex=True)
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

        rax.set_xlabel(f"{name}")
    
        if "nsel" in var:
            binning = np.arange(xmin, xmax, step=1)
        else: 
            binning = [ edge for edge in np.arange(xmin, xmax+(xmax-xmin)/nbins, (xmax-xmin)/nbins) ]

        # treat under/overflow
        infBins = [np.array([-np.inf]), binning, np.array([np.inf])]
        infBins = np.concatenate(infBins)

        h_nohlt_dat, bins = np.histogram(df_dat[var], bins=infBins)
        h_whlt1_dat, bins = np.histogram(df_hlt1_dat[var], bins=infBins)
        h_whlt2_dat, bins = np.histogram(df_hlt2_dat[var], bins=infBins)
        h_whlt3_dat, bins = np.histogram(df_hlt3_dat[var], bins=infBins)
        h_whlt4_dat, bins = np.histogram(df_hlt4_dat[var], bins=infBins)
        h_whlt5_dat, bins = np.histogram(df_hlt5_dat[var], bins=infBins)
        h_whlt6_dat, bins = np.histogram(df_hlt6_dat[var], bins=infBins)
        h_whlt7_dat, bins = np.histogram(df_hlt7_dat[var], bins=infBins)
        h_whlt8_dat, bins = np.histogram(df_hlt8_dat[var], bins=infBins)
        h_whltcur_dat, bins = np.histogram(df_hltcur_dat[var], bins=infBins)
        h_whltall_dat, bins = np.histogram(df_hltall_dat[var], bins=infBins)

        #weight
        h_nohlt_tt, bins_tt = np.histogram(df_tt[var], bins=infBins, weights = df_tt['evWeight_all']*wtt)
        h_whlt1_tt, bins_tt = np.histogram(df_hlt1_tt[var], bins=infBins, weights = df_hlt1_tt['evWeight_all']*wtt)
        h_whlt2_tt, bins_tt = np.histogram(df_hlt2_tt[var], bins=infBins, weights = df_hlt2_tt['evWeight_all']*wtt)
        h_whlt3_tt, bins_tt = np.histogram(df_hlt3_tt[var], bins=infBins, weights = df_hlt3_tt['evWeight_all']*wtt)
        h_whlt4_tt, bins_tt = np.histogram(df_hlt4_tt[var], bins=infBins, weights = df_hlt4_tt['evWeight_all']*wtt)
        h_whlt5_tt, bins_tt = np.histogram(df_hlt5_tt[var], bins=infBins, weights = df_hlt5_tt['evWeight_all']*wtt)
        h_whlt6_tt, bins_tt = np.histogram(df_hlt6_tt[var], bins=infBins, weights = df_hlt6_tt['evWeight_all']*wtt)
        h_whlt7_tt, bins_tt = np.histogram(df_hlt7_tt[var], bins=infBins, weights = df_hlt7_tt['evWeight_all']*wtt)
        h_whlt8_tt, bins_tt = np.histogram(df_hlt8_tt[var], bins=infBins, weights = df_hlt8_tt['evWeight_all']*wtt)
        h_whltcur_tt, bins_tt = np.histogram(df_hltcur_tt[var], bins=infBins, weights = df_hltcur_tt['evWeight_all']*wtt)
        h_whltall_tt, bins_tt = np.histogram(df_hltall_tt[var], bins=infBins, weights = df_hltall_tt['evWeight_all']*wtt)

        h_nohlt_qcd_BGenFilter_1, bins_qcd_BGenFilter_1 = np.histogram(df_qcd_BGenFilter_1[var], bins=infBins, weights = df_qcd_BGenFilter_1['evWeight_all']*wqcd_BGenFilter_1)
        h_whlt1_qcd_BGenFilter_1, bins_qcd_BGenFilter_1 = np.histogram(df_hlt1_qcd_BGenFilter_1[var], bins=infBins, weights = df_hlt1_qcd_BGenFilter_1['evWeight_all']*wqcd_BGenFilter_1)
        h_whlt2_qcd_BGenFilter_1, bins_qcd_BGenFilter_1 = np.histogram(df_hlt2_qcd_BGenFilter_1[var], bins=infBins, weights = df_hlt2_qcd_BGenFilter_1['evWeight_all']*wqcd_BGenFilter_1)
        h_whlt3_qcd_BGenFilter_1, bins_qcd_BGenFilter_1 = np.histogram(df_hlt3_qcd_BGenFilter_1[var], bins=infBins, weights = df_hlt3_qcd_BGenFilter_1['evWeight_all']*wqcd_BGenFilter_1)
        h_whlt4_qcd_BGenFilter_1, bins_qcd_BGenFilter_1 = np.histogram(df_hlt4_qcd_BGenFilter_1[var], bins=infBins, weights = df_hlt4_qcd_BGenFilter_1['evWeight_all']*wqcd_BGenFilter_1)
        h_whlt5_qcd_BGenFilter_1, bins_qcd_BGenFilter_1 = np.histogram(df_hlt5_qcd_BGenFilter_1[var], bins=infBins, weights = df_hlt5_qcd_BGenFilter_1['evWeight_all']*wqcd_BGenFilter_1)
        h_whlt6_qcd_BGenFilter_1, bins_qcd_BGenFilter_1 = np.histogram(df_hlt6_qcd_BGenFilter_1[var], bins=infBins, weights = df_hlt6_qcd_BGenFilter_1['evWeight_all']*wqcd_BGenFilter_1)
        h_whlt7_qcd_BGenFilter_1, bins_qcd_BGenFilter_1 = np.histogram(df_hlt7_qcd_BGenFilter_1[var], bins=infBins, weights = df_hlt7_qcd_BGenFilter_1['evWeight_all']*wqcd_BGenFilter_1)
        h_whlt8_qcd_BGenFilter_1, bins_qcd_BGenFilter_1 = np.histogram(df_hlt8_qcd_BGenFilter_1[var], bins=infBins, weights = df_hlt8_qcd_BGenFilter_1['evWeight_all']*wqcd_BGenFilter_1)
        h_whltcur_qcd_BGenFilter_1, bins_qcd_BGenFilter_1 = np.histogram(df_hltcur_qcd_BGenFilter_1[var], bins=infBins, weights = df_hltcur_qcd_BGenFilter_1['evWeight_all']*wqcd_BGenFilter_1)
        h_whltall_qcd_BGenFilter_1, bins_qcd_BGenFilter_1 = np.histogram(df_hltall_qcd_BGenFilter_1[var], bins=infBins, weights = df_hltall_qcd_BGenFilter_1['evWeight_all']*wqcd_BGenFilter_1)

        h_nohlt_qcd_BGenFilter_2, bins_qcd_BGenFilter_2 = np.histogram(df_qcd_BGenFilter_2[var], bins=infBins, weights = df_qcd_BGenFilter_2['evWeight_all']*wqcd_BGenFilter_2)
        h_whlt1_qcd_BGenFilter_2, bins_qcd_BGenFilter_2 = np.histogram(df_hlt1_qcd_BGenFilter_2[var], bins=infBins, weights = df_hlt1_qcd_BGenFilter_2['evWeight_all']*wqcd_BGenFilter_2)
        h_whlt2_qcd_BGenFilter_2, bins_qcd_BGenFilter_2 = np.histogram(df_hlt2_qcd_BGenFilter_2[var], bins=infBins, weights = df_hlt2_qcd_BGenFilter_2['evWeight_all']*wqcd_BGenFilter_2)
        h_whlt3_qcd_BGenFilter_2, bins_qcd_BGenFilter_2 = np.histogram(df_hlt3_qcd_BGenFilter_2[var], bins=infBins, weights = df_hlt3_qcd_BGenFilter_2['evWeight_all']*wqcd_BGenFilter_2)
        h_whlt4_qcd_BGenFilter_2, bins_qcd_BGenFilter_2 = np.histogram(df_hlt4_qcd_BGenFilter_2[var], bins=infBins, weights = df_hlt4_qcd_BGenFilter_2['evWeight_all']*wqcd_BGenFilter_2)
        h_whlt5_qcd_BGenFilter_2, bins_qcd_BGenFilter_2 = np.histogram(df_hlt5_qcd_BGenFilter_2[var], bins=infBins, weights = df_hlt5_qcd_BGenFilter_2['evWeight_all']*wqcd_BGenFilter_2)
        h_whlt6_qcd_BGenFilter_2, bins_qcd_BGenFilter_2 = np.histogram(df_hlt6_qcd_BGenFilter_2[var], bins=infBins, weights = df_hlt6_qcd_BGenFilter_2['evWeight_all']*wqcd_BGenFilter_2)
        h_whlt7_qcd_BGenFilter_2, bins_qcd_BGenFilter_2 = np.histogram(df_hlt7_qcd_BGenFilter_2[var], bins=infBins, weights = df_hlt7_qcd_BGenFilter_2['evWeight_all']*wqcd_BGenFilter_2)
        h_whlt8_qcd_BGenFilter_2, bins_qcd_BGenFilter_2 = np.histogram(df_hlt8_qcd_BGenFilter_2[var], bins=infBins, weights = df_hlt8_qcd_BGenFilter_2['evWeight_all']*wqcd_BGenFilter_2)
        h_whltcur_qcd_BGenFilter_2, bins_qcd_BGenFilter_2 = np.histogram(df_hltcur_qcd_BGenFilter_2[var], bins=infBins, weights = df_hltcur_qcd_BGenFilter_2['evWeight_all']*wqcd_BGenFilter_2)
        h_whltall_qcd_BGenFilter_2, bins_qcd_BGenFilter_2 = np.histogram(df_hltall_qcd_BGenFilter_2[var], bins=infBins, weights = df_hltall_qcd_BGenFilter_2['evWeight_all']*wqcd_BGenFilter_2)

        h_nohlt_qcd_BGenFilter_3, bins_qcd_BGenFilter_3 = np.histogram(df_qcd_BGenFilter_3[var], bins=infBins, weights = df_qcd_BGenFilter_3['evWeight_all']*wqcd_BGenFilter_3)
        h_whlt1_qcd_BGenFilter_3, bins_qcd_BGenFilter_3 = np.histogram(df_hlt1_qcd_BGenFilter_3[var], bins=infBins, weights = df_hlt1_qcd_BGenFilter_3['evWeight_all']*wqcd_BGenFilter_3)
        h_whlt2_qcd_BGenFilter_3, bins_qcd_BGenFilter_3 = np.histogram(df_hlt2_qcd_BGenFilter_3[var], bins=infBins, weights = df_hlt2_qcd_BGenFilter_3['evWeight_all']*wqcd_BGenFilter_3)
        h_whlt3_qcd_BGenFilter_3, bins_qcd_BGenFilter_3 = np.histogram(df_hlt3_qcd_BGenFilter_3[var], bins=infBins, weights = df_hlt3_qcd_BGenFilter_3['evWeight_all']*wqcd_BGenFilter_3)
        h_whlt4_qcd_BGenFilter_3, bins_qcd_BGenFilter_3 = np.histogram(df_hlt4_qcd_BGenFilter_3[var], bins=infBins, weights = df_hlt4_qcd_BGenFilter_3['evWeight_all']*wqcd_BGenFilter_3)
        h_whlt5_qcd_BGenFilter_3, bins_qcd_BGenFilter_3 = np.histogram(df_hlt5_qcd_BGenFilter_3[var], bins=infBins, weights = df_hlt5_qcd_BGenFilter_3['evWeight_all']*wqcd_BGenFilter_3)
        h_whlt6_qcd_BGenFilter_3, bins_qcd_BGenFilter_3 = np.histogram(df_hlt6_qcd_BGenFilter_3[var], bins=infBins, weights = df_hlt6_qcd_BGenFilter_3['evWeight_all']*wqcd_BGenFilter_3)
        h_whlt7_qcd_BGenFilter_3, bins_qcd_BGenFilter_3 = np.histogram(df_hlt7_qcd_BGenFilter_3[var], bins=infBins, weights = df_hlt7_qcd_BGenFilter_3['evWeight_all']*wqcd_BGenFilter_3)
        h_whlt8_qcd_BGenFilter_3, bins_qcd_BGenFilter_3 = np.histogram(df_hlt8_qcd_BGenFilter_3[var], bins=infBins, weights = df_hlt8_qcd_BGenFilter_3['evWeight_all']*wqcd_BGenFilter_3)
        h_whltcur_qcd_BGenFilter_3, bins_qcd_BGenFilter_3 = np.histogram(df_hltcur_qcd_BGenFilter_3[var], bins=infBins, weights = df_hltcur_qcd_BGenFilter_3['evWeight_all']*wqcd_BGenFilter_3)
        h_whltall_qcd_BGenFilter_3, bins_qcd_BGenFilter_3 = np.histogram(df_hltall_qcd_BGenFilter_3[var], bins=infBins, weights = df_hltall_qcd_BGenFilter_3['evWeight_all']*wqcd_BGenFilter_3)

        h_nohlt_qcd_BGenFilter_4, bins_qcd_BGenFilter_4 = np.histogram(df_qcd_BGenFilter_4[var], bins=infBins, weights = df_qcd_BGenFilter_4['evWeight_all']*wqcd_BGenFilter_4)
        h_whlt1_qcd_BGenFilter_4, bins_qcd_BGenFilter_4 = np.histogram(df_hlt1_qcd_BGenFilter_4[var], bins=infBins, weights = df_hlt1_qcd_BGenFilter_4['evWeight_all']*wqcd_BGenFilter_4)
        h_whlt2_qcd_BGenFilter_4, bins_qcd_BGenFilter_4 = np.histogram(df_hlt2_qcd_BGenFilter_4[var], bins=infBins, weights = df_hlt2_qcd_BGenFilter_4['evWeight_all']*wqcd_BGenFilter_4)
        h_whlt3_qcd_BGenFilter_4, bins_qcd_BGenFilter_4 = np.histogram(df_hlt3_qcd_BGenFilter_4[var], bins=infBins, weights = df_hlt3_qcd_BGenFilter_4['evWeight_all']*wqcd_BGenFilter_4)
        h_whlt4_qcd_BGenFilter_4, bins_qcd_BGenFilter_4 = np.histogram(df_hlt4_qcd_BGenFilter_4[var], bins=infBins, weights = df_hlt4_qcd_BGenFilter_4['evWeight_all']*wqcd_BGenFilter_4)
        h_whlt5_qcd_BGenFilter_4, bins_qcd_BGenFilter_4 = np.histogram(df_hlt5_qcd_BGenFilter_4[var], bins=infBins, weights = df_hlt5_qcd_BGenFilter_4['evWeight_all']*wqcd_BGenFilter_4)
        h_whlt6_qcd_BGenFilter_4, bins_qcd_BGenFilter_4 = np.histogram(df_hlt6_qcd_BGenFilter_4[var], bins=infBins, weights = df_hlt6_qcd_BGenFilter_4['evWeight_all']*wqcd_BGenFilter_4)
        h_whlt7_qcd_BGenFilter_4, bins_qcd_BGenFilter_4 = np.histogram(df_hlt7_qcd_BGenFilter_4[var], bins=infBins, weights = df_hlt7_qcd_BGenFilter_4['evWeight_all']*wqcd_BGenFilter_4)
        h_whlt8_qcd_BGenFilter_4, bins_qcd_BGenFilter_4 = np.histogram(df_hlt8_qcd_BGenFilter_4[var], bins=infBins, weights = df_hlt8_qcd_BGenFilter_4['evWeight_all']*wqcd_BGenFilter_4)
        h_whltcur_qcd_BGenFilter_4, bins_qcd_BGenFilter_4 = np.histogram(df_hltcur_qcd_BGenFilter_4[var], bins=infBins, weights = df_hltcur_qcd_BGenFilter_4['evWeight_all']*wqcd_BGenFilter_4)
        h_whltall_qcd_BGenFilter_4, bins_qcd_BGenFilter_4 = np.histogram(df_hltall_qcd_BGenFilter_4[var], bins=infBins, weights = df_hltall_qcd_BGenFilter_4['evWeight_all']*wqcd_BGenFilter_4)

        h_nohlt_qcd_BGenFilter_5, bins_qcd_BGenFilter_5 = np.histogram(df_qcd_BGenFilter_5[var], bins=infBins, weights = df_qcd_BGenFilter_5['evWeight_all']*wqcd_BGenFilter_5)
        h_whlt1_qcd_BGenFilter_5, bins_qcd_BGenFilter_5 = np.histogram(df_hlt1_qcd_BGenFilter_5[var], bins=infBins, weights = df_hlt1_qcd_BGenFilter_5['evWeight_all']*wqcd_BGenFilter_5)
        h_whlt2_qcd_BGenFilter_5, bins_qcd_BGenFilter_5 = np.histogram(df_hlt2_qcd_BGenFilter_5[var], bins=infBins, weights = df_hlt2_qcd_BGenFilter_5['evWeight_all']*wqcd_BGenFilter_5)
        h_whlt3_qcd_BGenFilter_5, bins_qcd_BGenFilter_5 = np.histogram(df_hlt3_qcd_BGenFilter_5[var], bins=infBins, weights = df_hlt3_qcd_BGenFilter_5['evWeight_all']*wqcd_BGenFilter_5)
        h_whlt4_qcd_BGenFilter_5, bins_qcd_BGenFilter_5 = np.histogram(df_hlt4_qcd_BGenFilter_5[var], bins=infBins, weights = df_hlt4_qcd_BGenFilter_5['evWeight_all']*wqcd_BGenFilter_5)
        h_whlt5_qcd_BGenFilter_5, bins_qcd_BGenFilter_5 = np.histogram(df_hlt5_qcd_BGenFilter_5[var], bins=infBins, weights = df_hlt5_qcd_BGenFilter_5['evWeight_all']*wqcd_BGenFilter_5)
        h_whlt6_qcd_BGenFilter_5, bins_qcd_BGenFilter_5 = np.histogram(df_hlt6_qcd_BGenFilter_5[var], bins=infBins, weights = df_hlt6_qcd_BGenFilter_5['evWeight_all']*wqcd_BGenFilter_5)
        h_whlt7_qcd_BGenFilter_5, bins_qcd_BGenFilter_5 = np.histogram(df_hlt7_qcd_BGenFilter_5[var], bins=infBins, weights = df_hlt7_qcd_BGenFilter_5['evWeight_all']*wqcd_BGenFilter_5)
        h_whlt8_qcd_BGenFilter_5, bins_qcd_BGenFilter_5 = np.histogram(df_hlt8_qcd_BGenFilter_5[var], bins=infBins, weights = df_hlt8_qcd_BGenFilter_5['evWeight_all']*wqcd_BGenFilter_5)
        h_whltcur_qcd_BGenFilter_5, bins_qcd_BGenFilter_5 = np.histogram(df_hltcur_qcd_BGenFilter_5[var], bins=infBins, weights = df_hltcur_qcd_BGenFilter_5['evWeight_all']*wqcd_BGenFilter_5)
        h_whltall_qcd_BGenFilter_5, bins_qcd_BGenFilter_5 = np.histogram(df_hltall_qcd_BGenFilter_5[var], bins=infBins, weights = df_hltall_qcd_BGenFilter_5['evWeight_all']*wqcd_BGenFilter_5)

        h_nohlt_qcd_BGenFilter_6, bins_qcd_BGenFilter_6 = np.histogram(df_qcd_BGenFilter_6[var], bins=infBins, weights = df_qcd_BGenFilter_6['evWeight_all']*wqcd_BGenFilter_6)
        h_whlt1_qcd_BGenFilter_6, bins_qcd_BGenFilter_6 = np.histogram(df_hlt1_qcd_BGenFilter_6[var], bins=infBins, weights = df_hlt1_qcd_BGenFilter_6['evWeight_all']*wqcd_BGenFilter_6)
        h_whlt2_qcd_BGenFilter_6, bins_qcd_BGenFilter_6 = np.histogram(df_hlt2_qcd_BGenFilter_6[var], bins=infBins, weights = df_hlt2_qcd_BGenFilter_6['evWeight_all']*wqcd_BGenFilter_6)
        h_whlt3_qcd_BGenFilter_6, bins_qcd_BGenFilter_6 = np.histogram(df_hlt3_qcd_BGenFilter_6[var], bins=infBins, weights = df_hlt3_qcd_BGenFilter_6['evWeight_all']*wqcd_BGenFilter_6)
        h_whlt4_qcd_BGenFilter_6, bins_qcd_BGenFilter_6 = np.histogram(df_hlt4_qcd_BGenFilter_6[var], bins=infBins, weights = df_hlt4_qcd_BGenFilter_6['evWeight_all']*wqcd_BGenFilter_6)
        h_whlt5_qcd_BGenFilter_6, bins_qcd_BGenFilter_6 = np.histogram(df_hlt5_qcd_BGenFilter_6[var], bins=infBins, weights = df_hlt5_qcd_BGenFilter_6['evWeight_all']*wqcd_BGenFilter_6)
        h_whlt6_qcd_BGenFilter_6, bins_qcd_BGenFilter_6 = np.histogram(df_hlt6_qcd_BGenFilter_6[var], bins=infBins, weights = df_hlt6_qcd_BGenFilter_6['evWeight_all']*wqcd_BGenFilter_6)
        h_whlt7_qcd_BGenFilter_6, bins_qcd_BGenFilter_6 = np.histogram(df_hlt7_qcd_BGenFilter_6[var], bins=infBins, weights = df_hlt7_qcd_BGenFilter_6['evWeight_all']*wqcd_BGenFilter_6)
        h_whlt8_qcd_BGenFilter_6, bins_qcd_BGenFilter_6 = np.histogram(df_hlt8_qcd_BGenFilter_6[var], bins=infBins, weights = df_hlt8_qcd_BGenFilter_6['evWeight_all']*wqcd_BGenFilter_6)
        h_whltcur_qcd_BGenFilter_6, bins_qcd_BGenFilter_6 = np.histogram(df_hltcur_qcd_BGenFilter_6[var], bins=infBins, weights = df_hltcur_qcd_BGenFilter_6['evWeight_all']*wqcd_BGenFilter_6)
        h_whltall_qcd_BGenFilter_6, bins_qcd_BGenFilter_6 = np.histogram(df_hltall_qcd_BGenFilter_6[var], bins=infBins, weights = df_hltall_qcd_BGenFilter_6['evWeight_all']*wqcd_BGenFilter_6)

        h_nohlt_qcd_bEnriched_1, bins_qcd_bEnriched_1 = np.histogram(df_qcd_bEnriched_1[var], bins=infBins, weights = df_qcd_bEnriched_1['evWeight_all']*wqcd_bEnriched_1)
        h_whlt1_qcd_bEnriched_1, bins_qcd_bEnriched_1 = np.histogram(df_hlt1_qcd_bEnriched_1[var], bins=infBins, weights = df_hlt1_qcd_bEnriched_1['evWeight_all']*wqcd_bEnriched_1)
        h_whlt2_qcd_bEnriched_1, bins_qcd_bEnriched_1 = np.histogram(df_hlt2_qcd_bEnriched_1[var], bins=infBins, weights = df_hlt2_qcd_bEnriched_1['evWeight_all']*wqcd_bEnriched_1)
        h_whlt3_qcd_bEnriched_1, bins_qcd_bEnriched_1 = np.histogram(df_hlt3_qcd_bEnriched_1[var], bins=infBins, weights = df_hlt3_qcd_bEnriched_1['evWeight_all']*wqcd_bEnriched_1)
        h_whlt4_qcd_bEnriched_1, bins_qcd_bEnriched_1 = np.histogram(df_hlt4_qcd_bEnriched_1[var], bins=infBins, weights = df_hlt4_qcd_bEnriched_1['evWeight_all']*wqcd_bEnriched_1)
        h_whlt5_qcd_bEnriched_1, bins_qcd_bEnriched_1 = np.histogram(df_hlt5_qcd_bEnriched_1[var], bins=infBins, weights = df_hlt5_qcd_bEnriched_1['evWeight_all']*wqcd_bEnriched_1)
        h_whlt6_qcd_bEnriched_1, bins_qcd_bEnriched_1 = np.histogram(df_hlt6_qcd_bEnriched_1[var], bins=infBins, weights = df_hlt6_qcd_bEnriched_1['evWeight_all']*wqcd_bEnriched_1)
        h_whlt7_qcd_bEnriched_1, bins_qcd_bEnriched_1 = np.histogram(df_hlt7_qcd_bEnriched_1[var], bins=infBins, weights = df_hlt7_qcd_bEnriched_1['evWeight_all']*wqcd_bEnriched_1)
        h_whlt8_qcd_bEnriched_1, bins_qcd_bEnriched_1 = np.histogram(df_hlt8_qcd_bEnriched_1[var], bins=infBins, weights = df_hlt8_qcd_bEnriched_1['evWeight_all']*wqcd_bEnriched_1)
        h_whltcur_qcd_bEnriched_1, bins_qcd_bEnriched_1 = np.histogram(df_hltcur_qcd_bEnriched_1[var], bins=infBins, weights = df_hltcur_qcd_bEnriched_1['evWeight_all']*wqcd_bEnriched_1)
        h_whltall_qcd_bEnriched_1, bins_qcd_bEnriched_1 = np.histogram(df_hltall_qcd_bEnriched_1[var], bins=infBins, weights = df_hltall_qcd_bEnriched_1['evWeight_all']*wqcd_bEnriched_1)

        h_nohlt_qcd_bEnriched_2, bins_qcd_bEnriched_2 = np.histogram(df_qcd_bEnriched_2[var], bins=infBins, weights = df_qcd_bEnriched_2['evWeight_all']*wqcd_bEnriched_2)
        h_whlt1_qcd_bEnriched_2, bins_qcd_bEnriched_2 = np.histogram(df_hlt1_qcd_bEnriched_2[var], bins=infBins, weights = df_hlt1_qcd_bEnriched_2['evWeight_all']*wqcd_bEnriched_2)
        h_whlt2_qcd_bEnriched_2, bins_qcd_bEnriched_2 = np.histogram(df_hlt2_qcd_bEnriched_2[var], bins=infBins, weights = df_hlt2_qcd_bEnriched_2['evWeight_all']*wqcd_bEnriched_2)
        h_whlt3_qcd_bEnriched_2, bins_qcd_bEnriched_2 = np.histogram(df_hlt3_qcd_bEnriched_2[var], bins=infBins, weights = df_hlt3_qcd_bEnriched_2['evWeight_all']*wqcd_bEnriched_2)
        h_whlt4_qcd_bEnriched_2, bins_qcd_bEnriched_2 = np.histogram(df_hlt4_qcd_bEnriched_2[var], bins=infBins, weights = df_hlt4_qcd_bEnriched_2['evWeight_all']*wqcd_bEnriched_2)
        h_whlt5_qcd_bEnriched_2, bins_qcd_bEnriched_2 = np.histogram(df_hlt5_qcd_bEnriched_2[var], bins=infBins, weights = df_hlt5_qcd_bEnriched_2['evWeight_all']*wqcd_bEnriched_2)
        h_whlt6_qcd_bEnriched_2, bins_qcd_bEnriched_2 = np.histogram(df_hlt6_qcd_bEnriched_2[var], bins=infBins, weights = df_hlt6_qcd_bEnriched_2['evWeight_all']*wqcd_bEnriched_2)
        h_whlt7_qcd_bEnriched_2, bins_qcd_bEnriched_2 = np.histogram(df_hlt7_qcd_bEnriched_2[var], bins=infBins, weights = df_hlt7_qcd_bEnriched_2['evWeight_all']*wqcd_bEnriched_2)
        h_whlt8_qcd_bEnriched_2, bins_qcd_bEnriched_2 = np.histogram(df_hlt8_qcd_bEnriched_2[var], bins=infBins, weights = df_hlt8_qcd_bEnriched_2['evWeight_all']*wqcd_bEnriched_2)
        h_whltcur_qcd_bEnriched_2, bins_qcd_bEnriched_2 = np.histogram(df_hltcur_qcd_bEnriched_2[var], bins=infBins, weights = df_hltcur_qcd_bEnriched_2['evWeight_all']*wqcd_bEnriched_2)
        h_whltall_qcd_bEnriched_2, bins_qcd_bEnriched_2 = np.histogram(df_hltall_qcd_bEnriched_2[var], bins=infBins, weights = df_hltall_qcd_bEnriched_2['evWeight_all']*wqcd_bEnriched_2)

        h_nohlt_qcd_bEnriched_3, bins_qcd_bEnriched_3 = np.histogram(df_qcd_bEnriched_3[var], bins=infBins, weights = df_qcd_bEnriched_3['evWeight_all']*wqcd_bEnriched_3)
        h_whlt1_qcd_bEnriched_3, bins_qcd_bEnriched_3 = np.histogram(df_hlt1_qcd_bEnriched_3[var], bins=infBins, weights = df_hlt1_qcd_bEnriched_3['evWeight_all']*wqcd_bEnriched_3)
        h_whlt2_qcd_bEnriched_3, bins_qcd_bEnriched_3 = np.histogram(df_hlt2_qcd_bEnriched_3[var], bins=infBins, weights = df_hlt2_qcd_bEnriched_3['evWeight_all']*wqcd_bEnriched_3)
        h_whlt3_qcd_bEnriched_3, bins_qcd_bEnriched_3 = np.histogram(df_hlt3_qcd_bEnriched_3[var], bins=infBins, weights = df_hlt3_qcd_bEnriched_3['evWeight_all']*wqcd_bEnriched_3)
        h_whlt4_qcd_bEnriched_3, bins_qcd_bEnriched_3 = np.histogram(df_hlt4_qcd_bEnriched_3[var], bins=infBins, weights = df_hlt4_qcd_bEnriched_3['evWeight_all']*wqcd_bEnriched_3)
        h_whlt5_qcd_bEnriched_3, bins_qcd_bEnriched_3 = np.histogram(df_hlt5_qcd_bEnriched_3[var], bins=infBins, weights = df_hlt5_qcd_bEnriched_3['evWeight_all']*wqcd_bEnriched_3)
        h_whlt6_qcd_bEnriched_3, bins_qcd_bEnriched_3 = np.histogram(df_hlt6_qcd_bEnriched_3[var], bins=infBins, weights = df_hlt6_qcd_bEnriched_3['evWeight_all']*wqcd_bEnriched_3)
        h_whlt7_qcd_bEnriched_3, bins_qcd_bEnriched_3 = np.histogram(df_hlt7_qcd_bEnriched_3[var], bins=infBins, weights = df_hlt7_qcd_bEnriched_3['evWeight_all']*wqcd_bEnriched_3)
        h_whlt8_qcd_bEnriched_3, bins_qcd_bEnriched_3 = np.histogram(df_hlt8_qcd_bEnriched_3[var], bins=infBins, weights = df_hlt8_qcd_bEnriched_3['evWeight_all']*wqcd_bEnriched_3)
        h_whltcur_qcd_bEnriched_3, bins_qcd_bEnriched_3 = np.histogram(df_hltcur_qcd_bEnriched_3[var], bins=infBins, weights = df_hltcur_qcd_bEnriched_3['evWeight_all']*wqcd_bEnriched_3)
        h_whltall_qcd_bEnriched_3, bins_qcd_bEnriched_3 = np.histogram(df_hltall_qcd_bEnriched_3[var], bins=infBins, weights = df_hltall_qcd_bEnriched_3['evWeight_all']*wqcd_bEnriched_3)

        h_nohlt_qcd_bEnriched_4, bins_qcd_bEnriched_4 = np.histogram(df_qcd_bEnriched_4[var], bins=infBins, weights = df_qcd_bEnriched_4['evWeight_all']*wqcd_bEnriched_4)
        h_whlt1_qcd_bEnriched_4, bins_qcd_bEnriched_4 = np.histogram(df_hlt1_qcd_bEnriched_4[var], bins=infBins, weights = df_hlt1_qcd_bEnriched_4['evWeight_all']*wqcd_bEnriched_4)
        h_whlt2_qcd_bEnriched_4, bins_qcd_bEnriched_4 = np.histogram(df_hlt2_qcd_bEnriched_4[var], bins=infBins, weights = df_hlt2_qcd_bEnriched_4['evWeight_all']*wqcd_bEnriched_4)
        h_whlt3_qcd_bEnriched_4, bins_qcd_bEnriched_4 = np.histogram(df_hlt3_qcd_bEnriched_4[var], bins=infBins, weights = df_hlt3_qcd_bEnriched_4['evWeight_all']*wqcd_bEnriched_4)
        h_whlt4_qcd_bEnriched_4, bins_qcd_bEnriched_4 = np.histogram(df_hlt4_qcd_bEnriched_4[var], bins=infBins, weights = df_hlt4_qcd_bEnriched_4['evWeight_all']*wqcd_bEnriched_4)
        h_whlt5_qcd_bEnriched_4, bins_qcd_bEnriched_4 = np.histogram(df_hlt5_qcd_bEnriched_4[var], bins=infBins, weights = df_hlt5_qcd_bEnriched_4['evWeight_all']*wqcd_bEnriched_4)
        h_whlt6_qcd_bEnriched_4, bins_qcd_bEnriched_4 = np.histogram(df_hlt6_qcd_bEnriched_4[var], bins=infBins, weights = df_hlt6_qcd_bEnriched_4['evWeight_all']*wqcd_bEnriched_4)
        h_whlt7_qcd_bEnriched_4, bins_qcd_bEnriched_4 = np.histogram(df_hlt7_qcd_bEnriched_4[var], bins=infBins, weights = df_hlt7_qcd_bEnriched_4['evWeight_all']*wqcd_bEnriched_4)
        h_whlt8_qcd_bEnriched_4, bins_qcd_bEnriched_4 = np.histogram(df_hlt8_qcd_bEnriched_4[var], bins=infBins, weights = df_hlt8_qcd_bEnriched_4['evWeight_all']*wqcd_bEnriched_4)
        h_whltcur_qcd_bEnriched_4, bins_qcd_bEnriched_4 = np.histogram(df_hltcur_qcd_bEnriched_4[var], bins=infBins, weights = df_hltcur_qcd_bEnriched_4['evWeight_all']*wqcd_bEnriched_4)
        h_whltall_qcd_bEnriched_4, bins_qcd_bEnriched_4 = np.histogram(df_hltall_qcd_bEnriched_4[var], bins=infBins, weights = df_hltall_qcd_bEnriched_4['evWeight_all']*wqcd_bEnriched_4)

        h_nohlt_qcd_bEnriched_5, bins_qcd_bEnriched_5 = np.histogram(df_qcd_bEnriched_5[var], bins=infBins, weights = df_qcd_bEnriched_5['evWeight_all']*wqcd_bEnriched_5)
        h_whlt1_qcd_bEnriched_5, bins_qcd_bEnriched_5 = np.histogram(df_hlt1_qcd_bEnriched_5[var], bins=infBins, weights = df_hlt1_qcd_bEnriched_5['evWeight_all']*wqcd_bEnriched_5)
        h_whlt2_qcd_bEnriched_5, bins_qcd_bEnriched_5 = np.histogram(df_hlt2_qcd_bEnriched_5[var], bins=infBins, weights = df_hlt2_qcd_bEnriched_5['evWeight_all']*wqcd_bEnriched_5)
        h_whlt3_qcd_bEnriched_5, bins_qcd_bEnriched_5 = np.histogram(df_hlt3_qcd_bEnriched_5[var], bins=infBins, weights = df_hlt3_qcd_bEnriched_5['evWeight_all']*wqcd_bEnriched_5)
        h_whlt4_qcd_bEnriched_5, bins_qcd_bEnriched_5 = np.histogram(df_hlt4_qcd_bEnriched_5[var], bins=infBins, weights = df_hlt4_qcd_bEnriched_5['evWeight_all']*wqcd_bEnriched_5)
        h_whlt5_qcd_bEnriched_5, bins_qcd_bEnriched_5 = np.histogram(df_hlt5_qcd_bEnriched_5[var], bins=infBins, weights = df_hlt5_qcd_bEnriched_5['evWeight_all']*wqcd_bEnriched_5)
        h_whlt6_qcd_bEnriched_5, bins_qcd_bEnriched_5 = np.histogram(df_hlt6_qcd_bEnriched_5[var], bins=infBins, weights = df_hlt6_qcd_bEnriched_5['evWeight_all']*wqcd_bEnriched_5)
        h_whlt7_qcd_bEnriched_5, bins_qcd_bEnriched_5 = np.histogram(df_hlt7_qcd_bEnriched_5[var], bins=infBins, weights = df_hlt7_qcd_bEnriched_5['evWeight_all']*wqcd_bEnriched_5)
        h_whlt8_qcd_bEnriched_5, bins_qcd_bEnriched_5 = np.histogram(df_hlt8_qcd_bEnriched_5[var], bins=infBins, weights = df_hlt8_qcd_bEnriched_5['evWeight_all']*wqcd_bEnriched_5)
        h_whltcur_qcd_bEnriched_5, bins_qcd_bEnriched_5 = np.histogram(df_hltcur_qcd_bEnriched_5[var], bins=infBins, weights = df_hltcur_qcd_bEnriched_5['evWeight_all']*wqcd_bEnriched_5)
        h_whltall_qcd_bEnriched_5, bins_qcd_bEnriched_5 = np.histogram(df_hltall_qcd_bEnriched_5[var], bins=infBins, weights = df_hltall_qcd_bEnriched_5['evWeight_all']*wqcd_bEnriched_5)

        h_nohlt_qcd_bEnriched_6, bins_qcd_bEnriched_6 = np.histogram(df_qcd_bEnriched_6[var], bins=infBins, weights = df_qcd_bEnriched_6['evWeight_all']*wqcd_bEnriched_6)
        h_whlt1_qcd_bEnriched_6, bins_qcd_bEnriched_6 = np.histogram(df_hlt1_qcd_bEnriched_6[var], bins=infBins, weights = df_hlt1_qcd_bEnriched_6['evWeight_all']*wqcd_bEnriched_6)
        h_whlt2_qcd_bEnriched_6, bins_qcd_bEnriched_6 = np.histogram(df_hlt2_qcd_bEnriched_6[var], bins=infBins, weights = df_hlt2_qcd_bEnriched_6['evWeight_all']*wqcd_bEnriched_6)
        h_whlt3_qcd_bEnriched_6, bins_qcd_bEnriched_6 = np.histogram(df_hlt3_qcd_bEnriched_6[var], bins=infBins, weights = df_hlt3_qcd_bEnriched_6['evWeight_all']*wqcd_bEnriched_6)
        h_whlt4_qcd_bEnriched_6, bins_qcd_bEnriched_6 = np.histogram(df_hlt4_qcd_bEnriched_6[var], bins=infBins, weights = df_hlt4_qcd_bEnriched_6['evWeight_all']*wqcd_bEnriched_6)
        h_whlt5_qcd_bEnriched_6, bins_qcd_bEnriched_6 = np.histogram(df_hlt5_qcd_bEnriched_6[var], bins=infBins, weights = df_hlt5_qcd_bEnriched_6['evWeight_all']*wqcd_bEnriched_6)
        h_whlt6_qcd_bEnriched_6, bins_qcd_bEnriched_6 = np.histogram(df_hlt6_qcd_bEnriched_6[var], bins=infBins, weights = df_hlt6_qcd_bEnriched_6['evWeight_all']*wqcd_bEnriched_6)
        h_whlt7_qcd_bEnriched_6, bins_qcd_bEnriched_6 = np.histogram(df_hlt7_qcd_bEnriched_6[var], bins=infBins, weights = df_hlt7_qcd_bEnriched_6['evWeight_all']*wqcd_bEnriched_6)
        h_whlt8_qcd_bEnriched_6, bins_qcd_bEnriched_6 = np.histogram(df_hlt8_qcd_bEnriched_6[var], bins=infBins, weights = df_hlt8_qcd_bEnriched_6['evWeight_all']*wqcd_bEnriched_6)
        h_whltcur_qcd_bEnriched_6, bins_qcd_bEnriched_6 = np.histogram(df_hltcur_qcd_bEnriched_6[var], bins=infBins, weights = df_hltcur_qcd_bEnriched_6['evWeight_all']*wqcd_bEnriched_6)
        h_whltall_qcd_bEnriched_6, bins_qcd_bEnriched_6 = np.histogram(df_hltall_qcd_bEnriched_6[var], bins=infBins, weights = df_hltall_qcd_bEnriched_6['evWeight_all']*wqcd_bEnriched_6)

        h_nohlt_st_s, bins_st_s = np.histogram(df_st_s[var], bins=infBins, weights = df_st_s['evWeight_all']*wst_s)
        h_whlt1_st_s, bins_st_s = np.histogram(df_hlt1_st_s[var], bins=infBins, weights = df_hlt1_st_s['evWeight_all']*wst_s)
        h_whlt2_st_s, bins_st_s = np.histogram(df_hlt2_st_s[var], bins=infBins, weights = df_hlt2_st_s['evWeight_all']*wst_s)
        h_whlt3_st_s, bins_st_s = np.histogram(df_hlt3_st_s[var], bins=infBins, weights = df_hlt3_st_s['evWeight_all']*wst_s)
        h_whlt4_st_s, bins_st_s = np.histogram(df_hlt4_st_s[var], bins=infBins, weights = df_hlt4_st_s['evWeight_all']*wst_s)
        h_whlt5_st_s, bins_st_s = np.histogram(df_hlt5_st_s[var], bins=infBins, weights = df_hlt5_st_s['evWeight_all']*wst_s)
        h_whlt6_st_s, bins_st_s = np.histogram(df_hlt6_st_s[var], bins=infBins, weights = df_hlt6_st_s['evWeight_all']*wst_s)
        h_whlt7_st_s, bins_st_s = np.histogram(df_hlt7_st_s[var], bins=infBins, weights = df_hlt7_st_s['evWeight_all']*wst_s)
        h_whlt8_st_s, bins_st_s = np.histogram(df_hlt8_st_s[var], bins=infBins, weights = df_hlt8_st_s['evWeight_all']*wst_s)
        h_whltcur_st_s, bins_st_s = np.histogram(df_hltcur_st_s[var], bins=infBins, weights = df_hltcur_st_s['evWeight_all']*wst_s)
        h_whltall_st_s, bins_st_s = np.histogram(df_hltall_st_s[var], bins=infBins, weights = df_hltall_st_s['evWeight_all']*wst_s)

        h_nohlt_st_t, bins_st_t = np.histogram(df_st_t[var], bins=infBins, weights = df_st_t['evWeight_all']*wst_t)
        h_whlt1_st_t, bins_st_t = np.histogram(df_hlt1_st_t[var], bins=infBins, weights = df_hlt1_st_t['evWeight_all']*wst_t)
        h_whlt2_st_t, bins_st_t = np.histogram(df_hlt2_st_t[var], bins=infBins, weights = df_hlt2_st_t['evWeight_all']*wst_t)
        h_whlt3_st_t, bins_st_t = np.histogram(df_hlt3_st_t[var], bins=infBins, weights = df_hlt3_st_t['evWeight_all']*wst_t)
        h_whlt4_st_t, bins_st_t = np.histogram(df_hlt4_st_t[var], bins=infBins, weights = df_hlt4_st_t['evWeight_all']*wst_t)
        h_whlt5_st_t, bins_st_t = np.histogram(df_hlt5_st_t[var], bins=infBins, weights = df_hlt5_st_t['evWeight_all']*wst_t)
        h_whlt6_st_t, bins_st_t = np.histogram(df_hlt6_st_t[var], bins=infBins, weights = df_hlt6_st_t['evWeight_all']*wst_t)
        h_whlt7_st_t, bins_st_t = np.histogram(df_hlt7_st_t[var], bins=infBins, weights = df_hlt7_st_t['evWeight_all']*wst_t)
        h_whlt8_st_t, bins_st_t = np.histogram(df_hlt8_st_t[var], bins=infBins, weights = df_hlt8_st_t['evWeight_all']*wst_t)
        h_whltcur_st_t, bins_st_t = np.histogram(df_hltcur_st_t[var], bins=infBins, weights = df_hltcur_st_t['evWeight_all']*wst_t)
        h_whltall_st_t, bins_st_t = np.histogram(df_hltall_st_t[var], bins=infBins, weights = df_hltall_st_t['evWeight_all']*wst_t)

        h_nohlt_st_ant, bins_st_ant = np.histogram(df_st_ant[var], bins=infBins, weights = df_st_ant['evWeight_all']*wst_ant)
        h_whlt1_st_ant, bins_st_ant = np.histogram(df_hlt1_st_ant[var], bins=infBins, weights = df_hlt1_st_ant['evWeight_all']*wst_ant)
        h_whlt2_st_ant, bins_st_ant = np.histogram(df_hlt2_st_ant[var], bins=infBins, weights = df_hlt2_st_ant['evWeight_all']*wst_ant)
        h_whlt3_st_ant, bins_st_ant = np.histogram(df_hlt3_st_ant[var], bins=infBins, weights = df_hlt3_st_ant['evWeight_all']*wst_ant)
        h_whlt4_st_ant, bins_st_ant = np.histogram(df_hlt4_st_ant[var], bins=infBins, weights = df_hlt4_st_ant['evWeight_all']*wst_ant)
        h_whlt5_st_ant, bins_st_ant = np.histogram(df_hlt5_st_ant[var], bins=infBins, weights = df_hlt5_st_ant['evWeight_all']*wst_ant)
        h_whlt6_st_ant, bins_st_ant = np.histogram(df_hlt6_st_ant[var], bins=infBins, weights = df_hlt6_st_ant['evWeight_all']*wst_ant)
        h_whlt7_st_ant, bins_st_ant = np.histogram(df_hlt7_st_ant[var], bins=infBins, weights = df_hlt7_st_ant['evWeight_all']*wst_ant)
        h_whlt8_st_ant, bins_st_ant = np.histogram(df_hlt8_st_ant[var], bins=infBins, weights = df_hlt8_st_ant['evWeight_all']*wst_ant)
        h_whltcur_st_ant, bins_st_ant = np.histogram(df_hltcur_st_ant[var], bins=infBins, weights = df_hltcur_st_ant['evWeight_all']*wst_ant)
        h_whltall_st_ant, bins_st_ant = np.histogram(df_hltall_st_ant[var], bins=infBins, weights = df_hltall_st_ant['evWeight_all']*wst_ant)

        h_nohlt_st_tW, bins_st_tW = np.histogram(df_st_tW[var], bins=infBins, weights = df_st_tW['evWeight_all']*wst_tW)
        h_whlt1_st_tW, bins_st_tW = np.histogram(df_hlt1_st_tW[var], bins=infBins, weights = df_hlt1_st_tW['evWeight_all']*wst_tW)
        h_whlt2_st_tW, bins_st_tW = np.histogram(df_hlt2_st_tW[var], bins=infBins, weights = df_hlt2_st_tW['evWeight_all']*wst_tW)
        h_whlt3_st_tW, bins_st_tW = np.histogram(df_hlt3_st_tW[var], bins=infBins, weights = df_hlt3_st_tW['evWeight_all']*wst_tW)
        h_whlt4_st_tW, bins_st_tW = np.histogram(df_hlt4_st_tW[var], bins=infBins, weights = df_hlt4_st_tW['evWeight_all']*wst_tW)
        h_whlt5_st_tW, bins_st_tW = np.histogram(df_hlt5_st_tW[var], bins=infBins, weights = df_hlt5_st_tW['evWeight_all']*wst_tW)
        h_whlt6_st_tW, bins_st_tW = np.histogram(df_hlt6_st_tW[var], bins=infBins, weights = df_hlt6_st_tW['evWeight_all']*wst_tW)
        h_whlt7_st_tW, bins_st_tW = np.histogram(df_hlt7_st_tW[var], bins=infBins, weights = df_hlt7_st_tW['evWeight_all']*wst_tW)
        h_whlt8_st_tW, bins_st_tW = np.histogram(df_hlt8_st_tW[var], bins=infBins, weights = df_hlt8_st_tW['evWeight_all']*wst_tW)
        h_whltcur_st_tW, bins_st_tW = np.histogram(df_hltcur_st_tW[var], bins=infBins, weights = df_hltcur_st_tW['evWeight_all']*wst_tW)
        h_whltall_st_tW, bins_st_tW = np.histogram(df_hltall_st_tW[var], bins=infBins, weights = df_hltall_st_tW['evWeight_all']*wst_tW)

        h_nohlt_st_antW, bins_st_antW = np.histogram(df_st_antW[var], bins=infBins, weights = df_st_antW['evWeight_all']*wst_antW)
        h_whlt1_st_antW, bins_st_antW = np.histogram(df_hlt1_st_antW[var], bins=infBins, weights = df_hlt1_st_antW['evWeight_all']*wst_antW)
        h_whlt2_st_antW, bins_st_antW = np.histogram(df_hlt2_st_antW[var], bins=infBins, weights = df_hlt2_st_antW['evWeight_all']*wst_antW)
        h_whlt3_st_antW, bins_st_antW = np.histogram(df_hlt3_st_antW[var], bins=infBins, weights = df_hlt3_st_antW['evWeight_all']*wst_antW)
        h_whlt4_st_antW, bins_st_antW = np.histogram(df_hlt4_st_antW[var], bins=infBins, weights = df_hlt4_st_antW['evWeight_all']*wst_antW)
        h_whlt5_st_antW, bins_st_antW = np.histogram(df_hlt5_st_antW[var], bins=infBins, weights = df_hlt5_st_antW['evWeight_all']*wst_antW)
        h_whlt6_st_antW, bins_st_antW = np.histogram(df_hlt6_st_antW[var], bins=infBins, weights = df_hlt6_st_antW['evWeight_all']*wst_antW)
        h_whlt7_st_antW, bins_st_antW = np.histogram(df_hlt7_st_antW[var], bins=infBins, weights = df_hlt7_st_antW['evWeight_all']*wst_antW)
        h_whlt8_st_antW, bins_st_antW = np.histogram(df_hlt8_st_antW[var], bins=infBins, weights = df_hlt8_st_antW['evWeight_all']*wst_antW)
        h_whltcur_st_antW, bins_st_antW = np.histogram(df_hltcur_st_antW[var], bins=infBins, weights = df_hltcur_st_antW['evWeight_all']*wst_antW)
        h_whltall_st_antW, bins_st_antW = np.histogram(df_hltall_st_antW[var], bins=infBins, weights = df_hltall_st_antW['evWeight_all']*wst_antW)

        h_nohlt_wjets_1, bins_wjets_1 = np.histogram(df_wjets_1[var], bins=infBins, weights = df_wjets_1['evWeight_all']*wwjets_1)
        h_whlt1_wjets_1, bins_wjets_1 = np.histogram(df_hlt1_wjets_1[var], bins=infBins, weights = df_hlt1_wjets_1['evWeight_all']*wwjets_1)
        h_whlt2_wjets_1, bins_wjets_1 = np.histogram(df_hlt2_wjets_1[var], bins=infBins, weights = df_hlt2_wjets_1['evWeight_all']*wwjets_1)
        h_whlt3_wjets_1, bins_wjets_1 = np.histogram(df_hlt3_wjets_1[var], bins=infBins, weights = df_hlt3_wjets_1['evWeight_all']*wwjets_1)
        h_whlt4_wjets_1, bins_wjets_1 = np.histogram(df_hlt4_wjets_1[var], bins=infBins, weights = df_hlt4_wjets_1['evWeight_all']*wwjets_1)
        h_whlt5_wjets_1, bins_wjets_1 = np.histogram(df_hlt5_wjets_1[var], bins=infBins, weights = df_hlt5_wjets_1['evWeight_all']*wwjets_1)
        h_whlt6_wjets_1, bins_wjets_1 = np.histogram(df_hlt6_wjets_1[var], bins=infBins, weights = df_hlt6_wjets_1['evWeight_all']*wwjets_1)
        h_whlt7_wjets_1, bins_wjets_1 = np.histogram(df_hlt7_wjets_1[var], bins=infBins, weights = df_hlt7_wjets_1['evWeight_all']*wwjets_1)
        h_whlt8_wjets_1, bins_wjets_1 = np.histogram(df_hlt8_wjets_1[var], bins=infBins, weights = df_hlt8_wjets_1['evWeight_all']*wwjets_1)
        h_whltcur_wjets_1, bins_wjets_1 = np.histogram(df_hltcur_wjets_1[var], bins=infBins, weights = df_hltcur_wjets_1['evWeight_all']*wwjets_1)
        h_whltall_wjets_1, bins_wjets_1 = np.histogram(df_hltall_wjets_1[var], bins=infBins, weights = df_hltall_wjets_1['evWeight_all']*wwjets_1)

        h_nohlt_wjets_2, bins_wjets_2 = np.histogram(df_wjets_2[var], bins=infBins, weights = df_wjets_2['evWeight_all']*wwjets_2)
        h_whlt1_wjets_2, bins_wjets_2 = np.histogram(df_hlt1_wjets_2[var], bins=infBins, weights = df_hlt1_wjets_2['evWeight_all']*wwjets_2)
        h_whlt2_wjets_2, bins_wjets_2 = np.histogram(df_hlt2_wjets_2[var], bins=infBins, weights = df_hlt2_wjets_2['evWeight_all']*wwjets_2)
        h_whlt3_wjets_2, bins_wjets_2 = np.histogram(df_hlt3_wjets_2[var], bins=infBins, weights = df_hlt3_wjets_2['evWeight_all']*wwjets_2)
        h_whlt4_wjets_2, bins_wjets_2 = np.histogram(df_hlt4_wjets_2[var], bins=infBins, weights = df_hlt4_wjets_2['evWeight_all']*wwjets_2)
        h_whlt5_wjets_2, bins_wjets_2 = np.histogram(df_hlt5_wjets_2[var], bins=infBins, weights = df_hlt5_wjets_2['evWeight_all']*wwjets_2)
        h_whlt6_wjets_2, bins_wjets_2 = np.histogram(df_hlt6_wjets_2[var], bins=infBins, weights = df_hlt6_wjets_2['evWeight_all']*wwjets_2)
        h_whlt7_wjets_2, bins_wjets_2 = np.histogram(df_hlt7_wjets_2[var], bins=infBins, weights = df_hlt7_wjets_2['evWeight_all']*wwjets_2)
        h_whlt8_wjets_2, bins_wjets_2 = np.histogram(df_hlt8_wjets_2[var], bins=infBins, weights = df_hlt8_wjets_2['evWeight_all']*wwjets_2)
        h_whltcur_wjets_2, bins_wjets_2 = np.histogram(df_hltcur_wjets_2[var], bins=infBins, weights = df_hltcur_wjets_2['evWeight_all']*wwjets_2)
        h_whltall_wjets_2, bins_wjets_2 = np.histogram(df_hltall_wjets_2[var], bins=infBins, weights = df_hltall_wjets_2['evWeight_all']*wwjets_2)

        h_nohlt_wjets_3, bins_wjets_3 = np.histogram(df_wjets_3[var], bins=infBins, weights = df_wjets_3['evWeight_all']*wwjets_3)
        h_whlt1_wjets_3, bins_wjets_3 = np.histogram(df_hlt1_wjets_3[var], bins=infBins, weights = df_hlt1_wjets_3['evWeight_all']*wwjets_3)
        h_whlt2_wjets_3, bins_wjets_3 = np.histogram(df_hlt2_wjets_3[var], bins=infBins, weights = df_hlt2_wjets_3['evWeight_all']*wwjets_3)
        h_whlt3_wjets_3, bins_wjets_3 = np.histogram(df_hlt3_wjets_3[var], bins=infBins, weights = df_hlt3_wjets_3['evWeight_all']*wwjets_3)
        h_whlt4_wjets_3, bins_wjets_3 = np.histogram(df_hlt4_wjets_3[var], bins=infBins, weights = df_hlt4_wjets_3['evWeight_all']*wwjets_3)
        h_whlt5_wjets_3, bins_wjets_3 = np.histogram(df_hlt5_wjets_3[var], bins=infBins, weights = df_hlt5_wjets_3['evWeight_all']*wwjets_3)
        h_whlt6_wjets_3, bins_wjets_3 = np.histogram(df_hlt6_wjets_3[var], bins=infBins, weights = df_hlt6_wjets_3['evWeight_all']*wwjets_3)
        h_whlt7_wjets_3, bins_wjets_3 = np.histogram(df_hlt7_wjets_3[var], bins=infBins, weights = df_hlt7_wjets_3['evWeight_all']*wwjets_3)
        h_whlt8_wjets_3, bins_wjets_3 = np.histogram(df_hlt8_wjets_3[var], bins=infBins, weights = df_hlt8_wjets_3['evWeight_all']*wwjets_3)
        h_whltcur_wjets_3, bins_wjets_3 = np.histogram(df_hltcur_wjets_3[var], bins=infBins, weights = df_hltcur_wjets_3['evWeight_all']*wwjets_3)
        h_whltall_wjets_3, bins_wjets_3 = np.histogram(df_hltall_wjets_3[var], bins=infBins, weights = df_hltall_wjets_3['evWeight_all']*wwjets_3)

        h_nohlt_zjets_1, bins_zjets_1 = np.histogram(df_zjets_1[var], bins=infBins, weights = df_zjets_1['evWeight_all']*wzjets_1)
        h_whlt1_zjets_1, bins_zjets_1 = np.histogram(df_hlt1_zjets_1[var], bins=infBins, weights = df_hlt1_zjets_1['evWeight_all']*wzjets_1)
        h_whlt2_zjets_1, bins_zjets_1 = np.histogram(df_hlt2_zjets_1[var], bins=infBins, weights = df_hlt2_zjets_1['evWeight_all']*wzjets_1)
        h_whlt3_zjets_1, bins_zjets_1 = np.histogram(df_hlt3_zjets_1[var], bins=infBins, weights = df_hlt3_zjets_1['evWeight_all']*wzjets_1)
        h_whlt4_zjets_1, bins_zjets_1 = np.histogram(df_hlt4_zjets_1[var], bins=infBins, weights = df_hlt4_zjets_1['evWeight_all']*wzjets_1)
        h_whlt5_zjets_1, bins_zjets_1 = np.histogram(df_hlt5_zjets_1[var], bins=infBins, weights = df_hlt5_zjets_1['evWeight_all']*wzjets_1)
        h_whlt6_zjets_1, bins_zjets_1 = np.histogram(df_hlt6_zjets_1[var], bins=infBins, weights = df_hlt6_zjets_1['evWeight_all']*wzjets_1)
        h_whlt7_zjets_1, bins_zjets_1 = np.histogram(df_hlt7_zjets_1[var], bins=infBins, weights = df_hlt7_zjets_1['evWeight_all']*wzjets_1)
        h_whlt8_zjets_1, bins_zjets_1 = np.histogram(df_hlt8_zjets_1[var], bins=infBins, weights = df_hlt8_zjets_1['evWeight_all']*wzjets_1)
        h_whltcur_zjets_1, bins_zjets_1 = np.histogram(df_hltcur_zjets_1[var], bins=infBins, weights = df_hltcur_zjets_1['evWeight_all']*wzjets_1)
        h_whltall_zjets_1, bins_zjets_1 = np.histogram(df_hltall_zjets_1[var], bins=infBins, weights = df_hltall_zjets_1['evWeight_all']*wzjets_1)

        h_nohlt_zjets_2, bins_zjets_2 = np.histogram(df_zjets_2[var], bins=infBins, weights = df_zjets_2['evWeight_all']*wzjets_2)
        h_whlt1_zjets_2, bins_zjets_2 = np.histogram(df_hlt1_zjets_2[var], bins=infBins, weights = df_hlt1_zjets_2['evWeight_all']*wzjets_2)
        h_whlt2_zjets_2, bins_zjets_2 = np.histogram(df_hlt2_zjets_2[var], bins=infBins, weights = df_hlt2_zjets_2['evWeight_all']*wzjets_2)
        h_whlt3_zjets_2, bins_zjets_2 = np.histogram(df_hlt3_zjets_2[var], bins=infBins, weights = df_hlt3_zjets_2['evWeight_all']*wzjets_2)
        h_whlt4_zjets_2, bins_zjets_2 = np.histogram(df_hlt4_zjets_2[var], bins=infBins, weights = df_hlt4_zjets_2['evWeight_all']*wzjets_2)
        h_whlt5_zjets_2, bins_zjets_2 = np.histogram(df_hlt5_zjets_2[var], bins=infBins, weights = df_hlt5_zjets_2['evWeight_all']*wzjets_2)
        h_whlt6_zjets_2, bins_zjets_2 = np.histogram(df_hlt6_zjets_2[var], bins=infBins, weights = df_hlt6_zjets_2['evWeight_all']*wzjets_2)
        h_whlt7_zjets_2, bins_zjets_2 = np.histogram(df_hlt7_zjets_2[var], bins=infBins, weights = df_hlt7_zjets_2['evWeight_all']*wzjets_2)
        h_whlt8_zjets_2, bins_zjets_2 = np.histogram(df_hlt8_zjets_2[var], bins=infBins, weights = df_hlt8_zjets_2['evWeight_all']*wzjets_2)
        h_whltcur_zjets_2, bins_zjets_2 = np.histogram(df_hltcur_zjets_2[var], bins=infBins, weights = df_hltcur_zjets_2['evWeight_all']*wzjets_2)
        h_whltall_zjets_2, bins_zjets_2 = np.histogram(df_hltall_zjets_2[var], bins=infBins, weights = df_hltall_zjets_2['evWeight_all']*wzjets_2)

        h_nohlt_zjets_3, bins_zjets_3 = np.histogram(df_zjets_3[var], bins=infBins, weights = df_zjets_3['evWeight_all']*wzjets_3)
        h_whlt1_zjets_3, bins_zjets_3 = np.histogram(df_hlt1_zjets_3[var], bins=infBins, weights = df_hlt1_zjets_3['evWeight_all']*wzjets_3)
        h_whlt2_zjets_3, bins_zjets_3 = np.histogram(df_hlt2_zjets_3[var], bins=infBins, weights = df_hlt2_zjets_3['evWeight_all']*wzjets_3)
        h_whlt3_zjets_3, bins_zjets_3 = np.histogram(df_hlt3_zjets_3[var], bins=infBins, weights = df_hlt3_zjets_3['evWeight_all']*wzjets_3)
        h_whlt4_zjets_3, bins_zjets_3 = np.histogram(df_hlt4_zjets_3[var], bins=infBins, weights = df_hlt4_zjets_3['evWeight_all']*wzjets_3)
        h_whlt5_zjets_3, bins_zjets_3 = np.histogram(df_hlt5_zjets_3[var], bins=infBins, weights = df_hlt5_zjets_3['evWeight_all']*wzjets_3)
        h_whlt6_zjets_3, bins_zjets_3 = np.histogram(df_hlt6_zjets_3[var], bins=infBins, weights = df_hlt6_zjets_3['evWeight_all']*wzjets_3)
        h_whlt7_zjets_3, bins_zjets_3 = np.histogram(df_hlt7_zjets_3[var], bins=infBins, weights = df_hlt7_zjets_3['evWeight_all']*wzjets_3)
        h_whlt8_zjets_3, bins_zjets_3 = np.histogram(df_hlt8_zjets_3[var], bins=infBins, weights = df_hlt8_zjets_3['evWeight_all']*wzjets_3)
        h_whltcur_zjets_3, bins_zjets_3 = np.histogram(df_hltcur_zjets_3[var], bins=infBins, weights = df_hltcur_zjets_3['evWeight_all']*wzjets_3)
        h_whltall_zjets_3, bins_zjets_3 = np.histogram(df_hltall_zjets_3[var], bins=infBins, weights = df_hltall_zjets_3['evWeight_all']*wzjets_3)

        h_nohlt_tth, bins_tth = np.histogram(df_tth[var], bins=infBins, weights = df_tth['evWeight_all']*wtth)
        h_whlt1_tth, bins_tth = np.histogram(df_hlt1_tth[var], bins=infBins, weights = df_hlt1_tth['evWeight_all']*wtth)
        h_whlt2_tth, bins_tth = np.histogram(df_hlt2_tth[var], bins=infBins, weights = df_hlt2_tth['evWeight_all']*wtth)
        h_whlt3_tth, bins_tth = np.histogram(df_hlt3_tth[var], bins=infBins, weights = df_hlt3_tth['evWeight_all']*wtth)
        h_whlt4_tth, bins_tth = np.histogram(df_hlt4_tth[var], bins=infBins, weights = df_hlt4_tth['evWeight_all']*wtth)
        h_whlt5_tth, bins_tth = np.histogram(df_hlt5_tth[var], bins=infBins, weights = df_hlt5_tth['evWeight_all']*wtth)
        h_whlt6_tth, bins_tth = np.histogram(df_hlt6_tth[var], bins=infBins, weights = df_hlt6_tth['evWeight_all']*wtth)
        h_whlt7_tth, bins_tth = np.histogram(df_hlt7_tth[var], bins=infBins, weights = df_hlt7_tth['evWeight_all']*wtth)
        h_whlt8_tth, bins_tth = np.histogram(df_hlt8_tth[var], bins=infBins, weights = df_hlt8_tth['evWeight_all']*wtth)
        h_whltcur_tth, bins_tth = np.histogram(df_hltcur_tth[var], bins=infBins, weights = df_hltcur_tth['evWeight_all']*wtth)
        h_whltall_tth, bins_tth = np.histogram(df_hltall_tth[var], bins=infBins, weights = df_hltall_tth['evWeight_all']*wtth)

    
        h_nohlt = h_nohlt_tt + h_nohlt_qcd_BGenFilter_1 + h_nohlt_qcd_BGenFilter_2 + h_nohlt_qcd_BGenFilter_3 + h_nohlt_qcd_BGenFilter_4 + h_nohlt_qcd_BGenFilter_5 + h_nohlt_qcd_BGenFilter_6+ h_nohlt_qcd_bEnriched_1 + h_nohlt_qcd_bEnriched_2 + h_nohlt_qcd_bEnriched_3 + h_nohlt_qcd_bEnriched_4 + h_nohlt_qcd_bEnriched_5 + h_nohlt_qcd_bEnriched_6 + h_nohlt_st_s + h_nohlt_st_t + h_nohlt_st_ant + h_nohlt_st_tW + h_nohlt_st_antW + h_nohlt_wjets_1 + h_nohlt_wjets_2 + h_nohlt_wjets_3 + h_nohlt_zjets_1 + h_nohlt_zjets_2 + h_nohlt_zjets_3 + h_nohlt_tth
        h_whlt1 = h_whlt1_tt + h_whlt1_qcd_BGenFilter_1 + h_whlt1_qcd_BGenFilter_2 + h_whlt1_qcd_BGenFilter_3 + h_whlt1_qcd_BGenFilter_4 + h_whlt1_qcd_BGenFilter_5 + h_whlt1_qcd_BGenFilter_6+ h_whlt1_qcd_bEnriched_1 + h_whlt1_qcd_bEnriched_2 + h_whlt1_qcd_bEnriched_3 + h_whlt1_qcd_bEnriched_4 + h_whlt1_qcd_bEnriched_5 + h_whlt1_qcd_bEnriched_6 + h_whlt1_st_s + h_whlt1_st_t + h_whlt1_st_ant + h_whlt1_st_tW + h_whlt1_st_antW + h_whlt1_wjets_1 + h_whlt1_wjets_2 + h_whlt1_wjets_3 + h_whlt1_zjets_1 + h_whlt1_zjets_2 + h_whlt1_zjets_3 + h_whlt1_tth
        h_whlt2 = h_whlt2_tt + h_whlt2_qcd_BGenFilter_1 + h_whlt2_qcd_BGenFilter_2 + h_whlt2_qcd_BGenFilter_3 + h_whlt2_qcd_BGenFilter_4 + h_whlt2_qcd_BGenFilter_5 + h_whlt2_qcd_BGenFilter_6+ h_whlt2_qcd_bEnriched_1 + h_whlt2_qcd_bEnriched_2 + h_whlt2_qcd_bEnriched_3 + h_whlt2_qcd_bEnriched_4 + h_whlt2_qcd_bEnriched_5 + h_whlt2_qcd_bEnriched_6 + h_whlt2_st_s + h_whlt2_st_t + h_whlt2_st_ant + h_whlt2_st_tW + h_whlt2_st_antW + h_whlt2_wjets_1 + h_whlt2_wjets_2 + h_whlt2_wjets_3 + h_whlt2_zjets_1 + h_whlt2_zjets_2 + h_whlt2_zjets_3 + h_whlt2_tth
        h_whlt3 = h_whlt3_tt + h_whlt3_qcd_BGenFilter_1 + h_whlt3_qcd_BGenFilter_2 + h_whlt3_qcd_BGenFilter_3 + h_whlt3_qcd_BGenFilter_4 + h_whlt3_qcd_BGenFilter_5 + h_whlt3_qcd_BGenFilter_6+ h_whlt3_qcd_bEnriched_1 + h_whlt3_qcd_bEnriched_2 + h_whlt3_qcd_bEnriched_3 + h_whlt3_qcd_bEnriched_4 + h_whlt3_qcd_bEnriched_5 + h_whlt3_qcd_bEnriched_6 + h_whlt3_st_s + h_whlt3_st_t + h_whlt3_st_ant + h_whlt3_st_tW + h_whlt3_st_antW + h_whlt3_wjets_1 + h_whlt3_wjets_2 + h_whlt3_wjets_3 + h_whlt3_zjets_1 + h_whlt3_zjets_2 + h_whlt3_zjets_3 + h_whlt3_tth
        h_whlt4 = h_whlt4_tt + h_whlt4_qcd_BGenFilter_1 + h_whlt4_qcd_BGenFilter_2 + h_whlt4_qcd_BGenFilter_3 + h_whlt4_qcd_BGenFilter_4 + h_whlt4_qcd_BGenFilter_5 + h_whlt4_qcd_BGenFilter_6+ h_whlt4_qcd_bEnriched_1 + h_whlt4_qcd_bEnriched_2 + h_whlt4_qcd_bEnriched_3 + h_whlt4_qcd_bEnriched_4 + h_whlt4_qcd_bEnriched_5 + h_whlt4_qcd_bEnriched_6 + h_whlt4_st_s + h_whlt4_st_t + h_whlt4_st_ant + h_whlt4_st_tW + h_whlt4_st_antW + h_whlt4_wjets_1 + h_whlt4_wjets_2 + h_whlt4_wjets_3 + h_whlt4_zjets_1 + h_whlt4_zjets_2 + h_whlt4_zjets_3 + h_whlt4_tth
        h_whlt5 = h_whlt5_tt + h_whlt5_qcd_BGenFilter_1 + h_whlt5_qcd_BGenFilter_2 + h_whlt5_qcd_BGenFilter_3 + h_whlt5_qcd_BGenFilter_4 + h_whlt5_qcd_BGenFilter_5 + h_whlt5_qcd_BGenFilter_6+ h_whlt5_qcd_bEnriched_1 + h_whlt5_qcd_bEnriched_2 + h_whlt5_qcd_bEnriched_3 + h_whlt5_qcd_bEnriched_4 + h_whlt5_qcd_bEnriched_5 + h_whlt5_qcd_bEnriched_6 + h_whlt5_st_s + h_whlt5_st_t + h_whlt5_st_ant + h_whlt5_st_tW + h_whlt5_st_antW + h_whlt5_wjets_1 + h_whlt5_wjets_2 + h_whlt5_wjets_3 + h_whlt5_zjets_1 + h_whlt5_zjets_2 + h_whlt5_zjets_3 + h_whlt5_tth
        h_whlt6 = h_whlt6_tt + h_whlt6_qcd_BGenFilter_1 + h_whlt6_qcd_BGenFilter_2 + h_whlt6_qcd_BGenFilter_3 + h_whlt6_qcd_BGenFilter_4 + h_whlt6_qcd_BGenFilter_5 + h_whlt6_qcd_BGenFilter_6+ h_whlt6_qcd_bEnriched_1 + h_whlt6_qcd_bEnriched_2 + h_whlt6_qcd_bEnriched_3 + h_whlt6_qcd_bEnriched_4 + h_whlt6_qcd_bEnriched_5 + h_whlt6_qcd_bEnriched_6 + h_whlt6_st_s + h_whlt6_st_t + h_whlt6_st_ant + h_whlt6_st_tW + h_whlt6_st_antW + h_whlt6_wjets_1 + h_whlt6_wjets_2 + h_whlt6_wjets_3 + h_whlt6_zjets_1 + h_whlt6_zjets_2 + h_whlt6_zjets_3 + h_whlt6_tth
        h_whlt7 = h_whlt7_tt + h_whlt7_qcd_BGenFilter_1 + h_whlt7_qcd_BGenFilter_2 + h_whlt7_qcd_BGenFilter_3 + h_whlt7_qcd_BGenFilter_4 + h_whlt7_qcd_BGenFilter_5 + h_whlt7_qcd_BGenFilter_6+ h_whlt7_qcd_bEnriched_1 + h_whlt7_qcd_bEnriched_2 + h_whlt7_qcd_bEnriched_3 + h_whlt7_qcd_bEnriched_4 + h_whlt7_qcd_bEnriched_5 + h_whlt7_qcd_bEnriched_6 + h_whlt7_st_s + h_whlt7_st_t + h_whlt7_st_ant + h_whlt7_st_tW + h_whlt7_st_antW + h_whlt7_wjets_1 + h_whlt7_wjets_2 + h_whlt7_wjets_3 + h_whlt7_zjets_1 + h_whlt7_zjets_2 + h_whlt7_zjets_3 + h_whlt7_tth
        h_whlt8 = h_whlt8_tt + h_whlt8_qcd_BGenFilter_1 + h_whlt8_qcd_BGenFilter_2 + h_whlt8_qcd_BGenFilter_3 + h_whlt8_qcd_BGenFilter_4 + h_whlt8_qcd_BGenFilter_5 + h_whlt8_qcd_BGenFilter_6+ h_whlt8_qcd_bEnriched_1 + h_whlt8_qcd_bEnriched_2 + h_whlt8_qcd_bEnriched_3 + h_whlt8_qcd_bEnriched_4 + h_whlt8_qcd_bEnriched_5 + h_whlt8_qcd_bEnriched_6 + h_whlt8_st_s + h_whlt8_st_t + h_whlt8_st_ant + h_whlt8_st_tW + h_whlt8_st_antW + h_whlt8_wjets_1 + h_whlt8_wjets_2 + h_whlt8_wjets_3 + h_whlt8_zjets_1 + h_whlt8_zjets_2 + h_whlt8_zjets_3 + h_whlt8_tth
        h_whltcur = h_whltcur_tt + h_whltcur_qcd_BGenFilter_1 + h_whltcur_qcd_BGenFilter_2 + h_whltcur_qcd_BGenFilter_3 + h_whltcur_qcd_BGenFilter_4 + h_whltcur_qcd_BGenFilter_5 + h_whltcur_qcd_BGenFilter_6+ h_whltcur_qcd_bEnriched_1 + h_whltcur_qcd_bEnriched_2 + h_whltcur_qcd_bEnriched_3 + h_whltcur_qcd_bEnriched_4 + h_whltcur_qcd_bEnriched_5 + h_whltcur_qcd_bEnriched_6 + h_whltcur_st_s + h_whltcur_st_t + h_whltcur_st_ant + h_whltcur_st_tW + h_whltcur_st_antW + h_whltcur_wjets_1 + h_whltcur_wjets_2 + h_whltcur_wjets_3 + h_whltcur_zjets_1 + h_whltcur_zjets_2 + h_whltcur_zjets_3 + h_whltcur_tth
        h_whltall = h_whltall_tt + h_whltall_qcd_BGenFilter_1 + h_whltall_qcd_BGenFilter_2 + h_whltall_qcd_BGenFilter_3 + h_whltall_qcd_BGenFilter_4 + h_whltall_qcd_BGenFilter_5 + h_whltall_qcd_BGenFilter_6+ h_whltall_qcd_bEnriched_1 + h_whltall_qcd_bEnriched_2 + h_whltall_qcd_bEnriched_3 + h_whltall_qcd_bEnriched_4 + h_whltall_qcd_bEnriched_5 + h_whltall_qcd_bEnriched_6 + h_whltall_st_s + h_whltall_st_t + h_whltall_st_ant + h_whltall_st_tW + h_whltall_st_antW + h_whltall_wjets_1 + h_whltall_wjets_2 + h_whltall_wjets_3 + h_whltall_zjets_1 + h_whltall_zjets_2 + h_whltall_zjets_3 + h_whltall_tth

        # data
        h_hlt0_dat = wrap_hist(h_nohlt_dat)
        h_hlt1_dat = wrap_hist(h_whlt1_dat)
        h_hlt2_dat = wrap_hist(h_whlt2_dat)
        h_hlt3_dat = wrap_hist(h_whlt3_dat)
        h_hlt4_dat = wrap_hist(h_whlt4_dat)
        h_hlt5_dat = wrap_hist(h_whlt5_dat)
        h_hlt6_dat = wrap_hist(h_whlt6_dat)
        h_hlt7_dat = wrap_hist(h_whlt7_dat)
        h_hlt8_dat = wrap_hist(h_whlt8_dat)
        h_hltcur_dat = wrap_hist(h_whltcur_dat)
        h_hltall_dat = wrap_hist(h_whltall_dat)

        h_eff_hlt1_dat, yerr_dat_hlt1 = getEfficiency(h_hlt1_dat, h_hlt0_dat)
        h_eff_hlt2_dat, yerr_dat_hlt2 = getEfficiency(h_hlt2_dat, h_hlt0_dat)
        h_eff_hlt3_dat, yerr_dat_hlt3 = getEfficiency(h_hlt3_dat, h_hlt0_dat)
        h_eff_hlt4_dat, yerr_dat_hlt4 = getEfficiency(h_hlt4_dat, h_hlt0_dat)
        h_eff_hlt5_dat, yerr_dat_hlt5 = getEfficiency(h_hlt5_dat, h_hlt0_dat)
        h_eff_hlt6_dat, yerr_dat_hlt6 = getEfficiency(h_hlt6_dat, h_hlt0_dat)
        h_eff_hlt7_dat, yerr_dat_hlt7 = getEfficiency(h_hlt7_dat, h_hlt0_dat)
        h_eff_hlt8_dat, yerr_dat_hlt8 = getEfficiency(h_hlt8_dat, h_hlt0_dat)
        h_eff_hltcur_dat, yerr_dat_hltcur = getEfficiency(h_hltcur_dat, h_hlt0_dat)
        h_eff_hltall_dat, yerr_dat_hltall = getEfficiency(h_hltall_dat, h_hlt0_dat)
                
        y_dat_errs = [yerr_dat_hlt1,yerr_dat_hlt2,yerr_dat_hlt3,yerr_dat_hlt4,yerr_dat_hlt5,yerr_dat_hlt6,yerr_dat_hlt7,yerr_dat_hlt8,yerr_dat_hltcur,yerr_dat_hltall]

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

        h_eff_hlt1, yerr_hlt1 = getEfficiency(h_hlt1, h_hlt0)
        h_eff_hlt2, yerr_hlt2 = getEfficiency(h_hlt2, h_hlt0)
        h_eff_hlt3, yerr_hlt3 = getEfficiency(h_hlt3, h_hlt0)
        h_eff_hlt4, yerr_hlt4 = getEfficiency(h_hlt4, h_hlt0)
        h_eff_hlt5, yerr_hlt5 = getEfficiency(h_hlt5, h_hlt0)
        h_eff_hlt6, yerr_hlt6 = getEfficiency(h_hlt6, h_hlt0)
        h_eff_hlt7, yerr_hlt7 = getEfficiency(h_hlt7, h_hlt0)
        h_eff_hlt8, yerr_hlt8 = getEfficiency(h_hlt8, h_hlt0)
        h_eff_hltcur, yerr_hltcur = getEfficiency(h_hltcur, h_hlt0)
        h_eff_hltall, yerr_hltall = getEfficiency(h_hltall, h_hlt0)
                
        y_errs = [yerr_hlt1,yerr_hlt2,yerr_hlt3,yerr_hlt4,yerr_hlt5,yerr_hlt6,yerr_hlt7,yerr_hlt8,yerr_hltcur,yerr_hltall]
       
        # Main plot
        # standard
        hep.histplot([h_eff_hltall,h_eff_hltall_dat], binning, ax=ax, histtype='errorbar', color=myc, capsize=2, xerr=True, yerr=y_errs, label=["all possible OR MC","all possible OR Data (SingleMu)"])

        ratios, ratio_err = getEfficiency(h_eff_hltall_dat, h_eff_hltall)

#        hep.histplot(h_eff_hltall_dat/h_eff_hltall, binning, yerr=np.sqrt(h_eff_hltall_dat)/h_eff_hltall, ax=rax, histtype='errorbar', color='k', capsize=2, label="Data/MC")
#        hep.histplot(h_eff_hltall_dat/h_eff_hltall, binning, yerr=True, ax=rax, histtype='errorbar', color='k', capsize=2, label="Data/MC")
        hep.histplot(ratios, binning, yerr=ratio_err, ax=rax, histtype='errorbar', color='k', capsize=2, label="Data/MC")
        # Final styling
        rax.axhline(1, ls='--', color='k')
#        rax.set_ylim(0.5, 1.5)
        rax.set_ylim(0.7, 1.3)
        rax.set_ylabel("Data/MC")

        ax.set_xlabel("")
        ax.set_xlim(xmin, xmax)
        ax.set_ylim(0, 1.4)
        ax.legend();
        handles, labels = ax.get_legend_handles_labels()
        ax.legend(handles[::-1], labels[::-1])
        ax.legend(fontsize=20)

        fig.subplots_adjust(left=0.15, right=0.95, top=0.95, bottom=0.12)
        fig.savefig(f"{outloc}/sf_allOR_{var}.png")
        fig.savefig(f"{outloc}/sf_allOR_{var}.pdf")
        plt.close()
