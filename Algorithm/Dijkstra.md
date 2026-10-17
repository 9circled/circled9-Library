## 概要
頂点 $i$ から任意の頂点 $j$ までの最短距離を $O(|E|\log{|V|})$ で求めるやつ。

## コード
### 必須ライブラリ
- `vector`
- `queue`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct Dijkstra {
	int N;
	long long INF=1e18;
	vector<vector<pair<int, long long>>> G;
	Dijkstra(int n) : N(n), G(n) {}

	void add(int i, int j, long long d){
		G[i].emplace_back(j, d);
	}

	vector<long long> calc(int start){
		vector<long long> dist(N, INF);
		dist[start] = 0;

		priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
		pq.emplace(0, start);
		while (pq.size()){
			auto [v, from] = pq.top(); pq.pop();
			if (v>dist[from]) continue;
			for (auto [to, c] : G[from]){
				if (dist[to]>dist[from] + c){
					dist[to] = dist[from]+c;
					pq.emplace(dist[to], to);
				}
			}
		}
		return dist;
	}
};
```

## 仕様・機能
- `Dijkstra D(N)` で頂点数 $N$ のダイクストラ法を計算するグラフを構築できます。

### 関数
- `add(i, j, c)`：頂点 $i$ から頂点 $j$ にコスト $c$ の辺を張る。
- `calc(i)`：頂点 $i$ から各頂点の最短距離を計算し、配列として返す。

## 計算量
- `add`： $O(1)$
- `calc`： $O(|E|\log{|V|})$

## 使用例