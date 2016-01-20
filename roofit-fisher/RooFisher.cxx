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


  RooFisher::RooFisher(const char *name, const char *title, RooArgList& paramSet, FunctionMap& FisherMap): 
  
 
  RooAbsReal (name, title),
  FisherMap(),
  _paramSet("paramSet","paramset", this), 
  _inputPdfs("inputPdfs","inputPdfs", this)
   
  {
  RooFIter Iter1 = _inputPdfs.fwdIterator() ;
  RooAbsArg* f = FisherMap[alpha]; 
  while((f = Iter1.next())) {
    _inputPdfs.add(*f) ;

     }
  } 

  
 Double_t RooFisher::evaluate() const 
 { 
   return 1;
   }
