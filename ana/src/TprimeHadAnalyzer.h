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
        TprimeHadAnalyzer(TTree *t, std::string outfilename, std::string year="",std::string runtype="",std::string syst="",  std::string jsonfname="", string globaltag="", int nthreads=1,int isDATA=-1 );
        void defineCuts();
        void defineMoreVars();
        void bookHists();
        void setTree(TTree *t, std::string outfilename);
        void setupAnalysis();
        void genStudy();
        void selectElectrons();
        void selectMuons();
        void selectJets();
//        void removeOverlaps();
        void synch();
        void selectFatJets();
        void calculateEvWeight();

        private:
            std::string year;
            std::string runtype;

            std::string syst;

};



#endif /* TPRIMEHADANALYZER_H_ */
