#include <iostream>
#include <cstdio>
using namespace std;
int n;
long long prime[10000010], tot;
long long a[510][510];
bool sf[10000010];
long long gcd(long long x, long long y)
{
    return x == 0 ? y : gcd(y % x, x);
}
long long lcm(long long x, long long y)
{
    // printf("\n%lld %lld\n", x, y);
    if(x == 0 || y == 0) return x + y;
    return x / gcd(x, y) * y;
}
int main()
{
    scanf("%d", &n);
    if(n == 2)
    {
        return printf("4 7\n23 10\n" ), 0;
    }
    sf[0] = sf[1] = 1;
    for (long long i = 2; i <= 10000000; ++ i)
    {
        if(sf[i] == 0)prime[++ tot] = i;
        for (long long j = 1; prime[j] * i <= 10000000 && j <= tot; ++ j)
        {
            sf[i * prime[j]] = 1;
            if(i % prime[j] == 0)break;
        }
    }
    tot = 0;
    for(int i = 2; i <= 2 * n; i += 2)
    {
        long long x = prime[++ tot];
        for(int j = max(1, i - n); j <= min(n, i - 1); ++ j)
        a[j][i - j] = x;
    }
    // for (int i = 1; i <= n; ++ i)
    // {
    //     for (int j = 1; j <= n; ++ j)
    //     {
    //         printf("%lld ", a[i][j]);
    //     }
    //     printf("\n" );
    // }
    for(int i = (n & 1) ? 1 - n : 2 - n; i < n; i += 2)
    {
        long long x = prime[++ tot];
        for(int j = 1; j <= n; ++ j)
            if(i + j >= 1 && i + j <= n)a[j][i + j] *= x;
    }
    // for (int i = 1; i <= n; ++ i)
    // {
    //     for (int j = 1; j <= n; ++ j)
    //     {
    //         printf("%lld ", a[i][j]);
    //     }
    //     printf("\n" );
    // }
    for (int i = 1; i <= n; ++ i)
    {
        for (int j = 1; j <= n; ++ j)
        {
            if(a[i][j] == 0)
            a[i][j] = lcm(lcm(a[i + 1][j], a[i - 1][j]), lcm(a[i][j - 1], a[i][j + 1])) + 1;
            printf("%lld ", a[i][j]);
            // if(a[i][j] > 1000000000000000ll)
            // {printf("qwq\n" );return 0;}
        }
        printf("\n" );
    }
}
