import sys
from Memory.Memory import freeMemory

class Logger:
    totalLogString = ""
    
    maxSize = 0
    
    def __init__(self):
        self.maxSize = freeMemory() * 0.1
    
    def logString(self, string):
        #check if string array doest get bigger then 10% 
        if (sys.getsizeof(self.totalLogString)+sys.getsizeof(string) < self.maxSize):
            if self.totalLogString != "":
                self.totalLogString += "#"
            
            self.totalLogString += string
            
    