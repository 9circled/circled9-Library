## 概要
$N$ 頂点のグラフについて、任意の頂点間の距離を $O(N^3)$ で求めるやつ。

## コード
### 必須ライブラリ
- `vector`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct WarshallFloyd {
	int N;
	long long INF=1e18;
	vector<vector<long long>> dist;
	WarshallFloyd(int n){
		N = n;
		dist.assign(N, vector<long long>(N, (long long)INF));
		for (int i=0; i<N; i++) dist[i][i] = 0;
	}	

	void add(int i, int j, long long d){
		dist[i][j] = min(dist[i][j], d);
	}

	void calc(){
		for (int k=0; k<N; k++){
			for (int i=0; i<N; i++){
				for (int j=0; j<N; j++) dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
			}
		}
	}

	void update(int ni, int nj, long long d){
		for (int i=0; i<N; i++){
			for (int j=0; j<N; j++){
				dist[i][j] = min(dist[i][j], dist[i][ni]+d+dist[nj][j]);
			}
		}
	}
};
```

## 仕様・機能
- `WarshallFloyd W(N)` で頂点数 $N$ のワーシャルフロイド法を計算するグラフを構築できます。
- `calc`実行後に頂点 $i$ から頂点 $j$ までの距離が $W.dist[i][j]$ として格納されている。

### 関数
- `add(i, j, c)`：（`calc`の実行前）頂点 $i$ から頂点 $j$ にコスト $c$ の辺を張る。
- `calc()`：全頂点間の最短距離を計算する。
- `update(i, j, c)`：（`calc`の実行後）頂点 $i$ から頂点 $j$ にコスト $c$ の辺を張る。

## 計算量
- `add`： $O(1)$
- `calc`： $O(N^3)$
- `update`： $O(N^2)$

## 使用例