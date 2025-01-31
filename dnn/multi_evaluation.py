#! /usr/bin/env python
import os, sys, time, re
import csv

# HYU htop option
#os.environ["CUDA_VISIBLE_DEVICES"] = "0"

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

#plt.rcParams["figure.figsize"] = (7,9)
plt.rcParams["figure.figsize"] = (6,6)
plt.rcParams["legend.fontsize"] = 8
plt.rcParams["axes.labelsize"] = 8
plt.rcParams["xtick.labelsize"] = 8
plt.rcParams["ytick.labelsize"] = 8

def evaluation(df_data, name_inputvar, outputDir):
    """
    Evaluation the model from given model / input
    """

    print("Checking nan / inf in input dataset...")
    
    df_data = pd.DataFrame(df_data).fillna(-999)
    df_data.replace([np.inf, -np.inf], 999, inplace=True)
    
    if not df_data.isnull().values.any() and not np.isinf(df_data).values.any(): print("Cleaned data!")
    
    model = load_model(outputDir+'/model.h5')
    model.summary()

    print("whats going on")
    print(f"signal = {df_data['signal']}")
    print("categorical")
    cat_label = pd.DataFrame([], columns=['QCD','TTbar','Tprime'])
    print(f"{cat_label}")
    print("then try this") 
    #cat_label = pd.DataFrame(to_categorical(df_data.filter(['signal'])), columns=['QCD','TTbar','Tprime'])
    cat_label = pd.DataFrame(to_categorical(df_data.filter(['signal']), num_classes=3), columns=['QCD','TTbar','Tprime'])
    print(f"{cat_label}")
    real_label = cat_label['Tprime']
    #real_label = df_data.filter(['signal'])
    input_event = df_data.filter(['event'], axis=1)

    info = df_data.filter(['evWeight','mass_tprime'])
    input_data = df_data.filter(name_inputvar)
    pred = pd.DataFrame([], columns=['pred_QCD','pred_TTbar','pred_Tprime'])
    import pickle
    with open(f'models/{model_name}/scaler.pkl','rb') as f:
        scaler = pickle.load(f)
    #scaler = StandardScaler()
    if len(input_data) != 0:
        input_sc = scaler.fit_transform(input_data)
        #prediction
        pred = pd.DataFrame(model.predict(input_sc, batch_size = 2048), columns=['pred_QCD','pred_TTbar','pred_Tprime'])
        #pred = pred['pred_Tprime']

    #selLabel = pd.concat([real_label, pred], axis=1)
    #print(selLabel)
    #plt.figure()
    #selLabel.plot.hist(alpha=0.5)
    #plt.savefig("out_all.pdf")
    #plt.gcf().clear()
    
    selEvent = pd.concat([info, input_data, input_event, real_label, pred], axis=1)
    io.save(f"{outputDir}/pred/pred_{p}",selEvent)
    #addStep = True 

    #if addStep:
    #    selEvent = pd.concat([input_data, input_event, real_label, pred], axis=1)
    #    nf = TFile.Open(f"{outputDir}/{p}.root","RECREATE")
    #    outtree = TTree("tree","tree")
    #    njets        = np.zeros(1, dtype=int)
    #    nbjets       = np.zeros(1, dtype=int)
    #    mtprime      = np.zeros(1, dtype=np.float32)
    #    disc         = np.zeros(1, dtype=np.float32)

    #    outtree.Branch('njets'          ,  njets        , 'njets/I'         )
    #    outtree.Branch('nbjets'         ,  nbjets       , 'nbjets/I'        )
    #    outtree.Branch('mtprime'        ,  mtprime      , 'mtprime/F'       )
    #    outtree.Branch('disc'           ,  disc         , 'disc/F'          )
    #    
    #    h_njets = TH1D("h_njets","",10,5,15)
    #    h_njets.GetXaxis().SetTitle("Number of jets")
    #    h_njets.GetYaxis().SetTitle("Entries")

    #    h_nbjets = TH1D("h_nbjets","",6,2,8)
    #    h_nbjets.GetXaxis().SetTitle("Number of b-tagged jets")
    #    h_nbjets.GetYaxis().SetTitle("Entries")
    #    
    #    h_mtprime = TH1D("h_mtprime","",100,0,2000)
    #    h_mtprime.GetXaxis().SetTitle("Invariant Mass of Tprime candidate")
    #    h_mtprime.GetYaxis().SetTitle("Entries")

    #    h_disc = TH1D("h_disc","",100,0,1)
    #    h_disc.GetXaxis().SetTitle("DNN Discriminator")
    #    h_disc.GetYaxis().SetTitle("Entries")

    #    h_after_njets = TH1D("h_after_njets","",10,5,15)
    #    h_after_njets.GetXaxis().SetTitle("Number of jets")
    #    h_after_njets.GetYaxis().SetTitle("Entries")

    #    h_after_nbjets = TH1D("h_after_nbjets","",6,2,8)
    #    h_after_nbjets.GetXaxis().SetTitle("Number of b-tagged jets")
    #    h_after_nbjets.GetYaxis().SetTitle("Entries")
    #    
    #    h_after_mtprime = TH1D("h_after_mtprime","",100,0,2000)
    #    h_after_mtprime.GetXaxis().SetTitle("Invariant Mass of Tprime candidate")
    #    h_after_mtprime.GetYaxis().SetTitle("Entries")

    #    h_after_disc = TH1D("h_after_disc","",100,0,1)
    #    h_after_disc.GetXaxis().SetTitle("DNN Discriminator")
    #    h_after_disc.GetYaxis().SetTitle("Entries")

    #    for index, event in selEvent.iterrows():

    #        weight = event['evWeight']

    #        njets = event['nseljets']
    #        nbjets = event['nselbjets']
    #        mtprime = event['mass_tprime']
    #        disc = event['pred']

    #        h_njets.Fill(njets,weight)
    #        h_nbjets.Fill(nbjets,weight)
    #        h_mtprime.Fill(mtprime,weight)
    #        h_disc.Fill(disc,weight)

    #        if disc > 0.5:
    #            h_after_njets.Fill(njets,weight)
    #            h_after_nbjets.Fill(nbjets,weight)
    #            h_after_mtprime.Fill(mtprime,weight)
    #            h_after_disc.Fill(disc,weight)

    #    outtree.Fill()

    #    nf.Write()
    #    nf.Close()

    ################### Plot ROC curve ##################

    #fpr = dict()
    #tpr = dict()
    #fpr[1], tpr[1], thresholds1 = roc_curve(real_label.values.tolist(), pred['pred'].values.tolist(), pos_label=1)#w.r.t sig is truth to EVALUATION
    #roc_auc = roc_auc_score(real_label.values.tolist(),pred['pred'].values.tolist())

    #pd.DataFrame(tpr[1]).to_csv('roc_curve/tpr_evaluation.csv')
    #pd.DataFrame(fpr[1]).to_csv('roc_curve/fpr_evaluation.csv')

    #print("AUC: "+str(roc_auc))
    #plt.plot(tpr[1], 1-fpr[1]) #HEP style ROC
    #plt.xlabel('Signal Efficiency')
    #plt.ylabel('Background Rejection')
    #plt.title('ROC Curve')
    #plt.legend(['EVAL'], loc='lower left')
    #plt.savefig(os.path.join(outputDir+'/','fig_score_roc_eval.pdf'))
    #plt.gcf().clear()
    #print('ROC curve is saved!')
    #
    ################### Overtraining Check, as well as bkg & sig discrimination ##################
    #bins = 40
    #scores = [tpr[1], fpr[1]]
    #low = min(np.min(d) for d in scores)
    #high = max(np.max(d) for d in scores)
    #low_high = (low,high)
    #
    ## output distribution from evaluation
    #plt.hist(tpr[1],
    #    color='b', alpha=0.5, range=low_high, bins=bins,
    #    histtype='stepfilled', density=True)
    #plt.hist(fpr[1],
    #    color='r', alpha=0.5, range=low_high, bins=bins,
    #    histtype='stepfilled', density=True)

    #hist, bins = np.histogram(tpr[1], bins=bins, range=low_high, density=True)
    #scale = len(tpr[1]) / sum(hist)
    #err = np.sqrt(hist * scale) / scale
    #width = (bins[1] - bins[0])
    #center = (bins[:-1] + bins[1:]) / 2
    #plt.errorbar(center, hist, yerr=err, fmt='.', c='b', label='Signal')
    #hist, bins = np.histogram(fpr[1], bins=bins, range=low_high, density=True)
    #scale = len(tpr[1]) / sum(hist)
    #err = np.sqrt(hist * scale) / scale
    #plt.errorbar(center, hist, yerr=err, fmt='.', c='r', label='Background')
    #
    #plt.title('Output distribution')
    #plt.xlabel("Deep Learning Score")
    #plt.ylabel("Number of Events")
    #plt.legend(loc='best')
    #plt.savefig(os.path.join(outputDir+'/','fig_score_eval.pdf'))
    #plt.gcf().clear()
    #print('Output distribution is saved!')

    print("Evaluation completed!")


