#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=3e5+500,mod=998244353;
int limn,p[N],pw[N],prime[N],f[N],fac[N],g[N],rev[N],w[N],ifac[N],cnt,n,m;
int qpower(int a,int b){int ans=1;for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)ans=1ll*ans*a%mod;return ans;}
unsigned long long tmp[N];
void NTT(int a[])
{
    for(int i=0;i<limn;i++)tmp[rev[i]]=a[i];
    for(int i=1;i<limn;i<<=1)
        for(int j=0;j<limn;j+=i<<1)
            for(int k=0;k<i;k++)
            {
                int x=tmp[i+j+k]*w[i+k]%mod;
                tmp[i+j+k]=tmp[j+k]+mod-x,tmp[j+k]+=x;
            }
    for(int i=0;i<limn;i++)a[i]=tmp[i]%mod;
}
void prework(int n)
{
    limn=1;while(limn<=n)limn<<=1;
    for(int i=1;i<limn;i++)rev[i]=(rev[i>>1]>>1)|((i&1)?(limn>>1):0);
    for(int i=1;i<limn;i<<=1)
    {
        int omg=qpower(3,(mod-1)/(i<<1));
        w[i]=1;
        for(int j=1;j<i;j++)w[i+j]=1ll*w[i+j-1]*omg%mod;
    }
}
void IDFT(int a[])
{
    reverse(a+1,a+limn);NTT(a);int ivl=mod-(mod-1)/limn;
    for(int i=0;i<limn;i++)a[i]=1ll*a[i]*ivl%mod;
}
void prework()
{
    pw[1]=1;
    for(int i=2;i<=m+1;i++)
    {
        if(!p[i])prime[++cnt]=i,pw[i]=qpower(i,n);
        for(int j=1;j<=cnt&&i*prime[j]<=m+1;j++)
        {
            int x=i*prime[j];p[x]=1;pw[x]=1ll*pw[i]*pw[prime[j]]%mod;
            if(i%prime[j]==0)break;
        }
    }
    fac[0]=1;for(int i=1;i<=m;i++)fac[i]=1ll*fac[i-1]*i%mod;
    ifac[m]=qpower(fac[m],mod-2);
    for(int i=m-1;i>=0;i--)ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
    for(int i=0;i<=m;i++)f[i]=1ll*qpower(i,m)*ifac[i]%mod;
    for(int i=0;i<=m;i++)g[i]=((i&1)?mod-ifac[i]:ifac[i]);
    prework(2*m);
    NTT(f),NTT(g);
    for(int i=0;i<=limn;i++)f[i]=1ll*f[i]*g[i]%mod;
    reverse(f+1,f+limn);NTT(f);int ivl=mod-(mod-1)/limn;
    for(int i=0;i<=m;i++)f[i]=1ll*f[i]*ivl%mod*fac[i]%mod;
}
int main()
{
    scanf("%d%d",&n,&m);
    prework();
    int ans=0;
    for(int i=0;i<=m;i++)ans=(ans+(((i+m)&1)?-1ll:1ll)*f[i]*pw[i+1])%mod;
    cout<<(ans+mod)%mod<<endl;
}