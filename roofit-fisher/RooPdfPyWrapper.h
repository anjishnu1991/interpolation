/***************************************************************************** 
 * author: Anjishnu Bandyopdhyay <anjishnu@physik.uni-bonn.de>
                                                                         
 * Based on Kyle Cranmer's RooPyWrapper https://github.com/cranmer/roofit-python-wrapper
 *****************************************************************************/ 

#ifndef ROOPDFPYWRAPPER
#define ROOPDFPYWRAPPER

#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsCategory.h"


#ifndef __CINT__
#include "/usr/include/python2.7/Python.h"
#endif

#ifndef PyObject_HEAD
struct _object;
typedef _object PyObject;
#endif


class RooPdfPyWrapper : public RooAbsPdf{
public:
  RooPdfPyWrapper() {} ; 
  RooPdfPyWrapper(const char *name, const char *title, RooAbsReal& _x, RooAbsReal& _alpha1, RooAbsReal& _alpha2);
  RooPdfPyWrapper(const RooPdfPyWrapper& other, const char* name=0) ;
  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
  virtual TObject* clone(const char* newname) const { return new RooPdfPyWrapper(*this,newname); }
  inline virtual ~RooPdfPyWrapper() { }
  void RegisterCallBack( PyObject* pyobject );
  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;


protected:

  virtual Double_t evaluate() const ;
  RooRealProxy x ;
  RooRealProxy alpha1 ;
  RooRealProxy alpha2 ;

private:
   

  PyObject* m_callback;
  ClassDef(RooPdfPyWrapper,1); // Your description goes here...
};
 
#endif

