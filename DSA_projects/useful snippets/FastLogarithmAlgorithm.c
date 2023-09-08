#include <stdio.h>

#define logbase10e 0.4342944819
#define logbase102 0.3010299957

float logApprox( float x, int terms){
    x = 1 - x;
    float log = 0;
    for(int i = terms; i > 0; --i){
        log = log*x + (x/i);
    }
    log=-1*log;
    return log;
}

float Log10(float num){
    int NUM;
    NUM=*(int*) &num;

    float mant=((float)(NUM&0x7FFFFF))/(1<<23)+1.0f;
    

    int exp=((NUM>>23)&0xFF)-127;

    float log = (logApprox(mant,100)*logbase10e +logbase102*((float) exp));

    return log;
}

int main(){
    float num=123.4;

    printf("log base 10 of %.1f is %f",num,Log10(num));
}