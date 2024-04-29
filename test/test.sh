#!/bin/bash

# Define the function to process each line
process_line() {
    line="$1"
    line_with_suffix="${line} 20"
    output=$(../phylosopher  "$line_with_suffix")  # Replace 'your_program' with the name of your program
    
    # Check if the output contains the word "died"
    if grep -q "died" <<< "$output"; then
        echo "$output" > "./test_logs/${line}.txt"
    fi
}

# Process each file in the "inputs" folder
for file in ../test/test_input/*; do
    if [ -f "$file" ]; then  # Check if it's a regular file
        echo "Processing file: $file"
        while IFS= read -r line; do
            process_line "$line"
        done < "$file"
    fi
done
