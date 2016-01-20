#include "RooFisher.h"

void test(){

	gSystem->Load("libRooFisher");
	vector<double> alpha1, alpha2;
        std::map<int, vector<double>> point;
        point[0] = alpha1;
     //   point[1] = alpha2;
	alpha1.push_back(0.1);
	alpha1.push_back(1.1);
	alpha2.push_back(-1);
	alpha2.push_back(1.5);

	RooWorkspace* w = new RooWorkspace("ws");
	//ws->factory("x[-5,5], mu[-3,3], sigma[5,1.5]");
	RooAbsReal* g1 = (RooAbsReal*)w->factory("Gaussian:g1(x[-5,5], mu1[-3,3], sigma1[5,1.5])");
	RooAbsReal* g2 =  (RooAbsReal*)w->factory("Gaussian:g2(x[-5,5], mu2[-3,3], sigma2[5,1.5])");
	w->Print();
         
        RooArgList List(*g1,*g2);
        FunctionMap FisherMap;
        FisherMap[point[0]] = g1;
      //  FisherMap[point[1]] = g2;
        RooFisher * Fisher = new RooFisher("testFisher", "testFisher", List, FisherMap); 



 }
