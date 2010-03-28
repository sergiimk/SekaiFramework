/*========================================================
* IfThenElse.h
* @author Sergey Mikhtonyuk
* @date 05 April 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _IFTHENELSE_H__
#define _IFTHENELSE_H__

//////////////////////////////////////////////////////////////////////////

/// IfThenElse template for compile-time choice between types
/** @ingroup Common */
template<bool COND, class T, class F>
struct if_then_else { typedef void value; };

template<class T, class F>
struct if_then_else<true, T, F> { typedef T value; };

template<class T, class F>
struct if_then_else<false, T, F> { typedef F value; };

//////////////////////////////////////////////////////////////////////////

/// IfThenElseInt template for compile-time choice between integral values
/** @ingroup Common */
template<bool COND, int T, int F>
struct if_then_else_int { static const int value = -1; };

template<int T, int F>
struct if_then_else_int<true, T, F> { static const int value = T; };

template<int T, int F>
struct if_then_else_int<false, T, F> { static const int value = F; };

//////////////////////////////////////////////////////////////////////////

#endif // _IFTHENELSE_H__
