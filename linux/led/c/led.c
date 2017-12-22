#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>  //getenv();


#define led_num 20



static int fd = -1;
int def_num=2;

void delay(unsigned int mt) //延时函数
{
	unsigned int x,y;
	for(x=mt;x>0;x--)
	for(y=123;y>0;y--);
	
}


//void fx(int )
void fx(int x,int y)
{
		int i;
		int a=1;
		int s;
		i = x-1;
		for(i;i>0;i--){
				a =a*2;
		}
		x = 255-a;
		a =1;
		i=y-1;
		for(i;i>0;i--){
				a= a*2;
		}
		y =a;
		s = x*256+y;

		ioctl(fd,0,s);
}


//0
unsigned char tu01[16]={3,4,5,6,7,2,8,2,8,2,8,3,4,5,6,7};
unsigned char tu02[16]={3,3,3,3,3,4,4,5,5,6,6,7,7,7,7,7};
//1
unsigned char tu11[11] ={3,8,2,3,4,5,6,7,8,8,8};
unsigned char tu12[11] ={5,5,6,6,6,6,6,6,5,6,7};
//2
unsigned char tu21[17] ={3,6,7,8,2,6,8,2,6,8,2,6,8,3,4,5,8};
unsigned char tu22[17] ={3,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7};
//3
unsigned char tu31[16] ={3,7,2,5,8,2,5,8,2,5,8,3,4,5,6,7};
unsigned char tu32[16] ={3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,7};
//4
unsigned char tu41[14]={5,6,4,6,3,6,2,3,4,5,6,7,8,6};
unsigned char tu42[14]={3,3,4,4,5,5,6,6,6,6,6,6,6,7};
//5
unsigned char tu51[17]={2,3,4,7,2,4,8,2,4,8,2,4,8,2,5,6,7};
unsigned char tu52[17]={3,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7};
//6
unsigned char tu61[17]={3,4,5,6,7,2,5,8,2,5,8,2,5,8,3,6,7};
unsigned char tu62[17]={3,3,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7};
//7
unsigned char tu71[11]={2,2,2,2,5,6,7,8,2,3,4};
unsigned char tu72[11]={3,4,5,6,6,6,6,6,7,7,7};
//8
unsigned char tu81[17]={3,4,6,7,2,5,8,2,5,8,2,5,8,3,4,6,7};
unsigned char tu82[17]={3,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7};
//9
unsigned char tu91[17]={3,4,7,2,5,8,2,5,8,2,5,8,3,4,5,6,7};
unsigned char tu92[17]={3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,7};







void gx0()
{	
	int q=-4;   //实现字符漂流
	int k=0;
	int j=0;
	int i=0;
	while(1)
	{
		for(i=0;i<100;i++){        //
			for(j=0;j<16;j++){     //亮的点数
				k=tu02[j]-q;     //
				if(k<0 || k>8)
					continue;
				fx (tu01[j],k);
				usleep(200);
				//delay(200 + 10 * def_num);//延时//流动速度
				
			}
		}
		q++;
		if(q>8)
		{	
			q=-4;
			break;
		}
	}
}


void gx1()
{	
	int q=-4;
	int k=0;
	int j=0;
	int i=0;
	while(1)
	{
		for(i=0;i<100;i++){
			for(j=0;j<11;j++){
				k=tu12[j]-q;
				if(k<0 || k>8)
					continue;
				fx (tu11[j],k);
				usleep(200);
				//delay(200 + 10 * def_num);
			}
		}
		q++;
		if(q>8)
		{	
			q=-4;
			break;
		}
	}
}

void gx2()
{	
	int q=-4;
	int k=0;
	int j=0;
	int i=0;
	
	while(1)
	{
		for(i=0;i<100;i++){
			for(j=0;j< 17;j++){
				k=tu22[j]-q;
				if(k<0 || k>8)
					continue;
				fx (tu21[j],k);
				usleep(200);
				//delay(200 + 10 * def_num);
			}

		}
		q++;
		if(q>8)
		{
			q=-4;
			break;
		}
	}
}

void gx3()
{	
	int q=-4;
	int k=0;
	int j=0;
	int i=0;
	
	while(1)
	{
		for(i=0;i<100;i++){
			for(j=0;j<16;j++){
				k=tu32[j]-q;
				if(k<0 || k>8)
					continue;
				fx (tu31[j],k);
				usleep(200);
				//delay(200 + 10 * def_num);
			}
		}
		q++;
		if(q>8)
		{	q=-4;
			break;
		}
	}	
}

void gx4()
{	
	int q=-4;
	int k=0;
	int j=0;
	int i=0;
	

	while(1)
	{
		for(i=0;i<100;i++){
			for(j=0;j<14;j++){
				k=tu42[j]-q;
				if(k<0 || k>8)
					continue;
				fx (tu41[j],k);
				usleep(200);
				//delay(200 + 10 * def_num);
			}
		}
		q++;
		if(q>8)
		{
			q=-4;
			break;
		}
	}
}

