
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
	alpha3.push_back(1.5);
	alpha3.push_back(1.5);
        point[0] = alpha1;
        point1[1] = alpha2;
        point2[2] = alpha3;

	RooWorkspace* w = new RooWorkspace("ws");
	 w->factory("Gaussian::g1(y[-5,5],mu1[0,-5,5],sigma1[1, 0, 3])");
	 w->factory("Gaussian::g2(y[-5,5],mu2[1,-5,5],sigma1[1, 0, 3])");
	 w->factory("Gaussian::g3(y[-5,5],mu3[1.5,-5,5],sigma3[1.5, 0, 3])");
	 RooRealVar* y = (RooRealVar*)w->var("y");
         RooRealVar* mu =(RooRealVar*)w->factory("mu[-5,5]");
	 mu = w->var("mu");
         RooRealVar*  sigma =(RooRealVar*)w->factory("sigma[0.1,5]");
         sigma = w->var("sigma");
       
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
	w->Print();
	Fisher->Print("v");
        
       // RooPlot* frame1 =  RooPlot(-10,10);
        

		//Fisher->plotOn(frame, RooFit::LineColor(kRed));

		mu->setVal(0.5);
		mu->Print();
		sigma->setVal(0.5);
		sigma->Print();
                cout << "The value is " << Fisher->getVal() << endl;
//		Fisher->plotOn(frame, RooFit::LineColor(kRed));
//		Fisher->plotOn(frame);
//		frame->Draw();





 }
