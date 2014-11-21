#include <glew.h>

class Material{

private:
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shinniness;
public:
	Material(GLfloat* amb,GLfloat* diff,GLfloat* spec,GLfloat shin);
	Material();
	void addSpecular(GLfloat* nspec);
	void addDiffuse(GLfloat* ndiff);
	void addAmbient(GLfloat*namb);
	void setShinniness(GLfloat nshin);

	GLfloat* getSpecular();
	GLfloat* getDiffuse();
	GLfloat* getAmbient();
	GLfloat* getShinniness();
	Material& operator=(const Material& rhs);
	bool operator==(const Material& rhs) const;
	bool operator!=(const Material& rhs) const;
};