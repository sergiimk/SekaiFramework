/*========================================================
* Platform.h
* @author Sergey Mikhtonyuk
* @date 23 April 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _ENVIRONMENTDEFS_H__
#define _ENVIRONMENTDEFS_H__

#include <cassert>
#include <cstddef>

/* This file provides useful definitions about the environment of project */

//////////////////////////////////////////////////////////////////////////
// Compiler
//////////////////////////////////////////////////////////////////////////

#if defined		(__GNUC__) || defined(__MINGW32__)
	#define COMPILER_GNUC		// GCC compiler

#elif defined	(_MSC_VER)
	#define COMPILER_MSC		// Microsoft compiler

#elif defined	(__ICL)
	#define COMPILER_INTEL		// Intel compiler

#elif defined	(__BORLANDC__)
	#define COMPILER_BORLAND	// Borland compiler

#elif defined (__COMO__)
	#define COMPILER_COMEAU		// Comeau compiler

#elif defined (__SUNPRO_CC)
	#define COMPILER_SUN		// Sun compiler

#else
	#error Unknown comiler

#endif

//////////////////////////////////////////////////////////////////////////
// Compiler-specific
//////////////////////////////////////////////////////////////////////////

#if defined (COMPILER_MSC)
    #define ALIGN_PROLOG(a) __declspec(align(a))
    #define ALIGN_EPILOG(a)
#elif defined (COMPILER_GNUC)
    #define ALIGN_PROLOG(a)
    #define ALIGN_EPILOG(a) __attribute__((aligned(a)))
#endif

//////////////////////////////////////////////////////////////////////////
// OS
//////////////////////////////////////////////////////////////////////////

#if defined	(WIN32) || defined (WIN64)
	#define OS_WINDOWS			// Windows

#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
	#define OS_MACOSX			// Mac OS X

#elif defined(linux) || defined(__linux) || defined(__linux__)
	#define OS_LINUX			// Linux

#else
	#error Unknown OS

#endif

//////////////////////////////////////////////////////////////////////////
// Standard library
//////////////////////////////////////////////////////////////////////////
//#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
//	#define STDLIB_STLPORT			// STLPort
//#elif defined(__LIBCOMO__)
//	#define STDLIB_COMEAU			// Comeau STL
//#elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
//	#  define STDLIB_GNU			// GNU libstdc++ 3
//#endif

// No autodetection for now
#if defined (COMPILER_MSC)
#	define STDLIB_STLPORT
#elif defined (COMPILER_GNUC)
#	define STDLIB_GNU
#endif


//////////////////////////////////////////////////////////////////////////
// Processor architecture
//////////////////////////////////////////////////////////////////////////
#if defined (OS_WINDOWS)
	#if defined(_M_X64)
		#define PROCARCH_X86_64
	#elif defined(_M_IA64)
		#define PROCARCH_IA64
	#elif defined(_M_IX86)
		#define PROCARCH_X86
	#else
		#error Unknown processor architecture
	#endif

#elif defined (OS_LINUX)
	#if __x86_64__
		#define PROCARCH_X86_64
	#elif __ia64__
		#define PROCARCH_IA64
	#elif __i386__ || __i386
		#define PROCARCH_X86
	#else
		#error Unknown processor architecture
	#endif

#elif defined (OS_MACOSX)
	#if __x86_64__
		#define PROCARCH_X86_64
	#elif __ia64__
		#define PROCARCH_IA64
	#elif __i386__ || __i386
		#define PROCARCH_X86
	#else
		#error Unknown processor architecture
#endif

#else
	#error Add means to determine architecture on other OSes

#endif


//////////////////////////////////////////////////////////////////////////
// Data model
//////////////////////////////////////////////////////////////////////////
#if defined (PROCARCH_X86)
	#define DATAMODEL_ILP32		// sizeof( int, long, void* ) == 4

#else
	#if defined (OS_WINDOWS)
		#define DATAMODEL_LLP64	// sizeof( long long, void* ) == 8

	#elif defined (OS_LINUX)
		#define DATAMODEL_LP64	// sizeof( long, long long, void* ) == 8

    #elif defined (OS_MACOSX)
		#define DATAMODEL_LP64

	#else
		#error Undefined data model

	#endif
#endif


//////////////////////////////////////////////////////////////////////////
// Instruction set
//////////////////////////////////////////////////////////////////////////
#if defined (COMPILER_MSC) && !defined(__SSE__)

	#define __SSE__
	#define __SSE2__

#endif


//////////////////////////////////////////////////////////////////////////
// Debugging
//////////////////////////////////////////////////////////////////////////

// This assertion will cause debug versions to crash if parameter is false
#define ASSERT_STRICT(x) assert(x)

// This type of assertions is used when some error appear that can be
// properly processed by the engine, so it is possible to safely remove it in
// most of build types
#define ASSERT_SOFT(x) assert(x)

#define NOT_IMPLEMENTED() assert(false); throw __FUNCTION__;

#endif // _ENVIRONMENTDEFS_H__
