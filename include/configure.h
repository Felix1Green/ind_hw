//
// Created by felix on 09.03.2020.
//

#ifndef IZ_CONFIGURE_H
#define IZ_CONFIGURE_H

//основная структура продукта
struct config{
    char* name;
    char* class1;
    int version;
    struct tm date_inst,date_upd;
}* data,*fil_data;
typedef struct config config;



int* input_date(FILE*);
char* input_str(FILE*);
int input_int(FILE*);
int print(int);
int add(FILE*);
int filter(int);
int delete1(int);
void QuickSort(int,int);
#endif //IZ_CONFIGURE_H
