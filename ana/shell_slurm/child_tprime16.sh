#!/bin/bash

#SBATCH --job-name=DNN_Tprim700UL16post
#SBATCH --output=slurm/std_DNN_Tprim700UL16psot.out
#SBATCH --error=slurm/std_DNN_Tprim700UL16post.err

#SBATCH --ntasks=1
#SBATCH --cpus-per-task=16
#SBATCH --partition=hpc

#SBATCH --mail-type=ALL
#SBATCH --mail-user=j-e.choi@ip2i.in2p3.fr

export X509_USER_PROXY=/pbs/home/j/jechoi/x509up_u49606

#srun processnanoaod.py filelist/list_Tprime700UL16postVFP.txt out/mc_Tprime700UL16postVFP tprimeConfig_UL16postVFP > out/mc_Tprime700UL16postVFP.out
srun processnanoaod.py filelist/list_TprimeUL16.txt out/mc_Tprime700UL16 tprimeConfig_UL16 > out/mc_Tprime700UL16.out
