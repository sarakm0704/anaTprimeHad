/*
 * NanoAODAnalyzerrdframe.h
 *
 *  Created on: Sep 30, 2018
 *      Author: suyong
 */

#ifndef NANOAODANALYZERRDFRAME_H_
#define NANOAODANALYZERRDFRAME_H_

#include "TTree.h"
#include "TFile.h"

#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"

//#include "Math/Vector4D.h"

#include "correction.h"

#include <string>
#include <vector>
#include <map>
//#include "rapidjson/document.h"
#include "nlohmann/json.hpp"

#include "utility.h" // floats, etc are defined here
#include "RNodeTree.h"
#include "TCut.h"


using namespace ROOT::RDF;
using namespace std;

class TH1D;

using json = nlohmann::json;

class NanoAODAnalyzerrdframe {
	using RDF1DHist = RResultPtr<TH1D>;
	using RDF2DHist = RResultPtr<TH2D>;
public:
    NanoAODAnalyzerrdframe(string infilename, string intreename, string outfilename);
    NanoAODAnalyzerrdframe(TTree *t, string outfilename);
    virtual ~NanoAODAnalyzerrdframe();
    
    //void setupCorrections(string goodjsonfname, string pufname, string putag, string btvfname, string btvtype, string jercfname, string jerctag, string jercunctag);
    //void setupCorrections(string goodjsonfname, string pufname, string putag, string btvfname, string btvtype, string fname_btagEff, string jercfname, string jerctag, string jercunctag, string jercsys_total);
    void setupCorrections(string goodjsonfname, string pufname, string putag, string btvfname, string fname_btagEff, string jercfname, string jerctag, string jercunctag, string jercsys_total);
    virtual void setupObjects();
    virtual void setupAnalysis();
    virtual void setTree(TTree *t, string outfilename);
    
    // object selectors
    // RNode is in namespace ROOT::RDF
    bool readgoodjson(string goodjsonfname); // get ready for applying golden JSON

    // Jet MET corrections
    //void GetJetsys(string sys);
    //void setupJetMETCorrection(string fname, string jettag);
    //void applyJetMETCorrections();
    void selectFatJets();
    void removeOverlaps();
    
    void addVar(varinfo v);
    
    // define variables
    template <typename T, typename std::enable_if<!std::is_convertible<T, string>::value, int>::type = 0>
    void defineVar(string varname, T function,  const RDFDetail::ColumnNames_t &columns = {})
    {
    	_rlm = _rlm.Define(varname, function, columns);
    };
    
    void addVartoStore(string varname);
    void addCuts(string cut, string idx);
    void add1DHist(TH1DModel histdef, string variable, string weight, string mincutstep="");
	void add2DHist(TH2DModel histdef, string variable1, string variable2, string weight, string mincutstep="");

    double getBTaggingEff(double hadflav, double eta, double pt);

	//TFile *f_btagEff;
	//TH2D *hist_btagEff_bcflav;
	//TH2D *hist_btagEff_lflav;

    ROOT::RDF::RNode calculateBTagSF(RNode _rlm, std::vector<std::string> Jets_vars, int _case, const double btag_cut, std::string _BTaggingWP = "M", std::string output_var = "btag_SF_");
    
    void setupCuts_and_Hists();
    void drawHists(RNode t);
    void run(bool saveAll=true, string outtreename="outputTree");
    
    void setupTree();
    
    //setting parameters for nanoaod
    void setParams(int year, string runtype, int datatype, string sampletype, string region, string topPtReweight, string topPtReweightsys, string jecsys, string jersys, string btagsys, string btagsysuncorr);
    int _year;
    string _runtype;
    int _datatype;
    string _sampletype;
    string _region;

    string _topPtReweight;
    string _topPtReweightsys;

    bool _isTprime =false;
    bool _isTT =false;
    bool _isQCD =false;
    bool _isST =false;
    bool _isVJets =false;
    bool _isttH =false;

    bool _is2M1L =false;
    bool _is3L =false;
    bool _is3M =false;
    bool _is3T =false;

    bool _isUL =false;
    bool _isReReco = false;
    bool _isData;
    TTree* _atree;
    bool debug = true;
   
    std::string _jecsys; 
    std::string _jersys; 
    
    //initialize HLT names
    std::string ctrlBranchName(string str_Branch);
    std::string setHLT(string str_HLT = "" );
    std::vector< std::string > HLTGlobalNames;
    std::vector< std::string > HLT2016Names;
    std::vector< std::string > HLT2017Names;
    std::vector< std::string > HLT2018Names;

    //initialize object IDs
    std::string ElectronID(int cutbasedID);
    std::string MuonID(int cutbasedID);
    std::string JetID(int cutbasedID);
    
    //private:
    ROOT::RDataFrame _rd;
    
    //bool _isData;
    bool _jsonOK;
    string _outfilename;
    string _jsonfname;
    
    TFile *_outrootfile;
    vector<string> _outrootfilenames;
    RNode _rlm;
    map<string, RDF1DHist> _th1dhistos;
    bool helper_1DHistCreator(string hname, string title, const int nbins, const double xlow, const double xhi, string rdfvar, string evWeight, RNode *anode);
    vector<hist1dinfo> _hist1dinfovector;

	//for 2D histograms
	//map<string, RDF2DHist> _th2dhistos;
	//bool helper_2DHistCreator(string hname, string title, const int nbinsx, const double xlow, const double xhi, const int nbinsy, const double ylow, const double yhi, string rdfvarx, string rdfvary, string evWeight, RNode *anode);
    //vector<hist2dinfo> _hist2dinfovector;

    vector<string> _originalvars;
    vector<string> _selections;

    vector<varinfo> _varinfovector;
    vector<cutinfo> _cutinfovector;
    
    vector<string> _varstostore;
    map<string, vector<std::string>> _varstostorepertree;
    
    // using rapidjson
    //for applying golden json to data
    //rapidjson::Document jsonroot;
    
    json jsonroot;

    // JERC scale factors
    std::unique_ptr<correction::CorrectionSet> _jerc_fname;

    string _jercptres_type;
    string _jercSF_type; 
    string _jercsys_total;

    std::unique_ptr<correction::CorrectionSet> _correction_jerc; // json containing all forms of corrections and uncertainties
    std::shared_ptr<const correction::CompoundCorrection> _jetCorrector; // just the combined L1L2L3 correction
    std::shared_ptr<const correction::Correction> _jetCorrectionUnc; // for uncertainty corresponding to the jet corrector
    
    // btag correction
    std::unique_ptr<correction::CorrectionSet> _correction_btag1;
    std::unique_ptr<correction::CorrectionSet> _efficiency_btag1;

    //string _btvtype;

    // pile up weights
    std::unique_ptr<correction::CorrectionSet> _correction_pu;
    string _putag;

    string _jerctag;
    string _jercunctag;

    RNodeTree _rnt;
    
    bool isDefined(string v);

};

#endif /* NANOAODANALYZERRDFRAME_H_ */
