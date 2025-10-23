/*
 * utility.cpp
 *
 *  Created on: Dec 4, 2018
 *      Author: suyong
 */
#include "utility.h"
#include "TMatrixDSym.h"
#include "TVectorT.h"
#include "Math/SpecFuncMathMore.h"
#include "Math/GenVector/VectorUtil.h"
#include "Math/GenVector/Rotation3D.h"
#include "Math/Math.h"
#include "correction.h"

#include "TRandom2.h"

#include <bitset>

using namespace std;

// Utility function to generate fourvector objects for thigs that pass selections

//FourVectorVec gen4vec(floats &pt, floats &eta, floats &phi, floats &mass)
FourVectorVec generate_4vec(floats &pt, floats &eta, floats &phi, floats &mass)
{
	const int nsize = pt.size();
	FourVectorVec fourvecs;
	fourvecs.reserve(nsize);
	for (auto i=0; i<nsize; i++)
	{
		fourvecs.emplace_back(pt[i], eta[i], phi[i], fabs(mass[i]));
	}

	return fourvecs;
}

FourVectorVec genmet4vec(float met_pt, float met_phi)
{
        FourVectorVec vecs;
        float met_px = met_pt*cos(met_phi);
        float met_py = met_pt*sin(met_phi);
        for(int i = -500; i <= 500; i+=50){
                FourVector metfourvec;
                metfourvec.SetPxPyPzE(met_px, met_py, i, met_pt);
                vecs.emplace_back(metfourvec);
        }
        return vecs;
}

floats weightv(floats &x, float evWeight)
{
	const int nsize = x.size();
	floats weightvector(nsize, evWeight);
	return weightvector;
}

floats getsysJERC(std::unique_ptr<correction::CorrectionSet> &jercfname, floats &pts, floats &etas, string &tag)
{
        floats Xvars;
        //for (auto i=0; i<etas.size(); i++){
        for (unsigned int i=0; i<etas.size(); i++){
            float w = 0.0;
            if(pts[i] > 9.0 && pts[i] < 6538.0 && abs(etas[i]) < 5.4){
                w = jercfname->at(tag)->evaluate({float(etas[i]), float(pts[i])});
            }
            Xvars.emplace_back(w);
        }
        return Xvars;
}

floats JERCSF(std::unique_ptr<correction::CorrectionSet> &jercfname, string tag, string wp, floats &etas)
{
        floats Xvars;
        //for (auto i=0; i<etas.size(); i++){
        for (unsigned int i=0; i<etas.size(); i++){
                float w = jercfname->at(tag)->evaluate({float(etas[i]),wp});
                Xvars.emplace_back(w);
        }
        return Xvars;
}

float getmetsmear(float &met, float &metphi, floats jetptsbefore, floats jetptsafter, floats jetphis)
{
        auto metx = met * cos(metphi);
        auto mety = met * sin(metphi);
        //for (auto j=0; j<jetptsbefore.size(); j++){
        for (unsigned int j=0; j<jetptsbefore.size(); j++){
                if(jetptsafter[j] > 15.0){
                        metx -= (jetptsafter[j] - jetptsbefore[j])*cos(jetphis[j]);
                        mety -= (jetptsafter[j] - jetptsbefore[j])*sin(jetphis[j]);
                }
        }
        return float(sqrt(metx*metx + mety*mety));
}

floats JERCptResolution(std::unique_ptr<correction::CorrectionSet> &jercfname, string tag, floats &etas, floats &pts, floats &rhos)
{
        floats Xvars;
        //for (auto i=0; i<pts.size(); i++){
        for (unsigned int i=0; i<pts.size(); i++){
                float w = jercfname->at(tag)->evaluate({float(etas[i]),float(pts[i]),float(rhos[i])});
                Xvars.emplace_back(w);
        }
        return Xvars;
}

floats GenMatchJetPt(floats &JetsPt, floats &JetsEta, floats &JetsPhi, floats &JetsMass, floats &genJetsPt, floats &genJetsEta, floats &genJetsPhi, floats &genJetsMass, floats &ptresolution)
{
        float MatchgenJet_pt = -99.0;
        float mindR = 99.0;
        floats Xvars;
        //for(int i = 0; i < JetsPt.size(); i++){
        for(unsigned int i = 0; i < JetsPt.size(); i++){
                mindR = 99.0;
                MatchgenJet_pt = -99.0;
                for(unsigned int j = 0; j < genJetsPt.size(); j++){
                       float dr = ROOT::VecOps::DeltaR<float>(JetsEta[i], genJetsEta[j], JetsPhi[i], genJetsPhi[j]);
                       if(dr < 0.2 && abs(JetsPt[i]-genJetsPt[j])<3*JetsPt[i]*ptresolution[i]){
                              if(dr < mindR){
                                     MatchgenJet_pt = genJetsPt[j];
                              } 
                       }
                }
                Xvars.emplace_back(MatchgenJet_pt);
        }
        return Xvars;
}

floats getcJER(floats &JetsPt, floats &genJetsPt, floats &SF, floats &ptresolution)
{
        float w = 1.0;
        floats Xvars;
        //for(int i = 0; i < JetsPt.size(); i++){
        for(unsigned int i = 0; i < JetsPt.size(); i++){
                if(genJetsPt[i] > -9.0){
                       w = 1 + (SF[i]-1)*(JetsPt[i]-genJetsPt[i])/JetsPt[i];
                }
                else{
                       Double_t randm = gRandom->Gaus(0,ptresolution[i]);
                       w = 1 + randm*TMath::Sqrt(TMath::Max(SF[i]*SF[i] - 1.0, 0.0));
                }
                Xvars.emplace_back(w);
        }
        return Xvars;
}

