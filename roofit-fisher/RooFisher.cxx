/***************************************************************************** 
 * RooFisher
 * Author : Anjishnu Bandyopadhyay
 *****************************************************************************/ 

#include "RooFisher.h" 
#include "RooArgSet.h" 
#include <math.h> 
#include "RooLinkedListIter.h"
#include "RooRealIntegral.h"
#ifndef __CINT__
#endif

ClassImp(RooFisher) 


	RooFisher::RooFisher(const char *name, const char *title, const RooArgList& paramSet, const RooArgList& varList, const  FunctionMap& FisherMap, const RooWorkspace& win): 


		RooAbsReal (name, title),
		_paramSet("paramSet","paramset", this), 
		_varList("varList","varList", this), 
		_inputPdfs("inputPdfs","inputPdfs", this)

{ 
w = (RooWorkspace*)win.Clone();
	for(FunctionMap::const_iterator it = FisherMap.begin(); it != FisherMap.end(); it++) {
		keyType _parameterPoints = it->first;
		_inputPdfs.add(*it->second);
        	for(keyType::const_iterator it1=_parameterPoints.begin(); it1 != _parameterPoints.end(); it1++){
			vector<double> parameterpoint = it1->second;
			parameterPoints.push_back(parameterpoint); 
	 }
	}
        RooFIter Iter_param(paramSet.fwdIterator());
        RooAbsArg* param;
        while(param=(RooAbsArg*)Iter_param.next()){
              _paramSet.add(*param);
	      
	}
        RooFIter Iter_var(varList.fwdIterator());
        RooAbsArg* var;
        while(var=(RooAbsArg*)Iter_var.next()){
              _varList.add(*var);
	      
	}
	RooFIter Iter_pdf1(_inputPdfs.fwdIterator());
	RooAbsReal* pdf1;
	RooAbsReal* pdf2;
	RooAbsReal* inner_prod;
	vector<double> list_inner_prod;
	RooAbsReal* q;

	while((pdf1=(RooAbsReal*)Iter_pdf1.next())){
		string pdf1Name = pdf1->GetName();
		string sqrtF = "cexpr::sqrt_" + pdf1Name +"('sqrt(" + pdf1Name + ")'," + pdf1Name + ")";      
		q = (RooAbsReal* ) w->factory(sqrtF.c_str());
		_rootPdfs.add(*q);
		RooFIter Iter_pdf2(_inputPdfs.fwdIterator());
		while((pdf2=(RooAbsReal*)Iter_pdf2.next())){
			string pdf2Name = pdf2->GetName();
                        string sqrtF_pdf1_pdf2;
			if(pdf2Name==pdf1Name){
				sqrtF_pdf1_pdf2 = "cexpr::sqrt_" + pdf1Name + "_" + pdf2Name + "('sqrt(" + pdf1Name + "*" + pdf2Name + ")'," + pdf1Name + ")";
			}
			else{	
				 sqrtF_pdf1_pdf2 = "cexpr::sqrt_"+ pdf1Name + "_" + pdf2Name + "('sqrt(" + pdf1Name + "*" + pdf2Name + ")'," + pdf1Name + "," + pdf2Name + ")";
			}				
			inner_prod = (RooAbsReal* ) w->factory(sqrtF_pdf1_pdf2.c_str());
		        string var_x = _varList.at(0)->GetName();
                        x = (RooRealVar*)(_varList.at(0));
                        x = w->var(var_x.c_str());
                        
			RooAbsReal* integral = inner_prod->createIntegral(*x, NormSet(*x));
			double Inner_Product = integral->getVal();
			list_inner_prod.push_back(Inner_Product);
		}
		InnerProducts.push_back(list_inner_prod);
} 

	/*TODO RooAbsCacheManger */  


        n = _paramSet.getSize();
        dim = n+1;
	embeded = MatrixXd::Zero(dim,dim);
        MatrixXd gnomonicProjection_temp = MatrixXd::Zero(dim,dim);
        normedVertices = MatrixXd::Zero(dim,dim-1);
        gnomonicProjection = MatrixXd::Zero(dim,dim-1);
       	embeded(0,n) = -1;
	for(int k=1; k<dim;++k){
		MatrixXd y(k,k);
		VectorXd z(k);
		for (int j=0; j<k; j++){
                	double IP_jk = InnerProducts[j][k];
			z[j] = (1 - (IP_jk*IP_jk*0.5));
		}
//		z = VectorXd::Map(Z.data(),Z.size()); 
		y = embeded.topRightCorner(k,k);
		VectorXd X = y.colPivHouseholderQr().solve(z);
		double x_0k = -sqrt(1-X.squaredNorm());
                RowVectorXd x_temp = X.transpose();
                RowVectorXd a(k+1);
		a << x_temp, x_0k;
                RowVectorXd zero = (VectorXd::Zero(n-k)).transpose();
                if(k<n){
                embeded.row(k) << zero,a;
                }
		else if (k==n){ 
                embeded.row(k) <<  a;
                }
	}
        
	for(int i=0; i<dim; ++i){
		gnomonicProjection_temp.row(i) = -1*embeded.row(i)/embeded(i,n);            
	}        
	 gnomonicProjection =  gnomonicProjection_temp.block(0,0,dim,n);
	 normedVertices = gnomonicProjection;
	for(int row=1; row<dim; ++row){
		normedVertices.row(row) /=  sqrt((normedVertices.row(row)).squaredNorm());           
	} 
          
}




