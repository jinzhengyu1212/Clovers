#include<bits/stdc++.h>
using namespace std;
long long n,R,sum[2][200003],fa[200003],f[200003],p[200003];
bool vis[200003];
struct node{
	long long x,c0,c1;
	bool operator <(node b)const{
		return 1ll*c0*b.c1<1ll*c1*b.c0;
	}
	bool operator >(node b)const{
		return 1ll*c0*b.c1>1ll*c1*b.c0;
	}
};
node make(long long x,long long c0,long long c1){node ret;ret.x=x;ret.c0=c0;ret.c1=c1;return ret;}
long long find(long long x){if(fa[x]==x)return x;fa[x]=find(fa[x]);return fa[x];}
void init(){
}
void solve(){cin>>n;R=1;
	for(long long i=2;i<=n;i++)
		scanf("%lld",p+i);
	priority_queue<node>Q;
	for(long long i=1;i<=n;i++){
		long long x;scanf("%lld",&x);
		sum[x][i]=1;
		Q.push(make(i,1-x,x));
	}
	for(long long i=1;i<=n;i++)fa[i]=i;
	long long ans=0,cnt1=0;vis[0]=1;
	while(Q.size()){
		node now=Q.top();Q.pop();long long x=now.x;
		if(vis[x]||now.c0!=sum[0][x]||now.c1!=sum[1][x])continue;
		vis[x]=1;
		if(vis[find(p[x])]){
			ans+=f[x]+cnt1*1ll*sum[0][x];
			cnt1+=sum[1][x];
		}else{
			long long F=find(p[x]);
			f[F]+=f[x]+1ll*sum[1][F]*sum[0][x];
			sum[0][F]+=sum[0][x]; 
			sum[1][F]+=sum[1][x];
			Q.push(make(F,sum[0][F],sum[1][F]));
			fa[find(x)]=find(F);
		}
	}
	cout<<ans<<endl;
}
int main(){
	long long T=1;
	while(T--)init(),solve();
}