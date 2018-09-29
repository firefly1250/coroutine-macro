#include <stdio.h>

typedef unsigned long uint32_t;

#define coroutine_period 10

#define coroutine_begin \
 static uint32_t __state = 0; \
 static uint32_t __counter=0; \
 switch(__state){ \
 case 0:

 #define coroutine_begin_with(state,counter) \
 static uint32_t& __state = state; \
 static uint32_t& __counter = counter; \
 switch(__state){ \
 case 0:

#define coroutine_yield \
 __state = __LINE__; \
 return; \
 case __LINE__: while(0);

#define coroutine_end \
 __state = __LINE__; \
 }

 #define coroutine_delay(time) \
 for(;__counter<time; __counter+=coroutine_period){ \
 coroutine_yield; \
 } \
 __counter=0;


void func(){
    coroutine_begin{
        static int i=0;
        for(;i<2;i++){
            printf("poyo%d\n",i);
            coroutine_delay(50);
        }
        i=0;
        printf("end\n");
    }coroutine_end;
}

 int main(){
     for(int i=0;i<20;i++){
         printf("%d\n",i);
         func();
     }
 }