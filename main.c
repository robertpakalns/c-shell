#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void killport(char *port)
{
    char command[64];
    snprintf(command, sizeof(command), "netstat -ano | findstr :%s", port);

    FILE *fp = _popen(command, "r");
    if (fp == NULL)
    {
        printf("An error occured while executing netstat command.\n");
        return;
    }

    int pids[64]; // Assume that there are 64 or less target PIDs
    int pid_count = 0;
    char line[256];

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        char *pid_str = strrchr(line, ' ');

        if (!pid_str)
            continue;

        int pid = atoi(pid_str + 1);
        if (!(pid > 0))
            continue;

        int already_exists = 0;
        for (int i = 0; i < pid_count; i++)
        {
            if (pids[i] == pid)
            {
                already_exists = 1;
                break;
            }
        }
        if (!already_exists)
            pids[pid_count++] = pid;
    }
    _pclose(fp);

    if (pid_count == 0)
    {
        printf("No processes found on port %s.\n", port);
        return;
    }

    for (int i = 0; i < pid_count; i++)
    {
        snprintf(command, sizeof(command), "taskkill /PID %d /F", pids[i]);

        FILE *taskkill_fp = _popen(command, "r");
        if (taskkill_fp == NULL)
        {
            printf("An error occurred while executing taskkill command.\n");
            continue;
        }

        char output[256];

        if (fgets(output, sizeof(output), taskkill_fp) == NULL)
        {
            printf("No output received from taskkill for PID %d.\n", pids[i]);
            _pclose(taskkill_fp);
            continue;
        }

        if (strncmp(output, "SUCCESS", 6) == 0)
            printf("Process with PID %d has been terminated.\n", pids[i]);
        else
            printf("Failed to terminate process with PID %d.\n", pids[i]);

        _pclose(taskkill_fp);
    }
}

int main(int argc, char *argv[])
{
    if (argc == 3 && strcmp(argv[1], "killport") == 0)
    {
        killport(argv[2]);
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "killport") == 0)
    {
        printf("Usage: %s killport <port>\n", argv[0]);
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "list") == 0)
    {
        printf("List of commands:\n%s killport <port>\n", argv[0]);
        return 0;
    }

    printf("Hello! Tricko is here. Type\n%s list\nfor more information.\n", argv[0]);
    return 0;
}