/***************************************************************************** 
 * RooFisher
 * Author : Anjishnu Bandyopadhyay
 *****************************************************************************/ 

#include "Riostream.h"   
#include "RooFisher.h" 
#include "RooArgSet.h" 
#include <math.h> 
#include "RooLinkedListIter.h"
#include "RooRealIntegral.h"
#ifndef __CINT__
#endif

ClassImp(RooFisher) 


  RooFisher::RooFisher(const char *name, const char *title, const RooArgList& paramSet, const  FunctionMap& FisherMap): 
  
      
   RooAbsReal (name, title),
  _paramSet("paramSet","paramset", this), 
  _inputPdfs("inputPdfs","inputPdfs", this)
   
   {
	for(FunctionMap::const_iterator it = FisherMap.begin(); it != FisherMap.end(); it++) {
// 	std::cout <<   iterator->second   << std::endl ;
        _parameterPoints = it->first;
        _inputPdfs.add(*it->second);
       
	}  
  
}


 {
 RooFIter Iter_pdf1(_inputPdfs.fwdIterator());
 RooFIter Iter_pdf2(_inputPdfs.fwdIterator());
 RooAbsReal* pdf1;
 RooAbsReal* pdf2;
 RooAbsReal* inner_prod;
 vector<double> list_inner_prod;
 RooAbsReal* q;
 
while((pdf1=(RooAbsReal*)Iter_pdf1.next())){
 	q = (RooAbsReal* ) w->factory("cexpr::sqrt_f('sqrt(pdf1)',pdf1");
        _rootPdfs.add(*q);    
    while((pdf2=(RooAbsReal*)Iter_pdf2.next())){
    inner_prod = (RooAbsReal* ) w->factory("cexpr::sqrt_pdf1_pdf2('sqrt(pdf1*pdf2)',pdf1,pdf2)");
   RooRealVar* x = w->var("x");
   RooAbsReal* integral = inner_prod->createIntegral(*x);
    double Inner_Product = integral->getVal();
    list_inner_prod.push_back(Inner_Product);
   }
    InnerProducts.push_back(list_inner_prod);
 } 

    
}  
 
{
    dim =  inner_prods.size();
    n = dim -1;
    embeded(0,n) = -1;
    for(int k=1; k<dim;++k){
       vector<double> Z; 
       MatrixXd y(k,k);
       VectorXd z;
       for (int j=0; j<k; ++j){
           Z[j] = (1 - (pow(inner_prods[j][k],2))*0.5);
       z = VectorXd::Map(Z.data(),Z.size()); 
       y = embeded.topRightCorner(k,k);
	}
        VectorXd x = y.colPivHouseholderQr().solve(z);
        double x_0k = -sqrt(1-x.squaredNorm());
        embeded(k,dim-k) = x_0k;
    }
        for(int i=0; i<dim; ++i){
           gnomonicProjection(i) = -1*embeded(i)/embeded(i,n);            
        }        
       normedVertices =  gnomonicProjection.block(0,0,dim,n);
       for(int col=0; col<n; ++col){
          normedVertices.col(col) /=  (normedVertices.col(col)).squaredNorm();           
       } 
    
 }    


