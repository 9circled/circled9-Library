## 概要
幾何のベクトルを表現するやつ。

## コード
### 必須ライブラリ
- なし

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct Vec {
	long long x, y;
	Vec(long long x=0, long long y=0) : x(x), y(y) {}
	Vec& operator+=(const Vec& v) { x += v.x; y += v.y; return *this; }
	Vec& operator-=(const Vec& v) { x -= v.x; y -= v.y; return *this; }
	Vec& operator*=(long long s) { x *= s; y *= s; return *this; }
	Vec& operator/=(long long s) { x /= s; y /= s; return *this; }
	Vec operator+(const Vec& v) const { return Vec(*this) += v; }
	Vec operator-(const Vec& v) const { return Vec(*this) -= v; }
	Vec operator*(long long s) const { return Vec(*this) *= s; }
	Vec operator/(long long s) const { return Vec(*this) /= s; }
	Vec operator-() const { return Vec(-x, -y); }
	bool operator==(const Vec& v) const { return x==v.x && y==v.y; }
	bool operator!=(const Vec& v) const { return !(*this==v); }

	long long dot(const Vec& v) const { return x*v.x+y*v.y; }
	long long cross(const Vec& v) const { return x*v.y-y*v.x; }
	long long norm2() const { return x*x+y*y; }
	Vec rotate90() const { return Vec(-y, x); }
	int orthant() const {
		if (x==0&&y==0) return 0;
		if (y>0) return (x>0) ? 1 : 2;
		else return (x>0) ? 4 : 3;
	}
	bool operator<(const Vec& v) const {
		int o = orthant(), vo = v.orthant();
		if (o!=vo) return o<vo;
		return cross(v)>0;
	}
	bool codir(const Vec& v) const { return cross(v)==0 && dot(v)>0; }

	friend istream& operator>>(istream& is, Vec& v) { return is>>v.x>>v.y; }
	friend ostream& operator<<(ostream& os, const Vec& v){ return os<<v.x<<" "<<v.y; }
};
```

## 仕様・機能
- `Vec v;` でベクトルを作れます。
- `sort()`でラムダ式を定義すると偏角ソートができます。

### 関数。
- `v.dot(w)`：ベクトル $v$ とベクトル $w$ の内積を返す。
- `v.cross(w)`：ベクトル $v$ とベクトル $w$ の外積を返す。
- `v.norm2()`：ベクトル $v$ と原点との長さの2乗を返す。
- `v.rotate90(p)`：ベクトル $v$ を原点を中心に反時計回りに90度回転させたベクトルを返す。
- `v.orthant()`：ベクトル $v$ の属する象限を返す。
- `v.codir(w)`：ベクトル $v$ とベクトル $w$ が同じ方向を向ているかを返す。

## 計算量
- 全部： $O(1)$

## 使用例
- [ABC442 E - Laser Takahashi](https://atcoder.jp/contests/abc442/tasks/abc442_e) - [提出](https://atcoder.jp/contests/abc442/submissions/80066669)