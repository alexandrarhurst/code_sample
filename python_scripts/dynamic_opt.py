# dynamic_opt.py
"""Volume 2: Dynamic Optimization.
Alexandra Hurst
<Class>
<Date>
"""

import numpy as np
from matplotlib import pyplot as plt

# Problem 1
def graph_policy(policy, b, u):
    """Plot the utility gained over time.
    Return the total utility gained with the policy given.

    Parameters:
        policy (ndarray): Policy vector.
        b (float): Discount factor. 0 < beta < 1.
        u (function): Utility function.

    Returns:
        total_utility (float): Total utility gained from the policy given.
    """
    if sum(policy)!=1:
        raise ValueError("Sum of the policy vector must equal 1")
    l=[b**t*u(policy[t]) for t in xrange(len(policy))]
    temp=0
    x=[]
    for i in l:
        temp+=i
        x.append(temp)
    plt.plot(x)
    plt.show()
    return sum(l)


# Problem 2
def consumption(N, u=lambda x: np.sqrt(x)):
    """Create the consumption matrix for the given parameters.

    Parameters:
        N (int): Number of pieces given, where each piece of cake is the
            same size.
        u (function): Utility function.

    Returns:
        C ((N+1,N+1) ndarray): Consumption matrix.
    """
    w=np.linspace(0,1,N+1).astype(np.float)
    m=np.zeros((N+1,N+1))
    for i in xrange(N+1):
        k=1
        for j in xrange(i+1,N+1):
            m[j,i]=u(w[k])
            k+=1
    return m


# Problems 3-5
def eat_cake(T, N, B, u=lambda x: np.sqrt(x)):
    """Create the value and policy matrices for the given parameters.

    Parameters:
        T (int): Time at which to end (T+1 intervals).
        N (int): Number of pieces given, where each piece of cake is the
            same size.
        B (float): Discount factor, where 0 < B < 1.
        u (function): Utility function.

    Returns:
        A ((N+1,T+1) ndarray): The matrix where the (ij)th entry is the
            value of having w_i cake at time j.
        P ((N+1,T+1) ndarray): The matrix where the (ij)th entry is the
            number of pieces to consume given i pieces at time j.
    """
    m=consumption(N,u)
    t=np.linspace(0,1,N+1)
    A=np.zeros((N+1,T+1))
    P=np.zeros((N+1,T+1))
    for i in xrange(N+1):
        P[i,T]=t[i]
        A[i,T]=u(t[i])
    for w in xrange(1,T+1):
        i=T-w
        temp=np.zeros((N+1,N+1))
        for j in xrange(N+1):
            for k in xrange(N+1):
                if j>=k:
                    temp[j,k]=m[j,k]+B*A[k,i+1]
        cake=np.argmax(temp,axis=1)
        A[:,i]=np.max(temp, axis=1)
        for j in xrange(N+1):
            P[j,i]=t[j-cake[j]]
         
    return A,P


# Problem 6
def find_policy(T, N, B, u=lambda x: np.sqrt(x)):
    """Find the most optimal route to take assuming that we start with all of
    the pieces. Show a graph of the optimal policy using graph_policy().

    Parameters:
        T (int): Time at which to end (T+1 intervals).
        N (int): Number of pieces given, where each piece of cake is the same size.
        B (float): Discount factor, where 0 < B < 1.
        u (function): Utility function.

    Returns:
        maximum_utility (float): The total utility gained from the
            optimal policy.
        optimal_policy ((N,) nd array): The matrix describing the optimal
            percentage to consume at each time.
    """
    A,P=eat_cake(T,N,B,u)
    x=np.linspace(0,1,N+1)
    val=[]
    opt=[]
    other=N
    total=0
    for i in xrange(T+1):
        eating=P[other,i]*N
        opt.append(eating)
        other=other-eating
        total+= B**(i-1)*u(x[eating])
        val.append(total)
    opt=np.asarray(opt)
    opt =1.*opt/N
    return graph_policy(opt,B,u), opt
    


"""if __name__=="__main__":
    f=lambda x: np.sqrt(x)
    #graph_policy(np.array([1,0,0,0,0]),.9,f)
    #print consumption(4)
    print eat_cake(4,5,.9)
    print find_policy(4,5,.9)"""