## 概要
幾何の多角形を表現するやつ。

## コード
### 必須ライブラリ
- `algorithm`
- [`Vec`](./Vec.md)
- [`Line`](./Line.md)

### 本体
```cpp
// https://github.com/9circled/circled9-Library
struct Polygon {
	vector<Vec> pts;

	Polygon() {}
	Polygon(int N) : pts(N) {}
	Polygon(const vector<Vec>& pts) : pts(pts) {}
	Vec& operator[](int i) { return pts[i]; }
	const Vec& operator[](int i) const { return pts[i]; }
	int size() const { return pts.size(); }
	void add(const Vec& p) { pts.push_back(p); }

	Polygon normalize() {
		Polygon res = *this;
		int N = res.size();
		if (N<3) return res;
		long long s = 0;
		for (int i=0; i<N; i++) s += res[i].cross(res[(i+1)%N]);
		if (s<0) reverse(res.pts.begin(), res.pts.end());
		int idx=0;
		for (int i=1; i<N; i++){
			if (res[i].y != res[idx].y){
				if (res[i].y<res[idx].y) idx=i;
			} else {
				if (res[i].x<res[idx].x) idx=i;
			}
		}
		rotate(res.pts.begin(), res.pts.begin()+idx, res.pts.end());
		return res;
	}
	long long area2() const {
		int N=size();
		if (N<3) return 0;
		long long s=0;
		for (int i=0; i<N; i++) s += pts[i].cross(pts[(i+1)%N]);
		return abs(s);
	}
 	long long diameter2() const {
 		Polygon p;
 		if (isConvex()) p = *this;
 		else p = convexHull();
 		int N = p.size();
 		if (N==2) return (p[0]-p[1]).norm2();
 		if (N<2) return 0.0;
 		int i=0, j=0;
 		for (int k=1; k<N; k++){
 			if (p[k].y<p[i].y) i=k;
 			if (p[k].y>p[j].y) j=k;
 		}
 		long long dist = 0;
 		int si=i, sj=j;
 		do {
 			dist = max(dist, (p[i]-p[j]).norm2());
 			Vec vi = p[(i+1)%N]-p[i], vj = p[(j+1)%N]-p[j];
 			if (vi.cross(vj)>=0) j = (j+1)%N;
 			else i = (i+1)%N;
 		} while (i!=si||j!=sj);
 		return dist;
 	}
	bool isConvex() const {
		int N=size();
		if (N<3) return false;
		for (int i=0; i<N; i++){
			Vec a = pts[i], b = pts[(i+1)%N], c = pts[(i+2)%N];
			Line l(a, b);
			if (l.ccw(c)==-1) return false;
		}
		return true;
	}
	int contain(const Vec& p) const {
		int N = size();
		bool in = false;
		for (int i=0; i<N; i++){
			Vec a = pts[i]-p, b = pts[(i+1)%N]-p;
			if (a.cross(b)==0&&a.dot(b)<=0) return 1; // on-edge
			if (a.y>b.y) swap(a, b);
			if (a.y<=0&&0<b.y&&a.cross(b)>0) in = !in;
		}
		return in ? 2 : 0; // in - out
	}
	Polygon convexHull() const {
		int N = size();
		if (N<3) return *this;
		vector<Vec> ps = pts;
		sort(ps.begin(), ps.end(), [](const Vec& a, const Vec& b){
			if (a.x!=b.x) return a.x<b.x;
			return a.y<b.y;
		});
		vector<Vec> ch(2*N);
		int k=0;
		for (int i=0; i<N; i++){
			while (k>=2&&Line(ch[k-2], ch[k-1]).ccw(ps[i])==-1) k--; // include on-edge
			// while (k>=2&&Line(ch[k-2], ch[k-1]).ccw(ps[i])!=1) k--; // exclude on-edge
			ch[k++] = ps[i];
		}
		int t=k;
		for (int i=N-2; i>=0; i--){
			while (k>t&&Line(ch[k-2], ch[k-1]).ccw(ps[i])==-1) k--; // include on-edge
			// while (k>t&&Line(ch[k-2], ch[k-1]).ccw(ps[i])!=1) k--; // exclude on-edge
			ch[k++] = ps[i];
		}
		ch.resize(k-1);
		return Polygon(ch);
	}

	friend istream& operator>>(istream& is, Polygon& p){
		for (int i=0; i<p.size(); i++) is>>p[i];
		return is;
	}

	friend ostream& operator<<(ostream& os, const Polygon& p){
		for (int i=0; i<p.size(); i++) os<<p[i]<<(i==p.size()-1 ? "" : "\n");
		return os;
	}
};
```

## 仕様・機能
- `Polygon poly;` で多角形を作れます。

### 関数
- `poly.size()`：多角形の頂点数を返します。
- `poly.add(p)`：多角形に点 $p$ を追加します。
- `poly.normalize()`：多角形の頂点順を反時計回りの順番にします。
- `poly.area2()`：多角形の面積の2倍を返します。
- `poly.diameter2()`：多角形の直径の2乗を返します。
- `poly.isConvex()`：多角形が凸多角形かを返します。
- `poly.contain(p)`：多角形に点 $p$ が含まれているかを返します。詳しくはコメントアウトに記載。
- `poly.convexHull()`：多角形の凸包を返します。（そのままだと辺上の点も含む）

## 計算量
多角形に追加された頂点の数を $N$ とする。
- 大体： $O(N)$
- `convexHull`： $O(N\log{N})$

## 使用例