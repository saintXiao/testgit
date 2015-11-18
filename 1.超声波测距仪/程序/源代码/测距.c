 #include<reg51.h>
#include<math.h>
/*定义数据类型*/
#define uint unsigned int
#define uchar unsigned char
/*定义系统常数*/
long int  time;      /*    时间   */
bit   CLflag;   /*  测量标志  */
char  cshu;       /* 串数 */
#define  T12us   (256-12)    /*定时器设初值   T=（256-T12us）*12/12MHZ  */
sbit VOLCK=P1^0;    /* 发射 */
//接收从P3^2口输入，采用外部中断方式

sbit S1=P2^1;
sbit S2=P2^3;
sbit S3=P2^5;
sbit S4=P2^7;

sbit alam=P3^7;					//报警

unsigned char  number[5];      /* 用于存放距离显示数据 */
unsigned char  temp_number[5];

unsigned char fr_alam;      //报警频率控制计数
unsigned char icont;		//距离计数

char  code table[] ={0x5F,0x44,0x9D,0xD5,0xC6,0xD3,0xDB,0x45,0xDF,0xD7}; //数字0-9的编码
//{0x03,0x9f,0x25,0x0d,0x99,0x49,0x41,0x1f,0x01,0x09};
                /* 码表 0,1,2,3,4,5,6,7,8,9 */

/*    通用延时子程序  */
void delay( int j)
{
	int i;
	for(i=0;i<j;i++);
}

void display(void)     /*  显示5位数据   */
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

/*  初始化定时器,CTC0、CTC1用于定时     */
void   init_CTC(void )
{
	TMOD = 0x21;      /*  设CTC1工作于模式2 */
	ET0 = 0;              /* 不允许CTC0中断  */
}

void init_INT( )    /*  外部中断初始化为高优先级，并开中断  */
{
	IP=0x01;   /*  置外部中断INT0优先级为高   */
	TCON=0;   /*  设置外部中断0的中断方式为电平触发  */
}

//=========距离与频率之间的转化==============
void Distance_Frequency(void)
{
	//以下语句用于计算距离与报警的频率大小
	if(number[3]>0)		//表示距离大于1米时，不报警
		icont=0;
	else				//否则
	{
		if(number[2]>0)		//小于1米时，但分米大于0时，报警频率与分米的数据成正比
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
		else 					//距离只在厘米时，高频率输出报警
		{
			if(number[1]>0)
				icont=1;
			else
				icont=0;
		}
	}
}

void Timetojuli(void)   /*   将测量的时间转换为距离 */
{
	long  i;
	i=(long)time*170;
	temp_number[4]=i/10000000;     /* 十米  */
	i=i-temp_number[4]*10000000;
	temp_number[3]=i/1000000;   /*  米  */
	i=i-temp_number[3]*1000000;
	temp_number[2]=i/100000;    /*  分米  */
	i=i-temp_number[2]*100000;
	temp_number[1]=i/10000;     /*  厘米  */
	i=i-(long)temp_number[1]*10000;
	temp_number[0]=i/1000;     /*  毫米  */
 	//以下用于控制是否测到距离，如全为0，表明没有测到距离
	if((temp_number[4]!=0)||(temp_number[3]!=0)||(temp_number[2]!=0)||(temp_number[1]!=0))
	{
		number[4]=temp_number[4];   //更新一次数据
		number[3]=temp_number[3];
		number[2]=temp_number[2];
		number[1]=temp_number[1];
		number[0]=temp_number[0];

		Distance_Frequency();		//转化一次
	}
}

void serve_INT0( ) interrupt 0
{
	/*  外部中断0，用于检测接收信号  */
	TR0=0;       /*  关闭定时器0 */
	EX0=0;       /* 关中断  */
	time=(long)TL0;
	time+=(long)TH0*256;
	Timetojuli();					//更新一次数据
	CLflag=1;
	TH0=0;
	TL0=0;
}
void CTC0_INT (  )   interrupt  1
{
	TR0=0;
	ET0=0;
}

/*  CTC1中断服务程序，12.5us 中断一次,用于发射  */
void CTC1_INT (  )   interrupt  3
{
	VOLCK=~VOLCK;
	cshu++;
}

/*主程序*/
void main()
{
	init_CTC(  );      		/*   初始化定时器 */
	init_INT(  );      		/* 初始化外部中断  */
	CLflag=1;         		/*    测量标志    */
	cshu=0;          		/*  传数 */
	IE=0x80;           		/* 开中断  */
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
		TL0 = 0;     TH0 = 0;    	/*  定时器0的初始时间 */
		VOLCK=0;
		TR1=1;       			 	/*  启动定时器1，发送信号  */
		while(cshu<20) ;		    /*  发10个脉冲串 */
		TR1=0;
		TR0=1;           			/*  启动定时器0，开始记时  */
		EX0=1;
		display();					//调用显示
	//	Distance_Frequency();		//调用距离频率转化程序
		fr_alam++;	//程序执行次数加1	用于控制报警频率与距离成正比
		if(icont>0)				//表示距离控制位达到报警时
		{
			if(fr_alam>=icont)
			{
				fr_alam=0;
				alam=~alam;		//蜂鸣器取反一次，即响一声
			}
		}
		else						//不报警时
		{
			alam=1;
		}
	}
}
