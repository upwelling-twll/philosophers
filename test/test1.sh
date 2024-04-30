#!/bin/bash
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
process_line() {

    line_raw="$1"
    file="$2"

    # change "turns" variable to change the number of turns philosophers should eat
    turns=20
    line="${line_raw} $turns"

    # Split the line into an array of arguments
    read -r -a args <<< "$line"
    argc=${#args[@]}
    # Check if there are less than 4 arguments
    if (( ${#args[@]} < 4 )); then
        echo "Error: Line '$line' does not contain enough arguments"
        return 1
    fi
    # Call phylosopher with the arguments
    output=$(.././phylosopher "${args[@]}")
    # echo "Output for line '$line': '$output'"
    if  grep -q "died" <<< "$output"  && [[ $file == *"test_input_not_die.txt"* ]]; then
        echo "$output" > "./test_logs/not_die/${line}.txt"
        echo -e "'$line' ${RED}KO${NC} Philosophers must not die"
     # Check if the output does not contain "died" but  the file name does not contain "not die"
    elif ! grep -q "died" <<< "$output" && [[ $file == *"test_input_die.txt"* ]]; then
        echo "$output" > "./test_logs/die/${line}.txt"
        echo -e "'$line' ${RED}KO${NC} Philosophers expected to die"
    else
         echo -e "'$line' ${GREEN}OK${NC}"
    fi
}

for file in ../test/test_input/*; do
  if [ -f "$file" ]; then  # Check if it's a regular file
        echo "Processing file: $file"
        while IFS= read -r line; do
            process_line "$line" "$file" "$3"
        done < "$file"
        fi
done



