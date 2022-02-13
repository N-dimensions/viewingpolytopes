#include <graphics.h>
#include <iostream>
#include <math.h>
#include <dos.h>
#include <time.h>
using namespace std;
int multi(float **, float *, float *);
int add(float *, float *, float *);
int identity(float **);
int inv(float **, int);
float det(float **, int);
float cofac(float **, int, int, int );
float cross(float *, float *, float *, int);
float cross(float *a, float *b, float *c, int d)
{
	int i, j;
	float m[4][4], *p[4], vec;
	for(i=0;i<4;i++)
	{
		p[i]=&m[i][0];
		m[1][i]=a[i];
		m[2][i]=b[i];
		m[3][i]=c[i];
	}
	vec=cofac(p, 0, d, 4);
	return vec;
}
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
float cofac(float *m[], int a, int b, int size)
{
	int i, j, x=0, y=0;
	float n[3][3], k, *p[3];
	for(i=0;i<size;i++)
	{	
		y=0;
		if(i!=a)
		{
			p[x]=&n[x][0];
			for(j=0;j<size;j++)
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
		if(size==3)
		{
			k=(n[0][0]*n[1][1]-n[0][1]*n[1][0]);
			return k;
		}
		k=det(p, size-1);
		return k;
	}
	else
	{
		if(size==3)
		{
			k=-(n[0][0]*n[1][1]-n[0][1]*n[1][0]);
			return k;
		}
		k=-det(p, size-1);
		return k;
	}
}
float det(float *m[], int size)
{
	int i, j;
	float k;
	k=0;
	for(j=0;j<size;j++)
	{
		k=k+m[0][j]*cofac(m, 0, j, size);
	}
	return k;
}
int inv(float *m[], int size)
{
	int i, j;
	float cof[4][4], de;
	de=det(m, size);
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			cof[j][i]=cofac(m, i, j, size);
		}
	}
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			m[i][j]=cof[i][j]/de;
		}
	}
	return 0;
}
int main()
{
	int i, j, temp, p;
	float s[4], ori[4], d[4], points[20][4], mag, mag2, mag3, mag4, D, image[20][4], icap[4], final[4], matrix[4][4], output[20][4], trans[4][4], t=0, adjust[4], jcap[4], kcap[4], x, y;
	float *mat[4], *p1[20], *p3[20], *p2[20], *p4[4], *p5;
	p5=&adjust[0];
	x=asin(2/sqrt(5));
	y=-asin(1/sqrt(6));
	for(i=0;i<20;i++)
	{
		temp=i;
		p1[i]=&image[i][0];
		p2[i]=&points[i][0];
		p3[i]=&output[i][0];
		if(i<16)
		{
			for(j=0;j<4;j++)
			{
				points[i][j]=temp%2;
				temp=temp/2;
			}
		}
		else
		{
			temp=pow(2,i-16);
		//	cout<<"Temp: "<<temp<<endl;
			for(j=0;j<4;j++)
			{
				points[i][j]=0.01*points[temp][j];
				output[i][j]=points[i][j];
			}
		}
	}
	cout<<"From where you wanna see stuff? "<<endl;
	for(i=0;i<4;i++)
	{
		mat[i]=&matrix[i][0];
		p4[i]=&trans[i][0];
		cout<<"Co-ordinate "<<i+1<<" : ";
		cin>>s[i];
	}
	cout<<"Direction of view? "<<endl;
	for(i=0;i<4;i++)
	{
		cout<<"Co-ordinate "<<i+1<<" : ";
		cin>>d[i];
	}
	mag=sqrt(d[0]*d[0]+d[1]*d[1]+d[2]*d[2]+d[3]*d[3]);
	for(i=0;i<4;i++)
	{
		d[i]=d[i]/mag;
	}
	mag=1;
	cout<<"Distance between screen and point of vision: ";
	cin>>D;
	cout<<"How do you wanna see things, specify you i^ (i cap): only first 2 co-ordinates... unless required: "<<endl;
	cout<<"X co-ordinate: ";
	cin>>icap[0];
	cout<<"Y co-ordinate: ";
	cin>>icap[1];
	cout<<"Z co-ordinate: ";
	cin>>icap[2];
	if(d[3]==0 && (icap[0]*d[0]+icap[1]*d[1]+icap[2]*d[2])==0)
	{
		cout<<"We need more info... W co-ordinates: ";
		cin>>icap[3];
	}
	else
	{
		if(d[3]!=0)
		{
			icap[3]=-(icap[0]*d[0]+icap[1]*d[1]+icap[2]*d[2])/d[3];
		}
		else
		{
			cout<<"Sorry your data is inconsistent: ";
			return 0;
		}
	}
	cout<<"Co-ordinates of j^ please: "<<endl;
	cout<<"X co-ordinate: ";
	cin>>jcap[0];
	cout<<"Y co-ordinate: ";
	cin>>jcap[1];
	cout<<"Z co-ordinate: ";
	cin>>jcap[2];
	if(d[3]==0 && (jcap[0]*d[0]+jcap[1]*d[1]+jcap[2]*d[2])==0)
	{
		cout<<"We need more info... W co-ordinates: ";
		cin>>jcap[3];
	}
	else
	{
		if(d[3]!=0)
		{
			jcap[3]=-(jcap[0]*d[0]+jcap[1]*d[1]+jcap[2]*d[2])/d[3];
		}
		else
		{
			cout<<"Sorry your data is inconsistent: ";
			return 0;
		}
	}
	cout<<"I am a bit afraid... please give me k^ also: "<<endl;
	cout<<"X co-ordinate: ";
	cin>>kcap[0];
	cout<<"Y co-ordinate: ";
	cin>>kcap[1];
	cout<<"Z co-ordinate: ";
	cin>>kcap[2];
	if(d[3]==0 && (kcap[0]*d[0]+kcap[1]*d[1]+kcap[2]*d[2])==0)
	{
		cout<<"We need more info... W co-ordinates: ";
		cin>>kcap[3];
	}
	else
	{
		if(d[3]!=0)
		{
			//cout<<"D3: "<<d[3];
			kcap[3]=-(kcap[0]*d[0]+kcap[1]*d[1]+kcap[2]*d[2])/d[3];
		}
		else
		{
			cout<<"Sorry your data is inconsistent: ";
			return 0;
		}
	}
	mag2=sqrt(icap[0]*icap[0]+icap[1]*icap[1]+icap[2]*icap[2]+icap[3]*icap[3]);
	mag3=sqrt(jcap[0]*jcap[0]+jcap[1]*jcap[1]+jcap[2]*jcap[2]+jcap[3]*jcap[3]);
	mag4=sqrt(kcap[0]*kcap[0]+kcap[1]*kcap[1]+kcap[2]*kcap[2]+kcap[3]*kcap[3]);
	for(i=0;i<4;i++)
	{
		icap[i]=icap[i]/mag2;
		jcap[i]=jcap[i]/mag3;
		kcap[i]=kcap[i]/mag4;
	}
	temp=1;
	int gd = DETECT, gm, color;
	initgraph(&gd, &gm, (char*)"");
	while(t<8*3.14159265358979323)
	{
		cleardevice();
		for(i=0;i<4;i++)
		{
			adjust[i]=-0.5;
			for(j=0;j<4;j++)
			{
				output[16+i][j]=points[16+i][j];
			}
		}
		for(i=0;i<16;i++)
		{
			add(p5, p2[i], p2[i]);
		}
		for(i=0;i<4;i++)
		{
			adjust[i]=0.5;
		}
		trans[0][0]=cos(t);
		trans[0][1]=0;
		trans[0][2]=0;
		trans[0][3]=-sin(t);
		trans[1][0]=0;
		trans[1][1]=1;
		trans[1][2]=0;
		trans[1][3]=0;
		trans[2][0]=0;
		trans[2][1]=0;
		trans[2][2]=1;
		trans[2][3]=0;
		trans[3][0]=sin(t);
		trans[3][1]=0;
		trans[3][2]=0;
		trans[3][3]=cos(t);
		for(i=0;i<4;i++)
		{
			matrix[i][0]=icap[i];
			matrix[i][1]=jcap[i];
			matrix[i][2]=kcap[i];
			matrix[i][3]=d[i];
		}
		for(i=0;i<16;i++)
		{
			multi(p4, p2[i], p3[i]);
			add(p5, p2[i], p2[i]);
			add(p5, p3[i], p3[i]);
		}
		for(i=0;i<20;i++)
		{
			for(j=0;j<4;j++)
			{
				image[i][j]=(s[j]-output[i][j])*D*mag/((output[i][0]-s[0])*d[0]+(output[i][1]-s[1])*d[1]+(output[i][2]-s[2])*d[2]+(output[i][3]-s[3])*d[3]);
				//cout<<image[i][j]<<endl;
			}
		}
		inv(mat, 4);
		//cout<<"D3: "<<d[3]<<endl;
		//cout<<"Matrix taken in: "<<endl;
		for(i=0;i<4;i++)
		{
			//a[i]=rand()%10;
			//b[i]=rand()%10;
			//c[i]=rand()%10;
			//p1[i]=&matrix[i][0];
			for(j=0;j<4;j++)
			{
				//cout<<matrix[i][j]<<"\t";
			}
			//cout<<endl;
		}
		for(i=0;i<20;i++)
		{
			multi(mat, p1[i], p3[i]);
			for(j=0;j<4;j++)
			{
			//	cout<<output[i][j]<<"\t";
			}
			//cout<<endl;
		}
		if(temp==1)
		{
			for(i=0;i<4;i++)
			{
				ori[i]=output[0][i];
				//cout<<"Hurray!!!=================="<<endl;
			}
		}
		temp++;
		trans[0][0]=cos(y);
		trans[0][1]=sin(x)*sin(y);
		trans[0][2]=cos(x)*sin(y);
		trans[0][3]=0;
		trans[1][0]=0;
		trans[1][1]=cos(x);
		trans[1][2]=-sin(x);
		trans[1][3]=0;
		trans[2][0]=-sin(y);
		trans[2][1]=sin(x)*cos(y);
		trans[2][2]=cos(x)*cos(y);
		trans[2][3]=0;
		trans[3][0]=0;
		trans[3][1]=0;
		trans[3][2]=0;
		trans[3][3]=0;
		for(i=0;i<16;i++)
		{
			multi(p4, p3[i], p1[i]);
		}
		//cout<<"Wait"<<endl;
		for(i=0;i<16;i++)
		{
			for(j=0;j<4;j++)
			{	
				output[i][j]=image[i][j];
			//	cout<<output[i][j]<<"\t";
			}
			//cout<<endl;
		}
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
					line(2*980/3+100*output[i][0], 2*540/3-100*output[i][1], 2*980/3+100*output[j][0], 2*540/3-100*output[j][1]);
				}
			}
		}
		delay(10);
		t=t+0.01;
	}
}

