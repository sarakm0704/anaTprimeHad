"""
File contains job options 
"""

RUN_YEAR = 2018
DATA_TYPE = -1
RUN_TYPE = '_UL'
#RUN_TYPE = 'preVFP_UL'
#RUN_TYPE = 'postVFP_UL'
JEC_SYS = 'Total'

# options for Nanoaodrdframe
if(RUN_YEAR == 2018 and RUN_TYPE == '_UL'):

        config = {
                # tree name of input file(s)
                'intreename': "Events",
                # tree name of output file(s) it cannot be the same as the input tree name or it'll crash
                'outtreename': "outputTree",
                #data year (2016,2017,2018)
                'year': RUN_YEAR,
                # is ReReco or Ultra Legacy
                #'runtype': 'UL',
                'runtype': RUN_TYPE,
                'datatype': -1,
        
                #for correction
                # good json file
                #'goodjson': 'data/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt',
                # suppose to be
                'goodjson': 'data/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt',
                # pileup weight for MC
                #'pileupfname': 'data/LUM/2016postVFP_UL/puWeights.json',
                #'pileupfname': 'data/LUM/2016postVFP_UL/puWeights.json',
                'pileupfname': 'data/LUM/2018_UL/puWeights.json',
                #'pileuptag': 'Collisions16_UltraLegacy_goldenJSON',
                #'pileuptag': 'Collisions17_UltraLegacy_goldenJSON',
                'pileuptag': 'Collisions18_UltraLegacy_goldenJSON',
        
                #'muonid_fname': 'data/MUON/2018_UL/Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root',
                #'muonid_type': 'NUM_TightID_DEN_TrackerMuons_abseta_pt',
                #'muoniso_fname': 'data/MUON/2018_UL/Efficiencies_muon_generalTracks_Z_Run2018_UL_ISO.root',
                #'muoniso_type': 'NUM_TightRelIso_DEN_TightIDandIPCut_abseta_pt',
        
                #'muonreco_fname': 'data/MUON/2018_UL/NUM_TrackerMuons_DEN_genTracks_Z_abseta_pt_2018_schemaV2.json',
                #'muonreco_type': 'NUM_TrackerMuons_DEN_genTracks',
        
                #'elereco_fname': 'data/ELECTRON/2018_UL/egammaEffi_ptAbove20.txt_EGM2D_UL2018.root',
                #'elerecotype': 'EGamma_SF2D',# values are the same with ele.json 
        
                #'eleid_fname': 'data/ELECTRON/2018_UL/egammaEffi.txt_Ele_Tight_EGM2D.root',
                #'eleidtype': 'EGamma_SF2D',
        
                # json filename for BTV correction
                #'btvfname': 'data/BTV/2016postVFP_UL/btagging.json',
                #'btvfname': 'data/BTV/2017_UL/btagging.json',
                'btvfname': 'data/BTV/2018_UL/btagging.json',
                # BTV correction type
                'btvtype': 'deepJet_shape',
                # json file name for JERC
                #'jercfname': 'data/JERC/UL16postVFP_jerc.json',
                #'jercfname': 'data/JERC/UL17_jerc.json',
                'jercfname': 'data/JERC/jetUL18_jerc.json',
                # combined correction type for jets
                #'jerctag': 'Summer19UL16_V7_MC_L1L2L3Res_AK4PFchs', 
                #'jerctag': 'Summer19UL17_V5_MC_L1L2L3Res_AK4PFchs', 
                'jerctag': 'Summer19UL18_JRV2_MC_PtResolution_AK4PFchs', 
                # jet uncertainty 
                #'jercunctag': 'Summer19UL16_V7_MC_Total_AK4PFchs', 
                #'jercunctag': 'Summer19UL17_V5_MC_Total_AK4PFchs', 
                'jercunctag': 'Summer19UL18_JRV2_MC_ScaleFactor_AK4PFchs',
                'jercsys_total': 'Summer19UL18_V5_MC_Regrouped_Total_AK4PFchs', 
                
                }
        
        # processing options
        procflags = {
                # how many jobs?
                'split': 1,
                # if False, one output file per input file, if True then one output file for everything
                'allinone': True, 
                # if True then skip existing analyzed files
                'skipold': True,
                # travel through the subdirectories and their subdirecties when processing.
                # becareful not to mix MC and real DATA in them.
                'recursive': True,
                # if False then only selected branches which is done in the .cpp file will be saved
                'saveallbranches': False,
                #How many input files?
                #'nrootfiles': 0,
                }

# input directory where your input root tree resides
# output directory wheere your output should go
# dump of stderr/stdout to file
nanoaod_inputdir_outputdir_pairs = [
        #['testinputdata/MC/2018','analyzed/test_nano_v1.root', 'stderrout.out' ],
        #['processed/2016','analyzed/t_test_nan0v1.root', 'stderrout.out' ],
        ['/gridgroup/cms/jichoi/sample/mc/RunIISummer19UL18NanoAODv2/TprimeBToTH_M-700_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8',
         'out/TprimeBToTH_M-700.root',
         'tail.out']
]

