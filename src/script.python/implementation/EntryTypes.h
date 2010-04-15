/*========================================================
* EntryTypes.h
* @author Sergey Mikhtonyuk
* @date 05 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _ENTRYTYPES_H__
#define _ENTRYTYPES_H__

namespace ScriptPy
{
	//////////////////////////////////////////////////////////////////////////

	class CScriptManager;
	class CScriptModule;

	//////////////////////////////////////////////////////////////////////////

	const int _EntNameBufLen = 100;
	const int _EntHeader = 0xaaaaaaaa;

	//////////////////////////////////////////////////////////////////////////

	/// Stores info about type exported to script
	/** @ingroup Py */
	struct ExportEntry
	{
		int								_header;

		/// Name of the exported type
		char							Name[_EntNameBufLen];

		/// Full name of the exported type
		//char							FullName[_EntNameBufLen];
		
		/// Type of the class
		const reflection::user_type*	Type;

		/// Corresponding class object in script
		PyTypeObject					ClassObj;

		/// Module that exported this type
		CScriptModule*					Module;

		/// Entry of the base class
		ExportEntry*					BaseType;


		ExportEntry() 
		{
			_header = _EntHeader;
			memset(&ClassObj, 0, sizeof(PyTypeObject)); 
		}
	};

	//////////////////////////////////////////////////////////////////////////

	/// Defines the type of object instance
	/** @ingroup Py */
	enum InstanceType
	{
		SIT_NONE,		///< Used when object don't need associated instance (like for built-in types)
		SIT_OWNED,		///< Objects created inside of the script and managed by it
		SIT_SHARED,		///< Objects returned to the script with lifetime controlled by application
	};

	//////////////////////////////////////////////////////////////////////////

	/// Describes properties of the object instance
	/** @ingroup Py */
	struct InstanceObject
	{
		PyObject_HEAD
		void*									instance;
		InstanceType							inst_type;
		const reflection::construct_attribute*	ctor;
		ExportEntry*							object_type;
		PyObject*								inst_dictionary;
	};

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _ENTRYTYPES_H__
