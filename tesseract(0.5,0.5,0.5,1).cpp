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
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
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
	for(i=0;i<4;i++)
	{
		output[i]=0;
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			output[i]=output[i]+trans[i][j]*vec[j];
		}
	}
	return 0;
}
int add(float *m, float *n, float *p)
{
	int i;
	for(i=0;i<4;i++)
	{
		p[i]=m[i]+n[i];
	}
	return 0;
}
int main()
{
	int gd = DETECT, gm, color;
	initgraph(&gd, &gm, (char*)"");
	float trans[4][4], vec[4], output[16][4], points[16][4], adjust[4], theta, x, y, z, m, trans1[4][4], output2[16][4], u, v, output1[16][4];
	int i, j, temp, count[8], cubicface[8][8], cont=0, p;
	float *p1[4], *p2, *p3[16], *p4[16], *p5, *p6[16], *p7[16];
	x=asin(-1/sqrt(5));
	y=asin(-1/sqrt(6));
	z=asin(-1/sqrt(7));
	u=asin(2/sqrt(5));
	v=-asin(1/sqrt(6));
	m=0;
	for(i=0;i<8;i++)
	{
		count[i]=0;
	}
	for(i=0;i<4;i++)
	{
		//vec[i]=i+3;
		p1[i]=&trans[i][0];
		adjust[i]=-0.5;
	}
	identity(p1);
	cout<<"Your transformation matrix sir: "<<endl;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			cout<<trans[i][j]<<"\t";
		}
		cout<<endl;
	}
	p2=&vec[0];
	p5=&adjust[0];
	for(i=0;i<16;i++)
	{
		temp=i;
		p4[i]=&points[i][0];
		p3[i]=&output[i][0];
		p6[i]=&output2[i][0];
		p7[i]=&output1[i][0];
		for(j=0;j<4;j++)
		{
			points[i][j]=temp%2;
			temp=temp/2;
		}
	}
	cout<<"Your points matrix sir: "<<endl;
	for(i=0;i<16;i++)
	{
		for(j=0;j<4;j++)
		{
			cout<<points[i][j]<<"\t";
		}
		cout<<endl;
	}
	//let's take w=1 plane and find the midpoint of this thing the midpoint I think is (1/2,1/2,1/2,1)
	cout<<"WAIT WAIT WAIT!..."<<endl<<endl<<endl;
	trans[0][0]=cos(z);
	trans[0][1]=-sin(y)*sin(z);
	trans[0][2]=-sin(x)*cos(y)*sin(z);
	trans[0][3]=cos(x)*cos(y)*sin(z);
	trans[1][0]=0;
	trans[1][1]=cos(y);
	trans[1][2]=-sin(x)*sin(y);
	trans[1][3]=cos(x)*sin(y);
	trans[2][0]=0;
	trans[2][1]=0;
	trans[2][2]=cos(x);
	trans[2][3]=sin(x);
	trans[3][0]=-sin(z);
	trans[3][1]=-sin(y)*cos(z);
	trans[3][2]=-sin(x)*cos(y)*cos(z);
	trans[3][3]=cos(x)*cos(y)*cos(z);
	for(i=0;i<16;i++)
	{
		//add(p4[i], p5, p4[i]);
		multi(p1, p4[i], p3[i]);
	}
	for(i=0;i<16;i++)
	{
		for(j=0;j<4;j++)
		{
			cout<<output[i][j]<<"\t";
		}
		cout<<endl;
	}
	while(m<=5000)
	{
		identity(p1);
		trans[2][2]=cos(m);
		trans[2][3]=-sin(m);
		trans[3][2]=sin(m);
		trans[3][3]=cos(m);
		for(i=0;i<16;i++)
		{
			multi(p1, p3[i], p7[i]);
		}
		for(i=0;i<16;i++)
		{
			output[i][3]=0;
		}
		trans[0][0]=cos(v);
		trans[0][1]=sin(u)*sin(v);
		trans[0][2]=cos(u)*sin(v);
		trans[0][3]=0;
		trans[1][0]=0;
		trans[1][1]=cos(u);
		trans[1][2]=-sin(u);
		trans[1][3]=0;
		trans[2][0]=-sin(v);
		trans[2][1]=sin(u)*cos(v);
		trans[2][2]=cos(u)*cos(v);
		trans[2][3]=0;
		trans[3][0]=0;
		trans[3][1]=0;
		trans[3][2]=0;
		trans[3][3]=0;
		for(i=0;i<16;i++)
		{
			multi(p1, p7[i], p6[i]);
		}
		cleardevice();
		for(i=0;i<16;i++)
		{
			for(j=i+1;j<16;j++)
			{
				temp=0;
				//cout<<"Temp initial: "<<temp<<endl;
				for(p=0;p<4;p++)
				{
					if(points[i][p]!=points[j][p])
					{
						temp++;
					}
				}
				//cout<<"Temp final: "<<temp<<endl;
				if(temp==1)
				{
				//	cout<<"Yipee! "<<i<<" "<<j<<endl;
				//	cout<<output[i][0]<<"\t"<<output[i][1]<<"\t"<<output[j][0]<<"\t"<<output[j][1]<<endl;
					line(2*980/3+100*output2[i][0], 2*540/3-100*output2[i][1], 2*980/3+100*output2[j][0], 2*540/3-100*output2[j][1]);
				}
			}
		}
		line(2*980/3+1000*output2[0][0], 2*540/3-1000*output2[0][1], 2*980/3+1000*output2[1][0], 2*540/3-1000*output2[1][1]);
		line(2*980/3+1000*output2[0][0], 2*540/3-1000*output2[0][1], 2*980/3+1000*output2[2][0], 2*540/3-1000*output2[2][1]);
		line(2*980/3+1000*output2[0][0], 2*540/3-1000*output2[0][1], 2*980/3+1000*output2[4][0], 2*540/3-1000*output2[4][1]);
		line(2*980/3+1000*output2[0][0], 2*540/3-1000*output2[0][1], 2*980/3+1000*output2[8][0], 2*540/3-1000*output2[8][1]);
		m=m+0.01;
		if(cont==0)
		{
			delay(5000);
		}
		cont++;
		delay(1);
	}
	delay(100000);
}
