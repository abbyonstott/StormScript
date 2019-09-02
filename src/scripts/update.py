#!/usr/bin/env python3
# Check if version is latest, and download latest update 
import sys
import os
import json
import urllib.request

cwd = os.getcwd()

version = sys.argv[1]

sizetypes = ["B", "KiB", "MiB", "GiB"] # I hope it never reaches the GiB size, but putting it there to be safe

latest = json.loads(urllib.request.urlopen("https://api.github.com/repos/stormprograms/stormscript/releases/latest").read())
latesttag = latest["tag_name"]
latestsize = latest["assets"][1]["size"]
latestfname = latest["assets"][1]["name"]
latesturl = latest["assets"][1]["browser_download_url"]

if latesttag == version:
	print("You are currently on the latest version")
	exit(0)

print("StormScript version {} is out now!".format(latesttag))

sizetypenum = 0

while len(str(latestsize)) > 3:
	latestsize = str(round(int(latestsize) / 1000))
	sizetypenum += 1

latestsize += " {}".format(sizetypes[sizetypenum])

c = ''
while c not in {"y", "n", "Y", "N"}:
	c = input("Confirm Update from StormScript {0} to {1} [{2}] (y/n) ".format(version, latesttag, latestsize))

if c == 'y':
	print("Starting Update")
	print ("Downloading {}".format(latestfname))

	os.system("curl -LOs {}".format(latesturl))
	os.system("mkdir /tmp/stormscript; mv {} /tmp/stormscript".format(latestfname))
	os.system("cd /tmp/stormscript; tar -xf {0} {1};".format(latestfname, latestfname[:-7]))
	os.system("cd /tmp/stormscript/{}; ./install.sh".format(latestfname[:-7]))
	print(cwd)
	os.system("cd {}; rm -rf /tmp/stormscript".format(cwd))
else:
	print("Canceling Update")

exit(0)