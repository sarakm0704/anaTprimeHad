import sys, os
import pandas as pd
import numpy as np
import pickle
from sklearn.preprocessing import StandardScaler

import keras
from keras.models import Model, load_model
from tensorflow.keras.utils import to_categorical

import matplotlib.pyplot as plt
import seaborn as sns

import dcor

region = ['2M1L','3M','3T']
nbins=30

def cleaning(d):
    d = pd.DataFrame(d).fillna(-999)
    d.replace([np.inf, -np.inf], 999, inplace=True)
    if not d.isnull().values.any() and not np.isinf(d).values.any(): print("Cleaned data!")
    
    return d

def distance_correlation_matrix(df):
    n = df.shape[1]
    dcor_matrix = np.zeros((n, n))
    for i in range(n):
        print(f"for index i = {i}")
        for j in range(n):
            print(f"correlation with index j = {j}")
            dcor_matrix[i, j] = dcor.distance_correlation(df.iloc[:, i], df.iloc[:, j])
    return pd.DataFrame(dcor_matrix, index=df.columns, columns=df.columns)


for r in region:
    dfQCD = pd.read_hdf(f"/Users/jieun/WORK/vlq/dnn/array/arrayOut/ana/multi/{r}/array_merged_qcd.h5")
    dfTT = pd.read_hdf(f"/Users/jieun/WORK/vlq/dnn/array/arrayOut/ana/multi/{r}/array_merged_ttbar.h5")
    dfTp = pd.read_hdf(f"/Users/jieun/WORK/vlq/dnn/array/arrayOut/ana/multi/{r}/array_merged_tprime.h5")
    df = pd.concat([dfQCD, dfTT, dfTp], axis=0)

    event_var=['nseljets', 'nselbjets', 'goodht', 'relht', 'mindR_dRbb', 'mindR_mbb', 'Chi2_max', 'Chi2_min', 'Chi2_min_H', 'Chi2_min_W', 'Chi2_min_Top', 'mass_h', 'mass_w', 'mass_top', 'mass_wh', 'mass_secondtop', 'mass_leadjets', 'dR_hbb', 'dR_wjj', 'dR_bw', 'dR_tprimeoj', 'ratio_mass_topH', 'ratio_mass_secondtopW', 'ratio_pt_topsecondtop', 'ratio_pt_htoptprime', 'ratio_pt_tprimehtprimetop']
    jet_var=['jet1_eta', 'jet1_e_massnom', 'jet2_eta', 'jet2_e_massnom', 'jet3_eta', 'jet3_e_massnom', 'jet4_eta', 'jet4_e_massnom', 'jet5_eta', 'jet5_e_massnom']
    name_inputvar = event_var+jet_var
    
    #clean data
#    dfQCD = cleaning(dfQCD)
#    dfTT = cleaning(dfTT)
#    dfTp = cleaning(dfTp)
    df = cleaning(df)

    # looping over all 3 signals: QCD, TTbar, Signal
    signal = None
    for s in range(3):
        if s == 0:
            print("run over QCD")
            signal = "qcd"
        elif s == 1:
            print("run over TTbar")
            signal = "tt"
        elif s == 2:
            print("run over Tprime")
            signal = "tprime"
        else:
            print("who are you")
            sys.exit()

        df_tar = df.loc[df['signal'] == s]
        df_tar = df_tar.filter(name_inputvar)
        df_tar = df_tar.astype(np.float64)
        
        pearson_corrmat = df_tar.corr()
        dist_corrmat = distance_correlation_matrix(df_tar)

        # it takes so long time to calculate. it is precious, lets save it
        file_path = 'corrmat/corrmat_'+r+'_'+signal
        dist_corrmat.to_csv(file_path+'_distance.csv')
        pearson_corrmat.to_csv(file_path+'_pearson.csv')

        combined_matrix = np.zeros_like(pearson_corrmat)
        # Fill the upper triangle with the Pearson correlation coefficients
        for i in range(combined_matrix.shape[0]):
            for j in range(i, combined_matrix.shape[1]):
                combined_matrix[i, j] = pearson_corrmat.iloc[i, j]

        # Fill the lower triangle with the Distance correlation coefficients
        for i in range(combined_matrix.shape[0]):
            for j in range(i):
                combined_matrix[i, j] = dist_corrmat.iloc[i, j]

        combined_matrix = pd.DataFrame(combined_matrix, index=df_tar.columns, columns=df_tar.columns)

        mask_upper = np.triu(np.ones_like(combined_matrix, dtype=bool))
        mask_lower = np.tril(np.ones_like(combined_matrix, dtype=bool), -1)
        mask_combined = mask_upper | mask_lower

        print("drawing...")

        plt.figure(figsize=(14, 12),dpi=80)
        sns.heatmap(combined_matrix, annot=False, mask=~mask_combined, cmap='RdBu', vmin=-1, vmax=1)
        plt.tight_layout()
        plt.title("Combined Correlation Matrix: Pearson (Upper) and Distance (Lower)")
        plt.savefig(f"corrmat/corrmat_{r}_{signal}.pdf")
        plt.savefig(f"corrmat/corrmat_{r}_{signal}.png")
