#include <catch.hpp>

#include <BitMask.hpp>

using namespace Poly;

TEST_CASE("Toggle and check", "[BitMask]")
{
	BitMask a(20);
	REQUIRE(a.GetSize() == 20);
	REQUIRE(a.GetSize2() == 3);
	REQUIRE(a.DASize() == 3);
	//To potem
	BitMask b(20);
	REQUIRE(a == b);
	for (size_t i = 0; i < 23; i++) //max i==24 not 23??
		REQUIRE(a[i] == false);
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
	REQUIRE(a.DASize() == 0);
	BitMask c(4), d(10);
	for (size_t i = 0; i < 4; i++)
		REQUIRE(c[i] == false);
	for (size_t i = 0; i < 10; i++)
		REQUIRE(d[i] == false);
	c.Toggle(2); c.Toggle(3);
	d.Toggle(1); d.Toggle(6);
	REQUIRE(c != d);
	d |= c;
	for (size_t i = 0; i < 10;i++)
	{
		if (i == 1 || i == 2 || i == 3 || i == 6)
			REQUIRE(d[i] == true);
		else
			REQUIRE(d[i] == false);
	}
}