#pragma once
#include"Image.h"
class Pgm : public Image {
private:
	size_t max;
public:
	Pgm();
	Pgm(const char* fileName);
	Pgm(const char* fileName, size_t width, size_t  height, const char* format, size_t max, Pixel** pixels, Pixel** copyPixels);
	//Pgm(const char* fileName, size_t width, size_t height, Pixel** pixels, const char* format, size_t max);
	virtual Image* clone() override;
	virtual void Save() override;
	//void print();
	virtual void open() override;
	virtual void grayscale() override;
	virtual void monochrome() override;
	virtual void rotateLeft();
	virtual void rotateRight();
	virtual void changeCopy() override;
	virtual void undo() override;
	virtual void negative() override;
	virtual void  collageHoris(Image* sec, const char* fileName);
	virtual void  collageVert(Image* sec, const char* fileName);
	virtual void saveAs(const char* fileName) override;
};