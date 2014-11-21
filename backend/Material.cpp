#include "Material.h"

Material::Material(GLfloat* amb,GLfloat* diff,GLfloat* spec,GLfloat shin)
{
	shinniness = shin;
	for(int i = 0; i < 4; i++)
	{
		specular[i] = spec[i];
		ambient[i] = amb[i];
		diffuse[i] = diff[i];
	}
}
Material::Material()
{
	shinniness = 0.0f;
	for(int i = 0; i < 4; i++)
	{
		specular[i] = 0.0f;
		ambient[i] = 0.0f;
		diffuse[i] = 0.0f;
	}	
}
void Material::addSpecular(GLfloat* spec)
{
	for(int i = 0; i < 4; i++)
	{
		specular[i] = spec[i];
	}
}
void Material::addDiffuse(GLfloat* diff)
{
	for(int i = 0; i < 4; i++)
	{
		diffuse[i] = diff[i];
	}
}
void Material::addAmbient(GLfloat* amb)
{
	for(int i = 0; i < 4; i++)
	{
		ambient[i] = amb[i];
	}
}
void Material::setShinniness(GLfloat shin)
{
	shinniness = shin;
}
GLfloat* Material::getSpecular()
{
	return specular;
}
GLfloat* Material::getDiffuse()
{
	return diffuse;
}
GLfloat* Material::getAmbient()
{
   return ambient;
}
GLfloat* Material::getShinniness()
{
  return &shinniness;
}
Material& Material::operator=(const Material& rhs)
{
	if(this == &rhs)
		return *this;

	(*this).shinniness = rhs.shinniness;

	for(int i = 0; i < 4; i++)
	{
		(*this).specular[i] = rhs.specular[i];
		(*this).ambient[i] = rhs.ambient[i];
		(*this).diffuse[i] = rhs.diffuse[i];
	}
	return *this;
}
bool Material::operator==(const Material& rhs) const
{
	if(this == &rhs)
		return true;

	bool same = true;
	same &= (*this).shinniness == rhs.shinniness;

	for(int i = 0; i < 4; i++)
	{
		same &= (*this).specular[i] == rhs.specular[i];
		same &= (*this).ambient[i] == rhs.ambient[i];
		same &= (*this).diffuse[i] == rhs.diffuse[i];
	}
	return same;
}
bool Material::operator!=(const Material& rhs) const
{
	if(this == &rhs)
		return false;

	bool same = true;
	same &= (*this).shinniness == rhs.shinniness;

	for(int i = 0; i < 4; i++)
	{
		same &= (*this).specular[i] == rhs.specular[i];
		same &= (*this).ambient[i] == rhs.ambient[i];
		same &= (*this).diffuse[i] == rhs.diffuse[i];
	}

	return !same;
}