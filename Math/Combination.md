## 概要
$k!$ ・ $_nC_k$ ・ $_nP_k$ ・ $_nH_k$ を $\text{mod}M$ で計算するやつ。

## コード
### 必須ライブラリ
- `vector`
- [`modint`](./modint.md)

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct Combination {
	inline static vector<mint> fact{1}, ifact{1};

	static void extend(int N){
		int M = fact.size();
		if (N<M) return;
		fact.resize(N+1);
		for (int i=M; i<=N; i++) fact[i] = fact[i-1]*mint(i);
		ifact.resize(N+1);
		ifact[N] = fact[N].inv();
		for (int i=N; i>=M; i--) ifact[i-1] = ifact[i]*mint(i);
	}

	static mint F(int n){
		if (n<0) return 0;
		extend(n);
		return fact[n];
	}

	static mint C(int n, int k){
		if (k<0 || k>n) return 0;
		extend(n);
		return fact[n]*ifact[k]*ifact[n-k];
	}

	static mint P(int n, int k){
		if (k<0 || k>n) return 0;
		extend(n);
		return fact[n]*ifact[n-k];
	}

	static mint H(int n, int k){
		if (n==0 && k==0) return 1;
		return C(n+k-1, k);
	}
};
using comb = Combination;
```

## 仕様・機能
- 必要な値まで自動で延長されるので、初期値を与えて構築する必要はないです。
  - ただし、大きい初期値を与えて計算させた方が実行時間は短くなります。

### 関数
- `comb::extend(n)`： $n$ まで拡張します。
- `comb::F(n)`： $n!$ を計算。
- `comb::C(n, k)`： $_nC_k$ を計算。
- `comb::P(n, k)`： $_nP_k$ を計算。
- `comb::H(n, k)`： $_nH_k$ を計算。

## 計算量
- 計算： 拡張時 $O(n)$ ・拡張不要時 $O(1)$

## 使用例
- [ABC405 E - Fruit Lineup](https://atcoder.jp/contests/abc405/tasks/abc405_e) - [提出](https://atcoder.jp/contests/abc405/submissions/80617490)