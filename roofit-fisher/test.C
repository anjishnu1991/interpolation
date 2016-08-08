
#include "RooFisher.h"
#include "TSystem.h"
using namespace std;

void test(){

	gSystem->Load("libRooFisher.so");
	gSystem->Load("/usr/local/lib/libCGAL.so");




	vector<double> alpha1, alpha2;
        std::map<int, vector<double>> point;
        std::map<int, vector<double>> point1;
	alpha1.push_back(1);
	alpha1.push_back(1);
	alpha2.push_back(1.1);
	alpha2.push_back(1.1);
        point[0] = alpha1;
        point1[0] = alpha2;

	RooWorkspace* w = new RooWorkspace("ws");
	RooAbsReal* g1 = (RooAbsReal*)w->factory("Gaussian:g1(x[-5,5], mu1[-3,3], sigma1[0.5,1.5])");
	RooAbsReal* g2 =  (RooAbsReal*)w->factory("Gaussian:g2(x[-5,5], mu2[-3,3], sigma2[0.5,1.5])");
	w->Print();

        RooArgList List(*g1,*g2);
        FunctionMap FisherMap;
           
        FisherMap[point] = g1;
        FisherMap[point1] = g2; 
        RooFisher * Fisher = new RooFisher("testFisher", "testFisher", List, FisherMap); 



 }
