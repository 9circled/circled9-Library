## 概要
$R-L$ が抑えられているときに $L\leq x\leq R$ の任意の整数 $x$ を素因数分解するやつ。

## コード
### 必須ライブラリ
- `vector`
- `cmath`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct SegmentSieve {
	long long L, R;
	vector<long long> primes;
	vector<vector<long long>> factors;

	SegmentSieve(long long l, long long r) : L(l), R(r), factors(r-l+1) {
		long long sqrtR = sqrt(R);
		vector<bool> _is_sprime(sqrtR+1, true);
		vector<long long> sprimes;
		for (long long i=2; i<=sqrtR; i++){
			if (_is_sprime[i]){
				sprimes.push_back(i);
				for (long long j=i*i; j<=sqrtR; j+=i){
					_is_sprime[j] = false;
				}
			}
		}
		vector<long long> rem(R-L+1);
		for (long long i=0; i<R-L+1; i++) rem[i] = L+i;
		for (long long p : sprimes){
			for (long long x=p*max((L+p-1)/p, 1LL); x<=R; x+=p){
				while (rem[x-L]>0&&rem[x-L]%p==0){
					factors[x-L].push_back(p);
					rem[x-L] /= p;
				}
			}
		}
		for (long long i=0; i<R-L+1; i++){
			if (rem[i]>1) factors[i].push_back(rem[i]);
			if (factors[i].size()==1) primes.push_back(L+i);
		}
	}

	vector<long long> factorize(long long x) const { return factors[x-L]; }
	bool is_prime(long long x) const { return factors[x-L].size()==1; }
};
```

## 仕様・機能
- `SegmentSieve sieve(L, R)` で $L\leq x\leq R$ までの構築ができます。
  - `sieve.primes` に $L\leq p\leq R$ を満たす素数 $p$ がまとめられています。

### 関数
- `factorize(x)`： $x$ の素因数が昇順に連なった配列を返します。
- `is_prime(x)`： $x$ が素数かどうかを返します。

## 計算量
- 構築： $O(\sqrt{R}\log\log\sqrt{R}+(R-L+1)\log\log\sqrt{R})$
- `factorize`： $O(\log{R})$
- `is_prime`： $O(1)$

## 使用例