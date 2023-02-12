#include <iostream>

using namespace std;

bool is_leap_year(int year)
{
	if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
		return true;
	return false;
}

class Triad
{
public:
	Triad()
	{
		a = b = c = 0;
		cout << "Constructor Triad()" << endl;
	}
	Triad(int a, int b, int c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		cout << "Constructor Triad(int a, int b, int c)" << endl;
	}
	Triad(int* values)
	{
		this->a = values[0];
		this->b = values[1];
		this->c = values[2];
		cout << "Constructor Triad(int* values)" << endl;
	}
	Triad(const Triad& t)
	{
		this->a = t.a;
		this->b = t.b;
		this->c = t.c;
		cout << "Constructor Triad(const Triad& t) (copy)" << endl;
	}
	Triad(Triad&& t)
	{
		this->a = t.a;
		this->b = t.b;
		this->c = t.c;
		t.a = t.b = t.c = 0;
		cout << "Constructor Triad(Triad&& t) (move)" << endl;
	}
	~Triad()
	{
		cout << "Destructor ~Triad()" << endl;
	}

	Triad& operator=(const Triad& t)
	{
		this->a = t.a;
		this->b = t.b;
		this->c = t.c;
		cout << "Operator operator=(const Triad& t) (copy)" << endl;
		return *this;
	}
	Triad& operator=(Triad&& t)
	{
		this->a = t.a;
		this->b = t.b;
		this->c = t.c;
		t.a = t.b = t.c = 0;
		cout << "Operator operator=(Triad&& t) (move)" << endl;
		return *this;
	}
	
	int get_a() const
	{
		return a;
	}
	void set_a(int a)
	{
		this->a = a;
	}
	int get_b() const
	{
		return b;
	}
	void set_b(int b)
	{
		this->b = b;
	}
	int get_c() const
	{
		return c;
	}
	void set_c(int c)
	{
		this->c = c;
	}

	void inc_a()
	{
		a++;
	}
	void inc_b()
	{
		b++;
	}
	void inc_c()
	{
		c++;
	}

	friend istream& operator>>(istream& in, Triad& t);
	friend ostream& operator<<(ostream& out, const Triad& t);

private:
	int a, b, c;
};

istream& operator>>(istream& in, Triad& t)
{
	in >> t.a >> t.b >> t.c;
	return in;
}

ostream& operator<<(ostream& out, const Triad& t)
{
	out << "(" << t.a << ", " << t.b << ", " << t.c << ")";
	return out;
}

class Date
{
public:
	int error_state = 0;

	Date()
	{
		cout << "Constructor Date()" << endl;
		date = new Triad(1, 1, 1970);
	}
	Date(int day, int month, int year) : Date()
	{
		cout << "Constructor Date(int day, int month, int year)" << endl;
		if (month < 1 || month > 12)
		{
			error_state = -1;
			return;
		}
		int d = 0;
		switch (month)
		{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			d = 31;
			break;
		case 4: case 6: case 9: case 11:
			d = 30;
			break;
		case 2:
			d = 28;
			if (is_leap_year(year))
				d++;
			break;
		default:
			break;
		}
		if (day < 1 || day > d)
		{
			error_state = -1;
			return;
		}
		date = new Triad(day, month, year);
	}
	Date(int* values) : Date()
	{
		cout << "Constructor Date(int day, int month, int year)" << endl;
		if (values[1] < 1 || values[1] > 12)
		{
			error_state = -1;
			return;
		}
		int d = 0;
		switch (values[1])
		{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			d = 31;
			break;
		case 4: case 6: case 9: case 11:
			d = 30;
			break;
		case 2:
			d = 28;
			if (is_leap_year(values[2]))
				d++;
			break;
		default:
			break;
		}
		if (values[0] < 1 || values[0] > d)
		{
			error_state = -1;
			return;
		}
		date = new Triad(values);
	}
	Date(const Date& d)
	{
		cout << "Constructor Date(const Date& d) (copy)" << endl;
		if (this->date == nullptr)
			this->date = new Triad();
		this->date->set_a(d.date->get_a());
		this->date->set_b(d.date->get_b());
		this->date->set_c(d.date->get_c());
	}
	Date(Date&& d)
	{
		cout << "Constructor Date(Date&& d) (move)" << endl;
		if (this->date == nullptr)
			this->date = new Triad();
		this->date->set_a(d.date->get_a());
		this->date->set_b(d.date->get_b());
		this->date->set_c(d.date->get_c());
		d.date->set_a(0);
		d.date->set_b(0);
		d.date->set_c(0);
	}
	~Date()
	{
		cout << "Destructor ~Date()" << endl;
		if (date != nullptr)
			delete date;
	}

