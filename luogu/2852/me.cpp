/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
const int N=1000005;

char s[N];
int n;
int sa[N],rk[N],id[N],oldrk[N],cnt[N],P[N];
bool cmp(int x,int y,int w){
    return oldrk[x]==oldrk[y]&&oldrk[x+w]==oldrk[y+w];
}
void build(){
    int m=130,p;
    scanf("%s",s+1);
    n=strlen(s+1);
    for(register int i=1;i<=n;++i) ++cnt[rk[i]=s[i]];
    for(register int i=1;i<=m;++i) cnt[i]+=cnt[i-1];
    for(register int i=n;i>=1;--i) sa[cnt[rk[i]]--]=i;
    for(register int w=1;w<n;w<<=1,m=p){
        memset(cnt,0,sizeof(int)*(m+1));
        p=0;
        for(register int i=n;i>n-w;--i) id[++p]=i;
        for(register int i=1;i<=n;++i){
            if(sa[i]>w) id[++p]=sa[i]-w;
        }
        for(register int i=1;i<=n;++i) ++cnt[P[i]=rk[id[i]]];
        for(register int i=1;i<=m;++i) cnt[i]+=cnt[i-1];
        for(register int i=n;i>=1;--i) sa[cnt[P[i]]--]=id[i];
        memcpy(oldrk,rk,sizeof(int)*(n+1));
        p=0;
        for(register int i=1;i<=n;++i){
            rk[sa[i]]=cmp(sa[i],sa[i-1],w) ? p : ++p;
        }
        if(p==n) break;
    } 
    for(register int i=1;i<=n;++i) printf("%d ",sa[i]);
}

int main()
{
    build();
    return 0;
}