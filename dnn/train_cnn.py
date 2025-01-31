from __future__ import division
import sys, os, re, shutil, array

#os.environ["CUDA_DEVICE_ORDER"] = "PCI_BUS_ID"
#os.environ['CUDA_VISIBLE_DEVICES'] = '2, 3'

import numpy as np
import pandas as pd

from keras.models import Model, Sequential, load_model
from keras.layers import Input, Dense, Dropout, LSTM, Concatenate
from tensorflow.keras.layers import BatchNormalization
from keras.layers.convolutional import Conv1D

from keras.callbacks import ModelCheckpoint, EarlyStopping
from sklearn.metrics import confusion_matrix, roc_auc_score, roc_curve
from sklearn.utils.class_weight import compute_class_weight
from sklearn.model_selection import train_test_split
from tensorflow.keras.utils import to_categorical

import matplotlib
matplotlib.use('Agg')

import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter
import seaborn as sns

from time import time, localtime, strftime

import argparse
parser = argparse.ArgumentParser()
parser.add_argument('--e', required=False, default=5, help='epochs')

args = parser.parse_args()
epochs = int(args.e) #Epoch
njets = 5

def split_train_test():
    pd_label = data.filter(items = ['signal'])
    pd_input = data.filter(items = event_var+jet_var)
    np_label = np.array( pd_label )
    np_input = np.array( pd_input )
    # split
    #test_size = 0.3
    test_size = 0.4
    train_input, valid_input, train_label, valid_label = train_test_split( np_input, np_label, test_size=test_size )

    # train set
    pd_train_input = pd.DataFrame( train_input, columns= event_var+jet_var )
    pd_train_label = pd.DataFrame( train_label, columns=['signal'] )
    # event info
    train_event_input = pd_train_input.filter( items=event_var )
    train_event_input = np.array( train_event_input )
    train_event_label = pd_train_label.filter( items=['signal'] )
    train_event_label = to_categorical( train_event_label )
    # jet info
    train_jet_input = pd_train_input.filter( items=jet_var )
    train_jet_input = np.array( train_jet_input )
    train_jet_input = train_jet_input.reshape( train_jet_input.shape[0], njets, -1 )
    
    # valid set
    pd_valid_input = pd.DataFrame( valid_input,columns= event_var+jet_var )
    pd_valid_label = pd.DataFrame( valid_label, columns=['signal'] )
    
    # event info
    print(f".shapepd_valid_input = {pd_valid_input}")
    print(f"pd_valid_input type = {type(pd_valid_input)}")
    print(f"pd_valid_input shape = {pd_valid_input.shape}")
    valid_event_input = pd_valid_input.filter( items=event_var )
    print(f"before array shape valid_event_input = {valid_event_input.shape}")
    print(f"before array valid_event_input = {valid_event_input}")
    valid_event_input = np.array( valid_event_input )
    print(f"after array valid_event_input = {valid_event_input}")
    print(f"after array shape valid_event_input = {valid_event_input.shape}")

    valid_event_label = pd_valid_label.filter( items=['signal'] )
    valid_event_label = to_categorical( valid_event_label )
    # jet info
    valid_jet_input = pd_valid_input.filter( items=jet_var )
    valid_jet_input = np.array( valid_jet_input )
    valid_jet_input = valid_jet_input.reshape( valid_jet_input.shape[0], njets, -1 )

    #print(train_event_input.shape)
    #print(train_jet_input.shape)
    #return train_event_input, train_event_label, train_jet_input, valid_event_input, valid_event_label, valid_jet_input
    return train_event_input, pd_train_label, train_event_label, train_jet_input, valid_event_input, pd_valid_label, valid_event_label, valid_jet_input


