### Diffindo Command Line Tool 
#### In one command, this tool separates an xcode project based on user comments, creates two new xcode projects with each version, and opens side-by-side LLDB debuggers to   simultaneously compare VersionA with VersionB

![diffindo logo](https://44.media.tumblr.com/tumblr_lpiavfuhkK1qbrxslo1_r1_500.gif)

##### BASIC NOTES:
1. two test cases: test folder contains all that you need to run the command, test2 folder contains the output along with the original command. If you would like to recreate test2, delete VersionA.xcodeproj, VersionB.xcodeproj, dir_A, and dir_B
2. See diffindo_gen.sh for the source code of the tool
3. XCODE is required
4. Homebrew is required
5. This project uses XcodeGen (https://github.com/yonaskolb/XcodeGen/tree/master), which will be installed automatically if you don't already have it

##### COMMAND LINE ARGUMENTS: example for test) ./diffindo_gen.sh -n 'test' -p '/Users/ethankahana/Desktop/Diffindo/test' -f 'main.cpp' -s 2 
###### See test and test2 folders for examples 
1. name of original xcodeproj (REQUIRED)
2. path to original xcode project, not including the name of the project (REQUIRED)
3. file that you want to split (REQUIRED)
4. Number of Version A/B regions that are in your xcode project (OPTIONAL if only 1 region, REQUIRED if multiple regions).

##### TO READ IN FILES: see test2 for an example and follow this basic format
