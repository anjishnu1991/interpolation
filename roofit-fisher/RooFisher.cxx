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


	RooFisher::RooFisher(const char *name, const char *title, const RooArgList& paramSet, const  FunctionMap& FisherMap, const RooWorkspace& win): 


		RooAbsReal (name, title),
		_paramSet("paramSet","paramset", this), 
		_inputPdfs("inputPdfs","inputPdfs", this)

{ 
w = (RooWorkspace*)win.Clone();
	for(FunctionMap::const_iterator it = FisherMap.begin(); it != FisherMap.end(); it++) {
		// 	std::cout <<   iterator->second   << std::endl ;
		_parameterPoints = it->first;
		_inputPdfs.add(*it->second);

	}  



	RooFIter Iter_pdf1(_inputPdfs.fwdIterator());
	RooAbsReal* pdf1;
	RooAbsReal* pdf2;
	RooAbsReal* inner_prod;
	vector<double> list_inner_prod;
	RooAbsReal* q;

	while((pdf1=(RooAbsReal*)Iter_pdf1.next())){
		string pdf1Name = pdf1->GetName();
		string sqrtF = "cexpr::sqrt" + pdf1Name +"('sqrt(" + pdf1Name + ")'," + pdf1Name + ")";      
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
			x = w->var("x");
			RooAbsReal* integral = inner_prod->createIntegral(*x);
			double Inner_Product = integral->getVal();
			list_inner_prod.push_back(Inner_Product);
		}
		InnerProducts.push_back(list_inner_prod);
} 

	/*TODO RooAbsCacheManger */  



	dim =  InnerProducts.size();
	n = dim -1;
        embeded = MatrixXd::Zero(dim,dim);
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
		VectorXd x = y.colPivHouseholderQr().solve(z);
		double x_0k = -sqrt(1-x.squaredNorm());
                RowVectorXd x_temp = x.transpose();
                RowVectorXd a(k+1);
		a << x_temp, x_0k;
                RowVectorXd zero = (VectorXd::Zero(n-k)).transpose();
                if(k<n){
                embeded.row(k) << zero,a;
                }
		else if (k==n){ 
                embeded.row(k) <<  a;
                }
                cout << embeded << endl;
	}
	for(int i=0; i<dim; ++i){
		gnomonicProjection(i) = -1*embeded(i)/embeded(i,n);            
	}        
	normedVertices =  gnomonicProjection.block(0,0,dim,n);
	for(int col=0; col<n; ++col){
		normedVertices.col(col) /=  (normedVertices.col(col)).squaredNorm();           
	} 




}




