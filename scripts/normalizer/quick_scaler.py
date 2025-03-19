import ROOT
from array import array
import os,sys
import time

inputDir = '/Users/jieun/WORK/vlq/dnn/strategy/score_efficiency/hists/'

targetDir = '/Users/jieun/WORK/vlq/dnn/strategy/score_efficiency/inputs/'
outputDir = '/Users/jieun/WORK/vlq/dnn/strategy/score_efficiency/outputs/'

def GetScale(inputDir, process):

    f = ROOT.TFile.Open(inputDir+process)
    #hist = f.Get('hnevents_nocut')
    # name changed
    hist = f.Get('h_nevents_nocut')
    evt = hist.Integral()
    count = hist.GetEntries()

    xsec = -1

    if "Tprime" in process:
      #br = 0.4 #tH to hadronic
      br = 1 # but the sample itself it doesnt count
      # https://www.hepdata.net/record/ins2636335
      if "600" in process:    xsec = 0.1764
      elif "700" in process:  xsec = 0.0886
      elif "800" in process:  xsec = 0.0459
      elif "900" in process:  xsec = 0.0251
      elif "1000" in process: xsec = 0.0145
      elif "1100" in process: xsec = 0.0086
      elif "1200" in process: xsec = 0.0053
      else: print(f"unknown mass point: {process}")

    elif "TTToHadronic" in process:
        #br = 0.67 * 0.67 * 4
        br = 0.67 * 0.67
        xsec =  833.9

    elif "QCD" in process:
      br = 1
      # from XSDB
      if "BGenFilter" in process:
          if "HT100to200" in process: xsec = 1266000.0
          elif "HT200to300" in process: xsec = 109900.0
          elif "HT300to500" in process: xsec = 27360.0
          elif "HT500to700" in process: xsec = 2991.0
          elif "HT700to1000" in process: xsec = 731.8
          elif "HT1000to1500" in process: xsec = 139.3
          elif "HT1500to2000" in process: xsec = 14.74
          elif "HT2000toInf" in process: xsec = 3.09
      elif "bEnriched" in process:
          if "HT100to200" in process: xsec = 1122000
          elif "HT200to300" in process: xsec = 79760.0
          elif "HT300to500" in process: xsec = 16600.0
          elif "HT500to700" in process: xsec = 1503.0
          elif "HT700to1000" in process: xsec = 297.4
          elif "HT1000to1500" in process: xsec = 48.08
          elif "HT1500to2000" in process: xsec = 3.951
          elif "HT2000toInf" in process: xsec = 0.6957

    elif "Jets" in process:
      br = 1

      if "WJets" in process:
        if "HT200to400" in process: xsec = 2546
        elif "HT400to600" in process: xsec = 275.4
        elif "HT600to800" in process: xsec = 59.55
        elif "HT800toInf" in process: xsec = 29.1

      elif "ZJets" in process:
        if "HT200to400" in process: xsec = 1002
        elif "HT400to600" in process: xsec = 116.4
        elif "HT600to800" in process: xsec = 25.47
        elif "HT800toInf" in process: xsec = 12.99

    elif "ST" in process:
      br = 1
      if "_tW" in process:
        if "_top" in process: xsec = 32.45
        elif "_antitop" in process: xsec = 32.51

      elif "_t" in process and "_tW" not in process:
        if "_top" in process: xsec = 113.4 
        if "_antitop" in process: xsec = 67.93

      elif "_s" in process: xsec = 7.104

    elif "ttHTobb" in process:
        br = 1
        xsec = 0.5269 

    else: print("I do not know this, what is this sample? "+str(process))

    print("  pretty-name: '"+str(process)+"'")
    print("  cross-section: "+str(xsec))
    print("  generated-events: "+str(evt))
    print("  generated-counts: "+str(count))
    
    lumi = 59741 # 2018

    scale = lumi * xsec * br / evt

    print(f"scale = {scale}")

    return scale

start_time = time.time()

print("Start processing")

for region in os.listdir(inputDir):

    if "round" in region: continue
    print(f"target region = {region}")

    for p in os.listdir(inputDir+region):

        process = p
        print(process)
        if "JetHT" in process: continue
        print("Start "+str(process))
        print(f"work on {inputDir}/{region}/{process}")
        sc = GetScale(inputDir+region+"/", process)
        print(sc)

#        f = ROOT.TFile.Open(inputDir+region+process)
#        nf = ROOT.TFile.Open(outputDir+region+"/hist_"+process, "RECREATE")
#
#        keys = [k.GetName() for k in f.GetListOfKeys()]
#        #print(keys)
#    
#        for key in keys:
#            hist = f.Get(key)
#            new_hist = hist.Clone(key)
#            new_hist.Scale(sc)
#            nf.cd()
#            new_hist.Write()
#            f.cd()

print("Done! Total running time :%s " %(time.time() - start_time))
