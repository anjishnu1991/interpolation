/***************************************************************************** 
 * author: Anjishnu Bandyopdhyay <anjishnu@physik.uni-bonn.de>
                                                                         
 *****************************************************************************/ 

#ifndef ROOFISHER
#define ROOFISHER

#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooWorkspace.h"
#include "RooRealProxy.h"
#include "RooListProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsCategory.h"
#include <map>
#include "TMatrix.h"
#include "TVector.h"
#include "TDecompLU.h"
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
  RooListProxy _rootPdfs;
  RooListProxy _tangents;
  vector<vector<double>> Innerproducts;
private:
  RooWorkspace* w;
  int dim;
  RooAbsReal* pdf1;
  RooAbsReal* pdf2;
  RooAbsReal* prod;
  RooAbsReal* q_dist;
  vector<double> BaryoCords;
  vector<double> normBaryoCords;
  vector<Double_t> alpha;
  RooAbsReal* inner_prod;
  TMatrixD _getNormedSimplex();
  vector<vector<double>> alphas;
  vector<Double_t> alphaSimplex; //Triangulation
  ClassDef(RooFisher,1); // Your description goes here...
};
#endif 