Double_t RooFisher::evaluate() const 
{
	vector<Point_d> alphas;
	vector<double> target_alpha;
	//Get target alpha point
	RooAbsReal* param; 
	RooFIter paramIter(_paramSet.fwdIterator()) ;
	RooFIter tangentIter(_tangents.fwdIterator()) ;
	while((param=(RooAbsReal*)paramIter.next())) {
		double target_alpha_i = param->getVal(); 
		target_alpha.push_back(target_alpha_i); 
	}    


	Point_d target_alpha_point(dim, target_alpha.begin(), target_alpha.end()); 

	/*TODO Try to make delaunay triangulations member variables. Since the datatype D doesn't have assignment operator it didn't work for me. Kyle, if you have any ideas, it would be great. 
http://doc.cgal.org/latest/Convex_hull_d/classCGAL_1_1Delaunay__d.html
The following way creates only an instance. No copy constructor/assignment operator available
	 */

	D alpha_Dt(n);
	D gnomonic_Dt(n);
	D normed_Dt(n);




	//Delaunay triangulation of alphas
	for(keyType::const_iterator it =  _parameterPoints.begin(); it !=  _parameterPoints.end(); it++) {
		Point_d alpha_i(dim, (it->second).begin(), (it->second).end()); 
		alphas.push_back(alpha_i); 
	}
	for(vector<Point_d>::iterator Itr = alphas.begin(); Itr!= alphas.end(); ++Itr){
		alpha_Dt.insert(*Itr);
	}
	//Gnomonic delaunay triangulation
	// Need iterator but MatrixXd doesn't have it so using methods like described here http://stackoverflow.com/questions/26094379/typecasting-eigenvectorxd-to-stdvector and then using the vector

	vector<Point_d> gnomonicCoords;
	for(int i=0; i<gnomonicProjection.rows(); ++i){

		VectorXd v1 = gnomonicProjection.row(i);
		vector<double> v2;
		v2.resize(v1.size());
		VectorXd::Map(&v2[0], v1.size()) = v1;
		Point_d gnomonicCoord(dim, v2.begin(), v2.end());
		gnomonicCoords.push_back(gnomonicCoord); 
	}

	for(vector<Point_d>::iterator Itr1 = gnomonicCoords.begin(); Itr1!= gnomonicCoords.end(); ++Itr1){
		gnomonic_Dt.insert(*Itr1);
	}

	vector<Point_d> normedCoords;
	//normedVertices delaunay triangulation 
	for(int i=0; i<normedVertices.rows(); ++i){

		VectorXd V1 = normedVertices.row(i);
		vector<double> V2;
		V2.resize(V1.size());
		VectorXd::Map(&V2[0], V1.size()) = V1;
		Point_d normedCoord(dim, V2.begin(), V2.end());
		normedCoords.push_back(normedCoord); 


	}

	for(vector<Point_d>::iterator Itr2 = normedCoords.begin(); Itr2!= normedCoords.end(); ++Itr2){
		normed_Dt.insert(*Itr2);
	}
	//Locate target alpha in appropriate simplex of triangulation 
	Vertex_handle v = alpha_Dt.nearest_neighbor(target_alpha_point);
	Simplex_handle s = alpha_Dt.simplex(v);    

	vector<Point_d> Simplex_vertices;
	for(int j=0; j<=n; ++j){
		Vertex_handle vertex = alpha_Dt.vertex_of_simplex(s,j);
		Simplex_vertices.push_back(alpha_Dt.associated_point(vertex));
	}

	vector<double> coords;
	vector<double> gnomonicTarget;
	vector<double> normedBaryoCoords;
	//Barycentric coordinates of target alpha in alpha simplex
	K::Barycentric_coordinates_d BaryCoords;
	BaryCoords(Simplex_vertices.begin(), Simplex_vertices.end(),target_alpha_point,std::inserter(coords, coords.begin()));
	// Locate and barycentric coords of gnomonicTarget
	Point_d alphaBaryoCoord(dim, coords.begin(), coords.end());
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
	Point_d gnomonicTargetCoord(dim, gnomonicTarget.begin(), gnomonicTarget.end());
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
		RooAbsReal* t = (RooAbsReal*) w->factory("cexpr::t(`(_rootPdfs.at(i) - InnerProducts[0][m]*_rootPdfs.at(m))',_rootPdfs.at(m),_rootPdfs.at(0)");
		RooAbsReal* Norm = (RooAbsReal*) w->factory("prod:t^2('t*t')");
		double norm_integral = ((RooAbsReal*)Norm->createIntegral(*x))->getVal();
		RooAbsReal* u = (RooAbsReal*) w->factory("cexpr::u('t/sqrt(norm_integral)')");

		RooAbsReal* unNormtan_i = (RooAbsReal*) w->factory("sum::uNti(normBaryoCoords[i]*u,unNormtan)");
		unNormtan = (RooAbsReal*) w->factory("sum::unt(normedBaryoCoords[i]*u,unNormtan)");






	}
	RooAbsReal* unnorm_tan_prod =  (RooAbsReal* ) w->factory("prod::unt*unt(unNormtan*unNormtan)");
	RooAbsReal* normtan = unnorm_tan_prod->createIntegral(*x);
	RooAbsReal* tangent = (RooAbsReal*) w->factory("cexpr::tangent(`(unNormtan/sqrt(normtan))',unNormtan,normtan");

	RooAbsReal* q_interpolant =  (RooAbsReal*) w->factory("cexpr::tangent(`(cos(t_val)*,_rootPdfs.at(0) + sin(t_val)*tangent)',tangent,_rootPdfs.at(0)");
	RooAbsReal* interpolant =  (RooAbsReal* ) w->factory("prod::interpolant(q_interpolant*q_interpolant)");

	Double_t interp_val = interpolant->getVal();

	return interp_val;   

}   
