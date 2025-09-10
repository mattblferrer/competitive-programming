

class Student(Person): # type: ignore
    def __init__(self, firstName, lastName, idNumber, scores):
        Person.__init__(self, firstName, lastName, idNumber) # type: ignore
        self.scores = scores
        
    def calculate(self):
        average = sum(self.scores) / len(self.scores)
        if 90 <= average <= 100:
            return "O"
        elif 80 <= average <= 90:
            return "E"
        elif 70 <= average <= 80:
            return "A"
        elif 55 <= average <= 70:
            return "P"
        elif 40 <= average <= 55:
            return "D"
        else:
            return "T"
        
    #   Class Constructor
    #   
    #   Parameters:
    #   firstName - A string denoting the Person's first name.
    #   lastName - A string denoting the Person's last name.
    #   id - An integer denoting the Person's ID number.
    #   scores - An array of integers denoting the Person's test scores.
    #
    # Write your constructor here
    

    #   Function Name: calculate
    #   Return: A character denoting the grade.
    #
    # Write your function here

