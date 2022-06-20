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

floats sphericity(FourVectorVec &p);

double foxwolframmoment(int l, FourVectorVec &p, int minj=0, int maxj=-1);

ints good_idx(ints good);

floats lqtop_reconstruction( FourVectorVec &cjet, FourVectorVec &mu);

floats top_reconstruction_whad(FourVectorVec &jets, FourVectorVec &bjets, FourVectorVec &muons);

floats top_reco_products(FourVectorVec &jets, FourVectorVec &muons, floats topreco);


float calculate_deltaEta( FourVector &p1, FourVector &p2);

float calculate_deltaPhi( FourVector &p1, FourVector &p2);

float calculate_deltaR( FourVector &p1, FourVector &p2);

float calculate_invMass( FourVector &p1, FourVector &p2);

float calculate_goodHT( floats jet_pt );

float calculate_RelHT( FourVector &top, FourVector &higgs, float ht );

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

#endif /* UTILITY_H_ */
