
#include "RooFisher.h"
#include "TSystem.h"
using namespace std;

void test(){

	gSystem->Load("libRooFisher.so");


       

	vector<double> alpha1, alpha2,alpha3;
        std::map<int, vector<double>> point,point1,point2;
	alpha1.push_back(1);
	alpha1.push_back(1);
	alpha2.push_back(2);
	alpha2.push_back(2);
	alpha3.push_back(3);
	alpha3.push_back(3);
        point[0] = alpha1;
        point1[0] = alpha2;
        point2[0] = alpha3;

	RooWorkspace* w = new RooWorkspace("ws");
        for(int i=1;i<4; ++i){
	 w->factory(Form("Gaussian::g%d(x[-10,10],mu%d[%d,-5,5],sigma%d[%d, 0, 3])", i, i,i,i,i));;
        }
	 x = w->var("x");
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
        RooArgList List(*mu,*sigma);  
	RooPlot* frame = x->frame();
        pdf1= w->pdf("g1");
	pdf1->plotOn(frame);
	FisherMap[point] = pdf1;
        pdf2 = w->pdf("g2");
	pdf2->plotOn(frame);
	FisherMap[point1] = pdf2;
        pdf3 = w->pdf("g3");
	pdf3->plotOn(frame);
	FisherMap[point2] = pdf3;
	frame->Draw();
        
	RooFisher * Fisher = new RooFisher("testFisher", "testFisher", List, FisherMap, *w); 
        cout << "a" << endl; 
        cout << "b" << endl; 
	w->Print();
        cout << "c" << endl; 
	Fisher->Print("v");

	for (int j=0; j<3; ++j){
		mu->setVal(.8+j);
		mu->Print();
		sigma->setVal(.8+j);
		sigma->Print();
//		Fisher->plotOn(frame, RooFit::LineColor(kRed));
}





 }
