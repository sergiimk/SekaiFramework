/*========================================================
* guid.h
* @author Sergey Mikhtonyuk
* @date 23 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _SF_GUID_H__
#define _SF_GUID_H__

#include "module_fwd.h"
#include <memory.h>
#include <iosfwd>


namespace module
{

	//////////////////////////////////////////////////////////////////////////


	/// guid structure
	/** Used to uniquely identify interface between modules
	 *  @ingroup module */
	struct MODULE_API guid
	{
		//@{
		/** Data fields */
		unsigned long  data1;
		unsigned short data2;
		unsigned short data3;
		unsigned char  data4[ 8 ];
		//@}

		/// Comparison operator
		bool operator == (const guid& rhs) const
		{
			return data1 == rhs.data1
				&& data2 == rhs.data2
				&& data3 == rhs.data3
				&& memcmp(data4, rhs.data4, sizeof(char)*8) == 0;
		}

		/// Comparison operator
		bool operator != (const guid& rhs) const
		{
			return !(this->operator ==(rhs));
		}

		/// Comparison operator
		bool operator < (const guid& rhs) const
		{
			// If guid first components are not equal -> return their comparison result
			// Otherwise, proceed to the next component pair
			// Continue for all components of guid
			if( data1 != rhs.data1 )
			{
				return data1 < rhs.data1;
			}

			if ( data2 != rhs.data2 )
			{
				return data2 < rhs.data2;
			}

			if ( data3 != rhs.data3 )
			{
				return data3 < rhs.data3;
			}

			for(int i = 0; i < 8; ++i)
			{
				if ( data4[i] != rhs.data4[i] )
					return data4[i] < rhs.data4[i];
			}

			// Guids are equal
			return false;
		}

		/// Sets data to zero
		void reset()
		{
			memset(this, 0, sizeof(guid));
		}

		/// Checks is guid is zero
		bool is_reset() const
		{
			guid zero;
			zero.reset();
			return *this == zero;
		}

		operator bool() const { return !is_reset(); }

		/// Parses the guid string
		bool parse(const char* s);

		/// Buffer must be 37 bytes long
		void to_string(char* buf) const;

		/// Constructs guid from string
		/** @return zero guid if failed */
		static guid guid_from_string(const char* s)
		{
			guid g;
			g.reset();
			g.parse(s);
			return g;
		}
	};

	//////////////////////////////////////////////////////////////////////////

	MODULE_API std::ostream& operator<<(std::ostream& os, const guid& g);

	MODULE_API std::istream& operator>>(std::istream& is, guid& g);

	//////////////////////////////////////////////////////////////////////////

	//@{
	/** Utils */

	/// Safe way to pass interface and void**
	#define UUID_PPV(infc, pp) uuid_of(infc), reinterpret_cast<void**>(static_cast<infc**>(pp))

	//@}

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _module_GUID_H__
