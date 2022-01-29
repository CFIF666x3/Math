#pragma once
const double pi(3.14159265358);
class Point2d
{
public:
	double x, y;
	Point2d() {}
	Point2d(int n, int m)
	{
		x = n; y = m;
	}
	Point2d Maxx(Point2d p)
	{
		if (x >= p.x) return *this;
		else return p;
	}
	Point2d Miny(Point2d p)
	{
		if (y >= p.y) return *this;
		else return p;
	}
	double angleX(Point2d p)
	{
		return atan((p.y - y) / (p.x - x));
	}
	Point2d rotate(double a)
	{
		Point2d p;
		p.x = x * cos(a) + y * sin(a);
		p.y = -x * sin(a) + y * cos(a);
		return p;
	}
	double length(Point2d p)
	{
		return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2));
	}
	void print()
	{
		cout << x << ' ' << y << ' ';
	}
	bool operator == (Point2d& p)
	{
		if (x == p.x and y == p.y) return true;
		else return false;
	}
	friend istream& operator >> (istream& stream, Point2d& p)
	{
		stream >> p.x;
		stream >> p.y;
		return stream;
	}
	friend ostream& operator << (ostream& stream, Point2d& p)
	{
		cout << p.x << ' ';
		return stream << p.y;
	}
};
class Vector2d
{
private:
	Point2d A, B;
	bool f = false;
public:
	double x, y;
	Vector2d() {}
	Vector2d(Point2d a, Point2d b)
	{
		A = a; B = b;
		x = B.x - A.x, y = B.y - A.y;
		f = true;
	}
	void init(Point2d a, Point2d b)
	{
		A = a; B = b;
		x = B.x - A.x, y = B.y - A.y;
		f = 1;
	}
	Vector2d(double X, double Y)
	{
		x = X; y = Y;
	}
	double operator * (Vector2d v) //scalar multiplication
	{
		return x * v.x + y * v.y;
	}
	double operator & (Vector2d v) //vector multiplication
	{
		return x * v.y - v.x * y;
	}
	double angle(Vector2d v)
	{
		return acos((*this * v) / length() / v.length());
	}
	/*Vector2d rotate(double a)
	{
		Point2d p;
		p.x = x * cos(a) + y * sin(a);
		p.y = -x * sin(a) + y * cos(a);
		return p;
	}*/
	double length()
	{
		return sqrt(pow(x, 2) + pow(y, 2));
	}
	double area()
	{
		if (f) return (A.y + B.y) / 2 * (B.x - A.x);
		else return -1; //points undefined
	}
	friend istream& operator >> (istream& stream, Vector2d& v)
	{
		stream >> v.x;
		stream >> v.y;
		return stream;
	}
	friend ostream& operator << (ostream& stream, Vector2d& v)
	{
		cout << v.x << ' ';
		return stream << v.y;
	}
};
class Figure2d
{
private:
	int NmbPnts;
	Point2d* P;
public:
	Figure2d() {}
	Figure2d(int N, Point2d* a)
	{
		NmbPnts = N;
		P = a;
	}
	void init(int N, Point2d* a)
	{
		NmbPnts = N;
		P = a;
	}
	bool isconvex()
	{
		double Sa = 0;
		for (int i = 1; i < NmbPnts - 1; i++)
		{
			Vector2d v1(P[i], P[i - 1]), v2(P[i], P[i + 1]);
			Sa += v1.angle(v2);
		}
		Vector2d v1(P[0], P[1]), v2(P[0], P[NmbPnts - 1]);
		Sa += v1.angle(v2); //First corner's angle
		v1.init(P[NmbPnts - 1], P[0]), v2.init(P[NmbPnts - 1], P[NmbPnts - 2]);
		Sa += v1.angle(v2); //Last corner's angle
		if (trunc(Sa * 1e5) == trunc((NmbPnts - 2) * pi * 1e5)) return true;
		else return false;
	}
	double perimeter()
	{
		double S = 0;
		for (int i = 0; i < NmbPnts - 1; i++) S += P[i].length(P[i + 1]);
		S += P[NmbPnts - 1].length(P[0]);
		return S;
	}
	double area()
	{
		double S = 0; Vector2d v;
		for (int i = 0; i < NmbPnts - 1; i++)
		{
			v.init(P[i], P[i + 1]);
			S += v.area();
		}
		v.init(P[NmbPnts - 1], P[0]);
		S += v.area();
		return abs(S);
	}
};