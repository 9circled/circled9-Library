## 概要
$1\leq x\leq N$ の任意の整数 $x$ を素因数分解したり最小素因数を求めたりするやつ。

## コード
### 必須ライブラリ
- `vector`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct EratosSieve {
	int N;
	vector<int> primes, lpf, kinds;

	EratosSieve(int n) : N(n), lpf(n+1, 0), kinds(n+1, 0) {
		for (int i=2; i<=n; i++){
			if (lpf[i]==0){
				lpf[i] = i;
				kinds[i] = 1;
				primes.push_back(i);
				for (int j=i*2; j<=n; j += i){
					if (lpf[j] == 0) lpf[j] = i;
					kinds[j]++;
				}
			}
		}
	}

	vector<pair<int, int>> factorize(int x){
		vector<pair<int, int>> res;
		while (x>1){
			int p = lpf[x], e = 0;
			while (x%p==0){
				x /= p;
				e++;
			}
			res.emplace_back(p, e);
		}
		return res;
	}

	vector<int> divisors(int x){
		vector<int> res({1});
		auto pf = factorize(x);
		for (auto [p, e] : pf){
			int s = res.size();
			for (int i=0; i<s; i++){
				int v = 1;
				for (int j=0; j<e; j++){
					v *= p;
					res.push_back(res[i]*v);
				}
			}
		}
		return res;
	}

	bool is_prime(int x){
		if (x<=1) return false;
		return x==lpf[x];
	}
};
```

## 仕様・機能
- `EratosSieve es(N)` で最大値 $N$ までの構築ができます。
  - `es.primes` に $N$ までの素数がまとめられています。
  - `es.plf[i]` に $i$ の最小素因数があります。
  - `es.kinds[i]` に $i$ の素因数の数があります。

### 関数
- `factorize(x)`： $x$ を素因数分解して`(素数、指数)`の配列として返します。
- `divisor(x)`： $x$ の約数を配列で返します。（昇順とは限らない）
- `is_prime(x)`： $x$ が素数かどうかを返します。

## 計算量
- 構築： $O(N)$
- `factorize`： $O(\log{N})$
- `divisor`： $O(\sigma(x))$ （ $x$ の約数の個数）
- `is_prime`： $O(1)$

## 補足
$N$ 以下の自然数で約数の個数が最大の整数を $M$ とします。

| $N$ | $M$ | $\sigma(M)$ |
|:------:|:------:|:------:|
|100|60|12|
|500|360|24|
|1000|840|32|
|5000|2520|48|
|10000|7560|64|
| $10^5$ |83160|128|
| $10^6$ |720720|240|
| $10^7$ |8648640|448|
| $10^8$ |73513440|768|
| $10^9$ |735134400|1344|
| $10^{14}$ |97821761637600|17280|
| $10^{18}$ |897612484786617600|103680|

## 使用例