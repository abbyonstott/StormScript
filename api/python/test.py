#!/usr/bin/python
from stormscript import getAll, getVals

commands = getAll()

if 'greet' in commands:
    print "Hello!"
if 'ask' in commands:
    values=getVals("ask")
    q = "Hi, "+values[0]["name"]+". How are you? "
    a = raw_input(q)
    if a=="good":
        q = "Awesome! How is "+values[1]["occupation"]+" going? "
        a = raw_input(q)


