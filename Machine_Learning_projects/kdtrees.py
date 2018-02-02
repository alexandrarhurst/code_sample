# kdtrees.py
"""Volume 2A: Data Structures 3 (K-d Trees).
Alexandra Hurst
Math 321
10/10/16
"""

import numpy as np
from trees import BSTNode
from trees import BST
from scipy.spatial import KDTree
from sklearn import neighbors


# Problem 1
def metric(x, y):
    """Return the euclidean distance between the 1-D arrays 'x' and 'y'.

    Raises:
        ValueError: if 'x' and 'y' have different lengths.

    Example:
        >>> metric([1,2],[2,2])
        1.0
        >>> metric([1,2,1],[2,2])
        ValueError: Incompatible dimensions.
    """
    if len(x)!=len(y):
        raise ValueError("Incompatible dimensions.")
    else:
        i=0
        summation=0
        while i<len(x):
            summation=summation+(x[i]-y[i])**2
            i+=1
        summation=np.sqrt(summation)
        return summation


# Problem 2
def exhaustive_search(data_set, target):
    """Solve the nearest neighbor search problem exhaustively.
    Check the distances between 'target' and each point in 'data_set'.
    Use the Euclidean metric to calculate distances.

    Inputs:
        data_set ((m,k) ndarray): An array of m k-dimensional points.
        target ((k,) ndarray): A k-dimensional point to compare to 'dataset'.

    Returns:
        ((k,) ndarray) the member of 'data_set' that is nearest to 'target'.
        (float) The distance from the nearest neighbor to 'target'.
    """
    shortest=2**53
    listy=[]
    for item in data_set:
        compare=metric(target, item)
        if compare<shortest:
            shortest=compare
            listy=item
    return listy, shortest
    


# Problem 3: Write a KDTNode class.
class KDTNode(BSTNode):
    
    def __init__(self, data):
        BSTNode.__init__(self, data)
        if type(data) is not np.ndarray:
            raise TypeError("Input not np.array")
        else:
            self.axis=None

            

# Problem 4: Finish implementing this class by overriding
#            the __init__(), insert(), and remove() methods.
class KDT(BST):
    """A k-dimensional binary search tree object.
    Used to solve the nearest neighbor problem efficiently.

    Attributes:
        root (KDTNode): the root node of the tree. Like all other
            nodes in the tree, the root houses data as a NumPy array.
        k (int): the dimension of the tree (the 'k' of the k-d tree).
    """

    def find(self, data):
        """Return the node containing 'data'. If there is no such node
        in the tree, or if the tree is empty, raise a ValueError.
        """

        # Define a recursive function to traverse the tree.
        def _step(current):
            """Recursively step through the tree until the node containing
            'data' is found. If there is no such node, raise a Value Error.
            """
            if current is None:                     # Base case 1: dead end.
                raise ValueError(str(data) + " is not in the tree")
            elif np.allclose(data, current.value):
                return current                      # Base case 2: data found!
            elif data[current.axis] < current.value[current.axis]:
                return _step(current.left)          # Recursively search left.
            else:
                return _step(current.right)         # Recursively search right.

        # Start the recursion on the root of the tree.
        return _step(self.root)
        
    def parent_find2(self, data):
        
        def _step(current, extra=None):
            if current is None:
                return extra
            if np.allclose(data, current.value):
                raise ValueError("Value is already in the tree")
            if data[current.axis] < current.value[current.axis]:
                return _step(current.left, current)
            else:
                return _step(current.right, current)
         
        return _step(self.root)


    def insert(self, data):
        """Insert a new node containing 'data' at the appropriate location.
        Return the new node. This method should be similar to BST.insert().
        """
        nodes=KDTNode(data)
        if self.root is None:   
            nodes.axis=0       
            self.root=nodes
        else:
            parent=self.parent_find2(data)
            nodes.axis=(1+parent.axis)%(len(self.root.value))
            if data[parent.axis]<parent.value[parent.axis]:
                parent.left=nodes
                nodes.prev=parent
            else:
                parent.right=nodes
                nodes.prev=parent
    
    def remove(self):
        raise NotImplementedError("Remove is not a function")


# Problem 5
def nearest_neighbor(data_set, target):
    """Use your KDT class to solve the nearest neighbor problem.

    Inputs:
        data_set ((m,k) ndarray): An array of m k-dimensional points.
        target ((k,) ndarray): A k-dimensional point to compare to 'dataset'.

    Returns:
        The point in the tree that is nearest to 'target' ((k,) ndarray).
        The distance from the nearest neighbor to 'target' (float).
    """
    tree=KDT()
    for item in data_set:
        tree.insert(item)
    
    def KDTsearch(current, neighbor, distance):
        """The actual nearest neighbor search algorithm.

        Inputs:
            current (KDTNode): the node to examine.
            neighbor (KDTNode): the current nearest neighbor.
            distance (float): the current minimum distance.

        Returns:
            neighbor (KDTNode): The new nearest neighbor in the tree.
            distance (float): the new minimum distance.
        """
        if current is None:
            return neighbor, distance
        else:
            index=current.axis
            dist=metric(current.value, target)
        if dist<distance:
            neighbor=current.value
            distance=dist
        if target[index]<current.value[index]:
            neighbor, distance= KDTsearch(current.left, neighbor, distance)
            if target[index]+distance >= current.value[index]:
                neighbor, distance=KDTsearch(current.right, neighbor, distance)
        else:
            neighbor, distance=KDTsearch(current.right, neighbor, distance)
            if target[index]-distance<=current.value[index]:
                neighbor, distance=KDTsearch(current.left, neighbor, distance)
        return neighbor, distance
            
    return KDTsearch(tree.root, None, 2**53)

    


# Problem 6
def postal_problem():
    """Use the neighbors module in sklearn to classify the Postal data set
    provided in 'PostalData.npz'. Classify the testpoints with 'n_neighbors'
    as 1, 4, or 10, and with 'weights' as 'uniform' or 'distance'. For each
    trial print a report indicating how the classifier performs in terms of
    percentage of correct classifications. Which combination gives the most
    correct classifications?

    Your function should print a report similar to the following:
    n_neighbors = 1, weights = 'distance':  0.903
    n_neighbors = 1, weights =  'uniform':  0.903       (...and so on.)
    """
    labels, points, testlabels, testpoints=np.load('PostalData.npz').items()
    labels=labels[1]
    points=points[1]
    testpoints=testpoints[1]
    testlabels=testlabels[1]
    for item in [1,4,10]:
        nbrs=neighbors.KNeighborsClassifier(item, 'distance', p=2)
        nbrs.fit(points, labels)
        prediction=nbrs.predict(testpoints)
        average=np.sum(testlabels==prediction)/float(len(testlabels))
        print "Percentage Correct for", item, "neighbor(s) and distance: ", average*100,"%"
        nbrs=neighbors.KNeighborsClassifier(item, 'uniform', p=2)
        nbrs.fit(points, labels)
        prediction=nbrs.predict(testpoints)
        average=np.sum(testlabels==prediction)/float(len(testlabels))
        print "Percentage correct for", item, "neighbor(s) and uniform:", average*100,"%"
    print "Most correct option: 4 neighbors and distance"
    
    
