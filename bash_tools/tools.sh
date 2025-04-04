#!/bin/bash


my_putstr() {
    local size
    local char

    if [[ -n "$1" ]]; then
        char=$1
    else
        char="-"
    fi
    if [[ -n "$2" ]]; then
        size=$2
    else
        size=10
    fi

    for ((i = 0; i < size; i++)); do
        echo -e -n "$char"
    done
    if [[ -n "$3" ]]; then
        echo -e "$3"
    fi
}

remove() {
    local size

    if [[ -n "$1" ]]; then
        size=$1
    else
        size=0
    fi

    my_putstr "\b \b" $size
}

load_animation() {
    echo -e -n "."
    sleep 0.7
    echo -e -n "."
    sleep 0.4
    echo -n -e "\b \b\b \b\b \b"
    sleep 0.2
    echo -n -e "."
    sleep 0.7
    echo -n "."
    sleep 0.3
    echo -n "."
    sleep 0.2
    echo -n -e "\b \b\b \b\b \b"
    sleep 0.2
    echo -n "."
    sleep 0.2
    echo -n "."
    sleep 0.05
}

reset_file() {
    local file

    if [[ -n "$1" ]]; then
        file=$1
    else
        echo -e "reset_file: Argument needed."
        exit 1
    fi
    touch $file
    echo "" > $file
}
