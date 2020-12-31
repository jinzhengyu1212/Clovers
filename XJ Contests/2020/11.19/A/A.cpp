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
#define int long long
bool check(int y){
    return (y%400==0||(y%4==0&&y%100!=0));
}

int y2800=0,Y=0,y4=0;
void init(int year){
    int D=0;
    for(int i=1;i<=2800;i++){
        if(check(year+i)) D=(D+2)%7,Y+=366;
        else D=(D+1)%7,Y+=365;
        if(!D) y2800++;
        if(!D&&check(year+i)) y4++;
    }
}

int ans=0;
void brute(int t,int year){
    int D=0;
    while(t){
        int tmp=(check(year+1) ? 366 : 365);
        if(t<tmp){
            t=0; break;
        }
        t-=tmp;
        if(check(year+1)) D=(D+2)%7;
        else D=(D+1)%7;
        if(!D) ans++;
        year++;
    }
}

int A,B,C,t;
namespace solver1{
    void brute2(int t,int year){
        int D=0;
        while(t){
            int tmp=(check(year+1) ? 366 : 365);
            if(t<tmp){
                t=0; break;
            }
            t-=tmp;
            if(check(year+1)) D=(D+2)%7;
            else D=(D+1)%7;
            if(!D&&check(year+1)) ans++;
            year++;
        }
    }
    void main(){
        int R=t/Y;
        ans+=R*y4;
        A+=2800*R;
        t-=R*Y;
        brute2(t,A);
        cout<<ans<<endl;
    }
}

signed main()
{
    scanf("%lld%lld%lld%lld",&A,&B,&C,&t);
    if(B<=2) A--;
    init(A);
    if(B==2&&C==29){
        solver1::main();
        return 0;
    }
    int R=t/Y;
    t-=R*Y; ans+=y2800*R;
    A+=2800*R;
    brute(t,A);
    cout<<ans<<endl;
    return 0;
}