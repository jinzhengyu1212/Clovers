#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

const int S = 3 , N = 1010;

int sx[] = {1 , -1 , 0 , 0} , zy[] = {0 , 0 , 1 , -1}; 
int n , m , q , cur;
char A[N][N];

int siz[N][N] , c[N][N] , cs[N][N];
int s[N][N] , fa[N * N];
int vis[N][N];

int col[N * N];

int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m >> q; 
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cin >> A[i][j];
	for(int i = 0; i + S - 1 < n; i += S)
		for(int j = 0; j + S - 1 < m; j += S) {
			int cnt = 0;
			for(int x = 1; x <= S * S; x++) fa[x] = x;
			for(int x = i; x < i + S; x++)
				for(int y = j; y < j + S; y++)
					vis[x][y] = ++cnt;
			for(int x = i; x < i + S; x++)
				for(int y = j; y < j + S; y++)
				{
					for(int k = 0; k < 4; k++) {
						int tx = x + sx[k] , ty = y + zy[k];
						if(i <= tx && tx < i + S && j <= ty && ty < j + S && A[x][y] == A[tx][ty]) {
							if(find(vis[x][y]) != find(vis[tx][ty]))
								cnt-- , fa[fa[vis[x][y]]] = fa[vis[tx][ty]];
						}
					}
				}
			for(int x = i; x < i + S; x++)
				for(int y = j; y < j + S; y++)
					vis[x][y] = find(vis[x][y]);
			siz[i / S][j / S] = cnt;
			cnt = 0;
			for(int y = j; y < j + S - 1; y++) if(!col[vis[i][y]]) col[vis[i][y]] = ++cnt;
			for(int x = i; x < i + S - 1; x++) if(!col[vis[x][j + S - 1]]) col[vis[x][j + S - 1]] = ++cnt;
			for(int y = j + S - 1; y > j; y--) if(!col[vis[i + S - 1][y]]) col[vis[i + S - 1][y]] = ++cnt;
			for(int x = i + S - 1; x > i; x--) if(!col[vis[x][j]]) col[vis[x][j]] = ++cnt;
			for(int y = j; y < j + S - 1; y++) c[i][y] = col[vis[i][y]];
			for(int x = i; x < i + S - 1; x++) c[x][j + S - 1] = col[vis[x][j + S - 1]];
			for(int y = j + S - 1; y > j; y--) c[i + S - 1][y] = col[vis[i + S - 1][y]];
			for(int x = i + S - 1; x > i; x--) c[x][j] = col[vis[x][j]];
			for(int y = j; y < j + S - 1; y++) col[vis[i][y]] = 0;
			for(int x = i; x < i + S - 1; x++) col[vis[x][j + S - 1]] = 0;
			for(int y = j + S - 1; y > j; y--) col[vis[i + S - 1][y]] = 0;
			for(int x = i + S - 1; x > i; x--) col[vis[x][j]] = 0;
			cs[i / S][j / S] = cnt;
		}
	while(q--) {
		int x1 , y1 , x2 , y2;
		cin >> x1 >> y1 >> x2 >> y2;
		x1-- , y1-- , x2-- , y2--;
		int Sx1 = ceil(x1 * 1.0 / S) , Sy1 = ceil((y1 + 1) * 1.0 / S) ,
			Sx2 = floor(x2 * 1.0 / S) , Sy2 = floor((y2 + 1) * 1.0 / S);
		if(Sx1 >= Sx2 || Sy1 >= Sy2) {
			int cnt = 0;
			for(int i = x1; i <= x2; i++)
				for(int j = y1; j <= y2; j++)
					s[i][j] = ++cnt;
			for(int i = 1; i <= cnt; i++) fa[i] = i;
			for(int x = x1; x <= x2; x++)
				for(int y = y1; y <= y2; y++)
					for(int k = 0; k < 4; k++) {
						int tx = x + sx[k] , ty = y + zy[k];
						if(x1 <= tx && tx <= x2 && y1 <= ty && ty <= y2 && A[x][y] == A[tx][ty]) {
							if(find(s[x][y]) != find(s[tx][ty]))
								cnt-- , fa[fa[s[x][y]]] = fa[s[tx][ty]];
						}
					}
			cout << cnt << endl;
			continue;
		}
		Sx1 *= S , Sx2 *= S , Sy1 *= S , Sy2 *= S;
		int cnt = 0 , ans = 0;
		for(int Sx = Sx1; Sx < Sx2; Sx += S)
			for(int Sy = Sy1; Sy < Sy2; Sy += S) {
				for(int y = Sy; y < Sy + S - 1; y++) s[Sx][y] = cnt + c[Sx][y];
				for(int x = Sx; x < Sx + S - 1; x++) s[x][Sy + S - 1] = cnt + c[x][Sy + S - 1];
				for(int y = Sy + S - 1; y > Sy; y--) s[Sx + S - 1][y] = cnt + c[Sx + S - 1][y];
				for(int x = Sx + S - 1; x > Sx; x--) s[x][Sy] = cnt + c[x][Sy];
				cnt += cs[Sx / S][Sy / S] , ans += siz[Sx / S][Sy / S];
			}
		for(int x = x1; x < Sx1; x++) for(int y = y1; y < Sy2; y++)
			s[x][y] = ++cnt , ++ans;
		for(int x = x1; x < Sx2; x++) for(int y = Sy2; y <= y2; y++)
			s[x][y] = ++cnt , ++ans;
		for(int x = Sx2; x <= x2; x++) for(int y = Sy1; y <= y2; y++)
			s[x][y] = ++cnt , ++ans;
		for(int x = Sx1; x <= x2; x++) for(int y = y1; y < Sy1; y++)
			s[x][y] = ++cnt , ++ans;
		for(int i = 1; i <= cnt; i++) fa[i] = i;
		for(int x = x1; x < Sx1; x++) for(int y = y1; y < Sy2; y++) {
			for(int i = 0; i < 4; i++) {
				int tx = x + sx[i] , ty = y + zy[i];
				if(x1 <= tx && tx <= x2 && y1 <= ty && ty <= y2 && A[x][y] == A[tx][ty]) {
					if(find(s[x][y]) != find(s[tx][ty]))
						ans-- , fa[fa[s[x][y]]] = fa[s[tx][ty]];
				}
			}
		}
		for(int x = x1; x < Sx2; x++) for(int y = Sy2; y <= y2; y++) {
			for(int i = 0; i < 4; i++) {
				int tx = x + sx[i] , ty = y + zy[i];
				if(x1 <= tx && tx <= x2 && y1 <= ty && ty <= y2 && A[x][y] == A[tx][ty]) {
					if(find(s[x][y]) != find(s[tx][ty]))
						ans-- , fa[fa[s[x][y]]] = fa[s[tx][ty]];
				}
			}
		}
		for(int x = Sx2; x <= x2; x++) for(int y = Sy1; y <= y2; y++) {
			for(int i = 0; i < 4; i++) {
				int tx = x + sx[i] , ty = y + zy[i];
				if(x1 <= tx && tx <= x2 && y1 <= ty && ty <= y2 && A[x][y] == A[tx][ty]) {
					if(find(s[x][y]) != find(s[tx][ty]))
						ans-- , fa[fa[s[x][y]]] = fa[s[tx][ty]];
				}
			}
		}
		for(int x = Sx1; x <= x2; x++) for(int y = y1; y < Sy1; y++) {
			for(int i = 0; i < 4; i++) {
				int tx = x + sx[i] , ty = y + zy[i];
				if(x1 <= tx && tx <= x2 && y1 <= ty && ty <= y2 && A[x][y] == A[tx][ty]) {
					if(find(s[x][y]) != find(s[tx][ty]))
						ans-- , fa[fa[s[x][y]]] = fa[s[tx][ty]];
				}
			}
		}
		for(int x = Sx1 + S; x < Sx2; x += S)
			for(int y = Sy1; y < Sy2; y++)
				if(find(s[x][y]) != find(s[x - 1][y]) && A[x][y] == A[x - 1][y])
					ans-- , fa[fa[s[x][y]]] = fa[s[x - 1][y]];
		for(int x = Sx1; x < Sx2; x++)
			for(int y = Sy1 + S; y < Sy2; y += S)
				if(find(s[x][y]) != find(s[x][y - 1]) && A[x][y] == A[x][y - 1])
					ans-- , fa[fa[s[x][y]]] = fa[s[x][y - 1]];
		cout << ans << endl;
	}
	return 0;
}