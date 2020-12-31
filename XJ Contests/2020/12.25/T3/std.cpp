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
const int N=1000001;
set<int> st;
int n,m,maxC=0,L[N],R[N];
void dfs(int mask){
    for(auto &to : st){
        int to1=mask|to,to2=mask&to;
        if(!st.count(to1)){
            st.insert(to1);
            dfs(to1);
        }
        if(!st.count(to2)){
            st.insert(to2);
            dfs(to2);
        }
    }
}
 
namespace solver1{
    void main(){
        int full=(1<<n)-1;
        st.insert(0); st.insert(full);
        for(int i=1;i<=m;i++){
            int tmp=0;
            for(int j=L[i];j<=R[i];j++){
                tmp|=(1<<(j-1));
            }
            if(!st.count(tmp)) st.insert(tmp),dfs(tmp);
        }
        printf("%d\n",sz(st));
    }
}
 
int main()
{
    n=read(); m=read();
    for(int i=1;i<=m;i++){
        L[i]=read(); R[i]=read();
        checkmax(maxC,R[i]-L[i]+1);
    }
    if(n<=20){
        solver1::main();
        return 0;
    }
    if(maxC==1){
        int ans=qpow(2,m);
        if(m!=n) Add(ans,1);
        printf("%d\n",ans);
        return 0;
    }
    return 0;
}