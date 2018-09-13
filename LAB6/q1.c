#include <dirent.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <semaphore.h>

int file_index = 0;         // index for array[500];

struct params {
    char file_names [255];
    char word[255];           
};

void *thread(void *wData_element){
    struct params *temp = wData_element;

    FILE *fp; 
    char line[255]="";      
    fp = fopen(temp->file_names, "r");

    if(fp == NULL){
        perror("Error: File open failure.");
    }
    else{
        fgets(line,255, fp);
        char *token = strtok(line, " \t");
    	while (token != NULL){
        	//printf("%s\n", token);
		if (strstr(token,temp->word) != NULL){
        		printf("%s", strstr(token,temp->word));
        		fclose(fp);
        		return NULL;	
        	}        	
        	token = strtok(NULL, " \t");
    	}
    }
    fclose(fp);
    return NULL;
}

int main(int argc, char const* argv[]) {
	char dir_path[255];
	char word[255];
    DIR * dir_pointer;          // define a dir pointer;
    struct dirent * entry;      // entry under dir;
     // data directory contains all files in which we want to search.
    int count;
	printf("Enter the path of dir containing all files:");
	scanf("%s",dir_path);
	printf("Enter number of files to be scanned:");
	scanf("%d",&count);
	printf("Enter word to be searched:");
	scanf("%s",word); 
    struct params wData[count];
    pthread_t tid_array[count];
	
    if ((dir_pointer = opendir(dir_path)) == NULL) {
    	printf("can't open directory\n");
    	return 0;
  	}
    while( (entry = readdir(dir_pointer)) != NULL){

        if(entry->d_type == DT_REG){ // avoid the . and .. dir;
            char full_path[255];     
            full_path[0] = '\0';    // initilize the string;

            strcat(full_path, dir_path);  // concatenate file directory;
            strcat(full_path, entry->d_name);    // concatenate filename;
            strcpy(wData[file_index].file_names, full_path); // store file name into file_names array;
            strcpy(wData[file_index].word,word);
            pthread_create(&tid_array[file_index], NULL, thread, &wData[file_index]);

            file_index++;   // increase the file index for next file.
        }
    }

    for(int i=0; i < count; i++){
        pthread_join(tid_array[i], NULL);
    }
    return 0;
}
