import Sekai

tc1 = Sekai.TestClass()
tc1.Method1()

assert(tc1.GetMethodID() == 1)

tc2 = Sekai.TestClass()
tc2.Method2()

assert(tc2.GetMethodID() == 2)

tc1.Method1()
tc2.Method1()

assert(tc1.GetMethodID() == 1)

assert(tc2.GetMethodID() == 1)
