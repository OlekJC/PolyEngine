#include "CorePCH.hpp"

#include <climits>

#define ZERO 0UL

using namespace Poly;

BitMask::BitMask(size_t size)
	: BitsNumber(size)
{
	size_t arrSize = 0;
	
	if (size%CHAR_BIT)
		arrSize = size / CHAR_BIT + 1;
	else 
		arrSize = size / CHAR_BIT;
	Size = arrSize;
	for (int i = 0; i < Size;i++)
		BitList.PushBack(ZERO);
	//BitList = Dynarray<DataType>(arrSize);
	//BitList = Dynarray<DataType>(5);
	//for (auto x : BitList)
		//x = 0UL;
}

bool BitMask::Reset()
{
	BitList.Clear();
	Size = 0;
	BitsNumber = 0;
	return true;
}

bool BitMask::Toggle(int index)
{
	if (RangeCheck(index))
		return false;
	size_t bitListIndex = 0;
	bitListIndex = BitListIndex(index);
	BitList[bitListIndex] ^= 1UL << index%CHAR_BIT;
	return true;
}

bool BitMask::operator[](size_t index)
{
	size_t bitListIndex = 0;
	bitListIndex = BitListIndex(index);
	DataType tempChar = BitList[bitListIndex];
	tempChar = (tempChar >> index%CHAR_BIT) & 1UL;
	return tempChar != 0;
}

bool BitMask::Set(int index, bool state)
{
	if (RangeCheck(index))
		return false;
	size_t bitListIndex = BitListIndex(index);
	size_t bitPosition = index%CHAR_BIT;
	DataType bit = BitList[bitListIndex];
	if (state)
		BitList[bitListIndex] |= (1UL << bitPosition);
	else
		BitList[bitListIndex] &= ~(1UL << bitPosition);
	return true;
}

bool BitMask::RangeCheck(int index)
{
	if (index >= BitsNumber || index < 0)
		return true;
	return false;
}

BitMask BitMask::operator|(const BitMask rhs) const
{
	if (Size == rhs.Size)
	{
		BitMask temp(BitsNumber);
		for (size_t i = 0; i < Size; i++)
			temp.BitList[i] = BitList[i] | rhs.BitList[i];
		return temp;
	}
	else if (Size > rhs.Size)
	{
		BitMask temp(BitsNumber);
		for (size_t i = 0; i < rhs.Size; i++)
			temp.BitList[i] = BitList[i] | rhs.BitList[i];
		for (size_t i = rhs.Size; i < Size; i++)
			temp.BitList[i] = BitList[i] | ZERO;
		return temp;
	}
	else if (Size < rhs.Size)
	{
		BitMask temp(rhs.BitsNumber);
		for (size_t i = 0; i < Size; i++)
			temp.BitList[i] = BitList[i] | rhs.BitList[i];
		for (size_t i = Size; i < rhs.Size; i++)
			temp.BitList[i] = rhs.BitList[i] | ZERO;
		return temp;
	}
	return BitMask(0);
}

BitMask BitMask::operator^(const BitMask rhs) const
{
	if (Size == rhs.Size)
	{
		BitMask temp(BitsNumber);
		for (size_t i = 0; i < Size; i++)
			temp.BitList[i] = BitList[i] ^ rhs.BitList[i];
		return temp;
	}
	else if (Size > rhs.Size)
	{
		BitMask temp(BitsNumber);
		for (size_t i = 0; i < rhs.Size; i++)
			temp.BitList[i] = BitList[i] ^ rhs.BitList[i];
		for (size_t i = rhs.Size; i < Size; i++)
			temp.BitList[i] = BitList[i] ^ ZERO;
		return temp;
	}
	else if (Size < rhs.Size)
	{
		BitMask temp(rhs.BitsNumber);
		for (size_t i = 0; i < Size; i++)
			temp.BitList[i] = BitList[i] ^ rhs.BitList[i];
		for (size_t i = Size; i < rhs.Size; i++)
			temp.BitList[i] = rhs.BitList[i] ^ ZERO;
		return temp;
	}
	return BitMask(0);
}

