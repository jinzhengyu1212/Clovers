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
int n,m,a[11][N],match[N],len;
char s[N];
int stk[N],top=0;
bool checkq(){for(int i=1;i<=len;i++) if(s[i]=='?') return 0; return 1;}

void init(){
    n=read(); m=read();
    for(int i=0;i<m;i++){
        for(int j=1;j<=n;j++) a[i][j]=read();
    }
    scanf("%s",s+1); len=strlen(s+1);
    for(int i=1;i<=len;i++){
        if(s[i]=='(') stk[++top]=i;
        else if(s[i]==')'){
            match[stk[top]]=i;
            match[i]=stk[top]; top--;
        }
    }
}

namespace solver1{
    typedef vector<int> vec;
    vec v[11];
    int num[N],mx[5005][5005];
    vec Merge(vec A,vec B,char c){
        vec ret; ret.resize(n);
        for(int i=0;i<n;i++)
            ret[i]=(c=='>' ? max(A[i],B[i]) : min(A[i],B[i]));
        return ret;
    }
    vec calc(int l,int r){
        if(l==r) return v[s[l]-'0'];
        if(match[l]==r) return calc(l+1,r-1);
        return Merge(calc(l,mx[l][r]-1),calc(mx[l][r]+1,r),s[mx[l][r]]);
    }
    void main(){
        for(int i=0;i<m;i++){
            for(int j=1;j<=n;j++) v[i].push_back(a[i][j]);
        }
        for(int i=1;i<=len;i++){
            if(s[i]=='('){
                for(int j=i;j<=match[i];j++) num[j]++;
            }
        }
        num[0]=inf;
        for(int i=1;i<=len;i++){
            mx[i][i]=(s[i]=='>'||s[i]=='<' ? i : 0);
            for(int j=i+1;j<=len;j++){
                int tmp=(s[j]=='>'||s[j]=='<' ? num[j] : inf);
                if(num[mx[i][j-1]]>=tmp) mx[i][j]=j;
                else mx[i][j]=mx[i][j-1];
            }
        }
        vec ret=calc(1,len);
        int ans=0; 
        for(int i=0;i<sz(ret);i++) Add(ans,ret[i]);
        cout<<ans<<endl;
    }
}

namespace solver2{
    typedef vector<int> vec;
    typedef vector<vec> matrix;
    vec v[11]; matrix tt[11];
    int num[N],mx[5005][5005];
    matrix Merge(matrix A,matrix B,char c){
        matrix ret; ret.resize(m);
        for(int i=0;i<m;i++) ret[i].resize(m);
        for(int i=0;i<m;i++) for(int j=0;j<m;j++) ret[i][j]=0;
        if(c=='>'||c=='?'){
            for(int xa=0;xa<m;xa++){
                for(int ya=0;ya<m;ya++){
                    if(!A[xa][ya]) continue;
                    for(int xb=0;xb<m;xb++){
                        int x=max(xa,xb);
                        for(int yb=0;yb<m;yb++){
                            int y=max(ya,yb);
                            Add(ret[x][y],mul(A[xa][ya],B[xb][yb]));
                        }
                    }
                }
            }
        }
        if(c=='<'||c=='?'){
            for(int xa=0;xa<m;xa++){
                for(int ya=0;ya<m;ya++){
                    if(!A[xa][ya]) continue;
                    for(int xb=0;xb<m;xb++){
                        int x=min(xa,xb);
                        for(int yb=0;yb<m;yb++){
                            int y=min(ya,yb);
                            Add(ret[x][y],mul(A[xa][ya],B[xb][yb]));
                        }
                    }
                }
            }
        }
        return ret;
    }
    matrix calc(int l,int r){
        if(l==r) return tt[s[l]-'0'];
        if(match[l]==r) return calc(l+1,r-1);
        return Merge(calc(l,mx[l][r]-1),calc(mx[l][r]+1,r),s[mx[l][r]]);
    }
    int A[20],B[20];
    void init(){
        for(int i=0;i<m;i++){
            for(int j=1;j<=n;j++) v[i].push_back(a[i][j]);
            if(n==1) v[i].push_back(0);
        } n=2;
        for(int i=0;i<m;i++) A[i]=v[i][0],B[i]=v[i][1];
        sort(A,A+m); sort(B,B+m);
        for(int i=0;i<m;i++){
            v[i][0]=lower_bound(A,A+m,v[i][0])-A;
            v[i][1]=lower_bound(B,B+m,v[i][1])-B;
        }
        for(int i=1;i<=len;i++){
            if(s[i]=='('){
                for(int j=i;j<=match[i];j++) num[j]++;
            }
        }
        num[0]=inf;
        for(int i=1;i<=len;i++){
            mx[i][i]=(s[i]=='>'||s[i]=='<'||s[i]=='?' ? i : 0);
            for(int j=i+1;j<=len;j++){
                int tmp=(s[j]=='>'||s[j]=='<'||s[j]=='?' ? num[j] : inf);
                if(num[mx[i][j-1]]>=tmp) mx[i][j]=j;
                else mx[i][j]=mx[i][j-1];
            }
        }
    }
    void main(){
        init();
        for(int i=0;i<m;i++){
            tt[i].resize(m);
            for(int j=0;j<m;j++) tt[i][j].resize(m);
            tt[i][v[i][0]][v[i][1]]=1;
        }
        matrix ret=calc(1,len);
        int ans=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<m;j++){
                Add(ans,mul(add(A[i],B[j]),ret[i][j]));
            }
        }
        cout<<ans<<endl;
    }
}

void solve(){
    if(checkq()){
        solver1::main();
        return;
    }
    if(n<=2){
        solver2::main();
        return;
    }
}

int main()
{
    //freopen("expr.in","r",stdin);
    //freopen("expr.out","w",stdout);
    init(); solve();
    fclose(stdin); fclose(stdout);
    return 0;
}