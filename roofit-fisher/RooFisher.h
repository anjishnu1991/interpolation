/***************************************************************************** 
 * author: Anjishnu Bandyopdhyay <anjishnu@physik.uni-bonn.de>
                                                                         
 *****************************************************************************/ 

#ifndef ROOFISHER
#define ROOFISHER

#include <eigen3/Eigen/Dense>
#include <map>
#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "RooWorkspace.h"
#include "RooRealProxy.h"
#include "RooListProxy.h"
#include "RooArgSet.h"
#include "RooProduct.h"
#include "RooAddition.h"
#include "RooFormulaVar.h"
#include "RooCategoryProxy.h"
#include "RooAbsCategory.h"
#include <CGAL/Cartesian_d.h>
#include <CGAL/Delaunay_d.h>
#include <CGAL/predicates_d.h>
#include <CGAL/constructions_d.h>
#include <CGAL/algorithm.h>
#include <CGAL/Timer.h>
#include <CGAL/assertions.h>

#include <iostream>
#include <iterator>
#include <vector>

#include <CGAL/Gmpz.h>
typedef double  					     FT;
typedef CGAL::Cartesian_d<FT>                                 K;
typedef CGAL::Delaunay_d<K>                                      D;
typedef D::Simplex_handle  			        Simplex_handle;
typedef D::Vertex_handle  			        Vertex_handle;
typedef D::Point_d  			        Point_d;
using namespace std;
using namespace RooFit;
using namespace Eigen;
#ifndef __CINT__
#endif



typedef std::map<int,vector<double>> keyType;
typedef std::map<keyType, RooAbsReal*> FunctionMap;
class RooFisher : public RooAbsReal{
public:
  RooFisher() {} ; 
  RooFisher(const char *name, const char *title, const RooArgList& paramSet, const RooArgList& varList, const  FunctionMap& FisherMap);
  inline virtual ~RooFisher() { }
  virtual TObject* clone(const char* newName) const{return new RooFisher();}

//virtual RooPlot *plotOn (RooPlot *frame) {return frame;}

protected:

  virtual Double_t evaluate() const ;
  vector<vector<double>> parameterPoints;
  RooListProxy _paramSet;
  RooListProxy _varList;
  RooListProxy _inputPdfs;
  RooListProxy _rootPdfs;
  RooListProxy _tangents;
  RooWorkspace* w;
  RooRealVar* x;
  RooAbsReal* q_dist;
  vector<vector<double>> InnerProducts;
  MatrixXd normedVertices;
  MatrixXd embeded;
  MatrixXd gnomonicProjection;
  int dim;
  int n;

private:
  
  ClassDef(RooFisher,1); // Your description goes here...
};
#endif 

