#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "configure.h"
#define SUCCESS 0
#define ERROR -1
//ввод строки
char* input_str(FILE* f){
    int counter = 0;
    int size_a = 0;
    char* string = NULL;
    char c = '\0';
    while(c = getc(f), c != EOF && c!= '\n'){
        if(counter >= size_a){
            char* tmp_string = malloc(((!size_a ? 2:size_a*2+1)*sizeof(char)));
            size_a = (!size_a ? 1: size_a*2);
            if(!tmp_string){
                if(string)
                    free(string);
                return NULL;
            }
            if(string){
                strcpy(tmp_string,string);
                free(string);
            }
            string = tmp_string;
        }
        string[counter++] = c;
        string[counter] = '\0';
    }
    if(c == EOF){
        if(string)
            free(string);
        return NULL;
    }
    return string;
}

// ввод целочисленных значений
int input_int(FILE* f){
    int result = -1;
    char c = '\0';
    while(c=getc(f),c != EOF && c != '\n' && c!=' '){
        if(c >= '0' && c <= '9') {
            if(result < 0)
                result = 0;
            result = result * 10 +  (c - '0');
        }
        else{
            while(c=getc(f),c!=EOF && c !='\n');
            result = -1;
        }
    }
    return(result);
}

//ввод даты
int* input_date(FILE* f){
    int* a = malloc(3*sizeof(int));
    if(!a)
        return NULL;
    size_t day = input_int(f);
    if(day < 1 || day > 31){
        free(a);
        return NULL;
    }
    size_t month = input_int(f);
    if(month < 1 || month > 12){
        free(a);
        return NULL;
    }
    size_t year = input_int(f);
    if(year < 1900){
        free(a);
        return NULL;
    }
    a[0] = day,a[1] = month,a[2] = year;
    return a;
}

//вывод ответа
int print(int cnt){
    if(!fil_data)
        return ERROR;
    int i = 0;
    while(i < cnt && (fil_data+i)){
        printf("%d: %s, %s, %d, %d:%d:%d, %d:%d:%d\n",i,(fil_data+i)->name,(fil_data+i)->class1,(fil_data+i)->version,
               (fil_data+i)->date_inst.tm_mday,(fil_data+i)->date_inst.tm_mon+1,(fil_data+i)->date_inst.tm_year + 1900,
               (fil_data+i)->date_upd.tm_mday,(fil_data+i)->date_upd.tm_mon+1,(fil_data+i)->date_upd.tm_year + 1900);
        i++;
    }
    return SUCCESS;
}



int add(FILE* f){
    int cnt = 0;
    int size = 0;
    char* name = NULL;
    // добавление новых продуктов в структуру
    while(printf("Enter name for product\n"),name = input_str(f),name){
        if(!name)
            return cnt;
        printf("enter class of product\n");
        char* class = input_str(f);
        if(!class) {
            free(name);
            return cnt;
        }
        printf("enter version of product\n");
        int version = input_int(f);
        if(version == ERROR) {
            free(name),free(class);
            return cnt;
        }
        printf("enter installation date of product\n");
        int* date_inst = input_date(f);
        if(!date_inst) {
            free(name),free(class);
            return cnt;
        }
        printf("enter update date of product\n");
        int* date_upd = input_date(f);
        if(!date_upd) {
            free(name),free(class),free(date_inst);
            return cnt;
        }
        if(size == 0) {
            data = (config *)malloc(sizeof(config));
            size++;
        }else if(cnt >= size){
            data = (config*)realloc(data,size*2*sizeof(config));
            size*=2;
        }
        if(!data){
            free(name),free(class),free(date_inst),free(date_upd);
            return ERROR;
        }
        (data+cnt)->name = name;
        (data+cnt)->class1 = class;
        (data+cnt)->version = version;
        struct tm date_i = {0,0,0, date_inst[0],date_inst[1]-1,date_inst[2]-1900,0,0};
        (data+cnt)->date_inst = date_i;
        struct tm date_u = {0,0,0, date_upd[0],date_upd[1]-1,date_upd[2]-1900,0,0};
        (data+cnt)->date_upd = date_u;
        free(date_inst);
        free(date_upd);
        cnt++;
    }
    //конец ввода -> конец добавления
    return cnt;
}


int filter(int sz){
    if(!data)
        return ERROR;
    fil_data = (config*)malloc(sz*sizeof(config));
    if(!fil_data)
        return ERROR;
    size_t cnt = 0;
    time_t now = time(0);
    struct tm *local_tm = localtime(&now); // текущее время
    int half_year_sec = 31536000/2;
    // фильтрация по условию: установлены раньше чем полгода назад && ни разу не обновлялись
    for(size_t i = 0; i < sz; i++){
        if(mktime(&(data+i)->date_inst) >= mktime(&(data+i)->date_upd) && difftime(mktime(local_tm),mktime(&(data+i)->date_inst)) >= half_year_sec) {
            *(fil_data + cnt++) = *(data + i);
        }
    }// конец фильтра
    size_t j = 0;
    int borders[cnt];size_t index = 1;borders[0] = 0;
    // группировка по классам
    while(j != cnt){
        for(size_t i = j+1; i < cnt;i++) {
            if (*(fil_data + i)->class1 == *(fil_data + j)->class1) {
                config tmp = *(fil_data + j + 1);
                *(fil_data + j + 1) = *(fil_data + i);
                *(fil_data + i) = tmp;
                j++;
            }
        }j++;
        borders[index++] = j;
    }
    // ---- конец группировки ----
    // начало сортировки внутри класса
    for(size_t i = 1; i < index; i++){
        QuickSort(borders[i-1],borders[i]);
    }
    // конец сортировки внутри класса
    return cnt;
}


//(быстрая) сортировка по именам
void QuickSort(int a,int b){
    int l = a;
    int r = b-1;
    char* mid = (fil_data + (l+r)/2)->name;
    do{
        while(strcmp((fil_data + l)->name,mid) < 0)
            l++;
        while(strcmp((fil_data + r)->name,mid) >0)
            r--;
        if(l <= r){
            config tmp = *(fil_data + l);
            *(fil_data + l) = *(fil_data + r);
            *(fil_data + r) = tmp;
            l++,r--;
        }
    }while(l <= r);
    if(r > a)
        QuickSort(a,r);
    if(l < b-1)
        QuickSort(l,b);
}
//---конец сортировки---

//очистка динамически выделенной памяти
int delete1(int cnt){
    if(!data){
        return(ERROR);
    }
    for(int i = 0; i < cnt; i ++)
        free((data + i)->class1),free((data + i)->name);
    free(data);
    return(SUCCESS);
}
