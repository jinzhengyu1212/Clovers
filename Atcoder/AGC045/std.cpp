/*
AuThOr Gwj
*/
#include<bits/stdc++.h>
#define rb(a,b,c) for(int a=b;a<=c;++a)
#define rl(a,b,c) for(int a=b;a>=c;--a)
#define LL long long
#define IT iterator
#define PB push_back
#define II(a,b) make_pair(a,b)
#define FIR first
#define SEC second
#define FREO freopen("check.out","w",stdout)
#define rep(a,b) for(int a=0;a<b;++a)
#define KEEP while(1)
#define SRAND mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
#define random(a) rng()%a
#define ALL(a) a.begin(),a.end()
#define POB pop_back
#define ff fflush(stdout)
#define fastio ios::sync_with_stdio(false)
#define debug_pair(A) cerr<<A.FIR<<" "<<A.SEC<<endl;
using namespace std;
const int INF=0x3f3f3f3f;
typedef pair<int,int> mp;
typedef pair<mp,mp> superpair;
int n,a,b;
LL g[10050][2],allsum,sum[5005],f[5005][5005][2];
const int MOD=1e9+7,base=5010;	
int main(){
	fastio;
	cin>>n>>a>>b;
	if(a<b) swap(a,b);
	f[0][0][1]=1;
	g[0+base][1]=1;
	f[0][0][0]=1;
	sum[0]=1;
	allsum=1;
	rb(i,1,n){
		if(i>=b){
			allsum-=sum[i-b];
			allsum+=MOD;
			allsum%=MOD;
			rb(j,0,a-1){
				if(j>=b)
				g[j-i+base][0]+=f[i-b][j-b][0];
				g[j-i+base][0]%=MOD;
			}
		}
		rb(j,0,a-1){
			if(j<=i)
			rep(k,2){
				if(j==0){
					if(k==1){
						f[i][j][1]=allsum;
					}
				}
				else{
					if(!k){
						f[i][j][k]=g[j-i+base][1];
					}
					else{
						f[i][j][k]=g[j-i+base][0];
					}
				}
			}
			sum[i]+=f[i][j][0];
			sum[i]%=MOD;
			g[j-i+base][1]+=f[i][j][1];
			g[j-i+base][1]%=MOD;
		}
		allsum+=sum[i];
		allsum%=MOD;
	}
	LL res=1;
	rb(i,1,n) res<<=1,res%=MOD;
//	cout<<f[1][0][1]<<endl;
	rb(j,0,a-1){
		rep(k,2){
			res-=f[n][j][k];
//			cout<<j<<" "<<k<<" "<<f[n][j][k]<<endl;
			res+=MOD;
			res%=MOD;
		}
	}
	
	cout<<res<<endl;
	return 0;
}

