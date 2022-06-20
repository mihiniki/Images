#include"ppmBinaryr.h"
ppmBinary::ppmBinary() :Image(), max(0) {}
ppmBinary::ppmBinary(const char* fileName, size_t width, size_t  height, const char* format, size_t max, Pixel** pixels, Pixel** copyPixels) : Image(fileName, width, height, format, pixels, copyPixels) {
	this->max = max;
}

ppmBinary::ppmBinary(const char* fileName) : Image(fileName) {}
Image* ppmBinary::clone() {
	return new ppmBinary(*this);
}
/*void ppmBinary::open() {
	std::ifstream in(fileName, std::ios::binary);
	if (!in) {
		return;
	}
	size_t size = 0;
	in.read((char*)&size, sizeof(size_t));
	format = new char[size];
	in.read(format, size);
	std::cout << format;
	in.close();
}*/
