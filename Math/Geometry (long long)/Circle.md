## 概要
幾何の円を表現するやつ。

## コード
### 必須ライブラリ
- [`Vec`](./Vec.md)

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct Circle {
	Vec c; long long r;
	Circle(Vec c = Vec(0, 0), long long r = 0.0) : c(c), r(r) {}
	Circle(long long x, long long y, long long r) : c(Vec(x, y)), r(r) {}

	int contain(const Vec& p) const {
		long long d2 = (p-c).norm2();
		if (d2<r*r) return 2; // in
		if (d2==r*r) return 1; // on-edge
		return 0; // out
	}
	int intersect(const Circle& c2) const {
		long long d2 = (c-c2.c).norm2();
		long long ra2 = (r+c2.r)*(r+c2.r), rs2 = (r-c2.r)*(r-c2.r);
		if (d2>ra2) return 4; // apart
		if (d2==ra2) return 3; // out-touch
		if (rs2<d2&&d2<ra2) return 2; // cross
		if (d2==rs2) return 1; // in-touch
		return 0; // inside
	}

	friend istream& operator>>(istream& is, Circle& cr){ return is >>cr.c>>cr.r; }
	friend ostream& operator<<(ostream& os, const Circle& cr){ return os<<cr.c<<" "<<cr.r; }
};
```

## 仕様・機能
- `Circle c;` で円を作れます。
  - 中心を表すベクトル $c$ 、半径 $r$ の順番で定義されています。

### 関数
- `c.contain(p)`：円 $c$ が点 $p$ を含むかを返します。詳しくはコメントアウトに記載。
- `c.intersect(d)`：円 $c$ と円 $d$ の共通接線の数を返します。詳しくはコメントアウトに記載。

## 計算量
- 全部： $O(1)$

## 使用例