#!/bin/bash

#SBATCH -o slurm/%x.out
#SBATCH -e slurm/%x.err

#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=20
#SBATCH --partition=htc

#SBATCH --mail-type=ALL
#SBATCH --mail-user=j-e.choi@ip2i.in2p3.fr

echo "region $1 running $2"

export X509_USER_PROXY=/pbs/home/j/jechoi/x509up_u49606

srun --ntasks=1 processnanoaod.py filelist/QCD_2018/list_QCD_HT300to500_BGenFilter.txt /sps/lyon/jechoi/tprimeHad/2018/$1/QCD_HT300to500_BGenFilter mcConfig_UL18 $1 $2 > /sps/lyon/jechoi/tprimeHad/2018/$1/QCD_HT300to500_BGenFilter.out
