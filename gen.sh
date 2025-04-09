#!/bin/bash

# Get robot number.
 if [[ -n "$1" ]]; then
    nb_robots=$1
else
    echo "Usage: ./gen.sh nb_robots nb_rooms [limit=25]"
    exit 0
fi


# Get room number.
if [[ -n "$2" ]]; then
    nb_rooms=$2
else
    echo "Usage: ./gen.sh nb_robots nb_rooms [limit=25]"
    exit 0
fi


# Get the size limit (default = 25).
if [[ -n "$3" ]]; then
    limit=$3
else
    limit=25
fi



declare -A positions

# Function to generate a random position depending on the limit.
generate_pos() {
  while :; do
    x=$((RANDOM % limit))
    y=$((RANDOM % limit))
    key="$x,$y"
    if [ -z "${positions[$key]}" ]; then
      positions["$key"]=1
      echo "$x $y"
      return
    fi
  done
}


# Write the number of robots.
echo "$nb_robots"
echo "##start"


# Generate the rooms until the end.
for ((i = 0; i <= nb_rooms; i++)); do
  if [ "$i" -eq "$nb_rooms" ]; then
    echo "##end"
  fi
  echo -n "$i "
  generate_pos
done


# Generate the tunnels
echo "#tunnels"





# Generate a direct path to the end
current=0
while [ "$current" -ne "$nb_rooms" ]; do
  next=$(((current + 1 + RANDOM % ($nb_rooms - current))))
  echo "$current-$next"
  current=$next
done


# Generate random paths
for ((i = 0; i <= nb_rooms; i++)); do
  for ((j = i + 1; j <= nb_rooms; j++)); do
    if [ "$i" -ne "$j" ] && [ $((RANDOM % 100)) -lt 20 ]; then
      echo "$i-$j"
    fi
  done
done