def feature_importance(df_data, name_inputvar, outputDir, order):
    """
    Extract importance of features    
            then save it in outside
            load it from outside if it is exist
    Plotting importance in 'first-order' or 'second-order'
    """

    model = load_model(outputDir+'/model.h5')
    model.summary()
    
    input_data = df_data.filter(name_inputvar)

    ################### Feature importance ##################

    n_evts = len(input_data)
    n_var = len(name_inputvar)

    #TODO -> 2nd option put!
    mean_1st = []
    mean_2nd = []

    mean_grads = np.zeros(n_var)
    mean_jacobian = np.zeros(n_var)
    jacobian_matrix = np.zeros((n_var,n_var))

    if not os.path.exists(outputDir+'/feature_importance.txt'):

        mean_grads = np.zeros(len(name_inputvar))
        mean_jacobian = np.zeros(len(name_inputvar))
        jacobian_matrix = np.zeros((len(name_inputvar),len(name_inputvar)))

        if order == 1:
            for idx, row in input_data.iterrows():
                with tf.GradientTape() as tape:
                    inputs = tf.Variable([row.to_numpy()])
                    tape.watch(inputs)
                    output = model(inputs)
                g = tape.gradient(output, inputs)
                grads = g.numpy()[0]
                for i in range(n_var): mean_grads[i] += abs(grads[i])/n_evts

            print("Average of first order gradient: \n"+str(mean_grads))

        elif order == 2:
            for idx, row in input_data.iterrows():
                with tf.GradientTape() as tape2:
                    with tf.GradientTape() as tape:
                        inputs = tf.Variable([row.to_numpy()])
                        tape.watch(inputs)
                        tape2.watch(inputs)
                        output = model(inputs)
                    g = tape.gradient(output, inputs)
                    grads = g.numpy()[0]
                jacobian = tape2.jacobian(g, inputs).numpy()[0]
                for i in range(n_var):
                    mean_grads[i] += abs(grads[i])/n_evts
                    mean_jacobian[i] += abs(jacobian[i][0][i])/n_evts
                    for j in range(len(name_inputvar)): jacobian_matrix[i][j] += abs(jacobian[i][0][j])/n_evts

            print("Average of first order gradient: \n"+str(mean_grads))
            print("Average of second order gradient: \n"+str(mean_jacobian))

            normFactor = np.linalg.norm(jacobian_matrix)
            norm = jacobian_matrix/normFactor

            fig, ax1 = plt.subplots(ncols=1, figsize=(8,7))
    
            opts = {'cmap': plt.get_cmap("cividis"),
                    'vmin': np.min(norm), 'vmax': np.max(norm)}
            heatmap1 = ax1.pcolor(norm, **opts)
            plt.colorbar(heatmap1, ax=ax1)

            labels = input_data.columns.values
            for ax in (ax1,):
                ax.tick_params(labelsize=6)
                # shift location of ticks to center of the bins
                ax.set_xticks(np.arange(len(labels))+0.5, minor=False)
                ax.set_yticks(np.arange(len(labels))+0.5, minor=False)
                ax.set_xticklabels(labels, minor=False, ha='right', rotation=90)
                ax.set_yticklabels(labels, minor=False)
    
            plt.tight_layout()
            plt.savefig(outputDir+"/fig_jacobian_2ndorder.pdf")
            plt.gcf().clear()

        else:
            print("Expansion to first or second oder is only available. Error code = "+str(order))
            sys.exit()
        
        ##save it
        f_out = open(outputDir+'/feature_importance.txt','w')
        f_out.write("Feature importance with model: "+model_name+"\n")
        f_out.write("Average of first order gradient: \n" + str(mean_grads)+"\n")
        f_out.write("Average of second order gradient: \n" + str(mean_jacobian)+"\n")
        f_out.close()

        mean_grads = " ".join(map(str,mean_grads))
        mean_jacobian = " ".join(map(str,mean_jacobian))

        mean_1st = [float(num) for num in mean_grads.split(" ")]
        mean_2nd = [float(num) for num in mean_jacobian.split(" ")]

    else: 
        mean_grads = []
        mean_jacobian = []
        count = 0
        #TODO Still cant import 2nd order options...
        print("Reading exisiting importances..")
        with open(outputDir+'/feature_importance.txt','r') as f_in:
            for line in f_in:
                if "." in line:
                  if "[" in line: count = count + 1
                  if count == 1: mean_grads.append(line.strip('[\n]'))
                  elif count == 2: mean_jacobian.append(line.strip('[\n]'))
                  else: print("huh I shouldn't have 3rd term")

        mean_grads = "".join(mean_grads)
        mean_jacobian = "".join(mean_jacobian)

        mean_1st = [float(num) for num in mean_grads.split(" ")]
        mean_2nd = [float(num) for num in mean_jacobian.split(" ")]

    ################### Plotting importance ##################

    #df_impact = pd.DataFrame({'second-order':mean_2nd,'first-order':mean_1st}, index=name_inputvar)

    df_impact = pd.DataFrame({'first-order':mean_1st}, index=name_inputvar)
    df_impact = df_impact.sort_values(['first-order'], ascending = True)
    #df_impact = pd.DataFrame({'second-order':mean_2nd}, index=name_inputvar)
    #df_impact = df_impact.sort_values(['second-order'], ascending = True)

    #df_impact = (df_impact-df_impact.min())/(df_impact.max()-df_impact.min())
    df_impact = df_impact/df_impact.sum()
    
    #ax = df_impact.plot.barh(color={'first-order':'#002b54', 'second-order':'#b38e50'}, width=0.9, alpha = 0.9)
    ax = df_impact.plot.barh(color={'first-order':'#002b54'}, width=0.9, alpha = 0.9, figsize=(6,9))
    
    plt.ylim(-0.6, ax.get_yticks()[-1] + 0.6)
    
    ax.set_axisbelow(True)
    ax.xaxis.grid(color='gray', linestyle='dashed')
    plt.xlabel('Normalized Importance')
    
    #handles,labels = ax.get_legend_handles_labels()
    #handles = [handles[1], handles[0]]
    #labels = [labels[1], labels[0]]
    #ax.legend(handles,labels,loc='best')
    ax.legend(loc='best')
    
    plt.tight_layout()
    plt.savefig(outputDir+"/fig_feature_importance.pdf")
    plt.gcf().clear()

    print("Feature importance extracted!")


