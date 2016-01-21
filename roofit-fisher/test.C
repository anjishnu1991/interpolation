
#include "RooFisher.h"
using namespace std;

void test(){

	gSystem->Load("libRooFisher.so");
	vector<double> alpha1, alpha2;
        std::map<int, vector<double>> point;
        point[0] = alpha1;
        point[1] = alpha2;
	alpha1.push_back(1);
	alpha1.push_back(1);
	alpha2.push_back(1.1);
	alpha2.push_back(1.1);
	RooWorkspace* w = new RooWorkspace("ws");
	RooAbsReal* g1 = (RooAbsReal*)w->factory("Gaussian:g1(x[-5,5], mu1[-3,3], sigma1[0.5,1.5])");
	RooAbsReal* g2 =  (RooAbsReal*)w->factory("Gaussian:g2(x[-5,5], mu2[-3,3], sigma2[0.5,1.5])");
	w->Print();
        RooArgList List(*g1,*g2);
        FunctionMap FisherMap;
        FisherMap[point.at(0)]= g1;
        FisherMap[point.at(1)]= g2;
        RooFisher * Fisher = new RooFisher("testFisher", "testFisher", List, FisherMap); 



 }
