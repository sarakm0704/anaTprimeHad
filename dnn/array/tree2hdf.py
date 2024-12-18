#! /usr/bin/env python3
import sys, os
import numpy as np
from ROOT import *
import pandas as pd
import deepdish.io as io

def random(arrayDir,target):

    print("shuffle input datasets..")

    df = pd.read_hdf(arrayDir+target)
    print("from:\n" + str(df['signal']))
    df = df.sample(frac=1).reset_index(drop=True)
    print("To:\n" + str(df['signal']))
    io.save(arrayDir+"array_trainInput_shuffled.h5",df)
    print("Done")

def merge(arraydir):

    selevent = pd.dataframe([])

    #for process in os.listdir(arraydir+'/split/'):
    for process in os.listdir(arraydir+'/merged/'):
        print(process)
        infile = arraydir + '/merged/' + process
        print("merge process " + process[:-3] + " for training")
        df = pd.read_hdf(infile)
        if "tprime" in process: cut = len(df.index)
        #max_nevt_num = 0
        #if df.size != 0: last = len(df.index)
        #df['event'] = df['event'] + max_nevt_num
        if not "tprime" in process: df = df[:cut]
        selevent = pd.concat([selevent,df], axis=0)
        #max_nevt_num += last

    selevent.reset_index(drop=true, inplace=true)
    print(selevent)
    io.save(arraydir+"array_traininput.h5",selevent)

def merge_proc(arrayDir):

    proc = ["QCD_HT1000to1500_BGenFilter","QCD_HT100to200_BGenFilter","QCD_HT1500to2000_BGenFilter","QCD_HT2000toInf_BGenFilter","QCD_HT200to300_BGenFilter","QCD_HT300to500_BGenFilter","QCD_HT500to700_BGenFilter","QCD_HT700to1000_BGenFilter","QCD_bEnriched_HT1000to1500","QCD_bEnriched_HT100to200","QCD_bEnriched_HT1500to2000","QCD_bEnriched_HT2000toInf","QCD_bEnriched_HT200to300","QCD_bEnriched_HT300to500","QCD_bEnriched_HT500to700","QCD_bEnriched_HT700to1000","TTToHadronic","Tprime1000","Tprime1100","Tprime1200","Tprime600","Tprime700","Tprime800","Tprime900"]

    for p in proc:
        selEvent = pd.DataFrame([])
        print(f"merge all sets process {p}")
        for process in os.listdir(arrayDir+'/split/'):
            if not p in process: continue

            inFile = arrayDir + '/split/' + process

            df = pd.read_hdf(inFile)
            max_nevt_num = 0
            if df.size != 0: last = len(df.index)
            df['event'] = df['event'] + max_nevt_num
            selEvent = pd.concat([selEvent,df], axis=0)
            max_nevt_num += last

        selEvent.reset_index(drop=True, inplace=True)
        print(selEvent)
        io.save(arrayDir+"merged/array_"+p+".h5",selEvent)

def merge_train(arrayDir):

    selEvent = pd.DataFrame([])

    proc = ["Tprime","TTToHadronic","QCD"]
    cut = 0
    for p in proc:
        print(f"merge processes for training")
        for process in os.listdir(arrayDir+'/merged/'):
            if not p in process: continue

            print(process)
            inFile = arrayDir + '/merged/' + process

            df = pd.read_hdf(inFile)
            print(f"length {len(df.index)}")
            if "Tprime" in p :
                last = len(df.index)
                cut += last
                print(f"signal length = {cut}")
            if not "Tprime" in p :
                df = df[:cut]
                print(f"and all length now? {len(df.index)}")

            selEvent = pd.concat([selEvent,df], axis=0)

    selEvent.reset_index(drop=True, inplace=True)
    #print(selEvent)
    counts = selEvent['signal'].value_counts()
    print("Number of events:")
    print(f"Tprime = {counts.get(2,0)}")
    print(f"TTbar  = {counts.get(1,0)}")
    print(f"QCD    = {counts.get(0,0)}")
    io.save(arrayDir+"array_trainInput.h5",selEvent)

