## 概要
整数を自動で $\text{mod} M$ として計算するやつ。

## コード
### 必須ライブラリ
- なし

### 本体
```cpp
// https://github.com/9circled/circled9-Library
template<int id>
struct modint {
	unsigned int x;
	inline static unsigned int MOD = 998244353;
	//inline static unsigned int MOD = int(1e9)+7;

	inline static unsigned long long IM = (unsigned long long)(-1)/MOD+1;

	modint(long long v=0) : x((v %= MOD) < 0 ? v+MOD : v) {}

	static void setMOD(unsigned int m) { MOD = m; IM = (unsigned long long)(-1)/m+1;}

	unsigned int val() const { return x; }

	modint& operator+=(const modint a) { if ((x += a.x)>=MOD) x -= MOD; return *this; }
	modint& operator-=(const modint a) { if ((x += MOD - a.x)>=MOD) x -= MOD; return *this; }
	modint& operator*=(const modint a) {
		unsigned long long z = (unsigned long long)x * a.x;
		unsigned long long q = (unsigned long long)(((unsigned __int128)z*IM)>>64);
		x = (unsigned int)(z-q*MOD);
		if (MOD<=x) x += MOD;
		return *this;
	}
	modint& operator/=(const modint a) { return *this *= a.inv(); }

	friend modint operator+(modint a, const modint b) { return a += b; }
	friend modint operator-(modint a, const modint b) { return a -= b; }
	friend modint operator*(modint a, const modint b) { return a *= b; }
	friend modint operator/(modint a, const modint b) { return a /= b; }

	modint& operator++() { if (++x == MOD) x = 0; return *this; }
	modint& operator--() { if (x == 0) x = MOD; --x; return *this; }
	modint operator++(int) { modint res = *this; ++*this; return res; }
	modint operator--(int) { modint res = *this; --*this; return res; }

	bool operator==(const modint a) const { return x == a.x; }
	bool operator!=(const modint a) const { return x != a.x; }
	modint operator-() const { return (x==0) ? 0 : MOD-x; }

	modint pow(long long t) const {
		modint res=1, a=*this;
		while (t>0) {
			if (t&1) res *= a;
			a *= a;
			t >>= 1;
		}
		return res;
	}
	modint inv() const { return pow(MOD-2); }

	friend ostream& operator<<(ostream& os, const modint& a) { return os<<a.x; }
	friend istream& operator>>(istream& is, modint& a) { long long t; is >> t; a = modint(t); return is; }
};
using mint = modint<0>;
using mint2 = modint<1>;
```

## 仕様・機能
- `mint a;`のようにしてmodint型を定義できる。
- `mint::setMOD(M)` で $M$ の値を変更することができる。

### 関数
- `a.pow(t)`： $a^t$ を求める。
- `a.inv()`： $a$ の逆元を求める

## 計算量
- 大体： $O(1)$
- $x\div y$ ： $O(\log{M})$
- $x^t$ ： $O(\log{t})$

## 使用例
- [ABC298 D - Writing a Numeral](https://atcoder.jp/contests/abc298/tasks/abc298_d) - [提出](https://atcoder.jp/contests/abc298/submissions/80045111)