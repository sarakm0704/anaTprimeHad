//============================================================================
// Name        : nanoaodrdataframe.cpp
// Author      : Suyong Choi
// Version     :
// Copyright   : suyong@korea.ac.kr, Korea University, Department of Physics
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "NanoAODAnalyzerrdframe.h"
#include "TprimeHadAnalyzer.h"
//#include "SkimEvents.h"
#include "TChain.h"

using namespace std;
using namespace ROOT;

int main(void) {

	TChain c1("Events");
	//c1.Add("testinputdata/data/JetHT_2017C_DA05CA1A-3265-EE47-84F9-10CB09D22BDA.root"); //data
	c1.Add("testinputdata/MC/2017/ttJets-2017MC-A258F579-5EC0-D840-95D7-4327595FC3DE.root"); // MC
	TprimeHadAnalyzer nanoaodrdf(&c1, "testout.root");

	string goodjsonfname;
	string pileupfname;
	string pileuptag;
	string btvfname;
	string btvtype;
	string fname_btagEff;
	string fname_btagRatio;
	string hname_btagEff_bcflav;
	string hname_btagEff_lflav;
	string jercfname;
	string jerctag;
	string jercunctag;
    // di
    string jercsys_total;

	//nanoaodrdf.setupCorrections(goodjsonfname, pileupfname, pileuptag, btvfname, btvtype, jercfname, jerctag, jercunctag);
	//nanoaodrdf.setupCorrections(goodjsonfname, pileupfname, pileuptag, btvfname, btvtype, muonid_fname, muonid_type, muoniso_fname, muoniso_type, muonreco_fname, muonreco_type, elereco_fname, elerecotype, eleid_fname, eleidtype, jercfname, jerctag, jercunctag, jercsys_total);
	nanoaodrdf.setupCorrections(goodjsonfname, pileupfname, pileuptag, btvfname, fname_btagEff, fname_btagRatio, jercfname, jerctag, jercunctag, jercsys_total);
	nanoaodrdf.setupObjects();
	nanoaodrdf.setupAnalysis();
	nanoaodrdf.run(false, "outputTree");

	return EXIT_SUCCESS;
}
