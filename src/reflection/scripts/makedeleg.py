import sys
import io

MAX_PARAMS = int(sys.argv[1])

#=======================================================================================

make_generic_function = '''
//////////////////////////////////////////////////////////////////////////

template <class FT>
DelegateBase* MakeGenericDelegate(FT* func) 
{ return new Delegate<FT>(func); }

'''

make_generic_method = '''
//////////////////////////////////////////////////////////////////////////

template <class C, %targs%, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)(%args%))
{ return new Delegate<RT (%args%)>((C*)0, func); }

template <class C, %targs%, class RT>
DelegateBase* MakeGenericDelegate(RT (C::*func)(%args%) const)
{ return new Delegate<RT (%args%)>((C*)0, func); }

'''


#=======================================================================================

with open('makedeleg.inc', 'w') as file:

	file.write(make_generic_function)

	for i in range(0, MAX_PARAMS + 1):
		
		block = make_generic_method		

		args = ""
		for j in range(1, i+1):
			args += "A" + str(j) + ", "
			
		targs = ""
		for j in range(1, i+1):
			targs += "class A" + str(j) + ", "

		block = block.replace("%args%", args[:-2])
		block = block.replace("%targs%", targs[:-2])

		file.write(block)
