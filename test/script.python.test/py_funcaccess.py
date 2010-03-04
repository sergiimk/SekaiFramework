class TestClass(object):
	def __init__(self):
		pass
		
	def Foo(self, a):
		assert(a == 13)
		return a - 1

#=========================================

def run(a):	
	tc = TestClass()
	return tc.Foo(a)