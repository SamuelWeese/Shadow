#!/bin/bash

set -u

for file in *.c; do
    base_name="${file%.c}"
    
    if [[ $base_name =~ ^[0-9]+$ ]]; then
        echo "Processing file: $file"

        file_name="$base_name.out"

        gcc "$file" -o $file_name
        echo "BUILT $file TO $file_name"
        
        strace -o "$base_name.log" "./$file_name"
        echo "Ran $file_name with strace, log saved to $base_name.log"
        rm $file_name
    else
        echo "Skipping non-numeric file: $file"
    fi

done

echo "All files traced."
