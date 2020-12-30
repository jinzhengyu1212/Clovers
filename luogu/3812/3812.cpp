#include<bits/stdc++.h>
using namespace std;
const int N=1001;
#define int long long
int p[N],n;

int qpow(int x,int y){
    int ret=1;
    while(y){
        if(y&1) ret=ret*x;
        x=x*x;
        y>>=1; 
    }
    return ret;
}

int bl=0;
void insert(int x){
    for(int i=55;i>=0;i--){
        if(x>>i&1){
            if(!p[i]){p[i]=x; break;}
            x^=p[i];
        }
    }
    if(x==0) bl=1;
}

void init(){
    for(int i=55;i>=0;i--){
        if(p[i]) for(int j=i-1;j>=0;j--){
            if(p[i]>>j&1) p[i]^=p[j];
        }
    }
}

signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        int x; scanf("%lld",&x);
        insert(x);
    }
    init();
    int m; scanf("%lld",&m);
    while(m--){
        int x; scanf("%lld",&x);
        int cnt=0,ans=0;
        for(int i=0;i<=55;i++) if(p[i]) cnt++;
        if(!bl) x++;
        for(int i=55;i>=0;i--){
            if(!p[i]) continue;
            cnt--;
            if(qpow(2,cnt)<x) x-=qpow(2,cnt),ans^=p[i];
        }
        if(x>1) puts("-1");
        else printf("%lld\n",ans);
    }
    return 0;
}