#include "MechanicalObject.h"
#define EXTENDS : public 
#define DEGREES_TO_RAD 0.017453292f

//-----------------------------------------
//    Primitive Shapes
//-----------------------------------------

class WorkShop EXTENDS GameObject{
	public:
		WorkShop(GLfloat Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, List<Material> material);
};
class EngineBlock EXTENDS MechanicalObject{
	public:
		EngineBlock(GLfloat Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* material);
};
class EngineHead EXTENDS MechanicalObject{
	public:
		EngineHead(GLfloat Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* material);
		void setupCorrectMountingPoints(EngineBlock* engineBlock, int side);
};
class IntakeManifold EXTENDS MechanicalObject{
	public:
		IntakeManifold(EngineBlock* engineBlock, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* material);
		void setupCorrectMountingPoints(EngineBlock* engineBlock);
};
class Square EXTENDS GameObject{

	public:
		Square(GLfloat Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* material);
		void setupPhysData(GLfloat Scale);
};
class Cube EXTENDS MechanicalObject{

	public:
		 Cube(Vertex* Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* material);
		 void setupPhysData(Vertex* Scale);
};

class Cylinder EXTENDS GameObject
{
	public:
		Cylinder(int sides,Vertex* Scale,GLfloat dispx,GLfloat dispy ,GLfloat dispz,Material* TriColor);
};

class Marker EXTENDS GameObject
{
	public:
		Marker(int sides,Vertex* Scale,GLfloat dispx,GLfloat dispy ,GLfloat dispz,Material* TriColor);
};
/*
class SquarePyramid EXTENDS GameObject {
	public:
		 SquarePyramid(Vertex* Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* TriColor);
};

class Circle EXTENDS GameObject 
{
	public:
		Circle(int sides, GLfloat Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* TriColor);
};



class Sphere EXTENDS GameObject
{
	public:
		Sphere(int insides,Vertex* Scale,GLfloat dispx,GLfloat dispy ,GLfloat dispz,Material* TriColor);
};

class Cone EXTENDS GameObject
{
	public:
		Cone(int insides,Vertex* Scale,GLfloat dispx,GLfloat dispy ,GLfloat dispz,Material* TriColor);
};
*/