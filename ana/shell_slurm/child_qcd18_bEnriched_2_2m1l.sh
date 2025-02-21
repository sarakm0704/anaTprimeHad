#!/bin/bash

#SBATCH --job-name=QCD_bEnriched_HT300to500_2M1L
#SBATCH --output=slurm/std_18_QCD_bEnriched_HT300to500_2M1L.out
#SBATCH --error=slurm/std_18_QCD_bEnriched_HT300to500_2M1L.err

#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=20
#SBATCH --partition=htc

#SBATCH --mail-type=ALL
#SBATCH --mail-user=j-e.choi@ip2i.in2p3.fr

#SBATCH --chdir=/pbs/home/j/jechoi/work/vlq/CMSSW_14_1_2/src/ana/

export X509_USER_PROXY=/pbs/home/j/jechoi/x509up_u49606

srun --ntasks=1 processnanoaod.py filelist/QCD_2018/list_QCD_bEnriched_HT300to500.txt /sps/lyon/jechoi/tprimeHad/2018/2M1L/QCD_bEnriched_HT300to500 mcConfig_UL18_2M1L > /sps/lyon/jechoi/tprimeHad/2018/2M1L/QCD_bEnriched_HT300to500.out
