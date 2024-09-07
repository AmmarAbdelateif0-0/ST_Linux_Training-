#include"../shell/shell.h"


void uptime_exec() {
    FILE *uptime_file = fopen("/proc/uptime", "r");
    if (uptime_file == NULL) {
        perror("Failed to open /proc/uptime");
        return;
    }

    double uptime, idle_time;
    if (fscanf(uptime_file, "%lf %lf", &uptime, &idle_time) != 2) {
        perror("Failed to read /proc/uptime");
        fclose(uptime_file);
        return;
    }
    fclose(uptime_file);

    int uptime_hours = (int)(uptime / 3600);
    int uptime_minutes = (int)((uptime - (uptime_hours * 3600)) / 60);

    printf("System Uptime: %d hours, %d minutes\n", uptime_hours, uptime_minutes);
    printf("Idle Time: %.2f seconds\n", idle_time);
}
