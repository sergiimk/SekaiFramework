from Sekai import TestPlayer as Player
from Sekai import Vector3

def checkValues(vec, x, y, z):
	assert(vec.x == x and vec.y == y and vec.z == z)

player1 = Player()

#==============================================================

checkValues(player1.PositionPtr, 0.0, 0.0, 0.0)

vec = Vector3()
vec.x, vec.y, vec.z = 1.0, 2.0, 3.0
player1.Position = vec

checkValues(player1.PositionPtr, 1.0, 2.0, 3.0)

#==============================================================

player1.PositionPtr = vec

checkValues(player1.PositionPtr, 1.0, 2.0, 3.0)

vec.x, vec.y, vec.z = 3.0, 2.0, 1.0

checkValues(player1.PositionPtr, 3.0, 2.0, 1.0)

#==============================================================

vec.x, vec.y, vec.z = 1.0, 2.0, 3.0

vec2 = Vector3()
vec2.x, vec2.y, vec2.z = vec.z, vec.y, vec.x

player1.setPositionPtr(vec)

checkValues(player1.PositionPtr, 1.0, 2.0, 3.0)

player1.setPositionPtr(vec2)

checkValues(player1.PositionPtr, 3.0, 2.0, 1.0)

pvec = player1.getPositionPtr()

checkValues(pvec, 3.0, 2.0, 1.0)

#==============================================================