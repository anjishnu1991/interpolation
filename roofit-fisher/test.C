
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
/*	string pdf2Name = g2->GetName();
	string pdf1Name = g1->GetName();
	string sqrtF_pdf1_pdf2 = "cexpr::sqrt_pdf1_pdf2('sqrt(" + pdf1Name + "*" + pdf1Name + ")'," + pdf1Name + ")";
	cout << sqrtF_pdf1_pdf2 << endl;      
	inner_prod = (RooAbsReal* ) w->factory(sqrtF_pdf1_pdf2.c_str());
	x = w->var("x");
	RooAbsReal* integral = inner_prod->createIntegral(*x);
	double Inner_Product = integral->getVal();
        cout << "Integral " << Inner_Product << endl;
*/
	w->Print();

        RooArgList List(*g1,*g2);
        FunctionMap FisherMap;
           
        FisherMap[point] = g1;
        FisherMap[point1] = g2; 
        RooFisher * Fisher = new RooFisher("testFisher", "testFisher", List, FisherMap, *w); 



 }
