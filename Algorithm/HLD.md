## 概要
木の辺をheavyとlightに分けて木のパスクエリを良い感じにするやつ。

## コード
### 必須ライブラリ
- `vector`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct HLD {
	int N;
	vector<vector<int>> G;
	vector<int> parent, depth;
	vector<int> vertex, id, head;

	HLD(vector<vector<int>>& G, int root=0) : N(G.size()), G(G), parent(N), depth(N), vertex(N), id(N), head(N) {
		{
			auto dfs = [&](auto&& dfs, int u, int p) -> int {
				parent[u] = p;
				depth[u] = (p == -1 ? 0 : depth[p]+1);
				int sz_u = 1, max_sz = 0;
				for (int i=0; i<G[u].size(); i++){
					int ch = G[u][i];
					if (ch==p) continue;
					int s = dfs(dfs, ch, u);
					sz_u += s;
					if (max_sz<s){
						max_sz = s;
						swap(G[u][0], G[u][i]);
					}
				}
				return sz_u;
			};
			dfs(dfs, root, -1);
		}
		{
			int k = 0;
			auto dfs = [&](auto&& dfs, int u, int p) -> void {
				id[u] = k;
				vertex[k] = u;
				k++;
				for (int ch : G[u]){
					if (ch==p) continue;
					bool heavy = (ch==G[u][0]);
					head[ch] = (heavy ? head[u] : ch);
					dfs(dfs, ch, u);
				}
			};
			head[root] = root;
			dfs(dfs, root, -1);
		}
	};

	int level_ancestor(int u, int d){
		while (depth[head[u]]>d){
			u = parent[head[u]];
		}
		return vertex[id[u]-(depth[u]-d)];
	}

	int lca(int u, int v){
		while (head[u]!=head[v]){
			if (id[u]>id[v]) swap(u, v);
			v = parent[head[v]];
		}
		return (id[u]<id[v] ? u : v);
	}

	int distance(int u, int v){
		int w = lca(u, v);
		return (depth[u]-depth[w]) + (depth[v]-depth[w]);
	}

	int jump(int s, int t, int x){
		int c = lca(s, t);
		int dist = (depth[s]-depth[c]) + (depth[t]-depth[c]);
		if (dist<x) return -1;
		if (x<depth[s]-depth[c]) return level_ancestor(s, depth[s]-x);
		return level_ancestor(t, depth[t]-(dist-x));
	}

	pair<vector<pair<int, int>>, vector<pair<int, int>>> get_path(int u, int v, bool edge=false){
		vector<pair<int, int>> up, down;
		while (head[u]!=head[v]){
			if (id[u]>id[v]){
				up.push_back({id[head[u]], id[u]+1});
				u = parent[head[u]];
			} else {
				down.push_back({id[head[v]], id[v]+1});
				v = parent[head[v]];
			}
		}
		if (edge && u==v) return {up, down};
		if (id[u]>id[v]){
			up.push_back({id[v]+edge, id[u]+1});
		} else {
			down.push_back({id[u]+edge, id[v]+1});
		}
		return {up, down};
	}
};
```

## 仕様・機能
- `HLD hld(G, root)` で $root$ を根にした木 $G$ に関して重軽分解をします。

### 関数
- `level_ancestor(u, d)`：頂点 $u$ の祖先で、深さが $d$ のものを求めます。
- `lca(u, v)`：頂点 $u$ と頂点 $v$ の最近共通祖先(LCA)を求めます。
- `distance(u, v)`：頂点 $u$ と頂点 $v$ の距離を求めます。
- `jump(s, t, x)`：頂点 $s$ から頂点 $t$ までのパスにおいて $x$ 番目の頂点を求めます。
- `get_path`：頂点 $u$ から頂点 $v$ までのパスについて、対応するインデックスの範囲の組 $\lbrack l, r\rparen$ を返します。
  - 1つ目の要素が $u\rightarrow\text{LCA}$ 、2つ目の要素が $\text{LCA}\rightarrow v$ に対応します。

## 計算量
- 構築： $O(N)$
- `level_ancestor`・`lca`・`distance`・`jump`・`get_path`： $O(\log{N})$

## 使用例