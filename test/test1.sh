#!/bin/bash
GREEN='\033[0;32m'
RED='\033[0;31m'  # ANSI escape code for red color
NC='\033[0m'      # ANSI escape code for reset (to default color)
# Define the function to process each line
process_line() {
    # line="$1"
    line_raw="$1"
    file="$2"
    line="${line_raw} 20"
    # Split the line into an array of arguments
    read -r -a args <<< "$line"
    # Check if there are less than 5 arguments
    if (( ${#args[@]} < 3 )); then
        echo "Error: Line '$line' does not contain enough arguments"
        return 1
    fi
    # Call phylosopher with the arguments
    output=$(.././phylosopher "${args[@]}")
    # echo "Output for line '$line': '$output'"
    if  grep -q "died" <<< "$output"  && [[ $file == *"not die"* ]]; then
        echo "$output" > "./test_logs/not_die/${line}.txt"
        echo -e "'$line' ${RED}KO${NC} Philosophers must not die"
     # Check if the output does not contain "died" but the file name does not contain "not die"
    elif ! grep -q "died" <<< "$output" && [[ $file == *"test_input_die"* ]]; then
        echo "$output" > "./test_logs/die/${line}.txt"
        echo -e "'$line' ${RED}KO${NC} Philosophers expected to die"
    else
         echo -e "'$line' ${GREEN}OK${NC}"
    fi
}

# # Call the process_line function with a specific input line
#  process_line " 3 596 200 200"
# file="./test_input/test_input_die.c";
for file in ../test/test_input/*; do
  if [ -f "$file" ]; then  # Check if it's a regular file
        echo "Processing file: $file"
        while IFS= read -r line; do
            process_line "$line" "$file"
        done < "$file"
        fi
done