def build_model(model_path):
    Inputs = [ Input( shape=(train_event_input.shape[1],) ), Input( shape=(train_jet_input.shape[1], train_jet_input.shape[2]), ) ]
    
    dropout = 0.1
    nodes = 100
    #nodes = 200
    # BatchNormalization
    event_info = BatchNormalization( name = 'event_input_batchnorm' )(Inputs[0])
    jets = BatchNormalization( name = 'jet_input_batchnorm' )(Inputs[1])
    
    # Dense for event
    event_info = Dense(nodes, activation='relu', name='event_layer1')(event_info)
    event_info = Dropout(dropout)(event_info)
    event_info = Dense(nodes, activation='relu', name='event_layer2')(event_info)
    event_info = Dropout(dropout)(event_info)
    event_info = Dense(nodes, activation='relu', name='event_layer3')(event_info)
    event_info = Dropout(dropout)(event_info)
    
    # CNN for jet
    jets = Conv1D(150, 1, kernel_initializer='lecun_uniform',  activation='relu', name='jets_conv0')(jets)
    jets = Dropout(dropout)(jets)
    jets = Conv1D(100, 1, kernel_initializer='lecun_uniform',  activation='relu', name='jets_conv1')(jets)
    jets = Dropout(dropout)(jets)
    jets = Conv1D(100, 1, kernel_initializer='lecun_uniform',  activation='relu', name='jets_conv2')(jets)
    jets = Dropout(dropout)(jets)
    jets = Conv1D(25, 1, kernel_initializer='lecun_uniform',  activation='relu', name='jets_conv3')(jets)
    jets = Dropout(dropout)(jets)
    jets = Conv1D(25, 1, kernel_initializer='lecun_uniform',  activation='relu', name='jets_conv4')(jets)
    jets = Dropout(dropout)(jets)
    jets = LSTM(10, go_backwards=True, implementation=2, name='jets_lstm')(jets)
    
    # Concatenate
    x = Concatenate()( [event_info, jets] )
    x = Dense(10, activation='relu',kernel_initializer='lecun_uniform', name='concat_layer')(x)
    
    #pred_dense = Dense(1, activation='sigmoid', kernel_initializer='lecun_uniform', name='event_prediction' )(x)
    pred_dense = Dense(3, activation='softmax', kernel_initializer='lecun_uniform', name='event_prediction' )(x)
    model = Model(inputs=Inputs, outputs= pred_dense)
    #model.compile(loss='binary_crossentropy', optimizer = 'adam', metrics=['accuracy','binary_accuracy'])
    model.compile(loss='categorical_crossentropy', optimizer = 'adam', metrics=['accuracy'])
    model.save(model_path)
    print ('>>> This model is saved in ', model_path)
    
    return model

# variables
# from DNN
#name_inputvar=['nseljets', 'nselbjets', 'goodht', 'relht', 'mindR_dRbb', 'mindR_mbb', 'jet1_eta', 'jet2_eta', 'jet3_eta', 'jet4_eta', 'jet5_eta', 'bjet1_eta', 'bjet2_eta', 'jet1_e_massnom', 'jet2_e_massnom', 'jet3_e_massnom', 'jet4_e_massnom', 'jet5_e_massnom', 'bjet1_e_massnom', 'bjet2_e_massnom', 'Chi2_max', 'Chi2_min', 'Chi2_min_H', 'Chi2_min_W', 'Chi2_min_Top', 'mass_h', 'mass_w', 'mass_top', 'mass_wh', 'mass_secondtop', 'mass_leadjets', 'dR_hbb', 'dR_wjj', 'dR_bw', 'dR_tprimeoj', 'ratio_mass_topH', 'ratio_mass_secondtopW', 'ratio_pt_topsecondtop', 'ratio_pt_htoptprime', 'ratio_pt_tprimehtprimetop']
event_var=['nseljets', 'nselbjets', 'goodht', 'relht', 'mindR_dRbb', 'mindR_mbb', 'Chi2_max', 'Chi2_min', 'Chi2_min_H', 'Chi2_min_W', 'Chi2_min_Top', 'mass_h', 'mass_w', 'mass_top', 'mass_wh', 'mass_secondtop', 'mass_leadjets', 'dR_hbb', 'dR_wjj', 'dR_bw', 'dR_tprimeoj', 'ratio_mass_topH', 'ratio_mass_secondtopW', 'ratio_pt_topsecondtop', 'ratio_pt_htoptprime', 'ratio_pt_tprimehtprimetop']
jet_var=['jet1_eta', 'jet1_e_massnom', 'jet2_eta', 'jet2_e_massnom', 'jet3_eta', 'jet3_e_massnom', 'jet4_eta', 'jet4_e_massnom', 'jet5_eta', 'jet5_e_massnom']

nvar = len(event_var+jet_var)
model_name = 'model_reproduce_cnn_2M1L'

