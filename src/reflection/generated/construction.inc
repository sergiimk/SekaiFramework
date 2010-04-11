
template<class T, template<typename> class Alloc> 
inline void* type_ctor()
{
	Alloc<T> a; void* p = a.allocate(1);
	new(p) T;
	return p;
}


template<class T, template<typename> class Alloc, class A1> 
inline void* type_ctor(A1 a1)
{
	Alloc<T> a; void* p = a.allocate(1);
	new(p) T(a1);
	return p;
}


template<class T, template<typename> class Alloc, class A1, class A2> 
inline void* type_ctor(A1 a1, A2 a2)
{
	Alloc<T> a; void* p = a.allocate(1);
	new(p) T(a1, a2);
	return p;
}


template<class T, template<typename> class Alloc, class A1, class A2, class A3> 
inline void* type_ctor(A1 a1, A2 a2, A3 a3)
{
	Alloc<T> a; void* p = a.allocate(1);
	new(p) T(a1, a2, a3);
	return p;
}


template<class T, template<typename> class Alloc, class A1, class A2, class A3, class A4> 
inline void* type_ctor(A1 a1, A2 a2, A3 a3, A4 a4)
{
	Alloc<T> a; void* p = a.allocate(1);
	new(p) T(a1, a2, a3, a4);
	return p;
}


template<class T, template<typename> class Alloc, class A1, class A2, class A3, class A4, class A5> 
inline void* type_ctor(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
	Alloc<T> a; void* p = a.allocate(1);
	new(p) T(a1, a2, a3, a4, a5);
	return p;
}


template<class T, template<typename> class Alloc, class A1, class A2, class A3, class A4, class A5, class A6> 
inline void* type_ctor(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{
	Alloc<T> a; void* p = a.allocate(1);
	new(p) T(a1, a2, a3, a4, a5, a6);
	return p;
}


template<class T, template<typename> class Alloc, class A1, class A2, class A3, class A4, class A5, class A6, class A7> 
inline void* type_ctor(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{
	Alloc<T> a; void* p = a.allocate(1);
	new(p) T(a1, a2, a3, a4, a5, a6, a7);
	return p;
}


template<class T, template<typename> class Alloc, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> 
inline void* type_ctor(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{
	Alloc<T> a; void* p = a.allocate(1);
	new(p) T(a1, a2, a3, a4, a5, a6, a7, a8);
	return p;
}


//////////////////////////////////////////////////////////////////////////

template<class T, template<typename> class Alloc>
inline void type_destructor(void* v)
{
	T* p = static_cast<T*>(v);
	p->~T();
	Alloc<T> a;
	a.deallocate(p, 1);
}

//////////////////////////////////////////////////////////////////////////


template<class T>
void* type_create_inst() 
{ 
	T* ret = T::_ObjectClass::_CreateInstance();
	if(ret) ret->AddRef();
	return ret; 
}


template<class T, class A1>
void* type_create_inst(A1 a1) 
{ 
	T* ret = T::_ObjectClass::_CreateInstance();
	if(ret) ret->AddRef();
	ret->FinalConstruct(a1);
	return ret; 
}


template<class T, class A1, class A2>
void* type_create_inst(A1 a1, A2 a2) 
{ 
	T* ret = T::_ObjectClass::_CreateInstance();
	if(ret) ret->AddRef();
	ret->FinalConstruct(a1, a2);
	return ret; 
}


template<class T, class A1, class A2, class A3>
void* type_create_inst(A1 a1, A2 a2, A3 a3) 
{ 
	T* ret = T::_ObjectClass::_CreateInstance();
	if(ret) ret->AddRef();
	ret->FinalConstruct(a1, a2, a3);
	return ret; 
}


template<class T, class A1, class A2, class A3, class A4>
void* type_create_inst(A1 a1, A2 a2, A3 a3, A4 a4) 
{ 
	T* ret = T::_ObjectClass::_CreateInstance();
	if(ret) ret->AddRef();
	ret->FinalConstruct(a1, a2, a3, a4);
	return ret; 
}


template<class T, class A1, class A2, class A3, class A4, class A5>
void* type_create_inst(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) 
{ 
	T* ret = T::_ObjectClass::_CreateInstance();
	if(ret) ret->AddRef();
	ret->FinalConstruct(a1, a2, a3, a4, a5);
	return ret; 
}


template<class T, class A1, class A2, class A3, class A4, class A5, class A6>
void* type_create_inst(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) 
{ 
	T* ret = T::_ObjectClass::_CreateInstance();
	if(ret) ret->AddRef();
	ret->FinalConstruct(a1, a2, a3, a4, a5, a6);
	return ret; 
}


template<class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
void* type_create_inst(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) 
{ 
	T* ret = T::_ObjectClass::_CreateInstance();
	if(ret) ret->AddRef();
	ret->FinalConstruct(a1, a2, a3, a4, a5, a6, a7);
	return ret; 
}


template<class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
void* type_create_inst(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) 
{ 
	T* ret = T::_ObjectClass::_CreateInstance();
	if(ret) ret->AddRef();
	ret->FinalConstruct(a1, a2, a3, a4, a5, a6, a7, a8);
	return ret; 
}


//////////////////////////////////////////////////////////////////////////

template<class T> 
void type_destroy_inst(void* v) 
{ 
	if(v) static_cast<T*>(v)->Release(); 
}

//////////////////////////////////////////////////////////////////////////

