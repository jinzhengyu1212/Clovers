#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000005;
const int MOD=(int)1e9+7;
int n;
char s[N];

int nxt[N],pre[N],num[N],sum[N];
void solve(){
    for(int i=0;i<=n;i++) nxt[i]=0,pre[i]=0,num[i]=0,sum[i]=0;
    sum[0]=-1;
    nxt[1]=0; pre[1]=0; num[1]=0; sum[1]=0;
    for(int i=1;i<n;i++){//i->i+1 or (if i is odd->i+1,i+2)
        int j=nxt[i];
        while(j&&s[i+1]!=s[j+1]) j=nxt[j];
        if(s[i+1]==s[j+1]) j++; 
        nxt[i+1]=j;
        sum[i+1]=sum[nxt[i+1]]+1;
        if(i%2==1){
            j=pre[i];
            while(j&&s[i+1]!=s[j+1]) j=nxt[j];
            if(s[i+1]==s[j+1]) j++;
            pre[i+1]=j;
            num[i]=sum[pre[i+1]]+1;
        }
        else{
            j=pre[i];
            if(j==i/2) j=nxt[j];
            while(j&&s[i+1]!=s[j+1]) j=nxt[j];
            if(s[i+1]==s[j+1]) j++;
            pre[i+1]=j;
            num[i]=sum[pre[i+1]]+1;
        }
    }
    int ans=1;
    for(int i=1;i<=n;i++) ans=1ll*ans*(num[i]+1)%MOD;
    printf("%d\n",ans);
}

int main(){
    int T; scanf("%d",&T);
    while(T--){
        scanf("%s",s+1); n=strlen(s+1);
        solve();
    }
    return 0;
}