#pragma once

#include "Dynarray.hpp"
//#include "Defines.hpp"

namespace Poly {
	class CORE_DLLEXPORT BitMask
	{
		using DataType=unsigned char;
	public:
		BitMask(size_t size = sizeof(DataType));//Done

		//Overloading logical operators
		BitMask operator|(const BitMask rhs) const;	//Tested
		BitMask operator^(const BitMask rhs) const;	//Tested
		BitMask operator&(const BitMask rhs) const;	//Tested
		BitMask& operator~();						//Implemented, not tested
		/////////////////////////////////////////////////
		BitMask& operator|=(const BitMask rhs);		
		BitMask& operator^=(const BitMask rhs);
		BitMask& operator&=(const BitMask rhs);
		

		bool operator==(const BitMask rhs) const;	//Overloading == operator
		bool operator!=(const BitMask rhs) const 
		{ return !(*this == rhs); }
		bool operator[](size_t index);
		//BitMask& operator=(const BitMask&);		//Overloaded assignment operator
		//BitMask& operator=(const BitMask&&);		//Overloaded move operator
													//Set,Reset and toggle bits methods
		bool Set(int index, bool state);			//DONE
		bool Reset();								//Done, i think?
		bool Toggle(int index);						//DONE
		
		bool Resize(int offset = 0);				//DONE, not tested
		size_t GetSize() { return BitsNumber; }
		//////////////////////////////////////////////
		//size_t GetArraySize() { return Size; }
		size_t GetArraySize2() { return BitList.GetSize(); }
		//////////////////////////////////////////////
	private:
		inline bool RangeCheck(int index);
		inline size_t BitListIndex(size_t index);

		Dynarray<DataType> BitList;
		size_t BitsNumber = 0;				//How many bits are in the class
		size_t Size = 0;					//Size of BitList Dynarray
	};
}