#include<iostream>
using std::cout;
using std::endl;
using std::cin;

//#define CONSTRUCTIONS_CHECK
//#define OPERATORS_CHECK
//#define INPUT_OUTPUT_CHECK
#define TYPE_CONVERSIONS

class Fraction
{
	//Описывает простую дробь
	int integer; //целая часть дроби
	int numerator; //числитель
	int denominator; //знаменатель

public://в открытой секции обьявляются get/set методы
	int get_integer() const
	{
		return integer;
	}
	int get_numerator() const
	{
		return numerator;
	}
	int get_denominator() const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator != 0)
		{
			this->denominator = denominator;
		}
		else
		{
			this->denominator = 1;
		}
	}

	Fraction& operator()(int integer, int numerator, int denominator)
	{
		set_integer(integer);
		set_numerator(numerator);
		set_denominator(denominator);
		return *this;
	}

	//		Constructors
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		std::cout << "DefaultConstruct:\t" << this << std::endl;
	}
	explicit Fraction(int integer) // явный
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		std::cout << "SingleArgumentConstructor:\t" << this << std::endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		this->denominator = denominator ? denominator : 1;
		std::cout << "Constructor:\t" << this << std::endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		this->denominator = denominator ? denominator : 1;
		/*
			condition ? expression1 : expression2;
		*/
		std::cout << "Constructor:\t" << this << std::endl;
	}
	~Fraction()
	{
		std::cout << "Destructor:\t" << this << std::endl;
	}
	Fraction(const Fraction& other)
	{
		//*this = other;
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		std::cout << "CopyConstructor:\t" << this << std::endl;
	}
	Fraction& operator*=(Fraction& other)
	{
		this->to_improper();
		other.to_improper();
		this->numerator *= other.numerator;
		this->denominator *= other.denominator;
		return this->to_proper();
	}
	
	//		Operators:
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		std::cout << "CopyAssignment:" << this << std::endl;
		return *this;
	}

	Fraction& operator=(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		return *this;
	}

	/*Fraction operator*(Fraction right) const
	{
		Fraction left = *this;
		left.to_improper();
		right.to_improper();
		Fraction result;
		result.numerator = left.numerator * right.numerator;
		result.denominator = left.denominator * right.denominator;
		result.to_proper();
		return result;
	}*/

	//		Increment/Decrement (Инкримент и дикремент)
	Fraction& operator++()
	{
		this->integer++;
		return *this;
	}

	Fraction operator++(int) //postfix increment
	{
		Fraction buffer = *this;
		this->integer++;
		return buffer;
	}
	//		type-cast operators:
	explicit operator int() const
	{
		return integer;
	}
	operator double() const
	{
		// Из простой дроби делаем десятичную
		return integer + (double)numerator / denominator;
	}

	//		Methods:
	Fraction& print()
	{
		if (integer)std::cout << integer;
		if (numerator)
		{
			if (integer)std::cout << "(";
			std::cout << numerator << "/" << denominator;
			if (integer)std::cout << ")";
		}
		else if (integer == 0)std::cout << 0;
		std::cout << std::endl;
		return *this;
	}

	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer -= integer;
		return *this;
	}
	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}

	bool reduce() // метод reduce сокращает дробь
	{
		int a, b;
		a = this->numerator;
		b = this->denominator;
		bool res = false;
		for (int i = this->denominator; i > 1; i--)
		{
			if ((this->numerator % i == 0) && (this->denominator % i == 0))
			{
				a /= i;
				b /= i;
				this->numerator /= i;
				this->denominator /= i;
				i = this->denominator;
				res = true;
			}
		}
		return(res);
	}
	
};
Fraction operator*(Fraction left, Fraction right) // оператор умножения
{
	left.to_improper();
	right.to_improper();
	Fraction result(left.get_numerator() * right.get_numerator(), left.get_denominator() * right.get_denominator());
	/*result.set_numerator(left.get_numerator()*right.get_numerator());
	result.set_denominator(left.get_denominator()*right.get_denominator());*/
	//result.to_proper();
	return result.to_proper();
}
Fraction operator+(Fraction left, Fraction right) //оператор сложения
{
	left.to_improper();
	right.to_improper();
	Fraction result((left.get_numerator() * right.get_denominator())+(right.get_numerator() * left.get_denominator()), left.get_denominator() * right.get_denominator());
	return result.to_proper();
}

