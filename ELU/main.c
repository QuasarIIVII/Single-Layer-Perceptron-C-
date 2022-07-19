#include<stdio.h>
#define printf __mingw_printf
#define fprintf __mingw_fprintf
FILE*flog;
#include<conio.h>
#include<windows.h>
#include"perceptron.h"

int main(){
	flog=fopen("W:\\A\\log.log","w");
	int c;
	scanf("%d",&c);
	Perceptron a;
	pct.init(&a,2,0.01);
	printf("%Lf %Lf %p %d\n",a.b,a.eta,a.w,a.n);
	// long double 
	long double trainData[][3]={
		{0,0,0},
		{0,1,1},
		{1,0,1},
		{1,1,1},
	};
	// printf("A");
	// printf("%p\n",trainData);
	int i=0,j;
	long double e;
	for(i=0;i<c;i++){
		pct.train(&a,4,(void*)trainData);
		e=pct.mae(&a,4,(void*)trainData);
		// fprintf(flog,"%Lfx+%Lf\n",a.w[0],a.b);
		// fprintf(flog,"E : %Lf\n",e);
		if(fabs(e)<0.0001){
			fprintf(flog,"Br\n");
			break;
		}
		// fprintf(flog,"%Lf %Lf\n",a.b,a.w[0]);
	}
	for(i=0;i<a.n;i++)fprintf(flog,"%Lfx%d + ",a.w[i],i+1);fprintf(flog,"%Lf\n",a.b);
	// printf("%Lfx+%Lf\n",a.w[0],a.b);
	fprintf(flog,"%Lf\n",pct.calc(&a,(long double[]){0,0}));
	fprintf(flog,"%Lf\n",pct.calc(&a,(long double[]){0,1}));
	fprintf(flog,"%Lf\n",pct.calc(&a,(long double[]){1,0}));
	fprintf(flog,"%Lf",pct.calc(&a,(long double[]){1,1}));
	
	pct.destroy(&a);
	return 0;
}