import Sekai


#=== Test C++ class hierarchy =========================

d = Sekai.TestInh_Derived()

assert(issubclass(d.__class__, Sekai.TestInh_Base))
	
d.VirtFunc(15)

assert(d.getFlag() == 14)
	
d = Sekai.TestInh_Base()

d.VirtFunc(11)

assert(d.getFlag() == 11)

assert(isinstance(d, Sekai.TestInh_Base))


#=== Try to derive from C++ class =====================
class Derived1(Sekai.TestInh_Base):
	pass


d = Derived1()

assert(issubclass(d.__class__, Sekai.TestInh_Base)) and (not issubclass(d.__class__, Sekai.TestInh_Derived))

d.VirtFunc(15)

assert(d.getFlag() == 15)


#=== Try to derive from C++ class =====================
class Derived2(Sekai.TestInh_Derived):
	def VirtFunc(self, f):
		f += 10
		super(Derived2, self).VirtFunc(f)
	
d = Derived2()

assert(issubclass(d.__class__, Sekai.TestInh_Base) and issubclass(d.__class__, Sekai.TestInh_Derived))

d.VirtFunc(15)

assert(d.getFlag() == 24)

#=== Try to derive from C++ class =====================
class Vec3(Sekai.Vector3):
	def __init__(self, x, y, z, asdf):
		super(Vec3, self).__init__(x, y, z)
	
v = Vec3(1,2,3, 666)

assert((v.x, v.y, v.z) == (1,2,3))