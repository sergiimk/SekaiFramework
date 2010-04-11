import sys
import io

MAX_PARAMS = int(sys.argv[1])

#=======================================================================================

tl_ctors = '''
template<class T, template<typename> class Alloc, %targs%> 
inline void* type_ctor(%fargs%)
{
	Alloc<T> a; void* p = a.allocate(1);
	new(p) T(%args%);
	return p;
}

'''

tl_dtor = '''
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

'''

tl_create_inst = '''
template<class T, %targs%>
void* type_create_inst(%fargs%) 
{ 
	T* ret = T::_ObjectClass::_CreateInstance();
	if(ret) ret->AddRef();
	ret->FinalConstruct(%args%);
	return ret; 
}

'''

tl_destroy = '''
//////////////////////////////////////////////////////////////////////////

template<class T> 
void type_destroy_inst(void* v) 
{ 
	if(v) static_cast<T*>(v)->Release(); 
}

//////////////////////////////////////////////////////////////////////////

'''

#=======================================================================================

with open('construction.inc', 'w') as file:

	for i in range(0, MAX_PARAMS + 1):
		
		block = tl_ctors
		
		targs = ""
		for j in range(1, i+1):
			targs += "class A" + str(j) + ", "

		fargs = ""
		for j in range(1, i+1):
			fargs += "A" + str(j) + " " + "a" + str(j) + ", "

		args = ""
		for j in range(1, i+1):
			args += "a" + str(j) + ", "
			
		block = block.replace("%targs%", targs[:-2])
		block = block.replace("%fargs%", fargs[:-2])
		block = block.replace("%args%",   args[:-2])

		file.write(block)
	
	file.write(tl_dtor)




	for i in range(0, MAX_PARAMS + 1):
		
		block = tl_create_inst
		
		targs = ""
		for j in range(1, i+1):
			targs += "class A" + str(j) + ", "

		fargs = ""
		for j in range(1, i+1):
			fargs += "A" + str(j) + " " + "a" + str(j) + ", "

		args = ""
		for j in range(1, i+1):
			args += "a" + str(j) + ", "
			
		block = block.replace("%targs%", targs[:-2])
		block = block.replace("%fargs%", fargs[:-2])
		block = block.replace("%args%",   args[:-2])

		file.write(block)

	file.write(tl_destroy)