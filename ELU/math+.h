#ifndef __mathPlus__
#define __mathPlus__

#include<math.h>
#include<stdlib.h>
#include<time.h>

#define ReLU(x) ((long double)((long double)(x)>0?(x):0))
#define LReLU(x) ((long double)((long double)(x)>0?(x):(long double)(x)*0.0001))	//Leaky ReLU
#define ELU_C 1L
#define ELU(x) ((long double)((x)>0?(x):ELU_C*(exp(x)-1)))

long double randl(long double min, long double max){
	static unsigned int a;
	struct timeval tv;
	mingw_gettimeofday(&tv,NULL);
	srand((long long)tv.tv_sec*1000000+tv.tv_usec+a&0xFFFFFFFF);
	return (long double)((long long)(a=rand())*RAND_MAX*RAND_MAX+rand()*RAND_MAX+rand())*(max-min)/RAND_MAX/RAND_MAX/RAND_MAX+min;
}
long double sigmoid(long double x){return 1L/(1L+expl(-x));}

#endif//__mathPlus__