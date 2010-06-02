#ifndef _SF_DELEGATE_H__
#define _SF_DELEGATE_H__

namespace delegates
{

#include "delegate_config.h"
#include "delegate_utils.h"
#include "delegate_closure.h"
#include "delegate_delegn.h"

// Generate function-style delegate for zero-overhead and dynamic versions of delegates
#define FS_DELEGATE delegate
#define DELEGATE(n) delegate##n
#	include "delegate_funcstyle.h"
#undef FS_DELEGATE
#undef DELEGATE

// Generate both const and non-const versions of ordinary zero-overhead delegate makers
#define DELEG_CONST
#define DELEGATE(n) delegate##n
#define MAKE_DELEGATE make_delegate
#	include "delegate_makedeleg.h"
#undef DELEG_CONST
#define DELEG_CONST const
#	include "delegate_makedeleg.h"
#undef MAKE_DELEGATE
#undef DELEGATE
#undef DELEG_CONST

template<class FT>
delegate<FT> make_delegate(FT* f) {
	return delegate<FT>(f);
}

}

#endif //_SF_DELEGATE_H__