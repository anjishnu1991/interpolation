

## Ambient Fisher Gnomonic Interpolant


# by Kyle Cranmer, Anjishnu Bandyopadhay
# based on notes and discussion with Jeff Streets at UCI.



import numpy as np
import numpy.linalg as linalg
import matplotlib as mpl
import matplotlib.pyplot as plt
import scipy.optimize
from math import sqrt
from scipy.spatial import Delaunay


#def interpolateFunction(alphas,alpha):
    
# ## Create pairs of (parameter, distribution)


#parameter points
alphas = np.array([[0,0],[1,0],[0,1]])

# dim = 1+#dim parameters = dim of embedding
dim = 3 
# for starters, define a parametrized family of functions explicitly and draw from it
f = lambda alpha: lambda x : np.exp(-0.5*(x-alpha[0])**2 / (0.5*alpha[1]+1)**2)/np.sqrt(2*np.pi) / (0.5*alpha[1]+1)
dists = []
for alpha in alphas:
    dists.append( f(alpha) )


# ## Calculate pair-wise chord distances, embed on n-sphere, & rotate first to south pole

# It's going to be easier to work in the space of the sqrt of distributions, so let's define a simple transformation q 


q = lambda h: (lambda x: np.sqrt(h(x)))



def inner_product(q1,q2, xmin=-7, xmax=7):
    # this is a simple numeric integration
    num = 10000.
    xarray = np.linspace(xmin,xmax,num)
    return np.sum(q1(xarray) * q2(xarray))*(xmax-xmin)/num



(inner_product(q(dists[0]),q(dists[0])), inner_product(q(dists[1]),q(dists[1])),inner_product(q(dists[2]),q(dists[2])))


## Create pairs of (parameter simplex, Gnomonic simplex)


def getChordDistance(q1,q2):
    return 2.*np.sin( np.arccos( inner_product(q1, q2) ) /2. )



tempSim=[]
for f1 in dists:
    temp = []
    for f2 in dists:
        temp.append(getChordDistance(q(f1),q(f2)))
    tempSim.append(temp)
chordDistMatrix=np.array(tempSim)
chordDistMatrix #diagonals should be close to 0



## Embeding functions onto n-sphere
n=dim-1
embeded=np.zeros(shape=(dim,dim))
embeded[0]=[0,0,-1]
a=np.array([[-1], [2,3]], dtype=object)

for k in range(1,dim):
    y=np.empty([k,k])
    z=np.zeros(k)
    for j in range(0,k):
        z[j]=1-(chordDistMatrix[j][k]**2)*0.5
        y[j]=np.delete(embeded[j],np.arange(n+1-k))
    x = np.linalg.solve(y,z)
    x_0k=-sqrt(1-np.sum(x**2)) #negative sign to keep it totally in southern hemisphere
    a=np.append(x_0k,x)
    embeded[k]=np.append(np.zeros(n-k),a)



pointsOnSphere = embeded.copy()



gnomonicProjection = pointsOnSphere.copy()
for i, point in enumerate(pointsOnSphere):
    gnomonicProjection[i] = -1.*point/point[-1]



nSamples = 15 #samples along ray for visualization
rays = np.zeros((3*nSamples,dim))
for i, point in enumerate(gnomonicProjection):
    for j, c in enumerate(np.linspace(0,1,nSamples)):
        rays[i*nSamples+j] = c * point



alphaSimplex = Delaunay(alphas)
gnomonicSimplex = Delaunay(gnomonicProjection[:3,:2])



normedVertices = gnomonicProjection[:3,:2].copy()
normedVertices[1] /= linalg.norm(normedVertices[1])
normedVertices[2] /= linalg.norm(normedVertices[2])
normedSimplex = Delaunay(normedVertices)



inner_product(q(dists[0]),q(dists[1])),inner_product(q(dists[0]),q(dists[2])),inner_product(q(dists[1]),q(dists[2]))


pointsOnSphere[0].dot(pointsOnSphere[1]),pointsOnSphere[0].dot(pointsOnSphere[2]),pointsOnSphere[1].dot(pointsOnSphere[2])


# Create Interpolant


alpha = np.array([0.,0.5])
baryCoords = alphaSimplex.transform[0,:dim-1,:].dot(alpha)
gnomonicTarget = linalg.inv(gnomonicSimplex.transform[0,:dim-1,:]).dot(baryCoords)
normedBaryCoords = normedSimplex.transform[0,:dim-1,:].dot(gnomonicTarget)
t = np.arctan(linalg.norm(gnomonicTarget))



dot01 = inner_product(q(dists[0]),q(dists[1]))
dot02 = inner_product(q(dists[0]),q(dists[2]))
t1 = lambda x: q(dists[1])(x) - dot01*q(dists[0])(x)
t2 = lambda x: q(dists[2])(x) - dot02*q(dists[0])(x)
norm1 = inner_product(t1,t1)
norm2 = inner_product(t2,t2)
u1 = lambda x: t1(x)/np.sqrt(norm1)
u2 = lambda x: t2(x)/np.sqrt(norm2)
unnorm_tan = lambda x: u1(x)*normedBaryCoords[0]+u2(x)*normedBaryCoords[1]
norm_tan = inner_product(unnorm_tan,unnorm_tan)
tangent = lambda x: unnorm_tan(x) / np.sqrt(norm_tan)
q_interpolant = lambda x: np.cos(t)*q(dists[0])(x) + np.sin(t)*tangent(x) 
interpolant = lambda x: ( np.cos(t)*q(dists[0])(x) + np.sin(t)*tangent(x) )**2



xarray = np.linspace(-5,5,100)
plt.plot(xarray,dists[0](xarray),c='blue')
plt.plot(xarray,dists[1](xarray),c='r')
plt.plot(xarray,dists[2](xarray),c='g')
plt.plot(xarray,interpolant(xarray),c='b',ls='dashed')
plt.show()


#return interpolant












