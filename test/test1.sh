#!/bin/bash
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

process_line() {
    line_raw="$1"
    file="$2"

    # Check if a third argument is provided and use it as the number of turns, default to 20
    turns=10
    line="${line_raw} $turns"

    # Split the line into an array of arguments
    read -r -a args <<< "$line"
    argc=${#args[@]}

    # Check if there are less than 4 arguments
    if (( argc < 3 )); then
        echo "Error: Line '$line' does not contain enough arguments"
        return 1
    fi

    # Call phylosopher with the arguments
    output=$(.././phylosopher "${args[@]}")
    
    echo -e "'$line'"

    # Check if the output contains "detected memory leaks"
    if grep -q "detected memory leaks" <<< "$output"; then
        echo -e "${RED}leaks${NC}"
    # Check if the output contains "died" and the file name contains "test_input_not_die.txt"
    elif grep -q "died" <<< "$output" && [[ $file == *"test_input_not_die.txt"* ]]; then
        echo "$output" > "./test_logs/not_die/${line}.txt"
        echo -e "${RED}KO${NC} Philosophers must not die"
    # Check if the output does not contain "died" but the file name contains "test_input_die.txt"
    elif ! grep -q "died" <<< "$output" && [[ $file == *"test_input_die.txt"* ]]; then
        echo "$output" > "./test_logs/die/${line}.txt"
        echo -e "${RED}KO${NC} Philosophers expected to die"
    else
         echo -e "${GREEN}OK${NC}"
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