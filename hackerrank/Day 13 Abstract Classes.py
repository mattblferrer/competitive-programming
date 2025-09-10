

#Write MyBook class
class MyBook(Book): # type: ignore
    def __init__(self, title, author, price):
        Book.__init__(self, title, author) # type: ignore
        self.price = price
        
    def display(self):
        print(f"Title: {self.title}")
        print(f"Author: {self.author}")
        print(f"Price: {self.price}")