# read input
#data = pd.read_hdf("/Users/jieun/WORK/vlq/dnn/array/arrayOut/ana/multi/2M1L/train_121/array_trainInput.h5")
dat_qcd = pd.read_hdf("/Users/jieun/WORK/vlq/dnn/array/arrayOut/ana/multi/2M1L/train_121/array_merged_qcd.h5")
dat_ttbar = pd.read_hdf("/Users/jieun/WORK/vlq/dnn/array/arrayOut/ana/multi/2M1L/train_121/array_merged_ttbar.h5")
dat_tprime = pd.read_hdf("/Users/jieun/WORK/vlq/dnn/array/arrayOut/ana/multi/2M1L/train_121/array_merged_tprime.h5")

data = pd.concat([dat_qcd,dat_ttbar,dat_tprime],axis=0)
data = data.sample(frac=1).reset_index(drop=True)

weights = compute_class_weight( class_weight='balanced', classes=np.unique(data['signal']), y=data['signal'])
print(f"computed weights = {weights}")
dic_weights = dict(enumerate(weights))
print(f"computed dic weights = {dic_weights}")
model_path = 'models/'+model_name

ver = "model1"
newDir = model_path+ver
if os.path.exists( newDir ):
    string = re.split(r'(\d+)', ver)[0]
    num = int( re.split(r'(\d+)', ver)[1] )
    while os.path.exists( newDir ):
        num = num+1
        newDir = model_path+string+str(num)
print ('>>> Results directory: ', newDir)
os.makedirs( newDir )

data = data.reset_index()
train_event_input, pd_train_label, train_event_label, train_jet_input, valid_event_input, pd_valid_label, valid_event_label, valid_jet_input = split_train_test()

train_label = train_event_label
valid_label = valid_event_label

model = build_model(model_path)

earlystop = EarlyStopping(monitor='val_loss', patience=20)
filename = os.path.join(newDir, 'best_model.h5')

checkpoint = ModelCheckpoint(filename, monitor='val_loss', verbose=1, save_best_only=True, mode='auto')
hist = model.fit([train_event_input,train_jet_input], train_label, batch_size=1024, epochs=epochs, validation_data=([valid_event_input, valid_jet_input],  valid_label), callbacks=[earlystop, checkpoint], class_weight=dic_weights)
model.summary()

# copy this code for saving structure - TODO to make it simpler
shutil.copy('train_cnn.py',newDir)

# find best epoch
check_loss = model.history.history['val_loss']
bestepoch = np.argmin( check_loss )+1 

model.load_weights( filename )

valid_prediction = model.predict( [valid_event_input, valid_jet_input], batch_size=2048 )
train_prediction = model.predict( [train_event_input, train_jet_input], batch_size=2048 )

pred_data = pd.DataFrame(train_prediction, columns=['pred_QCD','pred_TTbar','pred_Tprime'])
pred_val_data = pd.DataFrame(valid_prediction, columns=['pred_QCD','pred_TTbar','pred_Tprime'])

pred = pd.concat([pred_data,pd_train_label],axis=1)
pred_val = pd.concat([pred_val_data,pd_valid_label],axis=1)

# pred jet & real jet
pred_val_max = np.argmax( valid_prediction, axis=1 )
real_val_label = np.argmax( valid_label, axis=1 )

confusion = confusion_matrix(real_val_label, pred_val_max)
correct = confusion.trace()
sum_row = confusion.sum(axis=1)[:, np.newaxis]
accuracy = correct/len(valid_label)*100

#######################################################################
#                          Plot loss curve                            # 
#######################################################################
plotDir = newDir+'/'
print("Plotting scores")

plt.plot(hist.history['accuracy'])
plt.plot(hist.history['val_accuracy'])
plt.title('Accuracy')
plt.ylabel('Accuracy')
plt.xlabel('Epochs')
plt.legend(['Train','Valid'], loc='lower right')
plt.savefig(os.path.join(plotDir, 'accuracy.pdf'), bbox_inches='tight')
plt.gcf().clear()

plt.plot(hist.history['loss'])
plt.plot(hist.history['val_loss'])
plt.title('Binary crossentropy')
plt.ylabel('Loss')
plt.xlabel('Epochs')
plt.legend(['Train','Valid'],loc='upper right')
plt.savefig(os.path.join(plotDir, 'loss.pdf'), bbox_inches='tight')
plt.gcf().clear()

