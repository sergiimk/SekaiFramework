#== Normal flow =============================================================

import Sekai

f = Sekai.TestInterfaceFactory()
i = f.GetTestInterface()

assert( i.Sum(1,2) == 3 )

i.Release()

#== Creation of abstract class ==============================================

try:
	i = Sekai.TestInterface()
	assert(False)
except:
	pass
	# must throw exception here
	
		