Fraction operator/(Fraction left, Fraction right) //оператор деления
{
	left.to_improper();
	right.to_improper();
	Fraction result(left.get_numerator() * right.get_denominator(), left.get_denominator() * right.get_numerator());
	return result.to_proper();
}

Fraction operator-(Fraction left, Fraction right) //оператор вычетания
{
	left.to_improper();
	right.to_improper();
	Fraction result((left.get_numerator() * right.get_denominator()) - (right.get_numerator() * left.get_denominator()), left.get_denominator() * right.get_denominator());
	return result.to_proper();
}

std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	if (obj.get_integer())os << obj.get_integer();
	if (obj.get_numerator())
	{
		if (obj.get_integer())os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())os << ")";
	}
	if(obj.get_integer() == 0 && obj.get_numerator() == 0)os << 0;
	return os;
}

std::istream& operator>>(std::istream& is, Fraction& obj)
{
	int integer, numerator, denominator;
	is >> integer >> numerator >> denominator;
	obj(integer, numerator, denominator);
	return is;

}

void main()
{
	setlocale(LC_ALL, "");
	std::cout << "**********************************************" << std::endl;
	std::cout << "\t\t\tOOP_Fraction" << std::endl;
	std::cout << "**********************************************" << std::endl;
#ifdef CONSTRUCTIONS_CHECK
	double a = 5;
	std::cout << a << std::endl;
	Fraction A; //Default constructor;
	A.print();
	Fraction B(5); //Single argument constructor
	B.print();

	Fraction C(1, 2); //Constructor
	C.print();

	Fraction D(2, 3, 4); //Constructor
	D.print();

	Fraction E = D; //Copy constructor
	E.print();

	Fraction F;
	F = E;
	F.print();
#endif // CONSTRUCTIONS_CHECK

#ifdef OPERATORS_CHECK
	Fraction A(2, 1, 2);
	Fraction B(3, 4, 5);
	A.print();
	B.print();
	Fraction C = A * B;
	Fraction D = A + B;
	Fraction E = A / B;
	Fraction F = A - B;
	C.print();
	D.print();
	E.print();
	F.print();
	std::cout << "---------------------" << std::endl;
	C.reduce();
	A.print();
	B.print();
	A *= B;
	A.print();

	double a = 2.5;
	double b = 3.14;
	double c = a * b;
#endif // OPERATORS_CHECK

#ifdef INPUT_OUTPUT_CHECK
	for (double i = 0.25; i < 10; i++)
	{
		std::cout << i << "\t";
	} 
	std::cout << "---------------------" << std::endl;
	Fraction A(1, 4);
	std::cout << A++ << std::endl;
	std::cout << "Введите целую часть дроби, числитель и знаменатель через пробел: ";
	std::cin >> A;
	std::cout << "Вы ввели: " << A << std::endl;
#endif // INPUT_OUTPUT_CHECK

#ifdef TYPE_CONVERSIONS
	int a = 2;
	double b = 3;
	a = b;
	std::cout << a << std::endl;
	Fraction A = (Fraction)4; // single argument constructor
	A = (Fraction)5; // operator=
	std::cout << A << std::endl;

	a = (int)A; // C-like cast notation
	a = int(A); // Functional notation
	std::cout << a << std::endl;
	std::cout << "**********************************************" << std::endl;
	A(2, 3, 10);
	b = A;
	std::cout << b << std::endl;
	
#endif // TYPE_CONVERSIONS

}
