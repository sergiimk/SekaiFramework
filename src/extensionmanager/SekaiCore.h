/*========================================================
* SekaiCore.h
* @author Sergey Mikhtonyuk
* @date 09 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
/** @defgroup Extensions Extensions
 *  Extension management facilities */

#ifndef _SEKAICORE_H__
#define _SEKAICORE_H__

#include "ICore.h"
#include "IPlugin.h"
#include "IPluginManager.h"
#include "IPluginShadow.h"
#include "IExtension.h"
#include "IStartListener.h"
#include "IExtensionPoint.h"
#include "logging/logging.h"

namespace Extensions
{
	// {654d7750-4574-4c6a-9393-b5fae3419621}
	const Module::GUID CLSID_CCore = { 0x654d7750, 0x4574, 0x4c6a, { 0x93, 0x93, 0xb5, 0xfa, 0xe3, 0x41, 0x96, 0x21 } };

} // namespace


/*! \mainpage Sekai Framework API Reference
*
* \section intro_sec Introduction
*
* Welcome to the Sekai Framework.
*
* Sekai Framework is a core functionality library for C++ that provides a lot
* of useful modules for advanced large-scale and modular application development.
*
*
* \section structure Structure
*
* The framework implementation intended to be highly modular. This means that all complete functionality
* will be packed into single module. This means that developer will be able to choose those modules
* he actually need in his application and leave the rest aside.
*
*
* \section modules Main modules
*
* Main set of modules includes:
* - Common library
* - Module library
* - Extension management module
* - Debugging module
* - Logging module
* - File system module
* - Reflection library
* - Script bindings generator
* - Unicode library
* - Threading library
* - Platform library
* - Serialization library
*
*
* \subsection module Module library
*
* This library is a heart of the framework. It provides means to seamlessly integrate modules (dlls)
* with each other. This library allows other modules to:
* - Define own interfaces wit unique IDs (GUID)
* - Define implementation classes
* - Query interface support by the class instance
* - Export implementation from module
* - Export classes with non-intrusive reference counting
* - Create implementation instances on-the-stack inside the module who provides them
* - Support different allocation policies for exported classes
* - Simplify reference counting by usage of smart pointers
*
*
* \subsection extensions Extension manager
*
* Extension management module allows to organize project into a plug-in-based system,
* where nearly any part of the system is a plug-in. The common tasks of this module are:
* - Allow modules to define extension points (where they can be extended by other modules)
* - Allow modules to extend specified extension points (own or other modules')
* - Create extension graph of the program at startup
* - Manage lifetimes of the modules
* - Support lazy loading of modules via creation indirection
* - Provide environment access to the modules
*
*
* \subsection debugging Debugging library
*
* This module provides multiple utilities for programmers to analyze program behavior,
* do defensive programming, inspect crashes etc. Main utilities are:
* - Assertions (SuperAssert style)
* - Call stack generation
* - Minidump generation
* - Exception interception (maybe some RTTI to translate exception names)
*
*
* \subsection logging Logging module
*
* Features:
* - Adjustable log details (both at compile-time and runtime)
* - Log listeners (for console output etc.)
* - Thread safe
*
*
* \subsection logging FileSystem module
*
* Cross-platform file system access library. Features:
* - Object model of file system
* - Seamless support of archives
* - Thread-safe
* - Async operation support
* - Supports unicode paths
*
*
* \subsection reflection Reflection library
*
* Reflection (introspection) library allows to add meta-info about any class and use it at runtime.
* It is also used in script binding generation, to expose classes to script. Features:
* - Non-intrusive (will allow to add reflection to third-party libraries)
* - Simple way to expose class members, methods, and accessors
* - Support of generic method invocation (like in C#, using an array of parameters)
* - Events
*
*
* \subsection script Script bindings generator
*
* This module allows to dynamically expose C++ types with reflection to the script language.
* This is very useful, because most of the not performance critical logic can bee easily
* scripted and will not require a recompilation on change.
*
* Currently, bindings are implemented for Python. Using Python bindings generator, user can inherit C++
* class in Python, override its methods etc. Bindings work both ways, this means that
* C++ side can operate on Python objects, call functions and modify variables.
* Stackless Python offers micro-threading solution to be used by the application.
*
*
* \subsection unicode Unicode library
*
* Unicode module can be a wrapped third-party solution (like ICU from IBM). It should provide:
* - Unicode strings (for a specified encoding type)
* - Conversions between formats
* - ...more to come...
*
*
* \subsection threading Threading library
*
* May be wait for C++0X ??
* - Task creation and scheduling
* - Atomic operations
* - Barriers
* - Synchronization primitives
*
*
* \subsection platform Platform library
*
* This library contains all needed to identify platform and compiler.
* Means to identify PC configuration, installed software etc.
*
*
* \subsection serialization Serialization library
*
* Serialization can be useful in lots of places. Primarily it can be used to save objects'
* states to the disk and load them afterwards. It is also useful in networking,
* when forming some XML or other requests.
*
*
*
* \section lic_sec License
*
* See LICENSE file for details
*
*
* \section contacts_sec Contacts:
*
* If you have any questions - mail me:
* Sergey Mikhtonyuk - mikhtonyuk@gmail.com
*
*/




#endif // _SEKAICORE_H__
