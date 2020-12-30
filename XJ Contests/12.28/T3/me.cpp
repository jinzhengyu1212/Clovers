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
const ll INF=(ll)5e17;
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
const int N=1000005;
int n,m,tot=0;
int id(int x,int y){return (x-1)*m+y;}
struct node{
    int val,b,c,d,e,x,y;
}a[N];
namespace solver1{
    ll dis[105][105];
    void main(){
        for(int i=1;i<=tot;i++){
            for(int j=1;j<=tot;j++){
                if(i==j){dis[i][i]=a[i].val; continue;}
                dis[i][j]=INF;
                if(a[j].x>=a[i].b&&a[j].x<=a[i].d&&a[j].y>=a[i].c&&a[j].y<=a[i].e)
                    dis[i][j]=1+a[j].val;    
            }
        }
        for(int k=1;k<=tot;k++){
            for(int i=1;i<=tot;i++){
                for(int j=1;j<=tot;j++) checkmin(dis[i][j],dis[i][k]+dis[k][j]);
            }
        }
        ll ans=INF;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=m;j++){
                if(id(1,i)==id(n,j)) checkmin(ans,dis[id(1,i)][id(n,j)]);
                else checkmin(ans,a[id(1,i)].val+dis[id(1,i)][id(n,j)]);
            }
        }
        cout<<ans<<endl;
    }
}

int main()
{
    n=read(); m=read(); tot=n*m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int tmp=id(i,j);
            a[tmp].x=i; a[tmp].y=j;
            a[tmp].val=read(); a[tmp].b=read(); a[tmp].c=read();
            a[tmp].d=read(); a[tmp].e=read();
        }
    }
    if(n*m<=100){
        solver1::main();
        return 0;
    }
    solver1::main();
    return 0;
}