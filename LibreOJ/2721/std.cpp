#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;const int N=1e5+10;typedef long long ll;
multiset <ll> s;int n;int m;ll mod[N];ll xs[N];ll cs[N];ll st[N];ll gif[N];int T;
inline void exgcd(ll a,ll& x,ll b,ll& y)//exgcd 
{if(b==0){x=1;y=0;return;}exgcd(b,x,a%b,y);ll t=x;x=y;y=t-(a/b)*y;}
inline ll gcd(ll a,ll b){if(a<b)swap(a,b);while(b){ll c=a%b;a=b;b=c;}return a;}
inline ll inv(ll a,ll p){a%=p;ll x;ll y;exgcd(a,x,p,y);return ((x<0)?x+p:x);}
inline ll mul(ll a,ll b,const ll& md)//龟速乘 
{ll ret=0;b=b%md;b=(b>0)?b:b+md;for(;b;b>>=1,a=(a+a)%md)(ret+=a*(b&1))%=md;return ret;}
inline void cfil(){printf("-1\n");return;}
inline void spsolve()//特判 
{
	ll res=0;
	for(int i=1;i<=n;i++)res=max(res,((cs[i]+xs[i]-1)/xs[i]));
	printf("%lld\n",res);
}
inline void spsolve2()//特判 
{
	ll lc=1;
    for(int i=1;i<=n;i++)
        {ll ds=mod[i]/gcd(mod[i],xs[i]);lc=lc/gcd(lc,ds)*ds;}
    printf("%lld\n",lc);
} 
inline void solve()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&cs[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&mod[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&gif[i]);
	for(int i=1;i<=m;i++)scanf("%lld",&st[i]);
	for(int i=1;i<=m;i++)s.insert(st[i]);
	multiset <ll>:: iterator it;
	for(int i=1;i<=n;i++)//预处理方程的系数 
	{
		it=(cs[i]<(*s.begin()))?s.begin():(--s.upper_bound(cs[i]));
		xs[i]=*it;s.erase(it);s.insert(gif[i]);
	}
	for(int i=1;i<=m;i++)if(mod[i]!=cs[i])goto ski;spsolve2();return;ski:;//判一下p=a的情况 
	for(int i=1;i<=n;i++)if(mod[i]!=1)goto skp;spsolve();return;skp:;//判一下p=1的情况 
	for(int i=1;i<=n;i++)xs[i]%=mod[i];
	for(int i=1;i<=n;i++)//检测是否有无用的方程 
		if(xs[i]==0){if(mod[i]==cs[i]){xs[i]=1;mod[i]=1;cs[i]=0;}else {cfil();return;}}
	for(int i=1;i<=n;i++)//化简同余方程 
	{
		ll sx;ll sy;ll g=gcd(xs[i],mod[i]);if(cs[i]%g!=0){cfil();return;}
		exgcd(xs[i],sx,mod[i],sy);
		mod[i]=mod[i]/g;sx=(sx%mod[i]+mod[i])%mod[i];cs[i]=mul(sx,cs[i]/g,mod[i]);
	}
	for(int i=1;i<=n-1;i++)//合并同余方程 
	{
		ll g=gcd(mod[i],mod[i+1]);if((cs[i+1]-cs[i])%g!=0){cfil();return;}
		ll ncs=mul(inv(mod[i]/g,mod[i+1]/g),(cs[i+1]-cs[i])/g,mod[i+1]/g);
		ll nmod=mod[i]/g*mod[i+1];
		ncs=mul(ncs,mod[i],nmod);(ncs+=cs[i])%=nmod;cs[i+1]=ncs;mod[i+1]=nmod;
	}printf("%lld\n",cs[n]);return;
}
inline void clear(){s.clear();}
int main(){scanf("%d",&T);for(int z=1;z<=T;z++)solve(),clear();return 0;}//拜拜程序~ 