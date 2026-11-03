## 概要
正整数 $N$ の約数全列挙を $O(\sqrt{N})$ で行うやつ。

## コード
### 必須ライブラリ
- `vector`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
vector<long long> divisors(long long N){
	vector<long long> div1,div2;
	for (long long p=1; p*p<=N; p++){
		if (N%p==0){
			div1.emplace_back(p);
			if (p*p!=N) div2.emplace_back(N/p);
		}
	}
	div1.insert(div1.end(), div2.rbegin(), div2.rend());
	return div1;
}
```

## 仕様・機能
- `divisors(N)` で $N$ の約数を昇順にまとめた配列を返す。

## 計算量
- 計算： $O(\sqrt{N})$

## 使用例