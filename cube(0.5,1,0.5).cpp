#include <graphics.h>
#include <iostream>
#include <math.h>
#include <dos.h>
using namespace std;
int multi(float *, float *, float *);
int add(float *, float *, float *);
int identity(float *);
int identity(float *trans[])
{
	int i, j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(i==j)
			{
				trans[i][j]=1;
			}
			else
			{
				trans[i][j]=0;
			}
		}			
	}
}
int multi(float *trans[], float *vec, float *output)
{
	int i, j;
	for(i=0;i<3;i++)
	{
		output[i]=0;
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			output[i]=output[i]+trans[i][j]*vec[j];
		}
	}
	return 0;
}
int add(float *m, float *n, float *p)
{
	int i;
	for(i=0;i<3;i++)
	{
		p[i]=m[i]+n[i];
	}
	return 0;
}
int main()
{
	int gd = DETECT, gm, color;
	initgraph(&gd, &gm, (char*)"");
	float points[8][3], plot[8][2], *p1[8], *p2[3], *p3[8], trans[3][3], x, y, output[8][3];
	int i, j, temp, count;
	x=0;
	y=0;
	count=0;
	//x=asin(2/sqrt(5));
	//y=-asin(1/sqrt(6));
	cout<<x<<endl;
	cout<<y<<endl;
	for(i=0;i<8;i++)
	{
		temp=i;
		p1[i]=&points[i][0];
		p3[i]=&output[i][0];
		for(j=0;j<3;j++)
		{
			points[i][j]=temp%2;
			temp=temp/2;
		}
	}
	for(i=0;i<8;i++)
	{
		for(j=0;j<3;j++)
		{
			cout<<points[i][j]<<"\t";
		}
		cout<<endl;
	}
	//transforming...
	//let's rotate!!!!!
	for(i=0;i<3;i++)
	{
		p2[i]=&trans[i][0];
	}
	while(x<=asin(2/sqrt(5)))
	{
		cleardevice();
		count=count+1;
		trans[0][0]=cos(y);
		trans[0][1]=sin(x)*sin(y);
		trans[0][2]=cos(x)*sin(y);
		trans[1][0]=0;
		trans[1][1]=cos(x);
		trans[1][2]=-sin(x);
		trans[2][0]=-sin(y);
		trans[2][1]=sin(x)*cos(y);
		trans[2][2]=cos(x)*cos(y);
		for(i=0;i<8;i++)
		{
			multi(p2, p1[i], p3[i]);
		}
		cout<<"Wait"<<endl;
		for(i=0;i<8;i++)
		{
			for(j=0;j<3;j++)
			{	
				cout<<output[i][j]<<"\t";
			}
			cout<<endl;
		}
		x=x+0.01*2.63271896;
		y=y-0.01;
		//axes
		line(2*980/3+1000*output[0][0], 2*540/3-1000*output[0][1], 2*980/3+1000*output[1][0], 2*540/3-1000*output[1][1]);
		line(2*980/3+1000*output[0][0], 2*540/3-1000*output[0][1], 2*980/3+1000*output[2][0], 2*540/3-1000*output[2][1]);
		line(2*980/3+1000*output[0][0], 2*540/3-1000*output[0][1], 2*980/3+1000*output[4][0], 2*540/3-1000*output[4][1]);
		//cube
		line(2*980/3+100*output[0][0], 2*540/3-100*output[0][1], 2*980/3+100*output[1][0], 2*540/3-100*output[1][1]);
		line(2*980/3+100*output[0][0], 2*540/3-100*output[0][1], 2*980/3+100*output[2][0], 2*540/3-100*output[2][1]);		
		line(2*980/3+100*output[0][0], 2*540/3-100*output[0][1], 2*980/3+100*output[4][0], 2*540/3-100*output[4][1]);
		line(2*980/3+100*output[1][0], 2*540/3-100*output[1][1], 2*980/3+100*output[3][0], 2*540/3-100*output[3][1]);
		line(2*980/3+100*output[1][0], 2*540/3-100*output[1][1], 2*980/3+100*output[5][0], 2*540/3-100*output[5][1]);
		line(2*980/3+100*output[2][0], 2*540/3-100*output[2][1], 2*980/3+100*output[3][0], 2*540/3-100*output[3][1]);
		line(2*980/3+100*output[2][0], 2*540/3-100*output[2][1], 2*980/3+100*output[6][0], 2*540/3-100*output[6][1]);
		line(2*980/3+100*output[3][0], 2*540/3-100*output[3][1], 2*980/3+100*output[7][0], 2*540/3-100*output[7][1]);
		line(2*980/3+100*output[4][0], 2*540/3-100*output[4][1], 2*980/3+100*output[5][0], 2*540/3-100*output[5][1]);
		line(2*980/3+100*output[4][0], 2*540/3-100*output[4][1], 2*980/3+100*output[6][0], 2*540/3-100*output[6][1]);
		line(2*980/3+100*output[5][0], 2*540/3-100*output[5][1], 2*980/3+100*output[7][0], 2*540/3-100*output[7][1]);
		line(2*980/3+100*output[6][0], 2*540/3-100*output[6][1], 2*980/3+100*output[7][0], 2*540/3-100*output[7][1]);
		if(count==1)
		{
			delay(5000);
		}
		delay(10);
	}
	cout<<"The value of x: "<<x<<endl;
	cout<<"The value of y: "<<y<<endl;
	delay(50000);
}
