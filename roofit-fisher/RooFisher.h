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
#include "TMatrix.h"
using namespace std;

#ifndef __CINT__
#endif


typedef std::map<int,vector<double>> keyType;
typedef std::map<keyType, RooAbsReal*> FunctionMap;
class RooFisher : public RooAbsReal{
public:
  RooFisher() {} ; 
  RooFisher(const char *name, const char *title, const RooArgList& paramSet, const  FunctionMap& FisherMap);
  inline virtual ~RooFisher() { }
  virtual TObject* clone(const char* newName) const{return new RooFisher();}

protected:

  virtual Double_t evaluate() const ;
  keyType  _parameterPoints;
  RooListProxy _paramSet;
  RooListProxy _inputPdfs;
private:
vector< vector<double>> _getRootpdfs();
 vector<double> linspace(double a, double b, double n);
  ClassDef(RooFisher,1); // Your description goes here...
};
#endif 

