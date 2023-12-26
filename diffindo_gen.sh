#!/bin/bash

# GENERAL VERSION (for all computers, takes arguments)
# VERSION 1 of diffindo command line tool (names after the Harry Potter splitting spell)
# README: This tool takes in one .xcodeproj file that has user-inputted markers to specify code from VersionA and VersionB (code without these markers is common in both versions), splits the code into two new xcodeproj files with each respective version, and then opens up two LLDB terminal windows for side-by-side debugging capabilities. Have fun!
# Developer: Ethan Kahana

# the sections command is only necessary if there are more than 1 version A/B regions. Otherwise, it defaults to 1
sections=1

# arguments
while getopts n:f:p:s: flag
do
    case "${flag}" in
        n) name=${OPTARG};;
        p) path=${OPTARG};;
        f) file=${OPTARG};;
        s) sections=${OPTARG};;
    esac
done
echo "name of original project: $name";
echo "Path Directory (to xcode proj): $path";
echo "File that you want to edit (with type): $file";
echo "Choose the number of Version A, Version B Sections (default is 1)": $sections

# Paths
echo "Running Tool"
# try this for multiple versions
original_file="$path/$name/$file"
version_a_file="$path/$name/version_a.cpp"
version_b_file="$path/$name/version_b.cpp"

mkdir $path/dir_A
mkdir $path/dir_B
# add common code before to both files
sed -n '1,/\/\/ Version A1 Start/p' "$original_file" | sed '$d' > "$path/dir_A/$file"
sed -n '1,/\/\/ Version A1 Start/p' "$original_file" | sed '$d' > "$path/dir_B/$file"
for i in $(seq 1 $sections);
    do
    # add first section A code
    # Extract Version A and combine with common code
    echo "Version A$i Start"
    sed -n "/\/\/ Version A$i Start/,/\/\/ Version A$i End/p" $original_file >> "$path/dir_A/$file"
    # extract middle code and add
    # Extract common code between "//Version A End" and "//Version B Start"
    sed -n "/\/\/ Version A$i End/,/\/\/ Version B$i Start/p" $original_file | sed "/\/\/ Version A$i End/d; /\/\/ Version B$i Start/d" >> "$path/dir_A/$file"
    sed -n "/\/\/ Version A$i End/,/\/\/ Version B$i Start/p" $original_file | sed "/\/\/ Version A$i End/d; /\/\/ Version B$i Start/d" >> "$path/dir_B/$file"
    # Extract Version B and combine with common code
    sed -n "/\/\/ Version B$i Start/,/\/\/ Version B$i End/p" $original_file > $version_b_file
    cat $version_b_file >> "$path/dir_B/$file"
    
    # check if this is the last section
    if [ $i -lt $sections ]; then
        next_section=$((i + 1))
        # Extract common code between current B end and next A start, then append
        sed -n "/\/\/ Version B$i End/,/\/\/ Version A$next_section Start/p" "$original_file" | sed "/\/\/ Version B$i End/d; /\/\/ Version A$next_section Start/d" >> "$path/dir_A/$file"
        sed -n "/\/\/ Version B$i End/,/\/\/ Version A$next_section Start/p" "$original_file" | sed "/\/\/ Version B$i End/d; /\/\/ Version A$next_section Start/d" >> "$path/dir_B/$file"
    fi
done
# Now get the last iteration of B$i End to the end of the file
awk "/\/\/ Version B$sections End/ {flag=1} flag" $original_file >> "$path/dir_A/$file"
awk "/\/\/ Version B$sections End/ {flag=1} flag" $original_file >> "$path/dir_B/$file"
rm $version_a_file $version_b_file
# end of try block/region

# Function to copy files
copy_files() {
    local source_dir=$1
    local dest_dir=$2
    local exclude_file=$3

    # Find and copy files, excluding the specified file and any .tar.gz files
    # Only copy if the file does not exist in the destination directory
    # fixes overwriting issue
    find "$source_dir" -type f \( ! -name "$exclude_file" ! -name "*.tar.gz" \) -exec bash -c 'cp -n "$1" "$2"' _ {} "$dest_dir" \;
}

