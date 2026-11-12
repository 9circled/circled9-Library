## 概要
負の辺が存在するグラフについて頂点 $i$ から任意の頂点 $j$ までの最短距離を $O(|E||V|)$ で求めるやつ。

## コード
### 必須ライブラリ
- `vector`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct BellmanFord {
	int N;
	long long INF=1e18;
	vector<tuple<int, int, long long>> E;
	BellmanFord(int n) : N(n) {}

	void add(int i, int j, long long d){
		E.emplace_back(i, j, d);
	}

	vector<long long> calc(int start){
		vector<long long> dist(N, INF);
		dist[start] = 0;
		for (int k=0; k<2*N; k++){
			bool cng = false;
			for (auto [i, j, d] : E){
				if (dist[i]==INF) continue;
				if (dist[i]==-INF){
					if (dist[j]!=-INF){
						cng = true;
						dist[j] = -INF;
					}
				} else if (dist[i]+d<dist[j]){
					cng = true;
					dist[j] = (k>=N-1 ? -INF : dist[i]+d);
				}
			}
			if (!cng) break;
		}
		return dist;
	}
};
```

## 仕様・機能
- `BellmanFord D(N)` で頂点数 $N$ のベルマンフォード法を計算するグラフを構築できます。

### 関数
- `add(i, j, c)`：頂点 $i$ から頂点 $j$ にコスト $c$ の辺を張る。
- `calc(i)`：頂点 $i$ から各頂点の最短距離を計算し、配列として返す。（負閉路が存在し無限に小さくなる場合は`-INF`を返す）

## 計算量
- `add`： $O(1)$
- `calc`： $O(|E||V|)$

## 使用例
- [ABC061 D - Score Attack](https://atcoder.jp/contests/abc061/tasks/abc061_d) - [提出](https://atcoder.jp/contests/abc061/submissions/80751784)