#include<bits/stdc++.h>
#define re register
#define LL long long
#define pt putchar(1)
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
const int maxn=366667;
const int M=maxn*4;
const LL inf=-1e15;
inline int read() {
	char c=getchar();int x=0,r=1;
	while(c<'0'||c>'9') {if(c=='-') r=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3ll)+(x<<1ll)+c-48,c=getchar();return r*x;
}
std::vector<int> son[M];
std::vector<LL> v[M];
struct E{int v,nxt,w;}e[M<<1];
int head[M],sum[M],vis[M],dfn[maxn],b[maxn];
int S,mnow,rn,n,num,col[maxn],rt,Mnow,tp[2],c[2][maxn];
LL g[maxn],dp[maxn][2],deep[maxn],tmp,ans;
inline int cmp(int A,int B) {return dfn[A]<dfn[B];}
inline void add(int x,int y,LL w) {
	e[++num].v=y;e[num].nxt=head[x];head[x]=num,e[num].w=w;
}
void dfs1(int x,int fa) {
	for(re int i=head[x];i;i=e[i].nxt) {
		if(e[i].v==fa) continue;
		deep[e[i].v]=deep[x]+e[i].w;
		son[x].push_back(e[i].v);v[x].push_back(e[i].w);
		dfs1(e[i].v,x);
	}
} 
void getrt(int x,int fa) {
	sum[x]=1;
	for(re int i=head[x];i;i=e[i].nxt) {
		if(vis[i>>1]||e[i].v==fa) continue;
		getrt(e[i].v,x);sum[x]+=sum[e[i].v];
		int now=max(sum[e[i].v],S-sum[e[i].v]);
		if(now<Mnow) Mnow=now,rt=i;
	}
}
struct Virtual_Tree {
	struct E{int v,nxt,w;}e[maxn<<1];
	int pos[maxn],f[21][maxn<<1],lg[maxn<<1];
	LL pre[maxn];int num,cnt,tot,head[maxn],top,st[maxn],d[maxn],root;
	inline void add(int x,int y,LL w) {
		e[++num].v=y;e[num].nxt=head[x];head[x]=num;e[num].w=w;
	}
	void dfs(int x) {
		dfn[x]=++cnt,f[0][++tot]=x;pos[x]=tot;
		for(re int i=head[x];i;i=e[i].nxt) {
			if(dfn[e[i].v]) continue;
			pre[e[i].v]=pre[x]+e[i].w;d[e[i].v]=d[x]+1;
			dfs(e[i].v);f[0][++tot]=x;
		}
	}
	inline int LCA(int x,int y) {
		int l=pos[x],r=pos[y];
		if(l>r) std::swap(l,r);
		int k=lg[r-l+1];
		if(d[f[k][l]]<d[f[k][r-(1<<k)+1]]) return f[k][l];
		return f[k][r-(1<<k)+1];
	}
	inline void build() {
		for(re int x,y,w,i=1;i<rn;i++) {
			x=read(),y=read(),w=read();
			add(x,y,w),add(y,x,w);
		}
		d[1]=1;dfs(1);memset(head,0,sizeof(head));
		for(re int i=2;i<=tot;i++) lg[i]=lg[i>>1]+1;
		for(re int j=1;j<=lg[tot];j++)
			for(re int i=1;i+(1<<(j-1))<=tot;i++)
				if(d[f[j-1][i]]<d[f[j-1][i+(1<<(j-1))]]) f[j][i]=f[j-1][i];
					else f[j][i]=f[j-1][i+(1<<(j-1))];
		for(re int i=1;i<=rn;i++) b[i]=i;
		std::sort(b+1,b+rn+1,cmp);
	}
	inline void ins(int x) {
		if(top<1) {st[++top]=x;return;}
		int lca=LCA(x,st[top]);
		if(lca==st[top]) {st[++top]=x;return;}
		while(top>1&&dfn[st[top-1]]>=dfn[lca]) 
			add(st[top-1],st[top],0),top--;
		if(lca!=st[top]) add(lca,st[top],0),st[top]=lca;
		st[++top]=x;
	}
	void tree_dp(int x) {
		dp[x][col[x]]=g[x];
		for(re int i=head[x];i;i=e[i].nxt) {
			tree_dp(e[i].v);
			tmp=max(tmp,-2ll*pre[x]+dp[x][0]+dp[e[i].v][1]);
			tmp=max(tmp,-2ll*pre[x]+dp[x][1]+dp[e[i].v][0]);
			dp[x][0]=max(dp[x][0],dp[e[i].v][0]);
			dp[x][1]=max(dp[x][1],dp[e[i].v][1]);
		}
	}
	inline void get_tree(int l,int r) {
		top=0;num=0;
		if(b[l]!=1) ins(1);
		for(re int i=l;i<=r;i++) ins(b[i]);
		while(top>1) add(st[top-1],st[top],0),top--;
		tree_dp(1);
	}
	void del(int x) {
		for(re int i=head[x];i;i=e[i].nxt) del(e[i].v);
		dp[x][0]=dp[x][1]=g[x]=inf;head[x]=0;
	}
}T;
void dfs2(int x,int fa,int o,LL d) {
	if(x<=rn) col[x]=o,g[x]=deep[x]+d;
	for(re int i=head[x];i;i=e[i].nxt) {
		if(vis[i>>1]||e[i].v==fa) continue;
		dfs2(e[i].v,x,o,d+e[i].w);
	}
}
void solve(int x,int s,int l,int r) {
	if(l>r) return;
	Mnow=M,S=s,getrt(x,0);
	if(Mnow==M) return;vis[rt>>1]=1;
	dfs2(e[rt].v,0,0,0),dfs2(e[rt^1].v,0,1,e[rt].w);
	tmp=inf;T.get_tree(l,r);
	ans=max(ans,tmp);
	tp[0]=tp[1]=0;T.del(1);
	for(re int i=l;i<=r;i++) c[col[b[i]]][++tp[col[b[i]]]]=b[i];
	for(re int i=l,k=1;k<=tp[0];i++,k++) b[i]=c[0][k];
	for(re int i=l+tp[0],k=1;k<=tp[1];i++,k++) b[i]=c[1][k];
	int now=s-sum[e[rt].v],k=rt,L=l+tp[0]-1,R=r-tp[1]+1;
	solve(e[k].v,sum[e[k].v],l,L);
	solve(e[k^1].v,now,R,r);
}
int main() {
	rn=n=read();
	for(re int w,x,y,i=1;i<n;i++) {
		x=read(),y=read(),w=read();
		add(x,y,w),add(y,x,w);
	}
	dfs1(1,0);num=1;memset(head,0,sizeof(head));
	int s[2];
	for(re int i=1;i<=n;i++) {
		int t=son[i].size();
		if(!t) continue;
		if(t==1) {
			add(i,son[i][0],v[i][0]),add(son[i][0],i,v[i][0]);
			continue;
		}
		if(t==2) {
			add(i,son[i][0],v[i][0]),add(son[i][0],i,v[i][0]);
			add(son[i][1],i,v[i][1]),add(i,son[i][1],v[i][1]);
			continue;
		}
		s[0]=++n,s[1]=++n;
		add(i,s[0],0),add(s[0],i,0);add(i,s[1],0),add(s[1],i,0);
		for(re int j=0;j<v[i].size();j++)
			son[s[j&1]].push_back(son[i][j]),v[s[j&1]].push_back(v[i][j]);
	}
	T.build();ans=inf;
	for(re int i=1;i<=rn;i++) dp[i][0]=dp[i][1]=g[i]=inf;
	solve(1,n,1,rn);ans>>=1ll;
	//std::cout<<ans<<"\n";
	for(re int i=1;i<=n;i++) ans=max(ans,deep[i]-T.pre[i]);
	std::cout<<ans<<"\n";
	return 0;
}