# Copy files to VersionA and VersionB directories
echo "Copying over all original files excpet for the one changed"
copy_files "$path/$name/" "$path/dir_A" "$original_file"
copy_files "$path/$name/" "$path/dir_B" "$original_file"


# set up yml files
# Content you want to add
# Set up YAML content
new_content_a="name: VersionA\n"
new_content_a+="targets:\n"
new_content_a+="  VersionA:\n"
new_content_a+="    type: tool\n"
new_content_a+="    platform: macOS\n"
new_content_a+="    sources:\n"
new_content_a+="      - path: '$path/dir_A/'\n"


# For format_a.yml
echo -e "$new_content_a" > $path/format_a.yml

# For version_b.yml
new_content_b="name: VersionB\n"
new_content_b+="targets:\n"
new_content_b+="  VersionB:\n"
new_content_b+="    type: tool\n"
new_content_b+="    platform: macOS\n"
new_content_b+="    sources:\n"
new_content_b+="      - path: '$path/dir_B/'\n"  # Path relative to the YAML file


# For format_b.yml
echo -e "$new_content_b" > $path/format_b.yml

# may need to install XcodeGen
# Check for dependencies, like xcodegen
echo "Checking dependencies (xcodegen and homebrew)"
# Check for dependencies, like xcodegen
if command -v xcodegen &> /dev/null; then
    echo "xcodegen is already installed."
else
    echo "xcodegen is required but not installed. Attempting to install xcodegen..."
    # Assuming installation via Homebrew on macOS
    if command -v brew &> /dev/null; then
        echo "Installing xcodegen using Homebrew..."
        brew install xcodegen
        if [ $? -ne 0 ]; then
            echo "Failed to install xcodegen. Please install it manually."
            exit 1
        fi
    else
        echo "Error: Homebrew is not installed. Please install Homebrew and then xcodegen."
        exit 1
    fi
fi


echo "xcodegen"
xcodegen --spec $path/format_a.yml
xcodegen --spec $path/format_b.yml

# Xcode project details
xcode_project_name_A="VersionA.xcodeproj"
scheme_name_A="VersionA" # Usually the scheme name is the same as the project name
executable_name_A="VersionA" # The executable name often matches the project name

xcode_project_name_B="VersionB.xcodeproj"
scheme_name_B="VersionB" # Usually the scheme name is the same as the project name
executable_name_B="VersionB" # The executable name often matches the project name

# Build directory for Xcode
build_dir="$path/DerivedData/"

# May need to run these two lines (see about this later after other ppl test it)
# sudo xcode-select -s /Applications/Xcode.app/Contents/Developer
# xcode-select -p

# Compile the extracted versions
echo "Building Version A..."
xcodebuild -project "$path/$xcode_project_name_A" \
           -scheme "$scheme_name_A" \
           -configuration Debug \
           -derivedDataPath "$build_dir" \

echo "Building Version B..."
xcodebuild -project "$path/$xcode_project_name_B" \
           -scheme "$scheme_name_B" \
           -configuration Debug \
           -derivedDataPath "$build_dir" \

# Executable paths
executable_a="$build_dir/Build/Products/Debug/$executable_name_A"
executable_b="$build_dir/Build/Products/Debug/$executable_name_B"

# Check if the executables were built
if [ ! -f "$executable_a" ]; then
    echo "Error: Failed to build Version A"
    exit 1
fi

if [ ! -f "$executable_b" ]; then
    echo "Error: Failed to build Version B"
    exit 1
fi


# Launch LLDB sessions for each version in new Terminal windows
osascript -e 'tell app "Terminal" to do script "lldb '"$executable_a"'"' &
osascript -e 'tell app "Terminal" to do script "lldb '"$executable_b"'"'

echo "Launched LLDB sessions for both versions."

# Cleanup (KEEP THE diffindo.sh and test.xcodeproj files!!!)
rm $path/format_a.yml $path/format_b.yml


