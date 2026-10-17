## 概要
文字列 $S$ を90度時計回り（右）に回転させます。

## コード
### 必須ライブラリ
- `vector`
- `string`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
void Rotate(vector<string>& S){
	int H = S.size(), W = S[0].size();
	vector<string> T(W);
	for (int i=H-1; i>=0; i--){
		for (int j=0; j<W; j++){
			T[j] += S[i][j];
		}
	}
	S = T;
}
```

## 仕様・機能
- `Rotate(S)` で文字列 $S$ をそのまま時計回りに90度回転させます。

## 計算量
- 操作： $O(HW)$

## 使用例
- [ABC404 B - Grid Rotation](https://atcoder.jp/contests/abc404/tasks/abc404_b) - [提出](https://atcoder.jp/contests/abc404/submissions/80098631)