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
const int N=505;
const int M=N*N;
int n,t[N],ans[M];
pii a[N];

int main()
{
    n=read();
    for(int i=1;i<=n;i++) t[i]=n;
    for(int i=1;i<=n;i++) a[i].first=read(),a[i].second=i;
    sort(a+1,a+n+1);
    int now=1;
    for(int i=1;i<=n;i++){
        int pos=a[i].second;
        t[pos]-=pos;
        ans[a[i].first]=pos;
        for(int j=1;j<pos;j++){
            while(ans[now]) now++;
            ans[now++]=pos;
        }
        if(now>a[i].first){puts("No"); return 0;}
    }
    for(int i=1;i<=n;i++){
        int pos=a[i].second;
        while(t[pos]--){
            while(ans[now]) now++;
            if(now<a[i].first){puts("No"); return 0;}
            ans[now++]=pos;
        }
    }
    puts("Yes");
    for(int i=1;i<=n*n;i++) printf("%d ",ans[i]);
    cout<<endl;
    return 0;
}