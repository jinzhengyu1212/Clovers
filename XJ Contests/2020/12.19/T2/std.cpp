#include<bits/stdc++.h>
#define L(i, j, k) for(int i = j, i##E = k; i <= i##E; i++)
#define R(i, j, k) for(int i = j, i##E = k; i >= i##E; i--)
#define ll long long
#define ull unsigned long long
#define db double
#define pii pair<int, int>
#define mkp make_pair
using namespace std;
const int N = 2e5 + 7;
const int C = 202;
const int mod = 998244353;
int n, m, q, f[N], las[N];
int mata[N + C][C], dya[N + C][C];
int matb[N + C][C], dyb[N + C][C];
int Fa(int t, int x, int y) {
    if(x == m + 1) return mata[t][y];
    else return (mod - mata[dya[t][x]][y]) % mod;
}
int Fb(int t, int x, int y) {
    if(y == m + 1) return matb[t][x];
    else return matb[dyb[t][y]][x];
}
int main() {
    scanf("%d%d%d", &n, &m, &q);
    if(q == 0) return 0;
    L(i, 1, n) scanf("%d", &f[i]);
    L(i, 1, m) mata[i + n + 1][i] = mod - 1, matb[i + n + 1][i] = 1, dya[n + 1][i] = dyb[0][i] = i + n + 1;
    mata[n + 1][m + 1] = matb[0][m + 1] = 1;
    R(i, n, 1) {
        L(j, 1, m) {
            if(f[i] != j) dya[i][j] = dya[i + 1][j];
            else dya[i][j] = i + 1;
        }
        L(j, 1, m + 1) mata[i][j] = (2ll * Fa(i + 1, m + 1, j) % mod + Fa(i + 1, f[i], j)) % mod;
    }
    L(i, 1, n) {
        L(j, 1, m) {
            if(f[i] != j) dyb[i][j] = dyb[i - 1][j];
            else dyb[i][j] = i - 1;
        }
        L(j, 1, m + 1) matb[i][j] = (2ll * Fb(i - 1, j, m + 1) % mod + mod - Fb(i - 1, j, f[i])) % mod;
    }
    while(q--) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        int res = 0;
        L(i, 1, m + 1) (res += 1ll * (2ll * Fa(a + 1, m + 1, i) % mod + Fa(a + 1, b, i)) % mod * Fb(a - 1, i, c) % mod) %= mod;
        printf("%d\n", res);
    }
    return 0;
}