import sys
import ast

def getAll():
    return ast.literal_eval(sys.argv[1])["command"]
    
def getVals(name):
    return getAll()[name]