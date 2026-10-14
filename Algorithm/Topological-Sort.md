## 概要
頂点同士の流れをそのままに一列に整列させるやつ。

## コード
### 必須ライブラリ
- `vector`
- `queue`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
vector<int> TopologicalSort(vector<vector<int>> &G){
	int N = G.size();
	vector<int> deg(N);
	for (int i=0; i<N; i++){
		for (int v : G[i]) deg[v]++;
	}
	priority_queue<int> que;
	for (int i=0; i<N; i++){
		if (deg[i]==0) que.push(-i);
	}
	vector<int> ret;
	while(que.size()){
		int idx = -que.top(); que.pop();
		ret.emplace_back(idx);
		for (int v : G[idx]){
			deg[v]--;
			if (deg[v]==0) que.push(-v);
		}
	}
	if (N==ret.size()) return ret;
	else return {};
}
```

## 仕様・機能
- `vector<int> A = TopologicalSort(G)` でグラフ $G$ の頂点をトポロジカルソートで昇順に整列します。
- トポロジカルソートができなかった場合は空の数列が返ってきます。

## 計算量
頂点の数 $V$ 、辺の数 $E$ として、
- 計算： $O(V\log{V}+E)$

## 使用例
- [ABC223 D - Restricted Permutation](https://atcoder.jp/contests/abc223/tasks/abc223_d) - [提出](https://atcoder.jp/contests/abc223/submissions/80047121)