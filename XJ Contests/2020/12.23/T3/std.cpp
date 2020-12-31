#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<bitset>
typedef long long ll;
typedef unsigned un;
typedef unsigned long long ull;
typedef std::pair<int,int> pii;
ll read(){ll x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9')x=x*10+(c-'0'),c=getchar();return f*x;}
ll max(ll a,ll b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}
void umax(int& a,int t){if(a<t)a=t;}
bool umin(ll& a,ll t){if(a>t)return a=t,1;return 0;}
bool umin(int& a,int t){if(a>t)return a=t,1;return 0;}
/**********/
const int MAXN = 2003;
std::bitset<MAXN>f[MAXN], b;
std::bitset<MAXN>pre[MAXN],suf[MAXN];
int a[MAXN],ss=0;
inline void solve(int n,int k)
{
    for(int i=1;i<=min(n,k-1);++i)suf[i]=suf[i-1]|f[a[i]];
    for(int i=k;i<=n;i+=k)
    {
        pre[i]=suf[i]=f[a[i]];
        for(int j=1;j<k;++j)pre[i-j]=pre[i-j+1]|f[a[i-j]],++ss;
        for(int j=1;j<k&&i+j<=n;++j)suf[i+j]=(suf[i+j-1]|f[a[i+j]]),++ss;
    }
    for(int i=1;i<n;++i)
    {
        if(i<k)f[a[i+1]]|=suf[i]<<1;
        else
        {
            f[a[i+1]]|=(pre[i-k+1]|suf[i])<<1;
        }
        ++ss;
    }
}
int main()
{
    int n=read(),m=read();
    f[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        int c=read(),v=read(),sum=0,pre=ss;
        double st=clock();
        for(int j=0;j<v;++j)
        {
            int l=0;
            for(int k=j;k<=m;k+=v)a[++l]=k;
            sum+=l;
            solve(l,c);
        }
        //printf("i=%d,ss=%d(+%d),sum=%d,ti=%.6lf\n",i,ss,ss-pre,sum,double(clock()-st)/CLOCKS_PER_SEC);
    }
    int p=read();
    while(p--)b[read()]=1;
    for(int i=0;i<=m;++i)
        if((f[i]&b).any())printf("%d ",i);
    puts("");
    return 0;
}