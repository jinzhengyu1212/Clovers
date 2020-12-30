#include<bits/stdc++.h>
using namespace std;
const int N=5005;
int n,MOD;
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}

int c[N],dp[N];
int main(){
    scanf("%d%d",&n,&MOD);
    int mid=n/2+1;
    for(int i=2;i<=mid;i++){
        c[i]-=(mid-i+1);
    }
    for(int i=2;i<=n;i++){
        if(i<=n-n/2) c[i]+=n/2;
        else c[i]+=n-i+1;
        c[i]++;
    }
    dp[0]=1;
    for(int i=2;i<=n;i++){
        for(int j=c[i];j<=n;j++){
            dp[j]=add(dp[j],dp[j-c[i]]);
        }
    }
    int ans=0;
    for(int i=0;i<n;i++){
        ans=add(ans,1ll*(n-i)*dp[i]%MOD);
    }
    cout<<ans<<endl;
    return 0;
}