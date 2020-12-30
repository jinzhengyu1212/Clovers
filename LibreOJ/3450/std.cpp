#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int Maxn=3000;
const int Mod=1000000007;
int n;
vector<pair<int,int> > a;
int f[2][Maxn+5][2];
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		int x;
		scanf("%d",&x);
		a.push_back(make_pair(x,0));
	}
	for(int i=0;i<n;i++){
		int x;
		scanf("%d",&x);
		a.push_back(make_pair(x,1));
	}
	sort(a.begin(),a.end());
	f[0][0][0]=1;
	for(int i=0;i<(n<<1);i++){
		int cur=(i&1),nxt=(i&1)^1;
		memset(f[nxt],0,sizeof f[nxt]);
		if(a[i].second){
			f[nxt][0][0]=(f[nxt][0][0]+f[cur][0][0])%Mod;
			for(int j=1;j<=n;j++){
				f[nxt][j][0]=(f[nxt][j][0]+f[cur][j][0])%Mod;
				f[nxt][j-1][0]=(f[nxt][j-1][0]+1ll*j*f[cur][j][0])%Mod;
				f[nxt][j-1][1]=(f[nxt][j-1][1]+1ll*j*f[cur][j][1])%Mod;
			}
		}
		else{
			for(int j=0;j<=n;j++){
				f[nxt][j][1]=(f[nxt][j][1]+f[cur][j][0])%Mod;
				f[nxt][j][1]=(f[nxt][j][1]+f[cur][j][1])%Mod;
				f[nxt][j+1][0]=(f[nxt][j+1][0]+f[cur][j][0])%Mod;
				f[nxt][j+1][1]=(f[nxt][j+1][1]+f[cur][j][1])%Mod;
			}
		}
	}
	printf("%d\n",(f[0][0][0]+f[0][0][1])%Mod);
	return 0;
}