def correlation_matrices(df_data, outputDir, label, invars, **kwds):

    """
    Calculate pairwise correlation between features.
    Extra arguments are passed on to DataFrame.corr()
    """
    # simply call df.corr() to get a table of
    # correlation values if you do not need
    # the fancy plotting

    data = df_data.loc[df_data['signal'] == label].drop('signal',axis=1)
    data = data.filter(invars)

    corrmat = data.corr(**kwds)

    plt.figure(figsize=(7,9),dpi=80)
    fig, ax1 = plt.subplots(ncols=1, figsize=(8,7))

    opts = {'cmap': plt.get_cmap("RdBu"),
    #opts = {'cmap': plt.get_cmap("twilight"),
    #opts = {'cmap': plt.get_cmap("twilight_shifted"),
            'vmin': -1, 'vmax': +1}
    heatmap1 = ax1.pcolor(corrmat, **opts)
    plt.colorbar(heatmap1, ax=ax1)

    labels = corrmat.columns.values

    for ax in (ax1,):
        ax.tick_params(labelsize=6)
        # shift location of ticks to center of the bins
        ax.set_xticks(np.arange(len(labels))+0.5, minor=False)
        ax.set_yticks(np.arange(len(labels))+0.5, minor=False)
        ax.set_xticklabels(labels, minor=False, ha='right', rotation=90)
        ax.set_yticklabels(labels, minor=False)

    plt.tight_layout()
    #plt.show()

    if label == 1 :
        ax1.set_title("Correlations in Signal")
        plt.savefig(outputDir+'/fig_corr_s.pdf')
        print('Correlation matrix for signal is saved!')
        plt.gcf().clear()
    elif label == 0 :
        ax1.set_title("Correlations in Background")
        plt.savefig(outputDir+'/fig_corr_b.pdf')
        plt.gcf().clear()
        print('Correlation matrix for background is saved!')
    else : print('Wrong class name! Sorry I can digest only binary information.. error code = '+str(label))


