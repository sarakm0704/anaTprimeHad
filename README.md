# anaTprimeHad
Searching for Tprime in Hadronic channel

nanoAOD private production: https://gitlab.cern.ch/cms-nanoAOD/nanoaod-doc/-/wikis/Instructions/Private%20production

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
