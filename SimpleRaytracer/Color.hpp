#ifndef COLOR_HPP
#define COLOR_HPP

#pragma once

class Color
{
public:
	typedef unsigned long DWORD;

	Color(DWORD c = 0)
		:	color(c)
	{
	}
	Color(DWORD a, DWORD r, DWORD g, DWORD b)
		:	color( (a&0xFF) << 24 |
				   (r&0xFF) << 16 |
				   (g&0xFF) <<  8 |
				   (b&0xFF))
	{
	}
	Color(const Color& rhs)
		:	color(rhs.getColor())
	{
	}

	DWORD getColor() const
	{
		return color;
	}
	DWORD getAlpha() const
	{
		return (color >> 24) & 0xFF;
	}
	DWORD getRed() const
	{
		return (color >> 16) & 0xFF;
	}
	DWORD getGreen() const
	{
		return (color >> 8) & 0xFF;
	}
	DWORD getBlue() const
	{
		return (color) & 0xFF;
	}

	Color& operator = (const Color& rhs)	{color = rhs.getColor(); return *this;}

	//Color& operator * (const float f) {color = Color(color.getAlpha() * f, color.getRed() * f, color.getGreen() * f, color.getBlue() * f); return *this;}
	//Color& operator *= (const float f) {color = color * f; return *this;}
private:
	DWORD color;
};

Color operator + (const Color a, const Color& b)	{return Color(a.getAlpha() + b.getAlpha(),
																  a.getRed() + b.getRed(),
																  a.getGreen() + b.getGreen(),
																  a.getBlue() + b.getBlue());}



#endif