floats sphericity(FourVectorVec &p)
{
	TMatrixDSym NormMomTensor(3);

	NormMomTensor = 0.0;
	double p2sum = 0.0;
	for (auto x: p)
	{
		p2sum += x.P2();
		double mom[3] = {x.Px(), x.Py(), x.Pz()};
		for (int irow=0; irow<3; irow++)
		{
			for (int icol=irow; icol<3; icol++)
			{
				NormMomTensor(irow, icol) += mom[irow] * mom[icol];
			}
		}
	}
	NormMomTensor *= (1.0/p2sum);
	TVectorT<double> Qrev;
	NormMomTensor.EigenVectors(Qrev);
	floats Q(3);
	for (auto i=0; i<3; i++) Q[i] = Qrev[2-i];

	return Q;
}


double foxwolframmoment(int l, FourVectorVec &p, int minj, int maxj)
{   // PRD 87, 073014 (2013)
	double answer = 0.0;

	double ptsum=0.0;

	if (maxj==-1) // process everything
	{
		maxj = p.size();
	}
	//for (auto x: p)
	for (auto i=minj; i<maxj; i++)
	{
		auto x = p[i];
		ptsum += x.Pt();
		//for (auto y: p)
		for (auto j=minj; j<maxj; j++)
		{
			auto y = p[j];
			double wij = x.Pt() * y.Pt();
			double cosdOmega = x.Vect().Dot(y.Vect()) / (x.P() * y.P());
			if (cosdOmega>1.0) cosdOmega=1.0;
			if (cosdOmega<-1.0) cosdOmega=-1.0;
			answer += wij * ROOT::Math::legendre(l, cosdOmega);
		}
	}
	answer /= ptsum*ptsum;
	if (fabs(answer)>1.0) std::cout << "FW>1 " << answer << std::endl;
	return answer;
}


ints good_idx(ints good)
{
        ints out;
        for(unsigned int i = 0; i < good.size(); i++){
                if( good[i] ){
                        out.emplace_back(i);
                }
        }
        return out;
}

float topPtWeight(floats &genpts, ints &genid, ints &genflag)
{
        float wtop = 1.0;
        float wtopbar = -1.0;
        bool top = false;
        bool topbar = false;
        //for(int i = 0; i < genpts.size(); i++){
        for(unsigned int i = 0; i < genpts.size(); i++){
                //cout<<bitset<16>(genflag[i])<<endl;
                //cout<<bitset<16>(genflag[i])[0]<<endl;
                //cout<<"genflag "<<genflag[i]<<endl;
                if(genid[i] == 6 && bitset<16>(genflag[i])[13]==1){
                       //cout<<bitset<16>(genflag[i])<<endl;
                //if(genid[i] == 6 && genflag[i] > 8192 && genflag[i] < 16384){
                       top = true;
                       if(genpts[i] < 500){
                //           cout<<"top lhe pt is "<<genpts[i]<<endl;
                           wtop = TMath::Exp(0.0615 - 0.0005*genpts[i]);
                       }
                       else{
                           wtop = TMath::Exp(0.0615 - 0.0005*500);
                       }
                }
                if(genid[i] == -6 && bitset<16>(genflag[i])[13]==1){
                       //cout<<bitset<16>(genflag[i])<<endl;
                       topbar = true;
                 //      cout<<"topbar lhe pt is "<<genpts[i]<<endl;
                       if(genpts[i] < 500){
                            wtopbar = TMath::Exp(0.0615 - 0.0005*genpts[i]);
                       }
                       else{
                            wtopbar = TMath::Exp(0.0615 - 0.0005*500);
                       }
                }
        }
        if(top == true && topbar == true){
                return TMath::Sqrt(wtop*wtopbar);
        }
        else{
                return 1.0;
        }
}

floats chi2(float smtop_mass, float smw_mass, float lfvtop_mass)
{
	floats out;
        // Theory values
//        const float MT_LFV = 172.5;
//        const float MT_SM = 172.5;
//        const float MW = 80.4;
//        const float WT_LFV = 1.41;
//        const float WT_SM = 1.41;
//        const float WW = 2.085;

        // Resolution applied values
        const float MT_LFV = 150.5;
        const float MT_SM = 165.2;
        const float MW = 80.8;
        const float WT_LFV = 17.8;
        const float WT_SM = 21.3;
        const float WW = 11.71;	

        float chi2_SMTop = pow((MT_SM-smtop_mass)/WT_SM, 2);
        float chi2_SMW = pow((MW-smw_mass)/WW, 2);
        float chi2_LFVTop = pow((MT_LFV-lfvtop_mass)/WT_LFV, 2);
        float chi2 = chi2_SMTop + chi2_SMW + chi2_LFVTop;

	out.emplace_back(chi2);
	out.emplace_back(chi2_SMTop);
	out.emplace_back(chi2_SMW);
	out.emplace_back(chi2_LFVTop);
	
	return out;
}


