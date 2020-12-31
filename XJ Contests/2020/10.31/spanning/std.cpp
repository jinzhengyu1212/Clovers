/*
after dusk passed,
there is a starry sky.
*/
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define m_k make_pair
#define mod 1000000007
#define base 277
#define p 700123939
#define int long long
using namespace std;
const int N=51,M=1000,K=1e5+100;
int n,m,a[N],fac[M],inv[M],cnt,dp[K];
int vi[N][N];
vector <vector<int> > f[N];
vector <int> tmp;
unordered_map <int,int> id;
inline void add(int &a,int b){a=(a+b)%mod;}
inline void del(int &a,int b){a=(a-b+mod)%mod;}
inline void mul(int &a,int b){a=(a*b)%mod;}
inline int down(int n,int m){return fac[n]*inv[n-m]%mod;}
inline int m_pow(int a,int b)
{
    int ans=1;
    while (b)
    {
        if (b&1) mul(ans,a);
        b>>=1;
        mul(a,a);
    }
    return ans;
}
inline int read()
{
    int f=1,x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline int inhash(vector<int> &tmp)
{
    int ans=0;
    for (int i=0;i<(int)tmp.size();i++) ans=(ans*base+tmp[i])%p;
    return ans;
}
inline void print(vector<int> &tmp)
{
    for (int i=0;i<(int)tmp.size();i++) printf("%lld ",tmp[i]);
    printf("\n");
}
void dfs(int x,int sum)
{
    if (!sum)
    {
        f[x].push_back(tmp);
        id[inhash(tmp)]=++cnt;
        if (x==n) dp[cnt]=1;
        return;
    }
    int last=((x==0)?1:tmp.back());
    for (int i=last;i<=sum;i++) tmp.push_back(i),dfs(x+1,sum-i),tmp.pop_back();
}
signed main()
{
    n=read();m=n*(n-1)/2;
    for (int i=1;i<n;i++) a[i]=read();
    a[n]=m+1;sort(a+1,a+n+1);reverse(a+1,a+1+n);
    fac[0]=1;
    for (int i=1;i<=m;i++) fac[i]=(fac[i-1]*i)%mod;
    inv[m]=m_pow(fac[m],mod-2);
    for (int i=m-1;i>=0;i--) inv[i]=(inv[i+1]*(i+1))%mod;
    dfs(0,n);
    for (int i=n;i>=2;i--)
    {
        for (int j=0;j<(int)f[i].size();j++)
        {
            vector <int> now=f[i][j];
            print(now); 
            int x=id[inhash(now)],sz=(int)now.size()-1,tot=0;
            cout<<dp[x]<<endl;
            for (int k=0;k<=sz;k++) tot+=now[k]*(now[k]-1)/2-now[k]+1;
            tot-=a[i+1]-(n-i);
            if (!dp[x]||tot<a[i]-a[i+1]-1) continue;
            mul(dp[x],down(tot,a[i]-a[i+1]-1));
            for (int r=0;r<=sz;r++) for (int c=0;c<r;c++) vi[now[r]][now[c]]=vi[now[r]][now[c]]=0;
            for (int r=0;r<=sz;r++)
            {
                for (int c=0;c<r;c++)
                {
                    tmp.clear();
                    bool bl=1;
                    for (int q=0;q<=sz;q++)
                    {
                        if (r==q||q==c) continue;
                        if (now[r]+now[c]<=now[q]&&bl) tmp.push_back(now[r]+now[c]),bl=0;
                        tmp.push_back(now[q]);
                    }
                    if (bl) tmp.push_back(now[r]+now[c]);
                    int nxt=id[inhash(tmp)];
                    vi[now[r]][now[c]]=vi[now[c]][now[r]]=nxt;
                    add(dp[nxt],dp[x]*(now[r]*now[c])%mod);
                }
            }
        }
    }
    cout<<dp[id[inhash(f[1][0])]]<<endl;
    printf("%lld\n",dp[id[inhash(f[1][0])]]*fac[m-a[2]]%mod);
}