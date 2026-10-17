## 概要
文字列のオートマトンをつくるやつ。

## コード
### 必須ライブラリ
- `vector`
- `map`
- `string`
- `queue`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct AhoCorasick {
	struct Node {
		map<char, int> ch;
		int cnt = 0;
		int fail = -1;
	};
	vector<Node> tree;
	vector<int> vs, id;

	AhoCorasick() { tree.emplace_back(); }

	int operator()(int v, char c) const {
		while (v!=-1){
			auto it = tree[v].ch.find(c);
			if (it!=tree[v].ch.end()) return it->second;
			v = tree[v].fail;
		}
		return 0;
	}

	int operator[](int v) const { return tree[v].cnt; }

	int insert(string S){
		int v = 0;
		for (char c : S){
			if (!tree[v].ch.count(c)){
				tree[v].ch[c] = tree.size();
				tree.emplace_back();
			}
			v = tree[v].ch[c];
		}
		id.push_back(v);
		tree[v].cnt++;
		return v;
	}

	void build(){
		queue<int> que;
		que.push(0);
		while (que.size()){
			int v = que.front(); que.pop();
			vs.emplace_back(v);
			for (auto [c, nv] : tree[v].ch){
				tree[nv].fail = (*this)(tree[v].fail, c);
				tree[nv].cnt += tree[tree[nv].fail].cnt;
				que.push(nv);
			}
		}
	}
	
	vector<long long> match(string S){
		vector<long long> cnt(tree.size(), 0);
		int v = 0;
		for (char c : S){
			v = (*this)(v, c);
			cnt[v]++;
		}
		for (int i=vs.size()-1; i>=0; i--){
			int v = vs[i];
			if (tree[v].fail!=-1) cnt[tree[v].fail] += cnt[v];
		}
		vector<long long> res(id.size());
		for (int i=0; i<id.size(); i++) res[i] = cnt[id[i]];
		return res;
	}
};
```

## 仕様・機能
- `AhoCorasick aho;` で初期化できます。
- `aho(v, c)`は頂点 $v$ にいるときに文字 $c$ を受け取ると進む次の頂点を返します。
- `aho[v]` は頂点 $v$ がいくつのパターンに合致しているかを返します。

### 関数
- `insert(S)`：検索する文字列 $S$ を追加します。
- `build()`：failノードを構築します。
- `match(T)`：検索対象の文字列 $T$ で検索を実行します。
  - 返り値は検索する文字列 $S$ が何回登場したかをvectorで返します。 

## 計算量
- `aho(v, c)`：償却 $O(1)$
- `aho[v]`： $O(1)$
- `insert(S)`： $O(|S|)$
- `build()`： $O(\Sigma|S|)$
- `match(T)`： $O(\Sigma|S|+|T|)$

- 全部： $O(|S|)$

## 使用例