#pragma once
#include"Image.h"
class Pbm : public Image {
public:
	Pbm();
	Pbm(const char* fileName);
	Pbm(const char* fileName, size_t width, size_t  height, const char* format, Pixel** pixels, Pixel** copyPixels);
	virtual void Save() override;
	void print() {}
	virtual Image* clone() override;
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
	virtual void saveAs(const char* fileName)override;
};