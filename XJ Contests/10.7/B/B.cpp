#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define mk make_pair
const int N=2005;
int n,m,k;
char mp[N][N];
pii Q[N];
int up[N][N],down[N][N],ans=0,dp[N][N];
deque<pii> U,D;

void update(int j)
{
    up[1][j]=(mp[1][j]=='X' ? 0 : 1);
    for(int i=2;i<=n;i++)
        up[i][j]=(mp[i][j]=='X' ? 0 : up[i-1][j]+1);
    down[n][j]=(mp[n][j]=='X' ? 0 : 1);
    for(int i=n-1;i>=1;i--)
        down[i][j]=(mp[i][j]=='X' ? 0 : down[i+1][j]+1);
}
void init()
{
    for(int i=1;i<=k;i++)
        mp[Q[i].first][Q[i].second]='X';
    for(int j=1;j<=m;j++) update(j);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if(mp[i][j]=='X') continue;
            dp[i][j]=min(dp[i-1][j-1],min(dp[i][j-1],dp[i-1][j]))+1;
            ans=max(ans,dp[i][j]);
        }
}

bool check(int len,int x,int y)
{
    U.clear(); D.clear();
    U.push_back(mk(up[x][1],1)); D.push_back(mk(down[x][1],1));
    for(int i=2;i<=m;i++)
    {
        while(!U.empty()&&U.front().second<i-len+1) U.pop_front();
        while(!D.empty()&&D.front().second<i-len+1) D.pop_front();
        while(!U.empty()&&U.back().first>=up[x][i]) U.pop_back();
        while(!D.empty()&&D.back().first>=down[x][i]) D.pop_back();
        U.push_back(mk(up[x][i],i)); D.push_back(mk(down[x][i],i));
        int minn=U.front().first+D.front().first-1;
        if(i>=len&&minn>=len) return 1; 
    }
    return 0;
}

int ANS[N];
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++) scanf("%s",mp[i]+1);
    for(int i=1;i<=k;i++) scanf("%d %d",&Q[i].first,&Q[i].second);
    init();
    for(int i=k;i>=1;i--)
    {
        ANS[i]=ans;
        mp[Q[i].first][Q[i].second]='.';
        update(Q[i].second);
        while(check(ans+1,Q[i].first,Q[i].second)) ans++;
    }
    for(int i=1;i<=k;i++) printf("%d\n",ANS[i]);
    return 0;
}