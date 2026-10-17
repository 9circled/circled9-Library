## 概要
有向グラフを強連結成分で分けるやつ。

## コード
### 必須ライブラリ
- `vector`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct SCC {
	int N;
	int cnt = 0;
	vector<vector<int>> G, rG;
	SCC(int n) : N(n), G(n), rG(n) {}

	void add(int i, int j){
		G[i].push_back(j);
		rG[j].push_back(i);
	}

	vector<vector<int>> calc(){
		cnt = 0;
		vector<int> ord;
		vector<bool> vis(N);
		auto dfs = [&](auto&& dfs, int idx){
			if (vis[idx]) return;
			vis[idx] = true;
			for (int nxt : G[idx]){
				dfs(dfs, nxt);
			}
			ord.push_back(idx);
		};
		for (int i=0; i<N; i++){
			if (!vis[i]){
				dfs(dfs, i);
			}
		}
		vector<bool> rvis(N);
		vector<vector<int>> ret;
		auto rdfs = [&](auto&& rdfs, int idx, int k){
			if (rvis[idx]) return;
			rvis[idx] = true;
			ret[k].push_back(idx);
			for (int nxt : rG[idx]){
				rdfs(rdfs, nxt, k);
			}
		};
		for (int i=N-1; i>=0; i--){
			if (!rvis[ord[i]]){
				ret.push_back({});
				rdfs(rdfs, ord[i], cnt++);
			}
		}
		return ret;
	}
};
```

## 仕様・機能
- `SCC scc(N)` で頂点数 $N$ のを強連結成分分解をするグラフを構築できます。

### 関数
- `add(i, j)`：頂点 $i$ から頂点 $j$ に辺を張る。
- `calc()`：強連結成分分解をする。
  - 強連結成分ごとにvectorとなったものを返します。

## 計算量
- 構築： $O(|V|)$
- `add`： $O(1)$
- `calc`：　$O(|V|+|E|)$

## 使用例