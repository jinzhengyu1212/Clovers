#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long D;
typedef pair<int,int> P;
typedef pair<D,int> QY;
const int maxn=1000003,mod=998244353,base=26,BASE=maxn,p1=1000000007,p2=1000000009;
int Plus(int x,int y,int p=mod){return (x+=y)>=p?x-p:x;}
void Pluseq(int &x,int y){if((x+=y)>=mod)x-=mod;}
int Minus(int x,int y,int p=mod){return Plus(x,p-y,p);}
void Minuseq(int &x,int y){Pluseq(x,mod-y);}
int mul(D x,int y,int p=mod){return x*y%p;}
void muleq(int &x,int y){x=mul(x,y);}
int n,fac[maxn],inv[maxn],buc[maxn];
QY mp[maxn*2];
char s[maxn];
P pw[maxn],PW[maxn],h[maxn],a1[maxn],a2[maxn];
P operator+(P x,int y){return P(Plus(x.fi,y,p1),Plus(x.se,y,p2));}
P operator+(P x,P y){return P(Plus(x.fi,y.fi,p1),Plus(x.se,y.se,p2));}
P operator-(P x,int y){return P(Minus(x.fi,y,p1),Minus(x.se,y,p2));}
P operator-(P x,P y){return P(Minus(x.fi,y.fi,p1),Minus(x.se,y.se,p2));}
P operator*(P x,int y){return P(mul(x.fi,y,p1),mul(x.se,y,p2));}
P operator*(P x,P y){return P(mul(x.fi,y.fi,p1),mul(x.se,y.se,p2));}
P gt(int l,int r){return h[r]-h[l-1]*pw[r-l+1];}
int main(){
    scanf("%s",s+1);
    n=strlen(s+1);
    fac[0]=1,pw[0]=PW[0]=P(1,1);
    for(int i=1;i<=n;i++){
        fac[i]=mul(fac[i-1],i);
        inv[i]=(i==1?1:mul(mod-mod/i,inv[mod%i]));
        pw[i]=pw[i-1]*base,PW[i]=PW[i-1]*BASE,h[i]=h[i-1]*base+(s[i]-'a');
    }
    int ans=0;
    for(int d=1;d<=n;d++){
        int tot=n/d,cntmp=0,cnt=0;
        for(int i=1;i<=tot;i++)a1[i]=gt((i-1)*d+1,i*d),a2[tot-i+1]=gt(n-i*d+1,n-(i-1)*d);
        for(int i=1;i<=tot;i++){
            mp[++cntmp]=QY(a1[i].fi*D(p2)+a1[i].se,i);
            mp[++cntmp]=QY(a2[i].fi*D(p2)+a2[i].se,i+tot);
        }
        sort(mp+1,mp+cntmp+1);
        for(int i=1,j=1;i<=cntmp;i=j){
            cnt++;
            for(;j<=cntmp&&mp[i].fi==mp[j].fi;j++){
                int pos=mp[j].se;
                (pos<=tot?a1[pos]:a2[pos-tot]).fi=cnt;
            }
        }
        P res(0,0);
        int cur=fac[tot];
        for(int i=1;i<=tot;i++)muleq(cur,inv[++buc[a2[i].fi]]),res=res+PW[a2[i].fi];
        for(int i=0;i<=tot;i++){
            if(i){
                muleq(cur,buc[a2[i].fi]--),muleq(cur,inv[++buc[a1[i].fi]]);
                res=res+PW[a1[i].fi]-PW[a2[i].fi];
            }
            mp[i]=QY(res.fi*D(p2)+res.se,cur);
        }
        sort(mp,mp+tot+1);
        for(int i=0,j=0;i<=tot;i=j){
            Pluseq(ans,mp[i].se);
            for(;j<=tot&&mp[i].fi==mp[j].fi;j++);
        }
        for(int i=1;i<=cnt;i++)buc[i]=0;
    }
    printf("%d\n",ans);
    return 0;
}