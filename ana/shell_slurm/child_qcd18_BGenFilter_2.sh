#!/bin/bash

#SBATCH --job-name=QCD_HT300to500_BGenFilter_effMap
#SBATCH --output=slurm/std_18_QCD_HT300to500_BGenFilter_effMap.out
#SBATCH --error=slurm/std_18_QCD_HT300to500_BGenFilter_effMap.err

#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=20
#SBATCH --partition=htc

#SBATCH --chdir=/pbs/home/j/jechoi/work/vlq/CMSSW_14_1_2/src/ana/

#SBATCH --mail-type=ALL
#SBATCH --mail-user=j-e.choi@ip2i.in2p3.fr

export X509_USER_PROXY=/pbs/home/j/jechoi/x509up_u49606

srun --ntasks=1 processnanoaod.py filelist/QCD_2018/list_QCD_HT300to500_BGenFilter.txt /sps/lyon/jechoi/tprimeHad/2018/effMap/QCD_HT300to500_BGenFilter mcConfig_UL18 > /sps/lyon/jechoi/tprimeHad/2018/effMap/QCD_HT300to500_BGenFilter.out
