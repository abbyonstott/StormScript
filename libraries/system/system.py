#!/usr/bin/python
from stormscript import getAll, getVals
import sys
import os

cmds = getAll()

if "setTempVar" in cmds: # appends path for this session
    vals = getVals("setTempVar")
    if "PATH" in vals[0]:
        sys.path.append(vals[0]["PATH"])

if "setVar" in cmds: # adds to bashrc so that path is always appended
    vals = getVals("setVar")
    if "PATH" in vals[0]:
        cmd = "echo 'export PATH="+'$PATH ' + vals[0]['PATH'] + "' >> " + os.path.expanduser("~")+"/.bashrc"
        os.system(cmd)