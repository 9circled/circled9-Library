## 概要
文字列 $S$ とそのすべての接尾辞に対する最長共通接頭辞(LCP)の長さを表すZ配列を求めるやつ。

## コード
### 必須ライブラリ
- `vector`
- `string`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
vector<int> ZAlgorithm(const string& S){
	int N = S.size();
	vector<int> Z(N);
	Z[0] = N;
	int L = 0, R = 0;
	for (int i=1; i<N; i++){
		if (i<=R) Z[i] = min(Z[i-L], R-i+1);
		while (i+Z[i]<N && S[Z[i]]==S[i+Z[i]]) Z[i]++;
		if (i+Z[i]-1>R){
			L = i; R = i+Z[i]-1;
		}
	}
	return Z;
}
```

## 仕様・機能
- `ZAlgorithm Z(S)`で文字列 $S$ に対するZ配列を求めます。

## 計算量
- 構築：　 $O(|S|)$

## 使用例
- [ABC430 E - Shift String](https://atcoder.jp/contests/abc430/tasks/abc430_e) - [提出](https://atcoder.jp/contests/abc430/submissions/80289389)