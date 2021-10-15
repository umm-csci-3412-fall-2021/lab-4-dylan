#!/bin/bash

# Find all files in the supplied directory  and use the type flag of find to filter our results
# for each respective file type. Pipe to wc to count our result. 
echo "There were $(find "$1" -name "*" -type d | wc -l) directories."
echo "There were $(find "$1" -name "*" -type f | wc -l) regular files."
