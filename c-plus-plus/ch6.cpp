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



/*
* 6.2.4 Integer Types (pg. 144)
* -----------------------------
*/
void ch6_2_4()
{
	// Integers come in three forms:
	int a = 1; // the default/plain form that is always signed (chars are default unsigned)
	signed int b = 2;
	unsigned int c = 3;

	// Integers come in four sizes
	short int d = 4;
	int e = 5;
	long int f = 6;
	long long int g = 7;

	// (shorthand examples)
	short h = 8;
	signed i = 9;
	unsigned j = 10;
	//long short is not an option for int

	// More explicit and detailed integer sizes can be accessed using aliases from <cstdint>. This contains sections for ints of different sizes, the fastest type available, integers with at least a certain size, and an unsigned version of those as well
	// For reference, visit: https://en.cppreference.com/w/cpp/header/cstdint
}



/*
* 6.2.4.1 Integer Literals (pg. 145)
* ----------------------------------
* Integer literals come in the forms of decimals, octals, and hexadecimals
*/
void ch6_2_4_1()
{
	// decimals
	int dec = 1234567890; // standard usage
	// octals
	int oct = 0123; // starts with a '0' and not followed by an 'x' or 'X'
	// hexadecimal
	int hex = 0x3e; // starts with '0x' or '0X'

	// Note: a number that is too large to represent should present a warning, but an error is only thrown with the {}-initializer
	int not_the_safest_initializer = 12345678901234567890123456789012345678901234567890;
	int use_this_initializer{ 12345678901234567890123456789012345678901234567890 };

	// The U and L suffixes are used to denote unsigned and long integers, respectively
	int un_signed = 24U;
	int long_int = 24L;
	int unsigned_and_long = 24UL;
	// These are helpful when the underlying integer implementation may be unknown or had an odd default state
}



/*
* 6.2.4.2 Types of Integer Literals (pg. 146)
* -------------------------------------------
* (direct paragraph from the section):
* If it is decimal and has no suffix, it has the first of these types in which its value can be represented: int, long int, long long int.
* If it is octal or hexadecimal and has no suffix, it has the first of these types in which its value can be represented: int, unsigned int, long int, unsigned long int, long long int, unsigned long long int.
* If it is suffixed by u or U, its type is the first of these types in which its value can be represented: unsigned int, unsigned long int, unsigned long long int.
* If it is decimal and suffixed by l or L, its type is the first of these types in which its value can be represented: long int, long long int.
* If it is octal or hexadecimal and suffixed by l or L, its type is the first of these types in which
its value can be represented: long int, unsigned long int, long long int, unsigned long long int.
* If it is suffixed by ul, lu, uL, Lu, Ul, lU, UL, or LU, its type is the first of these types in which its value can be represented: unsigned long int, unsigned long long int.
* If it is decimal and is suffixed by ll or LL, its type is long long int.
* If it is octal or hexadecimal and is suffixed by ll or LL, its type is the first of these types in which its value can be represented: long long int, unsigned long long int.
* If it is suffixed by llu, llU, ull, Ull, LLu, LLU, uLL, or ULL, its type is unsigned long long int.
*/



/*
* 6.2.5 Floating-Point Types (pg. 146)
* ------------------------------------
*/
void ch6_2_5()
{
	// Floating-points come in three forms:
	float a; // single precision
	double b; // double precision
	long double c; // extended precision
	// The exact definitions for each of these is implementation defined. If the situation truly matters which type of floating-point type is used, then a deep and extensive knowledge of floating-point computation is required. In the words of Stroustrup: "If you don’t have that understanding, get advice, take the time to learn, or use double and hope for the best."
}



/*
* 6.2.5.1 Floating-Point Literals (pg. 146)
* -----------------------------------------
* By default, a floating-point literal is of type double
* Provided examples (pg. 147): 1.23 .23 0.23 1. 1.0 1.2e10 1.23e-15
* Note: There cannot be any gaps/spaces in floating-point literals, even after the 'e' character
*/



