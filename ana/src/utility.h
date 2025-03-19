/*
 * utility.h
 *
 *  Created on: Dec 4, 2018
 *      Author: suyong
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"
#include "Math/Vector4D.h"
#include "correction.h"
#include <string>

using floats =  ROOT::VecOps::RVec<float>;
using doubles =  ROOT::VecOps::RVec<double>;
using ints =  ROOT::VecOps::RVec<int>;
using bools = ROOT::VecOps::RVec<bool>;
using uchars = ROOT::VecOps::RVec<unsigned char>;

using FourVector = ROOT::Math::PtEtaPhiMVector;
using FourVectorVec = std::vector<FourVector>;
using FourVectorRVec = ROOT::VecOps::RVec<FourVector>;


struct hist1dinfo
{
	ROOT::RDF::TH1DModel hmodel;
	std::string varname;
	std::string weightname;
	std::string mincutstep;
} ;

//for 2D histograms
struct hist2dinfo
{
  ROOT::RDF::TH2DModel hmodel;
  std::string varname1;
  std::string varname2;
  std::string weightname;
  std::string mincutstep;
} ;

struct varinfo
{
	std::string varname;
	std::string vardefinition;
	std::string mincutstep;
};

struct cutinfo
{
	std::string cutdefinition;
	std::string idx;
};


// generates vectors of 4 vectors given vectors of pt, eta, phi, mass
FourVectorVec generate_4vec(floats &pt, floats &eta, floats &phi, floats &mass);

FourVectorVec genmet4vec(float met_pt, float met_phi);

// return a vector size equal to length of x all filled with evWeight value
floats weightv(floats &x, float evWeight);

//std::unique_ptr<correction::CorrectionSet> _jerc_fname;

floats getsysJERC(std::unique_ptr<correction::CorrectionSet> &jercfname, floats &pts, floats &etas, std::string &tag);
floats JERCSF(std::unique_ptr<correction::CorrectionSet> &jercfname, std::string tag, std::string wp, floats &etas);
float getmetsmear(float &met, float &metphi, floats jetptsbefore, floats jetptsafter, floats jetphis);
floats JERCptResolution(std::unique_ptr<correction::CorrectionSet> &jercfname, std::string tag, floats &etas, floats &pts, floats &rhos);
floats GenMatchJetPt(floats &JetsPt, floats &JetsEta, floats &JetsPhi, floats &JetsMass, floats &GENJetsPt, floats &GENJetsEta, floats &GENJetsPhi, floats &GENJetsMass, floats &ptresolution);
floats getcJER(floats &JetsPt, floats &GENJetsPt, floats &SF, floats &ptresolution);

floats sphericity(FourVectorVec &p);

double foxwolframmoment(int l, FourVectorVec &p, int minj=0, int maxj=-1);

ints good_idx(ints good);

float topPtWeight(floats &genpts, ints &genid, ints &genflag);

floats lqtop_reconstruction( FourVectorVec &cjet, FourVectorVec &mu);

floats top_reconstruction_whad(FourVectorVec &jets, FourVectorVec &bjets, FourVectorVec &muons);

floats top_reco_products(FourVectorVec &jets, FourVectorVec &muons, floats topreco);


float calculate_deltaEta( FourVector &p1, FourVector &p2);

float calculate_deltaPhi( FourVector &p1, FourVector &p2);

float calculate_deltaR( FourVector &p1, FourVector &p2);

float calculate_invMass( FourVector &p1, FourVector &p2);

float calculate_goodHT( floats jet_pt );

float calculate_RelHT( FourVector &top, FourVector &higgs, float ht );

float calculate_newRelHT( FourVector &top, FourVector &higgs, float oj_pt, float ht );

FourVector sum_4vec( FourVector &p1, FourVector &p2);

FourVector sum_Five4vec( FourVector &p1, FourVector &p2, FourVector &p3, FourVector &p4, FourVector &p5);

floats sort_discriminant( floats discr, floats obj );
floats sort_intdisc( floats discr, ints obj );

FourVector select_leadingvec( FourVectorVec &v );

//========pair example =======================//
//w reconstruction from 2 jets  definition
floats w_reconstruction (FourVectorVec &jets);

floats Tprime_reconstruction(FourVectorVec &jets, FourVectorVec &bjets);

floats mindR_bb(FourVectorVec &bjets);
floats dR_bb(FourVectorVec &bjets);
floats m_bb(FourVectorVec &bjets);

int count5s(floats targets, float obj1, float obj2, float obj3, float obj4, float obj5);
int count3s(floats targets, float obj1, float obj2, float obj3);
int count2s(floats targets, float obj1, float obj2);

bool isHadWHiggs(FourVectorVec &p, ints &pdgId, ints &midx);

//floats btv_shape_correction(std::unique_ptr<correction::CorrectionSet> &cset, std::string sys, floats &pts, floats &etas, ints &hadflav, floats &btags);

//float btv_case1(std::unique_ptr<correction::CorrectionSet> &cset, std::string type, std::string sys, std::string sysl, std::string wp, ints &hadflav, floats &etas, floats &pts );
float btv_case1( std::unique_ptr<correction::CorrectionSet> &cset, std::string sys, std::string sysl, std::string wp, ints &hadflav, floats &etas, floats &pts );

float btv_effMap( std::unique_ptr<correction::CorrectionSet>& eff, std::string wp, ints &hadflav, floats &etas, floats &pts );

float producer_btagWeight(std::unique_ptr<correction::CorrectionSet>& cset, std::unique_ptr<correction::CorrectionSet>& eff, std::string sys, std::string sysl, ints &hadflav, floats &etas, floats &pts, floats &discs, ints &wpL, ints &wpM, ints &wpT, bool isTp, bool isTT, bool isQCD, bool isST, bool isVJets, bool isttH);

float pucorrection(std::unique_ptr<correction::CorrectionSet> &cset, std::string name, std::string syst, float ntruepileup);

floats PrintVector(floats myvector);
floats compute_DR (FourVectorVec &muons, ints goodMuons_charge);
#endif /* UTILITY_H_ */
