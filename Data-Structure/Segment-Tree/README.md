## 概要
一点更新・区間クエリを $O(log N)$ でできるやつ。

## 必須ライブラリ
- `vector`

## 仕様・機能
- `SegmentTree<ST, op, e>` で構築できます

### パラメータについて
- 要素の型 (`ST`)
- 演算 (`op`) ：要素を集約する時にどのような演算を行うのか
- 単位元 (`e`) ：演算を行っても値を変化させないような値

### 関数
以下は全て0-indexedです。
- `set(i, x)`：$A\lbrack i\rbrack$ を $x$ にする
- `add(i, x)`：$A\lbrack i\rbrack$ に $x$ を足す
- `get(i)`：$A\lbrack i\rbrack$ を返す
- `query(l, r)`：区間 $\lbrack l, r\rparen$ に対する演算結果を返す
- `max_right(l, check)`：$l$ を左端として区間 $\lbrack l,x\rparen$ が条件 $check$ を満たす最大の $x$ を返す
- `min_left(r, check)`：$r$ を右端として区間 $\lbrack x, r\rparen$ が条件 $check$ を満たす最小の $x$ を返す

## 計算量
- 構築： $O(N)$
- `set`・`add`・`query`・`max_right`・`min_left`： $O(\log N)$ 
- `get`： $O(1)$

## 使用例
- [ALPC J - Segment Tree](https://atcoder.jp/contests/practice2/tasks/practice2_j) - [提出](https://atcoder.jp/contests/practice2/submissions/80044188)