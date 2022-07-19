#ifndef __perceptron__
#define __perceptron__

#include"math+.h"

typedef struct Perceptron{
	long double b,eta;
	long double*w;
	int n;
}Perceptron;

void _00(Perceptron*inst, int numOfWeights,long double learningRate){
	inst->n=numOfWeights;
	inst->eta=learningRate;
	inst->w=(long double*)malloc(inst->n*sizeof(long double));
	int i;
	for(i=0;i<inst->n;i++)do{inst->w[i]=randl(-1,1);}while(inst->w[i]==0);
	do{inst->b=randl(-1,1);}while(inst->b==0);
}
void _01(Perceptron* inst){free(inst->w);}
long double _02(Perceptron* inst, long double*input){
	int i;
	long double s=0;
	for(i=0;i<inst->n;i++){
		// printf("%Lf %Lf\n",inst->w[i],input[i]);
		s+=inst->w[i]*input[i];
	}
	return sigmoid(s+inst->b);
}
long double _03(Perceptron* inst, int numOfData, long double*data){//{{x0,x1,x2,...,x(n-1),y}0,{x0,x1,x2,...,x(n-1),y}1,...}
	int i,j,k,n=inst->n;
	long double s,s_,e=0,t;
	long double tmp[n];
	for(k=0;k<n;k++){
		for(i=t=0;i<numOfData;i++){
			for(s=j=0;j<n;j++)s+=inst->w[j]*data[i*(n+1)+j];
			s+=inst->b;
			s=expl(s);
			s=-s*((data[i*(n+1)+n]-1)*s+data[i*(n+1)+n])*data[i*(n+1)+k] / ((s+1)*(s+1)*(s+1));
			t+=s;
		}
		// fprintf(flog,"R : %Lf\t",inst->eta*s/numOfData);
		e+=t*=inst->eta/numOfData;
		tmp[k]=inst->w[k]-t;
	}
	for(i=t=0;i<numOfData;i++){
		for(s=j=0;j<n;j++)s+=inst->w[j]*data[i*(n+1)+j];
		s+=inst->b;
		s=expl(s);
		s=-s*((data[i*(n+1)+n]-1)*s+data[i*(n+1)+n]) / ((s+1)*(s+1)*(s+1));
		t+=s;
	}
	// fprintf(flog,"%Lf\n",inst->eta*t/numOfData);
	e+=t*=inst->eta/numOfData;
	inst->b-=t;
	for(i=0;i<n;i++)inst->w[i]=tmp[i];
	return e/(n+1);
}
long double _04(Perceptron* inst, int numOfData, long double*data){
	int i,j,n=inst->n;
	long double s,t;
	for(i=t=0;i<numOfData;i++){
		s=_02(inst,data+i*(n+1))-data[i*(n+1)+n];
		t+=s*s;
	}
	return t/numOfData;
}

static struct{
	void (*init)(Perceptron*,int,long double);
	void (*destroy)(Perceptron*);
	long double (*calc)(Perceptron*,long double*input);
	long double (*train)(Perceptron*,int,long double*);
	long double (*mae)(Perceptron*,int,long double*);
}pct={_00,_01,_02,_03,_04};

#endif//__perceptron__
