#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit IN=P2^1;
sbit OUT=P2^0;
sbit led=P2^4;


void Delay100ms();	


void main() {
	int x=0;
	
	while(1){
	if(IN==1){
		Delay100ms();
   		if(IN==1){
   			x=x+1;
   		}
	}	
	if(OUT==1){
		Delay100ms();
   		if(OUT==1){
   			x=x-1;
   		}
	}

   		if(x==0){
   			led=1;//�ߵ�ѹϨ��led
   		}
		else{led=0;}//�͵�ѹ����led
	}
}

void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 52;
	k = 195;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}














