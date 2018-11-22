# StormScript v0.2.0 "Banana"
This is the changelog for the December 2018 build of StormScript

# What's New:
* You can change items in lists with `list[item]: "value";`
* Changelog
* Parser and interpreter split up into more files
* Installer now uses the regular cmake file for the project which is located in the release's src directory
* StormScript library written in StormScript
* [runtests.sh](runtests.sh) now only shows which tests failed
* Outputs folder for expected test results
* [writenewouts.sh](writenewouts.sh) generates results to be put in the outputs folder
* class methods can now be declared. [C++ file](/classes/decmethod.cpp)
* Removed `end;` from being used at the end of scopes

# What's Fixed
* Global variables no longer reset for every iteration of a loop
* Fixed issue where installer could find `src/libraries/system/stormscript`
* Fixed issue where library function couldn't be run in print without args.

# Other
* Renamed sts.cpp to [stormscript.cpp](/core/stormscript.cpp)
* made [interpreter](/interpreter/exec/cpp) easier to use