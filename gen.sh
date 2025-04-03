#!/bin/bash

echo "$1"
echo "##start"
for ((i = 1; i <= $2 - 1; i++)); do
    echo "$i $((i + 2)) $3"
done
echo "##end"
echo "$2 $3 $(($2 + 2))"
echo -e "# tunnels"
for ((i = 1; i < $2; i++)); do
    echo "$i-$((i + 1))"
done
echo "# DONE"

