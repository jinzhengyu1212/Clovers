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
const int N=200005;
int n,a[N],b[N],sum1[30][N],S0=0,S1=0;
pii id[30][N];
int ans[30];

int main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=28;i++){
        for(int j=1;j<=n;j++) id[i][j]=mk(a[j]%(1<<i),j);
        sort(id[i]+1,id[i]+n+1);
        for(int j=n;j>=1;j--){
            sum1[i][j]=sum1[i][j+1];
            int u=id[i][j].second;
            if(a[u]>>i&1) sum1[i][j]++;
        }
    }
    for(int i=1;i<=n;i++) if(a[i]&1) S1++; else S0++;
    for(int i=1;i<=n;i++){
        int x=read();
        if(x&1) ans[0]^=(S0%2);
        else ans[0]^=(S1%2);
        for(int j=1;j<=28;j++){
            //outln(ans[j]);
            int now=x%(1<<j);
            int rest=(1<<j)-now;
            int pos=lower_bound(id[j]+1,id[j]+n+1,mk(rest,0))-id[j];
            int L=pos-1,R=n-pos+1;
            int r1=sum1[j][pos],r0=R-r1;
            int l1=sum1[j][1]-sum1[j][pos],l0=L-l1;
            if(x>>j&1){
                ans[j]^=(r1%2);
                ans[j]^=(l0%2);
            }
            else{
                ans[j]^=(r0%2);
                ans[j]^=(l1%2);
            }
            //out(pos); out(j); out(l0); out(l1); out(r0); out(r1); outln(ans[j]);
        }
    }
    int ANS=0;
    for(int i=0;i<=28;i++) ANS+=(ans[i]<<i);
    cout<<ANS<<endl;
    return 0;
}