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


typedef std::vector<std::pair<RooAbsReal*,vector<double>>> FunctionMap;

class RooFisher : public RooAbsReal{
public:
  RooFisher() {} ; 
  RooFisher(const char *name, const char *title, const RooArgList& paramSet, const  FunctionMap& FisherMap);
  inline virtual ~RooFisher() { }
  virtual TObject* clone(const char* newName) const{return new RooFisher();}

protected:

  virtual Double_t evaluate() const ;
  std::map<int,vector<double>> _parameterPoints;
  RooListProxy _inputPdfs;
  RooListProxy _paramSet;
  int _index;
private:
   

  ClassDef(RooFisher,1); // Your description goes here...
};
#endif 