def draw_features(df_data, outputDir, label0, label1, **kwds):

    """
    Draw distribution of input features.
    """

    bkgdata = df_data.loc[df_data['signal'] == label0].drop('signal',axis=1)
    sigdata = df_data.loc[df_data['signal'] == label1].drop('signal',axis=1)

    print('Plotting input variables')
    bins = 50

    for colname in sigdata:
      if 'seljets' in colname: bins=10
      elif 'nselbjets' in colname: bins=5
      else: bins=25
      dataset = [sigdata, bkgdata]
      low = min(np.min(d[colname].values) for d in dataset)
      high = max(np.max(d[colname].values) for d in dataset)
      low_high = (low,high)

      plt.figure()
      sigdata[colname].plot.hist(color='b', density=True, range=low_high, bins=bins, histtype='step', label='signal')
      bkgdata[colname].plot.hist(color='r', density=True, range=low_high, bins=bins, histtype='step', label='background')
      plt.xlabel(colname)
      #plt.ylabel('Number of entries')
      plt.ylabel('Nomalized entries')
      plt.title('Intput variables')
      plt.legend(loc='best')
      plt.savefig(outputDir+'fig_input_'+colname+'.pdf')
      plt.gcf().clear()
      plt.close()

    print("Input distributions are saved!")

