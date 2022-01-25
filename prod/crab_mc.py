from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'TprimeBToTH_THad_Hbb_LH_MT700_MH125'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.psetName = 'myTprimeProdMC2018UL20_NANO.py'
config.JobType.pluginName = 'Analysis'
config.JobType.outputFiles = ['nanoTree.root']

config.Data.inputDataset = '/TprimeBToTH_THad_Hbb_LH_MT700_MH125_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM'
#config.Data.inputDataset = '/TprimeBToTH_M-700_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM'

config.Data.unitsPerJob = 1
config.Data.splitting = 'FileBased'

config.Site.storageSite = 'T3_FR_IPNL'
config.Data.outLFNDirBase = '/store/user/jichoi/'
config.Data.publication = False
config.Data.outputDatasetTag = 'nanoTprimeAna'
