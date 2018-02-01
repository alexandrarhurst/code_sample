# gradient_methods.py
"""Volume 2: N-D Optimization 2 (Gradient Descent Methods).
Alexandra Hurst
<Class>
<Date>
"""

import numpy as np
from scipy import linalg as la
from scipy.optimize import fmin_cg

# Problem 1
def steepestDescent(f, Df, x0, step=1, tol=.0001, maxiters=50):
    """Use the Method of Steepest Descent to find the minimizer x of the convex
    function f:Rn -> R.

    Parameters:
        f (function Rn -> R): The objective function.
        Df (function Rn -> Rn): The gradient of the objective function f.
        x0 ((n,) ndarray): An initial guess for x.
        step (float): The initial step size.
        tol (float): The convergence tolerance.

    Returns:
        x ((n,) ndarray): The minimizer of f.
    """
    for i in xrange(maxiters):
        a=step
        while f(x0-a*Df(x0))>=f(x0):
            a=a/2.
            if a<tol:
                return x0
        x0=x0-a*Df(x0)
    return x0
            


# Problem 2
def conjugateGradient(b, x0, Q, tol=.0001):
    """Use the Conjugate Gradient Method to find the solution to the linear
    system Qx = b.

    Parameters:
        b  ((n, ) ndarray)
        x0 ((n, ) ndarray): An initial guess for x.
        Q  ((n,n) ndarray): A positive-definite square matrix.
        tol (float): The convergence tolerance.

    Returns:
        x ((n, ) ndarray): The solution to the linear systm Qx = b, according
            to the Conjugate Gradient Method.
    """
    r=np.dot(Q,x0)-b
    d=-r
    k=0
    while max(r) > tol:
        a=np.dot(r,r)/np.dot(d,np.dot(Q,d))
        x0=x0+a*d
        rk=r+a*np.dot(Q,d)
        beta=np.dot(rk,rk)/np.dot(r,r)
        r=rk
        d=-r+beta*d
        k+=1
    return x0


# Problem 3
def prob3(filename="linregression.txt"):
    """Use conjugateGradient() to solve the linear regression problem with
    the data from linregression.txt.
    Return the solution x*.
    """
    data=np.loadtxt(filename)
    m,n=np.shape(data)
    y=data[:,0]
    data=np.column_stack((np.ones_like(y), data[:,1:]))
    b=np.dot(data.T, y)
    x=[ 0.55672449,  0.62291634,  0.58657931,  0.65791076,  0.04976144,  0.87430799,  0.41095175]
    return conjugateGradient(b, x, np.dot(data.T,data))
    
def objective(x,y,b):
    return (np.log(1+np.exp(x.dot(b)))-y*(x.dot(b))).sum()


# Problem 4
def prob4(filename="logregression.txt"):
    """Use scipy.optimize.fmin_cg() to find the maximum likelihood estimate
    for the data in logregression.txt.
    """
    def objective(b):
        return (np.log(1+np.exp(x.dot(b)))-y*(x.dot(b))).sum()
    
    data=np.loadtxt(filename)
    y=data[:,0]
    x=np.column_stack((np.ones_like(y), data[:,1:]))
    temp=np.ones(4)
    b=fmin_cg(objective, temp)
    return b


"""if __name__=="__main__":
    f=lambda x: x[0]**2+x[1]**2
    g=lambda x: np.array([[2*x[0], 2*x[1]]])
    x0=np.array([[1,1]])
    #print g(x0)
    #print steepestDescent(f,g,x0)
    print prob4()"""
