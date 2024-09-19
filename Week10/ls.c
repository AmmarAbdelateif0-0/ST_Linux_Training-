#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>


#define MAX_SIZE 1024

#define MAX_FILES 1024
#define MAX_PATH 1024
extern int errno;

typedef struct filee{
	char name[MAX_SIZE];
	struct stat stat
}FileInfo;
 

static int cmpstringp(const void *p1, const void *p2) {
    return strcmp(*(const char **) p1, *(const char **) p2);
}

int compare_mod_time(const void *a, const void *b) {
    return ((FileInfo *)b)->stat.st_mtime - ((FileInfo *)a)->stat.st_mtime;
}

int compare_acc_time(const void *a, const void *b) {
    return ((FileInfo *)b)->stat.st_atime - ((FileInfo *)a)->stat.st_atime;
}

int compare_chg_time(const void *a, const void *b) {
    return ((FileInfo *)b)->stat.st_ctime - ((FileInfo *)a)->stat.st_ctime;
}



void do_ls(char *dir,int show_all,int list_long,int sort_by_mod_time,int sort_by_acc_time,int sort_by_chg_time,int only_files,int only_dirs,int one_per_line,int inode_numbers);
void print_permissions(mode_t mode);
void print_file_info(FileInfo *file_info);



int main(int argc, char* argv[]) {
   int list_long = 0;
    int show_all = 0;
    int sort_by_mod_time = 0;
    int sort_by_acc_time = 0;
    int sort_by_chg_time = 0;
    int only_files = 0;
    int only_dirs = 0;
    int one_per_line = 0;
    int inode_numbers=0;

    int opt;
    while ((opt = getopt(argc, argv, "latucifd1")) != -1) {
        switch (opt) {
            case 'l': list_long = 1; break;
            case 'a': show_all = 1; break;
            case 't': sort_by_mod_time = 1; break;
            case 'u': sort_by_acc_time = 1; break;
            case 'c': sort_by_chg_time = 1; break;
            case 'f': only_files = 1; break;
            case 'd': only_dirs = 1; break;
	    case 'i': inode_numbers=1; break;      
            case '1': one_per_line = 1; break;
            default:
                fprintf(stderr, "Usage: %s [-latucifd1] [directories...]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        do_ls(".", show_all, list_long, sort_by_mod_time, sort_by_acc_time, sort_by_chg_time, only_files, only_dirs, one_per_line,inode_numbers);
    } else {
        for (int i = optind; i < argc; i++) {
            do_ls(argv[i], show_all, list_long, sort_by_mod_time, sort_by_acc_time, sort_by_chg_time, only_files, only_dirs, one_per_line,inode_numbers);
        }
    }

    return 0;


}

void do_ls(char *dir,int show_all,int list_long,int sort_by_mod_time,int sort_by_acc_time,int sort_by_chg_time,int only_files,int only_dirs,int one_per_line,int inode_numbers) {
    struct dirent *entry;
    
    FileInfo files[MAX_SIZE]= {NULL};
    
    int file_counter = 0;
    char *files_name[MAX_FILES] = {NULL};
    int total_inode=0;  
    DIR *dp = opendir(dir);
    
    if (dp == NULL) {
        fprintf(stderr, "Cannot open directory: %s\n", dir);
        return;
    }

    errno = 0;
    while ((entry = readdir(dp)) != NULL) {
    
     	if (errno != 0) {
            perror("readdir failed");
            closedir(dp);
            exit(1);
        }
     		if (!show_all && entry->d_name[0] == '.') continue;
        	if (only_dirs && entry->d_type != DT_DIR) continue;
        	if (only_files && entry->d_type != DT_REG) continue;

        char full_path[MAX_PATH];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, entry->d_name);

	struct stat st;
        if (stat(full_path, &st) == -1) {
            perror("stat");
            continue;
        }

        strncpy(files[file_counter].name, entry->d_name, sizeof(files[file_counter].name));
        files[file_counter].stat = st;

        files_name[file_counter] = strdup(entry->d_name);

       
       
        if (file_counter >= MAX_FILES) {
            fprintf(stderr, "Too many files\n");
            break;
        }

        if (files_name[file_counter] == NULL) {
            perror("strdup failed");
            closedir(dp);
            exit(1);
        }
                file_counter++;       
    }

    closedir(dp);
    
	

     if (sort_by_mod_time) {
        qsort(files, file_counter, sizeof(FileInfo), compare_mod_time);
    } else if (sort_by_acc_time) {
        qsort(files, file_counter, sizeof(FileInfo), compare_acc_time);
    } else if (sort_by_chg_time) {
        qsort(files, file_counter, sizeof(FileInfo), compare_chg_time);
    }else{
   	qsort(files_name, file_counter, sizeof(char *), cmpstringp);
    }
    for(int i=0;i<file_counter;i++){
    	total_inode+=files[file_counter].stat.
    }
    
    int file_in_oneline=0;
    if (list_long) {
        for (int i = 0; i < file_counter; i++) {
            print_file_info(&files[i]);
        }
    } else {
        if (one_per_line) {
            for (int i = 0; i < file_counter; i++) {
                printf("%s\n", files[i].name);
            }
        } else {
            for (int i = 0; i < file_counter; i++) {
            	if(file_in_oneline>=8){
        		printf("\n");
        		file_in_oneline=0;
        	}
                printf("%s   ", files[i].name);
                file_in_oneline++;
            }
            printf("\n");
        }
    }

   

}


void print_file_info(FileInfo *file_info) {
    struct tm *timeinfo;
    char time_buf[256];
    

    print_permissions(file_info->stat.st_mode);
    
    printf(" %ld", file_info->stat.st_nlink);
    
    struct passwd *pwd = getpwuid(file_info->stat.st_uid);
    struct group *grp = getgrgid(file_info->stat.st_gid);
    if (pwd) {
        printf(" %s", pwd->pw_name);
    } else {
        printf(" %d", file_info->stat.st_uid);
    }
    
    if (grp) {
        printf(" %s", grp->gr_name);
    } else {
        printf(" %d", file_info->stat.st_gid);
    }
    printf(" %5ld", file_info->stat.st_size);

    timeinfo = localtime(&file_info->stat.st_mtime);
    strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", timeinfo);
    printf(" %s", time_buf);

    printf(" %s\n", file_info->name);
}


void print_permissions(mode_t mode) {

    printf("%c%c%c%c%c%c%c%c%c%c",
           ((S_ISDIR(mode) )? ('d') : (S_ISCHR(mode) )? ('c') : ( S_ISBLK(mode) ) ? ( 'b' ): (S_ISLNK(mode)) ? ('s') :('-')),
           (mode & S_IRUSR) ? 'r' : '-',
           (mode & S_IWUSR) ? 'w' : '-',
           (mode & S_IXUSR) ? 'x' : '-',
           (mode & S_IRGRP) ? 'r' : '-',
           (mode & S_IWGRP) ? 'w' : '-',
           (mode & S_IXGRP) ? 'x' : '-',
           (mode & S_IROTH) ? 'r' : '-',
           (mode & S_IWOTH) ? 'w' : '-',
           (mode & S_IXOTH) ? 'x' : '-');
}

