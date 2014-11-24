#include"BoundingVolume.h"

BoundingVolume::BoundingVolume()
{
	GLfloat specular[4] = {1.0f,1.0f,1.0f,0.1f};
	GLfloat nothing[4] = {0.0f,0.0f,0.0f,0.0f};
	GLfloat diffPurp[4] = {0.9f,0.0f,0.9f,1.0f};
	GLfloat ambwht[4] = {1.0f,1.0f,1.0f,1.0f};
	GLfloat grnamb[4] = {0.0f,1.0f,0.0f,1.0f};
	GLfloat grndiff[4] = {0.0f,0.5f,0.0f,1.0f};
	GLfloat tanamb[4] = {1.0f,1.0f,0.8f,1.0f};
	GLfloat greyamb[4] = {0.5f,0.5f,0.5f,1.0f};
	GLfloat blueamb[4] = {0.0f,0.0f,0.5f,1.0f};
	GLfloat redamb[4] = {0.5f,0.0f,0.0f,1.0f};

    Material* Green = new  Material(grnamb,grndiff,nothing,30.0f);
    Material* Purple = new Material(diffPurp,diffPurp,specular,30.0f);
    Material* Tan = new Material(tanamb,tanamb,nothing,0.0f);
    Material* Grey = new Material(greyamb,greyamb,nothing,0.0f);
	Material* floor = new Material(greyamb,greyamb,greyamb,10.0f);
	Material* Red = new Material(redamb,redamb,nothing,0.0f);
	Material* Blue = new Material(blueamb,blueamb,nothing,0.0f);
	Material* roof = new Material(ambwht,ambwht,nothing,0.0f);

	
	//setup engine
	gameObjects.addItem(EngineBlock(2.0f,0.0f,0.0f,-10.0f,Grey));
	gameObjects.addItem(EngineHead(4.0f,13.0f,0.0f,-10.0f,Red));
	gameObjects[1].rotateZ(-45.0f * DEGREES_TO_RAD);

	Vertex movement = ((*(*gameObjects[0].getVisualData(0)).getVertex(0)) + gameObjects[0].getPosition() + (*gameObjects[0].getVisualData(0)).getPosition()) - 
		((*(*gameObjects[1].getVisualData(0)).getVertex(0)) + gameObjects[1].getPosition() + (*gameObjects[1].getVisualData(0)).getPosition());
	
	gameObjects[1].adjustPosition(1.0f * movement.getX(),1.0f *movement.getY(),0.0f);

	//setup room
	List<Material> temp = List<Material>();
	temp.addItem(*floor);
	temp.addItem(*roof);
	temp.addItem(*Tan);
	gameObjects.addItem(WorkShop(30.0f,0.0f,0.0f,0.0f,temp));

	//setup table
	//Vertex cubeScale = Vertex(20.0f,4.0f,20.0f);
	//gameObjects.addItem(Cube(&cubeScale,0.0f,0.0f,10.0f,Purple));
	/*


	
	gameObjects.addItem(Square(80.0f,0.0f,-20.0f,0.0f,Grey));
	(*(Square*) gameObjects.getItem(0)).setupPhysData(80.0f);

	gameObjects.addItem(Square(80.0f,0.0f, 20.0f,0.0f,Grey));
	(*(Square*) gameObjects.getItem(1)).setupPhysData(80.0f);

	gameObjects.addItem(Square(80.0f ,0.0f,0.0f,40.0f,Grey));
	(*((Square*) gameObjects.getItem(2))).setupPhysData(80.0f);
	(*gameObjects.getItem(2)).rotateX(90 * DEGREES_TO_RAD);

	gameObjects.addItem(Square(80.0f,0.0f,0.0f,-40.0f,Grey));
	(*((Square*) gameObjects.getItem(3))).setupPhysData(80.0f);
	(*gameObjects.getItem(3)).rotateX(90 * DEGREES_TO_RAD);


	gameObjects.addItem(Square(80.0f,40.0f,0.0f,0.0f,Grey));
	(*((Square*) gameObjects.getItem(4))).setupPhysData(80.0f);
	(*gameObjects.getItem(4)).rotateZ(90 * DEGREES_TO_RAD);

	gameObjects.addItem(Square(80.0f,-40.0f,0.0f,0.0f,Grey));
	(*((Square*) gameObjects.getItem(5))).setupPhysData(80.0f);
	(*gameObjects.getItem(5)).rotateZ(90 * DEGREES_TO_RAD);

	gameObjects.addItem(Cube(new Vertex(4.0f,4.0f,4.0f) ,0.0f,10.0f,-30.0f,Blue));
	(*((Cube*) gameObjects.getItem(6))).setupPhysData(new Vertex(4.0f,4.0f,4.0f));
	(*(*gameObjects.getItem(6)).getPhysicsData()).setVelocity(0.0f,0.0f,20.0f);
	(*(*gameObjects.getItem(6)).getPhysicsData()).setAcceleration(0.0f,-9.81f,0.0f);
	(*(*gameObjects.getItem(6)).getPhysicsData()).setRestitution(0.4f);
	(*(*gameObjects.getItem(6)).getPhysicsData()).setMass(20.0f);

	gameObjects.addItem(Cube(new Vertex(4.0f,4.0f,4.0f) ,20.0f,10.0f,-30.0f,Red));
	(*((Cube*) gameObjects.getItem(7))).setupPhysData(new Vertex(4.0f,4.0f,4.0f));
	(*(*gameObjects.getItem(7)).getPhysicsData()).setVelocity(-20.0f,0.0f,20.0f);
	(*(*gameObjects.getItem(7)).getPhysicsData()).setAcceleration(0.0f,-9.81f,0.0f);
	(*(*gameObjects.getItem(7)).getPhysicsData()).setRestitution(0.9f);
	(*(*gameObjects.getItem(7)).getPhysicsData()).setMass(10.0f);
	*/
}
BoundingVolume::~BoundingVolume()
{
}
void BoundingVolume::draw()
{
	int noObjects = gameObjects.getNoItems();
	for(int i = 0; i < noObjects; i++)
		(*gameObjects.getItem(i)).draw();
}
void BoundingVolume::adjustPositions(GLfloat x, GLfloat y, GLfloat z)
{
	int noObjects = gameObjects.getNoItems();
	for(int i = 0; i < noObjects; i++)
		(*gameObjects.getItem(i)).adjustPosition(x,y,z);
}
GameObject* BoundingVolume::getGameObject(int index)
{
	return gameObjects.getItem(index);
}
int BoundingVolume::getNoItems()
{
	return gameObjects.getNoItems();
}
US_INT BoundingVolume::searchForPotentialCollisions(US_INT index, US_INT* possibleCollisions,GLfloat elapsedTime)
{
	#define FOR_ALL_OTHER_OBJECTS for(int b = 0; b < noObjects; b++){ if(b != index) {
	#define END_FOR_LOOP }}
	#define ORIGIN_PHYS_DATA (*(*gameObjects.getItem(index)).getPhysicsData())
	#define ORIGIN_PHYS_HULL (*(*(*gameObjects.getItem(index)).getPhysicsData()).getPhysicsHull(0))
	#define TARGET_PHYS_HULL (*(*(*gameObjects.getItem(b)).getPhysicsData()).getPhysicsHull(0))
	#define ORIGIN_OBJECT (*gameObjects.getItem(index))
	#define TARGET_OBJECT (*gameObjects.getItem(b))
	int noObjects = gameObjects.getNoItems();

	US_INT noPossCollisions = 0;
	GLfloat velocitylen = (ORIGIN_PHYS_DATA.getVelocity() * elapsedTime).length();

	FOR_ALL_OTHER_OBJECTS
		GLfloat threshold = velocitylen + ORIGIN_PHYS_HULL.getMaxRadius() + TARGET_PHYS_HULL.getMaxRadius();
		GLfloat dist = (ORIGIN_OBJECT.getPosition() - TARGET_OBJECT.getPosition()).length();

		if( dist <= threshold )
			possibleCollisions[noPossCollisions++] = b;
		
	END_FOR_LOOP

	return noPossCollisions;
}
void BoundingVolume::animate(GLfloat elapsedTime)
{
	#define ALL_OBJECTS int i = 0; i < noObjects ; i++
	#define OBJECT_MOVING (*(*gameObjects.getItem(i)).getPhysicsData()).getVelocity().length() > 0.0005f
	#define ALL_POSSIBLE_COLLISIONS US_INT b = 0; b < noPossCollisions; b++
	#define FIRST_OR_CLOSER_COLLISION (tlength < length || length == -1.0f)

	int noObjects = gameObjects.getNoItems();
	US_INT* possibleCollisions = new US_INT[noObjects - 1];
	
	for(ALL_OBJECTS)
	{
		(*gameObjects.getItem(i)).updateVelocity(elapsedTime);

		if(OBJECT_MOVING)
		{
			US_INT noPossCollisions = searchForPotentialCollisions(i,possibleCollisions,elapsedTime);
			bool collides = false;
			US_INT targetObject = 0;
			Vertex collisionPt = Vertex(0.0f,0.0f,0.0f); 
			Vertex normal = Vertex(0.0f,0.0f,0.0f);
			GLfloat length = -1.0f;
			for(ALL_POSSIBLE_COLLISIONS)
			{
				Vertex tcollisionPt = Vertex(0.0f,0.0f,0.0f); 
				GLfloat tlength = 0.0f;
				Vertex tnormal = Vertex(0.0f,0.0f,0.0f);
				bool tcollides = false;
				tcollides = (*(*gameObjects.getItem(i)).getPhysicsData()).checkCollision((*gameObjects.getItem(possibleCollisions[b])).getPhysicsData(),&tcollisionPt,&tnormal,&tlength,elapsedTime);
				
				if(tcollides && FIRST_OR_CLOSER_COLLISION)
				{
					length = tlength;
					collisionPt = tcollisionPt;
					normal = tnormal;
					targetObject = possibleCollisions[b];
					collides = true;
				}
			}

			if(collides)
			{
				if(length > 0.005f && ((*(*gameObjects.getItem(i)).getPhysicsData()).getVelocity() - (*(*gameObjects.getItem(targetObject)).getPhysicsData()).getVelocity()).length() > 0.0005f)
					(*(*gameObjects.getItem(i)).getPhysicsData()).collide((*gameObjects.getItem(targetObject)).getPhysicsData(),length,normal,elapsedTime);
				else
					*(*(*gameObjects.getItem(i)).getPhysicsData()).getVelocityPointer() = 0.0f;
			}
			else 
				(*gameObjects.getItem(i)).updatePosition(elapsedTime);
		}
	}
	delete []possibleCollisions;
}

GameObject* BoundingVolume::getGameObjectFromId(unsigned int id)
{
	for(int i = 0; i < gameObjects.getNoItems(); i++)
	{
		if((*gameObjects.getItem(i)).getShapeId() == id)
		{
			return gameObjects.getItem(i);
		}
	}
	return NULL;
}
