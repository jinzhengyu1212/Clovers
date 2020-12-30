#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,m,dep[N];
vector<int> v[N];
void dfs(int u,int f){
    for(int i=0;i<(int)v[u].size();i++){
        int to=v[u][i]; if(to==f) continue;
        dep[to]=dep[u]+1; dfs(to,u);
    }
}

int mi[N<<2],tag[N<<2];
struct Segment_Tree{
    void update(int x,int l,int r,int L,int R,int val){
        if(L<=l&&r<=R){
            tag[x]=val;
            mi[x]=val;
        }
        
    }
}tree;

int main(){

}