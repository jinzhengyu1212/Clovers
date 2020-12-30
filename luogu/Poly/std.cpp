#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define f(i, l, r) for (int i = l; i <= r; ++i)
#define rf(i, r, l) for (int i = r; i >= l; --i)
#define all(x) (x).begin(), (x).end()
#define lch (o << 1)
#define rch (o << 1 | 1)
#define mid ((l + r) >> 1)
#define mem(x, y) memset(x, y, sizeof(x))
#define mod1(x) ((x >= mod) && (x -= mod))
#define mod2(x) ((x < 0) && (x += mod))
constexpr int mod = 998244353;
ll power(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
typedef unsigned int uint;
namespace Poly {
int W;
pii operator*(pii a, pii b) {
    pii c;
    c.first = ((ll)a.first * b.first + (ll)a.second * b.second % mod * W) % mod;
    c.second = ((ll)a.first * b.second + (ll)a.second * b.first) % mod;
    return c;
}
pii piipower(pii a, ll b) {
    pii res = { 1, 0 };
    while (b) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
inline int mosqrt(int x) {
    pii a;
    int y = rand() % mod;
    while (power(W = ((ll)y * y % mod - x + mod) % mod, (mod - 1) >> 1) <= 1) y = rand() % mod;
    if (W < 0)
        W += mod;
    a.first = y;
    a.second = 1;
    a = piipower(a, mod + 1 >> 1);
    return min(a.first, mod - a.first);
}
typedef vector<uint> poly;
constexpr uint Max_size = 1 << 21 | 5;
constexpr int gn = 3;
inline uint mf(uint x) { return (static_cast<ll>(x) << 32) / mod; }
int sz;
uint w[Max_size], w_mf[Max_size];
inline void init(int n) {
    for (sz = 2; sz < n; sz <<= 1)
        ;
    uint pr = power(gn, (mod - 1) / sz);
    w[sz / 2] = 1, w_mf[sz / 2] = mf(w[sz / 2]);
    for (int i = 1; i < sz / 2; ++i)
        w[sz / 2 + i] = (ll)w[sz / 2 + i - 1] * pr % mod, w_mf[sz / 2 + i] = mf(w[sz / 2 + i]);
    for (int i = sz / 2 - 1; i; --i) w[i] = w[i << 1], w_mf[i] = w_mf[i << 1];
}
inline void NTT(poly& A, const int L) {
    for (int d = L >> 1; d; d >>= 1)
        for (int i = 0; i != L; i += d << 1)
            for (int j = 0; j != d; ++j) {
                uint x = A[i + j] + A[i + d + j];
                if (x >= mod * 2)
                    x -= mod * 2;
                ll t = A[i + j] + mod * 2 - A[i + d + j];
                ll q = t * w_mf[d + j] >> 32;
                uint y = t * w[d + j] - q * mod;
                A[i + j] = x, A[i + d + j] = y;
            }
}
inline void INTT(poly& A, const int L) {
    for (int d = 1; d != L; d <<= 1)
        for (int i = 0; i != L; i += d << 1)
            for (int j = 0; j != d; ++j) {
                uint x = A[i + j];
                if (x >= mod * 2)
                    x -= mod * 2;
                ll y = A[i + d + j];
                ll q = y * w_mf[d + j] >> 32;
                ll t = y * w[d + j] - q * mod;
                A[i + j] = x + t, A[i + d + j] = x + mod * 2 - t;
            }
    reverse(A.begin() + 1, A.end());
    int k = __builtin_ctz(L);
    for (int i = 0; i != L; ++i) {
        ll m = -A[i] & (L - 1);
        A[i] = (A[i] + m * mod) >> k;
    }
}
poly operator*(poly a, poly b) {
    int n = a.size() + b.size() - 1, R = 2;
    for (; R <= n; R <<= 1)
        ;
    init(R);
    a.resize(R), b.resize(R);
    NTT(a, R);
    NTT(b, R);
    f(i, 0, R - 1) a[i] = 1ll * b[i] * a[i] % mod;
    INTT(a, R);
    a.resize(n);
    f(i, 0, n - 1) if (a[i] >= mod) a[i] -= mod;
    return a;
}
poly operator+(poly a, poly b) {
    int n = max(a.size(), b.size());
    a.resize(n), b.resize(n);
    f(i, 0, n - 1) a[i] += b[i], mod1(a[i]);
    return a;
}
poly operator-(poly a, poly b) {
    int n = max(a.size(), b.size());
    a.resize(n), b.resize(n);
    f(i, 0, n - 1) a[i] = a[i] + mod - b[i], mod1(a[i]);
    return a;
}
void inv(poly& a) {
    int n = a.size();
    if (n == 1) {
        a[0] = power(a[0], mod - 2);
        return;
    }
    poly b = a;
    b.resize((n + 1) / 2);
    inv(b);
    int R = 2;
    for (; R <= n << 1; R <<= 1)
        ;
    init(R);
    a.resize(R), b.resize(R);
    NTT(a, R);
    NTT(b, R);
    f(i, 0, R - 1) a[i] = (2 + mod - 1ll * a[i] * b[i] % mod) * b[i] % mod;
    INTT(a, R);
    a.resize(n);
    f(i, 0, n - 1) if (a[i] >= mod) a[i] -= mod;
}
poly operator/(poly a, poly b) {
    reverse(all(a));
    reverse(all(b));
    int n = a.size(), m = b.size();
    b.resize(n - m + 1);
    inv(b);
    a = a * b, a.resize(n - m + 1);
    reverse(all(a));
    return a;
}
poly operator%(poly a, poly b) {
    a = a - a / b * b;
    a.resize(b.size());
    return a;
}
const int inv2 = power(2, mod - 2);
void Sqrt(poly& a) {
    int n = a.size();
    if (n == 1) {
        a[0] = mosqrt(a[0]);
        return;
    }
    poly h = a;
    h.resize((n + 1) >> 1);
    Sqrt(h);
    h.resize(n);
    poly g = h;
    inv(g);
    int R = 2;
    for (; R <= n << 1; R <<= 1)
        ;
    init(R);
    a.resize(R), h.resize(R), g.resize(R);
    NTT(a, R);
    NTT(h, R);
    NTT(g, R);
    f(i, 0, R - 1) a[i] = 1ll * inv2 * (1ll * h[i] % mod + 1ll * a[i] * g[i] % mod) % mod;
    INTT(a, R);
    a.resize(n);
    f(i, 0, n - 1) if (a[i] >= mod) a[i] -= mod;
}
void deri(poly& a) {
    int w = a.size();
    f(i, 1, w - 1) a[i - 1] = 1ll * i * a[i] % mod;
    a.pop_back();
}
int Inv[Max_size];
void inte(poly& a) {
    Inv[0] = Inv[1] = 1;
    int w = a.size();
    f(i, 2, w + 1) Inv[i] = 1ll * (mod - mod / i) * Inv[mod % i] % mod;
    a.push_back(0);
    rf(i, w, 1) a[i] = 1ll * a[i - 1] * Inv[i] % mod;
    a[0] = 0;
}
void ln(poly& a) {
    int n = a.size();
    poly b = a;
    inv(b);
    poly c = a;
    deri(c);
    a = b * c, a.resize(n - 1);
    inte(a);
}
void exp(poly& a) {
    int n = a.size();
    if (n == 1) {
        a[0] = 1;
        return;
    }
    poly b = a;
    b.resize((n + 1) >> 1), exp(b);
    b.resize(n);
    poly c = b;
    ln(c);
    f(i, 0, n - 1) c[i] = a[i] + mod - c[i], mod1(c[i]);
    c[0]++, b = b * c;
    b.resize(n);
    a = b;
}
void poly_pow(poly& a, int b) {  // a[0]=1
    ln(a);
    int w = a.size();
    f(i, 0, w - 1) a[i] = 1ll * a[i] * b % mod;
    exp(a);
}
void poly_pow2(poly& a, int times, bool big_p,
               int times2) {  //设求a^k  times=k%(mod-1),big_p=(k>=mod),times2%=mod; 不保证a[0]=1
    int asz = a.size();
    if (times2 == 0) {
        a[0] = power(a[0], times);
        f(i, 1, asz - 1) a[i] = 0;
        return;
    }
    int i, j, k = 1, wy = 0, n = asz;
    if (a[0] == 0) {
        for (i = 1; i < n; i++)
            if (a[i])
                break;
        if ((ll)i * times2 >= asz || big_p) {
            f(i, 0, asz - 1) a[i] = 0;
            return;
        }
        a.erase(a.begin(), a.begin() + i);
        wy = i * times2;
        n -= i;
    }
    if (a[0] > 1) {
        k = power(a[0], mod - 2);
        f(i, 1, n - 1) a[i] = (ll)a[i] * k % mod;
        k = power(a[0], times);
        a[0] = 1;
    }
    poly_pow(a, times2);
    f(i, 0, n - 1) a[i] = (ll)a[i] * k % mod;
    a.resize(asz);
    rf(i, asz - 1, wy) a[i] = a[i - wy];
    f(i, 0, wy - 1) a[i] = 0;
}
const int point_num = 1e5 + 10;
poly f, g, q, r;
poly Z[4 * point_num];
int X[point_num], F[point_num];
void pre(int l, int r, int o) {
    if (l == r) {
        Z[o].resize(2);
        Z[o][1] = mod - X[l], mod1(Z[o][1]);
        Z[o][0] = 1;
        return;
    }
    pre(l, mid, lch);
    pre(mid + 1, r, rch);
    Z[o] = Z[lch] * Z[rch];
}
void mul2(poly& a, poly b) {
    int m = b.size();
    int n = a.size();
    int R = 2;
    for (; R <= n; R <<= 1)
        ;
    init(R);
    reverse(all(b));
    a.resize(R), b.resize(R);
    NTT(a, R);
    NTT(b, R);
    f(i, 0, R - 1) a[i] = 1ll * b[i] * a[i] % mod;
    INTT(a, R);
    a.resize(n);
    a.erase(a.begin(), a.begin() + m - 1);
    f(i, 0, n - m) if (a[i] >= mod) a[i] -= mod;
}
void work(int l, int r, int o, poly& tmp) {
    if (l == r) {
        F[l] = tmp[0];
        return;
    }
    poly L = tmp;
    mul2(L, Z[rch]);
    work(l, mid, lch, L);
    mul2(tmp, Z[lch]);
    work(mid + 1, r, rch, tmp);
}
void mul_v(poly f, int m) {  //函数为f 需要计算的点为m个 储存在X[1,m] 结果在F[1,m]
    if (m + 1 > f.size())
        f.resize(m + 1);
    m = max((int)f.size() - 1, m);
    pre(1, m, 1);
    poly h = Z[1];
    inv(h);
    reverse(all(h));
    poly g = f;
    g = g * h;
    g.resize(f.size() + m);
    g.erase(g.begin(), g.begin() + f.size());
    work(1, m, 1, g);
    f(i, 1, m) F[i] = (f[0] + (ll)F[i] * X[i] % mod) % mod, mod2(F[i]);
}
void qiuzhi() {
    int n, m;
    cin >> n >> m;
    f.resize(n + 1);
    f(i, 0, n) cin >> f[i];
    f(i, 1, m) cin >> X[i];
    mul_v(f, m);
    f(i, 1, m) cout << F[i] << "\n";
}
int pnum, y[point_num];
poly getf(int l, int r, int o) {
    if (l == r)
        return { (uint)(power(F[l], mod - 2) * y[l] % mod) };
    return Z[lch] * getf(mid + 1, r, rch) + Z[rch] * getf(l, mid, lch);
}
void chazhi() {
    cin >> pnum;
    f(i, 1, pnum) cin >> X[i] >> y[i];
    pre(1, pnum, 1);
    g = Z[1];
    reverse(all(g));
    deri(g);
    mul_v(g, pnum);
    f(i, 1, 4 * pnum) reverse(all(Z[i]));
    f = getf(1, pnum, 1);
    f(i, 0, pnum - 1) cout << f[i] << " ";
}
const int muli = 86583718, fmuli = mod - muli, invmuli = power(muli, mod - 2);
void polysin(poly& a) {
    poly b = a;
    int w = a.size();
    f(i, 0, w - 1) a[i] = (ll)a[i] * muli % mod;
    f(i, 0, w - 1) b[i] = (ll)b[i] * fmuli % mod;
    exp(a);
    exp(b);
    a = a - b;
    f(i, 0, w - 1) a[i] = (ll)a[i] * invmuli % mod * inv2 % mod;
}
void polycos(poly& a) {
    poly b = a;
    int w = a.size();
    f(i, 0, w - 1) a[i] = (ll)a[i] * muli % mod;
    f(i, 0, w - 1) b[i] = (ll)b[i] * fmuli % mod;
    exp(a);
    exp(b);
    a = a + b;
    f(i, 0, w - 1) a[i] = (ll)a[i] * inv2 % mod;
}
void polyasin(poly& a) {
    poly b = a;
    int w = a.size();
    deri(a);
    b = b * b;
    b.resize(w - 1);
    b[0] = mod + 1 - b[0], mod1(b[0]);
    f(i, 1, w - 2) b[i] = mod - b[i], mod1(b[i]);
    Sqrt(b);
    inv(b);
    a = a * b;
    a.resize(w - 1);
    inte(a);
}
void polyatan(poly& a) {
    poly b = a;
    int w = a.size();
    deri(a);
    b = b * b;
    b.resize(w - 1);
    b[0] = 1 + b[0], mod1(b[0]);
    inv(b);
    a = a * b;
    a.resize(w - 1);
    inte(a);
}
const int gnum = 200;  // gnum*gnum>n
poly G[2][gnum];
poly F_G(poly f, poly g) {  //求f(g(x))(mod(x^n+1)) n为f的最高次
    int n = f.size();
    const int L = ceil(sqrt(n));
    G[0][0].resize(n);
    G[0][0][0] = 1;
    f(i, 1, L) G[0][i] = G[0][i - 1] * g, G[0][i].resize(n);
    G[1][0] = G[0][0];
    G[1][1] = G[0][L];
    f(i, 2, L) G[1][i] = G[1][i - 1] * G[1][1], G[1][i].resize(n);
    poly res(n);
    f(i, 0, L) {
        poly tmp(n);
        f(j, 0, L - 1) if (i * L + j >= n) break;
        else {
            const int v = f[i * L + j];
            f(k, 0, n - 1) tmp[k] += (ll)G[0][j][k] * v % mod, mod1(tmp[k]);
        }
        tmp = tmp * G[1][i];
        f(x, 0, n - 1) res[x] = res[x] + tmp[x], mod1(res[x]);
    }
    return res;
}
poly invF_G(poly g) {  //求f(x) 满足f(g(x))=x  其中g[0]=0,g[1]!=0
    g.erase(g.begin());
    int n = g.size() + 1;
    inv(g);
    const int L = ceil(sqrt(n));
    G[0][0].resize(n);
    G[0][0][0] = 1;
    f(i, 1, L) G[0][i] = G[0][i - 1] * g, G[0][i].resize(n);
    G[1][0] = G[0][0];
    G[1][1] = G[0][L];
    f(i, 2, L) G[1][i] = G[1][i - 1] * G[1][1], G[1][i].resize(n);
    poly res;
    f(i, 0, L) {
        f(j, 0, L - 1) if (i * L + j >= n) break;
        else {
            const int sum = i * L + j;
            uint now = 0;
            f(k, 0, sum - 1) now += (ll)G[0][j][k] * G[1][i][sum - 1 - k] % mod, mod1(now);
            now = (ll)now * power(sum, mod - 2) % mod;
            res.push_back(now);
        }
    }
    return res;
}
};  // namespace Poly
using namespace Poly;

int main() {
    ios::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    f.resize(n + 1);
    f(i, 0, n) cin >> f[i];
    g = f;
    Sqrt(f);
    inv(f);
    inte(f);
    exp(f);
    g[0] = 2;
    cout<<g[7]<<endl;
    g = g - f;
    f(i, 0, g.size()-1 ) cout << g[i] << " ";
    ln(g);
    g[0] = (g[0] + 1) % mod;
    poly_pow(g, k);
    cout<<g.size()<<endl;
    deri(g);
}