/*
 * GJetAnalyzer.h
 *
 *  Created on: 14 December, 2021
 *      Author: Jieun
 */

#ifndef TPRIMEHADANALYZER_H_
#define TPRIMEHADANALYZER_H_

#include "NanoAODAnalyzerrdframe.h"

class GJetAnalyzer: public NanoAODAnalyzerrdframe
{
    public:
    //        GJetAnalyzer(TTree *t, std::string outfilename, std::string year="",std::string runtype="",std::string syst="",  std::string jsonfname="", string globaltag="", int nthreads=1,int isDATA=-1 );
        GJetAnalyzer(TTree *t, std::string outfilename);
        void defineCuts();
        void defineMoreVars();
        void bookHists();
        
        void setTree(TTree *t, std::string outfilename);
        void setupObjects();
        void setupAnalysis();
        void selectLeptons();
        void selectPhotons();
        void selectJets();
        //  void removeOverlaps();
        //void calculateEvWeight();

//        private:
//            std::string year;
//            std::string runtype;
//
//            std::string syst;

        bool debug = false;
};


#endif /* TPRIMEHADANALYZER_H_ */
