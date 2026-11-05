## 概要
区間更新・区間クエリを $O(\log{N})$ でできるやつ。

## コード
### 必須ライブラリ
- `vector`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
template <typename M>
struct LazySegmentTree {
private:
	using T = typename M::T;
	using F = typename M::F;
	static T op(T a, T b){ return M::op(a, b); }
	static T e(){ return M::e(); }
	static T act(T x, F f, int w){ return M::act(x, f, w); }
	static F comp(F f, F g){ return M::comp(f, g); }
	static F id(){ return M::id(); }

	int n, N = 1;
	vector<T> tree;
	vector<F> lazy;

	void _push(int k, int w){
		if (lazy[k]==id()) return;
		int l = 2*k, r = 2*k+1, w2 = w/2;
		tree[l] = act(tree[l], lazy[k], w2);
		lazy[l] = comp(lazy[k], lazy[l]);
		tree[r] = act(tree[r], lazy[k], w2);
		lazy[r] = comp(lazy[k], lazy[r]);
		lazy[k] = id();
	}

	void _set(int i, T x, int k, int l, int r){
		if (r-l==1){
			tree[k] = x;
			lazy[k] = id();
			return;
		}
		_push(k, r-l);
		int m = (l+r)/2;
		if (i<m) _set(i, x, 2*k, l, m);
		else _set(i, x, 2*k+1, m, r);
		tree[k] = op(tree[2*k], tree[2*k+1]);
	}

	T _get(int i, int k, int l, int r){
		if (r-l==1) return tree[k];
		_push(k, r-l);
		int m = (l+r)/2;
		if (i<m) return _get(i, 2*k, l, m);
		else return _get(i, 2*k+1, m, r);
	}

	void _apply(int a, int b, F f, int k, int l, int r){
		if (r<=a||b<=l) return;
		if (a<=l&&r<=b){
			tree[k] = act(tree[k], f, r-l);
			lazy[k] = comp(f, lazy[k]);
			return;
		}
		_push(k, r-l);
		int m = (l+r)/2;
		_apply(a, b, f, 2*k, l, m);
		_apply(a, b, f, 2*k+1, m, r);
		tree[k] = op(tree[2*k], tree[2*k+1]);
	}

	T _query(int a, int b, int k, int l, int r){
		if (r<=a||b<=l) return e();
		if (a<=l&&r<=b) return tree[k];
		_push(k, r-l);
		int m = (l+r)/2;
		return op(_query(a, b, 2*k, l, m), _query(a, b, 2*k+1, m, r));
	}

	template <typename C>
	int _max_right(int a, C& check, T& sm, int k, int l, int r){
		if (r<=a) return n;
		if (a<=l){
			if (check(op(sm, tree[k]))){
				sm = op(sm, tree[k]);
				return n;
			}
			if (r-l==1) return l;
		}
		_push(k, r-l);
		int m = (l+r)/2;
		int li = _max_right(a, check, sm, 2*k, l, m);
		if (li!=n) return li;
		return _max_right(a, check, sm, 2*k+1, m, r);
	}

	template <typename C>
	int _min_left(int b, C& check, T& sm, int k, int l, int r){
		if (b<=l) return 0;
		if (r<=b){
			if (check(op(tree[k], sm))){
				sm = op(tree[k], sm);
				return 0;
			}
			if (r-l==1) return r;
		}
		_push(k, r-l);
		int m = (l+r)/2;
		int ri = _min_left(b, check, sm, 2*k+1, m, r);
		if (ri!=0) return ri;
		return _min_left(b, check, sm, 2*k, l, m);
	}

public:
	LazySegmentTree(int n, T v=e()) : n(n){
		while (N<n) N *= 2;
		tree = vector<T>(2*N, e());
		lazy = vector<F>(2*N, id());
		for (int i=0; i<n; i++) tree[i+N] = v;
		for (int i=N-1; i>0; i--) tree[i] = op(tree[2*i], tree[2*i+1]);
	}

	LazySegmentTree(const vector<T>& A) : n(A.size()){
		while (N<n) N *= 2;
		tree = vector<T>(2*N, e());
		lazy = vector<F>(2*N, id());
		for (int i=0; i<n; i++) tree[i+N] = A[i];
		for (int i=N-1; i>0; i--) tree[i] = op(tree[2*i], tree[2*i+1]);
	}

	void set(int i, T x){ _set(i, x, 1, 0, N); }

	T get(int i){ return _get(i, 1, 0, N); }

	void apply(int l, int r, F f){ _apply(l, r, f, 1, 0, N); }

	T query(int l, int r){ return _query(l, r, 1, 0, N); }

	template <typename C>
	int max_right(int l, C check){
		if (l==n) return n;
		T sm = e();
		return min(_max_right(l, check, sm, 1, 0, N), n);
	}

	template <typename C>
	int min_left(int r, C check){
		if (r==0) return 0;
		T sm = e();
		return _min_left(r, check, sm, 1, 0, N);
	}
};

struct Monoid {
	using T = /* */;
	using F = /* */;
	static T op(T l, T r){ return /* */; }
	static T e(){ return /* */; }
	static T act(T x, F f, int w){ return /* */; }
	static F comp(F f, F g){ return /* */; }
	static F id(){ return /* */; }
};
```

## 仕様・機能
- `LazySegmentTree<モノイドの構造体名>` で構築できます
  - コードそのままだと`LazySegmentTree<Monoid>`

### モノイドの構造体について
- 要素の型 (`LT`)
- 要素の演算 (`op`) ：要素を集約する時にどのような演算を行うのか
- 要素の単位元 (`e`) ：演算を行っても値を変化させないような値
- 作用の型 (`LF`)
- 作用の適応 (`act`) ：要素を適応させるときにどのようなことを行うのか
- 作用の合成 (`comp`) ：作用を合成した時にどのようになるのか
- 作用の単位元 (`id`) ：合成しても変わらないような作用

例：非負整数long long型区間加算区間最小値
```cpp
struct MIN {
	using T = long long;
	using F = long long;
	static T op(T l, T r){ return min(l, r); }
	static T e(){ return 1e18; }
	static T act(T x, F f, int w){ return x+f; }
	static F comp(F f, F g){ return f+g; }
	static F id(){ return 0; }
};
// LazySegmentTree<MIN>
```

### 関数
以下は全て0-indexedです。
- `set(i, x)`： $A\lbrack i\rbrack$ を $x$ にする
- `get(i)`： $A\lbrack i\rbrack$ を返す
- `apply(l, r, f)`： 区間 $\lbrack l, r\rparen$ に対して $f$ を作用させる
- `query(l, r)`：区間 $\lbrack l, r\rparen$ に対する演算結果を返す
- `max_right(l, check)`： $l$ を左端として区間 $\lbrack l,x\rparen$ が条件 $check$ を満たす最大の $x$ を返す
  - $check$ はラムダ式で定義する
  - `[&](int val){ return /*判定式*/; }` の形
  - $val$ は区間の合成値を表す。
- `min_left(r, check)`：$r$ を右端として区間 $\lbrack x, r\rparen$ が条件 $check$ を満たす最小の $x$ を返す
  - $check$ は↑のと同じ

## 計算量
- 構築： $O(N)$
- `set`・`get`・`apply`・`query`・`max_right`・`min_left`： $O(\log{N})$ 

## 使用例
- [AALC001 B - 遅延セグメント木](https://atcoder.jp/contests/aalc001/tasks/aalc001_b) - [提出](https://atcoder.jp/contests/aalc001/submissions/80608099)