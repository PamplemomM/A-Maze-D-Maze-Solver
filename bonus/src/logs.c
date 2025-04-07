/*
** EPITECH PROJECT, 2025
** logs.c
** File description:
** Functions to update the logs.
*/

#include "../include/header_viewer.h"

int add_to_logs(char *entry)
{
    text_t *logs = get_text("logstxt");
    char *tmp = NULL;
    int cnt = 0;

    for (int i = 0; logs->str[i] != '\0'; i++) {
        if (logs->str[i] == '\n')
            cnt++;
        if (cnt >= 32) {
            logs->str[i + 1] = '\0';
            break;
        }
    }
    tmp = merge_str(entry, logs->str);
    if (tmp == NULL)
        return ERROR;
    OMNIFREE(logs->str, 1);
    logs->str = tmp;
    sfText_setString(logs->text, logs->str);
    return SUCCESS;
}

int add_logs_move(vwr_robot_t *robot, room_t *dest)
{
    char *entry = malloc(sizeof(char) * (strlen("moving  to room \n")
        + strlen(robot->sprite->name) + strlen(dest->name) + 1));

    if (entry == NULL)
        return ERROR;
    sprintf(entry, "moving %s to room %s\n", robot->sprite->name, dest->name);
    if (add_to_logs(entry) == ERROR) {
        OMNIFREE(entry, 1);
        return ERROR;
    }
    OMNIFREE(entry, 1);
    return SUCCESS;
}
