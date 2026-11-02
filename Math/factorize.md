## 概要
正整数 $N$ の素因数分解を $O(\sqrt{N})$ で行うやつ。

## コード
### 必須ライブラリ
- なし

### 本体
```cpp
// https://github.com/9circled/circled9-Library
vector<long long> factorize(long long N){
	vector<long long> factor;
	for (long long p=2; p*p<=N; p++){
		while (N%p==0){
			factor.push_back(p);
			N /= p;
		}
	}
	if (N!=1) factor.push_back(N);
	return factor;
}
```

## 仕様・機能
- `factorize(N)` で $N$ の素因数を昇順にまとめた配列を返す。

## 計算量
- 計算： $O(\sqrt{N})$

## 使用例