#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
from importlib import import_module

# loop over the directories and submit background jobs
def submit(jobconfmod):

    # get input directory, outputdirectory, stderrout file from the job configuration python module
    mod = import_module(jobconfmod)
    nanoaod_inputdir_outputdir_pairs= getattr(mod, 'nanoaod_inputdir_outputdir_pairs')

    # job configuation module name is to be passed to the skim nanoaod main 
    for indir,outdir,outfile in nanoaod_inputdir_outputdir_pairs:
        os.system('srun --mail-user=j-e.choi@ip2i.in2p3.fr --mail-type=ALL -n 1 --job-name deeponCSVoffJet processnanoaod.py'+ indir + ' ' + outdir + ' ' + jobconfmod  + ' > ' + outfile + ' 2>&1 &') # submit background jobs
#        os.system('./processnanoaod.py '+ indir + ' ' + outdir + ' ' + jobconfmod  + ' > ' + outfile + ' 2>&1 &') # submit background jobs
#        os.system('./processonefile.py '+ indir + ' ' + outdir + ' ' + jobconfmod) ### for parallelization, no this should not
    pass

if __name__=="__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser(usage="%prog jobconfigmodule", description='submits skim jobs in background where the job '\
        +' configuration python module name should be passedd')
    parser.add_argument("jobconfmod")
    args = parser.parse_args()

    jobconfmod_fname = args.jobconfmod
    # strip .py from the filename
    jobconfmod = jobconfmod_fname.replace('.py', '')

    submit(jobconfmod)
    pass
