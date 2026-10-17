## 概要
木の構造を配列に落としこむやつ。

## コード
### 必須ライブラリ
- `vector`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct Eulertour_Path {
	int N;
	vector<int> vin, vout, tour;
	vector<int> ein, eout;
	vector<long long> ew;
	
	Eulertour_Path(vector<vector<tuple<int, int, int>>>& G, int root=0) : N(G.size()), vin(N), vout(N), ein(N), eout(N), ew(2*N) {
		auto dfs = [&](auto&& self, int u, int p) -> void {
			vin[u] = tour.size();
			tour.emplace_back(u);
			for (auto [v, w, id] : G[u]){
				if (v==p) continue;
				ein[id] = tour.size();
				ew[tour.size()] = w;
				self(self, v, u);
				eout[id] = tour.size();
				ew[tour.size()] = -w;
				tour.emplace_back(u);
			}
			vout[u] = tour.size();
		};
		dfs(dfs, root, -1);
	}

	int size(){
		return tour.size();
	}
};
```

## 仕様・機能
- `Eulertour_Path et(G, root)` で $root$ を根にした木 $G$ に関してオイラーツアーテクニックをします。
- `et.vin[u]`で頂点 $u$ の左側（含める）を示します。
- `et.vout[u]`で頂点 $u$ の右側（含めない）を示します。
  - 頂点 $u$ を起点とする部分木のパスクエリは $\lbrack \text{in}\lbrack u\rbrack+1, \text{out}\lbrack u\rbrack\rparen$ の範囲に対応する。
- `et.ein[i]`で辺 $i$ を通って親から子へ下る時のインデックスを示します。
- `et.eout[i]`で辺 $i$ を通って子から親へ上がる時のインデックスを示します。
- `et.tour`でオイラーツアーで求めた、訪れた順の頂点列を返します。

### 関数
- `et.size()`：`et.tour`の大きさを返します。

## 計算量
- 構築： $O(N)$
- `size`： $O(1)$

## 使用例