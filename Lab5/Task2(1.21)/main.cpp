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
	}
	Triad(int a, int b, int c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}
	~Triad()
	{
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

private:
	int a, b, c;
};

class Date
{
public:
	int error_state = 0;

	Date()
	{
		date = Triad(1, 1, 1970);
	}
	Date(int day, int month, int year) : Date()
	{
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
		date = Triad(day, month, year);
	}
	~Date()
	{
	}

	void inc_day()
	{
		date.inc_a();
		switch (date.get_b())
		{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			if (date.get_a() > 31)
			{
				date.set_a(date.get_a() % 31);
				date.inc_b();
			}
			break;
		case 4: case 6: case 9: case 11:
			if (date.get_a() > 30)
			{
				date.set_a(date.get_a() % 30);
				date.inc_b();
			}
			break;
		case 2:
		{
			int d = 28;
			if (is_leap_year(date.get_c()))
				d++;
			if (date.get_a() > d)
			{
				date.set_a(date.get_a() % d);
				date.inc_b();
			}
			break;
		}
		default:
			break;
		}
		if (date.get_b() > 12)
		{
			date.set_b(date.get_b() % 12);
			date.inc_c();
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
		date.inc_b();
		if (date.get_b() > 12)
		{
			date.set_b(date.get_b() % 12);
			date.inc_c();
		}
		switch (date.get_b())
		{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			d = 31;
			break;
		case 4: case 6: case 9: case 11:
			d = 30;
			break;
		case 2:
			d = 28;
			if (is_leap_year(date.get_c()))
				d++;
			break;
		default:
			break;
		}
		if (date.get_a() > d)
			date.set_a(d);
	}
	void inc_year()
	{
		if (date.get_a() == 29 && date.get_b() == 2)
			date.set_a(28);
		date.inc_c();
	}

	friend ostream& operator<<(ostream& out, const Date& d)
	{
		out << d.date.get_a() << "." << d.date.get_b() << "." << d.date.get_c();
		return out;
	}

private:
	Triad date;
};

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