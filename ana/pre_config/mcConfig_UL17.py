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
        'year': 2017,
        # is ReReco or Ultra Legacy
        'runtype': 'UL',
        'datatype': -1,

        #for correction
        # good json file
        'goodjson': 'data/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt',
        # pileup weight for MC
        'pileupfname': 'data/LUM/2017_UL/puWeights.json',
        'pileuptag': 'Collisions17_UltraLegacy_goldenJSON',
        # json filename for BTV correction
        'btvfname': 'data/BTV/2017_UL/btagging.json',
        # BTV correction type
        'btvtype': 'deepJet_shape',
        # json file name for JERC
        'jercfname': 'data/JERC/UL17_jerc.json',
        # conbined correction type for jets
        'jerctag': 'Summer19UL17_V5_MC_L1L2L3Res_AK4PFchs', 
        # jet uncertainty 
        'jercunctag': 'Summer19UL17_V5_MC_Total_AK4PFchs', 
        
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

