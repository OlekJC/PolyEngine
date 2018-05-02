#include "CorePCH.hpp"

#include <climits>
//#include <cmath>

constexpr u64 ZERO = 0UL;

using namespace Poly;

constexpr BitMask::DataType TYPE_SIZE = CHAR_BIT * sizeof(BitMask::DataType);

BitMask::BitMask(size_t size)
	: BitsNumber(size)
{
	size_t arraySize = 0;
	
	if (size%CHAR_BIT)
		arraySize = size / CHAR_BIT + 1;
	else 
		arraySize = size / CHAR_BIT;

	for (int i = 0; i < arraySize;i++)
		BitList.PushBack(ZERO);
}

bool BitMask::Reset()
{
	BitList.Clear();
	BitsNumber = 0;
	return true;
}

bool BitMask::Toggle(size_t index)
{
	HEAVY_ASSERTE(RangeCheck(index), "Out of bounds");
	BitList[index/CHAR_BIT] ^= 1UL << index%CHAR_BIT;
	return true;
}

bool BitMask::operator[](size_t index) const
{
	DataType tempChar = BitList[index/CHAR_BIT];
	tempChar = (tempChar >> index%CHAR_BIT) & 1UL;
	return tempChar != 0;
}

bool BitMask::Set(size_t index, bool state)
{
	HEAVY_ASSERTE(RangeCheck(index), "Out of bounds");
	//size_t bitListIndex = BitListIndex(index);
	size_t bitListIndex	= index / CHAR_BIT;
	size_t bitPosition	= index % CHAR_BIT;
	//DataType bit = BitList[index / CHAR_BIT];
	if (state)
		BitList[bitListIndex] |= (1UL << bitPosition);
	else
		BitList[bitListIndex] &= ~(1UL << bitPosition);
	return true;
}

bool BitMask::RangeCheck(size_t index)
{
	if (index >= BitsNumber || index < 0)
		return false;
	return true;
}

BitMask BitMask::operator|(const BitMask& rhs) const
{
	//Equal Dynarray sizes
	if (BitList.GetSize() == rhs.BitList.GetSize())
	{
		size_t tempBitsNumber = 0;
		if (BitsNumber > rhs.BitsNumber)
			tempBitsNumber = BitsNumber;
		else
			tempBitsNumber = rhs.BitsNumber;

		BitMask temp(tempBitsNumber);
		for (size_t i = 0; i < BitList.GetSize(); i++)
			temp.BitList[i] = BitList[i] | rhs.BitList[i];
		return temp;
	}
	//Lhs size bigger than rhs size
	else if (BitList.GetSize() > rhs.BitList.GetSize())
	{
		BitMask temp(BitsNumber);
		for (size_t i = 0; i < rhs.BitList.GetSize(); i++)
			temp.BitList[i] = BitList[i] | rhs.BitList[i];
		for (size_t i = rhs.BitList.GetSize(); i < BitList.GetSize(); i++)
			temp.BitList[i] = BitList[i] | ZERO;
		return temp;
	}
	//Rhs size bigger than lhs size
	else if (BitList.GetSize() < rhs.BitList.GetSize())
	{
		BitMask temp(rhs.BitsNumber);
		for (size_t i = 0; i < BitList.GetSize(); i++)
			temp.BitList[i] = BitList[i] | rhs.BitList[i];
		for (size_t i = BitList.GetSize(); i < rhs.BitList.GetSize(); i++)
			temp.BitList[i] = rhs.BitList[i] | ZERO;
		return temp;
	}
	return BitMask(0);
}

BitMask BitMask::operator^(const BitMask& rhs) const
{
	//Equal BitMasks sizes
	if (BitList.GetSize() == rhs.BitList.GetSize())
	{
		size_t tempBitsNumber = 0;
		if (BitsNumber > rhs.BitsNumber)
			tempBitsNumber = BitsNumber;
		else
			tempBitsNumber = rhs.BitsNumber;

		BitMask temp(tempBitsNumber);
		for (size_t i = 0; i < BitList.GetSize(); i++)
			temp.BitList[i] = BitList[i] ^ rhs.BitList[i];
		return temp;
	}
	//Lhs size bigger than rhs size
	else if (BitList.GetSize() > rhs.BitList.GetSize())
	{
		BitMask temp(BitsNumber);
		for (size_t i = 0; i < rhs.BitList.GetSize(); i++)
			temp.BitList[i] = BitList[i] ^ rhs.BitList[i];
		for (size_t i = rhs.BitList.GetSize(); i < BitList.GetSize(); i++)
			temp.BitList[i] = BitList[i] ^ ZERO;
		return temp;
	}
	//rhs size bigger than lhs size
	else if (BitList.GetSize() < rhs.BitList.GetSize())
	{
		BitMask temp(rhs.BitsNumber);
		for (size_t i = 0; i < BitList.GetSize(); i++)
			temp.BitList[i] = BitList[i] ^ rhs.BitList[i];
		for (size_t i = BitList.GetSize(); i < rhs.BitList.GetSize(); i++)
			temp.BitList[i] = rhs.BitList[i] ^ ZERO;
		return temp;
	}
	return BitMask(0);
}

