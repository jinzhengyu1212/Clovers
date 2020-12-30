#include <bits/stdc++.h>
using namespace std;

inline int ty() {
	char ch = getchar(); int x = 0, f = 1;
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}

const int _ = 2e5 + 10;
int n, m, L, ct1, ct2, pos[_], lim[_], nxt[_], lst[_], num[_];

struct node {
	int id, dir, pos, dis, tar;
	node(int _id = 0, int _dir = 0, int _pos = 0, int _dis = 0, int _tar = 0) {
		id = _id, dir = _dir, pos = _pos, dis = _dis, tar = _tar;
	}
	bool operator<(const node &rhs) const {
		if (dir == rhs.dir) return pos < rhs.pos;
		return dir < rhs.dir;
	}
} sta[_];

#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid ((l + r) >> 1)

struct data {
	int dis, tar, id;
	data(int _dis = 0, int _tar = 0, int _id = 0) {
		dis = _dis, tar = _tar, id = _id;
	}
	bool operator<(const data &rhs) const {
		if (dis == rhs.dis) return id < rhs.id;
		return dis < rhs.dis;
	}
};

struct TAG {
	int dis, tar;
	TAG(int _dis = 0, int _tar = 0) { dis = _dis, tar = _tar; }
	TAG& operator+=(const TAG &rhs) {
		dis += rhs.dis;
		if (rhs.tar) tar = rhs.tar;
		return *this;
	}
};

struct SegmentTree {
	data val[_ << 2];
	TAG tag[_ << 2];
	void add(int p, TAG x) {
		val[p].dis += x.dis;
		if (x.tar) val[p].tar = x.tar;
		tag[p] += x;
	}
	void down(int p) {
		if (tag[p].dis || tag[p].tar) {
			add(ls, tag[p]);
			add(rs, tag[p]);
			tag[p] = TAG(0, 0);
		}
	}
	void up(int p) { val[p] = min(val[ls], val[rs]); }
	void build(int p, int l, int r) {
		if (l == r) {
			val[p] = data(sta[l].dis, sta[l].tar, sta[l].id);
			return;
		}
		build(ls, l, mid);
		build(rs, mid + 1, r);
		up(p);
	}
	data query(int p, int l, int r, int x, int y) {
		if (x <= l && r <= y) return val[p];
		down(p);
		if (y <= mid) return query(ls, l, mid, x, y);
		else if (x > mid) return query(rs, mid + 1, r, x, y);
		else return min(query(ls, l, mid, x, mid), query(rs, mid + 1, r, mid + 1, y));
	}
	void change(int p, int l, int r, int x) {
		if (l == r) {
			val[p].dis = 0x3f3f3f3f;
			return;
		}
		down(p);
		if (x <= mid) change(ls, l, mid, x);
		else change(rs, mid + 1, r, x);
		up(p);
	}
	void modify(int p, int l, int r, int x, int y, TAG z) {
		if (x <= l && r <= y) {
			add(p, z);
			return;
		}
		down(p);	
		if (y <= mid) modify(ls, l, mid, x, y, z);
		else if (x > mid) modify(rs, mid + 1, r, x, y, z);
		else modify(ls, l, mid, x, mid, z), modify(rs, mid + 1, r, mid + 1, y, z);
		up(p);
	}
} tr;

#undef ls
#undef rs
#undef mid

inline int getdis(int x, int y, int dir) {
	if (dir == 0) {
		if (pos[x] < pos[y]) return pos[y] - pos[x];
		else return L - pos[x] + pos[y];
	} else {
		if (pos[x] > pos[y]) return pos[x] - pos[y];
		else return pos[x] + L - pos[y];
	}
}

inline bool judge(int x, int y, int l, int r) {
	return sta[x].pos >= l && sta[x].pos <= r && sta[y].pos >= l && sta[y].pos <= r;
}

inline void modify(int l, int r, int dis, int tar, int dir) {
	node tmp;
	int L = (dir == 0) ? 1 : ct1 + 1;
	int R = (dir == 0) ? ct1 + 1 : n + 1;
	tmp.dir = dir, tmp.pos = l;
	int st = lower_bound(sta + L, sta + R, tmp) - sta;
	tmp.pos = r;
	int ed = upper_bound(sta + L, sta + R, tmp) - sta - 1;
	if (judge(st, ed, l, r))
		tr.modify(1, 1, n, st, ed, TAG(dis, tar));
}

inline void update1(int l, int r, int dis, int tar, int dir) {
	if (l > r) {
		modify(l + 1, L, dis, tar, dir);
		modify(0, r, dis, tar, dir);
	} else modify(l + 1, r, dis, tar, dir);
}

inline void update2(int l, int r, int dis, int tar, int dir) {
	if (l > r) {
		modify(l, L, dis, tar, dir);
		modify(0, r - 1, dis, tar, dir);
	} else modify(l, r - 1, dis, tar, dir);
}

int main() {
	n = ty(), m = ty(), L = ty();
	pos[1] = 0, lst[1] = m, nxt[1] = 2;
	for (int i = 2; i <= m; ++i) {
		pos[i] = ty();
		nxt[i] = i == m ? 1 : i + 1;
		lst[i] = i - 1;
	}
	for (int i = 1; i <= m; ++i) lim[i] = ty();
	for (int i = 1; i <= n; ++i) {
		int s = ty(), b = ty(), d, t;
		if (s == 0) {
			++ct1;
			t = lower_bound(pos + 1, pos + m + 1, b) - pos;
			if (t > m) t = 1, d = L - b;
			else d = pos[t] - b;
		} else {
			++ct2;
			t = upper_bound(pos + 1, pos + m + 1, b) - pos;
			--t;
			d = b - pos[t];
		}
		sta[i] = node(i, s, b, d, t);
	}
	sort(sta + 1, sta + n + 1);

	for (int i = 1; i <= n; ++i) num[sta[i].id] = i;
	tr.build(1, 1, n);
	int out = m, pp = n;
	long long ans = 0;
	while (out && pp) {
		data x = tr.query(1, 1, n, 1, n);
		int id = x.id, tar = x.tar;
		tr.change(1, 1, n, num[id]);
		ans ^= (1ll * id * tar);
        //cout<<id<<" "<<tar<<endl;
		--pp, --lim[tar];
		if (!lim[tar]) {
			int l = pos[lst[tar]] % L, r = pos[nxt[tar]] % L, now = pos[tar] % L;

			update1(l, now, getdis(tar, nxt[tar], 0), nxt[tar], 0);
			update2(now, r, getdis(tar, lst[tar], 1), lst[tar], 1);

			nxt[lst[tar]] = nxt[tar];
			lst[nxt[tar]] = lst[tar];
			--out;
		}
	}
	printf("%lld\n", ans);
	return 0;
}