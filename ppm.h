#pragma once
#include"Image.h"

class Ppm: public Image {
private:
	size_t max;
public:
	Ppm();
	Ppm(const char* fileName): Image(fileName) {

	}
	Ppm(const char* fileName, size_t width, size_t  height, const char* format, size_t max, Pixel** pixels, Pixel** copyPixels);
	Ppm(const char* fileName, size_t width, size_t height, Pixel** pixels, const char* format, size_t max, Pixel** copyPixels);
	//Ppm(const char* fileName);
	virtual Image* clone() override;
	virtual void Save() override;
	virtual void changeCopy() override;
	void print();
	virtual void open() override;
	virtual void grayscale() override;
	virtual void monochrome() override;
	virtual void rotateLeft() override;
	virtual void rotateRight() override;
	virtual void negative() override;
	virtual void undo() override;
	virtual void  collageHoris(Image* sec, const char* fileName);
	virtual void  collageVert(Image* sec, const char* fileName);
	virtual void saveAs(const char* fileName) override;
	void swapPixels(Pixel& first, Pixel& sec);
};