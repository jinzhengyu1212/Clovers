#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ul;
#define mk make_pair
#define ri register int
const int MOD1=20201029;
const int MOD2=998244353;
const int ulMOD=(1<<21)-1;
const int N=1000005;
const int B=31;
int add(int x,int y){x+=y; return x>=MOD2 ? x-MOD2 : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD2 : x;}
#define mul(x,y) (ll)(x)*(y)%MOD2
inline pii operator + (pii x,pii y){
    return mk((x.first+y.first)%MOD1,(x.second+y.second)%MOD2);
}
inline pii operator - (pii x,pii y){
    return mk((x.first-y.first+MOD1)%MOD1,(x.second-y.second+MOD2)%MOD2);
}
inline pii operator * (pii x,pii y){
    return mk((ll)x.first*y.first%MOD1,(ll)x.second*y.second%MOD2);
}
pii base[N];
struct Hash{
    int first[ulMOD],nxt[N],id[N],e=0;
    ul point[N];
    inline void insert(ul val,int ID){
        e++; int pos=val%ulMOD;
        point[e]=val; id[e]=ID;
        nxt[e]=first[pos];
        first[pos]=e;
    }
    inline int find(ul val){
        int pos=val%ulMOD;
        for(ri i=first[pos];~i;i=nxt[i]){
            ul to=point[i];
            if(to==val) return id[i];
        }
        return 0;
    }
    void clear(int pos){first[pos]=-1;}
}H3,H2;

ul change(pii A){
    ul ret=((ul)(A.first)<<31)|A.second;
    ret^=(ret<<15);
    ret^=(ret>>10);
    ret^=(ret<<7);
    return ret^1145141919810ll;
}
 
int n;
char s[N];
pii a[N];
pii calc(int l,int r){
    return (a[r]-a[l-1])*base[n-r];
}
 
void init(){
    scanf("%s",s+1); n=strlen(s+1);
    a[0]=mk(0,0);
    base[0]=mk(1,1);
    for(ri i=1;i<=n;++i) base[i]=base[i-1]*mk(B,B);
    for(ri i=1;i<=n;++i){
        a[i]=a[i-1]+(base[i-1]*mk(s[i]-'a'+1,s[i]-'a'+1));
    }
}
 
int head[N],vis[N],tot=0,ans=0,fac[N],Inv[N];
int used2[N],used3[N],top2=0,top3=0;
pii Calc[N];
void solve(){
    for(ri i=0;i<ulMOD;++i) H3.clear(i);
    for(ri i=0;i<ulMOD;++i) H2.clear(i);
    fac[0]=1;
    for(ri i=1;i<=n;++i) fac[i]=mul(fac[i-1],i);
    Inv[1]=1;
    for(ri i=2;i<=n;++i) Inv[i]=mul(Inv[MOD2%i],MOD2-MOD2/i);
    for(ri d=1;d<=n;d++){
        int rest=n%d;
        ri i;
        top2=0,top3=0; pii val;
        int cnt=0; H2.e=0; H3.e=0; tot=0; int ID=0;
        for(i=1;i+d-1<=n;i+=d){
            val=calc(i,i+d-1);
            Calc[i]=val;
            ul tmp=change(val);
            if(!H3.find(tmp)) 
                H3.insert(tmp,++ID),
                used3[++top3]=(tmp%ulMOD);
            if(n%d==0) continue;
            val=calc(i+rest,i+rest+d-1);
            Calc[i+rest]=val;
            tmp=change(val);
            if(!H3.find(tmp)) 
                H3.insert(tmp,++ID),
                used3[++top3]=(tmp%ulMOD);
        }

        int num=fac[n/d],pos;
        ul Mask=0;
        for(i=1;i+d-1<=n;i+=d){
            head[++cnt]=i;
            val=Calc[i];
            ul tmp=change(val);
            pos=H3.find(tmp);
            num=mul(num,Inv[vis[pos]+1]),vis[pos]++;
            Mask=Mask+change(base[pos]);
        }
        ans=add(ans,num);
        H2.insert(Mask,1);
        used2[++top2]=(Mask%ulMOD);
        if(n%d){
            for(i=cnt;i>=1;i--){
                val=Calc[head[i]];
                ul tmp=change(val);
                pos=H3.find(tmp);
                vis[pos]--,num=mul(num,vis[pos]+1);
                Mask=Mask-change(base[pos]);

                head[i]+=rest;
                val=Calc[head[i]];
                tmp=change(val);
                pos=H3.find(tmp);
                num=mul(num,Inv[vis[pos]+1]),vis[pos]++;
                Mask=Mask+change(base[pos]);
                if(!H2.find(Mask)){
                    ans=add(ans,num);
                    H2.insert(Mask,1);
                    used2[++top2]=(Mask%ulMOD);
                }
            }
        }
        for(i=1;i<=top2;++i) H2.clear(used2[i]);
        for(i=1;i<=top3;++i) H3.clear(used3[i]);
        for(i=1;i<=ID;i++) vis[i]=0;
    }
    printf("%d\n",ans);
}
 
int main(){
    init(); solve();
    return 0;
}