#######################################################################
#                           Plot ROC curve                            # 
#######################################################################
fpr = dict()
tpr = dict()
roc_auc = dict()

cat_valid_label = pd.DataFrame(valid_label, columns=['QCD','TTbar','Tprime'])
cat_train_label = pd.DataFrame(train_label, columns=['QCD','TTbar','Tprime'])

fpr[1], tpr[1], thresholds1 = roc_curve(cat_valid_label['Tprime'].tolist(), pred_val_data['pred_Tprime'].values.tolist(), pos_label=1)#w.r.t sig is truth in val set
fpr[2], tpr[2], thresholds2 = roc_curve(cat_train_label['Tprime'].tolist(), pred_data['pred_Tprime'].values.tolist(), pos_label=1)#w.r.t sig is truth in training set, for overtraining check
roc_auc_val = roc_auc_score(cat_valid_label['Tprime'].tolist(),pred_val_data['pred_Tprime'].values.tolist())
roc_auc_train = roc_auc_score(cat_train_label['Tprime'].tolist(),pred_data['pred_Tprime'].values.tolist())

print("Tprime AUC on valid: "+str(roc_auc_val))
print("Tprime AUC on train: "+str(roc_auc_train))
plt.plot(tpr[1], 1-fpr[1])#HEP style ROC
plt.plot(tpr[2], 1-fpr[2])#training ROC

pd.DataFrame(tpr[1]).to_csv(f'models/{model_name}/tpr_validation_tprime.csv')
pd.DataFrame(fpr[1]).to_csv(f'models/{model_name}/fpr_validation_tprime.csv')

plt.xlabel('Signal Efficiency')
plt.ylabel('Background Rejection')
plt.title('ROC Curve for Tprime')
plt.legend(['Valid', 'Train'], loc='lower left')
plt.savefig(os.path.join(os.path.join("models/"+model_name+'/','fig_score_roc_tprime.pdf')))
plt.gcf().clear()
print('ROC curve is saved!')

########################## QCD and TTbar ##############################
fpr[3], tpr[3], thresholds3 = roc_curve(cat_valid_label['QCD'].tolist(), pred_val_data['pred_QCD'].values.tolist(), pos_label=1)#w.r.t sig is truth in val set
fpr[4], tpr[4], thresholds4 = roc_curve(cat_train_label['QCD'].tolist(), pred_data['pred_QCD'].values.tolist(), pos_label=1)#w.r.t sig is truth in training set, for overtraining check
roc_auc_val_qcd = roc_auc_score(cat_valid_label['QCD'].tolist(),pred_val_data['pred_QCD'].values.tolist())
roc_auc_train_qcd = roc_auc_score(cat_train_label['QCD'].tolist(),pred_data['pred_QCD'].values.tolist())

fpr[5], tpr[5], thresholds5 = roc_curve(cat_valid_label['TTbar'].tolist(), pred_val_data['pred_TTbar'].values.tolist(), pos_label=1)#w.r.t sig is truth in val set
fpr[6], tpr[6], thresholds6 = roc_curve(cat_train_label['TTbar'].tolist(), pred_data['pred_TTbar'].values.tolist(), pos_label=1)#w.r.t sig is truth in training set, for overtraining check
roc_auc_val_ttbar = roc_auc_score(cat_valid_label['TTbar'].tolist(),pred_val_data['pred_TTbar'].values.tolist())
roc_auc_train_ttbar = roc_auc_score(cat_train_label['TTbar'].tolist(),pred_data['pred_TTbar'].values.tolist())

print("QCD AUC on valid: "+str(roc_auc_val_qcd))
print("QCD AUC on train: "+str(roc_auc_train_qcd))
plt.plot(tpr[3], 1-fpr[3])#HEP style ROC
plt.plot(tpr[4], 1-fpr[4])#training ROC

pd.DataFrame(tpr[3]).to_csv(f'models/{model_name}/tpr_validation_qcd.csv')
pd.DataFrame(fpr[3]).to_csv(f'models/{model_name}/fpr_validation_qcd.csv')

