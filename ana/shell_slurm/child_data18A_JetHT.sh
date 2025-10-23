#!/bin/bash

#SBATCH -o slurm/%x.out
#SBATCH -e slurm/%x.err

#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=30
#SBATCH --partition=hpc

#SBATCH --mail-type=ALL
#SBATCH --mail-user=j-e.choi@ip2i.in2p3.fr

echo "region $1 running $2"

export X509_USER_PROXY=/pbs/home/j/jechoi/x509up_u49606

srun --ntasks=1 processnanoaod.py filelist/list_2018A_JetHT.txt /sps/lyon/jechoi/tprimeHad/2018/$1/JetHT_A dataConfig_UL18 $1 $2 > /sps/lyon/jechoi/tprimeHad/2018/$1/JetHT_A.out
