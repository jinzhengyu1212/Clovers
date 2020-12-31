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
const int N=300005;
int a[N],b[N],top=0;
int n; ll ans[N],tmp[N];
unsigned int s[N];
void init(){
    for(int i=1;i<=n;i++){
        if(i!=1) s[i]=(747796405u*s[i-1]-1403630843u);
        a[i]=(s[i]/1024)%10;
    }
}

void print(){
    for(top=1;top<=n;top++){
        ans[top+1]+=ans[top]/10;
        ans[top]%=10;
    }
    while(!ans[top]&&top) top--;
    while(ans[top+1]){
        top++;
        ans[top+1]+=ans[top]/10;
        ans[top]%=10;
    }
    if(!top) cout<<"0";
    else for(int i=top;i>=1;i--) printf("%lld",ans[i]);
    puts("");
}
int back(int *a,int n){
    int ret;
    for(ret=1;ret<=n;ret++){
        a[ret+1]+=a[ret]/10;
        a[ret]%=10;
    }
    while(!a[ret]&&ret) ret--;
    while(a[ret+1]){
        ret++;
        a[ret+1]+=a[ret]/10;
        a[ret]%=10;
    }
    return ret;
}

int main()
{
    n=read(); s[1]=read();
    init();
    reverse(a+1,a+n+1);
    for(int i=1;i<=n;i++) a[i]*=9;
    for(int i=1;i<=n;i++){
        a[i+1]+=a[i]/10;
        a[i]%=10;
    }
    if(a[n+1]) n++;
    for(int d=2;d<=n;d++){
        int rest=n;
        for(int i=1;i<=n;i++) b[i]=a[i];
        while(rest>d){
            for(int i=1;i<=rest;i++) tmp[i]=b[i];
            for(int i=rest;i>d;i--){
                ans[i-d]+=tmp[i],tmp[i-d]+=tmp[i];
                int to=(i-1)%d+1; b[to]+=b[i];
            }
            for(int i=d+1;i<=rest;i++) b[i]=0; 
            rest=back(b,rest);
        }
        int flag=1;
        for(int i=1;i<=d;i++) if(b[i]!=9) flag=0;
        ans[1]+=flag;
    }
    print();
    return 0;
}