//floats top_reconstruction_whad(FourVectorVec &jets, FourVectorVec &bjets, FourVectorVec &muons, FourVectorVec &taus){
floats top_reconstruction_whad(FourVectorVec &jets, FourVectorVec &bjets, FourVectorVec &muons){
        
        floats out;

        float LFVtop_mass, SMW_mass, SMtop_mass;
        float X_LFVtop, X_SMW, X_SMtop;
        float X_min=9999999999, X_min_LFVtop_mass=-1, X_min_SMW_mass=-1, X_min_SMtop_mass=-1;
        float X_min_LFVtop=999999999, X_min_SMW=999999999, X_min_SMtop=999999999;
        float c_idx=-1, wj1_idx=-1, wj2_idx=-1;
        
        // Mass and Width of top and w boson
        const float MT_LFV = 150.5;
        const float MT_SM = 165.2;
        const float MW = 80.8;
        const float WT_LFV = 17.8;
        const float WT_SM = 21.3;
        const float WW = 11.71;	
        
        // U or C jet
        for(unsigned int j1 = 0; j1<jets.size(); j1++){
            //LFVtop_mass = (jets[j1]+taus[0]+muons[0]).M();
            LFVtop_mass = (jets[j1]+muons[0]).M();
            X_LFVtop = std::pow((MT_LFV-LFVtop_mass)/WT_LFV,2);
            // Jet1 from W
            for(unsigned int j2 = 0; j2<jets.size(); j2++){
                if(jets[j2].Pt() == bjets[0].Pt() || jets[j2].Pt() == jets[j1].Pt()) continue;
                // Jet2 from W
                for(unsigned int j3 = 0; j3<jets.size(); j3++){
                    if(jets[j3].Pt() == jets[j2].Pt() || jets[j3].Pt() == bjets[0].Pt() || jets[j3].Pt() == jets[j1].Pt()) continue;
                    SMW_mass = (jets[j2]+jets[j3]).M();
                    X_SMW = std::pow((MW-SMW_mass)/WW,2);
                    SMtop_mass = (bjets[0]+jets[j2]+jets[j3]).M();
                    X_SMtop = std::pow((MT_SM-SMtop_mass)/WT_SM,2);
                    //min error
                    if (X_LFVtop + X_SMW + X_SMtop < X_min){
                        X_min = X_LFVtop + X_SMW + X_SMtop;
                        X_min_LFVtop = X_LFVtop;
                        X_min_SMW = X_SMW;
                        X_min_SMtop = X_SMtop;
                        X_min_LFVtop_mass = LFVtop_mass;
                        X_min_SMW_mass = SMW_mass;
                        X_min_SMtop_mass = SMtop_mass;
                        c_idx = float(j1);
                        wj1_idx = float(j2);
                        wj2_idx = float(j3);
                    }
                }
            }
        }
        out.push_back(X_min);               // 0
        out.push_back(X_min_LFVtop_mass);   // 1
        out.push_back(X_min_SMW_mass);      // 2
        out.push_back(X_min_SMtop_mass);    // 3
        out.push_back(c_idx);               // 4
        out.push_back(wj1_idx);             // 5
        out.push_back(wj2_idx);             // 6
        out.push_back(X_min_LFVtop);        // 7
        out.push_back(X_min_SMW);           // 8
        out.push_back(X_min_SMtop);         // 9

        return out;
}

//floats top_reco_products(FourVectorVec &jets, FourVectorVec &muons, FourVectorVec &taus, floats topreco){
floats top_reco_products(FourVectorVec &jets, FourVectorVec &muons, floats topreco){
        floats out;
        int j_idx = topreco[4];
        int wjet1_idx = topreco[5];
        int wjet2_idx = topreco[6];

        FourVector lfvjet = jets[j_idx];
        FourVector wjet1 = jets[wjet1_idx];
        FourVector wjet2 = jets[wjet2_idx];
        //FourVector tau = taus[0];
        FourVector muon = muons[0];

        float wqq_dEta = wjet1.Eta() - wjet2.Eta();
        float wqq_dPhi = ROOT::Math::VectorUtil::DeltaPhi(wjet1, wjet2);
        float wqq_dR = ROOT::Math::VectorUtil::DeltaR(wjet1, wjet2);

        float lfvjmu_dEta = lfvjet.Eta() - muon.Eta();
        float lfvjmu_dPhi = ROOT::Math::VectorUtil::DeltaPhi(lfvjet, muon);
        float lfvjmu_dR = ROOT::Math::VectorUtil::DeltaR(lfvjet, muon);
        float lfvjmu_mass = ROOT::Math::VectorUtil::InvariantMass(lfvjet, muon);

        /*float lfvjtau_dEta = lfvjet.Eta() - tau.Eta();
        float lfvjtau_dPhi = ROOT::Math::VectorUtil::DeltaPhi(lfvjet, tau);
        float lfvjtau_dR = ROOT::Math::VectorUtil::DeltaR(lfvjet, tau);
        float lfvjtau_mass = ROOT::Math::VectorUtil::InvariantMass(lfvjet, tau);

        FourVector mutau = muon + tau;
        float lfvjmutau_dEta = lfvjet.Eta() - mutau.Eta();
        float lfvjmutau_dPhi = ROOT::Math::VectorUtil::DeltaPhi(lfvjet, mutau);
        float lfvjmutau_dR = ROOT::Math::VectorUtil::DeltaR(lfvjet, mutau);
        float lfvjmutau_mass = ROOT::Math::VectorUtil::InvariantMass(lfvjet, mutau);

        */
	out.emplace_back(wqq_dEta);         //0
        out.emplace_back(wqq_dPhi);         //1
        out.emplace_back(wqq_dR);           //2
        out.emplace_back(lfvjmu_dEta);      //3
        out.emplace_back(lfvjmu_dPhi);      //4
        out.emplace_back(lfvjmu_dR);        //5
        out.emplace_back(lfvjmu_mass);      //6
        //out.emplace_back(lfvjtau_dEta);     //7
        //out.emplace_back(lfvjtau_dPhi);     //8
        //out.emplace_back(lfvjtau_dR);       //9
        //out.emplace_back(lfvjtau_mass);     //10
        //out.emplace_back(lfvjmutau_dEta);   //11
        //out.emplace_back(lfvjmutau_dPhi);   //12
        //out.emplace_back(lfvjmutau_dR);     //13
        //out.emplace_back(lfvjmutau_mass);   //14

        return out;
}


