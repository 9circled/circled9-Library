## 概要
1文字1文字を頂点とする木のやつ。

## コード
### 必須ライブラリ
- `vector`
- `map`
- `string`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct Trie {
	struct Node {
		map<char, int> ch;
		int end = 0;
		int cnt = 0;
	};
	vector<Node> tree;

	Trie() { tree.emplace_back(); }

	void insert(string S){
		int v = 0;
		tree[v].cnt++;
		for (char c : S){
			if (!tree[v].ch.count(c)){
				tree[v].ch[c] = tree.size();
				tree.emplace_back();
			}
			v = tree[v].ch[c];
			tree[v].cnt++;
		}
		tree[v].end++;
	}

	int count(string S){
		int v = 0;
		for (char c : S){
			if (!tree[v].ch.count(c)) return 0;
			v = tree[v].ch[c];
		}
		return tree[v].end;
	}

	bool contain(string S){
		return count(S)>0;
	}

	int prefix(string S){
		int v = 0;
		for (char c : S){
			if (!tree[v].ch.count(c)) return 0;
			v = tree[v].ch[c];
		}
		return tree[v].cnt;
	}

	bool erase(string S){
		if (count(S)==0) return false;
		int v = 0;
		tree[v].cnt--;
		for (char c : S){
			v = tree[v].ch[c];
			tree[v].cnt--;
		}
		tree[v].end--;
		return true;
	}

	string kth(int k){
		if (k<0||tree[0].cnt<=k) return "";
		int v = 0;
		string res;
		while (1){
			if (k<tree[v].end) return res;
			k -= tree[v].end;
			for (auto [c, nv] : tree[v].ch){
				if (k<tree[nv].cnt){
					res += c;
					v = nv;
					break;
				}
				k -= tree[nv].cnt;
			}
		}
		return res;
	}
	
	int rankl(string S){
		int v = 0, res = 0;
		for (char c : S){
			res += tree[v].end;
			for (auto [nc, nv] : tree[v].ch){
				if (nc<c){
					res += tree[nv].cnt;
				} else {
					break;
				}
			}
			if (!tree[v].ch.count(c)) return res;
			v = tree[v].ch[c];
		}
		return res;
	}

	int rankr(string S){
		int v = 0, res = 0;
		for (char c : S){
			res += tree[v].end;
			for (auto [nc, nv] : tree[v].ch){
				if (nc<c){
					res += tree[nv].cnt;
				} else {
					break;
				}
			}
			if (!tree[v].ch.count(c)) return res;
			v = tree[v].ch[c];
		}
		res += tree[v].end;
		return res;
	}

	int lcp(string S){
		int v = 0, res = 0;
		for (char c : S){
			if (!tree[v].ch.count(c)) break;
			int nv = tree[v].ch[c];
			if (tree[nv].cnt==0) break;
			v = nv;
			res++;
		}
		return res;
	}
};
```

## 仕様・機能
- `Trie tr;` でTrieを構築できます

### 関数
- `insert(S)`：文字列 $S$ を追加する。
- `count(S)`：文字列 $S$ がいくつあるかを返す。
- `contain(S)`：文字列 $S$ が存在するかを返す。
- `prefix(S)`：文字列 $S$ を接頭辞に持つ文字列がいくつあるかを返す。
- `erase(S)`：文字列 $S$ を削除する。
- `kth(k)`：昇順で $k$ 番目(0-indexed)の文字列を返す。
- `rankl(S)`：文字列 $S$ が昇順で何番目の要素であるかを返す。（左側）
- `rankr(S)`：文字列 $S$ が昇順で何番目の要素であるかを返す。（右側）
- `lcp(S)`：文字列 $S$ とTrie上に存在している文字列の最長共通接頭辞(LCP)を求める。

## 計算量
- 全部： $O(|S|)$

## 使用例
- [ABC287 E - Karuta](https://atcoder.jp/contests/abc287/tasks/abc287_e) - [提出](https://atcoder.jp/contests/abc287/submissions/80046681)