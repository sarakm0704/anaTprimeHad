# anaTprimeHad
Searching for Tprime in Hadronic channel

## Analysis workflow

Setup in el8_amd64_gcc12
```
source /cvmfs/cms.cern.ch/cmsset_default.sh

cmsrel CMSSW_14_1_12
cd CMSSW_14_1_12/src
cmsenv
git clone https://github.com/sarakm0704/anaTprimeHad.git
cd anaTprimeHad/ana
make clean
make -j 30
```
to test
```
mkdir test
./processnanoaod.py filelist/list_Tprime600UL18.txt test/Tprime600 tprimeConfig_UL18_3T > test/tp600.out
```
This workflow is currently using nanoaod via xrootd and running over slurm only. It could be modified to use HTCondor.

To run with complete datasets:
- modify tasks in `sjob.sh`
  - `-L sps` option is only allowed in `cca.in2p3.fr` to use sps storage
- individual tasks are defined in  `shell_slurm/` directory
  - but options for slurm job such as `--chdir`, `--mail*`, `X509_USER_PROXY` and storage locations should be modified according to the analyser themselves
 
After defining options correctly, run the job
```
./sjob.sh
```

## nanoAOD private production

ref: https://gitlab.cern.ch/cms-nanoAOD/nanoaod-doc/-/wikis/Instructions/Private%20production

Don't forget to source the environment from cvmfs if you are lyoserv user by doing:
```
cms_env
```

With 2018 datasets for example:

```
cmsrel CMSSW_10_6_27
cd CMSSW_10_6_27/src
cmsenv
git clone https://github.com/sarakm0704/anaTprimeHad.git
cd anaTprimeHad/prod
crab submit -c crab_mc.py
```
## NN workflow

Training via simple DNN is available with ```training.py```
Evaluation and extracting feature informations with ```ecid_afterTraining.py```

- ```training.py```<br>
> This has no option yet. Can be handled by changing input / structure itself. 

- ```ecid_afterTraining.py```<br>
do **E**valuation and extract **C**orrelations, **I**mportance, **D**istributions of features after training

```
python ecid_afterTraining -e -i -c -d (or -t)
```
- ```-e```: do Evaluation of model
- ```-i```: Extract Feature Importance
- ```-c```: Extract Correlations
- ```-d```: Draw Input variable Distributions
- ```-t```: Test with small portion from given dataset (100 events)
