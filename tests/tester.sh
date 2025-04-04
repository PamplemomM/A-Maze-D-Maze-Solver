#!/bin/bash

error_counter=0
error() {
    ((error_counter++))
    "$@" >> tests/testerEresult
    value=$?
    if [ "$value" -eq 84 ]; then
        echo -e "[Test $(printf "%02d" $error_counter)] : \e[1;32mSUCCESS\e[0m                       |"
    else
        echo -e "[Test $(printf "%02d" $error_counter)] : \e[1;31mFAILURE\e[0m                       |"
    fi
}

success_counter=0
success() {
    ((success_counter++))
    "$@" >> tests/testerSresult
    value=$?
    if [ "$value" -eq 0 ]; then
        echo -e "[Test $(printf "%02d" $success_counter)] : \e[1;32mSUCCESS\e[0m                       |"
    else
        echo -e "[Test $(printf "%02d" $success_counter)] : \e[1;31mFAILURE\e[0m                       |"
    fi
}


dispE() {
    echo "" >> tests/testerEresult
    echo "$1" >> tests/testerEresult
    echo "" >> tests/testerEresult
}

dispS() {
    echo "" >> tests/testerSresult
    echo "$1" >> tests/testerSresult
    echo "" >> tests/testerSresult
}


delimE() {
    echo "---------------------------------------" >> tests/testerEresult
}


delimS() {
    echo "---------------------------------------" >> tests/testerSresult
}



value=$1
if [ "$value" = "clean" ]; then
    touch data
    rm tests/testerEresult > data 2>&1
    result1=$?
    rm tests/testerSresult > data 2>&1
    result2=$?
    rm data

    if [ $result1 -ne 0 ] && [ $result2 -ne 0 ]; then
        echo -e "Cleaning the tests : \e[1;31mNothing to be clean.\e[0m"
    else
        echo -e "Cleaning the tests : \e[1;32mSUCCESS\e[0m"
    fi
    exit
fi


echo "-------------------------------------------"
echo -e "\e[1;31mTESTING\e[0m: Compilation                      |"
echo "-------------------------------------------"
sleep 0.3

make re

echo "-------------------------------------------"
echo -e "\e[1;33mTESTING\e[0m: Testing with error values        |"
echo "-------------------------------------------"
sleep 1.3

touch datas

# RESET the logs

touch tests/testerEresult
touch tests/testerSresult
echo "" > tests/testerEresult
echo "" > tests/testerSresult


delimE
dispE "[Test 01] - Testing with empty file :"
echo "" > data
error ./amazed < data
dispE "[Test 01] - Error exit Status : SUCCESS"
delimE

dispE "[Test 02] - Testing with bad robot count :"
echo "-1" > data
error ./amazed < data
dispE "[Test 02] - Error exit Status : SUCCESS"
delimE

dispE "[Test 03] - Testing with no exit :"
echo -e "1\n##end \n1 2 2 \n##start \n2 2 3 \n1-2" > data
error ./amazed < data
dispE "[Test 03] - Error exit Status : SUCCESS"
delimE

dispE "[Test 04] - Testing with no rooms :"
echo -e "3\n" > data
error ./amazed < data
dispE "[Test 04] - Error exit Status : SUCCESS"
delimE

dispE "[Test 05] - Testing with no tunnels :"
echo -e "3\n##end \n1 2 2 \n##start \n2 2 3" > data
error ./amazed < data
dispE "[Test 05] - Error exit Status : SUCCESS"
delimE

dispE "[Test 06] - Testing with bad tunnels :"
echo -e "3\n##end \n1 2 2 \n##start \n2 2 3 \n 3-4" > data
error ./amazed < data
dispE "[Test 06] - Error exit Status : SUCCESS"
delimE
sleep 0.3

dispE "[Test 07] - Testing with no start room :"
echo -e "3\n##end \n1 2 2 \n2 2 3 \n 2-1" > data
error ./amazed < data
dispE "[Test 07] - Error exit Status : SUCCESS"
delimE
sleep 0.8

dispE "[Test 08] - Testing with no end room :"
echo -e "3\n##start \n1 2 2 \n2 2 3 \n 2-1" > data
error ./amazed < data
dispE "[Test 08] - Error exit Status : SUCCESS"
delimE

dispE "[Test 09] - Testing with multiple start rooms :"
echo -e "3\n##start \n1 2 2 \n##end \n2 2 3 \n##start \n3 3 3 \n 1-2" >data
error ./amazed < data
dispE "[Test 09] - Error exit Status : SUCCESS"
delimE
sleep 0.8

dispE "[Test 10] - Testing with end rooms :"
echo -e "3\n##start \n1 2 2 \n##end \n2 2 3 \n##end \n3 3 3 \n 1-2" > data
error ./amazed < data
dispE "[Test 10] - Error exit Status : SUCCESS"
delimE
sleep 0.8

dispE "[Test 11] - Testing with input line containing garbage :"
echo -e "3\n##start \n1 2 2 \n##end \n2 2 3 \n ble blah bla\n3 3 3 \n1-2" > data
error ./amazed < data
dispE "[Test 11] - Error exit Status : SUCCESS"
delimE
sleep 0.8


sleep 0.1
echo "-------------------------------------------"
echo -e "\e[1;34mTESTING\e[0m: Testing with success values      |"
echo "-------------------------------------------"
sleep 1.2

delimS
success dispS "[Test 01] - Testing usage : "
success ./109titration -h
dispS "[Test 01] - Exit Status : SUCCESS"
delimS
sleep 1.3

success dispS "[Test 02] - Testing with good values : "
success ./109titration folder/values.csv
dispS "[Test 02] - Exit Status : SUCCESS"
delimS
sleep 0.3

success dispS "[Test 03] - Testing usage : "
success ./109titration -h
sleep 0.1
sleep 0.05
dispS "[Test 03] - Exit Status : SUCCESS"
delimS
sleep 0.1

success dispS "[Test 04] - Testing with good values : "
success ./109titration folder/dataset_1.csv
sleep 1.5
dispS "[Test 04] - Exit Status : SUCCESS"
delimS
sleep 1.55

success dispS "[Test 05] - Testing with good values : "
success ./109titration folder/dataset_2.csv
dispS "[Test 05] - Exit Status : SUCCESS"
delimS
sleep 0.3

success dispS "[Test 06] - Testing with good values : "
success ./109titration folder/dataset_3.csv
dispS "[Test 06] - Exit Status : SUCCESS"
delimS
sleep 0.3


sleep 1
echo "-------------------------------------------"
echo -e "\e[1;32mTESTING\e[0m: Every test has been executed     |"
echo "-------------------------------------------"

