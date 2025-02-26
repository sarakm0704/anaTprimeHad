import pandas as pd
import numpy as np
import pickle
from sklearn.preprocessing import StandardScaler

import keras
from keras.models import Model, load_model
from tensorflow.keras.utils import to_categorical

region = ['2M1L','3M','3T']
nbins=40

for i in range(len(region)):
    dfQCD = pd.read_hdf(f"/Users/jieun/WORK/vlq/dnn/array/arrayOut/ana/multi/{region[i]}/array_merged_qcd.h5")
    dfTT = pd.read_hdf(f"/Users/jieun/WORK/vlq/dnn/array/arrayOut/ana/multi/{region[i]}/array_merged_ttbar.h5")
    dfTp = pd.read_hdf(f"/Users/jieun/WORK/vlq/dnn/array/arrayOut/ana/multi/{region[i]}/array_merged_tprime.h5")
    df = pd.concat([dfQCD, dfTT, dfTp], axis=0)

    event_var=['nseljets', 'nselbjets', 'goodht', 'relht', 'mindR_dRbb', 'mindR_mbb', 'Chi2_max', 'Chi2_min', 'Chi2_min_H', 'Chi2_min_W', 'Chi2_min_Top', 'mass_h', 'mass_w', 'mass_top', 'mass_wh', 'mass_secondtop', 'mass_leadjets', 'dR_hbb', 'dR_wjj', 'dR_bw', 'dR_tprimeoj', 'ratio_mass_topH', 'ratio_mass_secondtopW', 'ratio_pt_topsecondtop', 'ratio_pt_htoptprime', 'ratio_pt_tprimehtprimetop']
    jet_var=['jet1_eta', 'jet1_e_massnom', 'jet2_eta', 'jet2_e_massnom', 'jet3_eta', 'jet3_e_massnom', 'jet4_eta', 'jet4_e_massnom', 'jet5_eta', 'jet5_e_massnom']

    
    # label = training label, QCD : TT : T' = 0 : 1 : 2
    labels = df.filter(['signal'], axis=1)
    train_label = to_categorical(labels)
    cat_train_label = pd.DataFrame(train_label, columns=['QCD','TTbar','Tprime'])
    
    # event = event + label
    all_event = df.filter(['event','signal'], axis=1)
    train_event = all_event
    
    # data = training data = input variable
    data = df.filter(['signal']+event_var+jet_var)
    data.astype('float32')
    data = data.drop('signal', axis=1) #then drop label
    #clean data
    data = pd.DataFrame(data).fillna(-999)
    data.replace([np.inf, -np.inf], 999, inplace=True)
    if not data.isnull().values.any() and not np.isinf(data).values.any(): print("Cleaned data!")
    
    # input
    data_train = data
    # load scaler
    #with open(f'model/{region[i]}_scaler.pkl','rb') as f:
    #with open(f'/Users/jieun/WORK/vlq/dnn/training/models/train_121/model_{region[i]}/scaler.pkl','rb') as f:
    #    scaler = pickle.load(f)
    
    #scaler = StandardScaler()
    #data_train_sc = scaler.fit_transform(data_train)
    #train_data = data_train_sc

    njets = 5
    event_input = data_train.filter(event_var)
    event_input = np.array(event_input)
    jet_input = data_train.filter(jet_var)
    jet_input = np.array(jet_input)
    jet_input = jet_input.reshape( jet_input.shape[0], njets, -1)

    model = load_model(f'/Users/jieun/WORK/vlq/dnn/training/models/model_{region[i]}model1/best_model.h5')
    
    pred_data = pd.DataFrame(model.predict([event_input, jet_input], batch_size=2048), columns=['pred_QCD','pred_TTbar','pred_Tprime']).set_index(train_event.index)
    
    print("prediction done")
    
    pred = pd.concat([pred_data,train_event], axis=1)
    
    import matplotlib.pyplot as plt
    print("imported matplotlib, drawing...")
    # stack
    print("stacked")
    yesQCD = pred['pred_QCD'].loc[pred['signal'] == 0]
    noQCD = pred['pred_QCD'].loc[pred['signal'] != 0]
    plt.hist([yesQCD,noQCD], bins=nbins, stacked=True,  density=True, color=['b','r'])
    plt.legend(["QCD", "!QCD"])
    plt.xlabel("QCD Prediction Score")
    plt.ylabel("Normalized Entries")
    plt.savefig(f'fig_pred_{region[i]}_qcd_stack.pdf')
    plt.savefig(f'fig_pred_{region[i]}_qcd_stack.png')
    plt.gcf().clear()
    
    plt.hist([pred['pred_TTbar'].loc[pred['signal'] == 1], pred['pred_TTbar'].loc[pred['signal'] != 1]],
              bins=nbins, stacked=True,  density=True, color = ['b','r'])
    plt.legend(["TT", "!TT"])
    plt.xlabel("TTbar Prediction Score")
    plt.ylabel("Normalized Entries")
    plt.savefig(f'fig_pred_{region[i]}_ttbar_stack.pdf')
    plt.savefig(f'fig_pred_{region[i]}_ttbar_stack.png')
    plt.gcf().clear()
    
    yesTp = pred['pred_Tprime'].loc[pred['signal'] == 2]
    noTp = pred['pred_Tprime'].loc[pred['signal'] != 2]
    plt.hist([yesTp,noTp], bins=nbins, stacked=True,  density=True, color = ['b','r'])
    plt.legend(["Tprime", "!Tprime"])
    plt.xlabel("Tprime Prediction Score")
    plt.ylabel("Normalized Entries")
    plt.savefig(f'fig_pred_{region[i]}_tprime_stack.pdf')
    plt.savefig(f'fig_pred_{region[i]}_tprime_stack.png')
    plt.gcf().clear()
    print("done")
    
    print("label")
    # label
    plt.hist(pred['pred_QCD'].loc[pred['signal'] == 0], 
             color = 'b', alpha=0.5, bins=nbins,  density=True, label='QCD')
    plt.hist(pred['pred_QCD'].loc[pred['signal'] != 0], 
             color = 'r', alpha=0.5, bins=nbins,  density=True, label='!QCD')
    plt.legend(["QCD", "!QCD"])
    plt.xlabel("QCD Prediction Score")
    plt.ylabel("Normalized Entries")
    plt.savefig(f'fig_pred_{region[i]}_qcd_label.pdf')
    plt.savefig(f'fig_pred_{region[i]}_qcd_label.png')
    plt.gcf().clear()
    
    plt.hist(pred['pred_TTbar'].loc[pred['signal'] == 1], 
             color = 'b', alpha=0.5, bins=nbins,  density=True, label='TTbar')
    plt.hist(pred['pred_TTbar'].loc[pred['signal'] != 1], 
             color = 'r', alpha=0.5, bins=nbins,  density=True, label='!TTbar')
    plt.legend(["TT", "!TT"])
    plt.xlabel("TTbar Prediction Score")
    plt.ylabel("Normalized Entries")
    plt.savefig(f'fig_pred_{region[i]}_ttbar_label.pdf')
    plt.savefig(f'fig_pred_{region[i]}_ttbar_label.png')
    plt.gcf().clear()
    
    plt.hist(pred['pred_Tprime'].loc[pred['signal'] == 2], 
             color = 'b', alpha=0.5, bins=nbins, density=True, label='Tprime')
    plt.hist(pred['pred_Tprime'].loc[pred['signal'] != 2], 
             color = 'r', alpha=0.5, bins=nbins, density=True, label='!Tprime')
    plt.legend(["Tprime", "!Tprime"])
    plt.xlabel("Tprime Prediction Score")
    plt.ylabel("Normalized Entries")
    plt.savefig(f'fig_pred_{region[i]}_tprime_label.pdf')
    plt.savefig(f'fig_pred_{region[i]}_tprime_label.png')
    plt.gcf().clear()
    print("done")
    
    print("nolabel")
    # nolabel
    plt.hist(pred['pred_QCD'], label='pred_QCD', density=True, bins=nbins)
    plt.legend(["event"])
    plt.xlabel("QCD Prediction Score")
    plt.ylabel("Normalized Entries")
    plt.savefig(f'fig_pred_{region[i]}_qcd_nolabel.pdf')
    plt.savefig(f'fig_pred_{region[i]}_qcd_nolabel.png')
    plt.gcf().clear()
    plt.hist(pred['pred_TTbar'], label='pred_TTbar', density=True, bins=nbins)
    plt.legend(["event"])
    plt.xlabel("TTbar Prediction Score")
    plt.ylabel("Normalized Entries")
    plt.savefig(f'fig_pred_{region[i]}_ttbar_nolabel.pdf')
    plt.savefig(f'fig_pred_{region[i]}_ttbar_nolabel.png')
    plt.gcf().clear()
    plt.hist(pred['pred_Tprime'], label='pred_Tprime', density=True, bins=nbins)
    plt.legend(["event"])
    plt.xlabel("Tprime Prediction Score")
    plt.ylabel("Normalized Entries")
    plt.savefig(f'fig_pred_{region[i]}_tprime_nolabel.pdf')
    plt.savefig(f'fig_pred_{region[i]}_tprime_nolabel.png')
    plt.gcf().clear()
    print("done")
