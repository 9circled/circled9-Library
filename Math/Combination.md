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
	vector<mint> fact, ifact;

	Combination(int n) : fact(n+1), ifact(n+1){
		fact[0] = 1;
		for (int i=1; i<=n; i++) fact[i] = fact[i-1]*mint(i);
		ifact[n] = fact[n].inv();
		for (int i=n; i>=1; i--) ifact[i-1] = ifact[i]*mint(i);
	}

	mint F(int k){
		if (k<0 || k>=fact.size()) return 0;
		return fact[k];
	}

	mint C(int n, int k){
		if (k<0 || k>n) return 0;
		return fact[n]*ifact[k]*ifact[n-k];
	}

	mint P(int n, int k){
		if (k<0 || k>n) return 0;
		return fact[n]*ifact[n-k];
	}

	mint H(int n, int k){
		if (n==0 && k==0) return 1;
		return C(n+k-1, k);
	}
};
```

## 仕様・機能
- `Combination comb(N)` で最大値 $N$ までの構築ができます。

### 関数
- `comb.F(k)`： $k!$ を計算。
- `comb.C(n, k)`： $_nC_k$ を計算。
- `comb.P(n, k)`： $_nP_k$ を計算。
- `comb.H(n, k)`： $_nH_k$ を計算。

## 計算量
- 構築： $O(N)$
- 計算： $O(1)$

## 使用例
- [ABC405 E - Fruit Lineup](https://atcoder.jp/contests/abc405/tasks/abc405_e) - [提出](https://atcoder.jp/contests/abc405/submissions/80045396)