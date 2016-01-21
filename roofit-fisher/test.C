
#include "RooFisher.h"
using namespace std;

void test(){

	gSystem->Load("libRooFisher.so");


	vector<double> alpha1, alpha2;
        std::map<int, vector<double>> point;
	alpha1.push_back(1);
	alpha1.push_back(1);
	alpha2.push_back(1.1);
	alpha2.push_back(1.1);
        point[0] = alpha1;
        point[1] = alpha2;

	RooWorkspace* w = new RooWorkspace("ws");
	RooAbsReal* g1 = (RooAbsReal*)w->factory("Gaussian:g1(x[-5,5], mu1[-3,3], sigma1[0.5,1.5])");
	RooAbsReal* g2 =  (RooAbsReal*)w->factory("Gaussian:g2(x[-5,5], mu2[-3,3], sigma2[0.5,1.5])");
	w->Print();

        RooArgList List(*g1,*g2);
        FunctionMap FisherMap;
        std::pair <RooAbsReal*, vector<double>> input1,input2;
        input1.first = g1;
        input2.first = g2;
        input1.second = point.at(0);
        input2.second = point.at(1);
        FisherMap.push_back(input1);
        FisherMap.push_back(input2);
           
        
        RooFisher * Fisher = new RooFisher("testFisher", "testFisher", List, FisherMap); 



 }
