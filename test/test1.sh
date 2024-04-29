#!/bin/bash

# Define the function to process each line
process_line() {
    line_raw="$1"
    line="${line_raw} 10"
    # Split the line into an array of arguments
    read -r -a args <<< "$line"
    # Check if there are less than 5 arguments
    if (( ${#args[@]} < 5 )); then
        echo "Error: Line '$line' does not contain enough arguments"
        return 1
    fi
    # Call phylosopher with the arguments
    output=$(.././phylosopher "${args[@]}")
    # echo "Output for line '$line': '$output'"
    if grep -q "died" <<< "$output"; then
        # echo "$output" > "./test_logs/${line}.txt"
        echo "$output"
    fi
}

# Call the process_line function with a specific input line
for file in ../test/test_input/*; do
    if [ -f "$file" ]; then  # Check if it's a regular file
        echo "Processing file: $file"
        while IFS= read -r line; do
            process_line "$line"
        done < "$file"
    fi
done



