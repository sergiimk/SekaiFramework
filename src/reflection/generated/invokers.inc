
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
void InvokeGeneric(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET() = MAKE_CALL(); }

template<class FT, class RT>
void InvokeGenericRef(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET_REF() = &MAKE_CALL(); }

template<class FT>
void InvokeGenericNoret(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); MAKE_CALL(); }

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class RT>
void InvokeGeneric(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 0)); }

template<class FT, class A1, class RT>
void InvokeGenericRef(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 0)); }

template<class FT, class A1>
void InvokeGenericNoret(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); MAKE_CALL(UNPCK_ARG(A1, 0)); }

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class RT>
void InvokeGeneric(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1)); }

template<class FT, class A1, class A2, class RT>
void InvokeGenericRef(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1)); }

template<class FT, class A1, class A2>
void InvokeGenericNoret(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1)); }

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class A3, class RT>
void InvokeGeneric(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2)); }

template<class FT, class A1, class A2, class A3, class RT>
void InvokeGenericRef(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2)); }

template<class FT, class A1, class A2, class A3>
void InvokeGenericNoret(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2)); }

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class A3, class A4, class RT>
void InvokeGeneric(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2), UNPCK_ARG(A4, 3)); }

template<class FT, class A1, class A2, class A3, class A4, class RT>
void InvokeGenericRef(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2), UNPCK_ARG(A4, 3)); }

template<class FT, class A1, class A2, class A3, class A4>
void InvokeGenericNoret(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2), UNPCK_ARG(A4, 3)); }

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class A3, class A4, class A5, class RT>
void InvokeGeneric(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2), UNPCK_ARG(A4, 3), UNPCK_ARG(A5, 4)); }

template<class FT, class A1, class A2, class A3, class A4, class A5, class RT>
void InvokeGenericRef(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2), UNPCK_ARG(A4, 3), UNPCK_ARG(A5, 4)); }

template<class FT, class A1, class A2, class A3, class A4, class A5>
void InvokeGenericNoret(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2), UNPCK_ARG(A4, 3), UNPCK_ARG(A5, 4)); }

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class A3, class A4, class A5, class A6, class RT>
void InvokeGeneric(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2), UNPCK_ARG(A4, 3), UNPCK_ARG(A5, 4), UNPCK_ARG(A6, 5)); }

template<class FT, class A1, class A2, class A3, class A4, class A5, class A6, class RT>
void InvokeGenericRef(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2), UNPCK_ARG(A4, 3), UNPCK_ARG(A5, 4), UNPCK_ARG(A6, 5)); }

template<class FT, class A1, class A2, class A3, class A4, class A5, class A6>
void InvokeGenericNoret(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2), UNPCK_ARG(A4, 3), UNPCK_ARG(A5, 4), UNPCK_ARG(A6, 5)); }

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class RT>
void InvokeGeneric(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2), UNPCK_ARG(A4, 3), UNPCK_ARG(A5, 4), UNPCK_ARG(A6, 5), UNPCK_ARG(A7, 6)); }

template<class FT, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class RT>
void InvokeGenericRef(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2), UNPCK_ARG(A4, 3), UNPCK_ARG(A5, 4), UNPCK_ARG(A6, 5), UNPCK_ARG(A7, 6)); }

template<class FT, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
void InvokeGenericNoret(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2), UNPCK_ARG(A4, 3), UNPCK_ARG(A5, 4), UNPCK_ARG(A6, 5), UNPCK_ARG(A7, 6)); }

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class RT>
void InvokeGeneric(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2), UNPCK_ARG(A4, 3), UNPCK_ARG(A5, 4), UNPCK_ARG(A6, 5), UNPCK_ARG(A7, 6), UNPCK_ARG(A8, 7)); }

template<class FT, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class RT>
void InvokeGenericRef(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2), UNPCK_ARG(A4, 3), UNPCK_ARG(A5, 4), UNPCK_ARG(A6, 5), UNPCK_ARG(A7, 6), UNPCK_ARG(A8, 7)); }

template<class FT, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
void InvokeGenericNoret(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); MAKE_CALL(UNPCK_ARG(A1, 0), UNPCK_ARG(A2, 1), UNPCK_ARG(A3, 2), UNPCK_ARG(A4, 3), UNPCK_ARG(A5, 4), UNPCK_ARG(A6, 5), UNPCK_ARG(A7, 6), UNPCK_ARG(A8, 7)); }

//////////////////////////////////////////////////////////////////////////

