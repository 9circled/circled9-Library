## 概要
$\left\lfloor \frac{A}{B}\right\rfloor$ を計算するやつ。

## コード
### 必須ライブラリ
- なし

### 本体
```cpp
// https://github.com/9circled/circled9-Library
template<typename T>
T Dfloor(T A, T B){
	if (B<0) return Dfloor(-A, -B);
	if (A%B==0||A>=0) return A/B;
	else return -((-A)/B)-1;
}
```

## 仕様・機能
- `Dfloor(A, B)` で $\left\lfloor \frac{A}{B}\right\rfloor$ を計算する。

## 計算量
- 計算： $O(1)$

## 使用例
- [ABC239 B - Integer Division](https://atcoder.jp/contests/abc239/tasks/abc239_b) - [提出](https://atcoder.jp/contests/abc239/submissions/80171588)