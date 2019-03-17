#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>


void search(const char *name, int in, const char *file)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;
	
	//char path[1024];

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            //printf("%*s[%s]\n", in, "", entry->d_name);
	    //printf("%s\n", path);
            search(path, in + 2, file);
        } else {
            //printf("%*s- %s", in, "", entry->d_name);
	    if(strstr(entry->d_name, file) != NULL){
		printf("%s/%s\n", name, entry->d_name);
	    }
        }
    }
    closedir(dir);
}

int main(int argc, char **argv) {
    
    if(argc < 3){
	printf("Invalid argument\n");
	return 0;	
    }
    search(argv[1], 0, argv[2]);
    printf("\n");
    return 0;
}
