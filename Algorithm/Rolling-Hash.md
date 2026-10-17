## 概要
文字列 $S$ の連続部分列についてハッシュ値を作るやつ。

## コード
### 必須ライブラリ
- `vector`
- `string`
- `random`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct RollingHash {
	static const long long mod = (1LL << 61)-1;
	vector<long long> hash, pow;

	static long long get_base(){
		static long long set_base = []() {
			random_device rd;
			mt19937_64 rng(rd());
			uniform_int_distribution<long long> rand(2, mod-2);
			return rand(rng);
		}();
		return set_base;
	}

	static long long mul(long long a, long long b){
		__uint128_t c = (__uint128_t)a * b;
		long long res = (long long)(c >> 61) + (long long)(c & mod);
		if (res >= mod) res -= mod;
		return res;
	}
	
	RollingHash(const string& S){
		long long base = get_base();
		int N = S.size();
		hash.assign(N+1, 0);
		pow.assign(N+1, 1);
		for (int i=0; i<N; i++){
			long long val = mul(hash[i], base) + S[i];
			if (val >= mod) val -= mod;
			hash[i+1] = val;
			pow[i+1] = mul(pow[i], base);
		}
	}

	long long get(int l, int r){
		long long res = hash[r] - mul(hash[l], pow[r-l]);
		if (res < 0) res += mod;
		return res;
	}

	long long concat(long long h1, long long h2, int h2_len){
		long long res = mul(h1, pow[h2_len]) + h2;
		if (res >= mod) res -= mod;
		return res;
	}
};
```

## 仕様・機能
- `RollingHash H(S)` で文字列 $S$ でハッシュ値の初期化をします。
  - 初回実行時に $base$ の値が定められ、以降の計算ではその値を用います。

### 関数
- `get(l, r)`： $S\lbrack l, r\rparen$ のハッシュ値を取得します。
- `concat(h1, h2, h2_len)`：ハッシュ値 $h_1, h_2$ の結合をします。
  - $h_2$ を求めた際の文字列の長さを渡す必要があります。

## 計算量
- 構築：　 $O(|S|)$
- `get`・`concat`： $O(1)$

## 使用例