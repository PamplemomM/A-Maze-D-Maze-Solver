#!/bin/bash

# import my_putstr(char c, int size), load_animation(void), remove(size)
[ -f "./bash_tools/tools.sh" ] && source "./bash_tools/tools.sh" || echo "clean.sh : Tools unfound!"

sleep 0.1
echo ""
echo -e -n "\e[1;34mCLEANER\e[0m: Cleaning project."

load_animation

touch unit_tests_test
rm unit_tests* > cleaner

rm coding-style-reports.log -f > cleaner

make fclean > cleaner

make viewer_fclean > cleaner

cd bonus/
make fclean > ../cleaner
cd ..

./tester.sh clean > cleaner
sleep 0.05

remove 29

rm cleaner
echo -e "\e[1;32mCLEANER\e[0m: your project is now completely clean!"
echo ""
