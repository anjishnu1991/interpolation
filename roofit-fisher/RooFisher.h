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
#include <Dense>
#include <map>
using namespace std;
using namespace Eigen;
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
  RooWorkspace* w;
  vector<vector<double>> InnerProducts;
  MatrixXd normedSimplex;
  MatrixXd embeded;
  MatrixXd gnomonicProjection;
  int dim;
  int n;
private:
  RooAbsReal* q_dist;
  vector<double> BaryoCords;
  vector<double> normBaryoCords;
  vector<Double_t> alpha;
  RooAbsReal* inner_prod;
  vector<vector<double>> alphas;
  vector<double> alphaSimplex; //Triangulation
  ClassDef(RooFisher,1); // Your description goes here...
};
#endif 

