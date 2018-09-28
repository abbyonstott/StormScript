#!/usr/bin/python
import json
import os

paths=" "

with open('../files.json') as files:
    data=json.load(files)

for item in data["std"]:
    paths += item["path"]
    paths += " "

cmd="g++"+paths+"-o ../release/linux-x86/bin/sts && sudo cp ../release/linux-x86/bin/sts /usr/bin -f && sts example.sts"

os.system(cmd)