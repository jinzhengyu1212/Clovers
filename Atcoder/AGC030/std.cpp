/*
Problem : 
Algorithm : 
Status : 
*/
#include<bits/stdc++.h>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#define DEBUG cerr << "Passing Line " << __LINE__<< " in Function [" << __FUNCTION__ << "].\n";
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
template<class T> inline bool checkMax(T &a,const T &b) {return a < b ? a = b,1 : 0;}
template<typename T, typename...Args> inline void checkMax(T &a,const Args...arg) {checkMax(a,max(arg...));}
template<class T> inline bool checkMin(T &a,const T &b) {return a > b ? a = b,1 : 0;}
template<typename T, typename...Args> inline void checkMin(T &a,const Args...arg) {checkMin(a,min(arg...));}

const int INF = 0x3f3f3f3f;
const ll llINF = 1e18;
const int MAXN = 305;
const int MAXM = 605;
const int MOD = 1e9 + 7;

void addmod(int &x,int y) {x += y; if(x >= MOD) x -= MOD;}
void submod(int &x,int y) {x -= y; if(x < 0) x += MOD;}
int add(int x,int y) {addmod(x,y); return x;}
int sub(int x,int y) {submod(x,y); return x;}

int n,m,ans,tot;
int a[MAXM],b[MAXM],f[MAXM][MAXN][MAXN],vis[MAXM],flag[MAXM];

int main(){
    // freopen("data.in","r",stdin);
    // freopen("data.out","w",stdout);
    scanf("%d",&n);
    for(int i = 1,x,y;i <= n;i++){
        x = (i << 1) - 1; y = (i << 1);
        scanf("%d%d",&a[x],&a[y]);
        if(a[x] > 0 && a[y] > 0){
            vis[a[x]] = vis[a[y]] = 1;
            continue;
        }
        if(a[x] == -1 && a[y] == -1) tot += 1;
        else flag[(a[x] == -1) ? a[y] : a[x]] = 1;
    }
    for(int i = 1;i <= (n << 1);i++){
        if(!vis[i])
            b[++m] = i;
    }
    f[m + 1][0][0] = 1;
    for(int i = m;i >= 1;i--){
        for(int j = 0;j <= n;j++){
            for(int k = 0;k <= n;k++){
                if(!flag[b[i]]){
                    addmod(f[i][j + 1][k],f[i + 1][j][k]);
                    if(j) addmod(f[i][j - 1][k],f[i + 1][j][k]);
                    if(k) addmod(f[i][j][k - 1],1ll * f[i + 1][j][k] * k % MOD);
                }else{
                    addmod(f[i][j][k + 1],f[i + 1][j][k]);
                    if(j) addmod(f[i][j - 1][k],f[i + 1][j][k]);
                }
            }
        }
    }
    ans = f[1][0][0];
    cout<<ans<<endl;
    for(int i = 1;i <= tot;i++)
        ans = 1ll * ans * i % MOD;
    printf("%d\n",ans);
    return 0;
}