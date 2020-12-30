#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf=(int)(2e9);
const ll INF=(ll)(5e18);
const int N=300010;

int first[N],nxt[N],point[N],e=0,n,m;
void add_edge(int x,int y)
{
	nxt[e]=first[x];
	first[x]=e;
	point[e]=y; e++;
}

struct Edge{
	int from,to;
}E[N];

int dfn[N],low[N],cnt=0,a[N]; 
int stk[N],top=0;
int val[N],tot=0,scc[N];
int vis[N],in[N];
void tarjan(int u)
{
	dfn[u]=++cnt;
	stk[++top]=u; low[u]=dfn[u]; vis[u]=1;
	for(int i=first[u];i!=-1;i=nxt[i])
	{
		int v=point[i];
		if(!dfn[v]) 
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		tot++;
		while(1)
		{
			int now=stk[top]; top--;
			vis[now]=0;
			val[tot]+=a[now];
			scc[now]=tot;
			if(now==u) break;
		}
	}
}

vector<int> V[N];
void init()
{
//	for(int i=1;i<=n;i++) cout<<scc[i]<<" "; cout<<endl;
//	for(int i=1;i<=n;i++) cout<<dfn[i]<<" "; cout<<endl;
//	for(int i=1;i<=n;i++) cout<<low[i]<<" ";cout<<endl;
	for(int i=1;i<=m;i++)
	{
		int x=scc[E[i].from];
		int y=scc[E[i].to];
		if(x==y) continue;
		//cout<<E[i].from<<" "<<E[i].to<<" "<<x<<" "<<y<<endl;
		V[x].push_back(y);
		in[y]++;
	}
}

int ans=0,dp[N];
void dfs(int u)
{ 
	int maxn=0;
	for(int i=0;i<(int)V[u].size();i++)
	{
		int v=V[u][i];
		dfs(v);
		maxn=max(maxn,dp[v]);
	}
	dp[u]=val[u]+maxn;
	ans=max(ans,dp[u]);
}

int main()
{
	//freopen("point.in","r",stdin);
	//freopen("point.out","w",stdout);
	memset(first,-1,sizeof(first));
	memset(nxt,-1,sizeof(nxt));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&E[i].from,&E[i].to);
		add_edge(E[i].from,E[i].to);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	init();
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=tot;i++) 
	{
		if(!in[i]) dfs(i);
	}
	cout<<ans<<endl;
	//fclose(stdin); fclose(stdout);
	return 0;
}