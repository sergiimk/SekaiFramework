#ifndef _DELEGATE_CONFIG_H__
#define _DELEGATE_CONFIG_H__

#include <memory.h> // to allow <,> comparisons

////////////////////////////////////////////////////////////////////////////////
//						Configuration options
//
////////////////////////////////////////////////////////////////////////////////

// Defines the maximum invoke arguments of delegate
static const int MAX_INVOKE_ARGS = 5;

// Uncomment the following #define for optimally-sized DELEGATEs.
// In this case, the generated asm code is almost identical to the code you'd get
// if the compiler had native support for DELEGATEs.
// It will not work on systems where sizeof(dataptr) < sizeof(codeptr). 
// Thus, it will not work for DOS compilers using the medium model.
// It will also probably fail on some DSP systems.
#define FASTDELEGATE_USESTATICFUNCTIONHACK

// Uncomment the next line to allow function declarator syntax.
// It is automatically enabled for those compilers where it is known to work.
//#define FASTDELEGATE_ALLOW_FUNCTION_TYPE_SYNTAX

////////////////////////////////////////////////////////////////////////////////
//						Compiler identification for workarounds
//
////////////////////////////////////////////////////////////////////////////////

// Compiler identification. It's not easy to identify Visual C++ because
// many vendors fraudulently define Microsoft's identifiers.
#if defined(_MSC_VER) && !defined(__MWERKS__) && !defined(__VECTOR_C) && !defined(__ICL) && !defined(__BORLANDC__)
#	define FASTDLGT_ISMSVC
#endif

// Does the compiler uses Microsoft's member function pointer structure?
// If so, it needs special treatment.
// Metrowerks CodeWarrior, Intel, and CodePlay fraudulently define Microsoft's 
// identifier, _MSC_VER. We need to filter Metrowerks out.
#if defined(_MSC_VER) && !defined(__MWERKS__)
#define FASTDLGT_MICROSOFT_MFP

#if !defined(__VECTOR_C)
// CodePlay doesn't have the __single/multi/virtual_inheritance keywords
#define FASTDLGT_HASINHERITANCE_KEYWORDS
#endif
#endif

// Does it allow function declarator syntax? The following compilers are known to work:
#if defined(FASTDLGT_ISMSVC) && (_MSC_VER >=1310) // VC 7.1
#	define FASTDELEGATE_ALLOW_FUNCTION_TYPE_SYNTAX
#endif

// Gcc(2.95+), and versions of Digital Mars, Intel and Comeau in common use.
#if defined (__DMC__) || defined(__GNUC__) || defined(__ICL) || defined(__COMO__)
#	define FASTDELEGATE_ALLOW_FUNCTION_TYPE_SYNTAX
#endif

// It works on Metrowerks MWCC 3.2.2. From boost.Config it should work on earlier ones too.
#if defined (__MWERKS__)
#	define FASTDELEGATE_ALLOW_FUNCTION_TYPE_SYNTAX
#endif

#ifdef __GNUC__ // Workaround GCC bug #8271 
// At present, GCC doesn't recognize constness of MFPs in templates
#	define FASTDELEGATE_GCC_BUG_8271
#endif

#endif //_DELEGATE_CONFIG_H__
