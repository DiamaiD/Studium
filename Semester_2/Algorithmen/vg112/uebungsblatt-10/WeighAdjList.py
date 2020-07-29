"""
Class representing a weighted graph as adjacency list

Copyright 2020, University of Freiburg

Philipp Schneider <philipp.schneider@cs.uni-freiburg.de>
"""


class WeighAdjList:
    '''
        represents a directed graph as an adjacency list

        Attributes:
            n - number of nodes (nodes enumerated with IDs 0,...,n-1)
            edges - an array of tupels containing all edge-information
    '''

    def __init__(self, n):
        '''
            Constructor

            Parameters:
                n - number of nodes (nodes enumerated with IDs 0,...,n-1)
        '''
        self.n = n
        # create an empty list of lists representing the adjacency array
        self.edges = [[] for i in range(n)]

    def add_edge(self, source, target, weight):
        '''
            adds a weighted edge to the graph

            Parameters:
                source - source node (as integer in {0,...,n-1})
                target - target node (as integer in {0,...,n-1})
                weight - weight of the edge (source, target)
        '''
        self.edges[source].append((target, weight))

    def get_neighbors(self, u):
        '''
            returns all neighbors of u

            Parameters:
                u - node (as integer in {0,...,n-1})

            Returns:
                a list of all pairs (v,w) for which an edge (u,v) exists
        '''
        return self.edges[u]

    def node_size(self):
        '''
            number of nodes of the graph

            Returns:
                number of nodes n
        '''
        return self.n

    def __str__(self):
        '''
            Returns a string representation of the adjacency list
        '''
        ret_str = ""
        for i in range(self.node_size()):
            ret_str += str(i) + ' -> ' + str(self.edges[i]) + '\n'

        return ret_str
