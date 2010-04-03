/*========================================================
* GUID.h
* @author Sergey Mikhtonyuk
* @date 23 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _SF_GUID_H__
#define _SF_GUID_H__

#include <memory.h>
#include <iosfwd>


namespace Module
{

	//////////////////////////////////////////////////////////////////////////


	/// GUID structure
	/** Used to uniquely identify interface between modules
	 *  @ingroup Module */
	struct GUID
	{
		//@{
		/** Data fields */
		unsigned long  Data1;
		unsigned short Data2;
		unsigned short Data3;
		unsigned char  Data4[ 8 ];
		//@}

		/// Comparison operator
		bool operator == (const Module::GUID& rhs) const
		{
			return Data1 == rhs.Data1
				&& Data2 == rhs.Data2
				&& Data3 == rhs.Data3
				&& memcmp(Data4, rhs.Data4, sizeof(char)*8) == 0;
		}

		/// Comparison operator
		bool operator != (const Module::GUID& rhs) const
		{
			return !(this->operator ==(rhs));
		}

		/// Comparison operator
		bool operator < (const Module::GUID& rhs) const
		{
			// If GUID first components are not equal -> return their comparison result
			// Otherwise, proceed to the next component pair
			// Continue for all components of GUID
			if( Data1 != rhs.Data1 )
			{
				return Data1 < rhs.Data1;
			}

			if ( Data2 != rhs.Data2 )
			{
				return Data2 < rhs.Data2;
			}

			if ( Data3 != rhs.Data3 )
			{
				return Data3 < rhs.Data3;
			}

			for(int i = 0; i < 8; ++i)
			{
				if ( Data4[i] != rhs.Data4[i] )
					return Data4[i] < rhs.Data4[i];
			}

			// Guids are equal
			return false;
		}

		/// Sets data to zero
		void SetZero()
		{
			memset(this, 0, sizeof(Module::GUID));
		}

		/// Checks is GUID is zero
		bool IsZero() const
		{
			GUID zero;
			zero.SetZero();
			return *this == zero;
		}

		/// Parses the GUID string
		bool FromString(const char* s);

		/// Buffer must be 37 bytes long
		void ToString(char* buf) const;

		/// Constructs GUID from string
		/** @return zero guid if failed */
		static GUID GUIDFromString(const char* s)
		{
			GUID g;
			g.SetZero();
			g.FromString(s);
			return g;
		}
	};

	//////////////////////////////////////////////////////////////////////////

	std::ostream& operator<<(std::ostream& os, const GUID& guid);

	std::istream& operator>>(std::istream& is, GUID& guid);

	//////////////////////////////////////////////////////////////////////////


	//@{
	/** Type masks */
	#define SF_IID  Module::GUID
	#define SF_RIID const Module::GUID&
	//@}


	//////////////////////////////////////////////////////////////////////////

	//@{
	/** Utils */

	/// Safe way to pass interface and void**
	#define UUID_PPV(infc, pp) uuid_of(infc), reinterpret_cast<void**>(static_cast<infc**>(pp))

	//@}

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _Module_GUID_H__
