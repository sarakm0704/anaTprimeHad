#!/bin/bash

## data
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/data18A_JetHT_3t.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/data18A_JetHT_3m.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/data18A_JetHT_2m1l.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/data18B_JetHT_3t.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/data18B_JetHT_3m.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/data18B_JetHT_2m1l.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/data18C_JetHT_3t.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/data18C_JetHT_3m.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/data18C_JetHT_2m1l.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/data18D_JetHT_3t.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/data18D_JetHT_3m.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/data18D_JetHT_2m1l.sh -L sps

###### resubmit 
sbatch -t 2-00:00 -n 7 --mem 21G shell_slurm/child_tprime18_3t.sh -L sps
sbatch -t 2-00:00 -n 7 --mem 21G shell_slurm/child_tprime18_3m.sh -L sps
sbatch -t 2-00:00 -n 7 --mem 21G shell_slurm/child_tprime18_2m1l.sh -L sps
sbatch -t 2-00:00 -n 1 --mem 16G shell_slurm/child_tthad18_3t.sh -L sps
sbatch -t 2-00:00 -n 1 --mem 16G shell_slurm/child_tthad18_3m.sh -L sps
sbatch -t 2-00:00 -n 1 --mem 16G shell_slurm/child_tthad18_2m1l.sh -L sps
#
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_0_3t.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_1_3t.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_2_3t.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_3_3t.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_4_3t.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_5_3t.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_6_3t.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_7_3t.sh -L sps

sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_0_3t.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_1_3t.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_2_3t.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_3_3t.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_4_3t.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_5_3t.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_6_3t.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_7_3t.sh -L sps

sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_0_3m.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_1_3m.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_2_3m.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_3_3m.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_4_3m.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_5_3m.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_6_3m.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_7_3m.sh -L sps

sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_0_3m.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_1_3m.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_2_3m.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_3_3m.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_4_3m.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_5_3m.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_6_3m.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_7_3m.sh -L sps

sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_0_2m1l.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_1_2m1l.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_2_2m1l.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_3_2m1l.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_4_2m1l.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_5_2m1l.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_6_2m1l.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_7_2m1l.sh -L sps

sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_0_2m1l.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_1_2m1l.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_2_2m1l.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_3_2m1l.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_4_2m1l.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_5_2m1l.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_6_2m1l.sh -L sps
sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_7_2m1l.sh -L sps

## old


#sbatch -t 0-06:00 -n 1 --mem 8G child_tprime16preVFP.sh
#sbatch -t 0-06:00 -n 1 --mem 8G child_tprime16postVFP.sh
#sbatch -t 0-06:00 -n 1 --mem 8G child_tprime17.sh
#sbatch -t 0-06:00 -n 1 --mem 8G child_tprime18.sh
#sbatch -t 1-00:00 -n 1 --mem 16G child_mc16APV.sh
#sbatch -t 1-00:00 -n 1 --mem 16G child_mc16.sh
##sbatch -t 1-00:00 -n 1 --mem 16G child_mc17.sh
#sbatch -t 2-00:00 -n 1 --mem 16G child_mc18.sh

#sbatch -t 2-00:00 -n 1 --mem 16G shell_slurm/child_tprime18.sh -L sps
#sbatch -t 2-00:00 -n 1 --mem 4G shell_slurm/quick_tp18.sh -L sps
#sbatch -t 2-00:00 -n 1 --mem 16G shell_slurm/child_tthad18.sh -L sps

#sbatch -t 1-00:00 -n 1 --mem 8G shell_slurm/child_qcd18_BGenFilter_0.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 8G shell_slurm/child_qcd18_BGenFilter_1.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 8G shell_slurm/child_qcd18_BGenFilter_2.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 8G shell_slurm/child_qcd18_BGenFilter_3.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 8G shell_slurm/child_qcd18_BGenFilter_4.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 8G shell_slurm/child_qcd18_BGenFilter_5.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 8G shell_slurm/child_qcd18_BGenFilter_6.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 8G shell_slurm/child_qcd18_BGenFilter_7.sh -L sps
#
#sbatch -t 1-00:00 -n 1 --mem 8G shell_slurm/child_qcd18_bEnriched_0.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 8G shell_slurm/child_qcd18_bEnriched_1.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 8G shell_slurm/child_qcd18_bEnriched_2.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 8G shell_slurm/child_qcd18_bEnriched_3.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 8G shell_slurm/child_qcd18_bEnriched_4.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 8G shell_slurm/child_qcd18_bEnriched_5.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 8G shell_slurm/child_qcd18_bEnriched_6.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 8G shell_slurm/child_qcd18_bEnriched_7.sh -L sps

#sbatch -t 2-00:00 -n 1 --mem 16G shell_slurm/data18A_JetHT.sh
#sbatch -t 2-00:00 -n 1 --mem 16G shell_slurm/data18B_JetHT.sh 
#sbatch -t 2-00:00 -n 1 --mem 16G shell_slurm/data18C_JetHT.sh 
#sbatch -t 2-00:00 -n 1 --mem 16G shell_slurm/data18D_JetHT.sh 

#when hpc is available
#sbatch -t 2-00:00 -n 7 --mem 16G shell_slurm/child_tprime18.sh
#sbatch -t 1-00:00 -n 8 --mem 16G shell_slurm/child_qcd18_BGenFilter.sh 
#sbatch -t 1-00:00 -n 8 --mem 16G shell_slurm/child_qcd18_bEnriched.sh
#sbatch -t 2-00:00 -n 1 --mem 16G shell_slurm/data18_JetHT.sh 

#sbatch -t 2-00:00 -n 7 --mem 16G -L sps shell_slurm/child_tprime18.sh
#sbatch -t 1-00:00 -n 8 --mem 8G -L sps shell_slurm/child_qcd18_BGenFilter.sh 
#sbatch -t 1-00:00 -n 8 --mem 8G -L sps shell_slurm/child_qcd18_bEnriched.sh
#sbatch -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/data18_JetHT.sh 

# resubmit for effMap
#sbatch -t 2-00:00 -n 7 --mem 21G shell_slurm/child_tprime18.sh -L sps
#sbatch -t 2-00:00 -n 1 --mem 16G shell_slurm/child_tthad18.sh -L sps
#
#sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_0.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_1.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_2.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_3.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_4.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_5.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_6.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_BGenFilter_7.sh -L sps
#
#sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_0.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_1.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_2.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_3.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_4.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_5.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_6.sh -L sps
#sbatch -t 1-00:00 -n 1 --mem 16G shell_slurm/child_qcd18_bEnriched_7.sh -L sps

