#include <bits/stdc++.h>
#define N 500005
#define ll long long
#define For(i,x,y) for(int i=(x);i<=(y);++i)
#define Rof(i,x,y) for(int i=(x);i>=(y);--i)
#define Edge(x) for(int i=head[x];i;i=e[i].nxt)
#define mset(x,y) memset(x,y,sizeof(x))
#define mod 998244353
using namespace std;
int fac[N],invf[N];
int C(int x,int y){ return x>=y?1ll*fac[x]*invf[y]%mod*invf[x-y]%mod:0; }
int main(){
	int n,k,ans=0;
	scanf("%d%d",&n,&k);
	fac[0]=fac[1]=1,invf[0]=invf[1]=1;
	For(i,2,k){
		fac[i]=1ll*fac[i-1]*i%mod;
		invf[i]=1ll*(1ll*mod-mod/i)*invf[mod%i]%mod;
	}
	For(i,2,k) invf[i]=1ll*invf[i-1]*invf[i]%mod;
	For(i,n,k) (ans+=C(k-1,i-1))%=mod;
	cout<<ans;
}