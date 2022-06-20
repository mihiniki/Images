#include"Image.h"
const int DEF_LEN = 10;
Image::Image():fileName(new char[MIN_LEN]), width(DEF_LEN), height(DEF_LEN), format(new char[1]), pixels(new Pixel*[DEF_LEN]), copyPixels(new Pixel* [DEF_LEN]) {
	fileName[0] = '\0';
	format[0] = '\0';
	copyWidth = width;
	copyHeight = height;
	for (int i = 0; i < height; i++) {
		pixels[i] = new Pixel[width];
	}
	for (int i = 0; i < copyHeight; i++) {
		copyPixels[i] = new Pixel[copyWidth];
	}
}
Image::Image(const char* fileName, size_t width, size_t height, Pixel** pixels, const char* format, Pixel** copyPixels) {
	copy(fileName, width, height, format, pixels, copyPixels);
}
void Image::copy(const char* fileName, size_t width, size_t height, const char* format, Pixel** pixels, Pixel** copyPixels) {
	size_t size = strlen(fileName) + 1;
	this->fileName = new char[size];
	strcpy(this->fileName, fileName);
	this->pixels = new Pixel * [height];
	for (int i = 0; i < height; i++) {
		this->pixels[i] = new Pixel[width];
		for (int j = 0; j < width; j++) {
			this->pixels[i][j].r = pixels[i][j].r;
			this->pixels[i][j].g = pixels[i][j].g;
			this->pixels[i][j].b = pixels[i][j].b;
		}
	}
	copyWidth = width;
	copyHeight = height;
	this->copyPixels = new Pixel * [copyHeight];
	for (int i = 0; i < copyHeight; i++) {
		this->copyPixels[i] = new Pixel[copyWidth];
		for (int j = 0; j < copyWidth; j++) {
			this->copyPixels[i][j].r = pixels[i][j].r;
			this->copyPixels[i][j].g = pixels[i][j].g;
			this->copyPixels[i][j].b = pixels[i][j].b;
		}
	}
	size = strlen(format) + 1;
	this->format = new char[size];
	strcpy(this->format, format);
	
	this->width = width;
	this->height = height;
	//swap(height, width);

}
Image::Image(const char* fileName) {
	this->fileName = new char[strlen(fileName) + 1];
	strcpy(this->fileName, fileName);
}
void Image::clear() {
	delete[]fileName;
	fileName = nullptr;

	delete[]format;
	format = nullptr;
    std::cout << "Delete pixels " << height << " " << width << std::endl;
	for (int i = 0; i < height; i++) {
		delete[]pixels[i];
	}
	delete[]pixels;
	//std::cout << "Delete copyPixels " << copyHeight << " " << copyWidth << std::endl;
	for (int i = 0; i < copyHeight; i++) {
		delete[]copyPixels[i];
	}
	delete[]copyPixels;
}
Image::Image(const char* fileName, size_t width, size_t  height, const char* format, Pixel** pixels, Pixel** copyPixels) {
	copy(fileName, width, height, format, pixels, copyPixels);
}

Image::~Image() {
	clear();
}
Image::Image(Image const& other) {
	copy(other.fileName, other.width, other.height, other.format, other.pixels, other.copyPixels);
}
Image& Image::operator=(Image const& other) {
	if (this != &other) {
		clear();
		copy(other.fileName, other.width, other.height, other.format, other.pixels, other.copyPixels);
	}
	return *this;
}