def makeCombi(inputDir, proc, inputFile, outputDir, makeTrainingInput=False):

    print(str(inputDir+"/"+inputFile)+" start")
    chain = TChain("outputTree")
    chain.Add(inputDir+"/"+inputFile)

    # for later..
    #data = False
    #if 'Data' in inputDir: data = True

    jetCombi = []

    for i in range(chain.GetEntries()) :
        if chain.GetEntries() <= 0: continue
        chain.GetEntry(i)

        #if 'Tprime' in inputFile: signal = 2
        #if 'TT' in inputFile: signal = 1
        #if 'QCD' in inputFile: signal = 0
        if 'Tprime' in proc: signal = 2
        if 'TT' in proc: signal = 1
        if 'QCD' in proc: signal = 0

        event = i

        #if event > 100: continue
        #if event > 24124: continue # 3T Tpriem at Cut 0

        #if event > 5000: continue # 2M1L rough QCD cutting out

        evWeight = chain.evWeight

        nseljets = chain.nselJets
        nselbjets = chain.nselbJets

        jet1_pt = chain.selJet1_pt
        jet2_pt = chain.selJet2_pt
        jet3_pt = chain.selJet3_pt
        jet4_pt = chain.selJet4_pt
        jet5_pt = chain.selJet5_pt

        jet1_pt_massnom = chain.selJet1_pt_massnom
        jet2_pt_massnom = chain.selJet2_pt_massnom
        jet3_pt_massnom = chain.selJet3_pt_massnom
        jet4_pt_massnom = chain.selJet4_pt_massnom
        jet5_pt_massnom = chain.selJet5_pt_massnom

        jet1_eta = chain.selJet1_eta
        jet2_eta = chain.selJet2_eta
        jet3_eta = chain.selJet3_eta
        jet4_eta = chain.selJet4_eta
        jet5_eta = chain.selJet5_eta

        jet1_e = chain.selJet1_e
        jet2_e = chain.selJet2_e
        jet3_e = chain.selJet3_e
        jet4_e = chain.selJet4_e
        jet5_e = chain.selJet5_e

        jet1_e_massnom = chain.selJet1_e_massnom
        jet2_e_massnom = chain.selJet2_e_massnom
        jet3_e_massnom = chain.selJet3_e_massnom
        jet4_e_massnom = chain.selJet4_e_massnom
        jet5_e_massnom = chain.selJet5_e_massnom

        jet1_btag = chain.selJet1_btag
        jet2_btag = chain.selJet2_btag
        jet3_btag = chain.selJet3_btag
        jet4_btag = chain.selJet4_btag
        jet5_btag = chain.selJet5_btag

        bjet1_pt = chain.selbJet1_pt
        bjet2_pt = chain.selbJet2_pt

        bjet1_pt = chain.selbJet1_pt_massnom
        bjet2_pt = chain.selbJet2_pt_massnom

        bjet1_eta = chain.selbJet1_eta
        bjet2_eta = chain.selbJet2_eta

        bjet1_e = chain.selbJet1_e
        bjet2_e = chain.selbJet2_e

        bjet1_e_massnom = chain.selbJet1_e_massnom
        bjet2_e_massnom = chain.selbJet2_e_massnom

        bjet1_btag = chain.selbJet1_btag
        bjet2_btag = chain.selbJet2_btag

        goodht = chain.goodHT
        relht = chain.RelHT
        newrelht = chain.newRelHT

        mindR_dRbb = chain.mindR_dRbb
        mindR_mbb = chain.mindR_mbb

        Chi2_max = chain.Chi2_max
        Chi2_min = chain.Chi2_min
        Chi2_min_H = chain.Chi2_min_H
        Chi2_min_W = chain.Chi2_min_W
        Chi2_min_Top = chain.Chi2_min_Top

        dR_hbb = chain.dRHbb_chi2
        dR_wjj = chain.dRWjj_chi2
        dR_bw = chain.dRbW_chi2

        dR_tprimeoj = chain.dRTprimeoj_chi2
        dR_htop = chain.dRHTop_chi2
        dEta_wh = chain.dEtaWH_chi2
        dPhi_htop = chain.dPhiHTop_chi2

        mass_h = chain.H_mass
        mass_w = chain.W_mass
        mass_top = chain.Top_mass

        mass_wh = chain.invmass_WH
        mass_secondtop = chain.invmass_2ndTop
        mass_tprime = chain.invmass_Tprime
        mass_leadjets = chain.invmass_leadjets

        ratio_mass_topH = chain.R_TopH
        ratio_mass_secondtopW = chain.R_2ndTopW

        ratio_pt_topsecondtop = chain.Rpt_Top2ndTop
        ratio_pt_htoptprime = chain.Rpt_HTopTprime
        ratio_pt_tprimehtprimetop = chain.Rpt_TprimeHTprimeTop

        jetCombi.append([signal, event, nseljets, nselbjets, goodht, relht, mindR_dRbb, mindR_mbb, jet1_pt, jet2_pt, jet3_pt, jet4_pt, jet5_pt, jet1_eta, jet2_eta, jet3_eta, jet4_eta, jet5_eta, jet1_e, jet2_e, jet3_e, jet4_e, jet5_e, jet1_btag, jet2_btag, jet3_btag, jet4_btag, jet5_btag, bjet1_pt, bjet2_pt, bjet1_eta, bjet2_eta, bjet1_e, bjet2_e, bjet1_btag, bjet2_btag, jet1_pt_massnom, jet2_pt_massnom, jet3_pt_massnom, jet4_pt_massnom, jet5_pt_massnom, jet1_e_massnom, jet2_e_massnom, jet3_e_massnom, jet4_e_massnom, jet5_e_massnom, bjet1_e_massnom, bjet2_e_massnom, Chi2_max, Chi2_min, Chi2_min_H, Chi2_min_W, Chi2_min_Top, mass_h, mass_w, mass_top, mass_wh, mass_secondtop, mass_tprime, mass_leadjets, dR_hbb, dR_wjj, dR_bw, dR_tprimeoj, dR_htop, dEta_wh, dPhi_htop, ratio_mass_topH, ratio_mass_secondtopW, ratio_pt_topsecondtop, ratio_pt_htoptprime, ratio_pt_tprimehtprimetop, evWeight])

    tmp = inputFile[:-5]

    combi = pd.DataFrame(jetCombi,columns=['signal','event','nseljets','nselbjets','goodht','relht','mindR_dRbb','mindR_mbb','jet1_pt','jet2_pt','jet3_pt','jet4_pt','jet5_pt','jet1_eta','jet2_eta','jet3_eta','jet4_eta','jet5_eta','jet1_e','jet2_e','jet3_e','jet4_e','jet5_e','jet1_btag','jet2_btag','jet3_btag','jet4_btag','jet5_btag','bjet1_pt','bjet2_pt','bjet1_eta','bjet2_eta','bjet1_e','bjet2_e','bjet1_btag','bjet2_btag','jet1_pt_massnom','jet2_pt_massnom','jet3_pt_massnom','jet4_pt_massnom','jet5_pt_massnom','jet1_e_massnom','jet2_e_massnom','jet3_e_massnom','jet4_e_massnom','jet5_e_massnom','bjet1_e_massnom','bjet2_e_massnom','Chi2_max','Chi2_min','Chi2_min_H','Chi2_min_W','Chi2_min_Top','mass_h','mass_w','mass_top','mass_wh','mass_secondtop','mass_tprime','mass_leadjets','dR_hbb','dR_wjj','dR_bw','dR_tprimeoj','dR_htop','dEta_wh','dPhi_htop','ratio_mass_topH','ratio_mass_secondtopW','ratio_pt_topsecondtop','ratio_pt_htoptprime','ratio_pt_tprimehtprimetop','evWeight'])

    if makeTrainingInput: combi = combi
    else: combi = combi.drop(['signal'], axis=1)

    print(combi['signal'])
    print(f"length: {len(combi['signal'])}")
    combi = pd.DataFrame(combi).fillna(-999)
    combi.replace(np.inf,999,inplace=True)

    if len(combi['signal']) > 0:
        io.save(outputDir+"split/array_"+proc+"_"+tmp+".h5",combi)
        print(str(inputDir+"/"+inputFile)+" end")
    else:
        print(f"{inputFile} has {len(combi['signal'])} entries. skip")

