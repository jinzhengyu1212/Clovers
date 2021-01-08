#include<bits/stdc++.h>
#define fo(i,a,b)for(int i=a,_e=b;i<=_e;++i)
#define fd(i,a,b)for(int i=b,_e=a;i>=_e;--i)
#define ll long long
using namespace std;
const int N=1005;
const ll inf=1e18;
int n,k,mn,mx,T,js;
int S[N],E[N],d[N*1000],fr[N*3],la[N*3];
struct edge{int y,ne;ll l,c;}e[N*20];
ll ans,f[N*3];
bool bz[N*3];
void link(int x,int y,ll l,ll c){
	e[++js]=(edge){y,la[x],l,c};la[x]=js;
	e[++js]=(edge){x,la[y],0,-c};la[y]=js;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>k>>mn>>mx;mx=k-mx;
	fo(i,1,n)cin>>S[i];
	fo(i,1,n)cin>>E[i],ans+=E[i];
	T=(n-k+1)*2+2;js=1;
	fo(i,1,n)
		link(i<=k?1:1+(i-k)*2,min(T-1,1+i*2),1,E[i]-S[i]);
	link(0,1,mx,0);link(T-1,T,mn,0);
	fo(i,2,T-2)
		if(i&1)link(0,i,mx,0),link(i,T,mn,0);
		else link(0,i,mn,0),link(i,T,mx,0);
	fo(i,1,T-2)
		if(i&1)link(i,i+1,inf,0);else link(i+1,i,inf,0);
	for(;;){
		fo(i,1,T)f[i]=inf;
		d[1]=0;bz[0]=1;
		for(int l=0,r=1,x,y;x=d[++l],l<=r;bz[x]=0)
			for(int i=la[x];i;i=e[i].ne)
				if(e[i].l&&f[y=e[i].y]>f[x]+e[i].c){
					f[y]=f[x]+e[i].c;
					fr[y]=i^1;
					if(!bz[y])d[++r]=y,bz[y]=1;
				}
		if(f[T]==inf)break;
		ans-=f[T];
		ll mi=inf;
		for(int x=T;x;x=e[fr[x]].y)
			mi=min(mi,e[fr[x]^1].l);
		for(int x=T;x;x=e[fr[x]].y)
			e[fr[x]].l+=mi,e[fr[x]^1].l-=mi;
	}
	printf("%lld\n",ans);
	fo(i,1,n)putchar(e[i*2].l?'E':'S');
}