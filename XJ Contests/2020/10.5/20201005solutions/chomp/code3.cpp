#include <cstdio>
#include <algorithm>
#include <vector>

const int MN = 845;

int N;
std::vector<bool> f[MN][MN];

int main() {
	freopen("table1.txt", "w", stdout);
//	scanf("%d", &N);
	N = 843;
	for (int a = 1; a <= N; ++a) {
		fprintf(stderr, "a = %d\n", a);
		for (int b = 0; b <= a; ++b) {
			f[a][b].resize(b + 1);
			for (int c = 0; c <= b; ++c) {
				int qwqwq = 0;
				for (int k = 0; k < c; ++k) {
					if (k && !f[k][k][k]) qwqwq = 1;
					if (!f[a][k][k]) qwqwq = 1;
					if (!f[a][b][k]) qwqwq = 1;
					if (qwqwq) break;
				}
				if (qwqwq) {
					f[a][b][c] = 1;
					continue;
				}
				for (int k = c; k < b; ++k) {
					if (k && !f[k][k][c]) qwqwq = 1;
					if (!f[a][k][c]) qwqwq = 1;
					if (qwqwq) break;
				}
				if (qwqwq) {
					f[a][b][c] = 1;
					continue;
				}
				for (int k = b; k < a; ++k)
					if (k && !f[k][b][c]) qwqwq = 1;
				f[a][b][c] = qwqwq;
			}
		}
	}
	fprintf(stderr, "done\n");
	for (int k = 0; k <= 408; ++k) {
		printf("%d: ", k);
		int cnt = 0, maxa = 0;
		for (int b = k; b <= N; ++b)
			for (int a = std::max(b, 1); a <= N; ++a) if (!f[a][b][k])
				++cnt, maxa = a;
		fprintf(stderr, "%d: (cnt, maxa) = (%d, %d)\n", k, cnt, maxa);
		if (maxa < 835) {
			for (int b = k; b <= N; ++b)
				for (int a = std::max(b, 1); a <= N; ++a) if (!f[a][b][k])
					printf("(%d,%d),", a, b);
			printf("\n%d: %d\n", k, cnt);
		} else {
			int zb = 0;
			for (int b = N; b >= k; --b) if (!f[N][b][k]) { zb = b; break; }
			int xb = zb, delta = N - zb;
			while (xb >= k && !f[xb + delta][xb][k]) --xb;
			++xb;
			for (int b = k; b < xb; ++b)
				for (int a = std::max(b, 1); a <= N; ++a) if (!f[a][b][k])
					printf("(%d,%d),", a, b);
			printf("pat(%d+k,%d+k),...", xb + delta, xb);
			printf("\n%d: inf(%d)\n", k, cnt);
		}
		puts("============");
	}
	return 0;
}