if __name__ == '__main__':
    from optparse import OptionParser 

    parser = OptionParser()
    parser.usage = """
    %prog [options] option
    do Evaluation and extract Correlations Importance Distributions of features after training
    """
    parser.add_option("-n", "--infnan", dest="incheck",
                      action = 'store_true',
                      default=True,
                      help='Check nan / inf in input dataset (default)')
    
    parser.add_option("-e", "--eval", dest="eval",
                      action = 'store_true',
                      default=False,
                      help='Do Evaluation of model')

    (options,args) = parser.parse_args()

    start_time = time.time()

    # Handle HERE
    #model_name = 'model_3T_noChis_noselb_QCDttbar'
    #model_name = 'model_2M1L_multi_sel'
    model_name = 'model_2M1L'

    # no Chi2s noselbjets
    #VAR=['nseljets', 'goodht', 'relht', 'mindR_dRbb', 'mindR_mbb', 'jet1_eta', 'jet2_eta', 'jet3_eta', 'jet4_eta', 'jet5_eta', 'jet1_btag', 'jet2_btag', 'jet3_btag', 'jet4_btag', 'jet5_btag', 'bjet1_eta', 'bjet2_eta', 'bjet1_btag', 'bjet2_btag', 'jet1_e_massnom', 'jet2_e_massnom', 'jet3_e_massnom', 'jet4_e_massnom', 'jet5_e_massnom', 'bjet1_e_massnom', 'bjet2_e_massnom', 'mass_h', 'mass_w', 'mass_top', 'mass_wh', 'mass_secondtop', 'mass_leadjets', 'dR_hbb', 'dR_wjj', 'dR_bw', 'dR_tprimeoj', 'ratio_mass_topH', 'ratio_mass_secondtopW', 'ratio_pt_topsecondtop', 'ratio_pt_htoptprime', 'ratio_pt_tprimehtprimetop']
    #VAR=['nseljets', 'goodht', 'relht', 'mindR_dRbb', 'mindR_mbb', 'jet1_eta', 'jet2_eta', 'jet3_eta', 'jet4_eta', 'jet5_eta', 'jet1_btag', 'jet2_btag', 'jet3_btag', 'jet4_btag', 'jet5_btag', 'bjet1_eta', 'bjet2_eta', 'bjet1_btag', 'bjet2_btag', 'jet1_e_massnom', 'jet2_e_massnom', 'jet3_e_massnom', 'jet4_e_massnom', 'jet5_e_massnom', 'bjet1_e_massnom', 'bjet2_e_massnom', 'Chi2_min_H', 'Chi2_min_W', 'mass_h', 'mass_w', 'mass_top', 'mass_wh', 'mass_secondtop', 'mass_leadjets', 'dR_hbb', 'dR_wjj', 'dR_bw', 'dR_tprimeoj', 'ratio_mass_topH', 'ratio_mass_secondtopW', 'ratio_pt_topsecondtop', 'ratio_pt_htoptprime', 'ratio_pt_tprimehtprimetop']
    # no btag
    VAR=['nseljets', 'nselbjets', 'goodht', 'relht', 'mindR_dRbb', 'mindR_mbb', 'jet1_eta', 'jet2_eta', 'jet3_eta', 'jet4_eta', 'jet5_eta', 'bjet1_eta', 'bjet2_eta', 'jet1_e_massnom', 'jet2_e_massnom', 'jet3_e_massnom', 'jet4_e_massnom', 'jet5_e_massnom', 'bjet1_e_massnom', 'bjet2_e_massnom', 'Chi2_max', 'Chi2_min', 'Chi2_min_H', 'Chi2_min_W', 'Chi2_min_Top', 'mass_h', 'mass_w', 'mass_top', 'mass_wh', 'mass_secondtop', 'mass_leadjets', 'dR_hbb', 'dR_wjj', 'dR_bw', 'dR_tprimeoj', 'ratio_mass_topH', 'ratio_mass_secondtopW', 'ratio_pt_topsecondtop', 'ratio_pt_htoptprime', 'ratio_pt_tprimehtprimetop']

    #DIR = "/pbs/home/j/jechoi/work/vlq/nn/array/ana/2M1L/multi/all/"
    DIR = '/sps/lyon/jechoi/tprimeHad/2018/2M1L/array/merged/'
    #TAR = "array_trainInput_shuffled.h5"
    OUT = "models/"+model_name+"/"

    for p in os.listdir(DIR):
        print(p)
        df = pd.read_hdf(DIR+p)
        if len(df) < 1:
            print(f"no len, len = {len(df)}")
            continue

        if options.incheck:
            print("Checking nan / inf in input dataset...")
            
            df = pd.DataFrame(df).fillna(-999)
            df.replace([np.inf, -np.inf], 999, inplace=True)
            
            if not df.isnull().values.any() and not np.isinf(df).values.any(): print("Cleaned input dataset!")

        if options.eval:
            evaluation(df, VAR, OUT)

    print("Total running time :%s " %(time.time() - start_time))
