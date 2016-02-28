void testInt(){
    	RooWorkspace* w = new RooWorkspace("ws");
	RooAbsReal* g1 = (RooAbsReal*)w->factory("Gaussian:g1(x[-5,5], mu1[-3,3], sigma1[0.5,1.5])");
	RooAbsReal* g2 =  (RooAbsReal*)w->factory("Gaussian:g2(x[-5,5], mu2[-3,3], sigma2[0.5,1.5])");
        
	RooAbsReal* prod = (RooAbsReal*) w->factory("prod:g1_g2(g1,g2)");
    	RooAbsReal* inner_prod = (RooAbsReal*) w->factory("cexpr::sqrt_g1_g2('sqrt(g1*g2)',g1,g2)");
        RooRealVar* x = w->var("x");
   	w->Print();
   	RooAbsReal* integral = inner_prod->createIntegral(*x);

	cout << "first eval " << integral->getVal() << endl;
    	cout << "second eval " << integral->getVal() << endl;
    	w->var("mu1")->setVal(0.2);
    	cout << "first eval after changing mu1 " << integral->getVal() << endl;






}        
