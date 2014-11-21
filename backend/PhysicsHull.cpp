 #include "PhysicsHull.h"

PhysicsHull::PhysicsHull()
{
	position = 0.0f;
	hullType = NoType;
	maxRadius = 0.0f;
}
PhysicsHull::PhysicsHull(GLfloat x, GLfloat y, GLfloat z)
{
	position = Vertex(x,y,z);
	hullType = NoType;
	maxRadius = 0.0f;
}
void PhysicsHull::adjustPosition(GLfloat x, GLfloat y, GLfloat z)
{
	position.setX(position.getX() + x);
	position.setY(position.getY() + y);
	position.setZ(position.getZ() + z);
}

