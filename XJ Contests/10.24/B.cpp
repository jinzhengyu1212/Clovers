#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define mk make_pair
const int N=200005;
const int inf=(int)1e9;
int n,p,a[N],b[N],val[N];
vector<pii> t[N<<1];

namespace BIT{
    int a[N<<1];
    int lowbit(int x){return x&(-x);}
    void update(int x,int add){
        for(int i=x;i<=n+n;i+=lowbit(i)) a[i]+=add;
    }
    int query(int x){
        int ret=0;
        for(int i=x;i;i-=lowbit(i)) ret+=a[i];
        return ret;
    }
}

int minn=0;
int main(){
    scanf("%d%d",&n,&p);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a[i],&b[i]);
        minn=max(minn,b[i]);
        if(a[i]>b[i]) swap(a[i],b[i]);
        val[i*2-1]=a[i],val[i*2]=b[i];
    }
    sort(val+1,val+n+n+1);
    int m=unique(val+1,val+n+n+1)-val-1;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(val+1,val+m+1,a[i])-val;
        b[i]=lower_bound(val+1,val+m+1,b[i])-val;
        t[a[i]].push_back(mk(i,1)); t[b[i]].push_back(mk(i,-1));
    }
    int ans=0;
    for(int i=1;i<=m;i++){
        for(int j=0;j<(int)t[i].size();j++){
            pii u=t[i][j];
            if(u.second==1) BIT::update(i,1);
            else{
                BIT::update(a[u.first],-1);
                BIT::update(i,1);
            }
        }
        int down=ceil(1.0*val[i]*(1.0*p/100.0));
        int pos=lower_bound(val+1,val+m+1,down)-val;
        if(minn<=val[i]) ans=max(ans,BIT::query(i)-BIT::query(pos-1));
    }
    cout<<ans<<endl;
    return 0;
}