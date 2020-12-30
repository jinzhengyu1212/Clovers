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
int _abs(int x){return x<0 ? -x : x;}
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
const int N=2005;
bitset<2015> dp[N],ans,pre[N],suf[N],S;
int a[N],tot=0,cur;
int n,L,c[N],v[N],C;
void print(bitset<2015> bit,int m){
    for(int i=1;i<=m;i++) if(bit.test(i)) cout<<"1"; else cout<<"0";
    cout<<endl;
}
void solve(int n,int c){
    for(int i=1;i<=n;i+=c){
        pre[i]=dp[a[i]];
        for(int j=i+1;j<=min(n,i+c-1);j++) pre[j]=pre[j-1]|dp[a[j]];
    }
    for(int i=c;i<=n;i+=c){
        suf[i]=dp[a[i]];
        for(int j=i-1;j>=i-c+1;j--) suf[j]=suf[j+1]|dp[a[j]];
    }
    for(int i=2;i<=n;i++){
        int L=max(1,i-c),R=i-1;
        if(i<=c) dp[a[i]]|=(pre[R]<<1);
        else dp[a[i]]|=((suf[L]|pre[R])<<1);
    }
}

int main()
{
    n=read(); L=read();
    for(int i=1;i<=n;i++) c[i]=read(),v[i]=read();
    dp[0].set(0);
    for(int i=1;i<=n;i++){
        for(int j=0;j<v[i];j++){
            tot=0; 
            for(int k=j;k<=L;k+=v[i]) a[++tot]=k;
            solve(tot,c[i]);
        }
        // for(int j=1;j<=L;j++){
        //     out(i); out(j);
        //     print(dp[j],i);
        // }
    }
    C=read();
    while(C--) S.set(read());
    for(int i=1;i<=L;i++) if((dp[i]&S).any()) printf("%d ",i);
    cout<<endl;
    return 0;
}