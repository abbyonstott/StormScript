# StormScript v0.2.0 "Banana"
This is the changlog for the December 2018 build of StormScript

# What's New:
* You can change items in lists with `list[item]: "value";`
* Changlog
* Parser and interpreter split up into more files
* Installer now uses the regular cmake file for the project which is located in the release's src directory

# What's Fixed
* Global variables no longer reset for every iteration of a loop
* Fixed issue where installer could find `src/libraries/system/stormscript`

# Other
* Renamed sts.cpp to stormscript.cpp