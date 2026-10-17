## 概要
ビットでTrieをつくるやつ。

## コード
### 必須ライブラリ
- `vector`
- `string`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct BinaryTrie {
	struct Node {
		int ch[2] = {-1, -1};
		int cnt = 0;
	};
	vector<Node> tree;

	BinaryTrie() { tree.emplace_back(); }

	void insert(string S){
		int v = 0;
		tree[v].cnt++;
		for (char c : S){
			int bit = c-'0';
			if (tree[v].ch[bit]==-1){
				tree[v].ch[bit] = tree.size();
				tree.emplace_back();
			}
			v = tree[v].ch[bit];
			tree[v].cnt++;
		}
	}

	int count(string S){
		int v = 0;
		for (char c : S){
			int bit = c-'0';
			if (tree[v].ch[bit]==-1) return 0;
			v = tree[v].ch[bit];
		}
		return tree[v].cnt;
	}

	bool erase(string S){
		if (count(S)==0) return false;
		int v = 0;
		tree[v].cnt--;
		for (char c : S){
			int bit = c-'0';
			v = tree[v].ch[bit];
			tree[v].cnt--;
		}
		return true;
	}

	string kth(int k){
		if (k<0||tree[0].cnt<=k) return "";
		string res;
		int v = 0;
		while (tree[v].ch[0]!=-1||tree[v].ch[1]!=-1){
			int l = tree[v].ch[0];
			int c0 = (l==-1 ? 0 : tree[l].cnt);
			if (k<c0){
				res += '0';
				v = tree[v].ch[0];
			} else {
				k -= c0;
				res += '1';
				v = tree[v].ch[1];
			}
		}
		return res;
	}

	int rankl(string S){
		int v = 0, res = 0;
		for (char c : S){
			int bit = c-'0';
			if (bit==1){
				int l = tree[v].ch[0];
				if (l!=-1) res += tree[l].cnt;
			}
			v = tree[v].ch[bit];
			if (v==-1) break;
		}
		return res;
	}

	int rankr(string S){
		return rankl(S)+count(S);
	}
};
```

## 仕様・機能
- `BinaryTrie bt;` でBinaryTrieを構築できます

### 関数
以下では文字列 $S$ は `0`・`1`でのみ構成されていて、全て同じ長さであることを想定する。

- `insert(S)`：01文字列 $S$ を追加する。
- `count(S)`：01文字列 $S$ がいくつあるかを返す。
- `erase(S)`：01文字列 $S$ を削除する。
- `kth(k)`：昇順で $k$ 番目(0-indexed)の文字列を返す。
- `rankl(S)`：文字列 $S$ が昇順で何番目の要素であるかを返す。（左側）
- `rankr(S)`：文字列 $S$ が昇順で何番目の要素であるかを返す。（右側）

## 計算量
- 全部： $O(|S|)$

## 使用例