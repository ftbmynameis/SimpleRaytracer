#pragma once

#include <Windows.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>

#include "Surface.hpp"
#include "Scene.hpp"
#include "Vector.hpp"
#include "BitmapWriter.hpp"

class Raytracer
{
public:
	Raytracer(unsigned int width, unsigned int height)
		:	w(width),
			h(height),
			bitmap(width, height)
	{
		campos.x = 0;
		campos.y = 0;
		campos.z = 0;

		screenz = 0.0f;

		Sphere *s = new Sphere(Vector3<float>(3, 0, 5.0f), 2.0f);
		s->setColor(Color(0xFF, 0, 0, 0xFF));
		Sphere *s2 = new Sphere(Vector3<float>(-2, 1, 8.0f), 2.0f);
		s2->setColor(Color(0xFF, 0xFF, 0, 0));

		Plane *p = new Plane(Vector3<float>(0, -2, 10.0f), Vector3<float>(0, 1.0f, 0.0f));
		p->setColor(Color(0xFF, 0xFF, 0, 0));
		scene.pushBack(p);
		scene.pushBack(s);
		scene.pushBack(s2);
		

		std::cout << "Starting raytracer:" << std::endl;
		render(bitmap);
		createBitmap("raytracer3d3.bmp", w, h, bitmap.getBufferPointer());
		std::cout << std::endl << "Finished!";
		std::cin.get();
	}
private:
	
	void render(Surface<DWORD>& bitmap)
	{
		float stepx = 2.0f / w;
		float stepy = -2.0f / h;

		float dy = 1.0f;

		for(int y = 0; y < h; ++y)
		{
			float dx = -1.0f;
			for(int x = 0; x < w; ++x)
			{

				Ray r(campos, normalize(Vector3<float>(dx, dy, 1.0f)));
				bitmap(x, y) = scene.traceRay(r, 0).getColor();
				
				dx += stepx;
			}
			dy += stepy;
		}
	}
	
	Vector3<float> campos;
	unsigned int w, h;
	float screenz;
	Surface<DWORD> bitmap;
	Scene scene;
};