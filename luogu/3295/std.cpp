#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;ll mod=1e9+7;
inline ll po(ll a,ll p){ll r=1;for(;p;p>>=1,a=(a*a)%mod){if(p&1)r=(r*a)%mod;}return r;}
const int N=100010;int n;int tr[20][N];int log[N];int ctt;//用来给各个区间编号
inline void createlog()//这里打表log其实并没咋用……
{int i=1;for(int j=2;j<=n;j++){if(j==(1<<(i+1)))i++;log[j]=i;}}
struct bcj//只写了路径压缩，理论来讲是log^2N的，但是路径压缩的均摊复杂度常数小于1……
{
	int fa[20*N];
	inline void ih(){for(int i=1;i<=ctt;i++)fa[i]=i;}
	inline int f(int x){return fa[x]=(fa[x]==x)?x:f(fa[x]);}
	inline void u(int x,int y){fa[f(x)]=f(y);}
}s;int m;int siz;bool book[N];
inline void dtr(int v,int& y){v%=n;y=v?v:n;}//解编号函数
int main()
{
	scanf("%d%d",&n,&m);createlog();
	for(int i=0;i<=log[n];i++)
	{for(int j=1;j<=n;j++){tr[i][j]=++ctt;}}//分配编号
	s.ih();
	for(int i=1;i<=m;i++)
	{
		int l;int r;int len;int d;
		scanf("%d%d%d%d",&l,&r,&len,&d);
		d=len-l;len=r-l+1;//len区间长度,d偏移量
		for(int k=0;len;len>>=1,k++)//这里的二进制拆分可能用了些位运算的奇技淫巧~
		{
			if(len&1)
			{
				int p1=l+((len>>1)<<(k+1));int p2=p1+d;
				s.u(tr[k][p1],tr[k][p2]);//把对应区间并起来
			}
		}
	}
	for(int i=log[n];i>=1;i--)
	{
		for(int j=1;j+(1<<i)-1<=n;j++)//分裂并查集
		{
			int fa=s.f(tr[i][j]);if(fa==tr[i][j]){continue;}int y;dtr(fa,y);//前一半后一半连边
			s.u(tr[i-1][j],tr[i-1][y]);s.u(tr[i-1][j+(1<<(i-1))],tr[i-1][y+(1<<(i-1))]);
		}
	}
	for(int i=1;i<=n;i++)//计算并查集个数
	{
		int fa=s.f(tr[0][i]);int y;dtr(fa,y);
		if(!book[y]){book[y]=true;siz++;}
	}
	printf("%lld\n",(9*po(10,siz-1))%mod);return 0;//拜拜程序~
}