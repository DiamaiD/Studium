
class TreeElement:
    '''
        represents a node in binary tree

        Attributes:
            key - the value according to which a binary search tree is sorted
            parent - TreeElement representing the parent in the tree
            left - TreeElement representing the left child in the tree
            right - TreeElement representing the right child in the tree
    '''

    def __init__(self, key, parent=None, left=None, right=None):

        self.key = key
        self.parent = parent
        self.left = left
        self.right = right
    """def __repr__(self):
        return str((self.key, self.parent, self.left, self.right))
    """


class BST:
    '''
        class that represents a binary search tree

        Attributes:
            root - a TreeElement that represents the root of the tree
    '''

    def __init__(self, root=None):

        self.root = root

    def insert(self, x):
        '''
            inserts a given key into the binary search tree

            Parameters:
                x - comparable key to insert
        Doctests:

        >>> a = BST()
        >>> k = TreeElement(None,None,None,None)
        >>> a.root ==k.key
        True

        >>> b = BST()
        >>> b.insert(5)
        >>> k = TreeElement(5)
        >>> k.key == b.root.key
        True

        >>> c = BST(6)
        >>> k = TreeElement(5, 5, 4, 6)
        >>> c.root==k.right
        True

        >>> bst=BST()
        >>> bst.insert(5)
        >>> bst.insert(4)
        >>> bst.insert(3)
        >>> bst.insert(6)
        >>> bst.root.parent==None
        True
        >>> c = bst.root.left
        >>> c.key==4
        True
        >>> d= c.left
        >>> d.key==3
        True
        >>> right=bst.root.right
        >>> right.key==6
        True
        '''
        if self.root is None:
            self.root = TreeElement(x)
        else:
            element = self.root
            while True:
                if x < element.key:
                    if element.left is None:
                        element.left = TreeElement(x, element)
                        break
                    else:
                        element = element.left
                        continue
                else:
                    if element.right is None:
                        element.right = TreeElement(x, element)
                        break
                    else:
                        element = element.right
                        continue

    def getrange(self, xmin, xmax):
        '''
            returns all keys x with xmin <= x < xmax.

            Implementation hints: May use either additional
            parameters or call a recursive subfunction with
            additional parameters.

            Parameters:
                xmin - lower bound (including)
                xmax - upper bound (excluding)

            Returns:
                List of keys with xmin <= x < xmax

            Doctests:
            >>> testbst = BST()
            >>> for i in range(100):
            ...     testbst.insert(i)
            >>> testbst.getrange(0, 20)
            [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, \
17, 18, 19]
            >>> bs = BST()
            >>> bs.getrange(0, 0)
            []
            >>> testbst.getrange(0, 0)
            []
            >>> testbst.getrange(100, 1000)
            []
        '''
        ranges = []
        if self.root is None:
            return ranges
        elements = [self.root]
        while elements:
            if elements[0].left:
                elements.append(elements[0].left)
            if elements[0].right:
                elements.append(elements[0].right)
            if elements[0].key >= xmin and elements[0].key < xmax:
                ranges.append(elements[0].key)
            elements.pop(0)
        return ranges

    def insert_from_file(self, filename='input.txt'):
        '''
            opens a file and inserts the content into the tree

            Parameters:
                filename - filename of file, must be in same filder

            Doctests:
            >>> teststrings = BST()
            >>> teststrings.insert_from_file()
            >>> teststrings.getrange("qw", "qx")
            ['qwxpyjl', 'qwyiwh', 'qwel', 'qwxrm', 'qwivkay', 'qwdjbcsm', \
'qwgzykg', 'qwohudf', 'qwb', 'qwgconj', 'qwo', 'qwqrn', 'qwmwwi', 'qwpoh', \
'qwtq', 'qwlybcn', 'qwrmxd']
        '''

        with open(filename) as input:
            words = input.read().splitlines()
            for word in words:
                self.insert(word)


def test_inser_from_file():
    teststrings = BST()
    teststrings.insert_from_file()
    assert teststrings.getrange("qw", "qx"), ['qwxpyjl', 'qwyiwh', 'qwel',
                                              'qwxrm', 'qwivkay', 'qwdjbcsm',
                                              'qwgzykg', 'qwohudf', 'qwb',
                                              'qwgconj', 'qwo', 'qwqrn',
                                              'qwmwwi', 'qwpoh', 'qwtq',
                                              'qwlybcn', 'qwrmxd']
