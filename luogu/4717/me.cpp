/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const int inf=(int)1e9;
const ll INF=(ll)5e18;
const int MOD=998244353;
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
#define mul(x,y) (ll)(x)*(y)%MOD
void Add(int &x,int y){x+=y; if(x>=MOD) x-=MOD;}
void Sub(int &x,int y){x-=y; if(x<0) x+=MOD;}
void Mul(int &x,int y){x=mul(x,y);}
int qpow(int x,int y){int ret=1; while(y){if(y&1) ret=mul(ret,x); x=mul(x,x); y>>=1;} return ret;}
void checkmin(int &x,int y){if(x>y) x=y;}
void checkmax(int &x,int y){if(x<y) x=y;}
void checkmin(ll &x,ll y){if(x>y) x=y;}
void checkmax(ll &x,ll y){if(x<y) x=y;}
#define out(x) cerr<<#x<<'='<<x<<' '
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=200001;
const int inv2=qpow(2,MOD-2);

int A[N<<2],B[N<<2];
void FWT_and(int len,int *a,int flag){
    for(int h=1;h<len;h<<=1){
        for(int i=0;i<len;i+=(h<<1)){
            for(int j=i;j<i+h;j++) 
                (flag==1 ? Add(a[j],a[j+h]) : Sub(a[j],a[j+h]));
        }
    }
}

void FWT_or(int len,int *a,int flag){
    for(int h=1;h<len;h<<=1){
        for(int i=0;i<len;i+=(h<<1)){
            for(int j=i;j<i+h;j++)
                (flag==1 ? Add(a[j+h],a[j]) : Sub(a[j+h],a[j]));
        }
    }
}

void FWT_xor(int len,int *a,int flag){
    for(int h=1;h<len;h<<=1){
        for(int i=0;i<len;i+=(h<<1)){
            for(int j=i;j<i+h;j++){
                int tmp1=add(a[j],a[j+h]),tmp2=sub(a[j],a[j+h]);
                a[j]=tmp1; a[j+h]=tmp2;
            }
        }
    }
    if(flag==-1){
        int invlen=qpow(len,MOD-2);
        for(int i=0;i<len;i++) Mul(a[i],invlen);
    }
}

int a[N<<2],b[N<<2],n;
int main()
{
    n=read();
    for(int i=0;i<(1<<n);i++) a[i]=read();
    for(int i=0;i<(1<<n);i++) b[i]=read();
    for(int i=0;i<(1<<n);i++) A[i]=a[i];
    for(int i=0;i<(1<<n);i++) B[i]=b[i];
    FWT_or(1<<n,A,1); FWT_or(1<<n,B,1);
    for(int i=0;i<(1<<n);i++) Mul(A[i],B[i]);
    FWT_or(1<<n,A,-1);
    for(int i=0;i<(1<<n);i++) printf("%d ",A[i]); puts("");
    
    for(int i=0;i<(1<<n);i++) A[i]=a[i];
    for(int i=0;i<(1<<n);i++) B[i]=b[i];
    FWT_and(1<<n,A,1); FWT_and(1<<n,B,1);
    for(int i=0;i<(1<<n);i++) Mul(A[i],B[i]);
    FWT_and(1<<n,A,-1);
    for(int i=0;i<(1<<n);i++) printf("%d ",A[i]); puts("");

    for(int i=0;i<(1<<n);i++) A[i]=a[i];
    for(int i=0;i<(1<<n);i++) B[i]=b[i];
    FWT_xor(1<<n,A,1); FWT_xor(1<<n,B,1);
    for(int i=0;i<(1<<n);i++) Mul(A[i],B[i]);
    FWT_xor(1<<n,A,-1);
    for(int i=0;i<(1<<n);i++) printf("%d ",A[i]); puts("");
    return 0;
}