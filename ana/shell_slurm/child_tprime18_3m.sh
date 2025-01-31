#!/bin/bash

#SBATCH --job-name=TprimUL18_3M
#SBATCH --output=slurm/std_TprimUL18_3M.out
#SBATCH --error=slurm/std_TprimUL18_3M.err

#SBTACH -N 7
#SBTACH -n 7
#SBATCH --cpus-per-task=1

#SBATCH --partition=hpc
#SBATCH --chdir=/pbs/home/j/jechoi/work/vlq/CMSSW_14_1_2/src/ana/

#SBATCH --mail-type=ALL
#SBATCH --mail-user=j-e.choi@ip2i.in2p3.fr

export X509_USER_PROXY=/pbs/home/j/jechoi/x509up_u49606

srun -N 1 -n 1 --exclusive --mem-per-cpu 3G processnanoaod.py filelist/list_Tprime600UL18.txt /sps/lyon/jechoi/tprimeHad/2018/3M/Tprime600 tprimeConfig_UL18_3M > /sps/lyon/jechoi/tprimeHad/2018/3M/Tprime600.out &
srun -N 1 -n 1 --exclusive --mem-per-cpu 3G processnanoaod.py filelist/list_Tprime700UL18.txt /sps/lyon/jechoi/tprimeHad/2018/3M/Tprime700 tprimeConfig_UL18_3M > /sps/lyon/jechoi/tprimeHad/2018/3M/Tprime700.out &
srun -N 1 -n 1 --exclusive --mem-per-cpu 3G processnanoaod.py filelist/list_Tprime800UL18.txt /sps/lyon/jechoi/tprimeHad/2018/3M/Tprime800 tprimeConfig_UL18_3M > /sps/lyon/jechoi/tprimeHad/2018/3M/Tprime800.out & 
srun -N 1 -n 1 --exclusive --mem-per-cpu 3G processnanoaod.py filelist/list_Tprime900UL18.txt /sps/lyon/jechoi/tprimeHad/2018/3M/Tprime900 tprimeConfig_UL18_3M > /sps/lyon/jechoi/tprimeHad/2018/3M/Tprime900.out &
srun -N 1 -n 1 --exclusive --mem-per-cpu 3G processnanoaod.py filelist/list_Tprime1000UL18.txt /sps/lyon/jechoi/tprimeHad/2018/3M/Tprime1000 tprimeConfig_UL18_3M > /sps/lyon/jechoi/tprimeHad/2018/3M/Tprime1000.out &
srun -N 1 -n 1 --exclusive --mem-per-cpu 3G processnanoaod.py filelist/list_Tprime1100UL18.txt /sps/lyon/jechoi/tprimeHad/2018/3M/Tprime1100 tprimeConfig_UL18_3M > /sps/lyon/jechoi/tprimeHad/2018/3M/Tprime1100.out &
srun -N 1 -n 1 --exclusive --mem-per-cpu 3G processnanoaod.py filelist/list_Tprime1200UL18.txt /sps/lyon/jechoi/tprimeHad/2018/3M/Tprime1200 tprimeConfig_UL18_3M > /sps/lyon/jechoi/tprimeHad/2018/3M/Tprime1200.out &
wait

echo "All job done"

exit 0
