#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/configure.h"
extern config* data;
extern config* fil_data;

int main(int argc,char* argv[]){
    FILE* f = stdin;
    int cnt = add(f);
    if(data) {
        int size = filter(cnt);
        if(fil_data)
            print(size);
    }
    delete1(cnt);
    if(fil_data)
        free(fil_data);
}
