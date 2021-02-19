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
const int N=50005;
const int M=1050;
int n,m,a[11][N],len;
char s[N];

void init(){
    n=read(); m=read();
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++) a[i][j]=read();
    }
    scanf("%s",s+1); len=strlen(s+1);
}
int opt[N]; pii num[N];//num0; num1
int top1=0,top2=0,ans[M],pos1[N];
bool checkopt(char c){return c=='<'||c=='>'||c=='?';}
pii Merge(pii A,pii B,char c){
    pii ret=mk(0,0);
    int tmp0=mul(A.first,B.first),tmp1=mul(A.second,B.second);
    int tmp2=add(mul(A.first,B.second),mul(A.second,B.first));
    if(c=='<'||c=='?'){
        Add(ret.first,add(tmp0,tmp2));
        Add(ret.second,tmp1);
    }
    if(c=='>'||c=='?'){
        Add(ret.first,tmp0);
        Add(ret.second,add(tmp1,tmp2));
    }
    return ret;
}

void ready(){
    for(int S=0;S<(1<<m);S++){
        top1=0; top2=0;
        for(int i=1;i<=len;i++){
            int flag=0;
            if(s[i]>='0'&&s[i]<='9'){
                int now=s[i]-'0';
                num[++top1]=(S>>now&1 ? mk(0,1) : mk(1,0));
                pos1[top1]=i;
            }
            else{
                if(s[i]==')') top2--;
                else opt[++top2]=i;
            }
            if(top1>=2&&top2&&checkopt(s[opt[top2]])&&pos1[top1]>opt[top2]){
                num[top1-1]=Merge(num[top1-1],num[top1],s[opt[top2]]);
                top1--; top2--;
            }
        }
        ans[S]=num[top1].second;
    }
}

pii t[11];
void solve(){
    ready();
    int ret=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) t[j]=mk(a[j][i],j);
        sort(t,t+m);
        for(int j=m-1;j>=1;j--) t[j].first-=t[j-1].first;
        int S=(1<<m)-1;
        for(int j=0;j<=m;j++){
            Add(ret,mul(ans[S],t[j].first));
            S^=(1<<t[j].second);
        }
    }
    cout<<ret<<endl;
}

int main()
{
    //freopen("expr.in","r",stdin);
    //freopen("expr.out","w",stdout);
    init(); solve();
    fclose(stdin); fclose(stdout);
    return 0;
}