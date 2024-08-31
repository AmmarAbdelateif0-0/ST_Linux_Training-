#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>

#define SECTOR_SIZE 512

typedef struct {
    uint8_t  status;
    uint8_t  s_chs[3];
    uint8_t  partition_type;
    uint8_t  e_chs[3];
    uint32_t lba;
    uint32_t num_of_sector;
} PartitionEntry;

int main(int argc, char *argv[]) {
  if (argc < 2) {
        fprintf(stderr, "Usage: %s <disk>\n", argv[0]);
        return 1;
    }

    char *disk_folder = argv[1];
    int fd = open(disk_folder, O_RDONLY);
    if (fd == -1) {
        perror("Open failed");
        return 1;
    }

    char buf[SECTOR_SIZE];
    if (read(fd, buf, SECTOR_SIZE) != SECTOR_SIZE) {
        perror("Read failed");
        close(fd);
        return 1;
    }

    PartitionEntry *table_entry = (PartitionEntry*) &(buf[446]);
    printf("%s     %s     %s           %s            %s         %s     %s     %s\n",
           "Device", "Boot", "Start", "End", "Sectors", "Size", "Id", "Type");

    uint8_t index_extended[4] = {0};

    for (int i = 0; i < 4; i++) {
        printf("%s%d     %c     %-10u      %-10u     %-10u      %-uG      %02X      %s\n",
               disk_folder, i + 1,
               table_entry[i].status == 0x80 ? '*' : ' ',
               table_entry[i].lba,
               table_entry[i].lba + table_entry[i].num_of_sector - 1,
               table_entry[i].num_of_sector,
               (uint32_t)((uint64_t)table_entry[i].num_of_sector * SECTOR_SIZE / (1024 * 1024 * 1024)),
               table_entry[i].partition_type,
               (table_entry[i].partition_type == 0x05 ? "Extended" : "Linux"));

        if (table_entry[i].partition_type == 0x05) {
            index_extended[i] = 1;
        }
    }

    for (int j = 0; j < 4; j++) {
        if (index_extended[j] == 1) {
            uint64_t start_sector = table_entry[j].lba;
            uint64_t end_sector = start_sector + table_entry[j].num_of_sector;

		int i=0;
            for (uint64_t current_sector = start_sector; current_sector < end_sector; ) {
             
                off_t offset = current_sector * SECTOR_SIZE;
		    if (lseek(fd, offset, SEEK_SET) < 0) {
                    perror("lseek failed");
                    close(fd);
                    return 1;
                }

                if (read(fd, buf, SECTOR_SIZE) != SECTOR_SIZE) {
                    perror("read failed");
                    close(fd);
                    return 1;
                }
                PartitionEntry *table_extended = (PartitionEntry*) &(buf[446]);
                printf("%s%d     %c     %-10u      %-10u     %-10u      %-uG      %02X      %s\n",
                       disk_folder, 5 + i,
                       table_extended[0].status == 0x80 ? '*' : ' ',
                       table_extended[0].lba+table_entry[j].lba,
                       table_extended[0].lba + table_extended[0].num_of_sector+table_entry[j].lba - 1,
                       table_extended[0].num_of_sector,
                       (uint32_t)((uint64_t)table_extended[0].num_of_sector * SECTOR_SIZE / (1024 * 1024 * 1024)),
                       table_extended[0].partition_type,
                       (table_extended[0].partition_type == 0x05 ? "Extended" : "Linux"));
			
			current_sector=(table_extended[0].lba+ table_extended[0].num_of_sector-table_entry[j].lba-1);
			i++;
		}
		}
	}                
                    close(fd);
    return 0;
}

