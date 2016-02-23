/***************************************************************************** 
 * RooFisher
 * Author : Anjishnu Bandyopadhyay
 *****************************************************************************/ 

#include "Riostream.h"   
#include "RooFisher.h" 
#include "RooArgSet.h" 
#include <math.h> 
#include "RooLinkedListIter.h"
#ifndef __CINT__
#endif

ClassImp(RooFisher) 


  RooFisher::RooFisher(const char *name, const char *title, const RooArgList& paramSet, const  FunctionMap& FisherMap): 
  
      
   RooAbsReal (name, title),
  _paramSet("paramSet","paramset", this), 
  _inputPdfs("inputPdfs","inputPdfs", this)
   
   {
	for(FunctionMap::const_iterator it = FisherMap.begin(); it != FisherMap.end(); it++) {
// 	std::cout <<   iterator->second   << std::endl ;
        _parameterPoints = it->first;
        _inputPdfs.add(*it->second);
       
	}  
  
}


 TMatrixD RooFisher::_getNormedSimplex(){
 RooFIter Iter_pdf1(_inputPdfs.fwdIterator());
 RooFIter Iter_pdf2(_inputPdfs.fwdIterator());
 vector<double> list_inner_prod;
 RooAbsReal* integral;
 RooAbsReal* q;
 while((pdf1=(RooAbsReal*)Iter_pdf1.next())){
 	q = (RooAbsReal* ) w->factory("cexpr::sqrt_f('sqrt(pdf1)',pdf1");
        _rootPdfs.add(*q);    
    while((pdf2=(RooAbsReal*)Iter_pdf2.next())){
    prod = (RooAbsReal* ) w->factory("prod:pdf1_pdf2(pdf1,pdf2)");
    inner_prod = (RooAbsReal* ) w->factory("cexpr::sqrt_pdf1_pdf2('sqrt(pdf1*pdf2)',pdf1,pdf2)");
  // The test code works but the createIntegral method doesn't work here. Asks for RooArgSet  
  //  x = w->var("x");
  //  integral = inner_prod->createIntegral(RooArgSet(*x));
  //  integral = inner_prod->createIntegral(*x);
    double Inner_Product = integral->getVal();
    list_inner_prod.push_back(Inner_Product);
   }
    Innerproducts.push_back(list_inner_prod);
 
}   
    dim =  Innerproducts.size();
    int n = dim -1;
    TMatrixD embeded(dim,dim);
    TMatrixD gnomonicProjection(dim,dim);
    embeded(0,n) = -1;
    for(int k=1; k<dim;++k){
       TMatrixD* y = new TMatrixD(k,k);
       TVectorD* z = new TVectorD(k);
        
       for (int j=0; j<k; ++j){
           z[j] = 1 - (pow(Innerproducts[j][k],2))*0.5;
           for (int m=0; m<k; ++j){
               y[j][m] = embeded[j][dim-k+j];
        } 
    }
        TDecompLU lu(*y);
        Bool_t ok;
        TVectorD x;
        x = lu.Solve(*z,ok);
        double x_0k = -sqrt(1-x.Norm2Sqr());
        embeded[k][dim-k] = x_0k;
        for(int i=0; i<dim; ++i){
           embeded[k][i]=x[0];
           gnomonicProjection[i] =embeded[i];
           TMatrixDRow (gnomonicProjection,i) = -1/embeded[i][n];
           alphas.push_back(_parameterPoints[i]); 
        } 
}
       
       TMatrixD normedVertices(dim,n);
       for(int col=0; col<n; ++col){
          TMatrixDColumn(normedVertices,col) = TMatrixDColumn(gnomonicProjection,col);
       } 
       TMatrixD normedSimplex = normedVertices; // Triangulation needed  
     
       for(int m=0; m<dim; ++m){
         RooAbsReal* t = (RooAbsReal*) w->factory("cexpr::t(`(_rootPdfs.at(i) - Innerproducts[0][m]*_rootPdfs.at(m))',_rootPdfs.at(m),_rootPdfs.at(0)");
        RooAbsReal* Norm = (RooAbsReal*) w->factory("prod:t^2('t*t')");
    //  double norm_integral = norm->creatIntegral(*x);
        double Norm_integral = Norm->getVal();
        RooAbsReal* u = (RooAbsReal*) w->factory("cexpr::u('t/sqrt(norm_integral)')");
        _tangents.add(*u); 
 }
   return normedSimplex;
}



 Double_t RooFisher::evaluate() const 
 {   RooAbsReal* param; 
     RooFIter paramIter(_paramSet.fwdIterator()) ;
     RooFIter tangentIter(_tangents.fwdIterator()) ;
     while((param=(RooAbsReal*)paramIter.next())) {
    Double_t alpha_i = param->getVal(); 
   //This line giving const error which I can't solve
   //  alpha.push_back(alpha_i); 
     }    
 //   BaryoCords = inner_product(begin(alphaSimplex), end(alphaSimplex), begin(alpha), 0.0);     //affine transform needed
    double t = 1; //arctan(inner_product(begin(BaryoCords), end(BaryoCords), begin(BaryoCords), 0.0)); //Replacement for gnomonicTarget     
     
//should I use workspace for defining unnorm_tan, norm_tan etc??

/*unnorm_tan = lambda x: u1(x)*normedBaryCoords[0]+u2(x)*normedBaryCoords[1]
norm_tan = inner_product(unnorm_tan,unnorm_tan)
tangent = lambda x: unnorm_tan(x) / np.sqrt(norm_tan)*/
   return t;   
     
}   
