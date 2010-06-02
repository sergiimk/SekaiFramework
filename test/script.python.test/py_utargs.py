from Sekai import TestPlayer as Player

def checkValues(vec, x, y, z):
	assert(vec.x == x and vec.y == y and vec.z == z)

player1 = Player()

checkValues(player1.Position, 0.0, 0.0, 0.0)

pos = player1.Position
pos.x, pos.y, pos.z = 3.0, 2.0, 1.0

checkValues(player1.Position, 0.0, 0.0, 0.0)

checkValues(pos, 3.0, 2.0, 1.0)

player1.Position = pos

checkValues(player1.Position, 3.0, 2.0, 1.0)

#==================================================
pos.x, pos.y, pos.z = 3.0, 4.0, 5.0

# using set method
player1.setPosition(pos)

#using get method
checkValues(player1.getPosition(), 3.0, 4.0, 5.0)
