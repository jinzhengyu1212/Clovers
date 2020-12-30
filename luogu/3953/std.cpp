#include<bits/stdc++.h>
using namespace std;
const int N=100005;
const int M=200005;
int n,m,k,p;
struct Edge
{
    int sum,h[N];
    int v[M],w[M],nxt[M];
    void adde(int x,int y,int z)
    {
        sum++;
        v[sum]=y;
        w[sum]=z;
        nxt[sum]=h[x];
        h[x]=sum;
    }
    void clear()
    {
        sum=0;
        memset(h,0,sizeof(h));memset(v,0,sizeof(v));
        memset(w,0,sizeof(w));memset(nxt,0,sizeof(nxt));
    }
}e,e0,une,une0;
struct node
{
    int pos,dis;int r;
    node(int x=0,int y=0):pos(x),dis(y){}
    friend bool operator <(node a,node b){return a.dis>b.dis;}
} g[N];
bool cmp(node a,node b){return a.dis!=b.dis?(a.dis<b.dis):(a.r<b.r);}
bool v[N];
priority_queue<node> q;
void dijkstra1()
{
    for(int i=1;i<=n;i++) g[i].pos=i,g[i].dis=0x7fffffff;
    memset(v,0,sizeof(v));
    g[1].dis=0;
    q.push(node(1,0));
    while(!q.empty())
    {
        int x=q.top().pos;q.pop();
        if(v[x]) continue;
        v[x]=1;
        for(int i=e.h[x];i;i=e.nxt[i])
        {
            int y=e.v[i];
            if(g[y].dis>1ll*g[x].dis+e.w[i])
            {
                g[y].dis=g[x].dis+e.w[i];
                q.push(node(y,g[y].dis));
            }
        }
    }
}
int undis[N];
void dijkstra2()
{
    memset(undis,127,sizeof(undis));
    memset(v,0,sizeof(v));
    undis[n]=0;
    q.push(node(n,0));
    while(!q.empty())
    {
        int x=q.top().pos;q.pop();
        if(v[x]) continue;
        v[x]=1;
        for(int i=une.h[x];i;i=une.nxt[i])
        {
            int y=une.v[i];
            if(undis[y]>1ll*undis[x]+une.w[i])
            {
                undis[y]=undis[x]+une.w[i];
                q.push(node(y,undis[y]));
            }
        }
    }
}
bool ine0[N];
int ind[N];
int unind[N];
void topo1()
{
	int cnt=0;
	queue<int> q;
	for(int i=1;i<=n;i++)
		if(ine0[i]&&ind[i]==0)
			g[i].r=++cnt,q.push(i);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=e0.h[x];i;i=e0.nxt[i])
		{
			int y=e0.v[i];
			ind[y]--;
			if(ind[y]==0)
				g[y].r=++cnt,q.push(y);
		}
	}
}
void topo2()
{
	int cnt=N;
	queue<int> q;
	for(int i=1;i<=n;i++)
		if(ine0[i]&&unind[i]==0)
			g[i].r=--cnt,q.push(i);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=une0.h[x];i;i=une0.nxt[i])
		{
			int y=une0.v[i];
			unind[y]--;
			if(unind[y]==0)
				g[y].r=--cnt,q.push(y);
		}
	}
}
int f[55][N];
int pos[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        e.clear();e0.clear();une.clear();une0.clear();
        memset(ine0,0,sizeof(ine0));
        memset(ind,0,sizeof(ind));
        memset(unind,0,sizeof(unind));
        scanf("%d%d%d%d",&n,&m,&k,&p);
        int a,b,c;
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&a,&b,&c);
            e.adde(a,b,c);
            une.adde(b,a,c);
            if(c==0)
            {
                ine0[a]=ine0[b]=1;
				ind[b]++;unind[a]++;
                e0.adde(a,b,c);une0.adde(b,a,c);
            }
        }
        dijkstra1();
        dijkstra2();
        topo1();
        topo2();
        bool ok=0;
        for(int i=1;i<=n;i++)
        	if(ind[i]&&unind[i]&&1ll*g[i].dis+undis[i]<=1ll*g[n].dis+k)//g[i].dis+undis[i]+k<=g[n].dis
        		{ok=1;break;}
        if(ok){printf("-1\n");continue;}
        sort(g+1,g+n+1,cmp);
        for(int i=1;i<=n;i++) pos[g[i].pos]=i;
        memset(f,0,sizeof(f));
        f[0][pos[1]]=1;
        for(int more=0;more<=k;more++)
        {
            for(int x=1;x<=n;x++)
            {
                if(f[more][x]==0) continue;
                for(int i=e.h[g[x].pos];i;i=e.nxt[i])
                {
                    int y=e.v[i];
                    int tmp=g[x].dis+more+e.w[i]-g[pos[y]].dis;
                    if(tmp<=k)
                    {
                        f[tmp][pos[y]]+=f[more][x];
                        while(f[tmp][pos[y]]>=p) f[tmp][pos[y]]-=p;
                    }
                }
            }
        }
        int ans=0;
        for(int i=0;i<=k;i++) ans=(ans+f[i][pos[n]])%p;
        printf("%d\n",ans);
    }
    return 0;
}