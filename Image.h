#pragma once
#include<fstream>
#include<iostream>
#include<cstring>
const char MIN_LEN = 1;
struct Pixel {
	unsigned short r;
	unsigned short g;
	unsigned short b;

	Pixel() :r(0), g(0), b(0) {}
	Pixel(unsigned short r, unsigned short g, unsigned short b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
};
class Image {
protected:
	char* fileName;
	//Extension extension;
	size_t width;
	size_t height;
	char* format;
	Pixel** pixels;
	Pixel** copyPixels;
	size_t copyWidth;
	size_t copyHeight;
private:
	void copy(const char* fileName, size_t width, size_t height, const char* format, Pixel** pixels, Pixel** copyPixels);
	void clear();
	
public:
	Image();
	Image(const char* fileName, size_t width, size_t height, Pixel** pixels, const char* format, Pixel** copyPixels);
	Image(const char* fileName, size_t width, size_t height, const char* format, Pixel** pixels, Pixel** copyPixels);
	virtual ~Image();
	Image(const char* fileName);
	Image(Image const& other);
	Image& operator=(Image const& other);
	virtual Image* clone() = 0;
	virtual void Save() = 0;
	virtual void open()= 0;
	virtual void rotateLeft() = 0;
	virtual void rotateRight() = 0;
	virtual void changeCopy() = 0;
	virtual void undo() = 0;
	virtual void grayscale() = 0;
	virtual void monochrome() = 0;
	virtual void negative() = 0;
	virtual void  collageHoris(Image* sec, const char* fileName) = 0;
	virtual void  collageVert( Image* sec, const char* fileName) = 0;
	virtual void saveAs(const char* fileName) = 0;
	char* getFileName() const {
		return fileName;
	}
	size_t getWidth() const {
		return width;
	}
	size_t getHeight() const {
		return height;
	}
	char* getFormat() const {
		return format;
	}
	Pixel** getPixelTable() const {
		return pixels;
	}
	Pixel** getCopyPixelTable() const {
		return copyPixels;
	}
	//virtual void load();
	/*virtual void close();
	virtual void save();
	virtual void saveAs();
	virtual void help();
	virtual void exit();
	virtual void rotate();
	*/
	void swap(size_t& a, size_t& b) {
		size_t buff;
		buff = a;
		a = b;
		b = buff;
	}
	
};