Double_t RooFisher::evaluate() const 
{
	vector<Point_d> alphas;
	vector<double> target_alpha;
	double target_alpha_i; 
	//Get target alpha point
	RooRealVar* param; 
	RooFIter paramIter(_paramSet.fwdIterator()) ;
	RooFIter tangentIter(_tangents.fwdIterator()) ;
	while((param=(RooRealVar*)paramIter.next())) {
		target_alpha_i = param->getVal(); 
		target_alpha.push_back(target_alpha_i); 
	}    

	Point_d target_alpha_point(n, target_alpha.begin(), target_alpha.end()); 

/*	TODO Try to make delaunay triangulations member variables. Since the datatype D doesn't have assignment operator it didn't work for me. Kyle, if you have any ideas, it would be great. 
http://doc.cgal.org/latest/Convex_hull_d/classCGAL_1_1Delaunay__d.html
The following way creates only an instance. No copy constructor/assignment operator available
*/	 

	D alpha_Dt(n);
	D gnomonic_Dt(n);
	D normed_Dt(n);


	CGAL_assertion(alpha_Dt.empty());
	//Delaunay triangulation of alphas
	for(vector<vector<double>>::const_iterator it =  parameterPoints.begin(); it !=  parameterPoints.end(); it++) {
		Point_d alpha_i(n, it->begin(), it->end()); 
		alphas.push_back(alpha_i); 
	}
//	return n;
	vector<Point_d>::iterator Itr;	
	for(Itr = alphas.begin(); Itr!= alphas.end(); ++Itr){
		alpha_Dt.insert(*Itr);
	}
        std::list<Simplex_handle> NL = alpha_Dt.all_simplices(D::NEAREST);
        CGAL_assertion(!alpha_Dt.empty());
    	CGAL_assertion(alpha_Dt.is_valid() );

	//Locate target alpha in appropriate simplex of triangulation 
	Vertex_handle v = alpha_Dt.nearest_neighbor(target_alpha_point);
	Simplex_handle s = alpha_Dt.simplex(v);    

	vector<Point_d> Simplex_vertices;
	for(int j=0; j<=n; ++j){
		Vertex_handle vertex = alpha_Dt.vertex_of_simplex(s,j);
		Point_d Pt = alpha_Dt.associated_point(vertex);
		Simplex_vertices.push_back(Pt);
	}
	
	//Barycentric coordinates of target alpha in alpha simplex
	vector<double> coords;
 	vector<Point_d> gnomonicCoords;
 	vector<Point_d> normedCoords;


	K::Barycentric_coordinates_d BaryCoords;
	BaryCoords(Simplex_vertices.begin(), Simplex_vertices.end(),target_alpha_point,std::inserter(coords, coords.begin()));

	//Gnomonic delaunay triangulation
	// Need iterator but MatrixXd doesn't have it so using methods like described here http://stackoverflow.com/questions/26094379/typecasting-eigenvectorxd-to-stdvector and then using the vector
	for(int i=0; i<gnomonicProjection.rows(); ++i){

		VectorXd v1 = gnomonicProjection.row(i);
		vector<double> v2;
		v2.resize(v1.size());
		VectorXd::Map(&v2[0], v1.size()) = v1;
		Point_d gnomonicCoord(n, v2.begin(), v2.end());
		gnomonicCoords.push_back(gnomonicCoord); 
	}


	for(vector<Point_d>::iterator Itr1 = gnomonicCoords.begin(); Itr1!= gnomonicCoords.end(); ++Itr1){
		gnomonic_Dt.insert(*Itr1);
	}

	//normedVertices delaunay triangulation 
	for(int i=0; i<normedVertices.rows(); ++i){

		VectorXd V1 = normedVertices.row(i);
		vector<double> V2;
		V2.resize(V1.size());
		VectorXd::Map(&V2[0], V1.size()) = V1;
		Point_d normedCoord(n, V2.begin(), V2.end());
		normedCoords.push_back(normedCoord); 
	}
   
	for(vector<Point_d>::iterator Itr2 = normedCoords.begin(); Itr2!= normedCoords.end(); ++Itr2){
		normed_Dt.insert(*Itr2);
	}
	vector<double> gnomonicTarget;
	vector<double> normedBaryoCoords;
	// Locate and barycentric coords of gnomonicTarget
	Point_d alphaBaryoCoord(n, coords.begin(), coords.end());
	Vertex_handle vert = gnomonic_Dt.nearest_neighbor(alphaBaryoCoord);
	Simplex_handle simpl = gnomonic_Dt.simplex(vert);    
         
	
	vector<Point_d> Simplex_vertices1;
	for(int k=0; k<=n; ++k){
		Vertex_handle vertex1 = gnomonic_Dt.vertex_of_simplex(simpl,k);
		Simplex_vertices1.push_back(gnomonic_Dt.associated_point(vertex1));
	}


	K::Barycentric_coordinates_d gnomonicbaryoCoords;
	K::Barycentric_coordinates_d normedbaryoCoords;

	gnomonicbaryoCoords(Simplex_vertices1.begin(), Simplex_vertices1.end(),target_alpha_point,std::inserter(gnomonicTarget, gnomonicTarget.begin()));
	//Getting normedBaryoCoords
	Point_d gnomonicTargetCoord(n, gnomonicTarget.begin(), gnomonicTarget.end());
	Vertex_handle vertx = normed_Dt.nearest_neighbor(gnomonicTargetCoord);
	Simplex_handle simplx = normed_Dt.simplex(vertx);    

	vector<Point_d> Simplex_vertices2;
	for(int m=0; m<=n; ++m){
		Vertex_handle vertex2 = normed_Dt.vertex_of_simplex(simplx,m);
		Simplex_vertices2.push_back(normed_Dt.associated_point(vertex2));
	}

	normedbaryoCoords(Simplex_vertices2.begin(), Simplex_vertices2.end(),gnomonicTargetCoord,std::inserter(normedBaryoCoords, normedBaryoCoords.begin()));

	double t_val = atan(std::inner_product(gnomonicTarget.begin(), gnomonicTarget.end(), gnomonicTarget.begin(),0));



	RooAbsReal* unNormtan;

	for(int m=0; m<dim; ++m){
                string rootpdfName = _rootPdfs.at(m)->GetName();
                string rootpdf0Name = _rootPdfs.at(0)->GetName();
                string tName = "cexpr::t(`(" +rootpdfName+ "- InnerProducts[0][m]*"+ rootpdf0Name+")'," +rootpdfName+"," +rootpdf0Name + ")"; 
		RooAbsReal* t = (RooAbsReal*) w->factory(tName.c_str());
		RooAbsReal* Norm = (RooAbsReal*) w->factory("prod:t^2('t*t')");
		double norm_integral = ((RooAbsReal*)Norm->createIntegral(*x, NormSet(*x)))->getVal();
		RooAbsReal* u = (RooAbsReal*) w->factory("cexpr::u('t/sqrt(norm_integral)')");

		RooAbsReal* unNormtan_i = (RooAbsReal*) w->factory("sum::uNti(normBaryoCoords[m]*u,unNormtan)");
		unNormtan = (RooAbsReal*) w->factory("sum::unt(normedBaryoCoords[m]*u,unNormtan)");






	}
	RooAbsReal* unnorm_tan_prod =  (RooAbsReal* ) w->factory("prod::unt*unt(unNormtan*unNormtan)");
	RooAbsReal* normtan = unnorm_tan_prod->createIntegral(*x, NormSet(*x));
	RooAbsReal* tangent = (RooAbsReal*) w->factory("cexpr::tangent(`(unNormtan/sqrt(normtan))',unNormtan,normtan");

	RooAbsReal* q_interpolant =  (RooAbsReal*) w->factory("cexpr::tangent(`(cos(t_val)*,_rootPdfs.at(0) + sin(t_val)*tangent)',tangent,_rootPdfs.at(0)");
	RooAbsReal* interpolant =  (RooAbsReal* ) w->factory("prod::interpolant(q_interpolant*q_interpolant)");

	Double_t interp_val = interpolant->getVal();

	return interp_val;   

}   
