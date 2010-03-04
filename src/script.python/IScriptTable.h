/*========================================================
* IScriptTable.h
* @author Sergey Mikhtonyuk
* @date 31 Jan 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _ISCRIPTTABLE_H__
#define _ISCRIPTTABLE_H__

#include "module/interfaces.h"
#include "reflection/types/Type.h"

namespace Script
{
	/// Represent abstract script table (a set of key-value pairs)
	/** @ingroup Script */
	sf_interface IScriptTable : public Module::IUnknown
	{
		sf_uuid("26e96cb7-d5f9-4364-86ec-c415157ceac9")

		template<typename T>
		bool HasEntry(T attr_key)
		{
			Reflection::ValueTypePair pair = Reflection::make_typed_pair(attr_key);
			return HasEntryRaw(pair);
		}

		template<typename KT, typename VT>
		bool GetEntry(KT attr_key, VT& out_val)
		{
			Reflection::ValueTypePair keyPair = Reflection::make_typed_pair(attr_key);
			Reflection::ValueTypePair valuePair = Reflection::make_typed_pair(out_val);
			return GetEntryRaw(keyPair, valuePair);
		}

		/// Determines if table has entry by specified key
		virtual bool HasEntryRaw(const Reflection::ValueTypePair& attr_key) = 0;

		/// Fetches entry value by specified key
		/** @return 'true' indicates success */
		virtual bool GetEntryRaw(const Reflection::ValueTypePair& attr_key, Reflection::ValueTypePair& out_val) = 0;
	};
}

#endif //_ISCRIPTTABLE_H__
