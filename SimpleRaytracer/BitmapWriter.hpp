#ifndef BITMAPWRITER_HPP
#define BITMAPWRITER_HPP

#pragma once

#include <Windows.h> // bitmap structs

void createBitmap(const std::string& filename, unsigned int width, unsigned int height, DWORD* pixeldata)
{
	std::fstream fileStream(filename, std::ios::binary | std::ios::out);
	BITMAPFILEHEADER fileHeader = { 0x4D42,
		54 + (width + (4 - ((width * 3) % 4))) * height,
		0,
		0,
		54 };
	BITMAPINFOHEADER fileInfoHeader = { 40, width, height * (-1), 1, 24, BI_RGB, 0, 0, 0, 0, 0 };

	/* BitmapFileHeader */
	fileStream.write(reinterpret_cast<char*>(&fileHeader), sizeof(BITMAPFILEHEADER));

	/* BitmapInfoHeader */
	fileStream.write(reinterpret_cast<char*>(&fileInfoHeader), sizeof(BITMAPINFOHEADER));

	DWORD *pdataptr = pixeldata;
	for (unsigned int y = 0; y < height; ++y)
	{
		pdataptr = pixeldata + width * y;
		unsigned int x = 0;
		for (; x < width; ++x, ++pdataptr)
		{
			DWORD pixel = *pdataptr;
			char bgr[3] = { (pixel & 0x000000ff) >> 0,
				(pixel & 0x0000ff00) >> 8,
				(pixel & 0x00ff0000) >> 16 };
			fileStream.write(reinterpret_cast<char*>(&bgr), sizeof(char)* 3);
		}
		if ((x * 3) % 4 != 0)
		{
			int padding = 4 - ((x * 3) % 4);
			for (int i = 0; i < padding; ++i)
			{
				char c = 0;
				fileStream.write(reinterpret_cast<char*>(&c), sizeof(char));
			}
		}
	}

	fileStream.close();
}

#endif