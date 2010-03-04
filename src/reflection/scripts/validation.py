import sys
import io

MAX_PARAMS = int(sys.argv[1])

#=======================================================================================

header = '''
//////////////////////////////////////////////////////////////////////////
#define _VT_RET(x) VariantTraits<Utils::TStripType<x>::ref2ptr>::type
#define _VT_PARAM(x) VariantTraits<Utils::TStripType<x>::noref>::type
		
'''

validate_func = '''
//////////////////////////////////////////////////////////////////////////

template<%targs%class RT>
inline ValidationEntry* ValidationInfo(RT (CALL_CONV *)(%args%))
{
	static ValidationEntry e[] = { %args_t%_VT_RET(RT), 0};
	return e;
}
'''

validate_method = '''
//////////////////////////////////////////////////////////////////////////

template<class C, %targs%class RT>
ValidationEntry* ValidationInfo(RT (CALL_CONV C::*func)(%args%))
{
	static ValidationEntry e[] = { T_CUSTOM, %args_t%_VT_RET(RT), 0};
	return e;
}
'''

#=======================================================================================

with open('validation.inc', 'w') as file:

	file.write(header)

	for i in range(0, MAX_PARAMS + 1):
	
		block = validate_func
		
		targs = ""
		for j in range(1, i + 1):
			targs += "class A" + str(j) + ", "
		
		args = ""
		for j in range(1, i + 1):
			args += "A" + str(j) + ", "
		args = args[:-2]
			
		args_t = ""
		for j in range(1, i + 1):
			args_t += "_VT_PARAM(A" + str(j) + "), "
			
		block = block.replace("%targs%", targs)
		block = block.replace("%args%", args)
		block = block.replace("%args_t%", args_t)
		
		file.write(block)
		
		
		
	for i in range(0, MAX_PARAMS + 1):
	
		block = validate_method
		
		targs = ""
		for j in range(1, i + 1):
			targs += "class A" + str(j) + ", "
		
		args = ""
		for j in range(1, i + 1):
			args += "A" + str(j) + ", "
		args = args[:-2]
			
		args_t = ""
		for j in range(1, i + 1):
			args_t += "_VT_PARAM(A" + str(j) + "), "
			
		block = block.replace("%targs%", targs)
		block = block.replace("%args%", args)
		block = block.replace("%args_t%", args_t)
		
		file.write(block)
	

