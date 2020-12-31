/*
the vast starry sky,
bright for those who chase the light.
*/
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const int inf=(int)1e9;
const ll INF=(ll)5e18;void checkmin(int &x,int y){if(x>y) x=y;}
void checkmax(int &x,int y){if(x<y) x=y;}
void checkmin(ll &x,ll y){if(x>y) x=y;}
void checkmax(ll &x,ll y){if(x<y) x=y;}
#define out(x) cerr<<#x<<'='<<x<<' '
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=1000001;
int k,m;
namespace solver1{
    bool check(int x){
        while(x){
            if(x%10>=k) return 0;
            x/=10;
        }
        return 1;
    }
    void main(){
        for(int i=1;i<=1000000;i++){
            if(check(i)&&i%m==0){
                printf("%d\n",i);
                return;
            }
        }
    }
}
typedef vector<short> V;
V vis[N];
queue<int> q;

void bfs(){
    for(int i=1;i<k;i++){
        V tmp; tmp.clear(); tmp.push_back(i);
        vis[i]=tmp;
        q.push(i);
    }
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(int i=0;i<k;i++){
            int to=(u*10%m+i)%m;
            if(to==0){
                for(auto &t : vis[u]) printf("%d",t);
                printf("%d\n",i);
                return;
            }
            if(!vis[to].empty()) continue;
            V tmp=vis[u]; tmp.push_back(i);
            vis[to]=tmp; q.push(to);
        }
    }
}

int main()
{
    k=read(); m=read();
    if(m<=1000){
        solver1::main();
        return 0;
    }
    bfs();
    return 0;
}