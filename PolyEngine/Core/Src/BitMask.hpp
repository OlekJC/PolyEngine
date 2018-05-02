#pragma once

#include "Dynarray.hpp"

namespace Poly {
	class CORE_DLLEXPORT BitMask
	{
	public:
		using DataType = unsigned char;

		BitMask(size_t size = sizeof(DataType));		///Tested

		//Bitwise operators
		BitMask operator|(const BitMask& rhs) const;	///Tested
		BitMask operator^(const BitMask& rhs) const;	///Tested
		BitMask operator&(const BitMask& rhs) const;	///Tested
		BitMask& operator~();							///Tested
		//Assignment bitwise operators
		BitMask& operator|=(const BitMask& rhs);		//Done			//Przepisaæ BitsNumbery!!
		BitMask& operator^=(const BitMask& rhs);		//To be done	//Przepisaæ BitsNumbery!!
		BitMask& operator&=(const BitMask& rhs);		//Done			//Przepisaæ BitsNumbery!!
		

		bool operator==(const BitMask rhs) const;	//Done
		bool operator!=(const BitMask rhs) const	//Done
		{ return !(*this == rhs); }
		bool operator[](size_t index) const;

		//Set,Reset and toggle bits methods
		bool Set(size_t index, bool state);			///Tested
		bool Reset();								///Tested
		bool Toggle(size_t index);					///Tested
		
		bool Resize(const int offset = 0);				//


		size_t GetSize() { return BitsNumber; }
		size_t GetDynarraySize() { return BitList.GetSize(); }
	private:
		inline bool RangeCheck(size_t index);
		inline size_t BitListIndex(size_t index);

		Dynarray<DataType> BitList;
		size_t BitsNumber = 0;				//How many bits are in the class
	};
}