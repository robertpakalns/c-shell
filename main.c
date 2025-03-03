#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void killport(const char *port)
{
    char command[256];
    snprintf(command, sizeof(command), "netstat -ano | findstr :%s", port);

    FILE *fp = _popen(command, "r");
    if (fp == NULL)
    {
        printf("Error executing netstat command.\n");
        return;
    }

    int pids[100]; // Assume that there are less than 100 PIDs
    int pid_count = 0;
    char line[256];

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        char *pid_str = strrchr(line, ' ');

        if (!pid_str)
            return;

        int pid = atoi(pid_str + 1);
        if (!(pid > 0))
            return;

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

    for (int i = 0; i < pid_count; i++)
    {
        snprintf(command, sizeof(command), "taskkill /PID %d /F", pids[i]);
        system(command);
        printf("Process with PID %d terminated.\n", pids[i]);
    }
}

int main(int argc, char *argv[])
{
    if (argc == 3 && strcmp(argv[1], "killport") == 0)
    {
        killport(argv[2]);
        return 0;
    }

    printf("Usage: %s killport <port>\n", argv[0]);
    return 1;
}