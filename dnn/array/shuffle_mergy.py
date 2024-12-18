import sys, os
import pandas as pd
import deepdish.io as io
import math

def merge_train(arrayDir):

    selEvent_train = pd.DataFrame([])
    selEvent_eval = pd.DataFrame([])

    selEvent_sig = pd.DataFrame([])
    selEvent_qcd = pd.DataFrame([])
    selEvent_ttbar = pd.DataFrame([])

    cut = 0
    print(f"merge processes for training")
    print(f"Tprime first")

    for process in os.listdir(arrayDir+'/merged/'):
        print(process)
        inFile = arrayDir + '/merged/' + process

        df = pd.read_hdf(inFile)
        if "Tprime" in process : selEvent_sig = pd.concat([selEvent_sig,df], axis=0)
        if "QCD" in process : selEvent_qcd = pd.concat([selEvent_qcd,df], axis=0)
        if "TT" in process : selEvent_ttbar = pd.concat([selEvent_ttbar,df], axis=0)

    # then shuffle those
    selEvent_sig = selEvent_sig.sample(frac=1).reset_index(drop=True)
    selEvent_qcd = selEvent_qcd.sample(frac=1).reset_index(drop=True)
    selEvent_ttbar = selEvent_ttbar.sample(frac=1).reset_index(drop=True)

    # total length for the moment
    print(f"total length of Tprime: {len(selEvent_sig)}")
    print(f"total length of TTbar {len(selEvent_ttbar)}")
    print(f"total length of QCD {len(selEvent_qcd)}")

    # to make it more generic - in case bkg is lacking
    eventList = [selEvent_sig,selEvent_qcd,selEvent_ttbar]
    min_length = min(len(x) for x in eventList)
    min_List = min(eventList, key=len)
    print(f"minimum length = {min_length}")

    # then cut on length of tprime
    # cut = len(selEvent_sig.index)
    # alternatively, we can do half of it -> other half for evaluation
    #cut = len(selEvent_sig.index) / 2
    #cut = math.ceil(cut)
    cut = min_length * 0.8
    cut = math.ceil(cut)

    print(f"length * 0.8 = {cut}")
    selEvent_sig_train = selEvent_sig[:cut]
    selEvent_qcd_train = selEvent_qcd[:cut]
    selEvent_ttbar_train = selEvent_ttbar[:cut*2]

    selEvent_sig_eval = selEvent_sig[cut:]
    selEvent_qcd_eval = selEvent_qcd[cut:]
    selEvent_ttbar_eval = selEvent_ttbar[cut*2:]

    selEvent_train = pd.concat([selEvent_sig_train,selEvent_qcd_train,selEvent_ttbar_train], axis=0)
    selEvent_train.reset_index(drop=True, inplace=True)

    selEvent_eval = pd.concat([selEvent_sig_eval,selEvent_qcd_eval,selEvent_ttbar_eval], axis=0)
    selEvent_eval.reset_index(drop=True, inplace=True)

    # eh then shuffle again?
    selEvent_train = selEvent_train.sample(frac=1).reset_index(drop=True) 
    selEvent_eval = selEvent_eval.sample(frac=1).reset_index(drop=True) 

    counts = selEvent_train['signal'].value_counts()
    print("Number of events:")
    print(f"Tprime = {counts.get(2,0)}")
    print(f"TTbar  = {counts.get(1,0)}")
    print(f"QCD    = {counts.get(0,0)}")

    #io.save(arrayDir+"array_trainInput.h5",selEvent_train)
    #io.save(arrayDir+"array_evaluationSet.h5",selEvent_eval)

    # I dont understand
    io.save(arrayDir+"array_merged_ttbar.h5",selEvent_ttbar)
    io.save(arrayDir+"array_merged_qcd.h5",selEvent_qcd)
    io.save(arrayDir+"array_merged_tprime.h5",selEvent_sig)

Dir = "/sps/lyon/jechoi/tprimeHad/2018/"
cat = ['2M1L','3M','3T']

for c in cat:
    arrayDir = Dir + c + "/array/"
    merge_train(arrayDir)
