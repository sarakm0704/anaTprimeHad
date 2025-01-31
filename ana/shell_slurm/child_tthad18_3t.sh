#!/bin/bash

#SBATCH --job-name=ttHad_UL18_3T
#SBATCH --output=slurm/std_ttHad_UL18_3T.out
#SBATCH --error=slurm/std_ttHad_UL18_3T.err

#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=30
#SBATCH --partition=hpc

#SBATCH --chdir=/pbs/home/j/jechoi/work/vlq/CMSSW_14_1_2/src/ana/

#SBATCH --mail-type=ALL
#SBATCH --mail-user=j-e.choi@ip2i.in2p3.fr

export X509_USER_PROXY=/pbs/home/j/jechoi/x509up_u49606

srun --ntasks=1 processnanoaod.py filelist/list_TTToHadronic2018.txt /sps/lyon/jechoi/tprimeHad/2018/3T/TTToHadronic ttConfig_UL18_3T > /sps/lyon/jechoi/tprimeHad/2018/3T/TTToHadronic.out
