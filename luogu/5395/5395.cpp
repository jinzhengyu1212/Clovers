#include<bits/stdc++.h>
using namespace std;
const int MOD=167772161;
const int N=270005;
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int mul(int x,int y){return 1ll*x*y%MOD;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
int qpow(int x,int y){
    int ret=1;
    while(y){
        if(y&1) ret=mul(ret,x);
        x=mul(x,x);
        y>>=1;
    }
    return ret;
}
namespace Poly{
    int rev[N<<1],G[N<<1],IG[N<<1];
    int a[N<<1],b[N<<1];
    void getrev(int len){
        rev[0]=0; rev[len-1]=len-1;
        for(int i=1;i<len-1;i++) rev[i]=(rev[i>>1]>>1)+(len>>1)*(i&1);
    }
    void getinv(int len){
        for(int i=1;i<=len;i<<=1){
            G[i]=qpow(3,(MOD-1)/i);
            IG[i]=qpow(G[i],MOD-2);
        }
    }
    void ntt(int *a,int len,int flag){
        for(int i=0;i<len;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
        for(int h=1;h<len;h<<=1){
            int wn=(flag==1 ? G[h<<1] : IG[h<<1]);
            int tmp1,tmp2,w;
            for(int i=0;i<len;i+=(h<<1)){
                w=1;
                for(int j=i;j<i+h;j++){
                    tmp1=a[j]; tmp2=mul(a[j+h],w);
                    a[j]=add(tmp1,tmp2);
                    a[j+h]=sub(tmp1,tmp2);
                    w=mul(w,wn);
                }
            }
        }
        if(flag==-1){
            int invlen=qpow(len,MOD-2);
            for(int i=0;i<len;i++) a[i]=mul(a[i],invlen);
        }
    }
    int getlen(int n){
        int ret=1;
        while(ret<n) ret<<=1;
        return ret;
    }
    void multi(int *a,int *b,int n,int m){
        int len=getlen(n+m+1);
        getrev(len); getinv(len);
        ntt(a,len,1); ntt(b,len,1); 
        for(int i=0;i<len;i++) a[i]=mul(a[i],b[i]);
        ntt(a,len,-1);
    }
}

int f[N<<1],g[N<<1],fac[N<<1];
int main(){
    int n; scanf("%d",&n);
    if(n==0){
        puts("0");
        return 0;
    }
    fac[0]=1; for(int i=1;i<=n;i++) fac[i]=mul(fac[i-1],i);
    for(int i=0;i<=n;i++) 
        f[i]=mul(qpow(MOD-1,i),qpow(fac[i],MOD-2)),
        g[i]=mul(qpow(i,n),qpow(fac[i],MOD-2));
    Poly::multi(f,g,n,n);
    for(int i=0;i<=n;i++) printf("%d ",f[i]); puts("");
    return 0;
}