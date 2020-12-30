#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
#define m_p make_pair
#define sz(x) (int)x.size()
#define mem(a,b) memset(a,b,sizeof(a))
#define setIO(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout)
#define closefile fclose(stdin),fclose(stdout)
#define see(x) cerr<<x<<" "
#define seeln(x) cerr<<x<<endl
#define out(x) cerr<<#x<<" = "<<x<<" "
#define outln(x) cerr<<#x<<" = "<<x<<endl
#define outarr(x,l,r) cerr<<#x"["<<l<<"-"<<r<<"] = "; for (int _i=l;_i<=r;++_i) cerr<<x[_i]<<" ";cerr<<endl;
#define ri register int
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<long long,int> pli;
template <class T> void read(T &x)
{
    x=0; char c=getchar(); int f=0;
    while (c<'0'||c>'9') f|=(c=='-'),c=getchar();
    while (c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    if (f) x=-x;
}
template <class T> T _max(T a,T b){return b>a ? b : a;}
template <class T> T _min(T a,T b){return b<a ? b : a;}
template <class T> bool checkmax(T &a,T b){return b>a ? a=b,1 : 0;}
template <class T> bool checkmin(T &a,T b){return b<a ? a=b,1 : 0;}
const int N=3003;
const int inf=0x3f3f3f3f;
const ll Inf=0x3f3f3f3f3f3f3f3fLL;
int n,m,k;
int e=0,first[N],nxt[N<<1],point[N<<1],value[N<<1];
int arr[N];
ll dp[N][N];
ll ans=Inf;
int w;
ll dis[N];
void add_edge(int x,int y,int z)
{
	nxt[++e]=first[x];
	first[x]=e;
	point[e]=y;
	value[e]=z;
}

void init()
{
	read(n); read(m); read(k);
	memset(first,-1,sizeof first);
	for (int i=1,w,u,v;i<=m;++i)
	{
		read(u); read(v); read(w);
		add_edge(u,v,w);
		add_edge(v,u,w);
		arr[i]=w;
	}
}

void nmdp()
{
	memset(dp,0x3f,sizeof dp);
	dp[1][0]=0;
	for (int i=0;i<m;++i)
	{
		for (int x=1;x<=n;++x)
		{
			for (int j=first[x];j!=-1;j=nxt[j])
			{
				int to=point[j];
				checkmin(dp[to][i+1],dp[x][i]+value[j]);
			}
		}
	}
	for (int i=0;i<=k;++i) checkmin(ans,dp[n][i]);
}

ll dijkstra(int s,int t)
{
	priority_queue<pli,vector<pli>,greater<pli> > q;
	for (int i=1;i<=n;++i) dis[i]=Inf;
	dis[s]=0;
	q.push(m_p(dis[s],s));
	while (!q.empty())
	{
		int x=q.top().second; ll D=q.top().first;
		q.pop();
		if (dis[x]<D) continue;
		for (int i=first[x];i!=-1;i=nxt[i])
		{
			int to=point[i]; int val=_max(value[i]-w,0);
			if (checkmin(dis[to],D+val))
			{
				q.push(m_p(dis[to],to));
			}
		}
	}
	return dis[t];
}

void solve()
{
	nmdp();
	checkmin(ans,dijkstra(1,n));
	for (int i=1;i<=m;++i)
	{
		w=arr[i];
		ll tmp=dijkstra(1,n);
		//out(w); outln(tmp);
		checkmin(ans,tmp+(ll)w*k);
	}
	printf("%lld\n",ans);
}

int main()
{
	init();
	solve();
	return 0;
}
