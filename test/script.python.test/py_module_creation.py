import TestModule

adder = TestModule.CFancyAdder();

res = adder.DoFancyThings(15, 35);
assert(res == 50);
assert(adder.LastResult == 50);