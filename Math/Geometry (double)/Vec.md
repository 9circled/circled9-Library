## 概要
幾何のベクトルを表現するやつ。

## コード
### 必須ライブラリ
- `cmath`

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct Vec {
	static constexpr double eps = 1e-9;

	double x, y;
	Vec(double x=0, double y=0) : x(x), y(y) {}
	Vec& operator+=(const Vec& v) { x += v.x; y += v.y; return *this; }
	Vec& operator-=(const Vec& v) { x -= v.x; y -= v.y; return *this; }
	Vec& operator*=(double s) { x *= s; y *= s; return *this; }
	Vec& operator/=(double s) { x /= s; y /= s; return *this; }
	Vec operator+(const Vec& v) const { return Vec(*this) += v; }
	Vec operator-(const Vec& v) const { return Vec(*this) -= v; }
	Vec operator*(double s) const { return Vec(*this) *= s; }
	Vec operator/(double s) const { return Vec(*this) /= s; }
	bool operator==(const Vec& v) const { return abs(x-v.x)<eps&&abs(y-v.y)<eps; }
	bool operator!=(const Vec& v) const { return !(*this==v); }
	Vec operator-() const { return Vec(-x, -y); }

	double arg() const { return atan2(y, x); }
	double angle(const Vec& v) const { return atan2(abs(cross(v)), dot(v)); }
	double dot(const Vec& v) const { return x*v.x+y*v.y; }
	double cross(const Vec& v) const { return x*v.y-y*v.x; }
	double norm2() const { return x*x+y*y; }
	double norm() const { return sqrt(norm2()); }
	Vec normalize() const { return *this/norm(); }
	Vec rotate90(const Vec& p=Vec(0, 0)) const {
		Vec v = *this-p;
		return p + Vec(-v.y, v.x);
	}
	Vec rotate_deg(double deg, const Vec& p=Vec(0, 0)) const { return rotate_rad(deg*acos(-1.0)/180.0, p); }
	Vec rotate_rad(double rad, const Vec& p=Vec(0, 0)) const { 
		Vec v = *this-p;
		return p + Vec(v.x*cos(rad)-v.y*sin(rad), v.x*sin(rad)+v.y*cos(rad));
	}
	int orthant() const {
		if (abs(x)<eps&&abs(y)<eps) return 0;
		if (y>0) return (x>0) ? 1 : 2;
		else return (x>0) ? 4 : 3;
	}
	bool operator<(const Vec& v) const {
		int o = orthant(), vo = v.orthant();
		if (o!=vo) return o<vo;
		return cross(v)>0;
	}
	bool codir(const Vec& v) const { return abs(cross(v))<eps && dot(v)>0; }

	static Vec polar_deg(double r, double deg){ return polar_rad(r, deg*acos(-1.0)/180.0); }
	static Vec polar_rad(double r, double rad){ return Vec(r*cos(rad), r*sin(rad)); }

	friend istream& operator>>(istream& is, Vec& v) { return is>>v.x>>v.y; }
	friend ostream& operator<<(ostream& os, const Vec& v){ return os<<v.x<<" "<<v.y; }
};
```

## 仕様・機能
- `Vec v;` でベクトルを作れます。
- `Vec::polar_deg(r, deg)`で半径 $r$ 、角度 $deg$ 度のベクトルを作れます。
- `Vec::polar_rad(r, rad)`で半径 $r$ 、角度 $rad$ ラジアンのベクトルを作れます。
- `sort()`でラムダ式を定義すると偏角ソートができます。

### 関数
- `v.arg()`：ベクトル $v$ の偏角 $\theta$ を $-\pi\leq\theta\leq\pi$ の範囲で返す。
- `v.angle(w)`：ベクトル $v$ とベクトル $w$ のなす角 $\theta$ を $0\leq\theta\leq\pi$ の範囲で返す。
- `v.dot(w)`：ベクトル $v$ とベクトル $w$ の内積を返す。
- `v.cross(w)`：ベクトル $v$ とベクトル $w$ の外積を返す。
- `v.norm2()`：ベクトル $v$ と原点との長さの2乗を返す。
- `v.norm2()`：ベクトル $v$ と原点との長さを返す。
- `v.normalize()`：ベクトル $v$ を正規化したベクトルを返す。
- `v.rotate90(p)`：ベクトル $v$ を点 $p$ (初期値： $(0, 0)$ )を中心に反時計回りに90度回転させたベクトルを返す。
- `v.rotate_deg(deg, p)`：ベクトル $v$ を点 $p$ (初期値： $(0, 0)$ )を中心に反時計回りに $deg$ 度回転させたベクトルを返す。
- `v.rotate_rad(rad, p)`：ベクトル $v$ を点 $p$ (初期値： $(0, 0)$ )を中心に反時計回りに $rad$ ラジアン回転させたベクトルを返す。
- `v.orthant()`：ベクトル $v$ の属する象限を返す。
- `v.codir(w)`：ベクトル $v$ とベクトル $w$ が同じ方向を向ているかを返す。

## 計算量
- 全部： $O(1)$

## 使用例
- [ABC259 B - Counterclockwise Rotation](https://atcoder.jp/contests/abc259/tasks/abc259_b) - [提出](https://atcoder.jp/contests/abc259/submissions/80066582)