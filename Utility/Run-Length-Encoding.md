## 概要
文字列 $S$ や数列 $A$ をランレングス圧縮するやつ。

## コード
### 必須ライブラリ
- なし

### 本体
```cpp
// https://github.com/9circled/circled9-Library
template <typename T>
vector<pair<typename T::value_type, int>> RLE(T& A){
	vector<pair<typename T::value_type, int>> ret;
	for (auto c : A){
		if (ret.size() && ret.back().first==c) ret.back().second++;
		else ret.emplace_back(c, 1);
	}
	return ret;
}
```

## 仕様・機能
`vector<pair<char, int>> R = RLE(S)` で文字列のランレングス圧縮を、

`vector<pair<int, int>> R = RLE(A)` などで数列のランレングス圧縮をします。

## 計算量
- 構築： $O(|S|)$ や $O(|A|)$

## 使用例
- [ABC019 B - 高橋君と文字列圧縮](https://atcoder.jp/contests/abc019/tasks/abc019_2) - [提出](https://atcoder.jp/contests/abc019/submissions/80045884)