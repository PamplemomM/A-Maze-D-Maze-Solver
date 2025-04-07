/*
** EPITECH PROJECT, 2025
** omnifree_test.c
** File description:
** test omnifree_function.
*/

#include "criterion/criterion.h"
#include "criterion/redirect.h"
#include "../../include/header_amazed.h"

//**********************************
// ------- OMNIFREE FUNCTION -------
//**********************************

Test(omnifree2dim, full_covr, .init = cr_redirect_stdout)
{
    char **arr = malloc(sizeof(char *) * 3);

    arr[0] = my_strdup("Hello !");
    arr[1] = my_strdup("BLUD!!");
    arr[2] = NULL;
    omnifree((void ***)&arr, 2);
}

Test(omnifree1dim, full_covr, .init = cr_redirect_stdout)
{
    char *dup = my_strdup("Hello !");

    omnifree((void ***)&dup, 1);
}

Test(omnifree_error, full_covr, .init = cr_redirect_stdout)
{
    char *dup = NULL;

    omnifree((void ***)&dup, 1);
}
