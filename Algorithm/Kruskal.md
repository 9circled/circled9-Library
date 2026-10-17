## 概要
グラフの最小全域木や最大全域木をつくるやつ。

## コード
### 必須ライブラリ
- `vector`
- `algorithm`
- [`Union-Find`](../Data-Structure/Union-Find.md)

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct Kruskal {
	int N;
	long long SUM=0;
	vector<tuple<long long, int, int, int>> edge;
	vector<vector<pair<int, long long>>> G;
	vector<int> ids;
	UnionFind uf;
	bool MAX;

	Kruskal(int n, bool MAX=false) : N(n), G(n), uf(n), MAX(MAX) {}

	void add(int i, int j, long long d, int id = -1) {
		edge.emplace_back(d, i, j, id);
	}

	bool calc(){
		int cnt=N;
		SUM = 0;
		if (MAX) sort(edge.rbegin(), edge.rend());
		else sort(edge.begin(), edge.end());
		for (auto [d, i, j, id] : edge){
			if (uf.unite(i, j)){
				G[i].emplace_back(j, d);
				G[j].emplace_back(i, d);
				SUM += d;
				cnt--;
				ids.push_back(id);
			}
		}
		return cnt == 1;
	}
};
```

## 仕様・機能
- `Kruskal K(N);` で頂点数 $N$ のクラスカル法を計算するグラフを構築できます。
- そのままだと最小全域木を、`K(N, true)`とすると最大全域木を作ります。

### 関数
- `add(i, j, c, id)`：頂点 $i$ から頂点 $j$ にコスト $c$ の辺番号 $id$ の辺を張る。
- `calc()`：最小全域木（最大全域木）を作る。
  - 計算後は以下のような形で結果が記録されています。
    - `K.G`：計算した木のグラフ構造（隣接リスト形式）
	- `K.SUM`：木の全体の重みの総和
	- `K.ids`：番号を定義した際の木を構成数辺の番号集合

## 計算量
- `add`： $O(1)$
- `calc`： $O(|E|\log{|E|})$

## 使用例