#include<cstdio>
#include<algorithm>
#define L 1<<25
#define C (c=*A++)
#define ENS //__attribute__((optimize("-O2")))
#define NES //__attribute__((optimize("-O2"))) __inline__ __attribute__((always_inline))
#define N 300001

using namespace std;int n,m,p,f[N],g[N],d[N],fa[N],e[N],E[N],z[N],mx[N],s[N],w[N],S[N],tl,li[N],q[N<<1],a[N],nt[N],nr[N<<1],et,wt,ss[19];char fl[L],*A=fl;long long MAPLE;
NES int F(int x){return f[x]?f[x]=F(f[x]):x;}NES int G(int x){return g[x]?g[x]=G(g[x]):(F(x)==F(fa[x])?g[x]=G(fa[x]):x);}
NES int LCA(int a,int b){for(;z[a]!=z[b];d[z[a]]>d[z[b]]?a=fa[z[a]]:b=fa[z[b]]);return d[a]>d[b]?b:a;}
NES void read(int&x){char c;for(x=0;'0'>C||c>'9';);while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+c-48,C;}NES void print(long long x){if(!x)putchar(48);else{for(wt=0;x;ss[++wt]=x%10,x/=10);for(;wt;putchar(ss[wt--]+48));}}
struct ques{int l,r,w,t;NES bool operator<(const ques&b)const{return w<b.w;}}t[N];
struct edge{int l,r;NES void add(int x,int y){l=F(l),r=F(r),q[++et]=l,nr[et]=E[r],E[r]=et,q[++et]=r,nr[et]=E[l],E[l]=et;}}cd[N];
ENS int main()
{int i,test,x,y;
	for(*(fl+fread(fl,1,L,stdin))=EOF,read(n),read(m),read(p),w[1]=d[1]=1,i=2;i<=n;read(fa[i]),d[i]=d[fa[i]]+1,w[i]=1,i++);
	for(i=n;i>1;i--)if(w[fa[i]]+=w[i],w[i]>w[mx[fa[i]]])mx[fa[i]]=i;for(i=1;i<=n;z[i]=i==mx[fa[i]]?z[fa[i]]:i,i++);
	for(i=1;i<=m;read(t[i].l),read(t[i].r),read(t[i].w),t[i].t=i,i++);for(i=1;i<=p;read(test),read(x),read(y),cd[++et]=(edge){x,y},nt[et]=e[test],e[test]=et,i++);
	for(sort(t+1,t+m+1),test=1;test<=m;test++)
	{int tmp,stmp,tp,NE=t[test].w,ld,rd;
		for(ld=d[t[test].l]+1,rd=d[t[test].r]+1,x=G(t[test].l),y=G(t[test].r),tl=0;x!=y;)
			if(d[x]>d[y]){if(!s[tmp=F(x)])li[++tl]=tmp;s[tmp]+=ld-d[x],ld=d[x],x=G(fa[x]);}
			else{if(!s[tmp=F(y)])li[++tl]=tmp;s[tmp]+=rd-d[y],rd=d[y],y=G(fa[y]);}
		if(!s[tmp=F(x)])li[++tl]=tmp;s[tmp]+=ld+rd-(d[LCA(t[test].l,t[test].r)]<<1)-1;
		for(et=0,y=e[t[test].t];y;cd[y].add(t[test].l,t[test].r),y=nt[y]);
		for(tp=0,i=1;i<=tl;i++)
		{
			for(y=E[li[i]];y;S[F(q[y])]++,y=nr[y]);
			for(tmp=0,stmp=s[li[i]],x=1;x<=tp;x++)
				if(S[a[x]]<(long long)s[a[x]]*s[li[i]])MAPLE+=NE,f[a[x]]=li[i],stmp+=s[a[x]];
				else S[a[++tmp]=a[x]]=0;
			s[a[tp=++tmp]=li[i]]=stmp,S[li[i]]=0;
		}for(i=1;i<=tp;E[a[i]]=s[a[i]]=0,i++);
	}print(MAPLE);
}