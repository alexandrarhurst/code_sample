# linked_lists.py
"""Volume II Lab 4: Data Structures 1 (Linked Lists)
Alexandra Hurst
Math 321
9/22/16
"""


# Problem 1
class Node(object):
    """A basic node class for storing data."""
    def __init__(self, data):
        if type(data) is not int and type(data) is not long and type(data) is not float and type(data) is not str:
            raise TypeError("Enter a compatable data type")
            """Store 'data' in the 'value' attribute."""
        else:
            self.value = data


class LinkedListNode(Node):
    """A node class for doubly linked lists. Inherits from the 'Node' class.
    Contains references to the next and previous nodes in the linked list.
    """
    def __init__(self, data):
        """Store 'data' in the 'value' attribute and initialize
        attributes for the next and previous nodes in the list.
        """
        Node.__init__(self, data)       # Use inheritance to set self.value.
        self.next = None
        self.prev = None


class LinkedList(object):
    """Doubly linked list data structure class.

    Attributes:
        head (LinkedListNode): the first node in the list.
        tail (LinkedListNode): the last node in the list.
    """
    def __init__(self):
        """Initialize the 'head' and 'tail' attributes by setting
        them to 'None', since the list is empty initially.
        """
        self.head = None
        self.tail = None

    def append(self, data):
        """Append a new node containing 'data' to the end of the list."""
        # Create a new node to store the input data.
        new_node = LinkedListNode(data)
        if self.head is None:
            # If the list is empty, assign the head and tail attributes to
            # new_node, since it becomes the first and last node in the list.
            self.head = new_node
            self.tail = new_node
        else:
            # If the list is not empty, place new_node after the tail.
            self.tail.next = new_node               # tail --> new_node
            new_node.prev = self.tail               # tail <-- new_node
            # Now the last node in the list is new_node, so reassign the tail.
            self.tail = new_node

    # Problem 2
    def find(self, data):
        """Return the first node in the list containing 'data'.
        If no such node exists, raise a ValueError.

        Examples:
            >>> l = LinkedList()
            >>> for i in [1,3,5,7,9]:
            ...     l.append(i)
            ...
            >>> node = l.find(5)
            >>> node.value
            5
            >>> l.find(10)
            ValueError: <message>
        """
        current=self.head
        found=False
        while current != None and not found:
            if current.value==data:
                found=True
            else:
                current=current.next
        if found==False:
            raise ValueError("Object not found")
        return current
        

    # Problem 3
    def __len__(self):
        """Return the number of nodes in the list.

        Examples:
            >>> l = LinkedList()
            >>> for i in [1,3,5]:
            ...     l.append(i)
            ...
            >>> len(l)
            3
            >>> l.append(7)
            >>> len(l)
            4
        """
        current=self.head
        i=0
        while current !=None:
            i+=1
            current=current.next
        return i
        

    # Problem 3
    def __str__(self):
        """String representation: the same as a standard Python list.

        Examples:
            >>> l1 = LinkedList()   |   >>> l2 = LinkedList()
            >>> for i in [1,3,5]:   |   >>> for i in ['a','b',"c"]:
            ...     l1.append(i)    |   ...     l2.append(i)
            ...                     |   ...
            >>> print(l1)           |   >>> print(l2)
            [1, 3, 5]               |   ['a', 'b', 'c']
        """
        l='['
        current=self.head
        if self.head==None:
            return "[]"
        else:
            if type(self.head.value) is str:
                while current.next != None:
                    l=l+'\''+str(current.value)+'\''+', '
                    current=current.next
                return l+'\''+str(current.value)+'\''+']'
            else:
                while current.next !=None:
                    l=l+str(current.value)+', '
                    current=current.next
                return l+str(current.value)+']'
        

    # Problem 4
    def remove(self, data):
        """Remove the first node in the list containing 'data'. Return nothing.

        Raises:
            ValueError: if the list is empty, or does not contain 'data'.

        Examples:
            >>> print(l1)       |   >>> print(l2)
            [1, 3, 5, 7, 9]     |   [2, 4, 6, 8]
            >>> l1.remove(5)    |   >>> l2.remove(10)
            >>> l1.remove(1)    |   ValueError: <message>
            >>> l1.remove(9)    |   >>> l3 = LinkedList()
            >>> print(l1)       |   >>> l3.remove(10)
            [3, 7]              |   ValueError: <message>
        """
        target=self.find(data)
        if self.head==target:
            self.head=self.head.next
        elif self.tail==target:
            self.tail=self.tail.prev
            target.prev.next=None
        else:
            target.prev.next=target.prev.next.next
            target.next.prev=target.next.prev.prev
                    
            

    # Problem 5
    def insert(self, data, place):
        """Insert a node containing 'data' immediately before the first node
        in the list containing 'place'. Return nothing.

        Raises:
            ValueError: if the list is empty, or does not contain 'place'.

        Examples:
            >>> print(l1)           |   >>> print(l1)
            [1, 3, 7]               |   [1, 3, 5, 7, 7]
            >>> l1.insert(7,7)      |   >>> l1.insert(3, 2)
            >>> print(l1)           |   ValueError: <message>
            [1, 3, 7, 7]            |
            >>> l1.insert(5,7)      |   >>> l2 = LinkedList()
            >>> print(l1)           |   >>> l2.insert(10,10)
            [1, 3, 5, 7, 7]         |   ValueError: <message>
        """
        new_node=LinkedListNode(data)
        if place==0:
            new_node.next=self.head
            self.head=new_node
        elif place==len(self):
            self.append(data)
        else:
            current=self.head
            previous=None
            while current!= self.find(place):
                previous=current
                current=current.next
            previous.next=new_node
            new_node.next=current
            new_node.prev=previous
            
            
            
            
            
        

# Problem 6: Write a Deque class.
class Deque(LinkedList):

    def __init__(self):
        LinkedList.__init__(self)
        
        
    def appendleft(self, data):
        new_node=LinkedListNode(data)
        self.insert(data, 0)
        
    def popleft(self):
        popcorn=self.head.value
        self.remove(popcorn)
        
    def pop(self):
        if self.tail==None:
            self.remove(self.head.value)
        else:
            popcorn=self.tail.value
            self.remove(popcorn)
        
    def remove(*args, **kwargs):
        raise NotImplementedError("Use pop() or popleft() for removal")
        
    def insert(*args, **kwargs):
        raise NotImplementedError("Use append() or appendleft() for insertion")
        
        
        


# Problem 7
def prob7(infile, outfile):
    """Reverse the file 'infile' by line and write the results to 'outfile'."""
    l=[]
    with open(infile, 'r') as myfile:
        l=myfile.readlines()
    i=0    
    with open(outfile, 'w') as out:
        while i<len(l):
            out.write(l[len(l)-i-1])
            i+=1
    
