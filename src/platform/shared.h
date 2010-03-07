/*========================================================
* shared.h
* @author Sergey Mikhtonyuk
* @date 07 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _SHARED_H__
#define _SHARED_H__

#include "platform.h"

#ifdef OS_WINDOWS
	#include <windows.h>
	void* Sekai_LoadLibrary(const char* name) { return LoadLibraryExA(name, 0, 0); }
	void* Sekai_GetProcAddress(void* library, const char* name) { return GetProcAddress((HMODULE)library, name); }
	void Sekai_FreeLibrary(void* library) { FreeLibrary((HMODULE)library); }
#else
	#include <dlfcn.h>
	void* Sekai_LoadLibrary(const char* name) { return dlopen(name, RTLD_NOW); }
	void* Sekai_GetProcAddress(void* library, const char* name) { return dlsym(library, name); }
	void* Sekai_FreeLibrary(void* library) { return (void*)dlclose(library); }
#endif

#endif //_SHARED_H__
