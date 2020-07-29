"""
Functions for scheduling jobs on machines

Copyright 2020, University of Freiburg

Philipp Schneider <philipp.schneider@cs.uni-freiburg.de>
Philipp Bamberger <philipp.bamberger@cs.uni-freiburg.de>
"""

import queue

from AdjacencyList import AdjacencyList


def dispatch_sequence(al):
    '''
        computes a valid sequence in which jobs can be
        dispatched to a single machine without violating
        the depency graph given as parameter

        Parameter:
            al - depency graph as instance of AdjacencyList

        Returns:
            a list representing a valid sequence of IDs for
            computing the respective jobs on a single machine
            or None if such a sequence does not exist

        Unit Tests (leave this one, but add more):
            >>> from AdjacencyList import AdjacencyList
            >>> cycle = AdjacencyList(6)
            >>> cycle.add_edge(0,1); cycle.add_edge(1,2)
            >>> cycle.add_edge(2,3); cycle.add_edge(3,0)
            >>> cycle.add_edge(4,5);
            >>> dispatch_sequence(cycle) is None
            True
    '''
    roots = al.get_roots()
    q = queue.Queue()
    for i in roots:
        q.put(i)
    result = []
    # 0 for white, 1 for grey, 2 for black
    # initialize with white
    colors = [0 for i in range(al.node_size())]

    while not q.empty():
        n = q.get()
        result.append(n)
        # colors[n] = 2
        for j in al.get_neighbors(n):
            # if colors[j] == 2:
            #     return None
            if colors[j] == 0:
                q.put(j)
                colors[j] = 1

    if len(result) < al.node_size():
        return None

    return result


def earliest_computation(al):
    '''
        for each job, gives the earliest point in time it can
        be completed with respect to the dependency graph

        Parameter:
            al - depency graph as instance of AdjacencyList

        Returns:
            a list of size n containing at position i the
            earliest point in time it can be computed
    '''
    result = [0 for i in range(al.n)]
    count = 0
    ques = al.get_roots()
    explored = []
    while ques:
        for i in ques:
            result[i] = count
            explored += al.get_neighbors(i)
        count += 1
        ques = explored
        explored = []
    return result


def read_graph_from_file(filename):
    '''
        reads a depency graph from a file (that must be loated
        in same folder) and creates an adjacency list from it

        Parameter:
            filename - name of file

        Returns:
            instance of AdjacencyList representing the file
    '''
    with open(filename) as input:
        lines = input.read().splitlines()
        # first line contains the number of nodes
        al = AdjacencyList(int(lines[0]))

        # other lines contain edges seperated by a whitespace
        for i in range(1, len(lines)):
            source = int(lines[i].split(' ')[0])
            target = int(lines[i].split(' ')[1])
            al.add_edge(source, target)

    return al
