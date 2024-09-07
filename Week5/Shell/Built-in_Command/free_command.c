#include"../shell/shell.h"



void free_exec() {
    FILE *meminfo = fopen("/proc/meminfo", "r");
    if (meminfo == NULL) {
        perror("Failed to open /proc/meminfo");
        return;
    }

    char line[256];
    long total_ram = 0, free_ram = 0, available_ram = 0;
    long total_swap = 0, free_swap = 0;

    while (fgets(line, sizeof(line), meminfo)) {
        sscanf(line, "MemTotal: %ld kB", &total_ram);
        sscanf(line, "MemFree: %ld kB", &free_ram);
        sscanf(line, "MemAvailable: %ld kB", &available_ram);
        sscanf(line, "SwapTotal: %ld kB", &total_swap);
        sscanf(line, "SwapFree: %ld kB", &free_swap);
    }
    fclose(meminfo);

    long used_ram = total_ram - free_ram;
    long used_swap = total_swap - free_swap;

    printf("RAM:\n");
    printf("  Total: %ld MB\n", total_ram / 1024);
    printf("  Used: %ld MB\n", used_ram / 1024);
    printf("  Free: %ld MB\n", free_ram / 1024);

    printf("Swap:\n");
    printf("  Total: %ld MB\n", total_swap / 1024);
    printf("  Used: %ld MB\n", used_swap / 1024);
    printf("  Free: %ld MB\n", free_swap / 1024);
}
