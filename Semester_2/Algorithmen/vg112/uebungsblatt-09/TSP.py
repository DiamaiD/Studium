"""
Approximating TSP using fast MST-Algorithms

Copyright 2020, University of Freiburg

Philipp Schneider <philipp.schneider@cs.uni-freiburg.de>
"""

import heapq # noqa
import math # noqa

from AdjacencyMatrix import AdjacencyMatrix # noqa


def compute_tour(am):
    '''
        computes a tour which as an array tour[0],...,tour[n-1]
        containing the nodes {0,...,n-1}) of a graph given as
        Adjacency matrix that has a small sum of edge weights of
        a roundtrip defined as:
        w(tour[0],tour[1]) + ...
                           + w(tour[n-2],tour[n-1])
                           + w(tour[n-1],tour[0])
        the guarantee is that the weight of the computed tour
        is at most twice that of the best possible tour.

        Parameter:
            am - Instance of AdjacencyMatrix

        Returns:
            an array of size n representing the order in which
            nodes are visited (in a roundtrip)
    '''
    s = 0  # start node
    pq = []  # priority queue

    marked = [False for i in range(am.node_size())]

    unmarked = [i for i in range(am.node_size())]

    # initialize priority queue for all nodes without s,
    # set weight of nodes to infinity
    w = []
    w.append(s)
    heapq.heappush(pq, (0, s))
    for i in range(1, am.node_size()):
        heapq.heappush(pq, (math.inf, i))
        w.append(math.inf)
    tour = []

    while pq:
        u = heapq.heappop(pq)
        if not marked[u[1]]:
            marked[u[1]] = True
            unmarked.pop(unmarked.index(u[1]))
            for v in unmarked:
                weight_u_to_v = am.get_weight(u[1], v)
                if weight_u_to_v < w[v]:
                    w[v] = weight_u_to_v
                    heapq.heappush(pq, (weight_u_to_v, v))
            tour.append(u[1])

    return tour


def tour_weight(am, tour):
    '''
        computes the sum of edge weigths when all nodes of a
        tour are visited as a roundtrip

        Parameter:
            am - Instance of AdjacencyMatrix of size n
            tour - permuation of {0,...,n-1}

        Returns:
            the following value rounded to two decimal places
            w(tour[0],tour[1]) + ...
                           + w(tour[n-1],tour[n-1])
                           + w(tour[n-1],tour[0])
    '''
    n = am.node_size()
    weight_sum = 0
    for i in range(n-1):
        weight_sum += am.get_weight(tour[i], tour[i + 1])
    weight_sum += am.get_weight(tour[n-1], tour[0])
    return round(weight_sum, 2)


def read_graph_from_file(filename):
    '''
        reads a complete weighted graph from a file (that must
        be loated in same folder) and creates an adjacency matrix
        from it

        Parameter:
            filename - name of file

        Returns:
            instance of AdjacencyMatrix representing the file
    '''
    with open(filename) as input:
        lines = input.read().splitlines()
        # first line contains the number of nodes
        am = AdjacencyMatrix(int(lines[0]))

        # other lines contain edges seperated by a whitespace
        for i in range(0, len(lines) - 1):
            for j in range(am.node_size()):
                entries = lines[i + 1].split(' ')
                am.set_weight(i, j, float(entries[j]))

    return am
