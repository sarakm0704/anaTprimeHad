#!/bin/bash

#SBATCH --job-name=QCD_HT100to200_BGenFilter_3T
#SBATCH --output=slurm/std_18_QCD_HT100to200_BGenFilter_3T.out
#SBATCH --error=slurm/std_18_QCD_HT100to200_BGenFilter_3T.err

#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=20
#SBATCH --partition=hpc

#SBATCH --mail-type=ALL
#SBATCH --mail-user=j-e.choi@ip2i.in2p3.fr

#SBATCH --chdir=/pbs/home/j/jechoi/work/vlq/CMSSW_14_1_2/src/ana/

export X509_USER_PROXY=/pbs/home/j/jechoi/x509up_u49606

srun --ntasks=1 processnanoaod.py filelist/QCD_2018/list_QCD_HT100to200_BGenFilter.txt /sps/lyon/jechoi/tprimeHad/2018/3T/QCD_HT100to200_BGenFilter mcConfig_UL18_3T > /sps/lyon/jechoi/tprimeHad/2018/3T/QCD_HT100to200_BGenFilter.out
