#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iostream>
using namespace std;
int tot=1,las=1;
struct NODE
{
    int ch[26];
    int len,fa;
    NODE(){memset(ch,0,sizeof(ch));len=fa=0;}
}dian[2000010];
struct Edge
{
    int t,nexty;
}edge[2000010];
int head[2000010],cnt=0;
void jia(int a,int b)
{
    cnt++;
    edge[cnt].t=b;
    edge[cnt].nexty=head[a];
    head[a]=cnt;
}
long long zhi[2000010];
inline void add(int c)
{
    register int p=las,np=las=++tot;zhi[tot]=1;
    dian[np].len=dian[p].len+1;
    for(;p&&!dian[p].ch[c];p=dian[p].fa)dian[p].ch[c]=np;
    if(!p)dian[np].fa=1;
    else
    {
        register int q=dian[p].ch[c];
        if(dian[q].len==dian[p].len+1)dian[np].fa=q;
        else
        {
            register int nq=++tot;
            dian[nq]=dian[q];dian[nq].len=dian[p].len+1;
            dian[q].fa=dian[np].fa=nq;
            for(;p&&dian[p].ch[c]==q;p=dian[p].fa)dian[p].ch[c]=nq;
        }
    }
}
char s[2000010];
int cd;
long long ans=0;
void dfs(int node)
{
    for(register int i=head[node];i;i=edge[i].nexty)
    {
        dfs(edge[i].t);
        zhi[node]+=zhi[edge[i].t];
    }
    if(zhi[node]!=1)ans=max(ans,zhi[node]*dian[node].len);
}
int main()
{
    scanf("%s",s);cd=strlen(s);
    for(register int i=0;i<cd;i++)add(s[i]-'a');
    for(register int i=2;i<=tot;i++){
        jia(dian[i].fa,i);
        cout<<dian[i].fa<<" "<<i<<endl;
    }
    dfs(1);
    printf("%lld\n",ans);
    return 0;
}