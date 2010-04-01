
//////////////////////////////////////////////////////////////////////////
#define MAKE_DELEG()		Delegate<FT>* pdeleg = static_cast<Delegate<FT>*>(deleg)
#define MAKE_DELEGM()		MAKE_DELEG(); \
							FunctionData fd = pdeleg->GetFunctionData(); \
							fd.SetThisPtr(reinterpret_cast<detail::GenericClass*>(*(void**)args[0])); \
							pdeleg->SetFunctionData(fd);
#define MAKE_CALL			(*pdeleg)
#define UNPCK_ARG(T, ARG)	(*(T*)args[ARG])
#define UNPCK_RET()			(*(RT*)res)
#define UNPCK_RET_REF()		(*(RT**)res)

//////////////////////////////////////////////////////////////////////////

template<class FT, class RT>
void invoke_generic(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET() = MAKE_CALL(); }

template<class FT, class RT>
void invoke_generic_ref(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET_REF() = &MAKE_CALL(); }

template<class FT>
void invoke_generic_noret(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); MAKE_CALL(); }

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class RT>
void invoke_generic(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 0)); }

template<class FT, class A1, class RT>
void invoke_generic_ref(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 0)); }

template<class FT, class A1>
void invoke_generic_noret(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); MAKE_CALL(UNPCK_ARG(A1, 0)); }

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class RT>
void invoke_generic(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1)); }

template<class FT, class A1, class A2, class RT>
void invoke_generic_ref(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1)); }

template<class FT, class A1, class A2>
void invoke_generic_noret(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1)); }

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class A3, class RT>
void invoke_generic(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2)); }

template<class FT, class A1, class A2, class A3, class RT>
void invoke_generic_ref(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2)); }

template<class FT, class A1, class A2, class A3>
void invoke_generic_noret(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2)); }

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class A3, class A4, class RT>
void invoke_generic(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2), UNPCK_ARG(A4, 3)); }

template<class FT, class A1, class A2, class A3, class A4, class RT>
void invoke_generic_ref(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2), UNPCK_ARG(A4, 3)); }

template<class FT, class A1, class A2, class A3, class A4>
void invoke_generic_noret(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2), UNPCK_ARG(A4, 3)); }

//////////////////////////////////////////////////////////////////////////

template<class FT, class RT>
void invoke_generic_m(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET() = MAKE_CALL();
}

template<class FT, class RT>
void invoke_generic_m_ref(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET_REF() = &MAKE_CALL();
}

template<class FT>
void invoke_generic_m_noret(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	MAKE_CALL();
}

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class RT>
void invoke_generic_m(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 1));
}

template<class FT, class A1, class RT>
void invoke_generic_m_ref(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 1));
}

template<class FT, class A1>
void invoke_generic_m_noret(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	MAKE_CALL(UNPCK_ARG(A1, 1));
}

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class RT>
void invoke_generic_m(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2));
}

template<class FT, class A1, class A2, class RT>
void invoke_generic_m_ref(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2));
}

template<class FT, class A1, class A2>
void invoke_generic_m_noret(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2));
}

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class A3, class RT>
void invoke_generic_m(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3));
}

template<class FT, class A1, class A2, class A3, class RT>
void invoke_generic_m_ref(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3));
}

template<class FT, class A1, class A2, class A3>
void invoke_generic_m_noret(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3));
}

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class A3, class A4, class RT>
void invoke_generic_m(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3), UNPCK_ARG(A4, 4));
}

template<class FT, class A1, class A2, class A3, class A4, class RT>
void invoke_generic_m_ref(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3), UNPCK_ARG(A4, 4));
}

template<class FT, class A1, class A2, class A3, class A4>
void invoke_generic_m_noret(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3), UNPCK_ARG(A4, 4));
}
