#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100005,LOG=20;
int Q;
inline LL read()
{
	LL ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){ret=ret*10+ch-'0';ch=getchar();}
	return ret*f;
}
struct ChairmanTree               //封装好的主席树
{
	int tot,T[maxn];
	struct Node{int L,R,Sum;}Tree[maxn*LOG];
	int Build(int L,int R)
	{
		int rt=++tot,mid=L+R>>1;
		if(L>=R) return rt;
		Tree[rt].L=Build(L,mid);
		Tree[rt].R=Build(mid+1,R);
		if(rt==1) T[0]=rt;
		return rt;
	}
	int Update(int num,int pre,int L,int R)
	{
		int rt=++tot,mid=L+R>>1;
		Tree[rt].L=Tree[pre].L;Tree[rt].R=Tree[pre].R;Tree[rt].Sum=Tree[pre].Sum+1;
		if(L>=R) return rt;
		if(num<=mid) Tree[rt].L=Update(num,Tree[pre].L,L,mid);
		else Tree[rt].R=Update(num,Tree[pre].R,mid+1,R);
		return rt;
	}
	int Query(int u,int v,int k,int L,int R)
	{
		int mid=L+R>>1,x=Tree[Tree[v].L].Sum-Tree[Tree[u].L].Sum;
		if(L==R) return mid;
		if(x>=k) return Query(Tree[u].L,Tree[v].L,k,L,mid);
		else return Query(Tree[u].R,Tree[v].R,k-x,mid+1,R);
	}
}CT;
namespace TemplateTree           //模板树
{
	int n,father[maxn][LOG],dep[maxn],idx,que[maxn],S[maxn],T[maxn],tot,lnk[maxn],son[maxn*2],nxt[maxn*2];
	inline void add_e(int x,int y){tot++;son[tot]=y;nxt[tot]=lnk[x];lnk[x]=tot;}
	void Build(int now,int fa)   //把树上的一些信息构造好
	{
		S[now]=++idx;que[idx]=now;father[now][0]=fa;dep[now]=dep[fa]+1;
		for(int i=1;i<=16;i++) father[now][i]=father[father[now][i-1]][i-1];
		for(int i=lnk[now];i;i=nxt[i])
			if(son[i]!=fa)
				Build(son[i],now);
		T[now]=idx;
	}
	inline void BuildCT()      //初始化主席树
	{
		CT.Build(1,n);
		for(int i=1;i<=n;i++) CT.T[i]=CT.Update(que[i],CT.T[i-1],1,n);
	}
	inline void Input()       //读入数据
	{
		for(int i=1;i<n;i++)
		{
			int a=read(),b=read();
			add_e(a,b);add_e(b,a);
		}
		Build(1,0);BuildCT();
	}
	int GetDist(int u,int v)    //LCA求亮点间距离
	{
		int ret=0;
		if(dep[u]<dep[v]) swap(u,v);
		for(int i=16;i>=0;i--) if(dep[father[u][i]]>=dep[v]){ret+=(1<<i);u=father[u][i];}
		for(int i=16;i>=0;i--) if(father[u][i]!=father[v][i]){ret+=(1<<i+1);u=father[u][i];v=father[v][i];}
		if(u==v) return ret;
		return ret+2;
	}
}
namespace BigTree             //大树
{
	int n,m,father[maxn][LOG],dep[maxn],pre[maxn];LL dist[maxn][LOG],S[maxn],T[maxn],lnk[maxn],cnt;
	inline int GetRoot(LL u)
	{
		int L=1,R=n,mid;
		while(L<=R)
		{
			mid=L+R>>1;
			S[mid]<=u?L=mid+1:R=mid-1;
		}
		return R;
	}
	inline int GetPre(LL u)
	{
		int rt=GetRoot(u);
		return CT.Query(CT.T[TemplateTree::S[pre[rt]]-1],CT.T[TemplateTree::T[pre[rt]]],u-S[rt]+1,1,TemplateTree::n);
	}
	inline void Build()        //初始化大树
	{
		n=1;dep[1]=1;pre[1]=1;S[1]=1;T[1]=TemplateTree::n;cnt=T[1];
		for(int i=1;i<=m;i++)
		{
			int fr=read();LL to=read();int rt=GetRoot(to);
			n++;dep[n]=dep[rt]+1;lnk[n]=to;pre[n]=fr;S[n]=cnt+1;T[n]=cnt+TemplateTree::T[fr]-TemplateTree::S[fr]+1;cnt=T[n];
			father[n][0]=rt;dist[n][0]=TemplateTree::dep[GetPre(to)]-TemplateTree::dep[pre[rt]]+1;
			for(int j=1;j<=16;j++){father[n][j]=father[father[n][j-1]][j-1];dist[n][j]=dist[n][j-1]+dist[father[n][j-1]][j-1];}
		}
	}
	inline LL Solve(LL u,LL v)     //计算答案(写的真丑QwQ)
	{
		LL ret=0;int rtu=GetRoot(u),rtv=GetRoot(v);
		if(rtu==rtv) return TemplateTree::GetDist(GetPre(u),GetPre(v));
		if(dep[rtu]<dep[rtv]){swap(u,v);swap(rtu,rtv);}
		ret+=TemplateTree::dep[GetPre(u)]-TemplateTree::dep[pre[rtu]];u=rtu;
		for(int i=16;i>=0;i--) if(dep[father[u][i]]>dep[rtv]){ret+=dist[u][i];u=father[u][i];}
		if(GetRoot(lnk[u])==rtv) return ret+1+TemplateTree::GetDist(GetPre(lnk[u]),GetPre(v));
		ret+=TemplateTree::dep[GetPre(v)]-TemplateTree::dep[pre[rtv]];v=rtv;
		if(dep[u]>dep[v]){ret+=dist[u][0];u=father[u][0];}
		for(int i=16;i>=0;i--) if(father[u][i]!=father[v][i]){ret+=dist[u][i]+dist[v][i];u=father[u][i];v=father[v][i];}
		u=lnk[u];v=lnk[v];ret+=2;
		return ret+TemplateTree::GetDist(GetPre(u),GetPre(v));
	}
}
int main()                    //好简洁的主函数
{
	TemplateTree::n=read();BigTree::m=read();Q=read();
	TemplateTree::Input();BigTree::Build();
	while(Q--) printf("%lld\n",BigTree::Solve(read(),read()));
	return 0;
}