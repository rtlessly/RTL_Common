#ifndef _RTL_Stdlib_h_
#define _RTL_Stdlib_h_

#include <inttypes.h>
#include <Streaming.h>
#include <pins_arduino.h>


/*******************************************************************************
 Macro to "stringize" a macro parameter
*******************************************************************************/
#define __Stringizer__(x) #x
#define Stringize(x) __Stringizer__(x)

/*******************************************************************************
 Helper macros for storing class name in PROGMEM (for debugging)
*******************************************************************************/
#define DECLARE_CLASSNAME public: static const __FlashStringHelper* _classname_;
#define DEFINE_CLASSNAME(ClassName) static const char ClassName##_classname_[] PROGMEM = Stringize(ClassName); \
                                    const __FlashStringHelper* ClassName::_classname_ = (const __FlashStringHelper*) ClassName##_classname_;

/*******************************************************************************
 Helper macro for converting a pointer to uint32_t
*******************************************************************************/
#define PTR(x) (reinterpret_cast<uint32_t>(x))

/*******************************************************************************
 Helper macros for arrays
*******************************************************************************/

//******************************************************************************
/// Get the length of an array. 
/// - Assumes that arr is an actual array and not a pointer
//******************************************************************************
#define ARRAY_LENGTH(arr) (sizeof(arr)/sizeof(*arr))

//******************************************************************************
/// Initializes all element of an array to the same value. 
/// - Assumes that arr is an actual array and not a pointer
/// - Assumes that the array element has an assignment operator (operator=) defined 
///   for typeof(value)
//******************************************************************************
#define INIT_ARRAY(arr, value) if (true) { for (int i=0; i < ARRAY_LENGTH(arr); arr[i++] = value);} else (void)0

//******************************************************************************
/// Initializes all element of an array to zero. 
/// - Assumes that arr is an actual array and not a pointer
/// - Assumes that the array element has an assignment operator (operator=) 
///   defined for a numeric type (int, long, etc...)
//******************************************************************************
#define ZERO_ARRAY(arr) if (true) { for (int i=0; i < ARRAY_LENGTH(arr); arr[i++] = 0);} else (void)0

//******************************************************************************
/// Initializes all element of an array to their default value. 
/// - Assumes that arr is an actual array and not a pointer
/// - Assumes that the array element has a default no-arg constructor
/// - Assumes that the array element has a default assignment operator
//******************************************************************************
#define DEFAULT_ARRAY(arr) if (true) { for (int i=0; i < ARRAY_LENGTH(arr); Default(arr[i++]));} else (void)0

//******************************************************************************
/// Returns the last valid index value for the array. 
/// - Assumes that arr is an actual array and not a pointer
//******************************************************************************
#define LAST_INDEX(arr) (ARRAY_LENGTH(arr)-1)

//******************************************************************************
/// Returns the last element in the array. 
/// - Assumes that arr is an actual array and not a pointer
//******************************************************************************
#define LAST_ELEMENT(arr) arr[LAST_INDEX(arr)]

//******************************************************************************
/// Shifts all elements of the array 1 position to the left (toward the first element).
/// The prior first element is lost as a result of this operation. 
/// - Assumes that arr is an actual array and not a pointer
/// - Assumes that a copy assignment operator exists for array elements
//******************************************************************************
#define SHIFT_ARRAY_LEFT(arr) if (true) { for (int i=1; i < ARRAY_LENGTH(arr); arr[i-1] = arr[i], i++);} else (void)0

//******************************************************************************
/// Shifts all elements of the array 1 position to the right (toward the last element). 
/// The prior last element is lost as a result of this operation. 
/// - Assumes that arr is an actual array and not a pointer
/// - Assumes that a copy assignment operator exists for array elements
//******************************************************************************
#define SHIFT_ARRAY_RIGHT(arr) if (true) { for (int i=0; i < LAST_INDEX(arr); arr[i+1] = arr[i], i++);} else (void)0

//******************************************************************************
/// Copies all elements of the srce array to the dest array. 
/// - Assumes that the srce array is an actual array and not a pointer
/// - The dest argument can be an actual array or a pointer
/// - Assumes that the srce and dest arrays are the same size and type (or compatible
///   types)
/// - Assumes that a copy assignment operator exists for array elements
//******************************************************************************
#define COPY_ARRAY(dest, srce) if (true) { for (int i=0; i < ARRAY_LENGTH(srce); i++) dest[i] = srce[i];} else (void)0

//******************************************************************************
/// Copies all elements of the srce array to the dest array, where srce array variable
/// is a pointer (so array length cannot be implicitly determined). 
/// - Both srce and dest arguments can be an actual array or a pointer
/// - Assumes that the srce and dest arrays are the same type (or compatible types)
/// - Assumes that the srce and dest arrays are the size specified by length argument
/// - Assumes that a copy assignment operator exists for array elements
//******************************************************************************
#define COPY_ARRAY_PTR(dest, srce, length) if (true) { for (int i=0; i < length; i++) dest[i] = srce[i];} else (void)0


/*******************************************************************************
 Handy functions
 Some are dups of what is available in the STL but this avoids the STL overhead
*******************************************************************************/

//******************************************************************************
/// Swaps the value  of 2 instances of type T
/// - Assumes that type T has a copy constructor
/// - Assumes that type T has a default assignment operator
//******************************************************************************
template <typename T> inline void swap(T& lhs, T& rhs) { T temp(lhs); lhs = rhs; rhs = temp; };

//******************************************************************************
/// Sets an instance of type T to its default value
/// - Assumes that type T has a default no-arg constructor
/// - Assumes that type T has a default assignment operator
//******************************************************************************
template <typename T> inline void Default(T& a) { T b(); a = b; };


/*******************************************************************************
 Handy macro-based functions 
*******************************************************************************/

//******************************************************************************
/// Determines if the value y is between the values x and z (inclusive). 
/// - Assumes that value, lower, and upper are of compatible types
/// - Assumes operator <= is defined for value, lower, and upper, and 
///   conveys the conventional meaning
//******************************************************************************
#define between(lower, value, upper) ((lower) <= (value) && (value) <= (upper))

//******************************************************************************
/// Determines if a value is between the lower and upper values (exclusive). 
/// - Assumes that value, lower, and upper are of compatible types
/// - Assumes operator < is defined for value, lower, and upper, and 
///   conveys the conventional meaning
//******************************************************************************
#define inside(lower, value, upper) ((lower) < (value) && (value) < (upper))

//******************************************************************************
/// Determines if a value is outside of the values lower and upper (exclusive). 
/// - Assumes that value, lower, and upper are of compatible types
/// - Assumes operator < is defined for value, lower, and upper, and 
///   conveys the conventional meaning
//******************************************************************************
#define outside(value, lower, upper) ((value) < (lower) || (upper) < (value))


#include "RTL_Debug.h"

#endif
