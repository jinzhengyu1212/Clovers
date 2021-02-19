#include <cstdio>
#include <cstring>

const int Mod = 1000000007;
const int MN = 100005;

int N, Sum; char s[MN];
int nx[MN][2], f[MN];

int main() {
	scanf("%s", s + 1), N = strlen(s + 1);
	int flag = 1;
	for (int i = 1; i < N; ++i) if (s[i] == s[i + 1]) flag = 0;
	if (flag) return puts("1"), 0;
	f[N + 1] = 1, nx[N + 1][0] = nx[N + 1][1] = nx[N + 2][0] = nx[N + 2][1] = N + 2;
	for (int i = N; i >= 1; --i) {
		(Sum += s[i] == 'a' ? 1 : 2) %= 3;
		nx[i][0] = s[i] == 'a' ? i + 1 : s[i + 1] == 'b' ? i + 2 : nx[i + 2][0];
		nx[i][1] = s[i] == 'b' ? i + 1 : s[i + 1] == 'a' ? i + 2 : nx[i + 2][1];
		f[i] = (f[nx[i][0]] + f[nx[i][1]] + (Sum == 0)) % Mod;
	}
	printf("%d\n", (f[1] - (Sum == 0) + Mod) % Mod);
	return 0;
}