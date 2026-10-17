## 概要
$\left\lceil \frac{A}{B}\right\rceil$ を計算するやつ。

## コード
### 必須ライブラリ
- なし

### 本体
```cpp
// https://github.com/9circled/circled9-Library
template<typename T>
T Dceil(T A, T B){
	if (B<0) return ceil(-A, -B);
	if (A%B==0) return A/B;
	if (A>=0) return (A/B)+1;
	else return -((-A)/B);
}
```

## 仕様・機能
- `Dceil(A, B)` で $\left\lceil \frac{A}{B}\right\rceil$ を計算する。

## 計算量
- 計算： $O(1)$

## 使用例