	Date& operator=(const Date& d)
	{
		cout << "Operator operator=(const Date& d) (copy)" << endl;
		this->date->set_a(d.date->get_a());
		this->date->set_b(d.date->get_b());
		this->date->set_c(d.date->get_c());
		return *this;
	}
	Date& operator=(Date&& d)
	{
		cout << "Operator operator=(Date&& d) (move)" << endl;
		this->date->set_a(d.date->get_a());
		this->date->set_b(d.date->get_b());
		this->date->set_c(d.date->get_c());
		d.date->set_a(0);
		d.date->set_b(0);
		d.date->set_c(0);
		return *this;
	}

	void inc_day()
	{
		date->inc_a();
		switch (date->get_b())
		{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			if (date->get_a() > 31)
			{
				date->set_a(date->get_a() % 31);
				date->inc_b();
			}
			break;
		case 4: case 6: case 9: case 11:
			if (date->get_a() > 30)
			{
				date->set_a(date->get_a() % 30);
				date->inc_b();
			}
			break;
		case 2:
		{
			int d = 28;
			if (is_leap_year(date->get_c()))
				d++;
			if (date->get_a() > d)
			{
				date->set_a(date->get_a() % d);
				date->inc_b();
			}
			break;
		}
		default:
			break;
		}
		if (date->get_b() > 12)
		{
			date->set_b(date->get_b() % 12);
			date->inc_c();
		}
	}
	void inc_day(int n)
	{
		for (int i = 0; i < n; i++)
			inc_day();
	}
	void inc_month()
	{
		int d;
		date->inc_b();
		if (date->get_b() > 12)
		{
			date->set_b(date->get_b() % 12);
			date->inc_c();
		}
		switch (date->get_b())
		{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			d = 31;
			break;
		case 4: case 6: case 9: case 11:
			d = 30;
			break;
		case 2:
			d = 28;
			if (is_leap_year(date->get_c()))
				d++;
			break;
		default:
			break;
		}
		if (date->get_a() > d)
			date->set_a(d);
	}
	void inc_year()
	{
		if (date->get_a() == 29 && date->get_b() == 2)
			date->set_a(28);
		date->inc_c();
	}

	friend istream& operator>>(istream& in, Date& d);
	friend ostream& operator<<(ostream& out, const Date& d);

private:
	Triad* date;
};

istream& operator>>(istream& in, Date& d)
{
	if (d.date == nullptr)
		d.date = new Triad();
	in >> *(d.date);
	return in;
}

ostream& operator<<(ostream& out, const Date& d)
{
	out << d.date->get_a() << "." << d.date->get_b() << "." << d.date->get_c();
	return out;
}

int main()
{
	Date d(1, 1, 1998);
	if (d.error_state == -1)
		cout << "Date created by default!" << endl << endl;

	cout << "Start date: " << d << endl << endl;
	
	d.inc_year();
	cout << "Increment year: " << d << endl << endl;

	cout << "Increment month 12 times: " << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			d.inc_month();
			cout << d << '\t';
		}
		cout << endl;
	}
	cout << endl;

	cout << "Increment day 70 times: " << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			d.inc_day();
			cout << d << '\t';
		}
		cout << endl;
	}
	cout << endl;

	d.inc_day(354);
	cout << "Increment 354 days: " << d << endl << endl;

	d.inc_day();
	cout << "Increment day: " << d << endl;
	return 0;
}