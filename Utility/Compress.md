## 概要
座標圧縮をするやつ。

## コード
### 必須ライブラリ
- `vector`
- `algorithm`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
template<typename T>
struct Compress {
	vector<T> X;

	Compress() {}
	Compress(const vector<T>& v){
		X = v;
		build();
	}

	void add(const T& x){ X.push_back(x); }
	void add(const vector<T>& v){
		for (const auto& x : v) X.push_back(x);
	}
	void build(){
		sort(X.begin(), X.end());
		X.erase(unique(X.begin(), X.end()), X.end());
	}

	int get(const T& x) const { return lower_bound(X.begin(), X.end(), x) - X.begin(); }
	int operator[](const T& x) const { return get(x); }
	T inv(int i) const { return X[i]; }
	int size() const { return X.size(); }
};
```

## 仕様・機能
- `Compress X;` で座標圧縮する配列を構築します。
- 数列 $A$ を引数に入れると自動で座標圧縮します。
- `X[x]`で値 $x$ に対応するインデックスを受け取れます。

### 関数
- `add(x)`：値 $x$ を追加します。
- `add(v)`：配列 $v$ の要素を全て追加します。
- `build()`：座標圧縮を行います。
- `get(x)`：値 $x$ に対応するインデックスを返します。
- `inv(i)`： $i$ 番目の要素の値を返します。
- `size`：座標圧縮後の配列の大きさを返します。

## 計算量
- `add(x)`・`inv`・`size`： $O(1)$
- `add(v)`： $O(|v|)$
- `build()`： $O(N\log{N})$
- `get(x)`： $O(\log{N})$

## 使用例
- [ABC036 C - 座圧](https://atcoder.jp/contests/abc036/tasks/abc036_c) - [提出](https://atcoder.jp/contests/abc036/submissions/80099261)