template<class FT, class RT>
void InvokeGenericM(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET() = MAKE_CALL();
}

template<class FT, class RT>
void InvokeGenericMRef(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET_REF() = &MAKE_CALL();
}

template<class FT>
void InvokeGenericMNoret(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	MAKE_CALL();
}

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class RT>
void InvokeGenericM(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 1));
}

template<class FT, class A1, class RT>
void InvokeGenericMRef(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 1));
}

template<class FT, class A1>
void InvokeGenericMNoret(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	MAKE_CALL(UNPCK_ARG(A1, 1));
}

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class RT>
void InvokeGenericM(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2));
}

template<class FT, class A1, class A2, class RT>
void InvokeGenericMRef(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2));
}

template<class FT, class A1, class A2>
void InvokeGenericMNoret(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2));
}

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class A3, class RT>
void InvokeGenericM(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3));
}

template<class FT, class A1, class A2, class A3, class RT>
void InvokeGenericMRef(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3));
}

template<class FT, class A1, class A2, class A3>
void InvokeGenericMNoret(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3));
}

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class A3, class A4, class RT>
void InvokeGenericM(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3), UNPCK_ARG(A4, 4));
}

template<class FT, class A1, class A2, class A3, class A4, class RT>
void InvokeGenericMRef(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3), UNPCK_ARG(A4, 4));
}

template<class FT, class A1, class A2, class A3, class A4>
void InvokeGenericMNoret(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3), UNPCK_ARG(A4, 4));
}

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class A3, class A4, class A5, class RT>
void InvokeGenericM(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3), UNPCK_ARG(A4, 4), UNPCK_ARG(A5, 5));
}

template<class FT, class A1, class A2, class A3, class A4, class A5, class RT>
void InvokeGenericMRef(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3), UNPCK_ARG(A4, 4), UNPCK_ARG(A5, 5));
}

template<class FT, class A1, class A2, class A3, class A4, class A5>
void InvokeGenericMNoret(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3), UNPCK_ARG(A4, 4), UNPCK_ARG(A5, 5));
}

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class A3, class A4, class A5, class A6, class RT>
void InvokeGenericM(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3), UNPCK_ARG(A4, 4), UNPCK_ARG(A5, 5), UNPCK_ARG(A6, 6));
}

template<class FT, class A1, class A2, class A3, class A4, class A5, class A6, class RT>
void InvokeGenericMRef(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3), UNPCK_ARG(A4, 4), UNPCK_ARG(A5, 5), UNPCK_ARG(A6, 6));
}

template<class FT, class A1, class A2, class A3, class A4, class A5, class A6>
void InvokeGenericMNoret(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3), UNPCK_ARG(A4, 4), UNPCK_ARG(A5, 5), UNPCK_ARG(A6, 6));
}

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class RT>
void InvokeGenericM(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3), UNPCK_ARG(A4, 4), UNPCK_ARG(A5, 5), UNPCK_ARG(A6, 6), UNPCK_ARG(A7, 7));
}

template<class FT, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class RT>
void InvokeGenericMRef(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3), UNPCK_ARG(A4, 4), UNPCK_ARG(A5, 5), UNPCK_ARG(A6, 6), UNPCK_ARG(A7, 7));
}

template<class FT, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
void InvokeGenericMNoret(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3), UNPCK_ARG(A4, 4), UNPCK_ARG(A5, 5), UNPCK_ARG(A6, 6), UNPCK_ARG(A7, 7));
}

//////////////////////////////////////////////////////////////////////////

template<class FT, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class RT>
void InvokeGenericM(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET() = MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3), UNPCK_ARG(A4, 4), UNPCK_ARG(A5, 5), UNPCK_ARG(A6, 6), UNPCK_ARG(A7, 7), UNPCK_ARG(A8, 8));
}

template<class FT, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class RT>
void InvokeGenericMRef(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET_REF() = &MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3), UNPCK_ARG(A4, 4), UNPCK_ARG(A5, 5), UNPCK_ARG(A6, 6), UNPCK_ARG(A7, 7), UNPCK_ARG(A8, 8));
}

template<class FT, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
void InvokeGenericMNoret(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	MAKE_CALL(UNPCK_ARG(A1, 1), UNPCK_ARG(A2, 2), UNPCK_ARG(A3, 3), UNPCK_ARG(A4, 4), UNPCK_ARG(A5, 5), UNPCK_ARG(A6, 6), UNPCK_ARG(A7, 7), UNPCK_ARG(A8, 8));
}
