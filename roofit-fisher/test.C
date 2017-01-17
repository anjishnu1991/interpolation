
#include "RooFisher.h"
#include "TSystem.h"
using namespace std;

void test(){

	gSystem->Load("libRooFisher.so");


       

	vector<double> alpha1, alpha2,alpha3;
        keyType point,point1,point2;
	alpha1.push_back(0);
	alpha1.push_back(1);
	alpha2.push_back(1);
	alpha2.push_back(1);
	alpha3.push_back(0.5);
	alpha3.push_back(0.5);
        point[0] = alpha1;
        point1[1] = alpha2;
        point2[2] = alpha3;

	RooWorkspace* w = new RooWorkspace("ws");
	 w->factory("Gaussian::g1(y[-5,5],mu1[0,-5,5],sigma1[1, 0, 3])");
	 w->factory("Gaussian::g2(y[-5,5],mu2[1,-5,5],sigma1[1, 0, 3])");
	 w->factory("Gaussian::g3(y[-5,5],mu3[0.5,-5,5],sigma3[0.5, 0, 3])");
	 RooRealVar* y = (RooRealVar*)w->var("y");
         RooRealVar* mu =(RooRealVar*)w->factory("mu[-5,5]");
	 mu = w->var("mu");
         RooRealVar*  sigma =(RooRealVar*)w->factory("sigma[0.1,5]");
         sigma = w->var("sigma");
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

        FunctionMap FisherMap;
        RooArgList params(*mu,*sigma);  
        RooArgList vars(*y);  
	RooPlot* frame = y->frame();
        pdf1= w->pdf("g1");
	pdf1->plotOn(frame);
	FisherMap[point] = pdf1;
        pdf2 = w->pdf("g2");
	pdf2->plotOn(frame);
	FisherMap[point1] = pdf2;
        pdf3 = w->pdf("g3");
	pdf3->plotOn(frame);
	FisherMap[point2] = pdf3;
        
	RooFisher * Fisher = new RooFisher("testFisher", "testFisher", params, vars, FisherMap); 
        cout << "a" << endl; 
        cout << "b" << endl; 
	w->Print();
        cout << "c" << endl; 
	Fisher->Print("v");
        
        cout << "d" << endl; 
//Fisher->plotSanityChecks(frame);
       // RooPlot* frame1 =  RooPlot(-10,10);
        
        cout << "e" << endl; 

		//Fisher->plotOn(frame, RooFit::LineColor(kRed));

		mu->setVal(0.5);
		mu->Print();
		sigma->setVal(0.5);
		sigma->Print();
		y->setVal(0.5);
		y->Print();
                cout << "The value is " << Fisher->getVal() << endl;
//		Fisher->plotOn(frame, RooFit::LineColor(kRed));
//		Fisher->plotOn(frame);
		frame->Draw();





 }
