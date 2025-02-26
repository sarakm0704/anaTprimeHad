import pandas as pd
import numpy as np
import pickle
from sklearn.preprocessing import StandardScaler

import keras
from keras.models import Model, load_model
from tensorflow.keras.utils import to_categorical

region = ['2M1L','3M','3T']
nbins=30

def cleaning(d):
    d = pd.DataFrame(d).fillna(-999)
    d.replace([np.inf, -np.inf], 999, inplace=True)
    if not d.isnull().values.any() and not np.isinf(d).values.any(): print("Cleaned data!")
    
    return d

for i in range(len(region)):
    dfQCD = pd.read_hdf(f"/Users/jieun/WORK/vlq/dnn/array/arrayOut/ana/multi/{region[i]}/array_merged_qcd.h5")
    dfTT = pd.read_hdf(f"/Users/jieun/WORK/vlq/dnn/array/arrayOut/ana/multi/{region[i]}/array_merged_ttbar.h5")
    dfTp = pd.read_hdf(f"/Users/jieun/WORK/vlq/dnn/array/arrayOut/ana/multi/{region[i]}/array_merged_tprime.h5")
    #df = pd.concat([dfQCD, dfTT, dfTp], axis=0)

    event_var=['nseljets', 'nselbjets', 'goodht', 'relht', 'mindR_dRbb', 'mindR_mbb', 'Chi2_max', 'Chi2_min', 'Chi2_min_H', 'Chi2_min_W', 'Chi2_min_Top', 'mass_h', 'mass_w', 'mass_top', 'mass_wh', 'mass_secondtop', 'mass_leadjets', 'dR_hbb', 'dR_wjj', 'dR_bw', 'dR_tprimeoj', 'ratio_mass_topH', 'ratio_mass_secondtopW', 'ratio_pt_topsecondtop', 'ratio_pt_htoptprime', 'ratio_pt_tprimehtprimetop']
    jet_var=['jet1_eta', 'jet1_e_massnom', 'jet2_eta', 'jet2_e_massnom', 'jet3_eta', 'jet3_e_massnom', 'jet4_eta', 'jet4_e_massnom', 'jet5_eta', 'jet5_e_massnom']
    name_inputvar = event_var+jet_var
    
    #clean data
    dfQCD = cleaning(dfQCD)
    dfTT = cleaning(dfTT)
    dfTp = cleaning(dfTp)

    import matplotlib.pyplot as plt
    print("imported matplotlib, drawing...")
    
    for names in name_inputvar:

        if 'seljets' in names: bins=10
        if 'selbjets' in names: bins=4
    
        print(f"running on {names}")

        bkg_qcd = pd.concat([dfTT,dfTp],axis=0)
        plt.hist(dfQCD[names], color = 'b', alpha=0.5, bins=nbins, density=True, label='QCD')
        plt.hist(bkg_qcd[names], color = 'r', alpha=0.5, bins=nbins, density=True, label='!QCD')
        plt.legend(["QCD", "!QCD"])
        plt.xlabel(f"{names}")
        plt.ylabel("Entries")
        plt.savefig(f'inputs/fig_{names}_{region[i]}_qcd.pdf')
        plt.savefig(f'inputs/fig_{names}_{region[i]}_qcd.png')
        plt.gcf().clear()

        bkg_tt = pd.concat([dfQCD,dfTp],axis=0)
        plt.hist(dfTT[names], color = 'b', alpha=0.5, bins=nbins, density=True, label='TT')
        plt.hist(bkg_tt[names], color = 'r', alpha=0.5, bins=nbins, density=True, label='!TT')
        plt.legend(["TT", "!TT"])
        plt.xlabel(f"{names}")
        plt.ylabel("Entries")
        plt.savefig(f'inputs/fig_{names}_{region[i]}_tt.pdf')
        plt.savefig(f'inputs/fig_{names}_{region[i]}_tt.png')
        plt.gcf().clear()

        bkg_sig = pd.concat([dfQCD,dfTT],axis=0)
        plt.hist(dfTp[names], color = 'b', alpha=0.5, bins=nbins, density=True, label='Tprime')
        plt.hist(bkg_sig[names], color = 'r', alpha=0.5, bins=nbins, density=True, label='!Tprime')
        plt.legend(["Tprime", "!Tprime"])
        plt.xlabel(f"{names}")
        plt.ylabel("Entries")
        plt.savefig(f'inputs/fig_{names}_{region[i]}_tprime.pdf')
        plt.savefig(f'inputs/fig_{names}_{region[i]}_tprime.png')
        plt.gcf().clear()
        
        plt.hist(dfTT[names], color = 'r', alpha=0.5, bins=nbins, density=True, label='TT')
        plt.hist(dfQCD[names], color = 'g', alpha=0.5, bins=nbins, density=True, label='QCD')
        plt.hist(dfTp[names], color = 'b', alpha=0.5, bins=nbins, density=True, label='Tprime')
        plt.legend(["TT", "QCD", "Tprime"])
        plt.xlabel(f"{names}")
        plt.ylabel("Entries")
        plt.savefig(f'inputs/all/fig_{names}_{region[i]}_all.pdf')
        plt.savefig(f'inputs/all/fig_{names}_{region[i]}_all.png')
        plt.gcf().clear()
        
        print("done")
