import Sekai

methodDoc = Sekai.TestDocClass.Add.__doc__
assert(methodDoc == "Return summ of two integers")

fieldDoc = Sekai.TestDocClass.somedata.__doc__
assert(fieldDoc == "Some data documentation")