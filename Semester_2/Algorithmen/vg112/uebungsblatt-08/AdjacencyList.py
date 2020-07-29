"""
Class representing a directed graph as adjacency list

Copyright 2020, University of Freiburg

Philipp Schneider <philipp.schneider@cs.uni-freiburg.de>
"""


class AdjacencyList:
    '''
        represents a directed graph as an adjacency list

        Attributes:
            n - number of nodes (nodes enumerated with IDs 1,...,n-1)
            edges - an array of lists containing all edge-infromation
    '''

    def __init__(self, n):
        '''
            Constructor

            Parameters:
                n - number of nodes (nodes enumerated with IDs 1,...,n-1)
        '''
        self.n = n
        # create an empty list of lists representing the adjacency array
        self.edges = [[] for i in range(n)]

    def add_edge(self, source, target):
        '''
            adds an edge (source, target) to the graph

            Parameters:
                source - source node (as integer in {0,...,n-1})
                target - target node (as integer in {0,...,n-1})
        '''
        self.edges[source].append(target)

    def get_neighbors(self, u):
        '''
            returns all neighbors of u

            Parameters:
                u - node (as integer in {0,...,n-1})

            Returns:
                a list of all nodes v for which an edge (u,v) exists
        '''
        return self.edges[u]

    def node_size(self):
        '''
            number of nodes of the graph

            Returns:
                number of nodes n
        '''
        return self.n

    def get_roots(self):
        '''
            a root is a node with in-degree zero

            Returns:
                list of roots
        '''
        n = self.node_size()
        aux = [1 for i in range(n)]
        for u in range(n):
            # if v is in u's adjacency list, it is not a root
            for v in self.get_neighbors(u):
                aux[v] = 0
        roots = []
        for u in range(n):
            if aux[u] == 1:
                roots.append(u)
        return roots

    def __str__(self):
        '''
            Returns a string representation of the adjacency list
        '''
        ret_str = ""
        for i in range(self.node_size()):
            ret_str += str(i) + ' -> ' + str(self.edges[i]) + '\n'

        return ret_str
