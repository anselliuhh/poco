//
// StringTest.h
//
// $Id: //poco/1.4/Foundation/testsuite/src/StringTest.h#1 $
//
// Definition of the StringTest class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef StringTest_INCLUDED
#define StringTest_INCLUDED


#include "Poco/Foundation.h"
#include "CppUnit/TestCase.h"
#include "Poco/NumericString.h"
#include "Poco/MemoryStream.h"


class StringTest: public CppUnit::TestCase
{
public:
	StringTest(const std::string& name);
	~StringTest();

	void testTrimLeft();
	void testTrimLeftInPlace();
	void testTrimRight();
	void testTrimRightInPlace();
	void testTrim();
	void testTrimInPlace();
	void testToUpper();
	void testToLower();
	void testIcompare();
	void testTranslate();
	void testTranslateInPlace();
	void testReplace();
	void testReplaceInPlace();
	void testCat();

	void testStringToInt();
	void testStringToFloat();
	void testStringToFloatError();
	void testNumericLocale();
	void benchmarkStrToFloat();
	void benchmarkStrToInt();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:

	template <typename T>
	void stringToInt()
	{
		T result = 0;
		if (123 <= std::numeric_limits<T>::max())
			assert(strToInt("123", result, 10)); assert(result == 123);
		
		assert(strToInt("0", result, 10)); assert(result == 0);
		assert(strToInt("000", result, 10)); assert(result == 0);
		
		if (123 < std::numeric_limits<T>::max())
			{ assert(strToInt("  123  ", result, 10)); assert(result == 123); }
		if (123 < std::numeric_limits<T>::max())
			{ assert(strToInt(" 123", result, 10)); assert(result == 123); }
		if (123 < std::numeric_limits<T>::max())
			{ assert(strToInt("123 ", result, 10)); assert(result == 123); }
		if (std::numeric_limits<T>::is_signed && (-123 > std::numeric_limits<T>::min()))
			{ assert(strToInt("-123", result, 10)); assert(result == -123); }
		if (0x123 < std::numeric_limits<T>::max())
			{ assert(strToInt("123", result, 0x10)); assert(result == 0x123); }
		if (0x12ab < std::numeric_limits<T>::max())
			{ assert(strToInt("12AB", result, 0x10)); assert(result == 0x12ab); }
		if (0x12ab < std::numeric_limits<T>::max())
			{ assert(strToInt("0X12AB", result, 0x10)); assert(result == 0x12ab); }
		if (0x12ab < std::numeric_limits<T>::max())
			{ assert(strToInt("0x12AB", result, 0x10)); assert(result == 0x12ab); }
		if (0x12ab < std::numeric_limits<T>::max())
			{ assert(strToInt("0x12aB", result, 0x10)); assert(result == 0x12ab); }
		if (0x98fe < std::numeric_limits<T>::max())
			{ assert(strToInt("0X98Fe", result, 0x10)); assert(result == 0x98fe); }
		if (123 < std::numeric_limits<T>::max())
			{ assert(strToInt("0x0", result, 0x10)); assert(result == 0); }
		if (123 < std::numeric_limits<T>::max())
			{ assert(strToInt("00", result, 0x10)); assert(result == 0); }
		if (0123 < std::numeric_limits<T>::max())
			{ assert(strToInt("123", result, 010));  assert(result == 0123); }
		if (0123 < std::numeric_limits<T>::max())
			{ assert(strToInt("0123", result, 010)); assert(result == 0123); }
		
		assert(strToInt("0", result, 010)); assert(result == 0);
		assert(strToInt("000", result, 010)); assert(result == 0);
	}

	template <typename T>
	bool parseStream(const std::string& s, T& value)
	{
		Poco::MemoryInputStream istr(s.data(), s.size());
#if !defined(POCO_NO_LOCALE)
		istr.imbue(std::locale::classic());
#endif
		istr >> value;
		return istr.eof() && !istr.fail();
	}

};


#endif // StringTest_INCLUDED
