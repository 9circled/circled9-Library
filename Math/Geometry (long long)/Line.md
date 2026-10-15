## 概要
幾何の直線を表現するやつ。

## コード
### 必須ライブラリ
- [Vec](./Vec.md)

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct Line {
	Vec s, t;
	Line(Vec s=Vec(0, 0), Vec t=Vec(0, 0)) : s(s), t(t) {}
	Line(long long sx, long long sy, long long tx, long long ty) : s(Vec(sx, sy)), t(Vec(tx, ty)) {}
	Line& operator+=(const Vec& v) { s += v; t += v; return *this; }
	Line& operator-=(const Vec& v) { s -= v; t -= v; return *this; }
	Line operator+(const Vec& v) const { return Line(*this) += v; }
	Line operator-(const Vec& v) const { return Line(*this) -= v; }
	Line operator-() const { return Line(-s, -t); }

	Vec dir() const { return t-s; }
	Line rev() const { return Line(t, s); }
	Line rotate90() const { return Line(s.rotate90(), t.rotate90()); }
	int ccw(Vec p) const {
		Vec b = t-s, c = p-s;
		if (b.cross(c)>0) return 1; // counter-clockwise
		if (b.cross(c)<0) return -1; // clockwise
		if (b.dot(c)<0) return 2; // p s--t
		if (b.norm2()<c.norm2()) return -2; // s--t p
		return 0; // s- p -t
	}
	bool isParallel(const Line& l) const { return dir().cross(l.dir())==0; }
	bool isOrthogonal(const Line& l) const { return dir().dot(l.dir())==0; }
	bool intersectSS(const Line& l) const { return (ccw(l.s)*ccw(l.t)<=0)&&(l.ccw(s)*l.ccw(t)<=0); }

	friend istream& operator>>(istream& is, Line& l) { return is>>l.s>>l.t; }
	friend ostream& operator<<(ostream& os, const Line& l) { return os<<l.s<<" "<<l.t; }
};
```

## 仕様・機能
- `Line l;` で直線を作れます。
  - 始点のベクトル $s$ と終点のベクトル $t$ で直線を定義します。

### 関数
- `l.dir()`：線分 $l$ の方向ベクトルを返します。
- `l.rev()`：始点 $s$ と終点 $t$ を逆にします。
- `l.rotate90()`：線分 $l$ を原点中心に反時計回りに90度回転させたベクトルを返します。
- `l.ccw(p)`：線分 $l$ と点 $p$ のccwを返します。詳しくはコメントアウトに記載。
- `l.isParallel(m)`：線分 $l$ と線分 $m$ が平行であるかを返します。
- `l.isOrthogonal(m)`：線分 $l$ と線分 $m$ が平行であるかを返します。
- `l.intersectSS(m)`：線分 $l$ と線分 $m$ が交わるかを返します。

## 計算量
- 全部： $O(1)$

## 使用例