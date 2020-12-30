#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define mk make_pair
const int M=(1<<11);
const int maxn=(1<<20)+3;
const int N=91;
int n,m,d,vis[maxn];
vector<pii> v[N];
int dp1[N][M],dp2[N][M],pre[N][M],cnt[N];
int main(){
    scanf("%d%d%d",&n,&m,&d);
    for(int i=1;i<=m;i++){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        v[x].push_back(mk(y,z)); v[y].push_back(mk(x,z));
    }
    dp1[1][0]=1;
    for(int rnd=1;rnd<=d/2;rnd++){
        for(int i=1;i<=n;i++){
            for(int mask=0;mask<(1<<rnd);mask++) 
                pre[i][mask]=dp1[i][mask], dp1[i][mask]=0;
        }
        for(int i=1;i<=n;i++){
            for(int mask=0;mask<(1<<rnd);mask++){
                if(!pre[i][mask]) continue;
                for(int j=0;j<(int)v[i].size();j++){
                    int to=v[i][j].first,c=v[i][j].second;
                    if(c==1) dp1[to][mask|(1<<(rnd-1))]=1;
                    else dp1[to][mask]=1;
                }
            }
        }
    }   
    for(int i=1;i<=n;i++) dp2[i][0]=1;
    for(int rnd=1;rnd<=(d+1)/2;rnd++){
        for(int i=1;i<=n;i++){
            for(int mask=0;mask<(1<<rnd);mask++) 
                pre[i][mask]=dp2[i][mask], dp2[i][mask]=0;
        }
        for(int i=1;i<=n;i++){
            for(int mask=0;mask<(1<<rnd);mask++){
                if(!pre[i][mask]) continue;
                for(int j=0;j<(int)v[i].size();j++){
                    int to=v[i][j].first,c=v[i][j].second;
                    if(c==1) dp2[to][mask|(1<<(rnd-1))]=1;
                    else dp2[to][mask]=1;
                }
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int mask=0;mask<(1<<((d+1)/2));mask++){
            if(dp2[i][mask]){
                for(int mask2=0;mask2<(1<<(d/2));mask2++){
                    if(dp1[i][mask2]){
                        int tmp=mask*(1<<(d/2))+mask2;
                        if(!vis[tmp]) ans++,vis[tmp]=1;
                    }
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}