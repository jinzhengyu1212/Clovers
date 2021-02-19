#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>

const int MN = 3005;

int N, pa[MN], pb[MN], id[MN * 2], nx[MN * 2];
std::string str, f[MN];

int main() {
	std::cin >> N >> str;
	str = " " + str;
	for (int i = 1, a = 0, b = 0; i <= N * 2; ++i)
		if (str[i] == 'a') pa[id[i] = ++a] = i;
		else pb[id[i] = ++b] = i;
	pa[N + 1] = pb[N + 1] = N * 2 + 1, id[N * 2 + 1] = N + 1;
	for (int i = 1, j = 0; i <= N + 1; ++i)
		while (j < std::min(pa[i], pb[i]))
			nx[++j] = i;
	for (int i = N; i >= 1; --i) {
		if (pa[i] > pb[i]) {
			int j = pb[i];
			for (; pb[id[j]] < pa[id[j]] && (id[j] <= i || pb[id[j]] < pa[id[j] - 1]); ++j)
				if (id[j] >= i) f[i] += str[j];
			f[i] += f[id[j]];
		} else f[i] = "ab" + f[nx[pb[i] + 1]];
		f[i] = std::max(f[i], f[i + 1]);
        //std::cout << i<<" "<<f[i] <<'\n';
    }
	std::cout << f[1] <<'\n';
	return 0;
}