float calculate_deltaEta( FourVector &p1, FourVector &p2){
        return p1.Eta() - p2.Eta();
}

float calculate_deltaPhi( FourVector &p1, FourVector &p2){
        return ROOT::Math::VectorUtil::DeltaPhi(p1, p2);
}

float calculate_deltaR( FourVector &p1, FourVector &p2){
        return ROOT::Math::VectorUtil::DeltaR(p1, p2);
}

float calculate_invMass( FourVector &p1, FourVector &p2){
        return ROOT::Math::VectorUtil::InvariantMass(p1, p2);
}

float calculate_goodHT( floats jet_pt ){

        float out = 0;
        for (unsigned int i = 0; i<jet_pt.size(); i++) if(jet_pt[i] > 30 ) out += jet_pt[i];
        return out;
}

float calculate_RelHT( FourVector &top, FourVector& higgs, float ht ){
 
        //std::cout << "Whats happening" << std::endl;
        //std::cout << "top " << top << " higgs: " << higgs << " ht: " << ht << std::endl;

        float out = 0;
        if ( top.Pt() < 10E+20 && !isnan(top.Pt()) && !isinf(top.Pt()) && !isnan(higgs.Pt()) && !isinf(higgs.Pt()) ) out = (top.Pt() + higgs.Pt()) / ht;
        //std::cout<< "so at the end: " << out << std::endl;
        
        return out;
        //return (top.Pt() + higgs.Pt()) / ht;
}

float calculate_newRelHT( FourVector &top, FourVector& higgs, float oj_pt, float ht ){
 
        //std::cout << "Whats happening" << std::endl;
        //std::cout << "top " << top << " higgs: " << higgs << " ht: " << ht << std::endl;

        float out = 0;
        if ( top.Pt() < 10E+20 && !isnan(top.Pt()) && !isinf(top.Pt()) && !isnan(higgs.Pt()) && !isinf(higgs.Pt()) ) out = (top.Pt() + higgs.Pt() + oj_pt) / ht;
        //std::cout<< "so at the end: " << out << std::endl;
        
        return out;
        //return (top.Pt() + higgs.Pt()) / ht;
}

FourVector sum_4vec( FourVector &p1, FourVector &p2){
        return p1+p2;
}

FourVector sum_Five4vec( FourVector &p1, FourVector &p2, FourVector &p3, FourVector &p4, FourVector &p5){
        return p1+p2+p3+p4+p5;
}

floats sort_discriminant( floats discr, floats obj ){
        auto sorted_discr = Reverse(Argsort(discr));
        floats out;
        for (auto idx : sorted_discr){
                out.emplace_back(obj[idx]);
        }
        return out;
}

floats sort_intdisc( floats discr, ints obj ){
        auto sorted_discr = Reverse(Argsort(discr));
        floats out;
        for (auto idx : sorted_discr){
                out.emplace_back(obj[idx]);
        }
        return out;
}

FourVector select_leadingvec( FourVectorVec &v ){
    FourVector vout;
    if(v.size() > 0) return v[0];
    else return vout;
}

ints find_element( ints vec, int a ){
        ints out;
        for(unsigned int i = 0; i < vec.size(); i++){
            if( vec[i] == a ) out.emplace_back(i);
        }
        return out;
}

//=====================build pair example=============================================//
//W reconstruction : 2 jets
//====================================================================================//
floats w_reconstruction (FourVectorVec &jets){
        floats out;
        float dijetMass;
        float dijetMass_out;
        float dijetDR;
        
        const float Mass_W = 80.9; //W mass 
        const float Width_W = 10.8; //W width
        float X_Min = 99999;
        float X_Recwidth_W; //
        
        //Loop on all selected jets
        for(unsigned int j1 = 0; j1<jets.size()-1; j1++){
                for(unsigned int j2 = j1+1; j2<jets.size(); j2++){
                        //select 2 jets
                        dijetMass = (jets[j1]+jets[j2]).M();
                        //select a best W candidate in min width in a event
                        X_Recwidth_W = std::pow((Mass_W-dijetMass)/Width_W,2);
                        if (X_Recwidth_W<X_Min){
                                dijetDR = ROOT::Math::VectorUtil::DeltaR(jets[j1],jets[j2]);
                                X_Min = X_Recwidth_W;
                                dijetMass_out = dijetMass;
                        }
                }
        }
        out.push_back(dijetMass_out);   //0:w_mass
        out.push_back(dijetDR);         //1:dijet_dr
        return out;
}

