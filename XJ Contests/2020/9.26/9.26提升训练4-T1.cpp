#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD=998244353;
const int N=137000;
int ADD(int x,int y){return x+y>=MOD ? x+y-MOD : x+y;}
int MUL(int x,int y){return 1ll*x*y%MOD;}

int qpow(int x,int y)
{
    int ret=1;
    while(y)
    {
        if(y&1) ret=MUL(ret,x);
        x=MUL(x,x); y>>=1;
    }
    return ret;
}

namespace Poly{
    int a[N],b[N],rev[N];
    int wn[N],wn_1[N];
    void getinv()
    {
        for(int h=1;h<N;h<<=1) wn[h]=qpow(3,(MOD-1)/h),wn_1[h]=qpow(wn[h],MOD-2); 
    }
    int getlen(int n)
    {
        int len=1;
        while(len<n) len<<=1;
        return len;
    }
    void getrev(int len)
    {
        rev[0]=0; rev[len-1]=len-1;
        for(int i=1;i<len-1;i++) rev[i]=(rev[i>>1]>>1)+(i&1 ? len>>1 : 0);
    }
    void ntt(int *a,int len,int flag)
	{
		for(int i=0;i<len;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
		for(int h=1;h<len;h<<=1)
		{
			int Wn=(flag==-1 ? wn_1[h<<1] : wn[h<<1]);
			int tmp1,tmp2;
			for(int i=0;i<len;i+=h*2)
			{
				int w=1;
				for(int j=i;j<i+h;j++)
				{
					tmp1=a[j],tmp2=1LL*a[j+h]*w%MOD;
					a[j]=(tmp1+tmp2)%MOD;
					a[j+h]=(tmp1-tmp2+MOD)%MOD;
					w=1LL*w*Wn%MOD;
				}
			}
		}
		if(flag==-1)
		{
			int inv_len=qpow(len,MOD-2);
			for(int i=0;i<len;i++) a[i]=MUL(a[i],inv_len);
		}
	}
}

int n,A[N],B[N];
int dp[N];
int f(int x,int id){
    return ADD(MUL(MUL(x,x),A[id]),MUL(x,B[id])+1)%MOD;
}

int m=10000,F[N];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&A[i]);
    for(int i=1;i<=n;i++) scanf("%d",&B[i]);
    dp[0]=1;
    int len=Poly::getlen(m+m);
    Poly::getrev(len); Poly::getinv();
    Poly::ntt(dp,len,1);
    for(int i=1;i<=n;i++){
        for(int j=0;j<len;j++) F[j]=0;
        for(int j=0;j<=m;j++) F[j]=f(j,i);
        Poly::ntt(F,len,1); 
        for(int j=0;j<len;j++) dp[j]=MUL(dp[j],F[j]);
    }
    Poly::ntt(dp,len,-1);
    int Q; scanf("%d",&Q);
    while(Q--){
        int X; scanf("%d",&X);
        printf("%d\n",dp[X]);
    }
    return 0;
}