{


//Delaunay triangulation of alphas
       for( _parameterPoints::const_iterator it =  _parameterPoints.begin(); it !=  _parameterPoints.end(); it++) {
          Point_d alpha_i(dim, (it->second).begin(), (it->second).end()); 
          vector<Point_d> alphas;
          alphas.push_back(alpha_i); 
}
       for(alphas::iterator Itr = alphas.begin(); Itr!= alphas.end(); ++Itr){
          alpha_Dt.insert(*Itr);
}

//Gnomonic delaunay triangulation
// Need iterator but MatrixXd doesn't have it so using methods like described here http://stackoverflow.com/questions/26094379/typecasting-eigenvectorxd-to-stdvector and then using the vector

      for(int i=0; i<gnomonicProjection.rows(); ++i){

          VectorXd v1 = gnomonicProjection.row(i);
          vector<double> v2;
          v2.resize(v1.size());
	  VectorXd::Map(&v2[0], v1.size()) = v1;
          Point_d gnomonicCoord(dim, v2.begin(), v22.end());
          vector<Point_d> gnomonicCoords;
          gnomonicCoords.push_back(gnomonicCoord); 


      }

       for(gnomonicCoords::iterator Itr1 = gnomonicCoords.begin(); Itr1!= gnomonicCoords.end(); ++Itr1){
         gnomonic_Dt.insert(*Itr1);
}

   //normedVertices delaunay triangulation 
      for(int i=0; i<normedVertices.rows(); ++i){

          VectorXd V1 = normedVertices.row(i);
          vector<double> V2;
          V2.resize(V1.size());
	  VectorXd::Map(&V2[0], V1.size()) = V1;
          Point_d normedCoord(dim, V2.begin(), V2.end());
          vector<Point_d> normedCoords;
          normedCoords.push_back(normedCoord); 


      }

       for(normedCoords::iterator Itr2 = normedCoords.begin(); Itr2!= normedCoords.end(); ++Itr2){
         normed_Dt.insert(*Itr2);
}


}



 Double_t RooFisher::evaluate() const 
 {
       vector<double> target_alpha;
//Get target alpha point
     RooAbsReal* param; 
     RooFIter paramIter(_paramSet.fwdIterator()) ;
     RooFIter tangentIter(_tangents.fwdIterator()) ;
     while((param=(RooAbsReal*)paramIter.next())) {
     double target_alpha_i = param->getVal(); 
     target_alpha.push_back(alpha_i); 
     }    


          Point_d target_alpha_point(dim, target_alpha.begin(), target_alpha.end()); 


//Locate target alpha in appropriate simplex of triangulation 
    Vertex_handle v = alpha_Dt.nearest_neighbor(target_alpha_point);
    Simplex_handle s = alpha_Dt.simplex(v);    
  
     vector<Point_d> Simplex_vertices;
     for(int j=0; j<=n; ++j){
          Vertex_handle vertex = alpha_Dt.vertex_of_simplex(s,j);
       	  Simplex_vertices.push_back(alpha_Dt.associated_point(vertex));
     }

//Barycentric coordinates of target alpha in alpha simplex
    K::Barycentric_coordinates_d BaryCoords;
    BaryCoords(Simplex_vertices.begin(), Simplex_vertices.end(),point,std::inserter(coords, coords.begin()));
 // Locate and barycentric coords of gnomonicTarget
    Point_d alphaBaryoCoord(dim, coords.begin(), coords.end());
    Vertex_handle vert = gnomonic_Dt.nearest_neighbor();
    Simplex_handle simpl = gnomonic_Dt.simplex(vert);    
  
     vector<Point_d> Simplex_vertices1;
     for(int k=0; k<=n; ++k){
          Vertex_handle vertex1 = gnomonic_Dt.vertex_of_simplex(simpl,k);
       	  Simplex_vertices1.push_back(gnomonic_Dt.associated_point(vertex1));
     }


    K::Barycentric_coordinates_d gnomonicCoords;
    gnomonicCoords(Simplex_vertices1.begin(), Simplex_vertices1.end(),point,std::inserter(gnomonicTarget, gnomonicTarget.begin()));
//Getting normedBaryoCoords
    Point_d gnomonicTargetCoord(dim, gnomonicTarget.begin(), gnomonicTarget,.end());
    Vertex_handle vertx = normed_Dt.nearest_neighbor();
    Simplex_handle simplx = normed_Dt.simplex(vertx);    
  
     vector<Point_d> Simplex_vertices2;
     for(int m=0; m<=n; ++m){
          Vertex_handle vertex2 = normed_Dt.vertex_of_simplex(simplx,m);
       	  Simplex_vertices2.push_back(normed_Dt.associated_point(vertex2));
     }


    K::Barycentric_coordinates_d normedCoords;
    normedCoords(Simplex_vertices2.begin(), Simplex_vertices2.end(),point,std::inserter(normedBaryoCoords,  normedBaryoCoords.begin()));

      double t_val = atan(std::inner_product(gnomonicTarget.begin(), gnomonicTarget.end(), gnomonicTarget.begin()));

        RooAbsReal* unNormtan;

       for(int m=0; m<dim; ++m){
         RooAbsReal* t = (RooAbsReal*) w->factory("cexpr::t(`(_rootPdfs.at(i) - InnerProducts[0][m]*_rootPdfs.at(m))',_rootPdfs.at(m),_rootPdfs.at(0)");
        RooAbsReal* Norm = (RooAbsReal*) w->factory("prod:t^2('t*t')");
        double norm_integral = ((RooAbsReal*)Norm->creatIntegral(*x))->getVal();
        RooAbsReal* u = (RooAbsReal*) w->factory("cexpr::u('t/sqrt(norm_integral)')");
        
        RooAbsReal* unNormtan_i = (RooAbsReal*) w->factory("sum::uNti(normBaryoCoords[i]*u,unNormtan)")';
        unNormtan = (RooAbsReal*) w->factory("sum::unt(normedBaryoCoords[i]*u,unNormtan)");
 





}
         unnorm_tan_prod =  (RooAbsReal* ) w->factory("prod::unt*unt(unNormtan*unNormtan)");
         RooAbsReal* normtan = unnorm_tan_prod->createIntegral(*x);
         RooAbsReal* tangent = (RooAbsReal*) w->factory("cexpr::tangent(`(unNormtan/sqrt(normtan))',unNormtan,normtan");
          
         RooAbsReal* q_interpolant =  (RooAbsReal*) w->factory("cexpr::tangent(`(cos(t_val)*,_rootPdfs.at(0) + sin(t_val)*tangent)',tangent,_rootPdfs.at(0)");
         RooAbsReal* interpolant =  (RooAbsReal* ) w->factory("prod::interpolant(q_interpolant*q_interpolant)");
         
        Double_t interp_val = interpolant->getVal();

   	return interp_val;   
     
}   
