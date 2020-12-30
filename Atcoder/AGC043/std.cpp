#include<bits/stdc++.h>
using namespace std;
const int N = 2e3 + 7, M = N * 3;
int n;
int f[M][M<<1], ans;

int main() {
    int p;
	cin>>n>>p; n *= 3;
	f[0][M] = 1;
	for (int i = 0; i < n; i++)
		for (int j = -i; j <= i; j++) {
			f[i+1][j+1+M] += f[i][j+M];
			f[i+2][j-1+M] += f[i][j+M] * (i + 1);
			f[i+3][j+M] += f[i][j+M] * (i + 1) * (i + 2);
		}
	for (int j = 0; j <= n; j++) ans += f[n][j+M];
	cout<<ans%p<<endl;
	return 0;
}