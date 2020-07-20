/*************************************************************************
	> File Name: mytest.h
	> Author: 
	> Mail: 
	> Created Time: Wed 08 Jul 2020 09:03:51 PM CST
 ************************************************************************/

#include <cstring>
#include <sys/timeb.h>

#ifndef _MYTEST_H
#define _MYTEST_H

#define EXPECT(a, comp, b) { \
    if (!((a) comp (b)))\
        expect_printf(__FILE__, __LINE__,  \
         "((" #a ") " #comp " (" #b "))"); \
}

#define EXPECT_EQ(a, b) EXPECT(a, ==, b)
#define EXPECT_NE(a, b) EXPECT(a, !=, b)
#define EXPECT_GT(a, b) EXPECT(a, >, b)
#define EXPECT_GE(a, b) EXPECT(a, >=, b)
#define EXPECT_LT(a, b) EXPECT(a, <, b)
#define EXPECT_LE(a, b) EXPECT(a, <=, b)


#define COLOR(msg, code) "\033[" #code "m" msg "\033[0m"

#define GREEN(msg) COLOR (msg,32)
#define YELLOW(msg) COLOR(msg, 33)
#define BLUE(msg) COLOR(msg, 34)
#define RED(msg) COLOR(msg, 35)


#define TEST(a,b)\
void a##_##b();\
__attribute__((constructor))\
void register_##a##_##b() {\
    add_test(a##_##b, #a "." #b); \
}\
void a##_##b()

struct TestData {
    void (*func)();
    char *func_name;
    
}func_arr[100];

int flag=0;

int func_cnt = 0;

void add_test(void (*func)(), const char *func_name) {
    func_arr[func_cnt].func = func;
    func_arr[func_cnt].func_name= strdup(func_name);
    func_cnt+=1;
    return;
}

void expect_printf(const char *file_name, int line_no, const char *msg) {
        printf(YELLOW("\t%s : %d : Failure\n"), file_name, line_no);
        printf(YELLOW("\t\t%s\n"), msg);
    flag =1;
  
        return ;

}



int RUN_ALL_TESTS() {
    printf(GREEN("[==========]") "Running %d tests\n",func_cnt);
    for(int i=0; i<func_cnt;i++) 
    {
        flag = 0;
        printf(GREEN("[  RUN     ]")"%s\n",func_arr[i].func_name);
        
        timeb ts1,ts2;
        time_t time;
        ftime(&ts1);

        func_arr[i].func();
        
        ftime(&ts2);
        //printf("%ld %ld \n",ts1,ts2);
        time=(ts2.time-ts1.time) *1000+ (ts2.millitm-ts1.millitm);

        
        if(flag !=0) {
            printf(RED("[  FAILED  ]") "%s (%ld ms)\n",func_arr[i].func_name,time);
        }else {
            printf(GREEN("[   OK     ]") "%s (%ld ms)\n", func_arr[i].func_name,time);
        }
    }
    return 0;
}

#endif

