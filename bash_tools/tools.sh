#!/bin/bash


disp_delim() {
    local size

    if [[ -n "$1" ]]; then
        size=$1
    else
        size=10
    fi

    for ((i = 0; i < size; i++)); do
        echo  -n "-"
    done
    echo ""
}

remove() {
    local size

    if [[ -n "$1" ]]; then
        size=$1
    else
        size=0
    fi

    for ((i = 0; i < size; i++)); do
        echo -e -n "\b \b"
    done
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
