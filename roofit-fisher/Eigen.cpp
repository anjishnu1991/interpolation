#include <iostream>
#include <Dense>
#include <vector>
using namespace Eigen;
using namespace std;




int main()
{
  MatrixXd m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = 1;
  VectorXd v1 = m.row(0);
  cout << v1[1] << "   " << m.rows() <<   "    " << m << endl;
  vector<double> v2;
v2.resize(v1.size());
VectorXd::Map(&v2[0], v1.size()) = v1;
  cout << v2[0] << "   " << v2[1] << endl;
 cout << std::abs(v2) << endl;
} 
//  std::cout << m << std::endl;
/*
    vector<vector <double> > Innerproducts;
    int dim =  Innerproducts.size();
    int n = dim -1;
    MatrixXd embeded;
    MatrixXd gnomonicProjection;
    embeded(0,n) = -1;
    for(int k=1; k<dim;++k){
       vector<double> Z; 
       MatrixXd y(k,k);
       VectorXd z;
       for (int j=0; j<k; ++j){
           Z[j] = (1 - (pow(Innerproducts[j][k],2))*0.5);
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
*/









