import uproot
import numpy as np
import correctionlib
import correctionlib.convert
import correctionlib.schemav2 as cs
import rich

file_list = ['Tprime','QCD','TTToHadronic']
# to be extended - WJets

corr_list = []

for file_in in file_list:

    f_in = uproot.open(f'effMaps/map_{file_in}.root')

    for wp in ['L','M','T']:
    
        for f in ['b','c','l']:
        
            h = f_in[f'h_eff_{wp}_{f}']
            sfhist = h.to_hist()
        
            sfhist.name = f"btag_effMap_{wp}_{f}_{file_in}"
            sfhist.label = "out"
            btag_effMap = correctionlib.convert.from_histogram(sfhist)
            btag_effMap.description = f"btagging efficiency map at wp {wp} and flavour {f} for {file_in} in VLQ FH analysis"
            # set overflow bins behavior (default is to raise an error when out of bounds)
            btag_effMap.data.flow = "clamp"
            corr_list.append(btag_effMap)
            #rich.print(btag_effMap)

#print(corr_list)
cset = cs.CorrectionSet(
    schema_version=2,
    description="VLQ FH custom btag eff. map",
    corrections=corr_list,
)

with open("btagEff_VLQ_FH.json","w") as f_out:
    f_out.write(cset.model_dump_json(exclude_unset=True))
