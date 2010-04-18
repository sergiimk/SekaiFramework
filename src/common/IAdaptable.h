/*========================================================
* IAdaptable.h
* @author Sergey Mikhtonyuk
* @date 23 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#ifndef _IADAPTABLE_H__
#define _IADAPTABLE_H__

#include "module/interfaces.h"

/// IAdaptable interface
/** This interface is a base of "Extension Object" pattern
  * that allows:
  * - to add a service interface to a type without exposing it in that type;
  * - to add behavior to preexisting types.
  *
  * Adapters are the wrapper classes that extend the functionality of the wrapped object.
  * They are similar to tear-off interfaces but simpler, because QueryInterface symmetric rule
  * can be ignored.
  *
  * @ingroup Extensions */
sf_interface IAdaptable : public module::IUnknown
{
    sf_uuid("f7c5f5ea-33ed-48e8-8823-5904da2cf6fa")

    /// Returns the adapter of the object if it exist
    virtual module::HResult GetAdapter(SF_RIID iid, module::IUnknown** ppv) = 0;
};

#endif // _IADAPTABLE_H__
