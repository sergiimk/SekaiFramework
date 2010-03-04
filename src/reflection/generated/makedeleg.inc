
//////////////////////////////////////////////////////////////////////////

template <class FT>
DelegateBase* MakeGenericDelegate(FT* func) 
{ return new Delegate<FT>(func); }


//////////////////////////////////////////////////////////////////////////

template <class C, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)())
{ return new Delegate<RT ()>((C*)0, func); }

template <class C, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)() const)
{ return new Delegate<RT ()>((C*)0, func); }


//////////////////////////////////////////////////////////////////////////

template <class C, class A1, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)(A1))
{ return new Delegate<RT (A1)>((C*)0, func); }

template <class C, class A1, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)(A1) const)
{ return new Delegate<RT (A1)>((C*)0, func); }


//////////////////////////////////////////////////////////////////////////

template <class C, class A1, class A2, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)(A1, A2))
{ return new Delegate<RT (A1, A2)>((C*)0, func); }

template <class C, class A1, class A2, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)(A1, A2) const)
{ return new Delegate<RT (A1, A2)>((C*)0, func); }


//////////////////////////////////////////////////////////////////////////

template <class C, class A1, class A2, class A3, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)(A1, A2, A3))
{ return new Delegate<RT (A1, A2, A3)>((C*)0, func); }

template <class C, class A1, class A2, class A3, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)(A1, A2, A3) const)
{ return new Delegate<RT (A1, A2, A3)>((C*)0, func); }


//////////////////////////////////////////////////////////////////////////

template <class C, class A1, class A2, class A3, class A4, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)(A1, A2, A3, A4))
{ return new Delegate<RT (A1, A2, A3, A4)>((C*)0, func); }

template <class C, class A1, class A2, class A3, class A4, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)(A1, A2, A3, A4) const)
{ return new Delegate<RT (A1, A2, A3, A4)>((C*)0, func); }


//////////////////////////////////////////////////////////////////////////

template <class C, class A1, class A2, class A3, class A4, class A5, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)(A1, A2, A3, A4, A5))
{ return new Delegate<RT (A1, A2, A3, A4, A5)>((C*)0, func); }

template <class C, class A1, class A2, class A3, class A4, class A5, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)(A1, A2, A3, A4, A5) const)
{ return new Delegate<RT (A1, A2, A3, A4, A5)>((C*)0, func); }


//////////////////////////////////////////////////////////////////////////

template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)(A1, A2, A3, A4, A5, A6))
{ return new Delegate<RT (A1, A2, A3, A4, A5, A6)>((C*)0, func); }

template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)(A1, A2, A3, A4, A5, A6) const)
{ return new Delegate<RT (A1, A2, A3, A4, A5, A6)>((C*)0, func); }


//////////////////////////////////////////////////////////////////////////

template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)(A1, A2, A3, A4, A5, A6, A7))
{ return new Delegate<RT (A1, A2, A3, A4, A5, A6, A7)>((C*)0, func); }

template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)(A1, A2, A3, A4, A5, A6, A7) const)
{ return new Delegate<RT (A1, A2, A3, A4, A5, A6, A7)>((C*)0, func); }


//////////////////////////////////////////////////////////////////////////

template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)(A1, A2, A3, A4, A5, A6, A7, A8))
{ return new Delegate<RT (A1, A2, A3, A4, A5, A6, A7, A8)>((C*)0, func); }

template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)(A1, A2, A3, A4, A5, A6, A7, A8) const)
{ return new Delegate<RT (A1, A2, A3, A4, A5, A6, A7, A8)>((C*)0, func); }

