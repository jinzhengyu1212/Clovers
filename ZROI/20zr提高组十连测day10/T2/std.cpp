#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define ll long long
const int maxn = 3010;
int read(){
	char c = getchar();
	int x = 0;
	while(c < '0' || c > '9')		c = getchar();
	while(c >= '0' && c <= '9')		x = x * 10 + c - 48,c = getchar();
	return x;
}
int dp[maxn];
int c[maxn];
int fac[maxn];
int inv[maxn];
#define mod 998244353
int qpow(int x,int y){
	int ans = 1;
	while(y){
		if(y & 1)	ans = 1ll * ans * x % mod;
		x = 1ll * x * x % mod;
		y >>= 1;
	}
	return ans;
}
void add(int &x,int y){
	x += y - mod;
	x += (x >> 31) & mod;
}
int main(){
	int n = read() + 1,m = read();
	c[0] = 1;/*c[i] = c(m-2,i)*/
	fac[0] = 1;
	for(int i = 1; i <= 3001; ++i)		fac[i] = 1ll * fac[i-1] * i % mod,inv[i] = qpow(i,mod-2);
	for(int i = 0; i <= min(3000,m-3); ++i){
		c[i+1] = 1ll * c[i] * (m - 2 - i) % mod * inv[i+1] % mod;
	}
	dp[1] = inv[n];
	for(int i = 1; i <= n; ++i){
		add(dp[i+1],1ll * dp[i] * inv[n-i] % mod);
		for(int r = i + 1; r <= n; ++r){
			int len = r - i - 1;
			if(len > m - 2)	continue;
			add(dp[r],1ll * dp[i] * c[len] % mod * inv[n-i] % mod);
		}
	}
	int ans = 1ll * dp[n] * fac[n] % mod;
	printf("%d\n",ans);
	return 0;
}