plt.xlabel('Signal Efficiency')
plt.ylabel('Background Rejection')
plt.title('QCD ROC Curve')
plt.legend(['Valid', 'Train'], loc='lower left')
plt.savefig(os.path.join("models/"+model_name+'/','fig_score_roc_qcd.pdf'))
plt.gcf().clear()

print("TTbar AUC on valid: "+str(roc_auc_val_ttbar))
print("TTbar AUC on train: "+str(roc_auc_train_ttbar))
plt.plot(tpr[5], 1-fpr[5])#HEP style ROC
plt.plot(tpr[6], 1-fpr[6])#training ROC

pd.DataFrame(tpr[5]).to_csv(f'models/{model_name}/tpr_validation_ttbar.csv')
pd.DataFrame(fpr[5]).to_csv(f'models/{model_name}/fpr_validation_ttbar.csv')

plt.xlabel('Signal Efficiency')
plt.ylabel('Background Rejection')
plt.title('TTbar ROC Curve')
plt.legend(['Valid', 'Train'], loc='lower left')
plt.savefig(os.path.join("models/"+model_name+'/','fig_score_roc_ttbar.pdf'))
plt.gcf().clear()
print('ROC curve for background are saved!')

#######################################################################

#######################################################################
#       Overtraining Check, as well as bkg & sig discrimination       # 
#######################################################################
nbins=40

scores = [tpr[1], fpr[1], tpr[2], fpr[2]]
low = min(np.min(d) for d in scores)
high = max(np.max(d) for d in scores)
low_high = (low,high)

# train set is filled
plt.hist(tpr[2],
    color='b', alpha=0.5, range=low_high, bins=nbins,
    histtype='stepfilled', density=True, label='TPR (train)')
plt.hist(fpr[2],
    color='r', alpha=0.5, range=low_high, bins=nbins,
    histtype='stepfilled', density=True, label='FPR (train)')

# valid set is dotted
hist, bins = np.histogram(tpr[1], bins=nbins, range=low_high, density=True)
scale = len(tpr[1]) / sum(hist)
err = np.sqrt(hist * scale) / scale
width = (bins[1] - bins[0])
center = (bins[:-1] + bins[1:]) / 2
plt.errorbar(center, hist, yerr=err, fmt='o', c='b', label='TPR (valid)')
hist, bins = np.histogram(fpr[1], bins=nbins, range=low_high, density=True)
scale = len(tpr[1]) / sum(hist)
err = np.sqrt(hist * scale) / scale
plt.errorbar(center, hist, yerr=err, fmt='o', c='r', label='FPR (valid)')

plt.xlabel("Tprime Seperation Score")
plt.ylabel("Arbitrary units")
plt.legend(loc='best')
plt.savefig(os.path.join("models/"+model_name+'/','fig_sep_score_overtraining_tprime.pdf'))
plt.gcf().clear()
print('Overtraining check plot is saved!')

scores = [tpr[3], fpr[3], tpr[4], fpr[4]]
low = min(np.min(d) for d in scores)
high = max(np.max(d) for d in scores)
low_high = (low,high)

# train set is filled
plt.hist(tpr[4],
    color='b', alpha=0.5, range=low_high, bins=nbins,
    histtype='stepfilled', density=True, label='TPR (train)')
plt.hist(fpr[4],
    color='r', alpha=0.5, range=low_high, bins=nbins,
    histtype='stepfilled', density=True, label='FPR (train)')

# valid set is dotted
hist, bins = np.histogram(tpr[3], bins=nbins, range=low_high, density=True)
scale = len(tpr[3]) / sum(hist)
err = np.sqrt(hist * scale) / scale
width = (bins[1] - bins[0])
center = (bins[:-1] + bins[1:]) / 2
plt.errorbar(center, hist, yerr=err, fmt='o', c='b', label='TPR (valid)')
hist, bins = np.histogram(fpr[3], bins=nbins, range=low_high, density=True)
scale = len(tpr[3]) / sum(hist)
err = np.sqrt(hist * scale) / scale
plt.errorbar(center, hist, yerr=err, fmt='o', c='r', label='FPR (valid)')

plt.xlabel("QCD Seperation Score")
plt.ylabel("Arbitrary units")
plt.legend(loc='best')
plt.savefig(os.path.join("models/"+model_name+'/','fig_sep_score_overtraining_qcd.pdf'))
plt.gcf().clear()

