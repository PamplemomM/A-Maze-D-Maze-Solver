sleep 0.1
echo ""
echo -e -n "\e[1;34mCLEANER\e[0m: Cleaning project."
sleep 0.5
echo -e -n "."
sleep 0.7
echo -e -n "."
touch data
touch unit_tests_test
rm unit_tests* > data
rm coding-style-reports.log -f > data
sleep 0.4
echo -n -e "\b \b"
rm a.out -f > data
sleep 0.2
make fclean > data
echo -n -e "\b \b"
sleep 0.7
echo -n "."
sleep 0.3
make viewer_fclean > data
echo -n "."
cd bonus/
make fclean > data
cd ..
sleep 0.6
echo -n -e "\b \b"
sleep 0.4
echo -n -e "\b \b\b \b\b \b\b \b\b \b"
echo -n -e "\b \b\b \b\b \b\b \b\b \b"
echo -n -e "\b \b\b \b\b \b\b \b\b \b"
echo -n -e "\b \b\b \b\b \b\b \b\b \b"
echo -n -e "\b \b\b \b\b \b\b \b\b \b"
echo -n -e "\b \b\b \b\b \b\b \b"
rm data
echo -e "\e[1;32mCLEANER\e[0m: your project is now completely clean!"
echo ""
