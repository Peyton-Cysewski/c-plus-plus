/*
* 6.1 The ISO Standard (pg. 135)
* ------------------------------
* "The C++ language and standard library are defined by their ISO standard: ISO/IEC 14882:2011. In
* this book, references to the standard are of the form §iso.23.3.6.1." (pg. 135)
* 
* For the most specific, accurate, and up-to-date information on the language, visit: https://isocpp.org/std/the-standard
*/

// implemetation-defined vs well defined
void ch6_1()
{
	// Stroustrup uses this example to show the potentially varying behaviors (pg. 136):

	unsigned char c1 = 64; // well defined: a char has at least 8 bits and can always hold 64
	unsigned char c2 = 1256; // implementation-defined: truncation if a char has only 8 bits

	// Where possible, it is wise to make very clear that a program is relying on implementation-defined behavior
}



/*
* 6.1.1 Implementations (pg. 137)
* -------------------------------
* Implementations can be either freestanding or hosted
* 
* hosted: includes all standared-library facilities
* freestanding: can include fewer standard-library facilities, meant for code that needs very little operating system support, requires these headers: (p. 137)
* 
* Purpose                         Header
* Types                           <cstddef>
* Implementation properties       <cfloat> <limits> <climits>
* Integer types                   <cstdint>
* Start and termination           <cstdlib>
* Dynamic memory management       <new>
* Type identification             <typeinfo>
* Exception handling              <exception>
* Initializer lists               <initializer_list>
* Other run-time support          <cstdalign> <cstdarg> <cstdbool>
* Type traits                     <type_traits>
* Atomics                         <atomic>
* 
* 
* Note: there are also non-standard options for using even less for extremely minimal programs
*/



/*
* 6.1.2 The Basic Source Character Set (pg. 137)
* ----------------------------------------------
* Writing C++ source code uses the ASCII character set
* 
* There are (atypical) ways to use an extended character set as an alternative. See: §6.2.3.2
*/



/*
* 6.2 Types (pg. 138)
* -------------------
* Knowing types and their behaviors is fundamental aspect of being able to read and write C++ code
*/



/*
* 6.2.1 Fundamental Types (pg. 138)
* ---------------------------------
* Fundamental types correspond to the most basic ways to store data on a computer:
*/
void ch6_2_1()
{
	bool b;       // A Boolean type
	char c;       // Character types
	int i;        // Integer types
	double db;    // Floating-point types
	void;         // A void type (signifying the absence of information)

	// From the above types there can be constructed:
	int* p = &i;  // Pointer types
	char arr[10]; // Array types
	int& r = i;   // Reference types
}
/*
* The Boolean, character, and integer types are "integral types"
* The integral and floating-point types are "arithmetic types"
* These fundamental types as well as pointers and references are "built-in types"
* Enumerations and classes are "user-defined types"
* 
* Note: the standard library provides many user-defined types despite it being tempting to consider all those as built-in
*/



/*
*  6.2.2 Booleans (pg. 139)
*/
void ch6_2_2()
{
	// Booleans can be "true" or "false":
	bool t = true;
	bool f = false;

	// Used to express the result of logical operations:
	bool logical_result = (t == f); // false

	// By definition true == 1 and false == 0 (any non-zero number including negatives will convert to true)
	int t1 = true; // 1
	int t2 {true}; // 1
	int f1 = false; // 0
	int f2 {false}; // 0

	bool b1 = 7; // true
	bool b2 = -7; // true
	//bool b2 {7}; // narrowing error

	// Converted to ints in arithmetic and logical operations
	bool b3 = b1 + b2; // 1 + 1 is non-zero therfore it evaluates to true

	// Non-null pointers evaluate to true, Null pointers evaluate to false
	int num = 5; // int variable
	int* num_ptr1 = &num; // pointer to variable
	int* num_ptr2 = nullptr; // pointer to null
	bool b_ptr = num_ptr1; // true
	bool n_b_ptr = num_ptr2; // false
}