if __name__ == '__main__':
    #Options
    from optparse import OptionParser

    parser = OptionParser()
    parser.usage = """
    %prog [options] option
    convert root ntuple to array 
    """

    parser.add_option("-m", "--merge", dest="merge",
                      action = 'store_true',
                      default=False,
                      help='Merge array files for training')

    parser.add_option("-p", "--merge_proc", dest="merge_proc",
                      action = 'store_true',
                      default=False,
                      help='Merge array files for each process')

    parser.add_option("-t", "--merge_train", dest="merge_train",
                      action = 'store_true',
                      default=False,
                      help='Merge all for training')

    parser.add_option("-d", "--deep", dest="deep",
            		      action = 'store_true',
            		      default=False,
            		      help='Run on signal sample for deep learning train')
            
    parser.add_option("-a", "--all", dest="all",
            		      action = 'store_true',
            		      default=False,
            		      help='all root fiels in input directory')

    parser.add_option("-r", "--random", dest="random",
            		      action = 'store_true',
            		      default=False,
            		      help='shuffle row randomly')
            
    (options,args) = parser.parse_args()

    Dir = '/sps/lyon/jechoi/tprimeHad/2018/'
    cat = ['2M1L','3M','3T']
    tar = ['Tprime','TTToHadronic','QCD'] 

    for c in range(len(cat)):

        print(f"Region {cat[c]}")
        ntupleDir = Dir + cat[c] + "/"
        arrayDir = Dir + cat[c] + "/array/"

        processes = []
        if len(args) == 1:
            f = open(args[0], "r") 
            processes = f.read().splitlines()
        else:
            processes = os.listdir(ntupleDir)

        if options.merge:
            merge(arrayDir)

        if options.merge_proc:
            merge_proc(arrayDir)

        if options.merge_train:
            merge_train(arrayDir)

        if options.deep:

            print(f"ntupleDir = {ntupleDir}")
            for proc in processes:

                if not proc in tar:
                    print(f"double check skip data: {proc}")

                if not any(i in proc for i in tar):
                    print(f"skip data: {proc}")
                    continue

                print(proc)
                if not os.path.isdir(ntupleDir+proc): continue
                print("hello")
                items = os.listdir(ntupleDir+proc)
                for item in items:
                    makeCombi(ntupleDir+proc, proc, item, arrayDir, True)
                    #makeCombi(ntupleDir+proc, proc, arrayDir, True)

            #makeCombi(ntupleDir, 'Tprime600.root', arrayDir, True)
            #makeCombi(ntupleDir, 'Tprime700.root', arrayDir, True)
            #makeCombi(ntupleDir, 'Tprime800.root', arrayDir, True)
            #makeCombi(ntupleDir, 'Tprime900.root', arrayDir, True)
            #makeCombi(ntupleDir, 'Tprime1000.root', arrayDir, True)
            #makeCombi(ntupleDir, 'Tprime1100.root', arrayDir, True)
            #makeCombi(ntupleDir, 'Tprime1200.root', arrayDir, True)

            #makeCombi(ntupleDir, 'TTToHadronic.root', arrayDir, True)

            #makeCombi(ntupleDir, 'QCD_bEnriched_HT100to200.root', arrayDir, True)
            #makeCombi(ntupleDir, 'QCD_bEnriched_HT200to300.root', arrayDir, True)
            #makeCombi(ntupleDir, 'QCD_bEnriched_HT300to500.root', arrayDir, True)
            #makeCombi(ntupleDir, 'QCD_bEnriched_HT500to700.root', arrayDir, True)
            #makeCombi(ntupleDir, 'QCD_bEnriched_HT700to1000.root', arrayDir, True)
            #makeCombi(ntupleDir, 'QCD_bEnriched_HT1000to1500.root', arrayDir, True)
            #makeCombi(ntupleDir, 'QCD_bEnriched_HT1500to2000.root', arrayDir, True)
            #makeCombi(ntupleDir, 'QCD_bEnriched_HT2000toInf.root', arrayDir, True)

            #makeCombi(ntupleDir, 'QCD_HT100to200_BGenFilter.root', arrayDir, True)
            #makeCombi(ntupleDir, 'QCD_HT200to300_BGenFilter.root', arrayDir, True)
            #makeCombi(ntupleDir, 'QCD_HT300to500_BGenFilter.root', arrayDir, True)
            #makeCombi(ntupleDir, 'QCD_HT500to700_BGenFilter.root', arrayDir, True)
            #makeCombi(ntupleDir, 'QCD_HT700to1000_BGenFilter.root', arrayDir, True)
            #makeCombi(ntupleDir, 'QCD_HT1000to1500_BGenFilter.root', arrayDir, True)
            #makeCombi(ntupleDir, 'QCD_HT1500to2000_BGenFilter.root', arrayDir, True)
            #makeCombi(ntupleDir, 'QCD_HT2000toInf_BGenFilter.root', arrayDir, True)

        if options.random:
            random(arrayDir,"array_trainInput.h5")

        if options.all:
            for process in processes:
                    os.makedirs(arrayDir+process)

                    #proc = process.split(".")[0]
                    makeCombi(ntupleDir, process, arrayDir)
