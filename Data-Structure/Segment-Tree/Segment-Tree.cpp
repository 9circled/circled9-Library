// https://github.com/9circled/circled9-Library
template <typename T, auto op, auto e>
struct SegmentTree {
private:
	int n, N = 1;
	vector<T> tree;

	void _set(int i, T x, int k, int l, int r){
		if (r-l==1){
			tree[k] = x;
			return;
		}
		int m = (l+r)/2;
		if (i<m) _set(i, x, 2*k, l, m);
		else _set(i, x, 2*k+1, m, r);
		tree[k] = op(tree[2*k], tree[2*k+1]);
	}

	void _add(int i, T x, int k, int l, int r){
		if (r-l==1){
			tree[k] = tree[k] + x;
			return;
		}
		int m = (l+r)/2;
		if (i<m) _add(i, x, 2*k, l, m);
		else _add(i, x, 2*k+1, m, r);
		tree[k] = op(tree[2*k], tree[2*k+1]);
	}

	T _query(int a, int b, int k, int l, int r){
		if (r<=a||b<=l) return e();
		if (a<=l&&r<=b) return tree[k];
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
		int m = (l+r)/2;
		int ri = _min_left(b, check, sm, 2*k+1, m, r);
		if (ri!=0) return ri;
		return _min_left(b, check, sm, 2*k, l, m);
	}

public:
	SegmentTree(int n, T v=e()) : n(n){
		while (N<n) N *= 2;
		tree = vector<T>(2*N, e());
		for (int i=0; i<n; i++) tree[i+N] = v;
		for (int i=N-1; i>0; i--) tree[i] = op(tree[2*i], tree[2*i+1]);
	}

	SegmentTree(const vector<T>& A) : n(A.size()){
		while (N<A.size()) N *= 2;
		tree = vector<T>(2*N, e());
		for (int i=0; i<A.size(); i++) tree[i+N] = A[i];
		for (int i=N-1; i>0; i--) tree[i] = op(tree[2*i], tree[2*i+1]);
	}

	void set(int i, T x){ _set(i, x, 1, 0, N); }

	void add(int i, T x){ _add(i, x, 1, 0, N); }

	T get(int i){ return tree[i+N]; }

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
// using ST = 
// ST op(ST l, ST r){ return; };
// ST e(){ return; };