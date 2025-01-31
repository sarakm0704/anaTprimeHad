/*
 * TprimeHadAnalyzer.h
 *
 *  Created on: 14 December, 2021
 *      Author: Jieun
 */

#ifndef TPRIMEHADANALYZER_H_
#define TPRIMEHADANALYZER_H_

#include "NanoAODAnalyzerrdframe.h"

class TprimeHadAnalyzer: public NanoAODAnalyzerrdframe
{
    public:
    //        TprimeHadAnalyzer(TTree *t, std::string outfilename, std::string year="",std::string runtype="",std::string syst="",  std::string jsonfname="", string globaltag="", int nthreads=1,int isDATA=-1 );
        TprimeHadAnalyzer(TTree *t, std::string outfilename);

        void defineCuts();
        void defineMoreVars();
        void bookHists();
        
        void setTree(TTree *t, std::string outfilename);
        void setupObjects();
        void setupAnalysis();
        void genStudy();
        void selectLeptons();
        void selectJets();
        void removeOverlaps();
        void synch();
        void calculateEvWeight();

//        private:
//            std::string year;
//            std::string runtype;
//
//            std::string syst;

        bool debug = false;

        bool _jsonOK;
        string _outfilename;

        TFile *_outrootfile;
        vector<string> _outrootfilenames;

        bool readgoodjson(string goodjsonfname); // get ready for applying golden JSON
        //json jsonroot;

		//std::string _jerctag;
		//std::string _jercunctag;
        //std::string _jercsys_total;
        //std::string _jercptres_type;
        //std::string _jercSF_type;

        void GetJetsys(string sys);
        
        //void setupCorrections(string goodjsonfname, string pufname, string putag, string btvfname, string btvtype, string jercfname, string jerctag, string jercunctag);
        //void setupCorrections(string goodjsonfname, string pufname, string putag, string btvfname, string btvtype, TString muonid_fname, TString muonid_type, TString muoniso_fname, TString muoniso_type, string muonreco_fname, string muonreco_type, TString elereco_fname, TString elerecotype, TString eleid_fname, TString eleidtype,  string jercfname, string jerctag, string jercunctag, string jercsys_total);
        //void setupCorrections(string goodjsonfname, string pufname, string putag, string btvfname, string btvtype, string jercfname, string jerctag, string jercunctag, string jercsys_total);

        void setupJetMETCorrection(string fname, string jettag);
        void applyJetMETCorrections();


};


#endif /* TPRIMEHADANALYZER_H_ */
