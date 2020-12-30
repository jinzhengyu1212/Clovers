#include<cstdio>
const int mod=1000000007,hmod=10000019;
int n,a[1000010],p[1000010],f[1000010];
long long sz[1000010];
int g[1000010];
long long gcd(long long a,long long b){return b?gcd(b,a%b):a;}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",a+i),sz[i]=a[i];
	for(int i=2;i<=n;i++)scanf("%d",p+i);
	for(int i=n;i>1;i--)sz[p[i]]+=sz[i];
	for(int i=1;i<=n;i++){
		long long j=sz[1]/gcd(sz[1],sz[i]);
		if(j<=n)g[j]++;
	}
	for(int i=n;i;i--)
		for(int j=i*2;j<=n;j+=i)g[j]+=g[i];
	for(int i=n;i>=1;i--)if(g[i]>=i){
		f[i]=1;
		for(int j=i*2;j<=n;j+=i)(f[i]+=f[j])%=mod;
	}
	printf("%d\n",f[1]);
}