void gx5()
{	
	int q=-4;
	int k=0;
	int j=0;
	int i=0;
	
	while(1)
	{
		for(i=0;i<100;i++){
			for(j=0;j<17;j++){
				k=tu52[j]-q;
				if(k<0 || k>8)
					continue;
				fx (tu51[j],k);
				usleep(200);
				//delay(200 + 10 * def_num);
			}
		}
		q++;
		if(q>8)
		{	q=-4;
			break;
		}
	}
}

void gx6()
{	
	int q=-4;
	int k=0;
	int j=0;
	int i=0;
	

	while(1)
	{
	for(i=0;i<100;i++){
		for(j=0;j<17;j++){
			k=tu62[j]-q;
			if(k<0 || k>8)
				continue;
			fx (tu61[j],k);
			usleep(200);
			//delay(200 + 10 * def_num);
		}
	}
	q++;
	if(q>8)
	{q=-4;
break;}
	}
}

void gx7()
{	
	int q=-4;
	int k=0;
	int j=0;
	int i=0;
	

	while(1)
	{
	for(i=0;i<100;i++){
		for(j=0;j<11;j++){
			k=tu72[j]-q;
			if(k<0 || k>8)
				continue;
			fx (tu71[j],k);
			usleep(200);
			//delay(200 + 10 * def_num);
		}
		
	
	}
	q++;
	if(q>8)
	{q=-4;
break;}
	}	

}

void gx8()
{	
	int q=-4;
	int k=0;
	int j=0;
	int i=0;
	

	while(1)
	{
	for(i=0;i<100;i++){
		for(j=0;j<17;j++){
			k=tu82[j]-q;
			if(k<0 || k>8)
				continue;
			fx (tu81[j],k);
			usleep(200);
			//delay(200 + 10 * def_num);
		}
	}
	q++;
	if(q>8)
	{q=-4;
break;}
	}
}

void gx9()
{	
	int q=-4;
	int k=0;
	int j=0;
	int i=0;

	while(1)
	{
	for(i=0;i<100;i++){
		for(j=0;j<17;j++){
			k=tu92[j]-q;
			if(k<0 || k>8)
				continue;
			fx (tu91[j],k);
			usleep(200);
			//delay(200 + 10 * def_num);
		}

	}
	q++;
	if(q>8)
	{q=-4;
break;}
	}
}


void py(char value,int speed){
	int count=0;
	switch(value){
	case '0':
		gx0();
		break;
	case '1':
		gx1();
		break;
	case '2':
		gx2();
		break;
	case '3':
		gx3();
		break;
	case '4':
		gx4();
		break;
	case '5':
		gx5();
		break;
	case '6':
		gx6();
		break;
	case '7':
		gx7();
		break;
	case '8':
		gx8();
		break;
	case '9':
		gx9();
		break;
	default:
		break;

	}

	if(count >= speed)
				{
					count=0;
					
				}
				else
					count++; //控制流动速度
				usleep(10000 + 1000 * speed);
}



int main()
{
	
	int i=0;
	int temp,count;
	int len;
	//int def_num=1; //流动速率
	char *data;
	char m[20];
	char n[20];

	printf("Content-type:text/html;charset=utf-8\n\r\n");
	printf("<title>post method </title>\n");
	printf("%d  %s \n",__LINE__,__func__);
	data=getenv("QUERY_STRING");	
	printf("param:%s <br />", data);
	if(data == NULL){
		printf("<p> 数据传输有误！！");
	}else{
		printf("%d  %s \n",__LINE__,__func__);
		if(sscanf(data,"text=%[^&]&sudu=%s",m,n)!=2)
		{
		
			printf("<p> 表单提取错误！！");
		}
		else
		{	printf("<p>");
			printf("m=%s,n=%s",m,n);		
			printf("</p>");	
			def_num=atoi(n);  //获取速度值
			len = strlen(m);
			for(i=0;i < len;i++)
			{
				if(!(m[i] <= '9' && m[i] >= '0'))
				{
						printf("<p> 输入数据非法！！\n");
						return -1;
				}	

			}
				
			

		}		

printf("%d  %s \n",__LINE__,__func__);
	
			

		fd=open("/dev/matrixled",O_RDWR);
		if(fd<0)
		{
printf("%d  %s \n",__LINE__,__func__);
			printf("Can't open\n");
			return -1;
		}
		else
		{
			printf("open OK 11%x\n", fd);
		}
		
printf("%d  %s \n",__LINE__,__func__);
		while(1)
		{
			
printf("%d  %s \n",__LINE__,__func__);
			for(i=0;i < len;i++)
			{
printf("%d  %s \n",__LINE__,__func__);
				py(m[i],def_num);	
			}
		printf("%d  %s \n",__LINE__,__func__);
			if(temp >= (len-1)) //循环播放
				temp=0;
			else
				temp++;
				
		}


	}


printf("%d  %s \n",__LINE__,__func__);

   	close(fd);
  	return 0;

}


 
