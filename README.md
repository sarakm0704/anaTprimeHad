# anaTprimeHad
Searching for Tprime in Hadronic channel

## Analysis workflow

Setup tested in `cca.in2p3.fr`
- pyroot, xrootd, slurm needed

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

## NN workflow

### Treating arrays for training inputs / prediction outputs
To convert training ntuples to hdf:
```
./tree2hdf.py -d -p
```
- ```-d```: convert single root file to hdf
- ```-p```: merge single hdf files per process

then to cut out training datasets for balancing training inputs into certain fractions and shuffle:
```
python3 shuffle_mergy.py
```
to convert hdf output with prediction scores into TTree once training is done:
```
./hdf2tree.py
```

### Training and evaluation
Training has been performed DNN+CNN architecture with `train_cnn.py`
```
python3 train_cnn.py
```
To run over all the samples and save prediction scores (e.g. data) use evaluation
```
cnn_evaluation.py -e
```
input/output location needs to be specified when train/evaluate using code aboves

There is a tool to have evaluation, correlation matrices, feature importance and input distribution of features. Dedicated for further studies only.
```
python doFeatures.py -e -i -c -d (or -t)
```
- ```-e```: do Evaluation of model
- ```-i```: Extract Feature Importance
- ```-c```: Extract Correlations
- ```-d```: Draw Input variable Distributions
- ```-t```: Test with small portion from given dataset (100 events)

<i>keras (2.8.0), pyroot (6.30/02) used above</i><br>

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
