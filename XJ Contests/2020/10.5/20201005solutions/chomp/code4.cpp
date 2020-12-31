#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;
const int MN = 6605;

int N;
int pa[MN * 2 + 70][MN * 2 + 70];
int fp(int *tpa, int j) { return tpa[j] ? tpa[j] = fp(tpa, tpa[j]) : j; }
int fp(int i, int j) { return fp(pa[i], j); }
struct dat {
	int a, b;
	dat() { a = b = 0; }
	dat(int A, int B) : a(A), b(B) {}
};
int vis[MN * 2 + 70];
std::vector<dat> v[MN], vcyc[MN];
int cyc[MN];

inline void Work() {
	pa[0][0] = 1;
	for (int i = 0; i <= 2 * N + 70; ++i) vis[i] = -1;
	for (int c = 0; c <= N; ++c) {
		if (c % 200 == 0) printf("%d\n", c);
		for (int b = c; ; ++b) {
			int a = fp(b, b);
			while (a <= 2 * N + 70 && vis[a] == c) a = fp(b, a + 1);
			if (a > 2 * N + 70) break;
//			printf("(%d, %d, %d)\n", a, b, c);
			v[c].push_back(dat(a, b));
			if (a == b) break;
			vis[a] = c;
		}
		for (dat p : v[c]) pa[p.b][p.a] = p.a + 1;
		dat p = v[c].front();
		for (int i = c; i <= p.a; ++i)
			if (!pa[i][p.a]) pa[i][p.a] = p.a + 1;
	}
}

int fail[55];
inline int findPeriod(int *arr, int len) {
	fail[1] = 0;
	for (int i = 2; i <= len; ++i) {
		int k = fail[i - 1];
		while (k && arr[k + 1] != arr[i]) k = fail[k];
		if (arr[k + 1] == arr[i]) ++k;
		fail[i] = k;
	}
	return len - fail[len];
}

int dif[2 * MN + 70];
inline void Simpl() {
	for (int c = 0; c <= N; ++c) {
		int maxa = 0;
		for (dat p : v[c]) maxa = std::max(maxa, p.a);
		if (maxa <= 2 * c + 10) continue;
		int siz = v[c].size();
		for (int i = siz - 1; i >= 0; --i)
			dif[siz - i] = v[c][i].a - v[c][i].b;
		int q = findPeriod(dif, 50), pos = 0;
		while (pos < siz && dif[pos + 1] == dif[pos % q + 1]) ++pos;
		for (int i = 0; i < q; ++i)
			vcyc[c].push_back(v[c][siz - pos + i]);
		v[c].resize(siz - pos);
		cyc[c] = q;
	}
}

int main() {
//	scanf("%d", &N);
	N = 6600;
	Work();
	Simpl();
//	freopen("table2.txt", "w", stdout);
//	for (int c = 0; c <= N; ++c) {
//		printf("%d: ", c);
//		for (dat p : v[c]) printf("(%d,%d),", p.a, p.b);
//		for (dat p : vcyc[c]) printf("pat(%d,%d,%d),", p.a, p.b, cyc[c]);
//		puts("");
//	}
	freopen("table3.txt", "w", stdout);
	for (int c = 0; c <= N; ++c) {
		printf("%d: ", c);
		if (vcyc[c].empty()) printf("finite(%d)\n", (int)v[c].size());
		else {
			printf("inf(%d);  ", (int)v[c].size());
			for (dat p : vcyc[c]) printf("pat(%d,%d),", p.a, p.b);
			printf("cyc=%d\n", cyc[c]);
		}
	}
	return 0;
}
