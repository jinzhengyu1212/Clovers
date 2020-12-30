//First Accepted by gedit!
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int fa[N][20];
int n,m; vector<int> v[N];
struct QU{
	int l,r,pos,lca,id;
	bool operator < (const QU &rhs) const{
		if(pos==rhs.pos) return r<rhs.r;
		return pos<rhs.pos;
	}
}Q[N];

int A[N<<1],cnt=0,in[N],out[N],dep[N];
void dfs(int u)
{
	A[++cnt]=u; in[u]=cnt;
	for(int i=0;i<(int)v[u].size();i++)
	{
		int to=v[u][i]; if(to==fa[u][0]) continue;
		fa[to][0]=u; for(int j=1;j<20;j++) fa[to][j]=fa[fa[to][j-1]][j-1];
		dep[to]=dep[u]+1; dfs(to);
	}		
	A[++cnt]=u; out[u]=cnt;
}

int LCA(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=19;i>=0;i--) if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
	if(x==y) return x;
	for(int i=19;i>=0;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i], y=fa[y][i];
	return fa[x][0];
}

int id[N],a[N],b[N],nn;
void init()
{
	memset(fa,0,sizeof(fa));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),b[i]=a[i];
	sort(b+1,b+n+1); nn=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+nn+1,a[i])-b;
	for(int i=1;i<n;i++)
	{
		int x,y; scanf("%d%d",&x,&y);
		v[x].push_back(y); v[y].push_back(x);
	}
	dep[1]=1; dfs(1);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(dep[x]>dep[y]) swap(x,y);
		int lca=LCA(x,y);
		if(x==lca) x=in[x], y=in[y], lca=0;
		else if(out[x]<in[y]) x=out[x],y=in[y];
		else x=in[x], y=out[y];
		if(x>y) swap(x,y);
		Q[i].l=x; Q[i].r=y; Q[i].lca=lca; Q[i].id=i;
	}		
	int TMP=sqrt(n+n);
	for(int i=1;i<=n+n;i++) id[i]=i/TMP+1;
	for(int i=1;i<=m;i++) Q[i].pos=id[Q[i].l];
	sort(Q+1,Q+m+1);
}

int ans=0,L=1,R=0,vis[N],t[N];
void add(int pos)
{
	int val=a[A[pos]];
	vis[A[pos]]++;
	int add=(vis[A[pos]]==1 ? 1 : -1);
	if(t[val]==0) ans++;
	t[val]+=add; 
	if(t[val]==0) ans--;
}
void sub(int pos)
{
	int val=a[A[pos]];
	vis[A[pos]]--;
	int add=(vis[A[pos]]==1 ? 1 : -1);	
	if(t[val]==0) ans++;
	t[val]+=add;
	if(t[val]==0) ans--;
}

int ANS[N];
void solve()
{
	for(int i=1;i<=m;i++)	
	{
		while(R<Q[i].r) add(++R);
		while(R>Q[i].r) sub(R--);
		while(L>Q[i].l) add(--L);
		while(L<Q[i].l) sub(L++);
		if(Q[i].lca&&!t[a[Q[i].lca]]) ans++;
		ANS[Q[i].id]=ans;
		if(Q[i].lca&&!t[a[Q[i].lca]]) ans--;
	}
	for(int i=1;i<=m;i++) printf("%d\n",ANS[i]);
}

int main()
{
	init(); solve();
	return 0;
}
