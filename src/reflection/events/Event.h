/*========================================================
* Event.h
* @author Sergey Mikhtonyuk
* @date 20 September 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _EVENT_H__
#define _EVENT_H__

#include "../delegate/Delegate.h"
#include <vector>
#include <algorithm>

namespace Reflection
{
	//////////////////////////////////////////////////////////////////////////
	template <typename Signature>
	class Event;
	//////////////////////////////////////////////////////////////////////////

	template<typename RT>
	class Event<RT ()>
	{
		typedef RT ReturnType;
		typedef ReturnType (Signature)();
		typedef Delegate0<ReturnType> DelegateType;

	public:

		void connect(const DelegateType& deleg)
		{ mSubscribers.push_back(deleg); }

		void disconnect(const DelegateType& deleg)
		{ mSubscribers.erase( std::remove(mSubscribers.begin(), mSubscribers.end(), deleg), mSubscribers.end() ); }

		void raise() {
			size_t size = mSubscribers.size();
			for(size_t i = 0; i != size; ++i)
				mSubscribers[i]();
		}

	private:
		std::vector<DelegateType> mSubscribers;
	};

	//////////////////////////////////////////////////////////////////////////

	template<typename RT, typename A1>
	class Event<RT (A1)>
	{
		typedef RT ReturnType;
		typedef ReturnType (Signature)(A1);
		typedef Delegate1<A1, ReturnType> DelegateType;

	public:
		void connect(const DelegateType& deleg)
		{ mSubscribers.push_back(deleg); }

		void disconnect(const DelegateType& deleg)
		{ mSubscribers.erase( std::remove(mSubscribers.begin(), mSubscribers.end(), deleg), mSubscribers.end() ); }

		void raise(A1 arg1) {
			size_t size = mSubscribers.size();
			for(size_t i = 0; i != size; ++i)
				mSubscribers[i](arg1);
		}

	private:
		std::vector<DelegateType> mSubscribers;
	};

} // namespace

#endif // _EVENT_H__
