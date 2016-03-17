#include <CGAL/Epick_d.h>
#include <CGAL/point_generators_d.h>
#include <CGAL/Delaunay_triangulation.h>
#include <CGAL/algorithm.h>
#include <CGAL/Timer.h>
#include <CGAL/assertions.h>

#include <iostream>
#include <iterator>
#include <vector>


const int D=3;

typedef CGAL::Epick_d< CGAL::Dimension_tag<D> >               K;
typedef CGAL::Delaunay_triangulation<K>                       T;



int main(){
    int N = 3;
    CGAL::Timer cost;
    std::vector<K::Point_d> points;
    std::vector<double> input1, input2, input3;
    input1.push_back(0);
    input1.push_back(1);
    input1.push_back(2);

    input2.push_back(3);
    input2.push_back(4);
    input2.push_back(5);

    input3.push_back(2);
    input3.push_back(6);
    input3.push_back(8);
   

    K::Point_d point1(1,1,1);
    K::Point_d point2(2,2,2);
    K::Point_d point3(3,3,3);

    K::Point_d point(1,2,3);


    points.push_back(point1);
    points.push_back(point2);
    points.push_back(point3);
   
   
    T t(D);
    CGAL_assertion(t.empty());
   
    // insert the points in the triangulation
    cost.reset();cost.start();
    std::cout << "  Delaunay triangulation of "<<N<<" points in dim "<<D<< std::flush;
    t.insert(points.begin(), points.end());
    std::cout << " done in "<<cost.time()<<" seconds." << std::endl;
    CGAL_assertion( t.is_valid() );

    T::Full_cell_handle c;
    c = t.locate(point);

    return 0;
}
