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
    char link[500];
    CURL *handle = curl_easy_init();
    CURLcode res;
    FILE *file, *f, *f1;
    f1 = fopen(argv[2],"r");
    fscanf(f1,"%s",link);

    lastslash = strrchr(link, '/');
    name = lastslash ? lastslash + 1 : link;
    //printf("\nURL: %s\n", argv[1]);
    //printf("Filename: %s\n", name);

    curl_easy_setopt(handle, CURLOPT_URL, link);
    file = fopen(name, "wb");       
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, file);
    //curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data); 
    res = curl_easy_perform(handle);
    //printf("%d",res);

    fseek(file, 0L, SEEK_END); // get file size 
    int sz = ftell(file); // file size = sz 

    curl_easy_cleanup   (handle);

    f = fopen("status.txt", "w+");
    getcwd(cwd, sizeof(cwd));
    fprintf(f,"link download: %s\n",link);
    fprintf(f,"link path local: %s\n",cwd);
    if(res==0 && sz !=0) {
        fprintf(f,"status: success");
    }
    else{
        fprintf(f,"status: false");
    }
    fclose(file);
    fclose(f);
    fclose(f1);
    return 0;
}
