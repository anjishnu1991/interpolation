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


 vector<vector<double>> RooFisher::InnerProducts(){
 RooFIter Iter_pdf1(_inputPdfs.fwdIterator());
 RooFIter Iter_pdf2(_inputPdfs.fwdIterator());
 RooAbsReal* pdf1;
 RooAbsReal* pdf2;
 RooAbsReal* prod;
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
    InnerProducts.push_back(list_inner_prod);
 } 

    return InnerProducts; 
}  
 

 MatrixXd RooFisher::normedSimplex(){
    dim =  InnerProducts.size();
    n = dim -1;
    embeded(0,n) = -1;
    for(int k=1; k<dim;++k){
       vector<double> Z; 
       MatrixXd y(k,k);
       VectorXd z;
       for (int j=0; j<k; ++j){
           Z[j] = (1 - (pow(InnerProducts[j][k],2))*0.5);
       z = VectorXd::Map(Z.data(),Z.size()); 
       y = embeded.topRightCorner(k,k);
	}
        VectorXd x = y.colPivHouseholderQr().solve(z);
        double x_0k = -sqrt(1-x.squaredNorm());
        embeded(k,dim-k) = x_0k;
    }
        for(int i=0; i<dim; ++i){
           gnomonicProjection(i) = -1*embeded(i)/embeded(i,n);            
        }        
       MatrixXd normedVertices(dim,n);
       normedVertices =  gnomonicProjection.block(0,0,dim,n);
       for(int col=0; col<n; ++col){
          normedVertices.col(col) /=  (normedVertices.col(col)).squaredNorm();           
       } 
       MatrixXd normedSimplex = normedVertices; // Triangulation needed 
    return normedSimplex;
 }    

 //      for(int m=0; m<dim; ++m){
 //        RooAbsReal* t = (RooAbsReal*) w->factory("cexpr::t(`(_rootPdfs.at(i) - Innerproducts[0][m]*_rootPdfs.at(m))',_rootPdfs.at(m),_rootPdfs.at(0)");
   //     RooAbsReal* Norm = (RooAbsReal*) w->factory("prod:t^2('t*t')");
    //  double norm_integral = norm->creatIntegral(*x);
     //   double Norm_integral = Norm->getVal();
     //   RooAbsReal* u = (RooAbsReal*) w->factory("cexpr::u('t/sqrt(norm_integral)')");
      //  _tangents.add(*u); 
// }




 Double_t RooFisher::evaluate() const 
 {/* RooAbsReal* param; 
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

unnorm_tan = lambda x: u1(x)*normedBaryCoords[0]+u2(x)*normedBaryCoords[1]
norm_tan = inner_product(unnorm_tan,unnorm_tan)
tangent = lambda x: unnorm_tan(x) / np.sqrt(norm_tan)*/
   return 1;   
     
}   
