#include<bits/stdc++.h>
using namespace std;
const int N=200005;

int a[N],dp[N],n;

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    dp[0]=0; dp[1]=a[1]; dp[2]=a[2];
    if(n<=2){
        printf("%d\n",min(a[1],a[2]));
        return 0;
    }
    for(int i=3;i<=n+1;i++) dp[i]=min(dp[i-2]+a[i],dp[i-3]+max(a[i],a[i-1]));
    cout<<dp[n+1]<<endl;
    return 0;
}