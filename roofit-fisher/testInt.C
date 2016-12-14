using namespace RooFit;
void testInt(){
    	RooWorkspace* w = new RooWorkspace("ws");
	RooAbsReal* g1 = (RooAbsReal*)w->factory("Gaussian:g1(x[-5,5], mu1[-3,3], sigma1[0.5,1.5])");
	RooAbsReal* g2 =  (RooAbsReal*)w->factory("Gaussian:g2(x[-5,5], mu2[-3,3], sigma2[0.5,1.51])");
        
	RooAbsReal* prod = (RooAbsReal*) w->factory("prod:g1_g2(g1,g2)");
    	RooAbsReal* inner_prod = (RooAbsReal*) w->factory("cexpr::sqrt_g1_g2('sqrt(g1*g2)',g1,g2)");
        RooRealVar* x = w->var("x");
   	w->Print();
   	RooAbsReal* integral = inner_prod->createIntegral(*x, NormSet(*x));

    	RooRealVar* mu1 = w->var("mu1");
        mu1->setVal(-3);
    	RooRealVar* mu2 = w->var("mu2");
        mu2->setVal(3);
    	RooRealVar* sigma1 = w->var("sigma1");
	sigma1->setVal(1.1);
    	RooRealVar* sigma2 = w->var("sigma2");
        sigma2->setVal(1.1);
        RooArgList List(*mu1,*mu2,*sigma1,*sigma2);
    	cout << "first eval after changing values " << integral->getVal(List) << endl;
        RooPlot* frame = x->frame();
        inner_prod->plotOn(frame);
        frame->Draw(); 


}        
