"""
Finding a path in a Maze

Copyright 2020, University of Freiburg

Philipp Schneider <philipp.schneider@cs.uni-freiburg.de>
"""

import math # noqa
import heapq # noqa

from WeighAdjList import WeighAdjList # noqa


def compute_path(adj_lst, s, t):
    '''
        computes a path from s to t through a maze

        Parameter:
            adj_lst - WeighAdjList representing the maze
            s - source node
            t - target node

        Returns:
            a sequence of nodes representing the shortest
            path from s to t
    '''


def read_graph_from_file(filename):
    '''
        reads a depency graph from a file (that must be loated
        in same folder) and creates an adjacency list from it

        Parameter:
            filename - name of file

        Returns:
            instance of WeighAdjList representing the file
    '''
    with open(filename) as input:
        lines = input.read().splitlines()
        # first line contains the number of nodes
        adj_lst = WeighAdjList(int(lines[0]))

        # other lines contain edge information seperated by a whitespace
        for i in range(1, len(lines)):
            line = lines[i].split(' ')
            source = int(line[0])
            target = int(line[1])
            weight = int(line[2])
            adj_lst.add_edge(source, target, weight)

    return adj_lst


def vizualize_path(adj_lst, path):
    '''
        gives a string representation of a maze in the
        required format with the path in it

        Parameter:
            adj_lst - WeighAdjList representing the maze
            path - list of nodes

        Returns:
            a string representation
    '''
    n = int(math.sqrt(adj_lst.node_size()))

    # upper delimitation
    maze_str = (2*n+1)*'@@@' + '\n'

    # iterate vertically
    for i in range(2*n-1):
        # left delimitation
        maze_str += '@@@'

        # uneven lines may have vertical openings
        if i % 2 == 1:
            # iterate horizontally
            for j in range(2*n-1):
                if j % 2 == 1:
                    maze_str += '@@@'
                else:
                    # get nodes below and above
                    u = (i // 2) * n + (j // 2)
                    v = u + n
                    if (v, 1) in adj_lst.get_neighbors(u):
                        maze_str += '   '  # downwards open
                    else:
                        maze_str += '@@@'  # downwards closed

        # even lines may have nodes or horizontal openings
        else:
            # iterate horizontally
            for j in range(2*n-1):
                if j % 2 == 1:
                    # get left and right node
                    u = (i // 2) * n + (j // 2)
                    v = u + 1
                    if (v, 2) in adj_lst.get_neighbors(u):
                        maze_str += '   '
                    else:
                        maze_str += '@@@'
                else:
                    u = (i // 2) * n + (j // 2)
                    if u in path:
                        maze_str += ' X '
                    else:
                        maze_str += '   '
        # right delimitation
        maze_str += '@@@\n'

    # lower delimitation
    maze_str += (2*n+1)*'@@@'

    return maze_str

test = read_graph_from_file("maze.txt")

print(vizualize_path(test, [i for i in range(888)]))