//====================================================================================//
//               H/Z + W + Top reconstruction : for hadronic channel                  //
//====================================================================================//
floats Tprime_reconstruction(FourVectorVec &jets, FourVectorVec &bjets){
//TODO WIP: feeding Z or H
//floats Tprime_reconstruction(FourVectorVec &jets, FourVectorVec &bjets, YEAR, MASS OR STRING OR OPTION?){

    //Store Jet idx and Chi2 from Higgs/W/Top
    floats out;
    float hj1_idx=-1, hj2_idx=-1, wj1_idx=-1, wj2_idx=-1, tjb_idx=-1, oj_idx=-1;

    float tmpH_mass=-1, tmpW_mass=-1, tmpTop_mass=-1;
    float H_mass, W_mass, Top_mass;
    float secondTop_mass=-1, secondW_mass=-1, Tprime_mass=-1, WH_mass=-1;
    float Chi2_H, Chi2_W, Chi2_Top;
    float Chi2_max=-1;
    float Chi2_min=FLT_MAX;
    float Chi2_min_H=FLT_MAX, Chi2_min_W=FLT_MAX, Chi2_min_Top=FLT_MAX;

    float hb1_e=-1, hb2_e=-1, tb_e=-1;

    // Mass and Width - 2018UL
    //const float trueSenario_mass;
    const float trueH_mass = 120.2;
    //const float trueZ_mass = 90.9;
    // B2G-19-001
    const float trueTop_mass = 175.9;
    const float trueW_mass = 83.9;
//    const float trueTop_mass = 50;
//    const float trueW_mass = 50;
    // PDG ? B2G-24-020
    //const float trueTop_mass = 172.69;
    //const float trueW_mass = 80.28;

    const float widthH = 14.3;
    //const float widthZ = 11.3;
    // B2G-19-001
    const float widthTop = 17.2;
    const float widthW = 10.8;
    // PDG ? B2G-24-020
    //const float widthTop = 17.2;
    //const float widthW = 10.8;
    
    //cout << "number of jets: " << jets.size() << " number of bjets: " << bjets.size() << endl;

    // making jet paring for candidates

    // 1) H/Z candiates
    // loop on all selected b-tag jets,
    for(unsigned int b1 = 0; b1<bjets.size()-1; b1++){
	//cout << "b1: " << bjets[b1].E() << endl;
        for(unsigned int b2 = b1+1; b2<bjets.size(); b2++){
	    //cout << "b2: " << bjets[b2].E() << endl;
            // select two jets, to make a H/Z candidate
            // and evaluate H/Z Chi2 - minimize before carrying on the loop
            tmpH_mass = (bjets[b1]+bjets[b2]).M();
            Chi2_H = std::pow((trueH_mass-tmpH_mass)/widthH,2);
            if (Chi2_H < Chi2_min_H){
                Chi2_min_H = Chi2_H;
                hj1_idx = b1;
                hj2_idx = b2;
                H_mass = tmpH_mass;

		        hb1_e = bjets[b1].E();
	            hb2_e = bjets[b2].E();
            }
        }
    }

    // 2) W candidate
    // loop on all selected jets,
    for(unsigned int j1 = 0; j1<jets.size()-1; j1++){
	//cout << "j1: " << jets[j1].E() << endl;
        // reject the jets used for the H/Z candidate,
        // why not pT - this algorithm messed up when it has jets with the same pT - 23/46973 entries
        if (jets[j1].E() == bjets[hj1_idx].E() || jets[j1].E() == bjets[hj2_idx].E()) continue;
        //cout << "I'm not higgs candidates" << endl;
        for(unsigned int j2 = j1+1; j2<jets.size(); j2++){
	    //cout << "j2: " << jets[j2].E() << endl;
            if (jets[j2].E() == bjets[hj1_idx].E() || jets[j2].E() == bjets[hj2_idx].E()) continue;
            //cout << "I'm not higgs candidates" << endl;
            // select two jets, to make a W candidate
            // and evaluate W Chi2
            tmpW_mass = (jets[j1]+jets[j2]).M();
            Chi2_W = std::pow((trueW_mass-tmpW_mass)/widthW,2);
            
            // 3) Top candidate
            // loop on all selected b-jets
            for(unsigned int b = 0; b<bjets.size(); b++){
	        //cout << "b: " << bjets[b].E() << endl;
                // reject the jets used for the H/Z/W candidate,
                if (b == hj1_idx || b == hj2_idx) continue;
                if (bjets[b].E() == jets[j1].E() || bjets[b].E() == jets[j2].E()) continue;
                //cout << "and I am not candidated b-jets" << endl;
                // select one b-tagged jet
                // and combine it with the W candidate
                // and evaluate the Top Chi2
                tmpTop_mass = (jets[j1]+jets[j2]+bjets[b]).M();
                Chi2_Top = std::pow((trueTop_mass-tmpTop_mass)/widthTop,2);

                if (Chi2_W + Chi2_Top < Chi2_min_W + Chi2_min_Top){

                    Chi2_min_W = Chi2_W;
                    Chi2_min_Top = Chi2_Top;
                    wj1_idx = j1;
                    wj2_idx = j2;
                    tjb_idx = b;
                    Top_mass = tmpTop_mass;
                    W_mass = tmpW_mass;
		
                    tb_e = bjets[b].E();
                } // chi2 minimization
            } // top bjet loop
        } // second W jet combi
	// last try
        //if (j1 != wj1_idx && j1 != wj2_idx && j1 != tjb_idx) oj_idx = j1;
    } // first W jet combi

    // I think this is inevitable
    // Assigning the last jet
    for(unsigned int j = 0; j<jets.size(); j++){
        if (j != wj1_idx && j != wj2_idx && jets[j].E() != hb1_e && jets[j].E() != hb2_e && jets[j].E() != tb_e){
            //cout << "The last piece: " << jets[j].E() << endl;
            oj_idx = j;
            break;
        }
    }

    Chi2_min = Chi2_min_Top + Chi2_min_W + Chi2_min_H;
    Chi2_max = std::max({Chi2_min_Top, Chi2_min_W, Chi2_min_H});

    // when everything is assigned
    if (hj1_idx != -1 && hj2_idx != -1 && wj1_idx != -1 && wj2_idx != -1 && tjb_idx != -1 && oj_idx != -1){
        secondTop_mass = (bjets[hj1_idx]+bjets[hj2_idx]+jets[oj_idx]).M();
        Tprime_mass = (bjets[hj1_idx]+bjets[hj2_idx]+jets[wj1_idx]+jets[wj2_idx]+bjets[tjb_idx]).M();
        WH_mass = (bjets[hj1_idx]+bjets[hj2_idx]+jets[wj1_idx]+jets[wj2_idx]).M();
        float W1 = abs((bjets[hj1_idx]+jets[oj_idx]).M()) - 80.4;
        float W2 = abs((bjets[hj2_idx]+jets[oj_idx]).M()) - 80.4;
        if (W1 < W2) secondW_mass = W1;
        else secondW_mass = W2;

    }

    if(Tprime_mass == -1){
        cout << "Hi again, I'm the minus" << endl;
        cout << "how is everything assigned?" << endl;
        cout << "hb1 E: " << bjets[hj1_idx].E() << endl;
        cout << "hb2 E: " << bjets[hj2_idx].E() << endl;
        cout << "wj1 E: " << jets[wj1_idx].E() << endl;
        cout << "wj2 E: " << jets[wj2_idx].E() << endl;
        cout << "tbj E: " << bjets[tjb_idx].E() << endl;
        cout << "oj E: " << jets[oj_idx].E() << endl;
    }

    out.push_back(hj1_idx);           // 0
    out.push_back(hj2_idx);           // 1
    out.push_back(wj1_idx);           // 2
    out.push_back(wj2_idx);           // 3
    out.push_back(tjb_idx);           // 4
    out.push_back(oj_idx);            // 5
    out.push_back(Chi2_min);          // 6
    out.push_back(Chi2_min_H);        // 7
    out.push_back(Chi2_min_W);        // 8
    out.push_back(Chi2_min_Top);      // 9
    out.push_back(H_mass);            // 10
    out.push_back(W_mass);            // 11
    out.push_back(Top_mass);          // 12
    out.push_back(secondTop_mass);    // 13 
    out.push_back(secondW_mass);      // 14  
    out.push_back(WH_mass);           // 15 
    out.push_back(Tprime_mass);       // 16
    out.push_back(Chi2_max);          // 17

    return out;

}

