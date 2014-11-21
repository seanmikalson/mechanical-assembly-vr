#include "PhysicsData.h"

#define PHYSICS_HULLS_FULL noPhysHulls >= maxPhysHulls
#define INDEX_OUT_OF_RANGE index >= physicsHulls.getNoItems()

#define ALL_PHYS_HULLS_IN_THIS_DATA int i = 0; i < noPhysHulls; i++
#define ALL_PHYS_HULLS_IN_TARGET_DATA int b = 0; b < (*target).getNoHulls(); b++
#define CURRENT_HULL (**(physicsHulls.getItem(i)))
#define CURRENT_TARGET_HULL (*target).getPhysicsHull(b)
#define TARGET_POSITION (*target).getPosition()
#define FIRST_COLLISION_OR_NEW_ONE_CLOSER tcollides && (tlength < *length || *length < 0.0f)
#define NOT_VALID_HULL_TYPE newHullType != TriangleMesh 

PhysicsData::PhysicsData()
{
	physicsHulls = List<PhysicsHull*>();
	velocity = 0.0f;
	acceleration = 0.0f;
	position = 0.0f;
	mass = 0.0f;
	restitution = 0.0f;
	staticFriction = dynamicFriction = 0.0f;
}
PhysicsData::PhysicsData(int maxHulls, GLfloat posx, GLfloat posy, GLfloat posz)
{
	physicsHulls = List<PhysicsHull*>(maxHulls);
	velocity = 0.0f;
	acceleration = 0.0f;
	position = Vertex(posx,posy,posz);
	mass = 0.0f;
	restitution = 0.0f;
	staticFriction = dynamicFriction = 0.0f;
}
PhysicsData::~PhysicsData()
{
	int noPhysHulls = physicsHulls.getNoItems();
	for(ALL_PHYS_HULLS_IN_THIS_DATA)
	{
		delete *physicsHulls.getItem(i);
	}
}
bool PhysicsData::addPhysicsHull(HullType newHullType)
{
	if(newHullType == TriangleMesh)
	{
		TriangleMeshHull* temp = new TriangleMeshHull;
		physicsHulls.addItem(temp);
		return true;
	}
	
	return false;
}
PhysicsHull* PhysicsData::getPhysicsHull(int index)
{
	if(INDEX_OUT_OF_RANGE)
		return nullptr;

	return *physicsHulls.getItem(index);
}
TriangleMeshHull* PhysicsData::getTriangleHull(int index)
{
	if(INDEX_OUT_OF_RANGE || (**physicsHulls.getItem(index)).getHullType() != TriangleMesh)
		return nullptr;

	return (TriangleMeshHull*) *physicsHulls.getItem(index);
}
void PhysicsData::adjustPosition(GLfloat addx,GLfloat addy,GLfloat addz)
{
	position.setX(position.getX() + addx);
	position.setY(position.getY() + addy);
	position.setZ(position.getZ() + addz);
}
void PhysicsData::accelerate(GLfloat x,GLfloat y,GLfloat z)
{
	acceleration.setX(acceleration.getX() + x);
	acceleration.setY(acceleration.getY() + y);
	acceleration.setZ(acceleration.getZ() + z);
}
void PhysicsData::addVelocity(GLfloat x,GLfloat y,GLfloat z)
{
	velocity.setX(velocity.getX() + x);
	velocity.setY(velocity.getY() + y);
	velocity.setZ(velocity.getZ() + z);
}
void PhysicsData::updateVelocity(GLfloat elapsedTime)
{
	Vertex temp = acceleration * elapsedTime;
	addVelocity(temp.getX(),temp.getY(),temp.getZ());
}
void PhysicsData::updatePosition(GLfloat elapsedTime)
{
	Vertex temp = velocity * elapsedTime;
	adjustPosition(temp.getX(),temp.getY(),temp.getZ());
}
bool PhysicsData::checkCollision(PhysicsData* target,Vertex* collisionpt, Vertex* normal, GLfloat* length,GLfloat elapsedtime)
{
	Vertex vector = Vertex(elapsedtime * velocity.getX(),elapsedtime * velocity.getY(),elapsedtime * velocity.getZ());
	bool collides = false;
	*length = -1.0f;

	int noPhysHulls = physicsHulls.getNoItems();
	for(ALL_PHYS_HULLS_IN_THIS_DATA)
	{
		for(ALL_PHYS_HULLS_IN_TARGET_DATA)
		{
			Vertex tintersection = Vertex();
			GLfloat tlength = -1.0f;

			bool tcollides = CURRENT_HULL.getIntersection(CURRENT_TARGET_HULL,vector,normal,&tlength,&tintersection,position,TARGET_POSITION);

			if(FIRST_COLLISION_OR_NEW_ONE_CLOSER)
			{
				collides = true;
				*length = tlength;
				*collisionpt = tintersection;
			}
		}
	}
	return collides;
}
void PhysicsData::resetPhysHulls(int newMaxHulls)
{
	int noPhysHulls = physicsHulls.getNoItems();
	for(ALL_PHYS_HULLS_IN_THIS_DATA)
	{
		delete *physicsHulls.getItem(i);
	}
	physicsHulls.resetList(newMaxHulls);
}
void PhysicsData::setPosition(GLfloat inX, GLfloat inY, GLfloat inZ)
{
	position = Vertex(inX,inY,inZ);
}
void PhysicsData::setVelocity(GLfloat inX, GLfloat inY, GLfloat inZ)
{
	velocity = Vertex(inX,inY,inZ);
}
void PhysicsData::collide(PhysicsData* target, GLfloat length,Vertex normal, GLfloat elapsedTime)
{
	#define TARGET_IMMOVABLE (*target).getMass() <= 0.0f

	GLfloat totalLength = ( velocity * elapsedTime).length();
	
	if(TARGET_IMMOVABLE) 
	{
		GLfloat tempTime = (length / totalLength) * elapsedTime;
		updatePosition(tempTime);
		velocity.reflect(normal);
		velocity *= restitution;

		tempTime = elapsedTime - tempTime;
		updatePosition(tempTime);
	}
	else
	{
		GLfloat tempTime = ((length / (totalLength)) * elapsedTime);
		updatePosition(tempTime);
		GLfloat targetMass = (*target).getMass();
		Vertex targetVelocity = (*target).getVelocity();
		Vertex* targetVelocityPointer = (*target).getVelocityPointer();
		Vertex originVelocity = velocity;
		GLfloat collisionRestitution = (restitution + (*target).getRestitution()) / (2.0f * (mass + targetMass));

		velocity = originVelocity * (mass - targetMass);
		velocity += targetVelocity * (2.0f * targetMass);
		velocity *= collisionRestitution;
		
		(*targetVelocityPointer) = targetVelocity * (targetMass - mass);
		(*targetVelocityPointer) += originVelocity * (2.0f * mass);
		(*targetVelocityPointer) *= collisionRestitution;
	}
}
void PhysicsData::setAcceleration(GLfloat inX, GLfloat inY, GLfloat inZ)
{
	acceleration = Vertex(inX,inY,inZ);
}
void PhysicsData::rotateX(GLfloat rad)
{
	int noPhysHulls = physicsHulls.getNoItems();

	for(ALL_PHYS_HULLS_IN_THIS_DATA)
		(**physicsHulls.getItem(i)).rotateX(rad);
}
void PhysicsData::rotateY(GLfloat rad)
{
	int noPhysHulls = physicsHulls.getNoItems();

	for(ALL_PHYS_HULLS_IN_THIS_DATA)
		(**physicsHulls.getItem(i)).rotateY(rad);
}
void PhysicsData::rotateZ(GLfloat rad)
{
	int noPhysHulls = physicsHulls.getNoItems();

	for(ALL_PHYS_HULLS_IN_THIS_DATA)
		(**physicsHulls.getItem(i)).rotateZ(rad);
}
void PhysicsData::rotate(GLfloat rad, Vertex axis)
{
	int noPhysHulls = physicsHulls.getNoItems();

	for(ALL_PHYS_HULLS_IN_THIS_DATA)
		(**physicsHulls.getItem(i)).rotate(rad,axis);
}
PhysicsData& PhysicsData::operator=( const PhysicsData& rhs)
{
	#define ALL_HULLS_TO_BE_COPIED int i = 0; i < noPhysHulls; i++

	if(this == &rhs)
		return (*this);

	(*this).restitution = rhs.restitution;
	(*this).mass = rhs.mass;
	(*this).velocity = rhs.velocity;
	(*this).position = rhs.position;
	(*this).acceleration = rhs.acceleration;
	List<PhysicsHull*> temp = rhs.physicsHulls;
	(*this).resetPhysHulls(temp.getMaxItems());
	
	int noPhysHulls = temp.getNoItems();
	for(ALL_HULLS_TO_BE_COPIED)
	{
		if((**temp.getItem(i)).getHullType() == TriangleMesh)
		{
			TriangleMeshHull* tempHull = new TriangleMeshHull();
			(*this).physicsHulls.addItem(tempHull);
			*((*this).physicsHulls.getDataPtr()[i]) = *(temp.getDataPtr()[i]);
		}
	}
	
	return *this;
}