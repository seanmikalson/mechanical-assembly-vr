#include"Primitives.h"
#define US_INT unsigned short int
class BoundingVolume
{
private:
	List<GameObject*> gameObjects;

public:
	//---------------------------------
	// Constructors + Destructors
	//---------------------------------
	BoundingVolume();
	~BoundingVolume();
	BoundingVolume(const BoundingVolume& rhs);

	//---------------------------------
	// Specific Class Functions
	//---------------------------------
	void draw();
	void adjustPositions(GLfloat,GLfloat,GLfloat);
	GameObject* getGameObject(int index);
	int getNoItems();
	GameObject* getGameObjectFromId(unsigned int id);

	//---------------------------------
	// Operators
	//---------------------------------
	BoundingVolume& operator=(const BoundingVolume& rhs);
};
