#include <bits/stdc++.h>
using namespace std;
const double eps=1e-10;
int n,m,sum;
struct vec
{
	double x,y;
	vec(double X=0,double Y=0):x(X),y(Y){}
	vec operator+(const vec&a)const
	{
		return vec(x+a.x,y+a.y);
	}
	vec operator-(const vec&a)const
	{
		return vec(x-a.x,y-a.y);
	}
	void operator+=(const vec&a)
	{
		this->x+=a.x,this->y+=a.y;
	}
	void operator-=(const vec&a)
	{
		this->x-=a.x,this->y-=a.y;
	}
	vec operator*(const double&a)const
	{
		return vec(x*a,y*a);
	}
	vec operator/(const double&a)const
	{
		return vec(x/a,y/a);
	}
	void operator*=(const double&a)
	{
		this->x*=a,this->y*=a;
	}
	void operator/=(const double&a)
	{
		this->x/=a,this->y/=a;
	}
}Q[1100],M[1100];
double cp(vec A,vec B)//叉积
{
	return A.x*B.y-A.y*B.x;
}
double pp(vec A,vec B)//点积
{
	return A.x*B.x+A.y*B.y;
}
struct line
{
	vec A,B;
	double K;
	line(vec a,vec b):A(a),B(b){K=atan2(B.y,B.x);}//按极角排序
	line(){}
	bool operator<(const line&a)const
	{
		return K<a.K; 
	}
}P[1100],T[1100];
int st,en;
vec get(line A,line B)//求交点
{
	vec C=A.A-B.A;
	double t=cp(B.B,C)/cp(A.B,B.B);
	return A.A+A.B*t; 
}
void work()
{
	st=en=1;
	T[st]=P[1];
	for(int i=2;i<=sum;i++)
	{
		printf("%.2lf %.2lf %.2lf %.2lf\n",P[i].B.x,P[i].B.y,P[i].A.x,P[i].A.y);
        //cout<<P[i].B.x<<" "<P[i].B.y<<" "<<P[i].A.x<<" "<<P[i].A.y<<endl;
		while(st<en&&cp(P[i].B,M[en-1]-P[i].A)<=eps)//踢出队尾，交点在当前边右侧
		{			
			--en;
		}
		while(st<en&&cp(P[i].B,M[st]-P[i].A)<=eps)//踢出队首，交点在当前边右侧
		{
			++st;
		}
        cerr<<i<<" "<<st<<" "<<en<<endl;
		T[++en]=P[i]; 
		if(fabs(cp(T[en].B,T[en-1].B))<=eps)//平行
		{
			cout<<i<<endl;
			en--;
			if(cp(T[en].B,P[i].A-T[en].A)>eps)//取更左边那个
			{
				T[en]=P[i];
			}
		}
		if(st<en)//有多个边在集合中，加入交点
		{
			M[en-1]=get(T[en-1],T[en]);
		}
	}
	while(st<en&&cp(T[st].B,M[en-1]-T[st].A)<=eps)
	{
		--en;
	}
	if(en-st<=1)
	{
		return ;
	}
	M[en]=get(T[st],T[en]);
}
void solve()
{
	double ans=0;
	for(int i=st;i<=en;i++)//计算面积
	{
		int to=i+1;
		if(i==en)
		{
			to=st;
		}
		ans+=cp(M[i],M[to]);
	}
	printf("%.3lf",ans/2);
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>m;
		for(int j=1;j<=m;j++)
		{
			scanf("%lf%lf",&Q[j].x,&Q[j].y);
		}
		for(int j=1;j<=m;j++)
		{
			++sum;
			int to=j+1;
			if(j==m)
			{
				to=1;
			}
			P[sum]=line(Q[j],Q[to]-Q[j]);
		}
	}
	sort(P+1,P+sum+1);//极角排序
	work();
	solve();
	return 0;
}
