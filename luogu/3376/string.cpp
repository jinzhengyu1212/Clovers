#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
typedef pair<int,int> pii;
#define mk make_pair
const int N=1100001;
const int MOD1=19260817;
const int MOD2=998244353;
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
pii operator + (pii A,pii B){
    return mk((A.first+B.first)%MOD1,(A.second+B.second)%MOD2);
}
pii operator - (pii A,pii B){
    return mk((A.first-B.first+MOD1)%MOD1,(A.second-B.second+MOD2)%MOD2);
}
pii operator * (pii A,int x){
    return mk(1ll*A.first*x%MOD1,1ll*A.second*x%MOD2);
}
pii operator * (pii A,pii B){
    return mk(1ll*A.first*B.first%MOD1,1ll*A.second*B.second%MOD2);
}
const int B=43;
char s[N];
pii sum[N],Base[N];
int n;

pii calc(int l,int r){
    return Base[n-r]*(sum[r]-sum[l-1]);
}

void init(){
    scanf("%s",s+1); n=strlen(s+1);
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+(Base[i]*(s[i]-'a'));
    }
}

namespace BIT{
    int a[40];
    int lowbit(int x){return x&(-x);}
    void update(int x,int add){
        for(int i=x;i<=27;i+=lowbit(i)) a[i]+=add;
    }
    int query(int x){
        int ret=0;
        for(int i=x;i;i-=lowbit(i)) ret+=a[i];
        return ret;
    }
}

int F[N],t[27];
ll ans[N];
void solve(){
    memset(t,0,sizeof(t));
    F[n+1]=0;
    for(int i=n;i>=1;i--){
        if(t[s[i]-'a']&1) F[i]=F[i+1]-1;
        else F[i]=F[i+1]+1;
        t[s[i]-'a']++;
    }
    memset(t,0,sizeof(t));
    memset(ans,0,sizeof(ans));
    int now=0;
    for(int i=1;i<=30;i++) BIT::a[i]=0;
    for(int i=1;i<=n;i++){
        if(i>=3){
            pii tmp=calc(1,i-1);
            for(int j=i;j<=n;j+=(i-1)){
                int from=j-(i-1),to=j-1;
                if(tmp!=calc(from,to)) break;
                ans[j]+=BIT::query(F[j]+1);
            }
        }
        if(i>=2){
            if(t[s[i-1]-'a']&1) now--;
            else now++;
            t[s[i-1]-'a']++;
            BIT::update(now+1,1);
        }
    }
    ll ret=0;
    for(int i=1;i<=n;i++){
        ret+=ans[i];
    }
    printf("%lld\n",ret);
}

signed main(){
    //freopen("string.in","r",stdin);
    //freopen("string.out","w",stdout);
    int T=read();
    sum[0]=mk(0,0);
    Base[0]=mk(1,1);
    for(int i=1;i<=1100000;i++) Base[i]=Base[i-1]*B;
    while(T--){
        init(); solve();
    }
    fclose(stdin); fclose(stdout);
    return 0;
}