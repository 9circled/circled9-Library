## 概要
閉区間 $\lbrack L, R\rbrack$ をsetととして管理するやつ。

## コード
### 必須ライブラリ
- `set`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct IntervalSet {
	set<pair<long long, long long>> s;
	long long len = 0, offset = 0;

	IntervalSet(bool merge=true){ offset=(merge) ? 1 : 0; }
	
	long long insert(long long l, long long r){
		long long bef = len;
		if (l>r) return 0;
		auto itr = s.lower_bound({l, -2e18});
		if (itr!=s.begin()){
			itr--;
			if (itr->second < l-offset) itr++;
		}
		long long nl = l, nr = r;
		while (itr!=s.end()){
			if (itr->first > r+offset) break;
			nl = min(nl, itr->first);
			nr = max(nr, itr->second);
			len -= itr->second-itr->first+1;
			itr = s.erase(itr);
		}
		len += nr-nl+1;
		s.insert({nl, nr});
		return len-bef;
	}

	long long remove(long long l, long long r){
		long long bef = len;
		if (l>r) return 0;
		auto itr = s.lower_bound({l, -2e18});
		if (itr!=s.begin()){
			itr--;
			if (itr->second < l) itr++;
		}
		while (itr!=s.end()){
			if (itr->first > r) break;
			long long cl = itr->first, cr = itr->second;
			len -= cr-cl+1;
			itr = s.erase(itr);
			if (cl<l){
				len += (l-1)-cl+1;
				s.insert({cl, l-1});
			}
			if (r<cr){
				len += cr-(r+1)+1;
				s.insert({r+1, cr});
			}
		}
		return bef-len;
	}

	bool contain(long long x){
		if (s.empty()) return false;
		auto itr = s.lower_bound({x+1, -2e18});
		if (itr==s.begin()) return false;	
		itr--;
		return x <= itr->second;
	}

	bool contain(long long l, long long r){
		if (l>r) return true;
		if (s.empty()) return false;
		auto itr = s.lower_bound({l+1, -2e18});
		if (itr==s.begin()) return false;	
		itr--;
		return itr->first <= l && r <= itr->second;
	}	

	long long length(){ return len; }

	int size(){ return s.size(); }

	set<pair<long long, long long>>& get(){ return s; }
};
```

## 仕様・機能
- `IntervalSet st` でInterval-Setを構築できます
- 作成時`st(false)` とすると隣接要素のマージを消せます。
  - 何も指定しないと $\lbrack A, B\rbrack$ $\lbrack B+1, C\rbrack$ は $\lbrack A, C\rbrack$ になります。

### 関数
- `insert(L, R)`：区間 $\lbrack L, R\rbrack$ を追加します。返り値は追加した合計の長さを返します。
- `remove(L, R)`：区間 $\lbrack L, R\rbrack$ を削除します。返り値は削除した合計の長さを返します。
- `contain(x)`： $x$ が含まれているかを返します。
- `contain(L, R)`：区間 $\lbrack L, R\rbrack$ が含まれているかを返します。
- `length()`：追加された全区間の覆う長さの合計を返します。
- `size()`：区間の数を返します。
- `get()`：対応する区間のsetそのものを返します。

## 計算量
- `insert`・`remove`：償却 $O(\log{N})$
- `contain`： $O(\log{N})$
- `length`・`size`・`get`： $O(1)$

## 使用例
- [ABC256 D - Union of Interval](https://atcoder.jp/contests/abc256/tasks/abc256_d) - [提出](https://atcoder.jp/contests/abc256/submissions/80046152)
- [ABC435 E - Cover query](https://atcoder.jp/contests/abc435/tasks/abc435_e) - [提出](https://atcoder.jp/contests/abc435/submissions/80046385)