/*
* 6.2.6 Prefixes and Suffixes (pg. 147)
* -------------------------------------
* This is dense, so here it is straight from the section:
* 
* ============= Arithmetic Literal Prefixes and Suffixes =============
* --------------------------------------------------------------------
* Notation     *fix    Meaning         Example  Reference  ISO
* --------------------------------------------------------------------
* 0            prefix  octal           0776     §6.2.4.1   §iso.2.14.2
* 0x or 0X     prefix  hexadecimal     0xff     §6.2.4.1   §iso.2.14.2
* u or U       suffix  hexadecimal     10U      §6.2.4.1   §iso.2.14.2
* l or L       suffix  long            20000L   §6.2.4.1   §iso.2.14.2
* ll or LL     suffix  long long       20000LL  §6.2.4.1   §iso.2.14.2
* f or F       suffix  float           10f      §6.2.5.1   §iso.2.14.4
* e or E       infix   floating-point  10e-4    §6.2.5.1   §iso.2.14.4
* .            infix   floating-point  12.3     §6.2.5.1   §iso.2.14.4
* --------------------------------------------------------------------
* '            prefix  char            'c'      §6.2.3.2   §iso.2.14.3
* u'           prefix  char16_t        u'c'     §6.2.3.2   §iso.2.14.3
* U'           prefix  char32_t        U'c'     §6.2.3.2   §iso.2.14.3
* L'           prefix  wchar_t         L'c'     §6.2.3.2   §iso.2.14.3
* --------------------------------------------------------------------
* "            prefix  string          "mess"   §7.3.2     §iso.2.14.5
* R"           prefix  raw string      R"(\b)"  §7.3.2.1   §iso.2.14.5
* u8" or u8R"  prefix  UTF-8 string    u8"foo"  §7.3.2.2   §iso.2.14.5
* u" or uR"    prefix  UTF-16 string   u"foo"   §7.3.2.2   §iso.2.14.5
* U" or UR"    prefix  UTF-32 string   U"foo"   §7.3.2.2   §iso.2.14.5
* L" or LR"    prefic  wchar_t string  L"foo"   §7.3.2.2   §iso.2.14.5
* ====================================================================
* 
* There are a few other outstanding instances not represented in the chart such as using the l/L and u/U suffixes together to represent an unsigned long or unsinged long long. The L suffix can also be paired with a floating-point literal to signify a long double, for example
* 
* Note that the u/U prefix has a very different meaning depending whether it is applies to a char or a string literal
*/



/*
* 6.2.7 Void (pg. 148)
* --------------------
* There are no objects of type void, rather it is used to represent the absence of a value
*/
void ch6_2_7()
{
	//void a; // error, there is not such thing as a void object
	//void& b;// error, there cannot be references to void
	void f(); // a function that returns nothing
	void* c; // pointer to an object of unknown type
}



/*
* 6.2.8 Sizes (pg. 148)
* ---------------------
* Stroustrup makes an excellent point stating that anyone who does not view their program with the possibility of it being ported to another system is shortsighted: "If your program is a success, it will be ported, so someone will have to find and fix problems related to implementation-dependent features". It is easier to think ahead and find solutions to these sorts of problems as you develop rather than to complete a project only to had to dig back through it later to fix bugs. It is far more efficient to address these issues as they arise.
* 
* Keeping track of sizes in C++ is done in terms of the char, which is of size 1. This can be done using the sizeof operator
* 
* These are the guarantees about the fundamental types (pg. 149-150):
* 1 == sizeof(char) <= sizeof(short) <= sizeof(int) <= sizeof(long) <= sizeof(long long)
* 1 <= sizeof(bool) <= sizeof(long)
* sizeof(char) <= sizeof(wchar_t) <= sizeof(long)
* sizeof(float) <= sizeof(double) <= sizeof(long double)
* sizeof(N) == sizeof(signed N) == sizeof(unsigned N), where N can be char, short, int, long, or long long
* char is at least 8 bits
* short is at least 16 bits
* long is at least 32 bits
*/
void ch6_2_8()
{
	// Keep in mind sizeof is an operator, not a function
	int size = sizeof(int); // implementation defined, but can be found using this operator
}



/*
* 6.2.9 Alignment (pg. 151)
* -------------------------
* From the section (pg. 151):
* An object doesn’t just need enough storage to hold its representation. In addition, on some machine architectures, the bytes used to hold it must have proper alignment for the hardware to access it efficiently (or in extreme cases to access it at all). For example, a 4-byte int often has to be aligned on a word (4-byte) boundary, and sometimes an 8-byte double has to be aligned on a word (8-byte) boundary.
* 
* The alignof operator returns the alignment of the argument
*/
void ch6_2_9()
{
	int a = 1;
	auto alignment = alignof(a);
	// alignment in declarations is sometimes needed. In this case, there is the type specifier alignas(T) which reads as: "align just like a T" where T is a type
}



/*
* 6.3 Declarations (pg. 151)
* --------------------------
* Before a name/identifier can be used in C++, it needs to be declared. This means that it needs to have a specified type so that the compiler knows what kind of entity it is.
*/