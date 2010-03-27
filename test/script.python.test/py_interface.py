#== Normal flow =============================================================

import Sekai

f = Sekai.TestInterfaceFactory()
i = f.GetTestInterface()

s = i.Sum(1, 2)
assert( s == 3 )

i.Release()

i = f.CreateTestInterface()

#== Creation of abstract class ==============================================

try:
	# must throw exception here
	i = Sekai.ITestInterface()
	
	assert(False)
except:
	pass
	
