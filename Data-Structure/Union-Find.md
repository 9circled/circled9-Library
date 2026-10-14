## 概要
動的な頂点同士の連結判定ができるやつ。

## コード
### 必須ライブラリ
- `vector`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct UnionFind {
	vector<int> parent;

	UnionFind(int N) : parent(N, -1) {}
	
	int root(int x) {
		if (parent[x] < 0) return x;
		return parent[x] = root(parent[x]);
	}

	int size(int x){
		return -parent[root(x)];
	}

	bool is_same(int x, int y) {
		return root(x) == root(y);
	}

	bool unite(int x, int y) {
		x = root(x); y = root(y);
		if (x == y) return false;
		if (parent[x]>parent[y]) swap(x, y);
		parent[x] += parent[y];
		parent[y] = x;
		return true;
	}
};
```

## 仕様・機能
- `UnionFind uf(N)` で頂点数 $N$ のUnion-Findを構築できます

### 関数
- `root(x)`：頂点 $x$ の代表根を返す。
- `size(x)`：頂点 $x$ の属する連結成分の大きさを返す。
- `is_same(x, y)`：頂点 $x$ と頂点 $y$ が同じ連結成分に属するかを判定する。
- `unite(x, y)`：頂点 $x$ と頂点 $y$ を繋ぐ。返り値として繋げたかを返す。

## 計算量
- 構築： $O(N)$
- `root`・`size`・`is_same`・`unite`：償却 $O(\alpha(N))$

## 使用例
- [ALPC A - Disjoint Set Union](https://atcoder.jp/contests/practice2/tasks/practice2_a) - [提出](https://atcoder.jp/contests/practice2/submissions/80045587)