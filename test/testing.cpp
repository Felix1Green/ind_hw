#include "gtest/gtest.h"

extern "C" {
#include "../include/configure.h"
}
FILE* t;


TEST(QuickSort,ok){
    if (!(t = fopen("../../test/files/sort_test.txt", "r")))
        printf("\nFILE ERROR\n");
    int cnt = add(t);
    int size = filter(cnt);
    char* exp_str[5] ={(char*)"abs",(char*)"bc",(char*)"clion",(char*)"as",(char*)"root"};
    for(int i = 0; i < 5; i++){
        EXPECT_EQ(strcmp((fil_data+i)->name,exp_str[i]),0);
    }
    delete1(cnt);
    if(fil_data)
        free(fil_data);
}

TEST(input_str,ok){
    if(!(t = fopen("../../test/files/input_test.txt","r")))
        printf("\nFILE ERROR\n");
    char* ex_str = (char*)"hi,friend.";
    char* ans = input_str(t);
    EXPECT_EQ(strcmp(ans,ex_str),0);
    if(ans)free(ans);
}


TEST(input_int,not_ok){
    if(!(t = fopen("../../test/files/input_test.txt","r")))
        printf("\nFILE ERROR\n");
    EXPECT_EQ(input_int(t),-1);
}

TEST(input_int,ok){
    if(!(t = fopen("../../test/files/input_int_test.txt","r")))
        printf("\nFILE ERROR\n");
    EXPECT_EQ(input_int(t),15);
}

TEST(input_date,ok){
    if(!(t = fopen("../../test/files/input_date.txt","r")))
        printf("\nFILE ERROR\n");
    int a[3] = {12,5,2019};
    int* res = input_date(t);
    EXPECT_EQ(res[0],a[0]);
    EXPECT_EQ(res[1],a[1]);
    EXPECT_EQ(res[2],a[2]);
    if(res)free(res);
}

TEST(print,not_ok){
    fil_data = NULL;
    EXPECT_EQ(print(0),-1);
}

TEST(add,ok){
    if(!(t = fopen("../../test/files/sort_test.txt","r")))
        printf("\nFILE ERROR\n");
    int cnt = add(t);
    EXPECT_EQ(cnt,5);
    delete1(cnt);
}

TEST(add,not_ok){
    if(!(t = fopen("../../test/files/add_test.txt","r")))
        printf("\nFILE ERROR\n");
    int cnt = add(t);
    EXPECT_EQ(cnt,4);
    delete1(cnt);
}

TEST(filter,not_ok){
    data = NULL;
    EXPECT_EQ(filter(0),-1);
}

TEST(filter,ok){
    if(!(t = fopen("../../test/files/sort_test.txt","r")))
        printf("\nFILE ERROR\n");
    data = NULL;
    int cnt = add(t);
    EXPECT_EQ(filter(cnt),5);
    delete1(cnt);
    if(fil_data)free(fil_data);
}

TEST(delete1,ok){
    if(!(t = fopen("../../test/files/sort_test.txt","r")))
        printf("\nFILE ERROR\n");
    data = NULL;
    int cnt = add(t);
    EXPECT_EQ(delete1(cnt),0);
}

TEST(delete1,not_ok){
    data = NULL;
    EXPECT_EQ(delete1(0),-1);
}