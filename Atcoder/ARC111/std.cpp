#include <bits/stdc++.h>
using namespace std;
long long mod = 998244353; 
long long power(long long a, long long n){
	long long mul = a % mod; 
	long long res = 1; 
	for(int i = 0; i < 62; i++){
		if((n >> i) & 1){
			res *= mul; res %= mod; 
		}
		mul = mul * mul % mod; 
	}
	return res; 
}
long long inv(long long a){
	return power(a, mod - 2); 
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	long long ans = 0; 
	long long N, M, Q; cin >> N >> M >> Q;
	long long A = (N * (N + 1) % mod) * (M * 2 + 1) % mod;   
	long long B = inv(A);
	for(long long i = 1; i <= N; i++){
		long long C = (mod + A - (2 * M * i % mod) * (N - i + 1) % mod) % mod; 
		long long R = C * B % mod; 
		if(R == 1) continue; 
		long long X = (M - 1) * 499122177 % mod;
		long long Y = (power(R, Q) - 1) * inv(R - 1) % mod; 
		long long Z = X * (mod + Q - Y) % mod; 
		long long I = 2 * i * (N - i + 1) % mod; 
		Z *= I; Z %= mod; Z *= B; Z %= mod;  
		ans += Z; ans %= mod;
	}
	long long T = power(N * (N + 1) / 2, Q) * power(M * 2 + 1, Q) % mod; 
	cout << ans * T % mod << "\n"; 
}