BitMask BitMask::operator&(const BitMask rhs) const
{
	if (Size == rhs.Size)
	{
		BitMask temp(BitsNumber);
		for (size_t i = 0; i < Size; i++)
			temp.BitList[i] = BitList[i] & rhs.BitList[i];
		return temp;
	}
	else if (Size > rhs.Size)
	{
		BitMask temp(BitsNumber);
		for (size_t i = 0; i < rhs.Size; i++)
			temp.BitList[i] = BitList[i] & rhs.BitList[i];
		for (size_t i = rhs.Size; i < Size; i++)
			temp.BitList[i] = BitList[i] & ZERO;
		return temp;
	}
	else if (Size < rhs.Size)
	{
		BitMask temp(rhs.BitsNumber);
		for (size_t i = 0; i < Size; i++)
			temp.BitList[i] = BitList[i] & rhs.BitList[i];
		for (size_t i = Size; i < rhs.Size; i++)
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


bool BitMask::Resize(int offset) 
{
	if (offset > 0)
	{
		if (BitsNumber + offset < Size*CHAR_BIT)
		{
			BitsNumber += offset;
		}
		else if (BitsNumber + offset > Size*CHAR_BIT)
		{
			BitsNumber += offset;
			//int times = (offset + BitsNumber - Size*CHAR_BIT) / CHAR_BIT + 1;
			size_t times = (((offset + BitsNumber) - Size*CHAR_BIT) / CHAR_BIT) + 1;
			for (size_t i = 0; i < times; i++)
				BitList.PushBack(ZERO);
			Size += times;
		}
		return true;
		//Czy BitsNumber+offset < Size*CHAR_BIT
		//Jesli tak to tylko BitsNumber+=offset;
		//Jesli nie to bitsnumber+=offset i BitList.pusback(0) tyle razy ile trzeba czyli 
		//offset/char_bit
		//BitsNumber += offset;
		/*
		int limit = 0;
		if (offset%CHAR_BIT)
			limit = offset / CHAR_BIT + 1;
		else
			limit = offset / CHAR_BIT;
		for (size_t i = 0; i < limit; i++)
			BitList.PushBack(0UL);
		Size += limit;
		return true;
		*/
	}
	if (offset < 0)
	{
		if (BitsNumber + offset > (Size - 1)*CHAR_BIT)
		{
			BitsNumber += offset;
		}
		else if (BitsNumber + offset < (Size - 1)*CHAR_BIT)
		{
			//int times = (offset + BitsNumber - (Size-1)*CHAR_BIT) / CHAR_BIT + 1;
			size_t times = ((Size - 1)*CHAR_BIT - (offset + BitsNumber)) / CHAR_BIT + 1;
			for (size_t i = 0; i < times; i++)
				BitList.PopBack();
			Size -= times;
			BitsNumber += offset;
		}
		return true;
		/*
		///Nie tak szybko!
		BitsNumber -= offset;
		int limit = 0;
		if (offset%CHAR_BIT)
			limit = offset / CHAR_BIT + 1;
		else
			limit = offset / CHAR_BIT;

		for (size_t i = 0; i < limit; i++)
			BitList.PopBack();

		Size -= limit;
		return true;
		*/
	}
	else
		return false;
}

size_t BitMask::BitListIndex(size_t index)
{
	if (index%CHAR_BIT)
		return index / CHAR_BIT;
	else
		return index / CHAR_BIT;
}

BitMask& BitMask::operator|=(const BitMask rhs)
{
	if (Size == rhs.Size)
	{
		for (size_t i = 0; i < Size; i++)
			BitList[i] |= rhs.BitList[i];
		return *this;
	}
	else if (Size > rhs.Size)
	{
		for (size_t i = 0; i < rhs.Size; i++)
			BitList[i] |= rhs.BitList[i];
		for (size_t i = rhs.Size; i < Size; i++)
			BitList[i] |= ZERO;
		return *this;
	}
	else if (Size < rhs.Size)
	{
		for (size_t i = 0; i < Size; i++)
			BitList[i] |= rhs.BitList[i];
		//size_t offset = 0;
		for (size_t i = 0; i < rhs.Size - Size; i++)
		{
			BitList.PushBack(ZERO);
			//offset+=CHAR_BIT;
		}
		for (size_t i = Size; i < rhs.Size; i++)
			BitList[i] |= ZERO;
		//Update of data quantity info changed in code above
		Size += rhs.Size;
		BitsNumber = rhs.BitsNumber - BitsNumber;
		return *this;
	}
	return *this;
}

BitMask& BitMask::operator^=(const BitMask rhs)
{
	if (Size == rhs.Size)
	{
		for (size_t i = 0; i < Size; i++)
			BitList[i] ^= rhs.BitList[i];
		return *this;
	}
	else if (Size > rhs.Size)
	{
		for (size_t i = 0; i < rhs.Size; i++)
			BitList[i] ^= rhs.BitList[i];
		for (size_t i = rhs.Size; i < Size; i++)
			BitList[i] ^= ZERO;
		return *this;
	}
	else if (Size < rhs.Size)
	{
		for (size_t i = 0; i < Size; i++)
			BitList[i] ^= rhs.BitList[i];
		size_t offset = 0;
		for (size_t i = 0; i < rhs.Size - Size; i++)
		{
			BitList.PushBack(ZERO);
			offset+=CHAR_BIT;
		}
		for (size_t i = Size; i < rhs.Size; i++)
			BitList[i] ^= ZERO;
		//Update of data quantity info changed in code above
		Size += offset;
		BitsNumber = rhs.BitsNumber - BitsNumber;
		return *this;
	}
	return *this;
}

BitMask& BitMask::operator&=(const BitMask rhs)
{
	if (Size == rhs.Size)
	{
		for (size_t i = 0; i < Size; i++)
			BitList[i] &= rhs.BitList[i];
		return *this;
	}
	else if (Size > rhs.Size)
	{
		for (size_t i = 0; i < rhs.Size; i++)
			BitList[i] &= rhs.BitList[i];
		for (size_t i = rhs.Size; i < Size; i++)
			BitList[i] &= ZERO;
		return *this;
	}
	else if (Size < rhs.Size)
	{
		for (size_t i = 0; i < Size; i++)
			BitList[i] &= rhs.BitList[i];
		size_t offset = 0;
		for (size_t i = 0; i < rhs.Size - Size; i++)
		{
			BitList.PushBack(ZERO);
			offset+=CHAR_BIT;
		}
		for (size_t i = Size; i < rhs.Size; i++)
			BitList[i] &= ZERO;
		//Update of data quantity info changed in code above
		Size += offset;
		BitsNumber = rhs.BitsNumber - BitsNumber;
		return *this;
	}
	return *this;
}

bool BitMask::operator==(const BitMask rhs) const
{
	if (Size!=rhs.Size)
		return false;

	if (Size == rhs.Size)
	{
		for (size_t i = 0; i < Size; i++)
			if (BitList[i] != rhs.BitList[i])
				return false;
		return true;
	}
	return false;
}