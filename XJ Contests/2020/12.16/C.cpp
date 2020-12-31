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
const int N=(1<<20);
int n,a[N],f1[N],f2[N],Base[N];
void FWT1(){
    for(int h=1;h<N;h<<=1){
        for(int i=0;i<N;i+=(h<<1)){
            for(int j=i;j<i+h;j++) f1[j]|=f1[j+h];
        }
    }
}

void FWT2(){
    for(int h=1;h<N;h<<=1){
        for(int i=0;i<N;i+=(h<<1)){
            for(int j=i;j<i+h;j++) f2[j]+=f2[j+h];
        }
    }
}

int bl[21],mp[21],mp1[N];
int main()
{
    n=read(); Base[0]=1;
    for(int i=1;i<=n;i++) Base[i]=mul(Base[i-1],2);
    for(int i=1;i<=n;i++){
        a[i]=read();
        for(int j=0;j<20;j++){
            if(!(a[i]>>j&1)) bl[j]|=1;
            else bl[j]|=2;
        }
        f2[a[i]]++; f1[(N-1)^a[i]]=1;
    }
    FWT1(); FWT2();
    for(int i=0;i<20;i++){
        for(int j=0;j<20;j++){
            if(bl[i]!=3||bl[j]!=3) continue;
            int tmp=((1<<i)|(1<<j));
            if(f1[tmp]) mp[i]|=(1<<j);
        }
    }
    for(int S=0;S<N;S++){
        for(int i=0;i<20;i++) if(S>>i&1) mp1[S]|=mp[i];
    }
    int full=N-1,ans=0;
    for(int mask=0;mask<N;mask++){
        int ju=1,flag=1;
        for(int i=0;i<20;i++) if((mask>>i&1)&&bl[i]!=3) ju=0;
        if(!ju) continue; 
        int cnt=0,tmp=mask;
        for(int i=0;i<20;i++){
            if(mask>>i&1) flag=MOD-flag;
            if(tmp>>i&1){
                int rest=tmp&mp[i];
                while(rest){
                    tmp^=rest;
                    rest=mp1[rest]&tmp;
                }
                cnt++;
            }
        }
        Add(ans,mul(flag,sub(Base[cnt+f2[mask]],2)));
    }
    cout<<ans<<endl;
    return 0;
}