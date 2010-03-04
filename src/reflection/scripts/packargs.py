import sys
import io

MAX_PARAMS = int(sys.argv[1])

#=======================================================================================

packargs = '''
//////////////////////////////////////////////////////////////////////////

template<%targs%class RT>
InvokeArguments* PackArguments(InvokeArguments& args, %pargs%RT* ret)
{
	#ifdef _DEBUG
	%validation%
	#endif
	args.ArgCount = %nargs%;
	%packargs%args.Arguments[%iret%] = ret;
	return &args;
}
'''

#=======================================================================================

with open('packargs.inc', 'w') as file:

	for i in range(0, MAX_PARAMS + 1):
	
		block = packargs
		
		targs = ""
		for j in range(1, i + 1):
			targs += "class A" + str(j) + ", "
		
		pargs = ""
		for j in range(1, i + 1):
			pargs += "A" + str(j) + "& a" + str(j) + ", "
		
		validation = ""
		for j in range(0, i):
			validation += "args.ValidationInfo[" + str(j + 1) + "] = VariantTraits<A" + str(j + 1) + ">::type;\n\t"
		validation += "args.ValidationInfo[" + str(i + 1) + "] = VariantTraits<RT>::type;\n\t"
		validation += "args.ValidationInfo[" + str(i + 2) + "] = T_EMPTY;"
		
		pckargs = ""
		for j in range(0, i):
			pckargs += "args.Arguments[" + str(j + 1) + "] = (void*)&a" + str(j + 1) + ";\n\t"
			
		block = block.replace("%targs%", targs)
		block = block.replace("%pargs%", pargs)
		block = block.replace("%validation%", validation)
		block = block.replace("%packargs%", pckargs)
		block = block.replace("%nargs%", str(i))
		block = block.replace("%iret%", str(i + 1))
		
		file.write(block)
	