BitMask BitMask::operator&(const BitMask& rhs) const
{
	if (BitList.GetSize() == rhs.BitList.GetSize())
	{
		size_t tempBitsNumber = 0;
		if (BitsNumber > rhs.BitsNumber)
			tempBitsNumber = BitsNumber;
		else
			tempBitsNumber = rhs.BitsNumber;

		BitMask temp(tempBitsNumber);
		for (size_t i = 0; i < BitList.GetSize(); i++)
			temp.BitList[i] = BitList[i] & rhs.BitList[i];
		return temp;
	}
	else if (BitList.GetSize() > rhs.BitList.GetSize())
	{
		BitMask temp(BitsNumber);
		for (size_t i = 0; i < rhs.BitList.GetSize(); i++)
			temp.BitList[i] = BitList[i] & rhs.BitList[i];
		for (size_t i = rhs.BitList.GetSize(); i < BitList.GetSize(); i++)
			temp.BitList[i] = BitList[i] & ZERO;
		return temp;
	}
	else if (BitList.GetSize() < rhs.BitList.GetSize())
	{
		BitMask temp(rhs.BitsNumber);
		for (size_t i = 0; i < BitList.GetSize(); i++)
			temp.BitList[i] = BitList[i] & rhs.BitList[i];
		for (size_t i = BitList.GetSize(); i < rhs.BitList.GetSize(); i++)
			temp.BitList[i] = rhs.BitList[i] & ZERO;
		return temp;
	}
	return BitMask(0);
}

BitMask& BitMask::operator~()
{
	for (auto& x : BitList)
		x=~x;

	return *this;
}


bool BitMask::Resize(const int offset)
{
	if (offset > 0)
	{
		HEAVY_ASSERTE(BitsNumber + offset < ULLONG_MAX, "Out of size_t range"); //Czy to ma sens?
		if (BitsNumber + offset <= GetDynarraySize()*CHAR_BIT)
		{
			BitsNumber += offset;
			return true;
		}
		else
		{
			size_t x = BitList.GetSize()*CHAR_BIT;
			size_t y = x-BitsNumber;
			size_t z = offset - static_cast<int>(y);
			size_t pushBackCount = z / CHAR_BIT;
			if (z%CHAR_BIT)
				pushBackCount++;
			for (size_t i = 0; i < pushBackCount; i++)
				BitList.PushBack(ZERO);
			
			BitsNumber += offset;
			return true;
		}
	}
	
	if (offset < 0)
	{
		HEAVY_ASSERTE(BitsNumber+offset>=0, "Out of bounds");
		if (BitsNumber + offset > (GetDynarraySize()-1)*CHAR_BIT)
		{
			BitsNumber += offset;
			return true;
		}
		else
		{
			size_t currentSize = BitList.GetSize();
			size_t targetSize = 0;
			if (-1*(BitsNumber+offset) % CHAR_BIT)
				targetSize = (BitsNumber + offset) / CHAR_BIT+1;
			else
				targetSize = (BitsNumber + offset) / CHAR_BIT;
			
			size_t popBackCount = currentSize - targetSize;
			for (size_t i = 0; i < popBackCount; i++)
				BitList.PopBack();

			BitsNumber += offset;
			return true;
		}
	}
	
	
	if (offset == 0)
	{
		return false;
	}
	return false;
}

size_t BitMask::BitListIndex(size_t index)
{
		return index / CHAR_BIT;
}

