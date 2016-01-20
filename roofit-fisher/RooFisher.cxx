/***************************************************************************** 
 * RooFisher
 * Author : Anjishnu Bandyopadhyay
 *****************************************************************************/ 

#include "Riostream.h" 

#include "RooFisher.h" 
#include <math.h> 

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
        _parameterPoints[i] = it->first;
        _inputPdfs.add(*it->second);
    
	}  
  
}
   
/*
   vector<double> linspace(double a, double b, int n) {
       vector<double> array;
       double step = (b-a) / (n-1);
   
       while(a <= b) {
           array.push_back(a);
           a += step;           
       }
       return array;
   }
*/
 Double_t RooFisher::evaluate() const 
 {/*
  double xmin =-7
  double xmax = 7
  int num = 1000
  
  xarray = linspace(xmin,xmax,num) 
*/
   return 1;   
     
   }
