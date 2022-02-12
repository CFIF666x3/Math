#pragma once
#include "Base.h"
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
		cout << x << ' ' << y;
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
	Vector2d(double X, double Y)
	{
		x = X; y = Y;
	}
	Vector2d(double a)
	{
		x = cos(a);
		y = sin(a);
	}
	void init(Point2d a, Point2d b)
	{
		A = a; B = b;
		x = B.x - A.x, y = B.y - A.y;
		f = true;
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
	Vector2d rotate(double a)
	{
		Vector2d v;
		v.x = x * cos(a) + y * sin(a);
		v.y = -x * sin(a) + y * cos(a);
		return v;
	}
	double length()
	{
		return sqrt(pow(x, 2) + pow(y, 2));
	}
	double area()
	{
		if (f) return ((A.y) + (B.y)) / 2 * (B.x - A.x);
		else return -1; //points undefined
	}
	double inertia_moment_x() //for area under vector. may have negative result
	{
		if (f) return (B.x - A.x) * (pow(A.y, 2) + pow(B.y, 2)) * (A.y + B.y) / 12;
		else return -1; //points undefined
	}
	double inertia_moment_y() //for area under vector. may have negative result
	{
		if (f) return (B.y - A.y) * (pow(A.x, 2) + pow(B.x, 2)) * (A.x + B.x) / 12;
		else return -1; //points undefined
	}
	//double line(double x)
	//{
	//	if (f) return (B.y - A.y) / (B.x - A.x) * (x - A.x) + A.y;
	//	else return -1; //points undefined
	//}
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
class Polygon: private Vector2d
{
private:
	int NmbPnts, intersectionsy_size, intersectionsx_size;
	Point2d* P;
	Point2d** Segment;
	double* intersections_y(double x)
	{
		double* y; y = new double[NmbPnts]; int y_size = 0;
		for (int j = 0; j < NmbPnts; j++)
		{
			if (x > Segment[0][j].x and x < Segment[1][j].x)
			{
				y[y_size] = (Segment[1][j].y - Segment[0][j].y) / (Segment[1][j].x - Segment[0][j].x) * (x - Segment[0][j].x) + Segment[0][j].y;
				y_size++;
			}
		}
		bubble_sort(y, y_size);
		intersectionsy_size = y_size;
		return y;
	}
	double* intersections_x(double y)
	{
		double* x; x = new double[NmbPnts]; int x_size = 0;
		for (int j = 0; j < NmbPnts; j++)
		{
			Point2d A, B;
			if (Segment[0][j].y < Segment[1][j].y)
			{
				A = Segment[0][j]; B = Segment[1][j];
			}
			else
			{
				A = Segment[1][j]; B = Segment[0][j];
			}
			if (y > A.y and y < B.y)
			{
				x[x_size] = (B.x - A.x) / (B.y - A.y) * (y - A.y) + A.x;
				x_size++;
			}
		}
		bubble_sort(x, x_size);
		intersectionsx_size = x_size;
		return x;
	}
public:
	Polygon() {}
	Polygon(int N, Point2d* a)
	{
		NmbPnts = N;
		P = a;
		Segment = new Point2d * [2];
		for (int i = 0; i < 2; i++) Segment[i] = new Point2d[NmbPnts];
		for (int i = 0; i < NmbPnts - 1; i++)
			if (P[i].x <= P[i + 1].x)
			{
				Segment[0][i] = P[i];
				Segment[1][i] = P[i + 1];
			}
			else
			{
				Segment[1][i] = P[i];
				Segment[0][i] = P[i + 1];
			}
	}
	void init(int N, Point2d* a)
	{
		NmbPnts = N;
		P = a;
		Segment = new Point2d* [2];
		for (int i = 0; i < 2; i++) Segment[i] = new Point2d[NmbPnts];
		for (int i = 0; i < NmbPnts - 1; i++)
			if (P[i].x <= P[i + 1].x)
			{
				Segment[0][i] = P[i];
				Segment[1][i] = P[i + 1];
			}
			else
			{
				Segment[1][i] = P[i];
				Segment[0][i] = P[i + 1];
			}
		if (P[NmbPnts - 1].x <= P[0].x)
		{
			Segment[0][NmbPnts - 1] = P[NmbPnts - 1];
			Segment[1][NmbPnts - 1] = P[0];
		}
		else
		{
			Segment[0][NmbPnts - 1] = P[0];
			Segment[1][NmbPnts - 1] = P[NmbPnts - 1];
		}
		//for (int i = 0; i < NmbPnts; i++) cout << Segment[0][i] << ' ' << Segment[1][i] << '\n';
	}
	Point2d maxxpoint()
	{
		double max = -DBL_MAX; int k;
		for (int i = 0; i < NmbPnts; i++)
			if (P[i].x > max)
			{
				max = P[i].x;
				k = i;
			}
		return P[k];
	}
	Point2d maxypoint()
	{
		double max = -DBL_MAX; int k;
		for (int i = 0; i < NmbPnts; i++)
			if (P[i].y > max)
			{
				max = P[i].y;
				k = i;
			}
		return P[k];
	}
	Point2d minxpoint()
	{
		double min = DBL_MAX; int k;
		for (int i = 0; i < NmbPnts; i++)
			if (P[i].x < min)
			{
				min = P[i].x;
				k = i;
			}
		return P[k];
	}
	Point2d minypoint()
	{
		double min = DBL_MAX; int k;
		for (int i = 0; i < NmbPnts; i++)
			if (P[i].y < min)
			{
				min = P[i].y;
				k = i;
			}
		return P[k];
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
	void move(double x, double y)
	{
		for (int i = 0; i < NmbPnts; i++)
		{
			P[i].x += x;
			P[i].y += y;
		}
		for (int i = 0; i < NmbPnts; i++)
		{
			Segment[0][i].x += x;
			Segment[0][i].y += y;
			Segment[1][i].x += x;
			Segment[1][i].y += y;
		}
	}
	double inertia_moment_x()
	{
		double S = 0; Vector2d v;
		for (int i = 0; i < NmbPnts - 1; i++)
		{
			v.init(P[i], P[i + 1]);
			S += v.inertia_moment_x();
		}
		v.init(P[NmbPnts - 1], P[0]);
		S += v.inertia_moment_x();
		return abs(S);
	}
	double inertia_moment_y()
	{
		double S = 0; Vector2d v;
		for (int i = 0; i < NmbPnts - 1; i++)
		{
			v.init(P[i], P[i + 1]);
			S += v.inertia_moment_y();
		}
		v.init(P[NmbPnts - 1], P[0]);
		S += v.inertia_moment_y();
		return abs(S);
	}
	double static_moment_x()
	{
		double x1 = minxpoint().x, x2 = maxxpoint().x;
		int N = 10;  double dx1, dx2 = (x2 - x1) / N, S1 = 0, S2 = 0, eps = 1e-3;
		for (int i = 0; i < N; i++)
		{
			double* y;
			y = intersections_y(x1 + dx2 * i);
			for (int j = 0; j < intersectionsy_size - 1; j = j + 2)
				S2 += dx2 * (y[j + 1] - y[j]) * (y[j + 1] + y[j]) / 2;
		}
		do
		{
			S1 = S2; dx1 = dx2;
			N *= 10; dx2 = (x2 - x1) / N; S2 = 0;
			for (int i = 0; i < N; i++)
			{
				double* y;
				y = intersections_y(x1 + dx2 * i);
				for (int j = 0; j < intersectionsy_size - 1; j = j + 2)
					S2 += dx2 * (y[j + 1] - y[j]) * (y[j + 1] + y[j]) / 2;
			}
		} while ((abs(S2 - S1) > eps));
		return S2;
	}
	double static_moment_y()
	{
		double y1 = minypoint().y, y2 = maxypoint().y;
		int N = 10;  double dy1, dy2 = (y2 - y1) / N, S1 = 0, S2 = 0, eps = 1e-3;
		for (int i = 0; i < N; i++)
		{
			double* x;
			x = intersections_x(y1 + dy2 * i);
			for (int j = 0; j < intersectionsx_size - 1; j = j + 2)
				S2 += dy2 * (x[j + 1] - x[j]) * (x[j + 1] + x[j]) / 2;
		}
		do
		{
			S1 = S2; dy1 = dy2;
			N *= 10; dy2 = (y2 - y1) / N; S2 = 0;
			for (int i = 0; i < N; i++)
			{
				double* x;
				x = intersections_x(y1 + dy2 * i);
				for (int j = 0; j < intersectionsx_size - 1; j = j + 2)
					S2 += dy2 * (x[j + 1] - x[j]) * (x[j + 1] + x[j]) / 2;
			}
		} while ((abs(S2 - S1) > eps));
		return S2;
	}
	void print()
	{
		for (int i = 0; i < NmbPnts; i++) cout << P[i] << ' ';
	}
};