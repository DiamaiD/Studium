"""
Class representing a directed graph as adjacency list

Copyright 2020, University of Freiburg

Philipp Schneider <philipp.schneider@cs.uni-freiburg.de>
"""


class AdjacencyMatrix:
    '''
        represents a weighted graph as adjacency matrix
        where the entry i,j in the matrix corresponds
        to the weight of the edge from node i to node j

        Attributes:
            n - number of nodes (nodes enumerated with IDs 0,...,n-1)
            matrix - an array of arrays containing the matrix entries
    '''

    def __init__(self, n):
        '''
            Constructor

            Parameters:
                n - number of nodes (nodes enumerated with IDs 0,...,n-1)
        '''
        self.n = n
        # create an n times n array representing the adjacency matrix
        self.matrix = [[0 for j in range(n)] for i in range(n)]

    def set_weight(self, i, j, weight):
        '''
            sets the weight of an edge (i, j)

            Parameters:
                i - source node (as integer in {0,...,n-1})
                j - target node (as integer in {0,...,n-1})
                weight - w(i,j)
        '''
        self.matrix[i][j] = weight

    def get_weight(self, i, j):
        '''
            returns the weight of the edge (i,j)

            Parameters:
                i - source node (as integer in {0,...,n-1})
                j - target node (as integer in {0,...,n-1})

            Returns:
                the weight of edge (i,j) or 0 of i==j
        '''
        return self.matrix[i][j]

    def node_size(self):
        '''
            number of nodes of the graph

            Returns:
                number of nodes n
        '''
        return self.n

    def __str__(self):
        '''
            Returns a string representation of the adjacency matrix
        '''
        ret_str = ""
        for i in range(self.node_size()):
            ret_str += "[ "
            for j in range(self.node_size()):
                ret_str += str(self.matrix[i][j]) + " "
            ret_str += "]\n"

        return ret_str
