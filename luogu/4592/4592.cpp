#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const int N=50005;
const int MOD=998244353;
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int mul(int x,int y){return 1ll*x*y%MOD;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
int qpow(int x,int y)
{
	int ret=1;
	while(y)
	{
		if(y&1) ret=mul(ret,x);
		x=mul(x,x);
		y>>=1;
	}
	return ret;
}

int n,m,k; vector<int> v[N];
int top[N],dfn[N],id[N],son[N],fa[N],sz[N],dep[N],cnt=0;
void dfs1(int u)
{
	sz[u]=1;
	for(int i=0;i<(int)v[u].size();i++)
	{
		int to=v[u][i]; if(to==fa[u]) continue;
		dep[to]=dep[u]+1; fa[to]=u; dfs1(to); sz[u]+=sz[to];
		if(sz[to]>sz[son[u]]) son[u]=to;
	}
}

void dfs2(int u)
{
	dfn[u]=++cnt; id[cnt]=u;
	if(son[u]) top[son[u]]=top[u], dfs2(son[u]);
	for(int i=0;i<(int)v[u].size();i++)
	{
		int to=v[u][i]; if(to==fa[u]||to==son[u]) continue;
		top[to]=to; dfs2(to);
	}
}

int Exp[N];
struct SEG{
	int sum[N<<2],tag[N<<2];
	void pushup(int x){sum[x]=add(sum[x<<1],sum[x<<1|1]);}
	void build(int x,int l,int r){
		sum[x]=0; tag[x]=0;
		if(l==r) return;
		int mid=(l+r)>>1;
		build(x<<1,l,mid); build(x<<1|1,mid+1,r);
		pushup(x);
	}
	void pushdown(int x,int l,int mid,int r){
		if(!tag[x]) return;
		int depmid=dep[id[mid]],depl=dep[id[l]],depr=dep[id[r]];
		sum[x<<1]=add(sum[x<<1],mul(sub(Exp[depmid],Exp[depl-1]),tag[x]));
		sum[x<<1|1]=add(sum[x<<1|1],mul(sub(Exp[depr],Exp[depmid]),tag[x]));
		tag[x<<1]=add(tag[x<<1],tag[x]); tag[x<<1|1]=add(tag[x<<1|1],tag[x]);
		tag[x]=0;
	}
	void update(int x,int l,int r,int L,int R){
		if(L<=l&&r<=R){
			int depr=dep[id[r]],depl=dep[id[l]];
			sum[x]=add(sum[x],sub(Exp[depr],Exp[depl-1]));
			tag[x]=add(tag[x],1);
			return;
		}
		int mid=(l+r)>>1; pushdown(x,l,mid,r);
		if(mid>=L) update(x<<1,l,mid,L,R);
		if(mid<R) update(x<<1|1,mid+1,r,L,R);
		pushup(x);
	}
	int query(int x,int l,int r,int L,int R){
		if(L<=l&&r<=R) return sum[x];
		int mid=(l+r)>>1; pushdown(x,l,mid,r);
		int ret=0;
		if(mid>=L) ret=add(ret,query(x<<1,l,mid,L,R));
		if(mid<R) ret=add(ret,query(x<<1|1,mid+1,r,L,R));
		return ret;
	}
}tree;

struct QU{
	int x,num,id;
}Q[N];

vector<pii> q[N];
void init()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&fa[i]);
		v[fa[i]].push_back(i);
	}
	dep[1]=1; dfs1(1);
	top[1]=1; dfs2(1);
	Exp[0]=0; for(int i=1;i<=n;i++) Exp[i]=qpow(i,k);
	for(int i=1;i<=m;i++) scanf("%d%d",&Q[i].x,&Q[i].num), Q[i].id=i;
	for(int i=1;i<=m;i++) q[Q[i].x].push_back(mk(Q[i].num,Q[i].id));
	tree.build(1,1,n);
}

void change_path(int x)
{
	while(x){
		int to=top[x],u=fa[to];
		tree.update(1,1,n,dfn[to],dfn[x]);
		x=u;
	}
}

int query(int x)
{
	int ret=0;
	while(x){
		int to=top[x], u=fa[to];
		ret=add(ret,tree.query(1,1,n,dfn[to],dfn[x]));
		x=u;
	}
	return ret;
}

int ans[N];
void solve()
{
	for(int i=1;i<=n;i++)
	{
		change_path(i);
		for(int j=0;j<(int)q[i].size();j++){
			pii now=q[i][j];
			ans[now.second]=query(now.first);
		}
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]); cout<<endl;
}

int main()
{
	init(); solve();
	return 0;
}
