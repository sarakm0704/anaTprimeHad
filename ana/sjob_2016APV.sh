##!/bin/bash
DIR="/pbs/home/j/jechoi/work/vlq/CMSSW_14_1_2/src/trgEff/"
#
###### data
##sbatch -J SingleMuon_UL16B-ver1_3T --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/data16B-ver1_SingleMuon.sh 3T Data
##sbatch -J SingleMuon_UL16B-ver2_3T --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/data16B-ver2_SingleMuon.sh 3T Data
##sbatch -J SingleMuon_UL16C_3T --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/data16C_SingleMuon.sh 3T Data
##sbatch -J SingleMuon_UL16D_3T --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/data16D_SingleMuon.sh 3T Data
##sbatch -J SingleMuon_UL16E_3T --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/data16E_SingleMuon.sh 3T Data
##sbatch -J SingleMuon_UL16F_3T --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/data16F_SingleMuon.sh 3T Data
##sbatch -J SingleMuon_UL16FpostVFP_3T --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016/data16F_postVFP_SingleMuon.sh 3T Data
##sbatch -J SingleMuon_UL16GpostVFP_3T --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016/data16G_postVFP_SingleMuon.sh 3T Data
##sbatch -J SingleMuon_UL16HpostVFP_3T --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016/data16H_postVFP_SingleMuon.sh 3T Data
#
##sbatch -J SingleMuon_UL16B-ver1_3M --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/data16B-ver1_SingleMuon.sh 3M Data
##sbatch -J SingleMuon_UL16B-ver2_3M --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/data16B-ver2_SingleMuon.sh 3M Data
##sbatch -J SingleMuon_UL16C_3M --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/data16C_SingleMuon.sh 3M Data
##sbatch -J SingleMuon_UL16D_3M --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/data16D_SingleMuon.sh 3M Data
##sbatch -J SingleMuon_UL16E_3M --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/data16E_SingleMuon.sh 3M Data
##sbatch -J SingleMuon_UL16F_3M --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/data16F_SingleMuon.sh 3M Data
##sbatch -J SingleMuon_UL16FpostVFP_3M --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016/data16F_postVFP_SingleMuon.sh 3M Data
##sbatch -J SingleMuon_UL16GpostVFP_3M --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016/data16G_postVFP_SingleMuon.sh 3M Data
##sbatch -J SingleMuon_UL16HpostVFP_3M --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016/data16H_postVFP_SingleMuon.sh 3M Data
##
##sbatch -J SingleMuon_UL16B-ver1_2M1L --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/data16B-ver1_SingleMuon.sh 2M1L Data
##sbatch -J SingleMuon_UL16B-ver2_2M1L --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/data16B-ver2_SingleMuon.sh 2M1L Data
##sbatch -J SingleMuon_UL16C_2M1L --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/data16C_SingleMuon.sh 2M1L Data
##sbatch -J SingleMuon_UL16D_2M1L --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/data16D_SingleMuon.sh 2M1L Data
##sbatch -J SingleMuon_UL16E_2M1L --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/data16E_SingleMuon.sh 2M1L Data
##sbatch -J SingleMuon_UL16F_2M1L --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/data16F_SingleMuon.sh 2M1L Data
##sbatch -J SingleMuon_UL16FpostVFP_2M1L --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016/data16F_postVFP_SingleMuon.sh 2M1L Data
##sbatch -J SingleMuon_UL16GpostVFP_2M1L --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016/data16G_postVFP_SingleMuon.sh 2M1L Data
##sbatch -J SingleMuon_UL16HpostVFP_2M1L --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016/data16H_postVFP_SingleMuon.sh 2M1L Data
#
#sbatch -J JetHT_UL16B-ver1-HIPM_3T --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_data16B-ver1-HIPM_JetHT.sh 3T Data
#sbatch -J JetHT_UL16B-ver2-HIPM_3T --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_data16B-ver2-HIPM_JetHT.sh 3T Data
#sbatch -J JetHT_UL16C-HIPM_3T --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_data16C-HIPM_JetHT.sh 3T Data
#sbatch -J JetHT_UL16D-HIPM_3T --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_data16D-HIPM_JetHT.sh 3T Data
#sbatch -J JetHT_UL16E-HIPM_3T --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_data16E-HIPM_JetHT.sh 3T Data
#sbatch -J JetHT_UL16F-HIPM_3T --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_data16F-HIPM_JetHT.sh 3T Data
###
#sbatch -J JetHT_UL16B-ver1-HIPM_3M --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_data16B-ver1-HIPM_JetHT.sh 3M Data
#sbatch -J JetHT_UL16B-ver2-HIPM_3M --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_data16B-ver2-HIPM_JetHT.sh 3M Data
#sbatch -J JetHT_UL16C-HIPM_3M --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_data16C-HIPM_JetHT.sh 3M Data
#sbatch -J JetHT_UL16D-HIPM_3M --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_data16D-HIPM_JetHT.sh 3M Data
#sbatch -J JetHT_UL16E-HIPM_3M --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_data16E-HIPM_JetHT.sh 3M Data
#sbatch -J JetHT_UL16F-HIPM_3M --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_data16F-HIPM_JetHT.sh 3M Data
#
#sbatch -J JetHT_UL16B-ver1-HIPM_2M1L --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_data16B-ver1-HIPM_JetHT.sh 2M1L Data
#sbatch -J JetHT_UL16B-ver2-HIPM_2M1L --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_data16B-ver2-HIPM_JetHT.sh 2M1L Data
#sbatch -J JetHT_UL16C-HIPM_2M1L --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_data16C-HIPM_JetHT.sh 2M1L Data
#sbatch -J JetHT_UL16D-HIPM_2M1L --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_data16D-HIPM_JetHT.sh 2M1L Data
#sbatch -J JetHT_UL16E-HIPM_2M1L --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_data16E-HIPM_JetHT.sh 2M1L Data
#sbatch -J JetHT_UL16F-HIPM_2M1L --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_data16F-HIPM_JetHT.sh 2M1L Data
#
####### mc
sbatch -J Tprime_3T_UL16APV --chdir=$DIR -t 2-00:00 -n 7 --mem 35G -L sps shell_slurm/2016APV/child_tprime16APV.sh 3T Tprime
sbatch -J Tprime_3M_UL16APV --chdir=$DIR -t 2-00:00 -n 7 --mem 35G -L sps shell_slurm/2016APV/child_tprime16APV.sh 3M Tprime
sbatch -J Tprime_2M1L_UL16APV --chdir=$DIR -t 2-00:00 -n 7 --mem 35G -L sps shell_slurm/2016APV/child_tprime16APV.sh 2M1L Tprime
##
#sbatch -J TTToHadronic_2M1L_UL16APV --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_tthad16APV.sh 2M1L TTToHadronic
#sbatch -J TTToHadronic_3M_UL16APV --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_tthad16APV.sh 3M TTToHadronic
#sbatch -J TTToHadronic_3T_UL16APV --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_tthad16APV.sh 3T TTToHadronic
##
#sbatch -J QCD_BGenFilter_0_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_0.sh 3T QCD
#sbatch -J QCD_BGenFilter_1_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_1.sh 3T QCD
#sbatch -J QCD_BGenFilter_2_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_2.sh 3T QCD
#sbatch -J QCD_BGenFilter_3_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_3.sh 3T QCD
#sbatch -J QCD_BGenFilter_4_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_4.sh 3T QCD
#sbatch -J QCD_BGenFilter_5_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_5.sh 3T QCD
#sbatch -J QCD_BGenFilter_6_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_6.sh 3T QCD
#sbatch -J QCD_BGenFilter_7_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_7.sh 3T QCD
##
#sbatch -J QCD_bEnriched_0_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_0.sh 3T QCD
#sbatch -J QCD_bEnriched_1_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_1.sh 3T QCD
#sbatch -J QCD_bEnriched_2_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_2.sh 3T QCD
#sbatch -J QCD_bEnriched_3_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_3.sh 3T QCD
#sbatch -J QCD_bEnriched_4_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_4.sh 3T QCD
#sbatch -J QCD_bEnriched_5_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_5.sh 3T QCD
#sbatch -J QCD_bEnriched_6_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_6.sh 3T QCD
#sbatch -J QCD_bEnriched_7_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_7.sh 3T QCD
#
#sbatch -J WJets_HT200to400_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_wjets_0.sh 3T VJets
#sbatch -J WJets_HT400to600_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_wjets_1.sh 3T VJets
#sbatch -J WJets_HT600to800_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_wjets_2.sh 3T VJets
#sbatch -J WJets_HT800toInf_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_wjets_3.sh 3T VJets
#
#sbatch -J ZJets_HT200to400_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_zjets_0.sh 3T VJets
#sbatch -J ZJets_HT400to600_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_zjets_1.sh 3T VJets
#sbatch -J ZJets_HT600to800_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_zjets_2.sh 3T VJets
#sbatch -J ZJets_HT800toInf_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_zjets_3.sh 3T VJets
#
#sbatch -J ST_s_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_s.sh 3T ST
#sbatch -J ST_t_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_t_top.sh 3T ST
###########error but available###########sbatch -J ST_ant_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_t_antitop.sh 3T ST
###########error but available###########sbatch -J ST_tW_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_tW_top.sh 3T ST
#sbatch -J ST_antW_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_tW_antitop.sh 3T ST
##
#sbatch -J ttHTobb_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_ttHTobb.sh 3T ttH
#sbatch -J ttHToNonbb_3T_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_ttHToNonbb.sh 3T ttH
#
#sbatch -J QCD_BGenFilter_0_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_0.sh 3M QCD
#sbatch -J QCD_BGenFilter_1_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_1.sh 3M QCD
#sbatch -J QCD_BGenFilter_2_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_2.sh 3M QCD
#sbatch -J QCD_BGenFilter_3_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_3.sh 3M QCD
#sbatch -J QCD_BGenFilter_4_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_4.sh 3M QCD
#sbatch -J QCD_BGenFilter_5_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_5.sh 3M QCD
#sbatch -J QCD_BGenFilter_6_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_6.sh 3M QCD
#sbatch -J QCD_BGenFilter_7_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_7.sh 3M QCD
#
#sbatch -J QCD_bEnriched_0_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_0.sh 3M QCD
#sbatch -J QCD_bEnriched_1_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_1.sh 3M QCD
#sbatch -J QCD_bEnriched_2_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_2.sh 3M QCD
#sbatch -J QCD_bEnriched_3_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_3.sh 3M QCD
#sbatch -J QCD_bEnriched_4_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_4.sh 3M QCD
#sbatch -J QCD_bEnriched_5_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_5.sh 3M QCD
#sbatch -J QCD_bEnriched_6_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_6.sh 3M QCD
#sbatch -J QCD_bEnriched_7_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_7.sh 3M QCD
#
#sbatch -J WJets_HT200to400_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_wjets_0.sh 3M VJets
#sbatch -J WJets_HT400to600_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_wjets_1.sh 3M VJets
#sbatch -J WJets_HT600to800_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_wjets_2.sh 3M VJets
#sbatch -J WJets_HT800toInf_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_wjets_3.sh 3M VJets
#
#sbatch -J ZJets_HT200to400_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_zjets_0.sh 3M VJets
#sbatch -J ZJets_HT400to600_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_zjets_1.sh 3M VJets
#sbatch -J ZJets_HT600to800_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_zjets_2.sh 3M VJets
#sbatch -J ZJets_HT800toInf_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_zjets_3.sh 3M VJets
#
#sbatch -J ST_s_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_s.sh 3M ST
#sbatch -J ST_t_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_t_top.sh 3M ST
#sbatch -J ST_ant_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_t_antitop.sh 3M ST
#########error but available############ sbatch -J ST_tW_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_tW_top.sh 3M ST
#########error but available############ sbatch -J ST_antW_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_tW_antitop.sh 3M ST
#
#sbatch -J ttHTobb_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_ttHTobb.sh 3M ttH
#sbatch -J ttHToNonbb_3M_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_ttHToNonbb.sh 3M ttH
#
#sbatch -J QCD_BGenFilter_0_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_0.sh 2M1L QCD
#sbatch -J QCD_BGenFilter_1_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_1.sh 2M1L QCD
#sbatch -J QCD_BGenFilter_2_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_2.sh 2M1L QCD
#sbatch -J QCD_BGenFilter_3_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_3.sh 2M1L QCD
#sbatch -J QCD_BGenFilter_4_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_4.sh 2M1L QCD
#sbatch -J QCD_BGenFilter_5_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_5.sh 2M1L QCD
#sbatch -J QCD_BGenFilter_6_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_6.sh 2M1L QCD
#sbatch -J QCD_BGenFilter_7_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_7.sh 2M1L QCD
#
#sbatch -J QCD_bEnriched_0_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_0.sh 2M1L QCD
#sbatch -J QCD_bEnriched_1_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_1.sh 2M1L QCD
#sbatch -J QCD_bEnriched_2_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_2.sh 2M1L QCD
#sbatch -J QCD_bEnriched_3_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_3.sh 2M1L QCD
#sbatch -J QCD_bEnriched_4_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_4.sh 2M1L QCD
#sbatch -J QCD_bEnriched_5_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_5.sh 2M1L QCD
#sbatch -J QCD_bEnriched_6_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_6.sh 2M1L QCD
#sbatch -J QCD_bEnriched_7_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_7.sh 2M1L QCD
#
#sbatch -J WJets_HT200to400_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_wjets_0.sh 2M1L VJets
#sbatch -J WJets_HT400to600_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_wjets_1.sh 2M1L VJets
#sbatch -J WJets_HT600to800_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_wjets_2.sh 2M1L VJets
#sbatch -J WJets_HT800toInf_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_wjets_3.sh 2M1L VJets
#
#sbatch -J ZJets_HT200to400_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_zjets_0.sh 2M1L VJets
#sbatch -J ZJets_HT400to600_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_zjets_1.sh 2M1L VJets
#sbatch -J ZJets_HT600to800_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_zjets_2.sh 2M1L VJets
#sbatch -J ZJets_HT800toInf_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_zjets_3.sh 2M1L VJets
#
#sbatch -J ST_s_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_s.sh 2M1L ST
#sbatch -J ST_t_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_t_top.sh 2M1L ST
#sbatch -J ST_ant_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_t_antitop.sh 2M1L ST
#sbatch -J ST_tW_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_tW_top.sh 2M1L ST
#sbatch -J ST_antW_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_tW_antitop.sh 2M1L ST
#
#sbatch -J ttHTobb_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_ttHTobb.sh 2M1L ttH
#sbatch -J ttHToNonbb_2M1L_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_ttHToNonbb.sh 2M1L ttH
##
###sbatch -J Tprime_effMap_UL16APV --chdir=$DIR -t 2-00:00 -n 7 --mem 35G -L sps shell_slurm/2016APV/child_tprime16APV.sh effMap Tprime
###sbatch -J TTToHadronic_effMap_UL16APV --chdir=$DIR -t 2-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_tthad16APV.sh effMap TToHadronic
###
###sbatch -J QCD_BGenFilter_0_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_0.sh effMap QCD
###sbatch -J QCD_BGenFilter_1_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_1.sh effMap QCD
###sbatch -J QCD_BGenFilter_2_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_2.sh effMap QCD
###sbatch -J QCD_BGenFilter_3_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_3.sh effMap QCD
###sbatch -J QCD_BGenFilter_4_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_4.sh effMap QCD
###sbatch -J QCD_BGenFilter_5_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_5.sh effMap QCD
###sbatch -J QCD_BGenFilter_6_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_6.sh effMap QCD
###sbatch -J QCD_BGenFilter_7_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_BGenFilter_7.sh effMap QCD
###
###sbatch -J QCD_bEnriched_0_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_0.sh effMap QCD
###sbatch -J QCD_bEnriched_1_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_1.sh effMap QCD
###sbatch -J QCD_bEnriched_2_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_2.sh effMap QCD
###sbatch -J QCD_bEnriched_3_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_3.sh effMap QCD
###sbatch -J QCD_bEnriched_4_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_4.sh effMap QCD
###sbatch -J QCD_bEnriched_5_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_5.sh effMap QCD
###sbatch -J QCD_bEnriched_6_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_6.sh effMap QCD
###sbatch -J QCD_bEnriched_7_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_qcd16APV_bEnriched_7.sh effMap QCD
####
###sbatch -J WJets_HT200to400_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_wjets_0.sh effMap VJets
###sbatch -J WJets_HT400to600_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_wjets_1.sh effMap VJets
###sbatch -J WJets_HT600to800_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_wjets_2.sh effMap VJets
###sbatch -J WJets_HT800toInf_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_wjets_3.sh effMap VJets
###
###sbatch -J ZJets_HT200to400_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_zjets_0.sh effMap VJets
###sbatch -J ZJets_HT400to600_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_zjets_1.sh effMap VJets
###sbatch -J ZJets_HT600to800_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_zjets_2.sh effMap VJets
###sbatch -J ZJets_HT800toInf_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_zjets_3.sh effMap VJets
###
###sbatch -J ST_s_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_s.sh effMap ST
###sbatch -J ST_t_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_t_top.sh effMap ST
###sbatch -J ST_ant_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_t_antitop.sh effMap ST
###sbatch -J ST_tW_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_tW_top.sh effMap ST
###sbatch -J ST_antW_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_st_tW_antitop.sh effMap ST
###
###sbatch -J ttHTobb_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_ttHTobb.sh effMap ttH
###sbatch -J ttHToNonbb_effMap_UL16APV --chdir=$DIR -t 1-00:00 -n 1 --mem 16G -L sps shell_slurm/2016APV/child_ttHToNonbb.sh effMap ttH
