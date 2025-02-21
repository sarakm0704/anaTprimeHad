#!/bin/bash

#SBATCH --job-name=ttHad_UL18_3M
#SBATCH --output=slurm/std_ttHad_UL18_3M.out
#SBATCH --error=slurm/std_ttHad_UL18_3M.err

#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=30
#SBATCH --partition=hpc

#SBATCH --chdir=/pbs/home/j/jechoi/work/vlq/CMSSW_14_1_2/src/ana/

#SBATCH --mail-type=ALL
#SBATCH --mail-user=j-e.choi@ip2i.in2p3.fr

export X509_USER_PROXY=/pbs/home/j/jechoi/x509up_u49606

srun --ntasks=1 processnanoaod.py filelist/list_TTToHadronic2018.txt /sps/lyon/jechoi/tprimeHad/2018/3M/TTToHadronic ttConfig_UL18_3M > /sps/lyon/jechoi/tprimeHad/2018/3M/TTToHadronic.out
