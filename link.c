#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}


int main(int argc, char *argv[]){

    int n = 0, k = 0;
    char *lastslash;
    char* name;
    char cwd[PATH_MAX];
    char chunk[200];
    CURL *handle = curl_easy_init();
    CURLcode res;
    FILE *f, *f1;
    f1 = fopen(argv[1],"r");
    f = fopen("status.txt", "w");
    
    //while(fgets(chunk, sizeof(chunk), fp) != NULL) {
    while (fscanf(f1, "%s", chunk) != EOF) {
        FILE *file;
        lastslash = strrchr(chunk, '/');
        name = lastslash ? lastslash + 1 : chunk;

        curl_easy_setopt(handle, CURLOPT_URL, chunk);
        file = fopen(name, "wb");   

        curl_easy_setopt(handle, CURLOPT_WRITEDATA, file);
        //curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
        res = curl_easy_perform(handle);
        fprintf(f,"link download: %s\n", chunk);
        printf("download file name: %s\n", name);
        printf("%d\n",res);
        
        fseek(file, 0L, SEEK_END); // get file size 
        int sz = ftell(file); // file size = sz 

        getcwd(cwd, sizeof(cwd));
        fprintf(f,"link path local: %s\n", cwd);

        if(res==0 && sz !=0) {
            fprintf(f,"status: success");
        }
        else{
            fprintf(f,"status: false");
        }

        fprintf(f,"\n============================\n\n");
        fclose(file);
        
    }
    curl_easy_cleanup (handle);
    fclose(f);
    fclose(f1);
    return 0;
}
