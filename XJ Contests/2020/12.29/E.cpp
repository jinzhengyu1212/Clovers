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
int T,a[4][4];

int main()
{
    T=read();
    while(T--){
        for(int i=1;i<=3;i++){
            for(int j=1;j<=3;j++){
                a[i][j]=read();
            }
        }
        int ans=0;
        for(int i1=1;i1<=3;i1++){
            for(int j1=1;j1<=3;j1++){
                int bl=1;
                for(int i2=1;i2<=3;i2++){
                    if(!bl) break;
                    for(int j2=1;j2<=3;j2++){
                        if(i1==i2||j1==j2||bl==0) continue;
                        int i3=6-i1-i2,j3=6-j1-j2,sum=0;
                        for(int i=1;i<=3;i++){
                            for(int j=1;j<=3;j++){
                                if((i==i1&&j==j1)||(i==i2&&j==j2)) continue;
                                if(i==i3&&j==j3) sum^=a[i][j];
                                else sum^=(a[i][j]-1);
                            }
                        }
                        if(!sum) bl=0;
                    }
                }
                ans+=bl;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}