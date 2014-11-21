#include"Primitives.h"
#define US_INT unsigned short int
class BoundingVolume
{
private:
	List<GameObject> gameObjects;
	US_INT searchForPotentialCollisions(US_INT index, US_INT* possibleCollisions,GLfloat elapsedTime);

public:
	BoundingVolume();
	~BoundingVolume();
	void draw();
	void adjustPositions(GLfloat,GLfloat,GLfloat);
	void animate(GLfloat);
	GameObject* getGameObject(int index);
};
