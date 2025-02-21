#! /usr/bin/env python
import os, sys, time, re
import csv

import numpy as np
import pandas as pd
import deepdish.io as io

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler, normalize
from sklearn.metrics import roc_auc_score, roc_curve

import tensorflow as tf
import keras
from keras.models import load_model
from tensorflow.keras.utils import to_categorical

plt.rcParams["figure.figsize"] = (6,6)
plt.rcParams["legend.fontsize"] = 8
plt.rcParams["axes.labelsize"] = 8
plt.rcParams["xtick.labelsize"] = 8
plt.rcParams["ytick.labelsize"] = 8

def evaluation(p, df_data, event_var, jet_var, outputDir):
    """
    Evaluation the model from given model / input
    """
    real_label = df_data.filter(['signal'], axis=1)
    input_event = df_data.filter(['event'], axis=1)
    info = df_data.filter(['evWeight','evWeight_all','mass_tprime'])

    #if len(input_data) != 0:
    input_data = df_data.filter(event_var+jet_var)

    njets = 5
    event_input = input_data.filter(event_var)
    event_input = np.array(event_input)
    jet_input = input_data.filter(jet_var)
    jet_input = np.array(jet_input)
    jet_input = jet_input.reshape( jet_input.shape[0], njets, -1)

    model = load_model(outputDir+'/best_model.h5')

    #prediction
    pred = pd.DataFrame(model.predict([event_input, jet_input], batch_size = 2048), columns=['pred_QCD','pred_TTbar','pred_Tprime']).set_index(input_event.index)

    selEvent = pd.concat([info, input_data, input_event, real_label, pred], axis=1)
    print(selEvent)
    print(list(selEvent))

    if not os.path.exists(f'{outputDir}/pred/'): os.makedirs(f'{outputDir}/pred/')

    io.save(f"{outputDir}/pred/pred_{p}",selEvent)

    print("Evaluation completed!")


    import matplotlib.pyplot as plt
    print("imported matplotlib, draw for cross-check...")
    nbins=40

    if not os.path.exists(f'{outputDir}/eval/'): os.makedirs(f'{outputDir}/eval/')

    # in case of data
"""
    print("w/ label")
    # label
    plt.hist(selEvent['pred_QCD'].loc[selEvent['signal'] == 0],
             color = 'b', alpha=0.5, bins=nbins,  density=True, label='QCD')
    plt.hist(selEvent['pred_QCD'].loc[selEvent['signal'] != 0],
             color = 'r', alpha=0.5, bins=nbins,  density=True, label='!QCD')
    plt.legend(["QCD", "!QCD"])
    plt.xlabel("QCD Prediction Score")
    plt.ylabel("Entries")
    plt.savefig(f'{outputDir}/eval/fig_pred_qcd_{region}_{p}_label.pdf')
    plt.gcf().clear()
   
    plt.hist(selEvent['pred_TTbar'].loc[selEvent['signal'] == 1],
             color = 'b', alpha=0.5, bins=nbins,  density=True, label='TTbar')
    plt.hist(selEvent['pred_TTbar'].loc[selEvent['signal'] != 1],
             color = 'r', alpha=0.5, bins=nbins,  density=True, label='!TTbar')
    plt.legend(["TT", "!TT"])
    plt.xlabel("TTbar Prediction Score")
    plt.ylabel("Entries")
    plt.savefig(f'{outputDir}/eval/fig_pred_ttbar_{region}_{p}_label.pdf')
    plt.gcf().clear()
   
    plt.hist(selEvent['pred_Tprime'].loc[selEvent['signal'] == 2],
             color = 'b', alpha=0.5, bins=nbins, density=True, label='Tprime')
    plt.hist(selEvent['pred_Tprime'].loc[selEvent['signal'] != 2],
             color = 'r', alpha=0.5, bins=nbins, density=True, label='!Tprime')
    plt.legend(["Tprime", "!Tprime"])
    plt.xlabel("Tprime Prediction Score")
    plt.ylabel("Entries")
    plt.savefig(f'{outputDir}/eval/fig_pred_tprime_{region}_{p}_label.pdf')
    plt.gcf().clear()
    print("done")

"""

if __name__ == '__main__':
    from optparse import OptionParser 

    parser = OptionParser()
    parser.usage = """
    %prog [options] option
    do Evaluation and extract Correlations Importance Distributions of features after training
    """
    parser.add_option("-e", "--eval", dest="eval",
                      action = 'store_true',
                      default=False,
                      help='Do Evaluation of model')

    (options,args) = parser.parse_args()

    start_time = time.time()

    event_var=['nseljets', 'nselbjets', 'goodht', 'relht', 'mindR_dRbb', 'mindR_mbb', 'Chi2_max', 'Chi2_min', 'Chi2_min_H', 'Chi2_min_W', 'Chi2_min_Top', 'mass_h', 'mass_w', 'mass_top', 'mass_wh', 'mass_secondtop', 'mass_leadjets', 'dR_hbb', 'dR_wjj', 'dR_bw', 'dR_tprimeoj', 'ratio_mass_topH', 'ratio_mass_secondtopW', 'ratio_pt_topsecondtop', 'ratio_pt_htoptprime', 'ratio_pt_tprimehtprimetop']
    jet_var=['jet1_eta', 'jet1_e_massnom', 'jet2_eta', 'jet2_e_massnom', 'jet3_eta', 'jet3_e_massnom', 'jet4_eta', 'jet4_e_massnom', 'jet5_eta', 'jet5_e_massnom']

    region = '2M1L'

    # Handle HERE
    model_name = f"model_{region}_redomodel1"

    DIR = '/Users/jieun/WORK/vlq/dnn/training/array/'+region+'/'
    OUT = "/Users/jieun/WORK/vlq/dnn/training/models/"+model_name+"/"

    for p in os.listdir(DIR):

        print(p)
        df = pd.read_hdf(DIR+p)
        if len(df) < 1:
            print(f"no len, len = {len(df)}")
            continue

        df.astype('float32')

        df = pd.DataFrame(df).fillna(-999)
        df.replace([np.inf, -np.inf], 999, inplace=True)
        if not df.isnull().values.any() and not np.isinf(df).values.any(): print("Dataset Cleaned!")

        if options.eval:
            evaluation(p, df, event_var, jet_var, OUT)

        else: print("Hi, this is shorten code. Add -e for evaluation to make sure you are running for full evaluation")

    print("Total running time :%s " %(time.time() - start_time))
