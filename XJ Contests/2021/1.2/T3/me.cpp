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
const int MOD=1e9+7;
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
const int N=300005;
char S[N],T[N];
int n,m,fac[N],ifac[N],Sa=0,Sb=0,Ta=0,Tb=0,Sq=0,Tq=0,Base[N];
int C(int n,int m){return mul(fac[n],mul(ifac[n-m],ifac[m]));}
vector<int> v1,v2;
bool check(){for(int i=1;i<=n;i++) if(S[i]!=T[i]) return 0; return 1;}

int main()
{
    n=300000;
    fac[0]=1; for(int i=1;i<=n;i++) fac[i]=mul(fac[i-1],i);
    ifac[n]=qpow(fac[n],MOD-2);
    for(int i=n-1;i>=0;i--) ifac[i]=mul(ifac[i+1],i+1);
    Base[0]=1; for(int i=1;i<=n+1;i++) Base[i]=mul(Base[i-1],2);
    scanf("%s",S+1); scanf("%s",T+1);
    n=max(strlen(S+1),strlen(T+1)); scanf("%d",&m);
    for(int i=1;i<=strlen(S+1);i++){
        Sa+=(S[i]=='A'); Sb+=(S[i]=='B'); Sq+=(S[i]=='?');
        if(S[i]=='?') v1.push_back(i);
    }
    for(int i=1;i<=strlen(T+1);i++){
        Ta+=(T[i]=='A'); Tb+=(T[i]=='B'); Tq+=(T[i]=='?');
        if(T[i]=='?') v2.push_back(i);
    }
    int ans=0;
    int full1=(1<<sz(v1))-1,full2=(1<<(sz(v2)))-1;
    for(int S1=0;S1<=full1;S1++){
        for(int S2=0;S2<=full2;S2++){
            int A=0,B=0;
            for(int i=0;i<sz(v1);i++){
                if(S1>>i&1) S[v1[i]]='A';
                else S[v1[i]]='B';
            }
            for(int i=0;i<sz(v2);i++){
                if(S2>>i&1) T[v2[i]]='A';
                else T[v2[i]]='B';
            }
            for(int i=1;i<=strlen(S+1);i++){
                if(S[i]=='A') A++;
                else B--;
            }
            for(int i=1;i<=strlen(T+1);i++){
                if(T[i]=='A') A--;
                else B++;
            }
            if(1ll*A*B<0||(A*B==0&&A+B!=0)) continue;
            if(A<0) A=-A,B=-B;
            if(A+B==0){
                if(check()){
                    Add(ans,mul(sub(Base[m+1],2),sub(Base[m+1],2)));
                    continue;
                }
                else A=1,B=1;
            }
            int g=__gcd(A,B); A/=g,B/=g;
            int tmp=m/max(A,B);
            Add(ans,sub(Base[tmp+1],2));
        }
    }
    cout<<ans<<endl;
    return 0;
}