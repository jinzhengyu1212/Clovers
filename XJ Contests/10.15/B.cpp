#include<bits/stdc++.h>
using namespace std;
const int N=500005;
int n,a[N],q;
char c[N];

namespace solver1{
    int dp[N];
    void main(){
        //for(int i=0;i<n;i++) cout<<a[i]<<" "; cout<<endl;
        dp[1]=1; int mx=1,ans=1;
        for(int i=2;i<=n;i++){
            if(a[i-2]!=a[i-1]) dp[i]=dp[i-1]+1;
            else dp[i]=1;
            if(i==dp[i]) mx=i;
            ans=max(ans,dp[i]);
        }
        if(mx==n&&a[0]!=a[n-1]){
            puts("-1");
            return;
        }
        if(a[0]!=a[n-1]) ans=max(ans,dp[n]+mx);
        printf("%d\n",(ans-1)/2);
    }
}

void solve(){
    scanf("%d%d",&n,&q);
    scanf("%s",c);
    for(int i=0;i<n;i++) a[i]=c[i]-'0';
    if(q<=10){
        while(q--){
            int s,l,k; scanf("%d%d%d",&s,&l,&k);
            for(int i=0;i<l;i++){
                a[(i+s)%n]=k;
            }
            solver1::main();
        }
    }
}

int main(){
    solve();
    return 0;
}