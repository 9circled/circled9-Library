## 概要
木の構造を配列に落としこむやつ。

## コード
### 必須ライブラリ
- `vector`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct Eulertour_Subtree {
	int N;
	vector<int> in, out, tour;
	
	Eulertour_Subtree(vector<vector<int>>& G, int root=0) : N(G.size()), in(N), out(N) {
		auto dfs = [&](auto&& self, int u, int p) -> void {
			in[u] = tour.size();
			tour.emplace_back(u);
			for (int v : G[u]){
				if (v==p) continue;
				self(self, v, u);
			}
			out[u] = tour.size();
		};
		dfs(dfs, root, -1);
	}
};
```

## 仕様・機能
- `Eulertour_Subtree et(G, root)` で $root$ を根にした木 $G$ に関してオイラーツアーテクニックをします。
- `et.in[u]`で頂点 $u$ の左側（含める）を示します。
- `et.out[u]`で頂点 $u$ の右側（含めない）を示します。
  - 頂点 $u$ の部分木の範囲は $\lbrack \text{in}\lbrack u\rbrack, \text{out}\lbrack u\rbrack\rparen$ に対応します。
- `et.tour`でオイラーツアーで求めた、訪れた順の頂点列を返します。

## 計算量
- 構築： $O(N)$

## 使用例