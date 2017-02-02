Steps for compiling the program and running it.

1. ROOT, CGAL and Eigen3 should be installed.
2. On Mac brew install cgal/eigen should do it.
3. In the roofit-fisher directory make should compile the library.
4. root test.C would test the code.



Problems currently faced

1. The plotting doesn't work in test.C for the RooFisher class although it is inherited from RooAbsReal.
2. At present the value I get for the test i.e Gauss(x=0, \mu=0.5, \sigma=0.5) is not the value I expect.
3. I feel this is because of the gnomonic barycentric coordinates I compute in lines 210 to 225.
4. When I look at the python code I see you write 
     gnomonicTarget = linalg.inv(gnomonicSimplex.transform[0,:dim-1,:]).dot(baryCoords)

 to achieve the gnomonicTarget. But I feel I'm simply getting the Barycentric coordinates. I am bit confused with the inverse you compute. What is been physically done here? If you can tell me I can talk to the writers of CGAL to see how this can be achieved. 
