#!/bin/bash

 if [[ -n "$1" ]]; then
    nb_robots=$1
else
    echo "Usage: ./gen.sh nb_robots nb_rooms [limit=25]"
    exit 0
fi

if [[ -n "$2" ]]; then
    nb_rooms=$2
else
    echo "Usage: ./gen.sh nb_robots nb_rooms [limit=25]"
    exit 0
fi

if [[ -n "$3" ]]; then
    limit=$3
else
    limit=25
fi

declare -A positions

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

echo "$nb_robots"
echo "##start"

for ((i = 0; i <= nb_rooms; i++)); do
  if [ "$i" -eq "$nb_rooms" ]; then
    echo "##end"
  fi
  echo -n "$i "
  generate_pos
done

echo "#tunnels"

current=0
while [ "$current" -ne "$nb_rooms" ]; do
  next=$(((current + 1 + RANDOM % ($nb_rooms - current))))
  echo "$current-$next"
  current=$next
done

for ((i = 0; i <= nb_rooms; i++)); do
  for ((j = i + 1; j <= nb_rooms; j++)); do
    if [ "$i" -ne "$j" ] && [ $((RANDOM % 100)) -lt 20 ]; then
      echo "$i-$j"
    fi
  done
done

