/*========================================================
* AssignmentDescriptor.h
* @author Sergey Mikhtonyuk
* @date 09 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _ASSIGNMENTDESCRIPTOR_H__
#define _ASSIGNMENTDESCRIPTOR_H__

#include "TypeDescriptor.h"

namespace Reflection
{

	/// Describes the custom assignment logic of type
	/** @ingroup Reflection */
	class AssignmentDescriptor : public TypeDescriptor
	{
	public:
		typedef void (*TAssign)(void* a, void* b);

		AssignmentDescriptor(TAssign assign, UserType* owner)
			: TypeDescriptor(RL_DESC_SERVICE_ASSIGN, owner, "<assign desc>"),
			mAsssign(assign)
		{
		}

		/// Calls the assignment
		void Assign(void* a, void* b) const
		{
			mAsssign(a, b);
		}

	private:
		TAssign mAsssign;
	};
} // namespace


#endif // _ASSIGNMENTDESCRIPTOR_H__
