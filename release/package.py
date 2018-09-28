#!/usr/bin/python
import json
import os

paths=" "

with open('../files.json') as files:
    data=json.load(files)

for item in data["std"]:
    paths += item["path"]
    paths += " "

print paths