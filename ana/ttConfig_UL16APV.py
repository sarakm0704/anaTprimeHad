"""
File contains job options 
"""

# options for Nanoaodrdframe
config = {
        # tree name of input file(s)
        'intreename': "Events",
        # tree name of output file(s) it cannot be the same as the input tree name or it'll crash
        'outtreename': "outputTree",
        #data year (2016,2017,2018)
        'year': 2015,
        # is ReReco or Ultra Legacy
        'runtype': 'UL',
        'datatype': -1,
        # sample descriptions
        'topPtReweight': "True",
        'topPtReweightsys': "none",
        'jecsys': "Total",
        'jersys': "none",
        'btagsys': "none",
        'btagsysuncorr': "none",
        #for correction
        # good json file
        'goodjson': 'data/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt',
        # pileup weight for MC
        'pileupfname': 'data/LUM/2016preVFP_UL/puWeights.json',
        'pileuptag': 'Collisions16_UltraLegacy_goldenJSON',
        # json filename for BTV correction
        'btvfname': 'data/BTV/2016preVFP_UL/btagging16pre.json',
        'fname_btagEff': 'data/BTV/2016preVFP_UL/2016APV_btagEff_VLQ_FH.json',
        'fname_btagRatio': 'data/BTV/2016preVFP_UL/2016APV_btagTF_VLQ_FH.json',
        # json file name for JERC
        'jercfname': 'data/JERC/jet_jerc16pre.json',
        # conbined correction type for jets
        'jerctag': 'Summer20UL16APV_JRV3_MC_PtResolution_AK4PFchs',
        # jet uncertainty 
        'jercunctag': 'Summer20UL16APV_JRV3_MC_ScaleFactor_AK4PFchs',
        'jercsys_total': 'Summer19UL16APV_V7_MC_Regrouped_Total_AK4PFchs'
        }

# processing options
procflags = {
        # how many jobs?
        'split': 30,
        # if False, one output file per input file, if True then one output file for everything
        'allinone': False, 
        # if True then skip existing analyzed files
        'skipold': True,
        # travel through the subdirectories and their subdirecties when processing.
        # becareful not to mix MC and real DATA in them.
        'recursive': True,
#        'recursive': False,
        # if False then only selected branches which is done in the .cpp file will be saved
        'saveallbranches': False,
        #How many input files?
        'nrootfiles': 0,
#        'nrootfiles': 1,
        }

# input directory where your input root tree resides
# output directory wheere your output should go
# dump of stderr/stdout to file
nanoaod_inputdir_outputdir_pairs = [
        ['filelist/list_Tprime700UL.txt','out/Tprime700UL','out/Tprime700UL/Tprime700UL.out'],
]

