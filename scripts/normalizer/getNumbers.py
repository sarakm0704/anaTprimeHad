import ROOT
from array import array
import os,sys
import time
import math

inputDir = '/Users/jieun/WORK/vlq/dnn/strategy/score_efficiency/outputs/'
#inputDir = '/Users/jieun/WORK/vlq/plot/mytool/output/'

start_time = time.time()

print("Start processing")

for region in os.listdir(inputDir):

    if "round" in region: continue
    if ".sh" in region: continue
    if "pre" in region: continue
    print(f"target region = {region}")

    print("> > > Sensitivity")
    fs = ROOT.TFile.Open(f"{inputDir}/{region}/hist_Tprime700.root")
    fb = ROOT.TFile.Open(f"{inputDir}/{region}/hadd/hist_bkg.root")

    hkeys = [k.GetName() for k in fs.GetListOfKeys()]
    for h in hkeys:
        if not "mtprime" in h: continue
        hs = fs.Get(h)
        hb = fb.Get(h)
        nums = hs.Integral()
        numb = hb.Integral()
        sen = round(nums / math.sqrt(numb),4)
        print(f"sensitivity on {h} = {sen}")

    flist = [f"{inputDir}/{region}/hist_Tprime700.root",f"{inputDir}/{region}/hadd/hist_bkg.root",f"{inputDir}/{region}/hist_TTToHadronic.root",f"{inputDir}/{region}/hadd/hist_QCD.root"]

    for o in flist:
        print(f"Hi, lets go through the major one first. Running on: {o}")
        of = ROOT.TFile.Open(o)
        print("> > > Efficiencies")
        print("denominator = h_dnncut_mtprime")
        base = of.Get("h_dnncut_mtprime")
        denum = base.Integral()
 
        keys = [k.GetName() for k in of.GetListOfKeys()]

        for key in keys:
            if not "mtprime" in key: continue
            hist = of.Get(key)
            new_hist = hist.Clone(key)
            numbers = new_hist.Integral()
            print(f"numerator = {hist}")
            eff = round(numbers/denum,2)
            print(f"{eff}")
    
        for key in keys:
            #if "njets" in key: continue
            if not "mtprime" in key: continue
            hist = of.Get(key)
            new_hist = hist.Clone(key)
            numbers = new_hist.Integral()
            numbers = round(numbers,2)
            print(f"{hist} = {numbers}")

    for process in os.listdir(inputDir+region):
        if not ".root" in process: continue
        print("Start "+str(process))

        f = ROOT.TFile.Open(inputDir+region+'/'+process)

        keys = [k.GetName() for k in f.GetListOfKeys()]
    
        for key in keys:
            hist = f.Get(key)
            new_hist = hist.Clone(key)
            numbers = new_hist.Integral()
            print(f"{hist} = {numbers}")

print("Done! Total running time :%s " %(time.time() - start_time))
