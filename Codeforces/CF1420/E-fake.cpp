/*
the cast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
    return x;
}

const int N=10005;
int n,a[N],b[N],cnt1=0,cnt0=0;
int dp[N][N/100],A[N];
int _abs(int x){return x<0 ? -x : x;}

int main(){
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    int now=0;
    for(int i=1;i<=n;i++){
        if(a[i]==1) b[++cnt1]=now,now=0;
        else cnt0++,now++;
    }
    b[cnt1+1]=now; int m=cnt1+1;
    int ans=cnt0*(cnt0-1)/2;
    for(int i=1;i<=m;i++) ans-=b[i]*(b[i]-1)/2;
    A[0]=ans;
    for(int i=1;i<=m;i++) dp[0][i]=b[i];
    for(int rnd=1;rnd<=n*(n-1)/2;rnd++){
        int F=-1,T=-1,mx=A[rnd-1];
        for(int from=1;from<=m;from++){
            for(int to=1;to<=m;to++){
                int dis=_abs(from-to);
                if(rnd<dis||dp[rnd-dis][from]<=dp[rnd-dis][to]) continue;
                if(mx<dp[rnd-dis][from]-dp[rnd-dis][to]-1+A[rnd-dis]){
                    mx=dp[rnd-dis][from]-dp[rnd-dis][to]-1+A[rnd-dis];
                    F=from,T=to;
                }
            }
        }
        if(mx==0){
            for(int i=1;i<=n;i++) dp[rnd][i]=dp[rnd-1][i];
            A[rnd]=A[rnd-1];
            continue; 
        }
        int dis=_abs(F-T);
        for(int i=1;i<=n;i++) dp[rnd][i]=dp[rnd-dis][i];
        A[rnd]=mx;
        dp[rnd][F]--; dp[rnd][T]++;
    }
    for(int i=0;i<=n*(n-1)/2;i++){
        printf("%d ",A[i]);
    }
    puts("");
    return 0;
}