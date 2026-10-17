## 概要
幾何の円を表現するやつ。

## コード
### 必須ライブラリ
- `algorithm`
- `cmath`
- [`Vec`](./Vec.md)
- [`Line`](./Line.md)
- [`Polygon`](./Polygon.md)

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct Circle {
	static constexpr double eps = 1e-9;

	Vec c; double r;
	Circle(Vec c = Vec(0, 0), double r = 0.0) : c(c), r(r) {}
	Circle(double x, double y, double r) : c(Vec(x, y)), r(r) {}

	int contain(const Vec& p) const {
		double d = (p-c).norm();
		if (d<r-eps) return 2; // in
		if (abs(d-r)<eps) return 1; // on-edge
		return 0; // out
	}
	int intersect(const Circle& c2) const {
		double d = (c-c2.c).norm();
		if (d>r+c2.r+eps) return 4; // apart
		if (abs(d-(r+c2.r))<eps) return 3; // out-touch
		if (d>abs(r-c2.r)+eps) return 2; // cross
		if (abs(d-abs(r-c2.r))<eps) return 1; // in-touch
		return 0; // inside
	}
	vector<Vec> crosspoint(const Line& l) const {
		Vec p = l.projection(c);
		double d = (p-c).norm();
		if (d>r+eps) return {};
		if (abs(d-r)<eps) return {p};
		double len = sqrt(max(0.0, r*r-d*d));
		Vec dir = l.normalize()*len;
		return {p-dir, p+dir};
	}
	vector<Vec> crosspoint(const Circle& c2) const {
		int rel = intersect(c2);
		if (rel==0||rel==4) return {};
		double d = (c-c2.c).norm();
		double a = acos(max(-1.0, min(1.0, (r*r+d*d-c2.r*c2.r)/(2*r*d))));
		double t = (c2.c-c).arg();
		if (rel==1||rel==3) return {c+Vec::polar_rad(r, t)};
		return {c+Vec::polar_rad(r, t+a), c+Vec::polar_rad(r, t-a)};
	}
	vector<Vec> tangent(const Vec& p) const {
		double d = (p-c).norm();
		if (d<r-eps) return {};
		if (abs(d-r)<eps) return {p};
		double a = acos(max(-1.0, min(1.0, r/d)));
		double t = (p-c).arg();
		return {c+Vec::polar_rad(r, t+a), c+Vec::polar_rad(r, t-a)};
	}
	vector<Line> tangent(const Circle& c2) const {
		vector<Line> res;
		double d = (c2.c-c).norm();
		if (d<eps) return res;
		double t = (c2.c-c).arg();
		auto add = [&](double a, double r2){
			Vec p1 = c+Vec::polar_rad(r, t+a), p2 = c2.c+Vec::polar_rad(r2, t+a);
			if ((p1-p2).norm()<eps) res.push_back(Line(p1, p1+(p1-c).rotate90()));
			else res.push_back(Line(p1, p2));
		};
		double diff = r-c2.r;
		if (d>abs(diff)+eps){
			double a = acos(diff/d);
			add(a, c2.r); add(-a, c2.r);
		} else if (abs(d-abs(diff))<eps){
			double a = acos(max(-1.0, min(1.0, diff/d)));
			add(a, c2.r);
		}
		double sum = r+c2.r;
		if (d>sum+eps){
			double a = acos(sum/d);
			add(a, -c2.r); add(-a, -c2.r);
		} else if (abs(d-sum)<eps){
			add(0.0, -c2.r);
		}
		return res;
	}
	double intersect_area(const Circle& c2) const {
		double d = (c-c2.c).norm();
		if (d>=r+c2.r-eps) return 0.0;
		if (d<=abs(r-c2.r)+eps) return acos(-1.0)*min(r, c2.r)*min(r, c2.r);
		double a1 = acos(max(-1.0, min(1.0, (r*r+d*d-c2.r*c2.r)/(2*r*d))));
		double a2 = acos(max(-1.0, min(1.0, (c2.r*c2.r+d*d-r*r)/(2*c2.r*d))));
		return r*r*a1+c2.r*c2.r*a2-r*d*sin(a1);
	}
	double intersect_area(const Polygon& p) const {
		double res = 0.0;
		int N = p.size();
		for (int i=0; i<N; i++){
			Vec a = p[i]-c, b = p[(i+1)%N]-c;
			Circle o(Vec(0, 0), r);
			vector<Vec> cro = o.crosspoint(Line(a, b));
			vector<Vec> pts = {a};
			for (const Vec& pt : cro){
				if (abs((pt-a).norm()+(pt-b).norm()-(a-b).norm())<eps) pts.push_back(pt);
			}
			pts.push_back(b);
			sort(pts.begin(), pts.end(), [&](const Vec& p1, const Vec& p2){ return (p1-a).norm()<(p2-a).norm();});
			for (int j=0; j<pts.size()-1; j++){
				Vec p1 = pts[j], p2 = pts[j+1];
				if ((p1-p2).norm()<eps) continue;
				Vec m = (p1+p2)/2.0;
				if (m.norm()<r+eps) res += p1.cross(p2)/2.0;
				else {
					double rad = atan2(p1.cross(p2), p1.dot(p2));
					res += r*r*rad/2.0;
				}
			}
		}
		return res;
	}

	static Circle circumcircle(const Vec& a, const Vec& b, const Vec& c){
		Vec m1 = (a+b)/2.0, m2 = (a+c)/2.0;
		Vec dir1 = (b-a).rotate90(), dir2 = (c-a).rotate90();
		Vec center = Line(m1, m1+dir1).crosspointLL(Line(m2, m2+dir2));
		return Circle(center, (center-a).norm());
	}
	static Circle incircle(const Vec& a, const Vec& b, const Vec& c){
		double lenA = (b-c).norm(), lenB = (c-a).norm(), lenC = (a-b).norm();
		Vec center = (a*lenA+b*lenB+c*lenC)/(lenA+lenB+lenC);
		double S = abs((b-a).cross(c-a))/2.0;
		double r = S/((lenA+lenB+lenC)/2.0);
		return Circle(center, r);
	}
	friend istream& operator>>(istream& is, Circle& cr){ return is >>cr.c>>cr.r; }
	friend ostream& operator<<(ostream& os, const Circle& cr){ return os<<cr.c<<" "<<cr.r; }
};
```

## 仕様・機能
- `Circle c;` で円を作れます。
  - 中心を表すベクトル $c$ 、半径 $r$ の順番で定義されています。
- `Circle::circumcircle(a, b, c)`でベクトル $a, b, c$ を頂点とする三角形の外接円を返します。
- `Circle::incircle(a, b, c)`でベクトル $a, b, c$ を頂点とする三角形の内接円を返します。

### 関数
- `c.contain(p)`：円 $c$ が点 $p$ を含むかを返します。詳しくはコメントアウトに記載。
- `c.intersect(d)`：円 $c$ と円 $d$ の共通接線の数を返します。詳しくはコメントアウトに記載。
- `c.crosspoint(l)`：円 $c$ と直線 $l$ の交点を返します。
- `c.crosspoint(d)`：円 $c$ と円 $d$ の交点を返します。
- `c.tangent(p)`：点 $p$ を通る円 $c$ の接線と円 $c$ との交点を返します。
- `c.tangent(d)`：円 $c$ と円 $d$ の共通接線を返します。
- `c.intersect_area(d)`：円 $c$ と円 $d$ の共通部分の面積を返します。
- `c.intersect_area(poly)`：円 $c$ と多角形 $poly$ の共通部分の面積を返します。

## 計算量
- 大体： $O(1)$
- `intersect_area(poly)`： $O(|poly|)$

## 使用例