BitMask& BitMask::operator|=(const BitMask& rhs)
{
	//Equal Dynarray sizes
	if (BitList.GetSize() == rhs.BitList.GetSize())
	{
		for (size_t i = 0; i < BitList.GetSize(); i++)
			BitList[i] |= rhs.BitList[i];

		if (rhs.BitsNumber > BitsNumber)
			BitsNumber = rhs.BitsNumber;

		return *this;
	}
	//Lhs size bigger than rhs size
	else if (BitList.GetSize() > rhs.BitList.GetSize())
	{
		for (size_t i = 0; i < rhs.BitList.GetSize(); i++)
			BitList[i] |= rhs.BitList[i];
		for (size_t i = rhs.BitList.GetSize(); i < BitList.GetSize(); i++)
			BitList[i] |= ZERO;
		return *this;
	}
	//Rhs size bigger than lhs size
	else if (BitList.GetSize() < rhs.BitList.GetSize())
	{
		for (size_t i = 0; i < BitList.GetSize(); i++)
			BitList[i] |= rhs.BitList[i];
		
		size_t oldBitListSize = BitList.GetSize();

		for (size_t i = 0; i < rhs.BitList.GetSize() - oldBitListSize; i++)
			BitList.PushBack(ZERO);
			
		for (size_t i = oldBitListSize; i < BitList.GetSize(); i++)
			BitList[i] |= ZERO;

		BitsNumber = rhs.BitsNumber;
		return *this;
	}
	return *this;
}

BitMask& BitMask::operator^=(const BitMask& rhs)
{
	if (BitList.GetSize() == rhs.BitList.GetSize())
	{
		for (size_t i = 0; i < BitList.GetSize(); i++)
			BitList[i] ^= rhs.BitList[i];

		//Przypisac BitsNumbery
		if (rhs.BitsNumber > BitsNumber)
			BitsNumber = rhs.BitsNumber;

		return *this;
	}
	else if (BitList.GetSize() > rhs.BitList.GetSize())
	{
		for (size_t i = 0; i < rhs.BitList.GetSize(); i++)
			BitList[i] ^= rhs.BitList[i];
		for (size_t i = rhs.BitList.GetSize(); i < BitList.GetSize(); i++)
			BitList[i] = rhs.BitList[i];	//BitList[i] will always be equal to rhs.BitList[i]
		return *this;
	}
	else if (BitList.GetSize() < rhs.BitList.GetSize())
	{
		for (size_t i = 0; i < BitList.GetSize(); i++)
			BitList[i] ^= rhs.BitList[i];

		size_t oldBitListSize = BitList.GetSize();

		for (size_t i = 0; i < rhs.BitList.GetSize() - BitList.GetSize(); i++)
			BitList.PushBack(ZERO);

		for (size_t i = oldBitListSize; i < BitList.GetSize(); i++)
			BitList[i] ^= ZERO;

		BitsNumber = rhs.BitsNumber;
		return *this;
	}
	return *this;
}

BitMask& BitMask::operator&=(const BitMask& rhs)
{
	if (BitList.GetSize() == rhs.BitList.GetSize())
	{
		for (size_t i = 0; i < BitList.GetSize(); i++)
			BitList[i] &= rhs.BitList[i];

		if (rhs.BitsNumber > BitsNumber)
			BitsNumber = rhs.BitsNumber;

		return *this;
	}
	else if (BitList.GetSize() > rhs.BitList.GetSize())
	{
		for (size_t i = 0; i < rhs.BitList.GetSize(); i++)
			BitList[i] &= rhs.BitList[i];
		for (size_t i = rhs.BitList.GetSize(); i < BitList.GetSize(); i++)
			BitList[i] &= ZERO;
		return *this;
	}
	else if (BitList.GetSize() < rhs.BitList.GetSize())
	{
		for (size_t i = 0; i < BitList.GetSize(); i++)
			BitList[i] &= rhs.BitList[i];
		
		size_t oldBitListSize = BitList.GetSize();

		for (size_t i = 0; i < rhs.BitList.GetSize() - BitList.GetSize(); i++)
			BitList.PushBack(ZERO);

		for (size_t i = oldBitListSize; i < BitList.GetSize(); i++)
			BitList[i] &= ZERO;
		//Update of data quantity info changed in code above
		//BitList.GetSize() = rhs.BitList.GetSize();
		BitsNumber = rhs.BitsNumber;
		return *this;
	}
	return *this;
}

bool BitMask::operator==(const BitMask rhs) const
{
	if (BitsNumber!=rhs.BitsNumber)
		return false;

	if (BitsNumber == rhs.BitsNumber)
	{
		for (size_t i = 0; i < BitList.GetSize(); i++)
			if (BitList[i] != rhs.BitList[i])
				return false;
		return true;
	}
	return false;
}