from Sekai import Vector3

vec = Vector3()
vec.x, vec.y, vec.z = 1.0, 2.0, 3.0

assert(str(vec) == "1 2 3")
	
assert(repr(vec).find("Vector3") != -1)
	
#==========================================

vec2 = vec

vec3 = Vector3()

assert(vec2 == vec)
	
assert(vec != vec3)

assert(vec != 13)

#==========================================

h = hash(vec2)