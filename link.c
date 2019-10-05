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

  
    //"https://codeload.github.com/minhsk96/nt/zip/master"};
    int n = 0, k = 0;
    char *lastslash;
    char* name;
    char cwd[PATH_MAX];

    CURL *handle = curl_easy_init();
    CURLcode res;
    FILE *file, *f;

    lastslash = strrchr(argv[1], '/');
    name = lastslash ? lastslash + 1 : argv[1];
    //printf("\nURL: %s\n", argv[1]);
    //printf("Filename: %s\n", name);

    curl_easy_setopt(handle, CURLOPT_URL, argv[1]);
    file = fopen(name, "wb");       
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, file);
    //curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data); 
    res = curl_easy_perform(handle);
    //printf("%d",res);

    fseek(file, 0L, SEEK_END); // get file size 
    int sz = ftell(file); // file size = sz 

    fclose(file);
    curl_easy_cleanup   (handle);

    f = fopen("status.txt", "w+");
    getcwd(cwd, sizeof(cwd));
    fprintf(f,"link download: %s\n",argv[1]);
    fprintf(f,"link path local: %s\n",cwd);
    if(res==0 && sz !=0) {
        fprintf(f,"status: success");
    }
    else{
        fprintf(f,"status: false");
    }
    fclose(f);
    return 0;
}

