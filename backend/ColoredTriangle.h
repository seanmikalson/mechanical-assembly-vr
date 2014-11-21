#include "Triangle.h"
#include "Color.h"

class ColoredTriangle : public Triangle {

private:
	Color* TriColor;
public:
	ColoredTriangle(GLfloat, GLfloat, GLfloat, Color* );
	void setColor(Color* newCol){ TriColor = newCol;};
	Color* getColor(){return TriColor;};
};