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
	if (B<0) return floor(-A, -B);
	if (A%B==0) return A/B;
	if (A>=0) return (A/B);
	else return -((-A)/B)-1;
}
```

## 仕様・機能
- `Dfloor(A, B)` で $\left\lfloor \frac{A}{B}\right\rfloor$ を計算する。

## 計算量
- 計算： $O(1)$

## 使用例