scores = [tpr[5], fpr[5], tpr[6], fpr[6]]
low = min(np.min(d) for d in scores)
high = max(np.max(d) for d in scores)
low_high = (low,high)

# train set is filled
plt.hist(tpr[6],
    color='b', alpha=0.5, range=low_high, bins=nbins,
    histtype='stepfilled', density=True, label='TPR (train)')
plt.hist(fpr[6],
    color='r', alpha=0.5, range=low_high, bins=nbins,
    histtype='stepfilled', density=True, label='FPR (train)')

# valid set is dotted
hist, bins = np.histogram(tpr[5], bins=nbins, range=low_high, density=True)
scale = len(tpr[5]) / sum(hist)
err = np.sqrt(hist * scale) / scale
width = (bins[1] - bins[0])
center = (bins[:-1] + bins[1:]) / 2
plt.errorbar(center, hist, yerr=err, fmt='o', c='b', label='TPR (valid)')
hist, bins = np.histogram(fpr[5], bins=nbins, range=low_high, density=True)
scale = len(tpr[5]) / sum(hist)
err = np.sqrt(hist * scale) / scale
plt.errorbar(center, hist, yerr=err, fmt='o', c='r', label='FPR (valid)')

plt.xlabel("TTbar Seperation Score")
plt.ylabel("Arbitrary units")
plt.legend(loc='best')
plt.savefig(os.path.join("models/"+model_name+'/','fig_sep_score_overtraining_ttbar.pdf'))
plt.gcf().clear()

print('Overtraining check plot for background are saved!')

#######################################################################
#       Overtraining Check v2, see the prediction scores only         # 
#######################################################################

# draw prediction scores from the original label = pred['signal']
pred_train_yQCD = pred['pred_QCD'].loc[pred['signal'] == 0]
pred_train_nQCD = pred['pred_QCD'].loc[pred['signal'] != 0]
pred_valid_yQCD = pred_val['pred_QCD'].loc[pred_val['signal'] == 0]
pred_valid_nQCD = pred_val['pred_QCD'].loc[pred_val['signal'] != 0]

scores = [pred_train_yQCD, pred_train_nQCD, pred_valid_yQCD, pred_valid_nQCD]
low = min(np.min(d) for d in scores)
high = max(np.max(d) for d in scores)
low_high = (low,high)

plt.hist([pred_train_yQCD,pred_train_nQCD],
          label=['S (train)','B (train)'],
          color=['b','r'], alpha=0.5,
          histtype='stepfilled', density=True, bins=nbins, range=low_high)

hist, bins = np.histogram(pred_train_yQCD, bins=nbins, range=low_high, density=True)
scale = len(pred_train_yQCD) / sum(hist)
err = np.sqrt(hist * scale) / scale
width = (bins[1] - bins[0])
center = (bins[:-1] + bins[1:]) / 2
plt.errorbar(center, hist, yerr=err, fmt='o', c='b', label='S (valid)')
hist, bins = np.histogram(pred_train_nQCD, bins=nbins, range=low_high, density=True)
scale = len(pred_train_nQCD) / sum(hist)
err = np.sqrt(hist * scale) / scale
plt.errorbar(center, hist, yerr=err, fmt='o', c='r', label='B (valid)')

plt.xlabel("QCD Prediction Score")
plt.ylabel("Normalized Entries")
plt.legend(loc='best')
plt.savefig(os.path.join("models/"+model_name+'/','fig_pred_score_qcd.pdf'))
plt.gcf().clear()

pred_train_yTTbar = pred['pred_TTbar'].loc[pred['signal'] == 1]
pred_train_nTTbar = pred['pred_TTbar'].loc[pred['signal'] != 1]
pred_valid_yTTbar = pred_val['pred_TTbar'].loc[pred_val['signal'] == 1]
pred_valid_nTTbar = pred_val['pred_TTbar'].loc[pred_val['signal'] != 1]

scores = [pred_train_yTTbar, pred_train_nTTbar, pred_valid_yTTbar, pred_valid_nTTbar]
low = min(np.min(d) for d in scores)
high = max(np.max(d) for d in scores)
low_high = (low,high)

plt.hist([pred_train_yTTbar,pred_train_nTTbar],
          label=['S (train)','B (train)'],
          color=['b','r'], alpha=0.5,
          histtype='stepfilled', density=True, bins=nbins, range=low_high)

