#pragma once
#include"Image.h"
class ppmBinary : public Image {
private:
	size_t max;
public:
	ppmBinary();
	ppmBinary(const char* fileName) : Image(fileName) {}
	ppmBinary(const char* fileName, size_t width, size_t  height, const char* format, size_t max, Pixel** pixels, Pixel** copyPixels);
	//ppmBinary(const char* fileName, size_t width, size_t height, Pixel** pixels, const char* format, size_t max, Pixel** copyPixels);
	//Ppm(const char* fileName);
	virtual Image* clone() override;
	virtual void writeToTextFile() {};
	virtual void open() {}
	virtual void rotateLeft() {};
	virtual void rotateRight() {};
	virtual void changeCopy() {};
	virtual void undo() {};
	virtual void grayscale() {};
	virtual void monochrome() {};
};