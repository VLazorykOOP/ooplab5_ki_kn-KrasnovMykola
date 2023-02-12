#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

using namespace std;

class Triangle
{
public:
	Triangle()
	{
		a = b = c = 0;
	}
	Triangle(double a, double b, double c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}
	~Triangle()
	{
	}

	double get_a()
	{
		return a;
	}
	void set_a(double a)
	{
		this->a = a;
	}
	double get_b()
	{
		return b;
	}
	void set_b(double b)
	{
		this->b = b;
	}
	double get_c()
	{
		return c;
	}
	void set_c(double c)
	{
		this->c = c;
	}

	double get_alpha()
	{
		return acos((b * b + c * c - a * a) / (2 * b * c)) * 180 / M_PI;
	}
	double get_beta()
	{
		return acos((a * a + c * c - b * b) / (2 * a * c)) * 180 / M_PI;
	}
	double get_gama()
	{
		return acos((a * a + b * b - c * c) / (2 * a * b)) * 180 / M_PI;
	}

	double perimeter()
	{
		return a + b + c;
	}

private:
	double a, b, c;
};

class Equilateral : public Triangle
{
public:
	Equilateral() : Triangle()
	{
	}
	Equilateral(double a) : Triangle(a, a, a)
	{
	}
	~Equilateral()
	{
	}

	double area()
	{
		return get_a() * get_a() * sqrt(3) / 4;
	}

private:

};

int main()
{
	Triangle t1(3, 4, 5);
	cout << "t1 -> (" << t1.get_a() << ", " << t1.get_b() << ", " << t1.get_c() << ")" << endl;
	cout << "t1.get_alpha -> " << t1.get_alpha() << endl;
	cout << "t1.get_beta -> " << t1.get_beta() << endl;
	cout << "t1.get_gama -> " << t1.get_gama() << endl;
	cout << "t1.perimeter -> " << t1.perimeter() << endl;
	Equilateral t2(5);
	cout << "t2 -> (" << t2.get_a() << ")" << endl;
	cout << "t2.get_alpha -> " << t2.get_alpha() << endl;
	cout << "t2.get_beta -> " << t2.get_beta() << endl;
	cout << "t2.get_gama -> " << t2.get_gama() << endl;
	cout << "t2.perimeter -> " << t2.perimeter() << endl;
	cout << "t2.area -> " << t2.area() << endl;
	return 0;
}
