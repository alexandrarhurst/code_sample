# pagerank.py
"""Volume 1: The Page Rank Algorithm.
Alexandra Hurst
<Class>
<Date>
"""

from scipy import sparse
from scipy import linalg as la
import numpy as np

# Problem 1
def to_matrix(filename, n):
    """Return the nxn adjacency matrix described by datafile.

    Parameters:
        datafile (str): The name of a .txt file describing a directed graph.
        Lines describing edges should have the form '<from node>\t<to node>\n'.
        The file may also include comments.
    n (int): The number of nodes in the graph described by datafile

    Returns:
        A SciPy sparse dok_matrix.
    """
    A=sparse.dok_matrix((n,n))
    with open(filename, 'r') as file:
        for line in file:
            line=line.strip().split()
            try:
                x=int(line[0])
                y=int(line[1])
                A[x,y]=1
            except:
                pass
    return A


# Problem 2
def calculateK(A,N):
    """Compute the matrix K as described in the lab.

    Parameters:
        A (ndarray): adjacency matrix of an array
        N (int): the datasize of the array

    Returns:
        K (ndarray)
    """
    D=np.ones((1,N))
    for i in xrange(N):
        if sum(A[i])==0:
            A[i]=np.ones((1,N))
        D[:,i]=sum(A[i])
    K=A/D.T
    return K.T
    


# Problem 3
def iter_solve(adj, N=None, d=.85, tol=1E-5):
    """Return the page ranks of the network described by 'adj'.
    Iterate through the PageRank algorithm until the error is less than 'tol'.

    Parameters:
        adj (ndarray): The adjacency matrix of a directed graph.
        N (int): Restrict the computation to the first 'N' nodes of the graph.
            If N is None (default), use the entire matrix.
        d (float): The damping factor, a float between 0 and 1.
        tol (float): Stop iterating when the change in approximations to the
            solution is less than 'tol'.

    Returns:
        The approximation to the steady state.
    """
    if N==None:
        N=len(adj)
    K=calculateK(adj, len(adj))
    p0=1/N*np.ones(N)
    p=lambda t: d*np.dot(K,p0)+(1-d)/N*np.ones(N)
    p1=p(p0)
    while la.norm(p1-p0)>tol:
        p0=p1
        p1=p(p0)
    return p1


# Problem 4
def eig_solve(adj, N=None, d=.85):
    """Return the page ranks of the network described by 'adj'. Use SciPy's
    eigenvalue solver to calculate the steady state of the PageRank algorithm

    Parameters:
        adj (ndarray): The adjacency matrix of a directed graph.
        N (int): Restrict the computation to the first 'N' nodes of the graph.
            If N is None (default), use the entire matrix.
        d (float): The damping factor, a float between 0 and 1.
        tol (float): Stop iterating when the change in approximations to the
            solution is less than 'tol'.

    Returns:
        The approximation to the steady state.
    """
    if N==None:
        N=len(adj)
    K=calculateK(adj, N)
    E=np.ones_like(K)
    p0=1/N*np.ones(N)
    B=d*K+((1.-d)/N)*E
    vals, vecs=la.eig(B)
    largest=vals.argsort()[-1]
    largest=vecs[:,largest].real
    return largest*1./sum(largest)


# Problem 5
def team_rank(filename='ncaa2013.csv'):
    """Use iter_solve() to predict the rankings of the teams in the given
    dataset of games. The dataset should have two columns, representing
    winning and losing teams. Each row represents a game, with the winner on
    the left, loser on the right. Parse this data to create the adjacency
    matrix, and feed this into the solver to predict the team ranks.

    Parameters:
        filename (str): The name of the data file.
    Returns:
        ranks (list): The ranks of the teams from best to worst.
        teams (list): The names of the teams, also from best to worst.
    """
    team=set()
    winners=[]
    with open(filename, 'r') as file:
        file.readline()
        for line in file:
            thing=line.strip().split(',')
            team.add(thing[0])
            team.add(thing[1])
            winners.append(thing)
    N=len(team)
    team=list(team)
    adj=np.zeros((N,N))
    for game in winners:
        adj[team.index(game[1]), team.index(game[0])]=1
    A=iter_solve(adj, d=.7)
    i=np.argsort(A)[::-1]
    return A[i], [team[x] for x in i]


"""if __name__=="__main__":
    A=to_matrix('matrix.txt', 8)
    A=A.toarray()
    #print calculateK(A,8)
    #print iter_solve(A)
    #print eig_solve(A)
    print team_rank()"""