floats mindR_bb(FourVectorVec &bjets){

    floats out;

    float mindR = FLT_MAX;
    float mbb = FLT_MAX;

    for(unsigned int b1 = 0; b1<bjets.size()-1; b1++){
        for(unsigned int b2 = b1+1; b2<bjets.size(); b2++){
              float dR = ROOT::Math::VectorUtil::DeltaR(bjets[b1],bjets[b2]);
              if( dR < mindR ){
                  mindR = dR;
                  mbb = (bjets[b1]+bjets[b2]).M();
              }
        }
    }

    out.emplace_back(mindR);
    out.emplace_back(mbb);

    return out;
}

//floats dR_bW(FourVectorVec &bjets, FourVectorVec &jets){
//
//    floats out;
//    float dR = -1;
//    for(unsigned int b1 = 0; b1<bjets.size()-1; b1++){
//        for(unsigned int b2 = b1+1; b2<bjets.size(); b2++){
//            dR = ROOT::Math::VectorUtil::DeltaR(bjets[b1],bjets[b2]);
//            out.emplace_back(dR);
//        }
//    }
//    return out;
//}

floats dR_bb(FourVectorVec &bjets){

    floats out;
    float dR = -1;
    for(unsigned int b1 = 0; b1<bjets.size()-1; b1++){
        for(unsigned int b2 = b1+1; b2<bjets.size(); b2++){
            dR = ROOT::Math::VectorUtil::DeltaR(bjets[b1],bjets[b2]);
            out.emplace_back(dR);
        }
    }
    return out;
}

floats m_bb(FourVectorVec &bjets){

    floats out;
    float mbb = -1;
    for(unsigned int b1 = 0; b1<bjets.size()-1; b1++){
        for(unsigned int b2 = b1+1; b2<bjets.size(); b2++){
            mbb = (bjets[b1]+bjets[b2]).M();
            out.emplace_back(mbb);
        }
    }
    return out;
}

int count5s(floats targets, float obj1, float obj2, float obj3, float obj4, float obj5){
    int out = 0;
    for( unsigned int i = 0; i < targets.size(); i++ ) if(obj1 == targets[i] || obj2 == targets[i] || obj3 == targets[i] || obj4 == targets[i] || obj5 == targets[i]) out+=1;
    return out;
}

int count3s(floats targets, float obj1, float obj2, float obj3){
    int out = 0;
    for( unsigned int i = 0; i < targets.size(); i++ ) if(obj1 == targets[i] || obj2 == targets[i] || obj3 == targets[i]) out+=1;
    return out;
}

int count2s(floats targets, float obj1, float obj2){
    int out = 0;
    for( unsigned int i = 0; i < targets.size(); i++ ) if(obj1 == targets[i] || obj2 == targets[i]) out+=1;
    return out;
}

bool isHadWHiggs(FourVectorVec &p, ints &pdgId, ints &midx){

    unsigned int np = p.size();
    bool flag = false;
    bool Whad = false;
    bool Hbb = false;

    //cout << "new event" << endl;

    // GenParticle loop 
    for(unsigned int i = 0; i < np; i++){
        ints d_idx = find_element(midx,i);
        // is any W decays into hadronically?
        if (abs(pdgId[i]) == 24){
            for(unsigned int d = 0; d < d_idx.size(); d++) if( abs(pdgId[d_idx[d]]) < 9 ) Whad = true;
        }
        // is any H decays into bb?
        else if (abs(pdgId[i]) == 25){
            for(unsigned int d = 0; d < d_idx.size(); d++) if( abs(pdgId[d_idx[d]]) == 5 ) Hbb = true;
        }
    }
    if (Whad && Hbb) flag = true;
    return flag;
};

