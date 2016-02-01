/***************************************************************************** 
 * RooFisher
 * Author : Anjishnu Bandyopadhyay
 *****************************************************************************/ 

#include "Riostream.h" 

#include "RooFisher.h" 
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

 vector<vector<double>> RooFisher::_getRootpdfs()
{
     RooAbsReal* pdf;
     RooFIter Iter1(_inputPdfs.fwdIterator());
     while(pdf = ((RooAbsReal*)Iter1.next())){
       double q = sqrt(pdf->getVal());
       vector<double> xarray = linspace(-7,7,1000);
       vector<vector<double>> Rootpdf;
       Rootpdf.push_back(q(xarray));
       return Rootpdf
      }   
    }  
 Double_t RooFisher::evaluate() const 
 {

   return 1;   
     
   }
