## 概要
一点更新・区間和クエリを $O(\log{N})$ でできるやつ。

## コード
### 必須ライブラリ
- `vector`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
template <typename T>
struct FenwickTree {
	int N;
	vector<T> tree;

	FenwickTree(int n, T e=0) : N(n+1), tree(n+1, 0) {
		for (int i=1; i<N; i++){
			tree[i] += e;
			int j = i+(i&-i);
			if (j<N) tree[j] += tree[i];
		}
	}

	FenwickTree(vector<T> A) : N(A.size()+1), tree(A.size()+1, 0) {
		for (int i=1; i<N; i++){
			tree[i] += A[i-1];
			int j = i+(i&-i);
			if (j<N) tree[j] += tree[i];
		}
	}

	void add(int i, T x){
		i++;
		for (int idx=i; idx<N; idx+=(idx & -idx)) tree[idx] += x;
	}

	void set(int i, T x){
		add(i, -get(i)+x);
	}

	T sum(int i){
		T ret(0);
		for (int idx=i; idx>0; idx-=(idx & -idx)) ret += tree[idx];
		return ret;
	}

	T sum(int l, int r){
		return sum(r)-sum(l);
	}

	T get(int i){
		return sum(i+1)-sum(i);
	}

	int lower_bound(T x){
		if (x<=0) return 0;
		int i=0, l=1;
		while (l<N) l = l << 1;
		for (int len=l; len>0; len=len>>1){
			if (i+len<N && tree[i+len]<x){
				x -= tree[i+len];
				i += len;
			}
		}
		return i;
	}
};
```

## 仕様・機能
- `FenwickTree<int>` などで構築できます
  - 値のある`vector`や`(長さ, 初期値)`を指定して構築できます。

### 関数
以下は全て0-indexedです。
- `add(i, x)`： $A\lbrack i\rbrack$ に $x$ を足す。
- `set(i, x)`： $A\lbrack i\rbrack$ を $x$ にする。
- `sum(i)`： $A\lbrack 0\rbrack+A\lbrack 1\rbrack+\cdots+A\lbrack i-1\rbrack$ を返す。
- `sum(l, r)`： $A\lbrack l\rbrack+A\lbrack l+1\rbrack+\cdots+A\lbrack r-1\rbrack$ を返す。。
- `get(i)`： $A\lbrack i\rbrack$ を返す。
- `lower_bound(x)`： $A\lbrack 0\rbrack+A\lbrack 1\rbrack+\cdots+A\lbrack i\rbrack\geq x$ となる最小の $i$ を返す。

## 計算量
- 構築： $O(N)$
- `add`・`set`・`sum`・`get`・`lower_bound`： $O(\log{N})$ 

## 使用例