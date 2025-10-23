#!/bin/bash

#SBATCH --job-name=DNN_Tprim700UL17
#SBATCH --output=slurm/std_DNN_Tprim700UL17.out
#SBATCH --error=slurm/std_DNN_Tprim700UL17.err

#SBATCH --ntasks=1
#SBATCH --cpus-per-task=16
#SBATCH --partition=hpc

#SBATCH --mail-type=ALL
#SBATCH --mail-user=j-e.choi@ip2i.in2p3.fr

export X509_USER_PROXY=/pbs/home/j/jechoi/x509up_u49606

#srun processnanoaod.py filelist/list_Tprime700UL17.txt out/mc_Tprime700UL17 tprimeConfig_UL17 > out/mc_Tprime700UL17.out
srun processnanoaod.py filelist/list_TprimeUL17.txt out/mc_Tprime700UL17 tprimeConfig_UL17 > out/mc_Tprime700UL17.out
