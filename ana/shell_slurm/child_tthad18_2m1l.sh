#!/bin/bash

#SBATCH --job-name=ttHad_2M1L
#SBATCH --output=slurm/std_ttHad_UL18_2M1L.out
#SBATCH --error=slurm/std_ttHad_UL18_2M1L.err

#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=30
#SBATCH --partition=hpc

#SBATCH --chdir=/pbs/home/j/jechoi/work/vlq/CMSSW_14_1_2/src/ana/

#SBATCH --mail-type=ALL
#SBATCH --mail-user=j-e.choi@ip2i.in2p3.fr

export X509_USER_PROXY=/pbs/home/j/jechoi/x509up_u49606

srun --ntasks=1 processnanoaod.py filelist/list_TTToHadronic2018.txt /sps/lyon/jechoi/tprimeHad/2018/2M1L/TTToHadronic ttConfig_UL18_2M1L > /sps/lyon/jechoi/tprimeHad/2018/2M1L/TTToHadronic.out
