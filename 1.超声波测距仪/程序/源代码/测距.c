 #include<reg51.h>
#include<math.h>
/*������������*/
#define uint unsigned int
#define uchar unsigned char
/*����ϵͳ����*/
long int  time;      /*    ʱ��   */
bit   CLflag;   /*  ������־  */
char  cshu;       /* ���� */
#define  T12us   (256-12)    /*��ʱ�����ֵ   T=��256-T12us��*12/12MHZ  */
sbit VOLCK=P1^0;    /* ���� */
//���մ�P3^2�����룬�����ⲿ�жϷ�ʽ

sbit S1=P2^1;
sbit S2=P2^3;
sbit S3=P2^5;
sbit S4=P2^7;

sbit alam=P3^7;					//����

unsigned char  number[5];      /* ���ڴ�ž�����ʾ���� */
unsigned char  temp_number[5];

unsigned char fr_alam;      //����Ƶ�ʿ��Ƽ���
unsigned char icont;		//�������

char  code table[] ={0x5F,0x44,0x9D,0xD5,0xC6,0xD3,0xDB,0x45,0xDF,0xD7}; //����0-9�ı���
//{0x03,0x9f,0x25,0x0d,0x99,0x49,0x41,0x1f,0x01,0x09};
                /* ��� 0,1,2,3,4,5,6,7,8,9 */

/*    ͨ����ʱ�ӳ���  */
void delay( int j)
{
	int i;
	for(i=0;i<j;i++);
}

void display(void)     /*  ��ʾ5λ����   */
{
	P0=~table[number[4]];
	S1=0;
	delay(200);
	S1=1;
	P0=~(table[number[3]]|0x20);
	S2=0;
	delay(200);
	S2=1;
	P0=~table[number[2]];
	S3=0;
	delay(200);
	S3=1;
	P0=~table[number[1]];
	S4=0;
	delay(200);
	S4=1;
}

/*  ��ʼ����ʱ��,CTC0��CTC1���ڶ�ʱ     */
void   init_CTC(void )
{
	TMOD = 0x21;      /*  ��CTC1������ģʽ2 */
	ET0 = 0;              /* ������CTC0�ж�  */
}

void init_INT( )    /*  �ⲿ�жϳ�ʼ��Ϊ�����ȼ��������ж�  */
{
	IP=0x01;   /*  ���ⲿ�ж�INT0���ȼ�Ϊ��   */
	TCON=0;   /*  �����ⲿ�ж�0���жϷ�ʽΪ��ƽ����  */
}

//=========������Ƶ��֮���ת��==============
void Distance_Frequency(void)
{
	//����������ڼ�������뱨����Ƶ�ʴ�С
	if(number[3]>0)		//��ʾ�������1��ʱ��������
		icont=0;
	else				//����
	{
		if(number[2]>0)		//С��1��ʱ�������״���0ʱ������Ƶ������׵����ݳ�����
		{
		    switch(number[2])
			{
				case 9: icont=9; break;
				case 8: icont=8; break;
				case 7: icont=7; break;
				case 6: icont=6; break;
				case 5: icont=5; break;
				case 4: icont=4; break;
				case 3: icont=3; break;
				case 2: icont=2; break;
				case 1: icont=1; break;
				default: break;
			}
		}
		else 					//����ֻ������ʱ����Ƶ���������
		{
			if(number[1]>0)
				icont=1;
			else
				icont=0;
		}
	}
}

void Timetojuli(void)   /*   ��������ʱ��ת��Ϊ���� */
{
	long  i;
	i=(long)time*170;
	temp_number[4]=i/10000000;     /* ʮ��  */
	i=i-temp_number[4]*10000000;
	temp_number[3]=i/1000000;   /*  ��  */
	i=i-temp_number[3]*1000000;
	temp_number[2]=i/100000;    /*  ����  */
	i=i-temp_number[2]*100000;
	temp_number[1]=i/10000;     /*  ����  */
	i=i-(long)temp_number[1]*10000;
	temp_number[0]=i/1000;     /*  ����  */
 	//�������ڿ����Ƿ�⵽���룬��ȫΪ0������û�в⵽����
	if((temp_number[4]!=0)||(temp_number[3]!=0)||(temp_number[2]!=0)||(temp_number[1]!=0))
	{
		number[4]=temp_number[4];   //����һ������
		number[3]=temp_number[3];
		number[2]=temp_number[2];
		number[1]=temp_number[1];
		number[0]=temp_number[0];

		Distance_Frequency();		//ת��һ��
	}
}

void serve_INT0( ) interrupt 0
{
	/*  �ⲿ�ж�0�����ڼ������ź�  */
	TR0=0;       /*  �رն�ʱ��0 */
	EX0=0;       /* ���ж�  */
	time=(long)TL0;
	time+=(long)TH0*256;
	Timetojuli();					//����һ������
	CLflag=1;
	TH0=0;
	TL0=0;
}
void CTC0_INT (  )   interrupt  1
{
	TR0=0;
	ET0=0;
}

/*  CTC1�жϷ������12.5us �ж�һ��,���ڷ���  */
void CTC1_INT (  )   interrupt  3
{
	VOLCK=~VOLCK;
	cshu++;
}

/*������*/
void main()
{
	init_CTC(  );      		/*   ��ʼ����ʱ�� */
	init_INT(  );      		/* ��ʼ���ⲿ�ж�  */
	CLflag=1;         		/*    ������־    */
	cshu=0;          		/*  ���� */
	IE=0x80;           		/* ���ж�  */
	ET1=1;       ET0=1;
	TR1=0;       TR0=0;
	TL1=T12us;   TH1=T12us;
	while(1)
	{
		CLflag=0;
		cshu=0;
		EX0=0;
		TH1=T12us;
		TL1=T12us;
		TL0 = 0;     TH0 = 0;    	/*  ��ʱ��0�ĳ�ʼʱ�� */
		VOLCK=0;
		TR1=1;       			 	/*  ������ʱ��1�������ź�  */
		while(cshu<20) ;		    /*  ��10�����崮 */
		TR1=0;
		TR0=1;           			/*  ������ʱ��0����ʼ��ʱ  */
		EX0=1;
		display();					//������ʾ
	//	Distance_Frequency();		//���þ���Ƶ��ת������
		fr_alam++;	//����ִ�д�����1	���ڿ��Ʊ���Ƶ������������
		if(icont>0)				//��ʾ�������λ�ﵽ����ʱ
		{
			if(fr_alam>=icont)
			{
				fr_alam=0;
				alam=~alam;		//������ȡ��һ�Σ�����һ��
			}
		}
		else						//������ʱ
		{
			alam=1;
		}
	}
}
