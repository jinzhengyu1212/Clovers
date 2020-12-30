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
const int N=500005;
const int M=1005;
int n,m,A,B;
char a[5005][5005];
void heng(int x,int y){a[x][y]='<'; a[x][y+1]='>';}
void shu(int x,int y){a[x][y]='^'; a[x+1][y]='v';}
void solve(int n,int m){
    if((n==0||m==0)&&(A!=0||B!=0)){
        puts("NO");
        exit(0);
    }
    if(A==0&&B==0) return;
    if(n==1&&B!=0){
        puts("NO");
        exit(0);
    }
    if(m==1&&A!=0){
        puts("NO");
        exit(0);
    }
    if(n%2==0&&m%2==1){
        for(int i=1;i<n;i+=2){
            if(B) shu(i,m),B--;
        }
        solve(n,m-1);
        return;
    }
    else if(m%2==0&&n%2==1){
        for(int i=1;i<m;i+=2){
            if(A) heng(n,i),A--;
        }
        solve(n-1,m);
        return;
    }
    else if(m%2==1&&n%2==1){
        int delA=m/2,delB=n/2;
        if(A<=delA){
            for(int i=1;i<m;i+=2){
                if(A) heng(n,i),A--;
            }
            solve(n-1,m);
            return;
        }
        else if(B<=delB){
            for(int i=1;i<n;i+=2){
                if(B) shu(i,m),B--;
            }
            solve(n,m-1); return;
        }
        else{
            if((A-delA)%2==1&&(B-delB)%2==1){
                if(A<B){
                    shu(n-1,1); heng(n-2,1); A--; B--;
                    for(int i=2;i<=m;i+=2) heng(n,i),A--;
                    for(int i=3;i<=m;i++) shu(n-2,i),B--;
                    solve(n-3,m);
                }
                else{
                    heng(1,m-1); shu(1,m-2); A--; B--;
                    for(int i=2;i<=n;i+=2) shu(i,m),B--;
                    for(int i=3;i<=n;i++) heng(i,m-2),A--;
                    solve(n,m-3);
                }
            }
            else{
                for(int i=1;i<m;i+=2){
                    if(A) heng(n,i),A--;
                }
                solve(n-1,m);
                return;
            }
        }
    }
    else{
        if(A>=m){
            for(int i=1;i<m;i+=2) heng(n,i),A--;
            for(int i=1;i<m;i+=2) heng(n-1,i),A--;
            solve(n-2,m); return;
        }
        else if(B>=n){
            for(int i=1;i<n;i+=2) shu(i,m),B--;
            for(int i=1;i<n;i+=2) shu(i,m-1),B--;
            solve(n,m-2); return;
        }
        else{
            //cout<<"PPP\n";
            if(A%2==0){
                int pos=1;
                for(int i=1;i<m;i+=2,pos+=2){
                    if(!A) break;
                    heng(n,i); heng(n-1,i);
                    A-=2;
                }
                for(int i=pos;i<=m;i++) if(B) shu(n-1,i),B--;
                solve(n-2,m); return;
            }
            else if(B==0){
                int pos=1;
                for(int i=1;i<n;i+=2,pos+=2){
                    if(!B) break;
                    shu(i,m); shu(i,m-1);
                    B-=2;
                }
                for(int i=pos;i<=n;i++) if(A) heng(i,m-1),A--;
                solve(n,m-2); return;
            }
            else{
                int pos=1;
                for(int i=1;i<n;i+=2,pos+=2){
                    if(!B) break;
                    if(B) shu(i,m),B--;
                    if(B) shu(i,m-1),B--;
                }
                for(int i=pos;i<=n;i++) if(A) heng(i,m-1),A--;
                solve(n,m-2); return;
            }
        }
    }
}

int main()
{
    n=read(),m=read(); A=read(); B=read();
    if(n*m<2*(A+B)){
        puts("NO");
        return 0;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) a[i][j]='.';
    solve(n,m);
    puts("YES");
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) printf("%c",a[i][j]);
        puts("");
    }
    return 0;
}