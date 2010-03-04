import Sekai

tc1 = Sekai.TestClass()
tc2 = Sekai.TestClass()

assert(tc1.data == 0)
	
assert(tc2.data == 1)
	
tc1.data = 700
tc2.data = 900

assert(tc1.data == 700)
	
assert(tc2.data == 900)
	
tc1.bval = True
tc2.bval = False

assert(tc1.bval)
	
assert(not tc2.bval)
