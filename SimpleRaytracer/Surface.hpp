#pragma once

template <typename T>
class Surface
{
public:
	Surface(unsigned int width, unsigned int height)
		:	w(width),
			h(height),
			pd(new T[width * height])
	{
	}

	~Surface()
	{
		delete[] pd;
	}

	T* getBufferPointer() {return pd;}

	unsigned int width() {return w;}
	unsigned int height() {return h;}

	T& operator ()(unsigned int x, unsigned int y)
	{
		return *(pd + y * w + x);
	}

	// set/get method
	T get(unsigned int x, unsigned int y)
	{
		return *(pd + y * w + x);
	}

	void set(unsigned int x, unsigned int y, T c)
	{
		pd[y * w + x] = c;
	}

	void clear(T c = T())
	{
		for(int i = 0; i < w * h; ++i)
			pd[i] = c;
	}


private:
	T* pd; // pixeldata
	unsigned int w, h; // width & height
};