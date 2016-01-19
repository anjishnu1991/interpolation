/***************************************************************************** 
 * RooPdfPyWrapper
 * author: Kyle Cranmer <kyle.cranmer@nyu.edu>
 * author: Lukas Heinrich
 *                                                                          * 
 * This is an example RooAbsReal that makes a call back to python code
 *****************************************************************************/ 

#include "Riostream.h" 

#include "RooPdfPyWrapper.h" 
#include <math.h> 
#include "Python.h"

#ifndef __CINT__
#endif

using namespace std;

ClassImp(RooPdfPyWrapper) 


  RooPdfPyWrapper::RooPdfPyWrapper(const char *name, const char *title, RooAbsReal& _x, RooAbsReal& _alpha1, RooAbsReal& _alpha2) :
  RooAbsPdf(name,title),
  x("x","x",this,_x),
  alpha1("alpha1","alpha1",this,_alpha1),
  alpha2("alpha2","alpha2",this,_alpha2)

  { 
     m_callback=NULL;
  } 

 RooPdfPyWrapper::RooPdfPyWrapper(const RooPdfPyWrapper& other, const char* name) :  
  RooAbsPdf(other,name),
  x("x",this,other.x),
  alpha1("alpha1",this,other.alpha1),
  alpha2("alpha2",this,other.alpha2),
  m_callback(other.m_callback) 
 { 
 } 

 Double_t RooPdfPyWrapper::evaluate() const 
 { 
    // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
    #ifndef __CINT__

   if(    m_callback==NULL) {
     cout << "no call back set" << endl;
     return 0;
   }

   // convert member variable features to PyObject
   PyObject* arg = PyFloat_FromDouble(x.arg().getVal());

   // callback with argument
   PyObject* result = PyObject_CallFunctionObjArgs( m_callback, arg , NULL  );

   // decrement reference counter to arg
   Py_XDECREF( arg );

   // convert result to double
   double ret;
   PyArg_Parse((result),"d", &ret);

   // other conversion approachs
   //   cout << "result as long " << PyInt_AsLong(result) << endl;
   //   cout << "result as double " << PyFloat_AsDouble(result) << endl; 


   Py_XDECREF( result );
    #endif
    return ret ; 
  }

	 
	 Int_t  RooPdfPyWrapper::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const  
	 { 
	    return 1 ; 
	  } 



	  Double_t  RooPdfPyWrapper::analyticalIntegral(Int_t code, const char* rangeName) const  
	  { 
	    assert(code==1) ; 
	    return 1;
	  }
	  
	  


void RooPdfPyWrapper::RegisterCallBack( PyObject* pyobject )
{
	// see http://root.cern.ch/phpBB3/viewtopic.php?t=2606
	Py_INCREF( pyobject );
	m_callback = pyobject;
}


