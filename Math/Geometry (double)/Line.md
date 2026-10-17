## 概要
幾何の直線を表現するやつ。

## コード
### 必須ライブラリ
- `cmath`
- [`Vec`](./Vec.md)

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct Line {
	static constexpr double eps = 1e-9;

	Vec s, t;
	Line(Vec s=Vec(0, 0), Vec t=Vec(0, 0)) : s(s), t(t) {}
	Line(double sx, double sy, double tx, double ty) : s(Vec(sx, sy)), t(Vec(tx, ty)) {}
	Line& operator+=(const Vec& v) { s += v; t += v; return *this; }
	Line& operator-=(const Vec& v) { s -= v; t -= v; return *this; }
	Line operator+(const Vec& v) const { return Line(*this) += v; }
	Line operator-(const Vec& v) const { return Line(*this) -= v; }
	Line operator-() const { return Line(-s, -t); }

	Vec dir() const { return t-s; }
	double norm() const { return dir().norm(); }
	Vec normalize() const { return dir().normalize(); }
	Vec div(double p) const { return s*(1-p)+t*p; }
	Line rev() const { return Line(t, s); }
	Line rotate90(const Vec& p=Vec(0, 0)) const { return Line(s.rotate90(p), t.rotate90(p)); }
	Line rotate_deg(double deg, const Vec& p=Vec(0, 0)) const { return Line(s.rotate_deg(deg, p), t.rotate_deg(deg, p)); }
	Line rotate_rad(double rad, const Vec& p=Vec(0, 0)) const { return Line(s.rotate_rad(rad, p), t.rotate_rad(rad, p)); }
	Line shift(double d) const {
		Vec n = dir().rotate90().normalize()*d;
		return Line(s+n, t+n);
	}
	double distSP(Vec p) const {
		if ((p-s).dot(t-s)<eps) return (s-p).norm();
		if ((p-t).dot(s-t)<eps) return (t-p).norm();
		return abs(dir().cross(p-s)/norm());
	}
	double distLP(Vec p) const { return abs(dir().cross(p-s)/norm()); }
	Vec projection(Vec p) const {
		Vec d = dir();
		double r = (p-s).dot(d) / d.norm2();
		return s+d*r;
	}
	Vec reflect(Vec p) const { return projection(p)*2-p; }
	int ccw(Vec p) const {
		Vec b = t-s, c = p-s;
		if (b.cross(c)>eps) return 1; // counter-clockwise
		if (b.cross(c)<-eps) return -1; // clockwise
		if (b.dot(c)<-eps) return 2; // p s--t
		if (b.norm2()<c.norm2()) return -2; // s--t p
		return 0; // s- p -t
	}
	bool isParallel(const Line& l) const { return abs(dir().cross(l.dir()))<eps; }
	bool isOrthogonal(const Line& l) const { return abs(dir().dot(l.dir()))<eps; }
	Vec crosspointLL(const Line& l) const {
		double A = dir().cross(l.dir()), B = (l.s-s).cross(dir());
		if (abs(A)<eps&&abs(B)<eps) return l.s;
		return l.s+l.dir()*(B/A);
	}
	bool intersectSS(const Line& l) const { return (ccw(l.s)*ccw(l.t)<=0)&&(l.ccw(s)*l.ccw(t)<=0); }
	double distSS(const Line& l) const {
		if (intersectSS(l)) return 0.0;
		return min(distSP(l.s), min(distSP(l.t), min(l.distSP(s), l.distSP(t))));
	}

	friend istream& operator>>(istream& is, Line& l) { return is>>l.s>>l.t; }
	friend ostream& operator<<(ostream& os, const Line& l) { return os<<l.s<<" "<<l.t;}
};
```

## 仕様・機能
- `Line l;` で直線を作れます。
  - 始点のベクトル $s$ と終点のベクトル $t$ で直線を定義します。

### 関数
- `l.dir()`：線分 $l$ の方向ベクトルを返します。
- `l.norm()`：線分 $l$ の長さを返します。
- `l.normalize()`：線分 $l$ の方向ベクトルを正規化したものを返します。
- `l.div(p)`：線分 $l$ について始点・終点を $p:(1-p)$ の比率で分割したベクトルを返します。
- `l.rev()`：始点 $s$ と終点 $t$ を逆にします。
- `l.rotate90(p)`：線分 $l$ を点 $p$ (初期値： $(0, 0)$ )を中心に反時計回りに90度回転させたベクトルを返す。
- `l.rotate_deg(deg, p)`：線分 $l$ を点 $p$ (初期値： $(0, 0)$ )を中心に反時計回りに $deg$ 度回転させたベクトルを返す。
- `l.rotate_rad(rad, p)`：線分 $l$ を点 $p$ (初期値： $(0, 0)$ )を中心に反時計回りに $rad$ ラジアン回転させたベクトルを返す。
- `l.shift(d)`：線分 $l$ を進行方向に対して左方向に $d$ だけ水平にずらします。
- `l.distSP(p)`：線分 $l$ と点 $p$ の距離を返します。
- `l.distLP(p)`：直線 $l$ と点 $p$ の距離を返します。
- `l.projection(p)`：直線 $l$ と点 $p$ を通る $l$ との垂線の交点を返します。
- `l.reflect(p)`：直線 $l$ を対称軸として、点 $p$ と点対称の位置にある点を返します。
- `l.ccw(p)`：線分 $l$ と点 $p$ のccwを返します。詳しくはコメントアウトに記載。
- `l.isParallel(m)`：線分 $l$ と線分 $m$ が平行であるかを返します。
- `l.isOrthogonal(m)`：線分 $l$ と線分 $m$ が平行であるかを返します。
- `l.crosspintLL(m)`：直線 $l$ と直線 $m$ の交点を返します。（平行だと`nan inf`とか返ってきます）
- `l.intersectSS(m)`：線分 $l$ と線分 $m$ が交わるかを返します。
- `l.distSS(m)`：線分 $l$ と線分 $m$ の距離を返します。

## 計算量
- 全部： $O(1)$

## 使用例