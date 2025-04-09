#!/bin/bash

# import my_putstr(char c, int size), load_animation(void), remove(size), reset_file(void)
[ -f "./bash_tools/tools.sh" ] && source "./bash_tools/tools.sh" || echo "clean.sh : Tools unfound!"

# Display the title.
sleep 0.1
echo ""
echo -e -n "\e[1;34mCLEANER\e[0m: Cleaning project."

# Animation during the cleaning.
load_animation

# Remove the unit tests.
touch unit_tests_test
rm unit_tests* > cleaner

# Remove the coding-style report.
rm coding-style-reports.log -f > cleaner

# Remove the program objects and executable.
make fclean > cleaner

# Remove the viewer objects and executable.
make viewer_fclean > cleaner

# Remove everything inside the viewer directory.
cd bonus/
make fclean > ../cleaner
cd ..

# Remove the functional test logs.
./tester.sh clean > cleaner
sleep 0.05

# Remove the text
remove 29

# Remove the cleaner file.
rm cleaner
# Display the success title.
echo -e "\e[1;32mCLEANER\e[0m: your project is now completely clean!"
echo ""
