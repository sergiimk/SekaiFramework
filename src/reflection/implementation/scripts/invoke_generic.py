import sys
import io

MAX_PARAMS = int(sys.argv[1])

#=======================================================================================

header = '''
//////////////////////////////////////////////////////////////////////////
#define MAKE_DELEG()		Delegate<FT>* pdeleg = static_cast<Delegate<FT>*>(deleg)
#define MAKE_DELEGM()		MAKE_DELEG(); \\
							FunctionData fd = pdeleg->GetFunctionData(); \\
							fd.SetThisPtr(reinterpret_cast<detail::GenericClass*>(*(void**)args[0])); \\
							pdeleg->SetFunctionData(fd);
#define MAKE_CALL			(*pdeleg)
#define UNPCK_ARG(T, ARG)	(*(T*)args[ARG])
#define UNPCK_RET()			(*(RT*)res)
#define UNPCK_RET_REF()		(*(RT**)res)
'''

function_invokers_ret = '''
//////////////////////////////////////////////////////////////////////////

template<class FT, %targs%, class RT>
void invoke_generic(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET() = MAKE_CALL(%args%); }

template<class FT, %targs%, class RT>
void invoke_generic_ref(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); UNPCK_RET_REF() = &MAKE_CALL(%args%); }
'''

function_invokers_noret = '''
template<class FT, %targs%>
void invoke_generic_noret(DelegateBase* deleg, void** args, void* res)
{ MAKE_DELEG(); MAKE_CALL(%args%); }
'''

method_invokers_ret = '''
//////////////////////////////////////////////////////////////////////////

template<class FT, %targs%, class RT>
void invoke_generic_m(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET() = MAKE_CALL(%args%);
}

template<class FT, %targs%, class RT>
void invoke_generic_m_ref(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	UNPCK_RET_REF() = &MAKE_CALL(%args%);
}
'''

method_invokers_noret = '''
template<class FT, %targs%>
void invoke_generic_m_noret(DelegateBase* deleg, void** args, void* res)
{
	MAKE_DELEGM();
	MAKE_CALL(%args%);
}
'''


#=======================================================================================

with open('invoke_generic.inc', 'w') as file:

	file.write(header)

	for i in range(0, MAX_PARAMS + 1):
		
		block = function_invokers_ret		

		args = ""
		for j in range(0, i):
			args += "UNPCK_ARG(A" + str(j + 1) + ", " + str(j) + "), "

		targs = ""
		for j in range(1, i+1):
			targs += "class A" + str(j) + ", "

		block = block.replace("%args%", args[:-2])
		block = block.replace("%targs%", targs[:-2])
		block = block.replace("%rti%", str(i))

		file.write(block)



		block = function_invokers_noret		

		args = ""
		for j in range(0, i):
			args += "UNPCK_ARG(A" + str(j + 1) + ", " + str(j) + "), "

		targs = ""
		for j in range(1, i+1):
			targs += "class A" + str(j) + ", "

		block = block.replace("%args%", args[:-2])
		block = block.replace("%targs%", targs[:-2])

		file.write(block)

#==========================================================================
	for i in range(0, MAX_PARAMS + 1):

		block = method_invokers_ret		

		args = ""
		for j in range(1, i+1):
			args += "UNPCK_ARG(A" + str(j) + ", " + str(j) + "), "

		targs = ""
		for j in range(1, i+1):
			targs += "class A" + str(j) + ", "

		block = block.replace("%args%", args[:-2])
		block = block.replace("%targs%", targs[:-2])
		block = block.replace("%rti%", str(i+1))

		file.write(block)



		block = method_invokers_noret		

		args = ""
		for j in range(1, i+1):
			args += "UNPCK_ARG(A" + str(j) + ", " + str(j) + "), "

		targs = ""
		for j in range(1, i+1):
			targs += "class A" + str(j) + ", "

		block = block.replace("%args%", args[:-2])
		block = block.replace("%targs%", targs[:-2])

		file.write(block)