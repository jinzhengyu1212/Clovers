#include<bits/stdc++.h>
using namespace std;
char Getchar() {
	static char now[1 << 20], *S, *T;
	if (T == S) {
		T = (S = now) + fread(now, 1, 1 << 20, stdin);
		if (T == S) return EOF;
	}
	return *S++;
}

int read() {
	int x = 0, f = 1;
	char ch = Getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = Getchar();
	}
	while (ch <= '9' && ch >= '0') x = x * 10 + ch - '0', ch = Getchar();
	return x * f;
}

typedef long long ll;
int n, m, a[110000], b[110000], c[110000], d[110000], u[110000], v[110000];

int main() {
	n = read(); m = read();
	for (int i = 1; i < n; i++) a[i] = read();
	for (int j = 1; j <= m; j++) b[j] = read();
	for (int i = 1; i <= n; i++) c[i] = read();
	for (int j = 1; j < m; j++) d[j] = read();
	ll ans = 0;
	for (int i = 1; i < n; i++) ans += a[i] + b[1];
	for (int j = 1; j < m; j++) ans += c[1] + d[j];

	/*for (int i=1;i<n;i++)
		for (int j=1;j<m;j++)
			ans+=min(a[i]+b[j+1],c[i+1]+d[j]);
	printf("%lld\n",ans);*/

	for (int i = 1; i < n; i++) ans += 1ll * (m - 1) * a[i];
	for (int j = 2; j <= m; j++) ans += 1ll * (n - 1) * b[j];
//	printf("%lld\n",ans);

	for (int i = 1; i < n; i++) u[i] = a[i] - c[i + 1];
	for (int j = 1; j < m; j++) v[j] = b[j + 1] - d[j];

	/*for (int i=1;i<n;i++)
		for (int j=1;j<m;j++)
			ans-=max(u[i]+v[j],0);
	printf("%lld\n",ans);*/

	sort(u + 1, u + n);
	sort(v + 1, v + m);
	int j = m - 1;
	ll sum = 0;
	for (int i = 1; i < n; i++) {
		while (j > 0 && u[i] + v[j] > 0) {
			sum += v[j];
			j--;
		}
		ans -= sum + 1ll * (m - j - 1) * u[i];
	}
	printf("%lld\n", ans);
	return 0;
}
