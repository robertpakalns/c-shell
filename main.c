#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void killport(const char *port)
{
    char command[64];
    snprintf(command, sizeof(command), "netstat -ano | findstr :%s", port);

    FILE *fp = _popen(command, "r");
    if (fp == NULL)
    {
        printf("An error occured while executing netstat command.\n");
        return;
    }

    int pids[64]; // Assume that there 64 and less target PIDs
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
        snprintf(command, sizeof(command), "taskkill /PID %d /F > nul 2>&1", pids[i]);
        system(command);
        printf("Process with PID %d has been terminated.\n", pids[i]);
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