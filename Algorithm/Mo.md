## 概要
追加・削除操作が $O(1)$ でできるが計算が複雑なクエリに対して $O(N\sqrt{Q})$ で求めるやつ。

## コード
### 必須ライブラリ
- `vector`
- `cmath`
- `algorithm`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct Mo {
	int N;
	vector<int> L, R;

	Mo(int n) : N(n) {}

	void add(int l, int r){
		L.push_back(l); R.push_back(r);
	}

	template<typename Add, typename Del, typename Res>
	void build(Add add, Del del, Res res){
		int Q = L.size();
		int sq = max(1, int(N/sqrt(Q)));
		vector<int> qi(Q);
		for (int i=0; i<Q; i++) qi[i] = i;
		sort(qi.begin(), qi.end(), [&](int i, int j){
			if (L[i]/sq!=L[j]/sq) return L[i]<L[j];
			return (L[i]/sq%2==0) ? R[i]<R[j] : R[i]>R[j];
		});
		int l = 0, r = 0;
		for (int i : qi){
			while (l>L[i]){
				l--;
				add(l);
			}
			while (r<R[i]){
				add(r);
				r++;
			}
			while (l<L[i]){
				del(l);
				l++;
			}
			while (r>R[i]){
				r--;
				del(r);
			}
			res(i);
		}
	}
};
```

## 仕様・機能
- `Mo mo(N);` で操作対象配列の大きさが $N$ のものの構築をします。

### 関数
- `add(l, r)`：クエリ $\lbrack l, r\rparen$ を追加します。
- `calc(add0, del0, res0)`：Moを実行します。
  - `add0`：追加操作を行うラムダ式（引数は対応する配列のインデックス）
  - `del0`：削除操作を行うラムダ式（引数は対応する配列のインデックス）
  - `res0`：答えの記録を行うラムダ式（引数は対応するクエリのインデックス）

## 計算量
- 構築： $O(N)$
- `add`： $O(1)$
- `calc`： $O(N\sqrt{Q})$

## 使用例