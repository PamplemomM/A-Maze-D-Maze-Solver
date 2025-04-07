/*
** EPITECH PROJECT, 2023
** lib_test.c
** File description:
** test each function of lib
*/

#include "criterion/criterion.h"
#include "criterion/redirect.h"
#include "../../include/header_amazed.h"

//**********************************
// ------ MINI_PRINTF FUNCTION------
//**********************************

Test(mini_printf_str, full_covr, .init = cr_redirect_stdout)
{
    char *str = "hello";

    mini_printf("%s\n", str);
    cr_assert_stdout_eq_str("hello\n");
}

Test(mini_printf_char, full_covr, .init = cr_redirect_stdout)
{
    mini_printf("%c %%", '\n');
    cr_assert_stdout_eq_str("\n %");
}

Test(mini_printf_num, full_covr, .init = cr_redirect_stdout)
{
    mini_printf("%d %d\n", 2, -25);
    cr_assert_stdout_eq_str("2 -25\n");
}

Test(mini_printf_overflow, full_covr, .init = cr_redirect_stdout)
{
    mini_printf("%d\n", -2147483647 - 1);
    cr_assert_stdout_eq_str("-2147483648\n");
}

//**********************************
// --------- LIB FUNCTIONS ---------
//**********************************

Test(my_getnbr, full_covr)
{
    char str[7] = "c-1bbc\0";
    char src[7] = "caac45\0";

    cr_assert_eq(my_getnbr(str), -1);
    cr_assert_eq(my_getnbr(src), 45);
}

Test(my_getnbr_error, full_covr)
{
    char *str = NULL;

    cr_assert_eq(my_getnbr(str), 0);
}

Test(char_in_str_true, full_covr)
{
    cr_assert_eq(char_in_str('o', "bonjour"), TRUE);
}

Test(char_in_str_false, full_covr)
{
    cr_assert_eq(char_in_str('z', "bonjour"), FALSE);
}
