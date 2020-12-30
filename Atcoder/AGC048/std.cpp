#include<bits/stdc++.h>
#define max(a,b) (a>b?a:b)
#define int long long
using namespace std;
const int N = 1e5 + 10;
int A[N], B[N];
int n, k;
signed main() {
	cin >> n >> k;
	A[n + 1] = B[n + 1] = k + 1;
	for (int i = 1; i <= n; i++)cin >> A[i];
	for (int i = 1; i <= n; i++)cin >> B[i];
	for (int i = n + 1; i >= 1; i--) {
		A[i] = A[i] - A[i - 1] - 1;
		B[i] = B[i] - B[i - 1] - 1;
	}
	int ans = 0;
	int j = 1;
	for (int i = 1; i <= n + 1; i++) {
		if (!B[i])continue;
		while (!A[j])j++;
		int sum = 0; int st = j;
		while (sum < B[i] and j <= n + 1)sum += A[j++];
		if (sum != B[i]) {
			puts("-1"); return 0;
		}
		int ed = j - 1;
		ans += max(0, i - st) + max(0, ed - i);
	}
	cout << ans << endl;
}