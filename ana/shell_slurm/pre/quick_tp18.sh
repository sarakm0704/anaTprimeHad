#!/bin/bash

#SBATCH --job-name=TprimUL18_DNN
#SBATCH --output=slurm/std_TprimUL18.out
#SBATCH --error=slurm/std_TprimUL18.err

#SBATCH --cpus-per-task=1
#SBATCH --partition=htc
#SBATCH --chdir=/pbs/home/j/jechoi/work/vlq/CMSSW_14_1_2/src/3t/

#SBATCH --mail-type=ALL
#SBATCH --mail-user=j-e.choi@ip2i.in2p3.fr

export X509_USER_PROXY=/pbs/home/j/jechoi/x509up_u49606

srun -n 1 --exclusive processnanoaod.py filelist/list_Tprime700UL18.txt /sps/lyon/jechoi/tprimeHad/2018/2M1L/Tprime700 tprimeConfig_UL18 > /sps/lyon/jechoi/tprimeHad/2018/2M1L/Tprime700.out

wait

echo "All job done"

exit 0
