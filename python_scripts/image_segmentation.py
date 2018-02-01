# image_segmentation.py
"""Volume 1A: Image Segmentation.
Alexandra Hurst
Math 345
11/4/16
"""

from matplotlib import pyplot as plt
import numpy as np
from scipy import linalg as la
from scipy import sparse
from scipy.sparse import csgraph
from scipy.sparse import spdiags
from scipy.sparse.linalg import eigsh

# Problem 1: Implement this function.
def laplacian(A):
    '''
    Compute the Laplacian matrix of the adjacency matrix A.
    Inputs:
        A (array): adjacency matrix for undirected weighted graph,
             shape (n,n)
    Returns:
        L (array): Laplacian matrix of A

    '''
    D=np.zeros((len(A),len(A)))
    i=0
    while i<len(A):
        D[i,i]=sum(A[i])
        i+=1
    return D-A

# Problem 2: Implement this function.
def n_components(A,tol=1e-8):
    '''
    Compute the number of connected components in a graph
    and its algebraic connectivity, given its adjacency matrix.
    Inputs:
        A -- adjacency matrix for undirected weighted graph,
             shape (n,n)
        tol -- tolerance value
    Returns:
        n_components -- the number of connected components
        lambda -- the algebraic connectivity
    '''
    A=laplacian(A)
    eigs=la.eigvals(A)
    l=[]
    z=[]
    for value in eigs:
        if value<tol:
            z.append(0)
        else:
            l.append(value)
    if len(z)>1:
        return len(z), 0
    else:
        return 1, min(l)

# Problem 3: Implement this function.
def adjacency(filename="dream.png", radius = 5.0, sigma_I = .02, sigma_d = 3.0):
    '''
    Compute the weighted adjacency matrix for
    the image given the radius. Do all computations with sparse matrices.
    Also, return an array giving the main diagonal of the degree matrix.

    Inputs:
        filename (string): filename of the image for which the adjacency matrix will be calculated
        radius (float): maximum distance where the weight isn't 0
        sigma_I (float): some constant to help define the weight
        sigma_d (float): some constant to help define the weight
    Returns:
        W (sparse array(csc)): the weighted adjacency matrix of img_brightness,
            in sparse form.
        D (array): 1D array representing the main diagonal of the degree matrix.
    '''
    color, brightness=getImage(filename)
    m, n=brightness.shape
    brightness=brightness.flatten()
    W=sparse.lil_matrix((n*m,n*m))
    for thing in xrange(m*n):
        indices, distances=getNeighbors(thing, radius, m,n)
        W[thing,indices]=np.e**(-abs(brightness[thing]-brightness[indices])/(sigma_I)-(distances)/(sigma_d))
    D=W.sum(axis=1)
    return W, D.T

# Problem 4: Implement this function.
def segment(filename="dream.png"):
    '''
    Compute and return the two segments of the image as described in the text.
    Compute L, the laplacian matrix. Then compute D^(-1/2)LD^(-1/2),and find
    the eigenvector corresponding to the second smallest eigenvalue.
    Use this eigenvector to calculate a mask that will be usedto extract
    the segments of the image.
    Inputs:
        filename (string): filename of the image to be segmented
    Returns:
        seg1 (array): an array the same size as img_brightness, but with 0's
                for each pixel not included in the positive
                segment (which corresponds to the positive
                entries of the computed eigenvector)
        seg2 (array): an array the same size as img_brightness, but with 0's
                for each pixel not included in the negative
                segment.
    '''
    color, brightness=getImage(filename)
    o,p=np.shape(brightness)
    A,D=adjacency(filename)
    L=sparse.csgraph.laplacian(A)
    m,n=np.shape(A)
    D_half=np.sqrt(1/D)
    D=spdiags(D, 0,m,m)
    D_half=spdiags(D_half, 0, m, m)
    DLD=D_half.dot(L).dot(D_half)
    val,vec=eigsh(DLD, which="SM")
    second=vec[:,1].T
    second=second.reshape(o,p)
    mask=second>0
    pos=brightness*mask
    neg=brightness*~mask
    displayPosNeg(color, pos, neg)
    return pos, neg
    
    

# Helper function used to convert the image into the correct format.
def getImage(filename='dream.png'):
    '''
    Reads an image and converts the image to a 2-D array of brightness
    values.

    Inputs:
        filename (str): filename of the image to be transformed.
    Returns:
        img_color (array): the image in array form
        img_brightness (array): the image array converted to an array of
            brightness values.
    '''
    img_color = plt.imread(filename)
    img_brightness = (img_color[:,:,0]+img_color[:,:,1]+img_color[:,:,2])/3.0
    return img_color,img_brightness

# Helper function for computing the adjacency matrix of an image
def getNeighbors(index, radius, height, width):
    '''
    Calculate the indices and distances of pixels within radius
    of the pixel at index, where the pixels are in a (height, width) shaped
    array. The returned indices are with respect to the flattened version of the
    array. This is a helper function for adjacency.

    Inputs:
        index (int): denotes the index in the flattened array of the pixel we are
                looking at
        radius (float): radius of the circular region centered at pixel (row, col)
        height, width (int,int): the height and width of the original image, in pixels
    Returns:
        indices (int): a flat array of indices of pixels that are within distance r
                   of the pixel at (row, col)
        distances (int): a flat array giving the respective distances from these
                     pixels to the center pixel.
    '''
    # Find appropriate row, column in unflattened image for flattened index
    row, col = index/width, index%width
    # Cast radius to an int (so we can use arange)
    r = int(radius)
    # Make a square grid of side length 2*r centered at index
    # (This is the sup-norm)
    x = np.arange(max(col - r, 0), min(col + r+1, width))
    y = np.arange(max(row - r, 0), min(row + r+1, height))
    X, Y = np.meshgrid(x, y)
    # Narrows down the desired indices using Euclidean norm
    # (i.e. cutting off corners of square to make circle)
    R = np.sqrt(((X-np.float(col))**2+(Y-np.float(row))**2))
    mask = (R<radius)
    # Return the indices of flattened array and corresponding distances
    return (X[mask] + Y[mask]*width, R[mask])

# Helper function used to display the images.
def displayPosNeg(img_color,pos,neg):
    '''
    Displays the original image along with the positive and negative
    segments of the image.

    Inputs:
        img_color (array): Original image
        pos (array): Positive segment of the original image
        neg (array): Negative segment of the original image
    Returns:
        Plots the original image along with the positive and negative
            segmentations.
    '''
    plt.subplot(131)
    plt.imshow(neg)
    plt.subplot(132)
    plt.imshow(pos)
    plt.subplot(133)
    plt.imshow(img_color)
    plt.show()

if __name__=="__main__":
    segment()