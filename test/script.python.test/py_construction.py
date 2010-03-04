from Sekai import Vector3

def checkValues(vec, x, y, z):
	assert(vec.x == x and vec.y == y and vec.z == z);

vec = Vector3(1, 2, 3);

checkValues(vec, 1, 2, 3);
