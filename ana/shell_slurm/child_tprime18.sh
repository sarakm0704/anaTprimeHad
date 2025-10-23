#!/bin/bash

#SBATCH -o slurm/%x.out
#SBATCH -e slurm/%x.err

#SBTACH -N 7
#SBTACH -n 7
#SBATCH --cpus-per-task=1

#SBATCH --partition=hpc

#SBATCH --mail-type=ALL
#SBATCH --mail-user=j-e.choi@ip2i.in2p3.fr

echo "region $1 running $2"

export X509_USER_PROXY=/pbs/home/j/jechoi/x509up_u49606

srun -N 1 -n 1 --exclusive --mem-per-cpu 5G processnanoaod.py filelist/list_Tprime600UL18.txt /sps/lyon/jechoi/tprimeHad/2018/$1/Tprime600 tprimeConfig_UL18 $1 $2 > /sps/lyon/jechoi/tprimeHad/2018/$1/Tprime600.out &
srun -N 1 -n 1 --exclusive --mem-per-cpu 5G processnanoaod.py filelist/list_Tprime700UL18.txt /sps/lyon/jechoi/tprimeHad/2018/$1/Tprime700 tprimeConfig_UL18 $1 $2 > /sps/lyon/jechoi/tprimeHad/2018/$1/Tprime700.out &
srun -N 1 -n 1 --exclusive --mem-per-cpu 5G processnanoaod.py filelist/list_Tprime800UL18.txt /sps/lyon/jechoi/tprimeHad/2018/$1/Tprime800 tprimeConfig_UL18 $1 $2 > /sps/lyon/jechoi/tprimeHad/2018/$1/Tprime800.out & 
srun -N 1 -n 1 --exclusive --mem-per-cpu 5G processnanoaod.py filelist/list_Tprime900UL18.txt /sps/lyon/jechoi/tprimeHad/2018/$1/Tprime900 tprimeConfig_UL18 $1 $2 > /sps/lyon/jechoi/tprimeHad/2018/$1/Tprime900.out &
srun -N 1 -n 1 --exclusive --mem-per-cpu 5G processnanoaod.py filelist/list_Tprime1000UL18.txt /sps/lyon/jechoi/tprimeHad/2018/$1/Tprime1000 tprimeConfig_UL18 $1 $2 > /sps/lyon/jechoi/tprimeHad/2018/$1/Tprime1000.out &
srun -N 1 -n 1 --exclusive --mem-per-cpu 5G processnanoaod.py filelist/list_Tprime1100UL18.txt /sps/lyon/jechoi/tprimeHad/2018/$1/Tprime1100 tprimeConfig_UL18 $1 $2 > /sps/lyon/jechoi/tprimeHad/2018/$1/Tprime1100.out &
srun -N 1 -n 1 --exclusive --mem-per-cpu 5G processnanoaod.py filelist/list_Tprime1200UL18.txt /sps/lyon/jechoi/tprimeHad/2018/$1/Tprime1200 tprimeConfig_UL18 $1 $2 > /sps/lyon/jechoi/tprimeHad/2018/$1/Tprime1200.out &

wait

echo "All job done"

exit 0
