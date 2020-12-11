/* 6.1 The ISO Standard (pg. 135)
* -------------------------------
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


/* 6.1.1 Implementations (pg. 137)
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











int main()
{
	return 0;
}