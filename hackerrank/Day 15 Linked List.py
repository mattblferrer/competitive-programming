def insert(self,head,data): 
    node = Node(data) # type: ignore
    if head is None:
        return node
    h = head
    while h.next is not None:
        h = h.next
    h.next = node
    return head
        
#Complete this method