//floats btv_shape_correction(std::unique_ptr<correction::CorrectionSet> &cset, std::string type, std::string sys, floats &pts, floats &etas, ints &hadflav, floats &btags)
//{
//    floats scalefactors;
//    auto nvecs = pts.size();
//    scalefactors.reserve(nvecs);
//    for (unsigned int i=0; i<nvecs; i++){
//
//        float sfi = cset->at(type)->evaluate({sys, int(hadflav[i]), fabs(float(etas[i])), float(pts[i]), float(btags[i])});
//        scalefactors.emplace_back(sfi);
//
//    }
//    return scalefactors;
//}

float btv_case1(std::unique_ptr<correction::CorrectionSet>& cset, std::string sys, std::string sysl, std::string wp, ints &hadflav, floats &etas, floats &pts)
{
    float btagWeight = 1.0;

    const auto nvecs = pts.size();
    for (unsigned int i = 0; i < nvecs; i++) {
        float bc_jets = 1.;
        if(std::fabs(etas[i]) < 2.5 && pts[i] > 20 && pts[i] < 1000){
            if (hadflav[i] == 4 || hadflav[i] == 5) {
                bc_jets = cset->at("deepJet_mujets")->evaluate({sys, wp, hadflav[i], std::fabs(etas[i]), pts[i]});
            } else if(hadflav[i] == 0){
                bc_jets = cset->at("deepJet_incl")->evaluate({sysl, wp, hadflav[i], std::fabs(etas[i]), pts[i]});
            } 
         }
         btagWeight *= bc_jets;
    }
    return btagWeight;
}

float btv_effMap(std::unique_ptr<correction::CorrectionSet>& eff, std::string wp, ints &hadflav, floats &etas, floats &pts)
{
    std::string flav;
    float efficiency=1;
    const auto nvecs = pts.size();
    for (unsigned int i = 0; i < nvecs; i++) {
        if(std::fabs(etas[i]) < 2.5 && pts[i] > 20 && pts[i] < 1000){
            if (hadflav[i] == 0) flav = "l";
            if (hadflav[i] == 4) flav = "c";
            if (hadflav[i] == 5) flav = "b";

            efficiency = eff->at("btag_effMap_"+wp+"_"+flav+"_Tprime")->evaluate({pts[i],std::fabs(etas[i])});
        }
    }

    return efficiency;
}

float producer_btagWeight(std::unique_ptr<correction::CorrectionSet>& cset, std::unique_ptr<correction::CorrectionSet>& eff, std::string sys, std::string sysl, ints &hadflav, floats &etas, floats &pts, floats &discs, ints &wpL, ints &wpM, ints &wpT, bool isTp, bool isTT, bool isQCD, bool isST, bool isVJets, bool isttH)
{
    std::string flav;
    std::string sample;
    float weight=1.0;
    float efficiencyL=0;
    float efficiencyM=0;
    float efficiencyT=0;

    float sfL=1.0;
    float sfM=1.0;
    float sfT=1.0;

    if (isTp == true) sample = "Tprime";
    if (isTT == true) sample = "TTToHadronic";
    if (isQCD == true) sample = "QCD";
    if (isST == true) sample = "ST";
    if (isVJets == true) sample = "VJets";
    if (isttH == true) sample = "ttH";

    //cout << "calculate btagWeight" << endl;

    const auto nvecs = pts.size();
    for (unsigned int i = 0; i < nvecs; i++) {
        if (std::fabs(etas[i]) > 2.5 || pts[i] < 20 || pts[i] > 1000) continue;

        //cout << "for a jet " << i << endl;
        //cout << "pT | eta = " << pts[i] << " | " << std::fabs(etas[i]) << endl;

        if (hadflav[i] == 0) flav = "l";
        if (hadflav[i] == 4) flav = "c";
        if (hadflav[i] == 5) flav = "b";

        //cout << "the flavour " << flav << endl;

        efficiencyL = eff->at("btag_effMap_L_"+flav+"_"+sample)->evaluate({pts[i],std::fabs(etas[i])});
        efficiencyM = eff->at("btag_effMap_M_"+flav+"_"+sample)->evaluate({pts[i],std::fabs(etas[i])});
        efficiencyT = eff->at("btag_effMap_T_"+flav+"_"+sample)->evaluate({pts[i],std::fabs(etas[i])});

        //cout << "efficiency loaded, e.g. L = " << flav << endl;

        if (hadflav[i] == 4 || hadflav[i] == 5) {
            //cout << "its heavy flavour" << endl;
            sfL = cset->at("deepJet_comb")->evaluate({sys, "L", hadflav[i], std::fabs(etas[i]), pts[i]});
            sfM = cset->at("deepJet_comb")->evaluate({sys, "M", hadflav[i], std::fabs(etas[i]), pts[i]});
            sfT = cset->at("deepJet_comb")->evaluate({sys, "T", hadflav[i], std::fabs(etas[i]), pts[i]});
            //cout << "scale factor loaded, e.g. L = " << sfL << endl;
        } else if(hadflav[i] == 0){
            sfL = cset->at("deepJet_incl")->evaluate({sysl, "L", hadflav[i], std::fabs(etas[i]), pts[i]});
            sfM = cset->at("deepJet_incl")->evaluate({sysl, "M", hadflav[i], std::fabs(etas[i]), pts[i]});
            sfT = cset->at("deepJet_incl")->evaluate({sysl, "T", hadflav[i], std::fabs(etas[i]), pts[i]});
        }

        // calculate weight
        // weight = tagged at T * tagged at M but not T * tagged at L but not M * not tagged at L
        if (wpT[i] == 1){
            weight *= sfT;
        } else if (wpM[i] == 1 && wpT[i] == 0){
             weight *= (sfM*efficiencyM - sfT*efficiencyT)/(efficiencyM - efficiencyT);
        } else if (wpL[i] == 1 && wpM[i] == 0){
             weight *= (sfL*efficiencyL - sfM*efficiencyM)/(efficiencyL - efficiencyM);
        } else if (wpL[i] == 0) {
            weight *= (1-sfL*efficiencyL)/(1-efficiencyL);
        } else cout << "something weird happening in tagging" << endl;
        
    }

    //cout << "the weight = " << weight << endl;

    return weight;
}

