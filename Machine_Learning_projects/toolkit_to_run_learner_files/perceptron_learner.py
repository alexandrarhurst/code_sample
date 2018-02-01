#perceptron.py
#Alexandra Hurst

from __future__ import (absolute_import, division, print_function, unicode_literals)
from toolkit.supervised_learner import SupervisedLearner
import numpy as np
from scipy import linalg as la


def weight(x):
    return np.log(np.abs(x))

weight=np.vectorize(weight)

class PerceptronLearner(SupervisedLearner):

    labels=[]

    def __init__(self):
        self.w=[]
        self.c=.1
        self.num_epochs=1000


    def train(self, features, labels):
        f=lambda x: 1 if x>0 else 0
        self.w=np.zeros(features.cols+1)
        data=np.squeeze(np.asarray(features.data))
        data=np.hstack((data,np.ones((features.rows,1))))
        #print(labels.attr_names)
        #print(features.attr_names)
        slowing=0
        for i in range(self.num_epochs):
            #print(i)
            old_w=self.w
            t=np.squeeze(np.asarray(labels.data))
            #print(t)
            for j in range(features.rows):
                delta_w=self.c*(t[j]-f(net))*(data[j])
                self.w=self.w+delta_w
            if la.norm(old_w-self.w)/features.rows<.001:
                slowing+=1
            else:
                slowing=0
            if slowing==6:
                print(i)
                break
        return self.w

    def test(self, features, weights):
        f=lambda x: 1 if x>0 else 0
        net=np.dot(features,weights)
        return f(net)

    def predict(self, features, labels):
        features.append(1)#bias
        del labels[:]
        labels+=[self.test(features,self.w)]
