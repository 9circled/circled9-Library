## 概要
$\lfloor\sqrt{N}\rfloor$ を計算するやつ。

## コード
### 必須ライブラリ
- `cmath`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
template<typename T>
long long isqrt(long long N){
	if (N==0) return 0;
	long long n = sqrt(N)-1;
	if (n*(n+2)<N) return n+1;
	else return n;
}
```

## 仕様・機能
- `isqrt(N)` で $\lfloor\sqrt{N}\rfloor$ を計算する。

## 計算量
- 計算： $O(1)$

## 使用例