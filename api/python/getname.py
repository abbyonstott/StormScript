from sys import argv
import re
import os
x = ""
with open("reader.cc", 'r') as f:
    x = f.read()
    x=x.replace("test", argv[1])
with open("reader.cc", 'w') as f:
    f.write(x)