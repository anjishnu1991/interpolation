/***************************************************************************** 
 * author: Anjishnu Bandyopdhyay <anjishnu@physik.uni-bonn.de>
                                                                         
 *****************************************************************************/ 

#ifndef ROOFISHER
#define ROOFISHER

#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooListProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsCategory.h"
#include <map>
using namespace std;

#ifndef __CINT__
#endif


typedef std::map<vector<double>, RooAbsReal*> FunctionMap;

class RooFisher : public RooAbsReal{
public:
  RooFisher() {} ; 
  RooFisher(const char *name, const char *title, RooArgList& paramSet,  FunctionMap& FisherMap);
  inline virtual ~RooFisher() { }


protected:

  virtual Double_t evaluate() const ;
  int i;
  vector<double> alpha;
  FunctionMap FisherMap;
  RooListProxy _paramSet;
  RooListProxy _inputPdfs;
private:
   

  ClassDef(RooFisher,1); // Your description goes here...
};
 
#endif

