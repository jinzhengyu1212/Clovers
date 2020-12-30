#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<queue>
#include<algorithm>
 
#define maxn 2000005
#define INF 0x3f3f3f3f
#define MOD 998244353
 
using namespace std;
 
inline long long getint()
{
	long long num=0,flag=1;char c;
	while((c=getchar())<'0'||c>'9')if(c=='-')flag=-1;
	while(c>='0'&&c<='9')num=num*10+c-48,c=getchar();
	return num*flag;
}
 
int n;
long long a[maxn],sum[maxn];
int ans[maxn],sz[maxn];
int vis[maxn];
 
int main()
{
	n=getint();
	for(int i=0;i<n;i++)
	{
		a[i]=getint();
		if(!a[i])n--,i--;
	}
	int S=(1<<n)-1;
	for(int i=0;i<=S;i++)for(int j=0;j<n;j++)if(i&(1<<j))sum[i]+=a[j];
	for(int i=0;i<=S;i++)
	{
		sz[i]=sz[i>>1]+(i&1);
		for(int j=(i-1)&i;((j<<1)>=i)&&j;j=(j-1)&i)
		{
			int tmp=i^j;
			long long num=abs(sum[j]-sum[tmp]);
			if(num<sz[i]&&((sz[i]-num)&1)){vis[i]=1;break;}
		}
	}
	for(int i=1;i<=S;i++)if(vis[i])
	{
		ans[i]=max(ans[i],1);int t=S^i;
		for(int j=t;j;j=(j-1)&t)ans[i|j]=max(ans[i|j],ans[j]+1);
	}
	printf("%d\n",n-*max_element(ans+1,ans+S+1));
}