hist, bins = np.histogram(pred_train_yTTbar, bins=nbins, range=low_high, density=True)
scale = len(pred_train_yTTbar) / sum(hist)
err = np.sqrt(hist * scale) / scale
width = (bins[1] - bins[0])
center = (bins[:-1] + bins[1:]) / 2
plt.errorbar(center, hist, yerr=err, fmt='o', c='b', label='S (valid)')
hist, bins = np.histogram(pred_train_nTTbar, bins=nbins, range=low_high, density=True)
scale = len(pred_train_nTTbar) / sum(hist)
err = np.sqrt(hist * scale) / scale
plt.errorbar(center, hist, yerr=err, fmt='o', c='r', label='B (valid)')

plt.xlabel("TTbar Prediction Score")
plt.ylabel("Normalized Entries")
plt.legend(loc='best')
plt.savefig(os.path.join("models/"+model_name+'/','fig_pred_score_ttbar.pdf'))
plt.gcf().clear()

pred_train_yTprime = pred['pred_Tprime'].loc[pred['signal'] == 2]
pred_train_nTprime = pred['pred_Tprime'].loc[pred['signal'] != 2]
pred_valid_yTprime = pred_val['pred_Tprime'].loc[pred_val['signal'] == 2]
pred_valid_nTprime = pred_val['pred_Tprime'].loc[pred_val['signal'] != 2]

scores = [pred_train_yTprime, pred_train_nTprime, pred_valid_yTprime, pred_valid_nTprime]
low = min(np.min(d) for d in scores)
high = max(np.max(d) for d in scores)
low_high = (low,high)

plt.hist([pred_train_yTprime,pred_train_nTprime],
          label=['S (train)','B (train)'],
          color=['b','r'], alpha=0.5,
          histtype='stepfilled', density=True, bins=nbins, range=low_high)

hist, bins = np.histogram(pred_train_yTprime, bins=nbins, range=low_high, density=True)
scale = len(pred_train_yTprime) / sum(hist)
err = np.sqrt(hist * scale) / scale
width = (bins[1] - bins[0])
center = (bins[:-1] + bins[1:]) / 2
plt.errorbar(center, hist, yerr=err, fmt='o', c='b', label='S (valid)')
hist, bins = np.histogram(pred_train_nTprime, bins=nbins, range=low_high, density=True)
scale = len(pred_train_nTprime) / sum(hist)
err = np.sqrt(hist * scale) / scale
plt.errorbar(center, hist, yerr=err, fmt='o', c='r', label='B (valid)')

plt.xlabel("Tprime Prediction Score")
plt.ylabel("Normalized Entries")
plt.legend(loc='best')
plt.savefig(os.path.join("models/"+model_name+'/','fig_pred_score_tprime.pdf'))
plt.gcf().clear()


# time
tm = localtime(time())
strtm = strftime('%Y-%m-%d %I:%M:%S %p', tm) 

print ('writing results...')

nqcd_train = len(pd_train_label['signal'] == 0)
ntt_train = len(pd_train_label['signal'] == 1)
ntp_train = len(pd_train_label['signal'] == 2)

nqcd_valid = len(pd_valid_label['signal'] == 0)
ntt_valid = len(pd_valid_label['signal'] == 1)
ntp_valid = len(pd_valid_label['signal'] == 2)

with open(f'{plotDir}/results.txt', "a") as f_log:
   f_log.write('###  '+strtm+'\n')
   f_log.write('Number of input variables: '+str(nvar)+'\n')
   f_log.write('Training samples: '+str(len(train_label))+'  validation samples: '+str(len(valid_label))+'\n')

   f_log.write(f'Training   :: QCD : {nqcd_train} | TT : {ntt_train} | Tprime: {ntp_train}\n')
   f_log.write(f'Validation :: QCD : {nqcd_valid} | TT : {ntt_valid} | Tprime: {ntp_valid}\n')

   f_log.write('Best epoch: '+str(bestepoch)+'  accuracy: '+str(correct)+'/'+str(len(valid_label))+'='+str(accuracy)+'\n\n')
   f_log.write('AUC on valid: '+str(roc_auc_val)+'  train: '+str(roc_auc_train)+'\n')

print("Training complete!")
