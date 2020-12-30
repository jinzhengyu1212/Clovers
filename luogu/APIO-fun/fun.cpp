#include<bits/stdc++.h>
#include "fun.h"
using namespace std;
typedef vector<int> V;
const int N=120000;
int dep[N],sz[N],rt=0,n,cnt=0,id[3],nowpos=-1;
vector<int> son[N],ans;
bool cmp(int x,int y){return dep[x]<dep[y];}
void solver2(int idx,int idy){//X first
    while(!son[idx].empty()||!son[idy].empty()){
        if(son[idx].empty()) break;
        ans.push_back(son[idx].back());
        son[idx].pop_back(); swap(idx,idy);
    }
    ans.push_back(rt);
    if(!son[idx].empty()) ans.push_back(son[idx][0]);
    if(!son[idy].empty()) ans.push_back(son[idy][0]);
}

typedef pair<int,int> pii;
#define mk make_pair
set<pii> st[N];
void solver3(){
    int mx=0,ID;
    for(int i=0;i<=2;i++)
        if((int)son[id[i]].size()>mx) mx=(int)son[id[i]].size(), ID=i;
    if(mx*2==n){
        if(ID!=0) swap(id[ID],id[0]);
        for(int i=0;i<(int)son[id[2]].size();i++) 
            son[id[1]].push_back(son[id[2]][i]);
        sort(son[id[1]].begin(),son[id[1]].end(),cmp);
        solver2(id[0],id[1]);
        return;
    } 
    for(int i=0;i<=2;i++) {
        for(int j=0;j<(int)son[id[i]].size();j++){
            int to=son[id[i]][j];
            st[id[i]].insert(mk(dep[to],to));
        }
    }
    int PRE=-1,rest=n,pre=1000000,predep=-1;
    while('M'+'Y'+'Y'+'A'+'N'+'D'+'H'+'C'+'Y'+'A'+'K'+'I'+'O'+'I'){
        int mx1=((st[id[0]].empty()||PRE==id[0]) ? -1 : st[id[0]].rbegin()->second);
        int mx2=((st[id[1]].empty()||PRE==id[1]) ? -1 : st[id[1]].rbegin()->second);
        int mx3=((st[id[2]].empty()||PRE==id[2]) ? -1 : st[id[2]].rbegin()->second);
        mx=0; int iid;
        if(mx1!=-1&&mx<dep[mx1]) mx=dep[mx1],ID=0,iid=mx1;
        if(mx2!=-1&&mx<dep[mx2]) mx=dep[mx2],ID=1,iid=mx2;
        if(mx3!=-1&&mx<dep[mx3]) mx=dep[mx3],ID=2,iid=mx3;
        assert(mx1!=-1||mx2!=-1||mx3!=-1);
        st[id[ID]].erase(mk(dep[iid],iid)); 
        ans.push_back(iid); rest--; 
        assert(rest==n-2||predep+dep[iid]<=pre);
        pre=predep+dep[iid]; predep=dep[iid];
        PRE=id[ID];
        mx=0,ID;
        for(int i=0;i<=2;i++)
            if((int)st[id[i]].size()>mx) mx=(int)st[id[i]].size(), ID=i;
        if(mx*2==rest){
            int tmpid=ID;
            mx1=((st[id[0]].empty()||PRE==id[0]) ? -1 : st[id[0]].rbegin()->second);
            mx2=((st[id[1]].empty()||PRE==id[1]) ? -1 : st[id[1]].rbegin()->second);
            mx3=((st[id[2]].empty()||PRE==id[2]) ? -1 : st[id[2]].rbegin()->second);
            mx=0;
            if(mx1!=-1&&mx<dep[mx1]) mx=dep[mx1],ID=0,iid=mx1;
            if(mx2!=-1&&mx<dep[mx2]) mx=dep[mx2],ID=1,iid=mx2;
            if(mx3!=-1&&mx<dep[mx3]) mx=dep[mx3],ID=2,iid=mx3;
            int CH=0; 
            if(ID!=tmpid&&mx>predep) CH=1;
            
            for(int i=0;i<=2;i++){
                son[id[i]].clear();
                while(!st[id[i]].empty()) {
                    if(CH!=1||st[id[i]].begin()->second!=iid) 
                        son[id[i]].push_back(st[id[i]].begin()->second);
                    st[id[i]].erase(st[id[i]].begin());
                }
            }
            if(tmpid!=0) swap(id[tmpid],id[0]);
            for(int i=0;i<(int)son[id[2]].size();i++) 
                son[id[1]].push_back(son[id[2]][i]);
            sort(son[id[0]].begin(),son[id[0]].end(),cmp);
            sort(son[id[1]].begin(),son[id[1]].end(),cmp);
            if(CH) son[id[1]].push_back(iid);
            if(!CH) solver2(id[0],id[1]);
            else solver2(id[1],id[0]);
            return;
        } 
    }
}

void init()
{
    sz[0]=n;
    for(int i=1;i<n;i++) sz[i]=attractionsBehind(0,i);
    for(int i=1;i<n;i++) 
        if(sz[i]<sz[rt]&&sz[i]>=(n+1)/2) rt=i;
    for(int i=0;i<n;i++) if(i!=rt){
        dep[i]=hoursRequired(rt,i);
        if(dep[i]==1) id[cnt++]=i, son[i].push_back(i);
    } 
    for(int i=0;i<n;i++) if(i!=rt&&dep[i]!=1){
        int dis1=hoursRequired(id[0],i),dis2=hoursRequired(id[1],i);
        if(dis1==dep[i]-1) son[id[0]].push_back(i);
        else if(dis2==dep[i]-1) son[id[1]].push_back(i);
        else son[id[2]].push_back(i);
    }
    for(int i=0;i<cnt;i++) sort(son[id[i]].begin(),son[id[i]].end(),cmp);
}

std::vector<int> createFunTour(int NN, int Q)
{
    n=NN;
    if(NN==2) {vector<int> TMP; TMP.push_back(0); TMP.push_back(1); return TMP;}
    init();
    if(cnt==2) solver2(id[0],id[1]);
    else solver3();
    return ans;
}