#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2005;
const int inf=(int)5e18;
 
struct node{
    int c,w,v;
    node(){}
    node(int c,int w,int v):c(c),w(w),v(v){}
    bool operator <(const node &rhs) const{
        return w>rhs.w;
    }
}A[N],B[N];
int n,m,dp[N*50],pre[N];
 
signed main(){
    memset(dp,0xcf,sizeof(dp));
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lld%lld%lld",&A[i].c,&A[i].w,&A[i].v);
    for(int i=1;i<=m;i++) scanf("%lld%lld%lld",&B[i].c,&B[i].w,&B[i].v);
    sort(A+1,A+n+1);
    sort(B+1,B+m+1);
    dp[0]=0;
    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+A[i].c;
    for(int i=1,j=1;i<=m;i++){
        while(A[j].w>=B[i].w&&j<=n){
            for(int k=pre[j];k>=A[j].c;k--){
                dp[k]=max(dp[k],dp[k-A[j].c]-A[j].v);
            }
            j++;
        }
        for(int k=0;k<=pre[j-1];k++){
            dp[k]=max(dp[k],dp[k+B[i].c]+B[i].v);
        }
         
    } 
    int ans=0;
    for(int i=0;i<N*50;i++) ans=max(ans,dp[i]);
    cout<<ans<<endl;
    return 0;
}