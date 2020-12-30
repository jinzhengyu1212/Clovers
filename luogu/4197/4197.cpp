#include<bits/stdc++.h>
using namespace std;
const int N=200005;
const int M=500005;
const int inf=(int)1e9+2;
int n,m,q,a[N],val[N],nn;
struct Edge{
	int from,to,cost;
	bool operator < (const Edge &rhs) const{
		return cost<rhs.cost;
	}
}E[M];

vector<int> v[N];
namespace BIT{
	int fa[N];
	void init(){for(int i=1;i<=n+n;i++) fa[i]=i;}
	int getfather(int x){return x==fa[x] ? x : fa[x]=getfather(fa[x]);}
	void unite(int x,int y){//y->x
		x=getfather(x); y=getfather(y);
		v[x].push_back(y);
		fa[y]=x;
	}
	bool same(int x,int y){return getfather(x)==getfather(y);}
}

int tot,A[N];
void kruskal(){
	for(int i=1;i<=m;i++){
		if(BIT::same(E[i].from,E[i].to)) continue;
		tot++; A[tot]=E[i].cost;
		BIT::unite(tot,E[i].from); BIT::unite(tot,E[i].to);
	}
}

int dfn_clock=0,dfn[N],sz[N],fa[N][20],dep[N],id[N],out[N];
void dfs(int u,int f){
	dfn[u]=++dfn_clock; id[dfn_clock]=u; 
	if(u<=n) sz[u]=1;
	for(int i=0;i<(int)v[u].size();i++){
		int to=v[u][i]; if(to==f) continue;
		fa[to][0]=u; for(int j=1;j<20;j++) fa[to][j]=fa[fa[to][j-1]][j-1];
		dep[to]=dep[u]+1; dfs(to,u); sz[u]+=sz[to];
	}
	out[u]=dfn_clock;
}

int find(int x,int VAL){//find the highest root that can reach
	A[0]=inf;
	for(int i=19;i>=0;i--)
		if(A[fa[x][i]]<=VAL) x=fa[x][i];
	return x;
}

int cnt=0;
struct Chairman_Tree{
	int sum[N<<5],ls[N<<5],rs[N<<5];
	void pushup(int x){sum[x]=sum[ls[x]]+sum[rs[x]];}
	void build(int x,int l,int r){
		if(l==r) {sum[x]=0; return;}
		int mid=(l+r)>>1; 
		ls[x]=++cnt; rs[x]=++cnt;
		build(ls[x],l,mid); build(rs[x],mid+1,r);
		pushup(x);
	}
	void update(int x,int y,int l,int r,int pos){
		if(pos==0){sum[x]=sum[y]; ls[x]=ls[y]; rs[x]=rs[y]; return;}
		if(l==r) {sum[x]=sum[y]+1; return;}
		int mid=(l+r)>>1;
		if(mid>=pos) ls[x]=++cnt, rs[x]=rs[y], update(ls[x],ls[y],l,mid,pos);
		else rs[x]=++cnt, ls[x]=ls[y], update(rs[x],rs[y],mid+1,r,pos);
		pushup(x);
	}
	int query(int x,int y,int l,int r,int K){//y-x
		if(l==r) return val[l];
		int mid=(l+r)>>1;
		int tmp=sum[ls[y]]-sum[ls[x]];
		if(tmp<K) return query(rs[x],rs[y],mid+1,r,K-tmp);
		else return query(ls[x],ls[y],l,mid,K);
	}
}tree;

void init()
{
	scanf("%d%d%d",&n,&m,&q); BIT::init(); tot=n;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),val[i]=a[i];
	sort(val+1,val+n+1); nn=unique(val+1,val+n+1)-val-1;
	cnt=n+n; 
	for(int i=1;i<=n;i++) a[i]=lower_bound(val+1,val+nn+1,a[i])-val;
	for(int i=1;i<=m;i++) scanf("%d%d%d",&E[i].from,&E[i].to,&E[i].cost);
	sort(E+1,E+m+1);
	kruskal();
	for(int i=1;i<=n+n-1;i++)
		if(BIT::getfather(i)==i) dep[i]=1, dfs(i,-1);
	tree.build(0,1,nn);
	for(int i=1;i<=n+n-1;i++) 
	{
		int tmp=(id[i]>n ? 0 : a[id[i]]);
		tree.update(i,i-1,1,nn,tmp);
	}
}

void solve(){
	while(q--){
		int from,x,k; scanf("%d%d%d",&from,&x,&k);
		int root=find(from,x);
		if(sz[root]<k) puts("-1");
		else printf("%d\n",tree.query(dfn[root]-1,out[root],1,nn,sz[root]-k+1));
	}	
}

int main()
{
	init(); solve();
	return 0;
}

