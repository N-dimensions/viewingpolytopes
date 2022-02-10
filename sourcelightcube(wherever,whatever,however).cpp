#include <graphics.h>
#include <iostream>
#include <math.h>
#include <dos.h>
using namespace std;
int multi(float *, float *, float *);
int add(float *, float *, float *);
int identity(float *);
int inv(float *);
float det(float *);
float cofac(float *, int, int);
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
float cofac(float *m[], int a, int b)
{
	int i, j, x=0, y=0;
	float n[2][2], k;
	for(i=0;i<3;i++)
	{	
		y=0;
		if(i!=a)
		{
			for(j=0;j<3;j++)
			{
				if(j!=b)
				{
					//cout<<x<<y<<endl;
					//cout<<"Hey: "<<m[i][j]<<endl;
					n[x][y]=m[i][j];
					y=y+1;
				}
			}
			x=x+1;
		}
	}
	if((a+b)%2==0)
	{
		k=(n[0][0]*n[1][1]-n[0][1]*n[1][0]);
	}
	else
	{
		k=-(n[0][0]*n[1][1]-n[0][1]*n[1][0]);
	}
	return k;
}
float det(float *m[])
{
	int i, j;
	float cof[3], k;
	k=0;
	for(j=0;j<3;j++)
	{
		k=k+m[0][j]*cofac(m, 0, j);
	}
	return k;
}
int inv(float *m[])
{
	int i, j;
	float cof[3][3], de;
	de=det(m);
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			cof[j][i]=cofac(m, i, j);
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			m[i][j]=cof[i][j]/de;
		}
	}
	return 0;
}
int main()
{
	int i, j, temp;
	float s[3], ori[3], d[3], points[11][3], mag, mag2, D, image[11][3], icap[3], final[3], matrix[3][3], output[11][3], trans[3][3], t=0, adjust[3];
	float *mat[3], *p1[11], *p3[11], *p2[11], *p4[3], *p5;
	p5=&adjust[0];
	for(i=0;i<11;i++)
	{
		temp=i;
		p1[i]=&image[i][0];
		p2[i]=&points[i][0];
		p3[i]=&output[i][0];
		if(i<8)
		{
			for(j=0;j<3;j++)
			{
				points[i][j]=temp%2;
				temp=temp/2;
			}
		}
		else
		{
			temp=pow(2,i-8);
		//	cout<<"Temp: "<<temp<<endl;
			for(j=0;j<3;j++)
			{
				points[i][j]=0.01*points[temp][j];
				output[i][j]=points[i][j];
			}
		}
	}
	cout<<"From where you wanna see stuff? "<<endl;
	for(i=0;i<3;i++)
	{
		mat[i]=&matrix[i][0];
		p4[i]=&trans[i][0];
		cout<<"Co-ordinate "<<i+1<<" : ";
		cin>>s[i];
	}
	cout<<"Direction of view? "<<endl;
	for(i=0;i<3;i++)
	{
		cout<<"Co-ordinate "<<i+1<<" : ";
		cin>>d[i];
	}
	cout<<"Distance between screen and point of vision: ";
	cin>>D;
	cout<<"How do you wanna see things, specify you i^ (i cap): only first 2 co-ordinates... unless required: "<<endl;
	cout<<"X co-ordinate: ";
	cin>>icap[0];
	cout<<"Y co-ordinate: ";
	cin>>icap[1];
	if(d[2]==0 && (icap[0]*d[0]+icap[1]*d[1])==0)
	{
		cout<<"We need more info... Z co-ordinates: ";
		cin>>icap[2];
	}
	else
	{
		if(d[2]!=0)
		{
			icap[2]=-(icap[0]*d[0]+icap[1]*d[1])/d[2];
		}
		else
		{
			cout<<"Sorry your data is inconsistent: ";
			return 0;
		}
	}
	mag=sqrt(d[0]*d[0]+d[1]*d[1]+d[2]*d[2]);
	mag2=sqrt(icap[0]*icap[0]+icap[1]*icap[1]+icap[2]*icap[2]);
	final[0]=d[1]*icap[2]-d[2]*icap[1];
	cout<<"Final 1: "<<final[0]<<endl;
	final[1]=-(d[0]*icap[2]-d[2]*icap[0]);
	cout<<"Final 2: "<<final[1]<<endl;
	final[2]=d[0]*icap[1]-d[1]*icap[0];
	cout<<"Final 3: "<<final[2]<<endl;
	//for(i=0;i<3;i++)
	//{
	//	d[i]=d[i]/mag;
	//}	
	temp=1;
	int gd = DETECT, gm, color;
	initgraph(&gd, &gm, (char*)"");
	while(t<8*3.14159265358979323)
	{
		cleardevice();
		for(i=0;i<3;i++)
		{
			adjust[i]=-0.5;
			for(j=0;j<3;j++)
			{
				output[8+i][j]=points[8+i][j];
			}
		}
		for(i=0;i<8;i++)
		{
			add(p5, p2[i], p2[i]);
		}
		for(i=0;i<3;i++)
		{
			adjust[i]=0.5;
		}
		trans[0][0]=cos(t);
		trans[0][1]=-sin(t);
		trans[0][2]=0;
		trans[1][0]=sin(t);
		trans[1][1]=cos(t);
		trans[1][2]=0;
		trans[2][0]=0;
		trans[2][1]=0;
		trans[2][2]=1;
		for(i=0;i<3;i++)
		{
			matrix[i][0]=icap[i];
			matrix[i][1]=final[i];
			matrix[i][2]=d[i];
		}
		for(i=0;i<8;i++)
		{
			multi(p4, p2[i], p3[i]);
			add(p5, p2[i], p2[i]);
			add(p5, p3[i], p3[i]);
		}
		for(i=0;i<11;i++)
		{
			for(j=0;j<3;j++)
			{
				image[i][j]=(s[j]-output[i][j])*D*mag/((output[i][0]-s[0])*d[0]+(output[i][1]-s[1])*d[1]+(output[i][2]-s[2])*d[2]);
			}
		}
		inv(mat);
		for(i=0;i<11;i++)
		{
			multi(mat, p1[i], p3[i]);
			//for(j=0;j<3;j++)
			//{
			//	cout<<output[i][j]<<"\t";
			//}
			//cout<<endl;
		}
		if(temp==1)
		{
			for(i=0;i<3;i++)
			{
				ori[i]=output[0][i];
				//cout<<"Hurray!!!=================="<<endl;
			}
		}
		temp++;
		//axes
		setcolor(GREEN);
		line(2*980/3-100*ori[0], 2*540/3-100*ori[1], 2*980/3-100*ori[0]+100000*(ori[0]-output[8][0]), 2*540/3-100*ori[1]+100000*(ori[1]-output[8][1]));
		line(2*980/3-100*ori[0], 2*540/3-100*ori[1], 2*980/3-100*ori[0]+100000*(ori[0]-output[9][0]), 2*540/3-100*ori[1]+100000*(ori[1]-output[9][1]));
		line(2*980/3-100*ori[0], 2*540/3-100*ori[1], 2*980/3-100*ori[0]+100000*(ori[0]-output[10][0]), 2*540/3-100*ori[1]+100000*(ori[1]-output[10][1]));
		//line(2*980/3-100*output[0][0], 2*540/3-100*output[0][1], 2*980/3-100*output[0][0]+100000*(output[0][0]-output[9][0]), 2*540/3-100*output[0][1]+100000*(output[0][1]-output[9][1]));
		//line(2*980/3-100*output[0][0], 2*540/3-100*output[0][1], 2*980/3-100*output[0][0]+100000*(output[0][0]-output[10][0]), 2*540/3-100*output[0][1]+100000*(output[0][1]-output[10][1]));
		//	circle(2*980/3+100*output[0][0], 2*540/3-100*output[0][1], 55);
		//cube
		setcolor(RED);	
		line(2*980/3-100*output[0][0], 2*540/3-100*output[0][1], 2*980/3-100*output[1][0], 2*540/3-100*output[1][1]);
		setcolor(BLUE);
		line(2*980/3-100*output[0][0], 2*540/3-100*output[0][1], 2*980/3-100*output[2][0], 2*540/3-100*output[2][1]);
		setcolor(YELLOW);		
		line(2*980/3-100*output[0][0], 2*540/3-100*output[0][1], 2*980/3-100*output[4][0], 2*540/3-100*output[4][1]);
		setcolor(WHITE);
		line(2*980/3-100*output[1][0], 2*540/3-100*output[1][1], 2*980/3-100*output[3][0], 2*540/3-100*output[3][1]);
		line(2*980/3-100*output[1][0], 2*540/3-100*output[1][1], 2*980/3-100*output[5][0], 2*540/3-100*output[5][1]);
		line(2*980/3-100*output[2][0], 2*540/3-100*output[2][1], 2*980/3-100*output[3][0], 2*540/3-100*output[3][1]);
		line(2*980/3-100*output[2][0], 2*540/3-100*output[2][1], 2*980/3-100*output[6][0], 2*540/3-100*output[6][1]);
		line(2*980/3-100*output[3][0], 2*540/3-100*output[3][1], 2*980/3-100*output[7][0], 2*540/3-100*output[7][1]);
		line(2*980/3-100*output[4][0], 2*540/3-100*output[4][1], 2*980/3-100*output[5][0], 2*540/3-100*output[5][1]);
		line(2*980/3-100*output[4][0], 2*540/3-100*output[4][1], 2*980/3-100*output[6][0], 2*540/3-100*output[6][1]);
		line(2*980/3-100*output[5][0], 2*540/3-100*output[5][1], 2*980/3-100*output[7][0], 2*540/3-100*output[7][1]);
		line(2*980/3-100*output[6][0], 2*540/3-100*output[6][1], 2*980/3-100*output[7][0], 2*540/3-100*output[7][1]);
		delay(10);
		t=t+0.01;
	}
}

