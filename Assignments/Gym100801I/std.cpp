//2015-2016 ACM-ICPC, NEERC, Northern Subregional Contest Problem. I
//O(n + m)
//I cannot handle this problem. QAQ
#include<bits/stdc++.h>
using namespace std;

int read(){
	int a = 0; char c = getchar(); while(!isdigit(c)) c = getchar();
	while(isdigit(c)){a = a * 10 + c - 48; c = getchar();} return a;
}
const int _ = 1e5 + 7; int N , M , A[_] , B[_] , C[_] , cntb[_]; bool vis[_]; vector < int > pot[_];

int main(){
	N = read(); M = read();
	for(int i = 1 ; i <= M ; ++i){
		A[i] = read(); B[i] = read(); C[i] = read(); ++cntb[B[i]];
		pot[A[i]].push_back(i); pot[C[i]].push_back(i);
	}
	vector < int > seq; queue < int > q; for(int i = 1 ; i <= N ; ++i) if(!cntb[i]) q.push(i);
	while(!q.empty()){
		int x = q.front(); q.pop(); seq.push_back(x); vector < int > tmp;
		for(auto t : pot[x]) if(!vis[t]){vis[t] = 1; tmp.push_back(t); if(!--cntb[B[t]]) q.push(B[t]);}
		pot[x] = tmp;
	}
    for(auto t: seq) cout<<t<<endl;
	static int id[_]; reverse(seq.begin() , seq.end()); int pl = 1 , pr = 0;
	for(auto t : seq){
		int cntl = 0 , cntr = 0; 
        for(auto i : pot[t]) id[A[i] + C[i] - t] > id[B[i]] ? ++cntl : ++cntr;
		id[t] = cntl >= cntr ? --pl : ++pr;
	}
	static int ans[_]; for(int i = 1 ; i <= N ; ++i) ans[id[i] - pl + 1] = i;
	for(int i = 1 ; i <= N ; ++i) printf("%d " , ans[i]);
	return 0;
}