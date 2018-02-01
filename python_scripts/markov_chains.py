# markov_chains.py
"""Volume II: Markov Chains.
Alexandra Hurst
Math 321
10/25/16
"""

import numpy as np
from scipy import linalg as la


# Problem 1
def random_markov(n):
    """Create and return a transition matrix for a random Markov chain with
    'n' states. This should be stored as an nxn NumPy array.
    """
    A=np.random.random((n,n))
    i=0
    while i<len(A):
        length=sum(A[:,i])
        j=0
        while j<len(A):
            A[j,i]=A[j,i]/length
            j+=1
        i+=1
    return A


# Problem 2
def forecast(days):
    """Forecast tomorrow's weather given that today is hot."""
    transition = np.array([[0.7, 0.6], [0.3, 0.4]])
    current=0
    l=[]
    # Sample from a binomial distribution to choose a new state.
    for item in xrange(days):
        current=np.random.binomial(1, transition[1,current])
        l.append(current)
    return l


# Problem 3
def four_state_forecast(days):
    """Run a simulation for the weather over the specified number of days,
    with mild as the starting state, using the four-state Markov chain.
    Return a list containing the day-by-day results, not including the
    starting day.

    Examples:
        >>> four_state_forecast(3)
        [0, 1, 3]
        >>> four_state_forecast(5)
        [2, 1, 2, 1, 1]
    """
    l=[]
    current=1
    this=np.array([0,1,2,3])
    transition=np.array([[.5,.3,.1,0.],[.3,.3,.3,.3],[.2,.3,.4,.5],[0.,.1,.2,.2]])
    for item in range(days):
        current=np.random.multinomial(1, transition[current])
        current=np.dot(this,current)
        l.append(current)
    return l

# Problem 4
def steady_state(A, tol=1e-12, N=40):
    """Compute the steady state of the transition matrix A.

    Inputs:
        A ((n,n) ndarray): A column-stochastic transition matrix.
        tol (float): The convergence tolerance.
        N (int): The maximum number of iterations to compute.

    Raises:
        ValueError: if the iteration does not converge within N steps.

    Returns:
        x ((n,) ndarray): The steady state distribution vector of A.
    """
    original=np.copy(A)
    x=np.random.random(len(A))
    x=x/sum(x)
    error=la.norm(x, ord=np.inf)
    for i in xrange(N):
        if error>=tol:
            prev=x
            x=np.dot(A,x)
            error=la.norm(prev-x, ord=np.inf)
            print error
        else:
            break
    if error<tol:
        return x
    else:
        raise ValueError("A^k does not converge")
    


# Problems 5 and 6
class SentenceGenerator(object):
    """Markov chain creator for simulating bad English.

    Attributes:
        (what attributes do you need to keep track of?)

    Example:
        >>> yoda = SentenceGenerator("Yoda.txt")
        >>> print yoda.babble()
        The dark side of loss is a path as one with you.
    """

    def __init__(self, filename):
        """Read the specified file and build a transition matrix from its
        contents. You may assume that the file has one complete sentence
        written on each line.
        """
        l=[]
        s=["$tart"]
        setting=set()
        for line in open(filename).readlines():
            l.append(line)
            w=line.split()
            setting.update(w)
        length=len(setting)
        matrix=np.zeros((length+2, length+2))
        for line in l:
            sentence=line.split()
            for i in xrange(len(sentence)):
                if sentence[i] not in s:
                    s.append(sentence[i])
                sentence[i]=s.index(sentence[i])
            matrix[sentence[0],0]=1
            i=1
            while i<(len(sentence)):
                matrix[sentence[i],sentence[i-1]]+=1
                i+=1        
            matrix[length+1, sentence[i-1]]+=1
            matrix[length+1,length+1]+=1
        for i in xrange(length+2):
            if sum(matrix[:,i])!=0:
                matrix[:,i]=matrix[:,i]/sum(matrix[:,i])
            else:
                print i, s[i]
        self.matrix= matrix
        self.list=s
        
        
            
            
        

    def babble(self):
        """Begin at the start sate and use the strategy from
        four_state_forecast() to transition through the Markov chain.
        Keep track of the path through the chain and the corresponding words.
        When the stop state is reached, stop transitioning and terminate the
        sentence. Return the resulting sentence as a single string.
        """
        n=len(self.matrix)-1
        current=0
        l=[]
        s=""
        this=xrange(n+1)
        while current != n:
            #print self.matrix[current]
            current=np.random.multinomial(1, self.matrix[:,current])
            current=np.dot(this,current)
            if current !=n:
                l.append(self.list[current])
        for item in l:
            s=s+" "+str(item)
        return s
        
        

