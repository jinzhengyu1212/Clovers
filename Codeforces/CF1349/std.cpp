#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])

char read_str[1 << 25], *CH = read_str;
#define getchar() (*CH++)
LL read() {
  char ch = getchar();
  int fl = 0;
  LL x = 0;
  while (!isdigit(ch)) {
    if (ch == '-') fl = 1;
    ch = getchar();
  }
  while (isdigit(ch)) x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
  return fl ? -x : x;
}
void rstr(char *s) {
  char *x = s;
  char ch = getchar();
  while (ch == ' ' || ch == '\n' || ch == '\r') ch = getchar();
  while (ch != ' ' && ch != '\n' && ch != '\r') {
    *x++ = ch;
    ch = getchar();
  }
}

const int Max_n = 3e5 + 5, mod = 998244353;
int n, m, a[Max_n];
int f[Max_n];

int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = (LL)a * a % mod)
    if (b & 1) res = (LL)res * a % mod;
  return res;
}

namespace Input {
void main() {
  scanf("%d",&n);
  for (int i = 1; i <= n; i++) scanf("%d",&a[i]),m+=a[i];
}
}  // namespace Input

namespace Solve {
void main() {
  f[0] = n - 1;
  int t = (LL)m * (n - 1) % mod;
  for (int i = 1; i < m; i++)
    f[i] = ((LL)i * (n - 1) % mod * f[i - 1] % mod + t) * ksm(m - i) % mod;
  for (int i = m - 1; ~i; i--) (f[i] += f[i + 1]) %= mod;
  int ans = 0;
  for(int i=0;i<m;i++) cout<<f[i]<<" "; cout<<endl;
  for (int i = 1; i <= n; i++) (ans += f[a[i]]) %= mod;
  (ans += mod - (LL)(n - 1) * f[0] % mod) %= mod;
  ans = (LL)ans * ksm(n) % mod;
  cout << ans << endl;
}
}  // namespace Solve

int main() {
  Input::main();
  Solve::main();
}