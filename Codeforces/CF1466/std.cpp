#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define int long long
#define ri register
#define mk make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define is insert
#define es erase
using namespace std; const int N=1000010, Mod=1e9+7;
inline int read()
{
	int s=0, w=1; ri char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48), ch=getchar();
	return s*w;
}
int n,m,g[N],f[N],book[N];
vector<int> S[N],Ans;
inline int Find(int x) { return f[x]^x?f[x]=Find(f[x]):x; }
inline int ksc(int x,int p) { int res=1; for(;p;p>>=1, x=x*x%Mod) if(p&1) res=res*x%Mod; return res; }
signed main()
{
	n=read(), m=read();
	for(ri int i=1;i<=n;i++)
	{
		g[i]=read();
		for(ri int j=1;j<=g[i];j++)
		{
			int x=read();
			S[i].eb(x);
		}
	}
	for(ri int i=1;i<=m;i++) f[i]=i;
	for(ri int i=1;i<=n;i++)
	{
		if((int)S[i].size()==1)
		{
			int x=S[i][0];
			int fx=Find(x);
			if(!book[fx]) book[fx]=1, Ans.eb(i);
		}
		else
		{
			int x=S[i][0], y=S[i][1];
			int fx=Find(x), fy=Find(y);
			if(fx==fy) continue;
			if(book[fx] && book[fy]) continue;
			f[fy]=fx, book[fx]|=book[fy];
			Ans.eb(i);
		}
	}
	printf("%lld %lld\n",ksc(2,(int)Ans.size()),(int)Ans.size());
	for(auto i:Ans) printf("%lld ",i); puts("");
	return 0;
}