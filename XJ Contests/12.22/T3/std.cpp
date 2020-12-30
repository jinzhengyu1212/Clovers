/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const int inf=(int)1e9+5;
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
const int N=100005;
struct node{
    int opt,ti;
}a[N];
int n,val[N],m,visl[N],visr[N],sum[N],posl[N],posr[N],fin,Len;
int mx[N],mi[N];

int main()
{
    n=read(); a[0].ti=-inf; Len=read(); fin=read();
    for(int i=1;i<=n;i++){
        char c[2]; scanf("%s",c);
        if(c[0]=='+') a[i].opt=1;
        else a[i].opt=-1;
        a[i].ti=read(); val[i]=a[i].ti-a[i-1].ti-1;
    }
    sort(val+1,val+n+1); m=unique(val+1,val+n+1)-val-1;
    reverse(val+1,val+m+1);
    vector<int> v;
    for(int rnd=1;rnd<=m;rnd++){
        v.clear(); int T=val[rnd];
        if(rnd==m){
            printf("%d %d\n",T,fin);
            return 0;
        }
        visl[0]=-1; visr[0]=-1;
        for(int i=1;i<=n;i++){
            visl[i]=-1; visr[i]=-1;
            if(a[i].ti-a[i-1].ti<=T) v.push_back(a[i].opt);
        }
        int sz=(int)v.size();
        for(int i=Len;i>=0;i--){
            int pos=i;
            for(int j=0;j<sz;j++){
                pos+=v[j];
                checkmax(pos,0);
                checkmin(pos,Len);
            }
            if(pos==fin){
                if(rnd==1) puts("infinity");
                else printf("%d %d\n",T,i);
                return 0;
            }
        }
    }
    return 0;
}