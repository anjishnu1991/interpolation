// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME RooFisherDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "RooFisher.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_RooFisher(void *p = 0);
   static void *newArray_RooFisher(Long_t size, void *p);
   static void delete_RooFisher(void *p);
   static void deleteArray_RooFisher(void *p);
   static void destruct_RooFisher(void *p);
   static void streamer_RooFisher(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooFisher*)
   {
      ::RooFisher *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooFisher >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RooFisher", ::RooFisher::Class_Version(), "RooFisher.h", 49,
                  typeid(::RooFisher), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooFisher::Dictionary, isa_proxy, 16,
                  sizeof(::RooFisher) );
      instance.SetNew(&new_RooFisher);
      instance.SetNewArray(&newArray_RooFisher);
      instance.SetDelete(&delete_RooFisher);
      instance.SetDeleteArray(&deleteArray_RooFisher);
      instance.SetDestructor(&destruct_RooFisher);
      instance.SetStreamerFunc(&streamer_RooFisher);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooFisher*)
   {
      return GenerateInitInstanceLocal((::RooFisher*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RooFisher*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr RooFisher::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RooFisher::Class_Name()
{
   return "RooFisher";
}

//______________________________________________________________________________
const char *RooFisher::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooFisher*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RooFisher::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooFisher*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooFisher::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooFisher*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooFisher::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooFisher*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void RooFisher::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooFisher.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      RooAbsReal::Streamer(R__b);
      {
         vector<vector<double> > &R__stl =  parameterPoints;
         R__stl.clear();
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class std::vector<double, class std::allocator<double> >));
         if (R__tcl1==0) {
            Error("parameterPoints streamer","Missing the TClass object for class std::vector<double, class std::allocator<double> >!");
            return;
         }
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            vector<double> R__t;
            R__b.StreamObject(&R__t,R__tcl1);
            R__stl.push_back(R__t);
         }
      }
      _paramSet.Streamer(R__b);
      _varList.Streamer(R__b);
      _inputPdfs.Streamer(R__b);
      _rootPdfs.Streamer(R__b);
      _tangents.Streamer(R__b);
      R__b >> w;
      R__b >> x;
      R__b >> q_dist;
      {
         vector<vector<double> > &R__stl =  InnerProducts;
         R__stl.clear();
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class std::vector<double, class std::allocator<double> >));
         if (R__tcl1==0) {
            Error("InnerProducts streamer","Missing the TClass object for class std::vector<double, class std::allocator<double> >!");
            return;
         }
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            vector<double> R__t;
            R__b.StreamObject(&R__t,R__tcl1);
            R__stl.push_back(R__t);
         }
      }
      R__b.StreamObject(&(normedVertices),typeid(normedVertices));
      R__b.StreamObject(&(embeded),typeid(embeded));
      R__b.StreamObject(&(gnomonicProjection),typeid(gnomonicProjection));
      R__b >> dim;
      R__b >> n;
      R__b.CheckByteCount(R__s, R__c, RooFisher::IsA());
   } else {
      R__c = R__b.WriteVersion(RooFisher::IsA(), kTRUE);
      RooAbsReal::Streamer(R__b);
      {
         vector<vector<double> > &R__stl =  parameterPoints;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class std::vector<double, class std::allocator<double> >));
         if (R__tcl1==0) {
            Error("parameterPoints streamer","Missing the TClass object for class std::vector<double, class std::allocator<double> >!");
            return;
         }
            vector<vector<double> >::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b.StreamObject((vector<double>*)&(*R__k),R__tcl1);
            }
         }
      }
      _paramSet.Streamer(R__b);
      _varList.Streamer(R__b);
      _inputPdfs.Streamer(R__b);
      _rootPdfs.Streamer(R__b);
      _tangents.Streamer(R__b);
      R__b << w;
      R__b << x;
      R__b << q_dist;
      {
         vector<vector<double> > &R__stl =  InnerProducts;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class std::vector<double, class std::allocator<double> >));
         if (R__tcl1==0) {
            Error("InnerProducts streamer","Missing the TClass object for class std::vector<double, class std::allocator<double> >!");
            return;
         }
            vector<vector<double> >::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b.StreamObject((vector<double>*)&(*R__k),R__tcl1);
            }
         }
      }
      R__b.StreamObject(&(normedVertices),typeid(normedVertices));
      R__b.StreamObject(&(embeded),typeid(embeded));
      R__b.StreamObject(&(gnomonicProjection),typeid(gnomonicProjection));
      R__b << dim;
      R__b << n;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooFisher(void *p) {
      return  p ? new(p) ::RooFisher : new ::RooFisher;
   }
   static void *newArray_RooFisher(Long_t nElements, void *p) {
      return p ? new(p) ::RooFisher[nElements] : new ::RooFisher[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooFisher(void *p) {
      delete ((::RooFisher*)p);
   }
   static void deleteArray_RooFisher(void *p) {
      delete [] ((::RooFisher*)p);
   }
   static void destruct_RooFisher(void *p) {
      typedef ::RooFisher current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_RooFisher(TBuffer &buf, void *obj) {
      ((::RooFisher*)obj)->::RooFisher::Streamer(buf);
   }
} // end of namespace ROOT for class ::RooFisher

namespace ROOT {
   static TClass *vectorlEvectorlEdoublegRsPgR_Dictionary();
   static void vectorlEvectorlEdoublegRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEdoublegRsPgR(void *p = 0);
   static void *newArray_vectorlEvectorlEdoublegRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEdoublegRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEdoublegRsPgR(void *p);
   static void destruct_vectorlEvectorlEdoublegRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<double> >*)
   {
      vector<vector<double> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<double> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<double> >", -2, "vector", 214,
                  typeid(vector<vector<double> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEdoublegRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<vector<double> >) );
      instance.SetNew(&new_vectorlEvectorlEdoublegRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEdoublegRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEdoublegRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEdoublegRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEdoublegRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<double> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<vector<double> >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEdoublegRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<vector<double> >*)0x0)->GetClass();
      vectorlEvectorlEdoublegRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEdoublegRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEdoublegRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<double> > : new vector<vector<double> >;
   }
   static void *newArray_vectorlEvectorlEdoublegRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<double> >[nElements] : new vector<vector<double> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEdoublegRsPgR(void *p) {
      delete ((vector<vector<double> >*)p);
   }
   static void deleteArray_vectorlEvectorlEdoublegRsPgR(void *p) {
      delete [] ((vector<vector<double> >*)p);
   }
   static void destruct_vectorlEvectorlEdoublegRsPgR(void *p) {
      typedef vector<vector<double> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<vector<double> >

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 214,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace {
  void TriggerDictionaryInitialization_RooFisherDict_Impl() {
    static const char* headers[] = {
"RooFisher.h",
0
    };
    static const char* includePaths[] = {
"/home/anjishnu/root-6.08.00/include",
"/home/anjishnu/interpolation/roofit-fisher/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "RooFisherDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(Your description goes here...)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(Your description goes here...)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$RooFisher.h")))  RooFisher;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "RooFisherDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "RooFisher.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"RooFisher", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("RooFisherDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_RooFisherDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_RooFisherDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_RooFisherDict() {
  TriggerDictionaryInitialization_RooFisherDict_Impl();
}
