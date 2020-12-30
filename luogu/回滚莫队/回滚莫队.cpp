#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
const int N=400005;
int n,a[N],m;
int b[N],nn;
void checkmax(int &x,int y){if(x<y) x=y;}
void checkmin(int &x,int y){if(x>y) x=y;}
struct QU{
    int l,r,id,pos;
    bool operator < (const QU &rhs) const{
        if(pos==rhs.pos) return r<rhs.r;
        else return pos<rhs.pos;
    }
}Q[N];

vector<int> v[N];
int id[N],cnt,LI[N],RI[N];
void init()
{
    memset(LI,0x3f,sizeof(LI));
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),b[i]=a[i];
    sort(b+1,b+n+1); nn=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+n+1,a[i])-b;
    scanf("%d",&m);
    for(int i=1;i<=m;i++) scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].id=i;
    int TMP=sqrt(n); cnt=TMP+1;
    for(int i=1;i<=n;i++) 
    {
        id[i]=i/TMP+1;
        checkmin(LI[id[i]],i);
        checkmax(RI[id[i]],i);
    }
    for(int i=1;i<=m;i++) Q[i].pos=id[Q[i].l];
    sort(Q+1,Q+m+1);
    for(int i=1;i<=cnt;i++) v[i].clear();
    for(int i=1;i<=m;i++) v[Q[i].pos].push_back(i);
}

int pre[N],nxt[N],NXT=0,PRE=0,t[N];
vector<int> tmp;
void add(int x,int val,int flag)//0:left 1:right
{
    t[val]++;
    if(t[val]==1) {
        if(flag) pre[val]=x;  
        else tmp.push_back(val);
        nxt[val]=x; return;
    }
    if(!flag) checkmax(PRE,nxt[val]-x), tmp.push_back(val);
    else checkmax(NXT,x-pre[val]), nxt[val]=x;
}

int ans[N];
void solve()
{
    for(int i=1;i<=cnt;i++)
    {
        int L,R=RI[i]; NXT=0;
        for(int j=0;j<(int)v[i].size();j++)
        {
            tmp.clear();
            int now=v[i][j]; PRE=0;
            L=min(RI[i],Q[now].r)+1;
            while(R<Q[now].r) R++, add(R,a[R],1);
            while(L>Q[now].l) L--, add(L,a[L],0);
            ans[Q[now].id]=max(NXT,PRE);
            for(int k=0;k<(int)tmp.size();k++) 
                if(nxt[tmp[k]]<=RI[i]) nxt[tmp[k]]=0,t[tmp[k]]--;
        }
        for(int j=LI[i];j<=n;j++) nxt[a[j]]=0,pre[a[j]]=0,t[a[j]]=0;
    }
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
}

int main()
{
    init(); solve();
    return 0;
}