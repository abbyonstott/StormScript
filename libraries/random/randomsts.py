#!/usr/bin/python
from stormscript import getAll, getVals
import random

commands = getAll()

if 'gen' in commands:
    vals = getVals('gen')
    fr = int(vals[0]["from"])
    to = int(vals[1]["to"])
    print random.randrange(fr, to)