/*
* 6.2.3 Character Types (pg. 140)
* -------------------------------
* C++ uses a variety of different character set encodings that can quickly become confusing
*/
void ch6_2_3()
{
	char c; // The default character type, uses the implementation's character set, usually 8 bits
	signed char sc; // Like char, but guaranteed to be signed and capable of holding positives and negatives
	unsigned char uc; // Like char, but guaranteed to be unsigned
	wchar_t wc; // Can hold characters of larger character sets like Unicode, implementation-defined, can hold as many characters as needed for a given locale
	char16_t c16; // Holds 16-bit character sets like UTF-16
	char32_t c32; // Holds 32-bit character sets like UTF-32

	/* Unsafe char assumptions (pg. 141):
	* -----------------------------------
	* There are no more than 127 characters in an 8-bit character set (e.g., some sets provide 255 characters)
	* There are no more alphabetic characters than English provides (most European languages provide more)
	* The alphabetic characters are contiguous (EBCDIC leaves a gap between 'i' and 'j')
	* Every character used to write C++ is available (e.g., some national character sets do not provide {, }, [, ], |, and \)
	* A char fits in 1 byte. There are embedded processors without byte accessing hardware for which a char is 4 bytes. Also, one could reasonably use a 16-bit Unicode encoding for the basic chars.
	*/

	// *Note* (pg. 141-142): a char being a default signed char or unsigned char is implementations specific. This can lead to a variety of potential portability problems. C++ allows unsigned chars to represent 0 to 255, but only allows signed chars to represent -127 to 127 NOT -128. This has to do with C++ leaving space open for 1's complement hardware. The safest thing to do is work within the range of 0 to 127.

	// Character types are integral types, so arithmetic and bitwise logical operators apply to them:
	char c1 = 'e';
	int char_plus_int = c1 + 5;
	int shifted_char = c1 << 2;
}



/*
* 6.2.3.1 Signed and Unsigned Characters (pg. 142)
* ------------------------------------------------
* The nature of implementation-defined chars can have some unpredictable behavior
*/
void ch6_2_3_1()
{
	// Example from page 142:
	char c = 255; // 255 is "all ones," hexadecimal 0xFF
	int i = c;

	// If c is unsigned, it will remain as it looks and be 255
	// If c is signed, the "all ones" corresponds to -1
	// It is best to be explicit with the definition of the char

	// Another example from page 142:
	char c = 1;
	signed char sc = 1;
	unsigned char uc = 1;

	//char* pc = &uc; // error : no pointer conversion
	//signed char* psc = pc; // error : no pointer conversion
	//unsigned char* puc = pc; // error : no pointer conversion
	//psc = puc; // error : no pointer conversion
}



/*
* 6.2.3.2 Character Literals (pg. 143)
* ------------------------------------
* A character literal is a single character in in single quotes: 'c'
*/
void ch6_2_3_2()
{
	// Character literals can be represented by the character itself or by decimal, hexadecimal, or octal
	char itself = 'c';
	char decimal = 99;
	char hexadecimal = '\x63'; // syntax is '\xhhh'
	char octal = '\143'; // syntax is '\ooo'
	// these all represent the same thing
	// Note: it is possible to enclose more than 1 character in the single quotes, but such use is "archaic"

	// When embedding these representations into a string, use:
	// 3 digits for octals
	// 2 digits for hexadecimals
	char s1[] = "\111\003\102";
	char s2[] = "\xff\x0e\xd4";

	// Wide character literals are of the type wchar_t and are denoted with an 'L' prefix:
	wchar_t w = L'ol';

	// Larger character sets such as Unicode can have literals denoted by the form U'\UXXXXXXXX':
	char32_t uni1 = U'\UABCDEFAB';
	char32_t uni2 = u'\U0000ABCD'; // only uses 16 bits so there is a shorter form
	char16_t uni3 = u'\xABCD'; //  the 'x' is equivalent to '0000'
	// Note: the 'U' and 'u' are interchangeable prefixes
}