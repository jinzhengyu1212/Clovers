#include<bits/stdc++.h>
using namespace std;
#define gc getchar()
#define pc putchar
#define li long long
li read(){
	li x = 0,y = 0,c = gc;
	while(!isdigit(c)) y = c,c = gc;
	while(isdigit(c)) x = (x << 1) + (x << 3) + (c ^ '0'),c = gc;
	return y == '-' ? -x : x;
}
void print(li q){
	if(q < 0) pc('-'),q = -q;
	if(q >= 10) print(q / 10);
	pc(q % 10 + '0');
}
int n,m,p,k,jz[1000010],vl[1000010];
struct wz{
	int x,y;
}a[1000010];
int t[4000010],s[4000010],c[4000010];
#define ls q << 1
#define rs q << 1 | 1
#define ln ls,l,mid
#define rn rs,mid + 1,r
#define md int mid = l + r >> 1
void build(int q,int l,int r){
	if(l == r){
		t[q] = vl[l];s[q] = 1;return;
	}
	md;
	build(ln);build(rn);
	t[q] = min(t[ls],t[rs]);
	s[q] = 0;if(t[q] == t[ls]) s[q] += s[ls];if(t[q] == t[rs]) s[q] += s[rs];
}
inline void ps(int q){
	t[ls] += c[q];c[ls] += c[q];
	t[rs] += c[q];c[rs] += c[q];
	c[q] = 0;
}
void ins(int q,int l,int r,int al,int ar,int x){
	if(al > ar) return;
	if(l >= al && r <= ar){
		t[q] += x;c[q] += x;return;
	}
	ps(q);md;
	if(mid >= al) ins(ln,al,ar,x);
	if(mid < ar) ins(rn,al,ar,x);
	t[q] = min(t[ls],t[rs]);
	s[q] = 0;if(t[q] == t[ls]) s[q] += s[ls];if(t[q] == t[rs]) s[q] += s[rs];
}
int dx[4] = {0,-1,0,1},dy[4] = {-1,0,1,0};
#define mt(x,y) jz[(x - 1) * m + (y)]
#define lx(x) (x + dx[0])
#define ux(x) (x + dx[1])
#define fx(x,i) (x + dx[i])
#define fy(x,i) (x + dy[i])
#define ly(x) (x + dy[0])
#define uy(x) (x + dy[1])
#define chk(x,y) (x >= 1 && x <= n && y >= 1 && y <= m)
#define ax(q) a[q].x
#define ay(q) a[q].y
#define qwq(x,y) mt(fx(ax(x),y),fy(ay(x),y))
inline int ed(int q){//“黑格左上”性质结束的时间 
	int mn = p + 1;
	if(chk(lx(ax(q)),ly(ay(q)))) mn = min(mn,qwq(q,0));
	if(chk(ux(ax(q)),uy(ay(q)))) mn = min(mn,qwq(q,1));
	return mn;
}
inline int bg(int q){//“白格相邻”性质开始的时间 
	int mn1 = p + 1,mn2 = p + 1;
	for(int i = 0;i < 4;++i) if(chk(fx(ax(q),i),fy(ay(q),i))){
		if(qwq(q,i) < mn1) mn2 = mn1,mn1 = qwq(q,i);
		else if(qwq(q,i) < mn2) mn2 = qwq(q,i);
	} 
	return mn2;
}
int st[15],ft;
int main(){
	int i,j,u,v;
	n = read();m = read();k = read();p = n * m;
	for(i = 1;i <= p;++i){
		a[i].x = read() + 1;a[i].y = read() + 1;mt(ax(i),ay(i)) = i;
	}
	for(i = 1;i <= p;++i){
		vl[i] = vl[i - 1];
		if(bg(i) < i) --vl[i];
		if(ed(i) > i) ++vl[i];
		for(j = 0;j < 4;++j) if(chk(fx(ax(i),j),fy(ay(i),j))){
			if(qwq(i,j) < i && ed(qwq(i,j)) == i) --vl[i];
			else if(qwq(i,j) > i && bg(qwq(i,j)) == i) ++vl[i];
		}
	}
	build(1,1,p);
	for(i = 1;i <= k;++i){
		u = read() + 1;v = read() + 1;if(u > v) swap(u,v);
		if(u == v){
			print(s[1]);pc('\n');continue;
		}
		ft = 0;
		st[++ft] = u;st[++ft] = v;
		for(j = 0;j < 4;++j) if(chk(fx(ax(u),j),fy(ay(u),j))) st[++ft] = qwq(u,j);
		for(j = 0;j < 4;++j) if(chk(fx(ax(v),j),fy(ay(v),j))) st[++ft] = qwq(v,j);
		sort(st + 1,st + ft + 1);
		for(j = 1;j <= ft;++j) if(st[j] != st[j - 1]){
			if(bg(st[j]) < st[j]) ins(1,1,p,max(bg(st[j]),u),min(st[j],v) - 1,-1);
			if(ed(st[j]) > st[j]) ins(1,1,p,max(st[j],u),min(ed(st[j]),v) - 1,-1);
		}
		swap(mt(ax(u),ay(u)),mt(ax(v),ay(v)));swap(a[u],a[v]);
		for(j = 1;j <= ft;++j) if(st[j] != st[j - 1]){
			if(bg(st[j]) < st[j]) ins(1,1,p,max(bg(st[j]),u),min(st[j],v) - 1,1);
			if(ed(st[j]) > st[j]) ins(1,1,p,max(st[j],u),min(ed(st[j]),v) - 1,1);
		}
		print(s[1]);pc('\n');
	}
	return 0;
}