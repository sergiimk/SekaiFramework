from Sekai import TestClass

tc1 = TestClass();

c = tc1.Method3(3, 1.0469);

assert(c > 3.14 and c < 3.15)
	
tc2 = TestClass();
c = tc2.Method3(2, tc1.Method3(1, 2.0))

assert(c > 3.99 and c < 4.01)
	
str = tc1.str

assert(str == "some string")
	
#str = "my string"
#tc1.str = str
#
#assert(tc1.str == "my string")