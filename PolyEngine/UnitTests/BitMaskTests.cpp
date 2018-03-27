#include <catch.hpp>

#include <BitMask.hpp>

using namespace Poly;

TEST_CASE("BitMask constructors", "[BitMask]")
{
	//default constructor
	BitMask a;
	REQUIRE(a.GetSize() == 1);
	BitMask b;
	REQUIRE(a.GetSize() == b.GetSize());
	REQUIRE(a.GetArraySize2() == b.GetArraySize2());
	REQUIRE(a.GetArraySize2() == 1);
	BitMask c(20);
	REQUIRE(c.GetSize() == 20);
	REQUIRE(c.GetArraySize2() == 3);
	for (size_t i = 0; i < a.GetSize(); i++)
		REQUIRE(a[i] == false);
	for (size_t i = 0; i < b.GetSize(); i++)
		REQUIRE(b[i] == false);
	for (size_t i = 0; i < c.GetSize(); i++)
		REQUIRE(c[i] == false);
}

TEST_CASE("BitMask Set,Toggle and Reset", "[BitMask]")
{
	BitMask a(8);
	//Set method
	a.Set(7, true);
	a.Set(0, true);
	REQUIRE(a[7] == true);
	REQUIRE(a[0] == true);
	a.Set(7, false);
	a.Set(0, false);
	REQUIRE(a[7] == false);
	REQUIRE(a[0] == false);

	//Toggle method
	a.Toggle(1);
	REQUIRE(a[1] == true);
	a.Toggle(1);
	REQUIRE(a[1] == false);

	//Reset method
	a.Reset();
	REQUIRE(a.GetSize() == 0);
	REQUIRE(a.GetArraySize2() == 0);
}
TEST_CASE("Bitwise operators", "[BitMask]")
{
	//Bitwise OR operator
	{
		BitMask a(9), b(20);
		BitMask c;
		a.Toggle(2);	a.Toggle(3);	a.Toggle(7);
		b.Toggle(4);	b.Toggle(10);	b.Toggle(14);
		c = a | b;
		REQUIRE(c.GetSize() == b.GetSize());
		for (size_t i = 0; i < c.GetSize(); i++)
		{
			if (i == 2 || i == 3 || i == 4 ||
				i == 7 || i == 10 || i == 14)
				REQUIRE(c[i] == true);
			else
				REQUIRE(c[i] == false);
		}
	}
	
	//Bitwise XOR operator
	{
		BitMask a(8), b(17);
		BitMask c;
		a.Toggle(2);	a.Toggle(3);	a.Toggle(7);
		b.Toggle(2);	b.Toggle(5);	b.Toggle(7);	b.Toggle(16);
		c = a ^ b;
		REQUIRE(c.GetSize() == b.GetSize());
		for (size_t i = 0; i < c.GetSize(); i++)
		{
			if (i == 3 || i == 5 || i == 16)
				REQUIRE(c[i] == true);
			else
				REQUIRE(c[i] == false);
		}
	}

	//Bitwise AND operator
	{
		BitMask a(4), b(10);
		BitMask c;
		a.Toggle(1);	a.Toggle(2);	a.Toggle(3);
		b.Toggle(1);	b.Toggle(3);	b.Toggle(7);
		c = a & b;
		REQUIRE(c.GetSize() == b.GetSize());
		for (size_t i = 0; i < c.GetSize(); i++)
		{
			if (i == 1 || i == 3)
				REQUIRE(c[i] == true);
			else
				REQUIRE(c[i] == false);
		}
	}
}

TEST_CASE("Negate operator", "[BitMask]")
{
	BitMask a(10);
	for (size_t i = 0; i < a.GetSize(); i++)
		if (i % 2)
			a.Toggle(static_cast<int>(i));

	~a;
	for (size_t i = 0; i < a.GetSize(); i++)
		if (i % 2)
			REQUIRE(a[i] == false);
		else
			REQUIRE(a[i] == true);
}

TEST_CASE("Bitwise assignment operators", "[BitMask]")
{
	//Bitwise OR assignment operator
	{
		BitMask a(9), b(20);
		a.Toggle(2);	a.Toggle(3);	a.Toggle(7);
		b.Toggle(4);	b.Toggle(10);	b.Toggle(14);
		a |= b;
		REQUIRE(a.GetSize() == b.GetSize());
		for (size_t i = 0; i < a.GetSize(); i++)
		{
			if (i == 2 || i == 3 || i == 4 ||
				i == 7 || i == 10 || i == 14)
				REQUIRE(a[i] == true);
			else
				REQUIRE(a[i] == false);
		}
	}
}
/*
TEST_CASE("Toggle and check", "[BitMask]")
{
	BitMask a(20);
	REQUIRE(a.GetSize() == 20);
	//REQUIRE(a.GetArraySize() == 3);
	//REQUIRE(a.GetArraySize2() == 3);
	//To potem
	BitMask b(20);
	REQUIRE(a == b);
	for (size_t i = 0; i < 23; i++) //max i==24 not 23??
		REQUIRE(a[i] == false);
	a.Set(0, true);
	REQUIRE(a[0] == true);
	REQUIRE(a[12] == false);
	a.Set(12, true);
	REQUIRE(a[12] == true);
	a.Set(12, false);
	REQUIRE(a[12] == false);
	//Toggle test
	a.Toggle(10);
	REQUIRE(a[10] == true);
	a.Toggle(10);
	REQUIRE(a[10] == false);
	a.Toggle(10);

	a.Reset();
	//REQUIRE(a.GetArraySize() == 0);
	BitMask c(4), d(10);
	for (size_t i = 0; i < 4; i++)
		REQUIRE(c[i] == false);
	for (size_t i = 0; i < 10; i++)
		REQUIRE(d[i] == false);
	c.Toggle(2); c.Toggle(3);
	d.Toggle(1); d.Toggle(6);
	REQUIRE(c != d);
	d |= c;
	for (size_t i = 0; i < 10; i++)
	{
		if (i == 1 || i == 2 || i == 3 || i == 6)
			REQUIRE(d[i] == true);
		else
			REQUIRE(d[i] == false);
	}
}
*/
TEST_CASE("BitMask resize", "[BitMask]")
{
	BitMask a;
	REQUIRE(a.GetSize() == 1);
	a.Resize(3);
	REQUIRE(a.GetSize() == 4);
	REQUIRE(a.GetArraySize2()==1);
	a.Resize(6);
	REQUIRE(a.GetSize() == 10);
	//REQUIRE(a.GetArraySize2() == 2);

}