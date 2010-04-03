/*========================================================
* Maps.h
* @author Sergey Mikhtonyuk
* @date 24 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _SF_MAPS_H__
#define _SF_MAPS_H__

#include "interfaces.h"
#include "common/typetraits.h"

// Fwd for reflection export
namespace Reflection { class Type; };

namespace  Module
{
	/////////////////////////////////////////////////////////////////////////
	//  Interface map
	/////////////////////////////////////////////////////////////////////////

	namespace detail
	{

		/// Interface locator function type
		typedef HResult (*INTERFACE_LOCATOR_FUNC)(void *pThis, void* pChain, SF_RIID riid, void **ppv);

		/// Indicate entry is just offset 
		static const INTERFACE_LOCATOR_FUNC SF_OFFSET_ENTRY = (INTERFACE_LOCATOR_FUNC)1;



		/////////////////////////////////////////////////////////////////////////


		/// Interface entry in interface map
		struct INTERFACE_MAP_ENTRY
		{
			const SF_IID*			piid;		///< pointer to interface ID
			void*					OffChain;	///< offset of class from IUnknown or chain pointer
			INTERFACE_LOCATOR_FUNC	locator;	///< 0 - table end; 1 - offset entry; else - real locator
		};


		/////////////////////////////////////////////////////////////////////////


		/// Interface query chaining structure
		struct _CHAINDATA
		{
			size_t dwOffset;
			const INTERFACE_MAP_ENTRY* (*pFunc)();
		};


		/////////////////////////////////////////////////////////////////////////


		template <class base, class derived>
		class _ComChainData	{ public: static _CHAINDATA data; };

		template <class base, class derived>
		_CHAINDATA _ComChainData<base, derived>::data = {classoffset<base, derived>(), base::_GetEntries};


		/////////////////////////////////////////////////////////////////////////

	} // detail


	#define BEGIN_INTERFACE_MAP() public:																						\
	Module::IUnknown* GetUnknown() throw() {return (Module::IUnknown*)((size_t)this+(size_t)_GetEntries()->OffChain); }			\
	const static Module::detail::INTERFACE_MAP_ENTRY* _GetEntries() throw() {													\
	static const Module::detail::INTERFACE_MAP_ENTRY _entries[] = {

	/////////////////////////////////////////////////////////////////////////
	
	#define INTERFACE_ENTRY(intrfc)	\
	{&uuid_of(intrfc), (void*)classoffset<intrfc, _ThisClass>(), Module::detail::SF_OFFSET_ENTRY},

	/////////////////////////////////////////////////////////////////////////

	//#define INTERFACE_ENTRY_BRANCHED(intrfc, branch)
	//{&uuid_of(intrfc), static_cast<void*>(static_cast<intrfc*>(static_cast<branch*>(reinterpret_cast<_ThisClass*>(8))))-8, Module::detail::SF_OFFSET_ENTRY},

	/////////////////////////////////////////////////////////////////////////

	#define INTERFACE_ENTRY_CHAIN(baseclass)\
	{0, (void*)&Module::detail::_ComChainData<baseclass, _ThisClass>::data, Module::detail::_Chain},

	/////////////////////////////////////////////////////////////////////////

	#define END_INTERFACE_MAP()													\
	{0, 0, 0}}; return &_entries[0];}											\
	unsigned long AddRef() { return 1; }										\
	unsigned long Release() { return 1; }										\
	Module::HResult QueryInterface(SF_RIID iid, void **ppObject)				\
	{ return Module::detail::_QueryInterface(this, _GetEntries(), iid, ppObject); }



	/////////////////////////////////////////////////////////////////////////
	//  Module map implementation
	/////////////////////////////////////////////////////////////////////////

	#define DECLARE_IMPLEMENTATION(className)																		\
	DECLARE_IMPLEMENTATIONA(className, Module::NewAllocator)

	/////////////////////////////////////////////////////////////////////////

	#define DECLARE_IMPLEMENTATIONA(className, Allocator)															\
	DECLARE_IMPLEMENTATION2A(className, Allocator, Module::ComClassFactory)

	/////////////////////////////////////////////////////////////////////////

	#define DECLARE_IMPLEMENTATION2(className, factoryClass)														\
	DECLARE_IMPLEMENTATION2A(className, Module::NewAllocator, factoryClass)

	/////////////////////////////////////////////////////////////////////////

	#define DECLARE_IMPLEMENTATION2A(className, Allocator, factoryClass)											\
	public:																											\
	typedef className _ThisClass;																					\
	typedef Module::detail::ComObject<className, Allocator> _ObjectClass;											\
	typedef factoryClass< _ObjectClass > _FactoryClass;

	/////////////////////////////////////////////////////////////////////////

	#define DECLARE_IMPLEMENTATION_DERIVED(className, baseClassName)												\
	DECLARE_IMPLEMENTATION_DERIVED2(className, baseClassName, Module::ComClassFactory)

	/////////////////////////////////////////////////////////////////////////

	#define DECLARE_IMPLEMENTATION_DERIVED2(className, baseClassName, factoryClass)									\
	public:																											\
	typedef baseClassName _BaseClass;																				\
	typedef className _ThisClass;																					\
	typedef Module::detail::ComObject<className> _ObjectClass;														\
	typedef factoryClass< _ObjectClass > _FactoryClass;

	/////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// Module map
	//////////////////////////////////////////////////////////////////////////

	namespace detail
	{

		typedef HResult (CREATOR_FUNC)(SF_RIID riid, void** ppv);

		typedef Reflection::Type* (TYPE_OF_FUNC)();

		/// Object entry in module map
		struct MODULE_MAP_ENTRY
		{
			const GUID*			pClsid;
			const GUID*			pInterfaceId;
			TYPE_OF_FUNC*		pTypeOf;
			CREATOR_FUNC*		pCreateFactoryFn;
			IClassFactory*		pClassFactory;
		};

	} // detail


	/////////////////////////////////////////////////////////////////////////

	#define DECLARE_MODULE_MAP()																					\
	extern "C" SHARED_EXPORT Module::detail::MODULE_MAP_ENTRY* GetModuleMap();

	//////////////////////////////////////////////////////////////////////////

	#define BEGIN_MODULE_MAP()																						\
	extern "C" SHARED_EXPORT Module::detail::MODULE_MAP_ENTRY* GetModuleMap()										\
	{ static Module::detail::MODULE_MAP_ENTRY e[] = {

	/////////////////////////////////////////////////////////////////////////

	#define OBJECT_ENTRY(clssid, intrfID, clss)																		\
	{ &clssid, &intrfID, 0, Module::detail::ComObject<clss::_FactoryClass>::_CreateInstance, 0 },

	/////////////////////////////////////////////////////////////////////////

	#define OBJECT_ENTRY_REFLECTED(clssid, intrfID, clss, type_func)												\
	{ &clssid, &intrfID, type_func, Module::detail::ComObject<clss::_FactoryClass>::_CreateInstance, 0 },

	/////////////////////////////////////////////////////////////////////////

	#define END_MODULE_MAP()																						\
	{ 0, 0, 0, 0 } };																								\
	return e; }																										\
																													\
	extern "C" SHARED_EXPORT void ModuleInit() { }																	\
	extern "C" SHARED_EXPORT void ModuleShutdown()																	\
	{																												\
		Module::detail::MODULE_MAP_ENTRY* e = GetModuleMap();														\
		while(e->pClsid)																							\
		{																											\
			if(e->pClassFactory)																					\
			{																										\
				e->pClassFactory->Release();																		\
				e->pClassFactory = 0;																				\
			}																										\
			++e;																									\
		}																											\
	}

	/////////////////////////////////////////////////////////////////////////	

} // namespace

#endif // _SF_MAPS_H__
