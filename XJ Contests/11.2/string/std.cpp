#include<bits/stdc++.h>
using namespace std;
const int inf=(int)5e8;
const int N=210005;
  
int n,len,dp[N],cal[N];
char s[N][25];
int f(int x,int y)
{
    for(int st=0;st<=len;st++)
    {
        int bl=1;
        for(int i=1;i+st<=len;i++)
        {
            if(s[x][st+i]!=s[y][i]) {bl=0; break;}
        }
        if(bl) return st;
    }
}
  
void init()
{
    scanf("%d%d",&n,&len);
    for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
    for(int i=1;i<n;i++) cal[i]=f(i,i+1);
    cal[0]=len;
}
  
void solve()
{
    for(int i=0;i<=n;i++) dp[i]=inf;
    dp[0]=cal[0];
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<=i-1;j++)
        {
            dp[i]=min(dp[j]+f(j,i+1),dp[i]);
            dp[j]=dp[j]+cal[i];
        }
    }
    int ans=inf;
    for(int i=0;i<n;i++) ans=min(ans,dp[i]);
    cout<<ans<<endl;
}
  
int main()
{
    init(); solve();
    return 0;
}