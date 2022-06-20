#pragma once
#include"Image.h"
class PlainPgm: public Image {
private:
	size_t max;
public:
	PlainPgm();
	PlainPgm(const char* fileName);
	PlainPgm(const char* fileName, size_t width, size_t  height, const char* format, size_t max, Pixel** pixels, Pixel** copyPixels);
	//ppmBinary(const char* fileName, size_t width, size_t height, Pixel** pixels, const char* format, size_t max, Pixel** copyPixels);
	//Ppm(const char* fileName);
	virtual Image* clone() override;
	virtual void Save();
	virtual void open();
	virtual void rotateLeft();
	virtual void rotateRight();
	virtual void changeCopy();
	virtual void undo();
	virtual void grayscale();
	virtual void monochrome();
	virtual void negative() override;
	virtual void  collageHoris(Image* sec, const char* fileName);
	virtual void  collageVert(Image* sec, const char* fileName);
	virtual void saveAs(const char* fileName) override;
};