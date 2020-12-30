#include<bits/stdc++.h>
using namespace std;
const int MOD=998244353;
const int N=272000;
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
int mul(int x,int y){return 1ll*x*y%MOD;}
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
    int init(int n){
        int len=1;
        while(len<n) len<<=1;
        rev[0]=0; rev[len-1]=len-1;
        for(int i=1;i<len-1;i++) rev[i]=(rev[i>>1]>>1)+(i&1 ? len>>1 : 0);
        for(int i=1;i<=len;i<<=1){
            G[i]=qpow(3,(MOD-1)/i);
            IG[i]=qpow(G[i],MOD-2);
        }
        return len;
    }
    void ntt(int *a,int len,int flag){
        for(int i=0;i<len;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
        for(int h=1;h<len;h<<=1){
            int wn=(flag==1 ? G[h<<1] : IG[h<<1]);
            for(int i=0;i<len;i+=(h<<1)){
                int W=1,tmp1,tmp2;
                for(int j=i;j<i+h;j++){
                    tmp1=a[j], tmp2=mul(a[j+h],W);
                    a[j]=add(tmp1,tmp2);
                    a[j+h]=sub(tmp1,tmp2);
                    W=mul(W,wn);
                }
            }
        }
        if(flag==-1){
            int invlen=qpow(len,MOD-2);
            for(int i=0;i<len;i++) a[i]=mul(a[i],invlen);
        }
    }
    void multi(int *a,int *b,int len)
    {
        ntt(a,len,1); ntt(b,len,1);
        for(int i=0;i<len;i++) a[i]=mul(a[i],b[i]);
        ntt(a,len,-1);
    }
    int A[N<<1],B[N<<1];
    void Inverse(int *a,int *b,int n){
        if(n==1){
            b[0]=qpow(a[0],MOD-2);
            return;
        }
        int mid=(n+1)/2;
        Inverse(a,b,mid);
        int len=init(n+n);
        for(int i=n;i<len;i++) A[i]=0,B[i]=0;
        for(int i=0;i<n;i++) A[i]=b[i],B[i]=a[i];
        ntt(A,len,1); ntt(B,len,1);
        for(int i=0;i<len;i++){
            A[i]=mul(A[i],sub(2,mul(A[i],B[i])));
        }
        ntt(A,len,-1);
        for(int i=0;i<n;i++) b[i]=A[i];
    }
}

int a[N<<1],b[N<<1],n;
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    Poly::Inverse(a,b,n);
    for(int i=0;i<n;i++) printf("%d ",b[i]);
    puts("");
    return 0;
}