float producer_btagTFWeight(std::unique_ptr<correction::CorrectionSet>& ratio, float p1, float p2, float p3, float eta1, float eta2, float eta3, bool is1bM, bool is1bL, bool is2bM, bool is2bL, bool is3bM, bool is3bL, bool is2M1L, bool is3M, bool is3T)
{
    float weight=1.0;

    float ratio1L=1.0;
    float ratio2L=1.0;
    float ratio3L=1.0;

    float ratio1M=1.0;
    float ratio2M=1.0;
    float ratio3M=1.0;

    float ratio1=1.0;
    float ratio2=1.0;
    float ratio3=1.0;

    //cout << "calculate btag TF Weight" << endl;

//    if (is2M1L == true){
//
//        if (is1bL) ratio1 = ratio->at("btag_tf_L")->evaluate({p1,std::fabs(eta1)});
//        else if (is2bL) ratio2 = ratio->at("btag_tf_L")->evaluate({p2,std::fabs(eta2)});
//        else if (is3bL) ratio3 = ratio->at("btag_tf_L")->evaluate({p3,std::fabs(eta3)});
//        else cout << "It is 2M1L but no L exists: " << is1bL << ":" << is2bL << ":" << is3bL << endl;
//
//    }else if (is3M == true){
//  
//        if (is1bM) ratio1 = ratio->at("btag_tf_M")->evaluate({p1,std::fabs(eta1)});
//        else if (is2bM) ratio2 = ratio->at("btag_tf_M")->evaluate({p2,std::fabs(eta2)});
//        else if (is3bM) ratio3 = ratio->at("btag_tf_M")->evaluate({p3,std::fabs(eta3)});
//        else cout << "It is 3M but no M exists: " << is1bM << ":" << is2bM << ":" << is3bM << endl;
//
//    }else cout << "no need to apply TF" << endl;

    if (is2M1L == true){

        if (is1bL){
          ratio1L = ratio->at("btag_tf_L")->evaluate({p1,std::fabs(eta1)});
          ratio1M = ratio->at("btag_tf_M")->evaluate({p1,std::fabs(eta1)});
        }
        else if (is2bL){
          ratio2L = ratio->at("btag_tf_L")->evaluate({p2,std::fabs(eta2)});
          ratio2M = ratio->at("btag_tf_M")->evaluate({p2,std::fabs(eta2)});
        }
        else if (is3bL){
          ratio3L = ratio->at("btag_tf_L")->evaluate({p3,std::fabs(eta3)});
          ratio3M = ratio->at("btag_tf_M")->evaluate({p3,std::fabs(eta3)});
        }
        else cout << "It is 2M1L but no L exists: " << is1bL << ":" << is2bL << ":" << is3bL << endl;
 
//    }else cout << "no need to apply TF" << endl;
    }else if (is3M == true){
  
        if (is1bM) ratio1M = ratio->at("btag_tf_M")->evaluate({p1,std::fabs(eta1)});
        else if (is2bM) ratio2M = ratio->at("btag_tf_M")->evaluate({p2,std::fabs(eta2)});
        else if (is3bM) ratio3M = ratio->at("btag_tf_M")->evaluate({p3,std::fabs(eta3)});
        else cout << "It is 3M but no M exists: " << is1bM << ":" << is2bM << ":" << is3bM << endl;

    }else cout << "no need to apply TF" << endl;

    // calculate weight
//    weight = ratio1 * ratio2 * ratio3;
    weight = ratio1L * ratio2L * ratio3L * ratio1M * ratio2M * ratio3M;

    //cout << "the weight = " << weight << endl;

    return weight;
}

float pucorrection(std::unique_ptr<correction::CorrectionSet> &cset, std::string name, std::string syst, float ntruepileup)
{
    return float(cset->at(name)->evaluate({ntruepileup, syst.c_str()}));
}

floats PrintVector(floats myvector){
    for (size_t i = 0; i < myvector.size(); i++){
        std::cout<<myvector[i]<<"\n";
    }
}

floats compute_DR (FourVectorVec &muons, ints goodMuons_charge){
    floats out;
    float mu_ss_DR;
    float mu_os_DR;
    //std::cout<<"Muonsize: " << muons.size()<<std::endl;
    if(muons.size()>0)
    //Loop on all selected muons
    for(unsigned int mu1 = 0; mu1<muons.size()-1; mu1++){
        for(unsigned int mu2 = mu1+1; mu2<muons.size(); mu2++){
            //select 2 muons with same sign
            if (goodMuons_charge[mu1]!=goodMuons_charge[mu2]) continue; //check charge of muons
            mu_ss_DR = ROOT::Math::VectorUtil::DeltaR(muons[mu1],muons[mu2]);
            //select 2 muons with same sign
            if (goodMuons_charge[mu1]==goodMuons_charge[mu2]) continue;
            mu_os_DR = ROOT::Math::VectorUtil::DeltaR(muons[mu1],muons[mu2]);
        }
    }
    out.push_back(mu_ss_DR);        //0: same sign dimuon DR
    out.push_back(mu_os_DR);        //1: opposite sign dimuon dR
    return out;
}
