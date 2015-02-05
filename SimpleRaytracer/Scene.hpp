#pragma once

#include <utility>
#include <list>
#include <memory>

#include "Vector.hpp"
#include "Color.hpp"

// First: distance 
// Second: normal @ intersection
typedef std::pair<float, Vector3<float> > IntersectData;

class Ray
{
public:
	Ray(const Vector3<float>& origin, const Vector3<float>& direction)
		:	org(origin),
			dir(direction)
	{
	}

	void setDirection(const Vector3<float> &v) {dir = v;}
	void setOrigin(const Vector3<float> &v) {org = v;}

	Vector3<float> getOrigin() const 
	{
		return org;
	}
	Vector3<float> getDirection() const
	{
		return dir;
	}


private:
	Vector3<float> org;
	Vector3<float> dir;
};

// Every SceneObject has to provide a intersectRay method that returns IntersectData
struct SceneObject
{
	SceneObject(float reflection) : refl(reflection) { }
	virtual IntersectData intersectRay(const Ray& ray) = 0;
	float getReflection() {return refl;}
	Color getColor() {return col;}
	void setColor(const Color& c) {col = c;}
private:
	float refl;
	Color col;
};

// Plane class
class Plane : public SceneObject
{
public:
	Plane(const Vector3<float>& point, const Vector3<float>& normal, float reflection = 0.5f)
		:	SceneObject(reflection),
			a(normal.x),
			b(normal.y),
			c(normal.z),
			d(-a*point.x - b*point.y - c*point.z)
	{
	}

	IntersectData intersectRay(const Ray &ray) 
	{
		IntersectData data;
		float D = ray.getDirection().x*a + ray.getDirection().y*b + ray.getDirection().z*c;

		if(abs(D) > 0.0001f)
		{
			float t = -(ray.getOrigin().x*a + ray.getOrigin().y*b + ray.getOrigin().z*c + d) / D;
			data.first = t > 0.0f ? t : std::numeric_limits<float>::infinity();
		}
		else
			data.first = std::numeric_limits<float>::infinity();
		
		data.second = Vector3<float>(a, b, c);
		return data;
	}

private:
	float a, b, c, d;
};

// Sphere class
class Sphere : public SceneObject
{
public:
	Sphere(const Vector3<float>& position, float radius, float reflection = 0.5f)
		:	SceneObject(reflection),
			org(position),
			rad(radius)
	{
	}


	IntersectData intersectRay(const Ray &ray) 
	{
		IntersectData data;
		Vector3<float> dst = ray.getOrigin() - org;
		float B = dot(dst, ray.getDirection());
		float C = dot(dst, dst) - rad * rad;
		float D = B*B - C;
		data.first = D > 0.0f ? -B - sqrt(D) : std::numeric_limits<float>::infinity();

		if(data.first != std::numeric_limits<float>::infinity())
			data.second = normalize((ray.getOrigin() + data.first * ray.getDirection()) - org);

		return data;
	}
private:
	Vector3<float> org;
	float rad;
};
// class containing a full scene
class Scene
{

public:
	Scene()
	{
		objlist.clear();
	}
	~Scene()
	{
		/*ListType::iterator it = objlist.begin();
		for( ; it != objlist.end(); ++it)
		{
			delete *it;
		}*/
		objlist.clear();
	}

	void pushBack(SceneObject *obj)
	{
		objlist.push_back(ListElement(obj));
	}

	Color traceRay(const Ray& ray, int depth = 0)
	{
		if(depth > 8)
			return Color();

		float t = std::numeric_limits<float>::infinity();
		IntersectData tmp, data;
		SceneObject *hitObj;

		ListType::iterator it = objlist.begin();
		for( ; it != objlist.end(); ++it)
		{
			tmp = (*it)->intersectRay(ray);
			if(tmp.first < t) // only use closest object!
			{
				t = tmp.first;
				data = tmp;
				hitObj = (*it).get();
			}
		}
		
		if(t == std::numeric_limits<float>::infinity())
			return Color();

		Color::DWORD red = hitObj->getColor().getRed();
		Color::DWORD green = hitObj->getColor().getGreen();
		Color::DWORD blue = hitObj->getColor().getBlue();
		Color resultColor;
		float dpr = dot(-ray.getDirection(), data.second);

		if(hitObj->getReflection() > 0)
		{
			
			float refract = 1 - hitObj->getReflection();
			Ray reflectedRay(ray.getOrigin() + ray.getDirection() * data.first,
							 reflect(ray.getDirection(), data.second));
			reflectedRay.setOrigin(reflectedRay.getOrigin() + reflectedRay.getDirection() * 0.0001f);

			Color reflectedColor = traceRay(reflectedRay, depth + 1);
				 
			red   = red   * refract + reflectedColor.getRed() * hitObj->getReflection();
			green = green * refract + reflectedColor.getGreen() * hitObj->getReflection();
			blue  = blue  * refract + reflectedColor.getBlue() * hitObj->getReflection();
		}
		return Color(0xFF, red * dpr, green * dpr, blue * dpr);
	}

	// on top so typedef is visibile..
private:
	typedef std::list<std::unique_ptr<SceneObject> > ListType;
	typedef std::unique_ptr<SceneObject> ListElement;
	ListType objlist;
};

