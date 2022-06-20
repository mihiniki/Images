#include"PlanePpm.h"
const int format_def = 3;
const int buff_def = 5;
PpmPlane::PpmPlane() : Image(), max(0) {}
PpmPlane::PpmPlane(const char* fileName, size_t width, size_t  height, const char* format, size_t max, Pixel** pixels, Pixel** copyPixels) : Image(fileName, width, height, format, pixels, copyPixels) {
	this->max = max;
}
Image* PpmPlane::clone() {
	return new PpmPlane(*this);
}
void PpmPlane::saveAs(const char* newFile) {
	std::ofstream out(newFile, std::ios::binary);
	if (!out) {
		return;
	}
	out << format << '\n';
	out << width << " " << height << '\n';
	out << max;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			out.write((const char*)&pixels[i][j].r, sizeof(unsigned char));
			out.write((const char*)&pixels[i][j].g, sizeof(unsigned char));
			out.write((const char*)&pixels[i][j].b, sizeof(unsigned char));
		}
	}
	out.close();
}
void PpmPlane::open() {
	//std::cout << 5;
	std::ifstream in(fileName, std::ios::binary);
	std::cout << fileName;
	std::cout << std::endl;
	if (!in) {
		//std::cout << "p";
		return;
	}
	
	//size_t size = 0;
	//in.read((char*)&size, sizeof(size_t));
	//std::cout << size;
	format = new char[format_def];
	in.read(format, format_def-1);
	format[format_def-1] = '\0';
	std::cout << format;
	std::cout << std::endl;
	char buffer[buff_def];
	in >> buffer;
	//std::cout << widthAr;
	width = atoi(buffer);
	std::cout << width << " ";
	in >> buffer;
	height = atoi(buffer);
	std::cout << height;
	pixels = new Pixel * [height];
	for (int i = 0; i < height; i++) {
		pixels[i] = new Pixel[width];
	}
	in >> buffer;
	max = atoi(buffer);
	std::cout << std::endl << max;
	/*Pixel pixells[1000];
	for (int i = 0; i < 50; i++) {
		in.read((char*)&pixells[i].r, sizeof(unsigned char));
		in.read((char*)&pixells[i].g, sizeof(unsigned char));
		in.read((char*)&pixells[i].b, sizeof(unsigned char));
	}*/
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			in.read((char*)&pixels[i][j].r, sizeof(unsigned char));
			in.read((char*)&pixels[i][j].g, sizeof(unsigned char));
			in.read((char*)&pixels[i][j].b, sizeof(unsigned char));
		}
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << pixels[i][j].r << " ";
			std::cout << pixels[i][j].g << " ";
			std::cout << pixels[i][j].b << " ";
		}
		std::cout << std::endl;
	}
	copyWidth = width;
	copyHeight = height;
	copyPixels = new Pixel*[height];
	for (int i = 0; i < height; i++) {
		copyPixels[i] = new Pixel[width];
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			copyPixels[i][j].r = pixels[i][j].r;
			copyPixels[i][j].g = pixels[i][j].g;
			copyPixels[i][j].b = pixels[i][j].b;
		}
	}
	in.close();
}
void PpmPlane::Save() {
	std::ofstream out(fileName, std::ios::binary);
	if (!out) {
		return;
	}
	out << format << '\n';
	out << width << " " << height << '\n';
	out << max ;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			out.write((const char*)&pixels[i][j].r, sizeof(unsigned char));
			out.write((const char*)&pixels[i][j].g, sizeof(unsigned char));
			out.write((const char*)&pixels[i][j].b, sizeof(unsigned char));
		}
	}
	out.close();
}
void PpmPlane::swapPixels(Pixel& a, Pixel& b) {
	Pixel copy;
	copy.r = b.r;
	copy.g = b.g;
	copy.b = b.b;

	b.r = a.r;
	b.g = a.g;
	b.b = a.b;

	a.r = copy.r;
	a.g = copy.g;
	a.b = copy.b;
}
void PpmPlane::rotateRight() {
	changeCopy();
	for (int i = 0; i < height; i++) {
		delete[]pixels[i];
	}
	delete[]pixels;

	//swap(height, width);

	pixels = new Pixel * [width];
	for (int i = 0; i < width; i++) {
		pixels[i] = new Pixel[height];
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			pixels[i][j].r = copyPixels[j][i].r;
			pixels[i][j].g = copyPixels[j][i].g;
			pixels[i][j].b = copyPixels[j][i].b;
		}
	}
	for (int i = 0; i < width; i++) {
		int index = height - 1;
		for (int j = 0; j < height / 2; j++) {
			swapPixels(pixels[i][j], pixels[i][index--]);
		}
	}
	std::cout << std::endl;;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			std::cout << pixels[i][j].r << " " << pixels[i][j].g << " " << pixels[i][j].b<<" ";
		}
		std::cout << std::endl;
	}
	swap(height, width);
}
void PpmPlane::rotateLeft() {
	changeCopy();
	for (int i = 0; i < height; i++) {
		delete[]pixels[i];
	}
	delete[]pixels;

	//swap(height, width);

	pixels = new Pixel * [width];
	for (int i = 0; i < width; i++) {
		pixels[i] = new Pixel[height];
	}
	//std::cout<<copyHeight
	//int m = copyHeight - 1;
	int p = copyWidth - 1;
	//std::cout << p << " " << m << std::endl;
	std::cout << copyPixels[0][p].r;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			pixels[i][j].r = copyPixels[j][p].r;
			pixels[i][j].g = copyPixels[j][p].g;
			pixels[i][j].b = copyPixels[j][p].b;
		}
		p--;
	}
	swap(width, height);
}
void PpmPlane::changeCopy() {
	for (int i = 0; i < height; i++) {
		delete[]copyPixels[i];
	}
	delete[]copyPixels;

	copyHeight = height;
	copyWidth = width;

	copyPixels = new Pixel * [copyHeight];
	for (int i = 0; i < copyHeight; i++) {
		copyPixels[i] = new Pixel[copyWidth];
	}

	for (int i = 0; i < copyHeight; i++) {
		for (int j = 0; j < copyWidth; j++) {
			copyPixels[i][j].r = pixels[i][j].r;
			copyPixels[i][j].g = pixels[i][j].g;
			copyPixels[i][j].b = pixels[i][j].b;
		}
	}
}
void PpmPlane::undo() {
	for (int i = 0; i < height; i++) {
		delete[]pixels[i];
	}
	delete[]pixels;
	height = copyHeight;
	width = copyWidth;
	pixels = new Pixel * [height];
	for (int i = 0; i < height; i++) {
		pixels[i] = new Pixel[width];
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixels[i][j].r = copyPixels[i][j].r;
			pixels[i][j].g = copyPixels[i][j].g;
			pixels[i][j].b = copyPixels[i][j].b;
		}
	}
	Save();
}
void PpmPlane::grayscale() {
	changeCopy();
	const float r = 0.299F;
	const float g = 0.587F;
	const float b = 0.114F;

	//width = 10;
	//height = 5;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixels[i][j].r = pixels[i][j].r * r + pixels[i][j].g * g + pixels[i][j].b * b;
			pixels[i][j].g = pixels[i][j].r * r + pixels[i][j].g * g + pixels[i][j].b * b;
			pixels[i][j].b = pixels[i][j].r * r + pixels[i][j].g * g + pixels[i][j].b * b;
		}
	}
}
void PpmPlane::monochrome() {
	changeCopy();
	size_t middleSum = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			middleSum += pixels[i][j].r;
			middleSum += pixels[i][j].g;
			middleSum += pixels[i][j].b;
		}
	}
	middleSum /= (height * width * 3);
	std::cout << middleSum;

	for (int i = 0; i < height; i++) {
		size_t middle = 0;
		for (int j = 0; j < width; j++) {
			middle += pixels[i][j].r;
			middle += pixels[i][j].g;
			middle += pixels[i][j].b;
			if (middle / 3 >= middleSum) {
				pixels[i][j].r = 255;
				pixels[i][j].g = 255;
				pixels[i][j].b = 255;
			}
			else {
				pixels[i][j].r = 0;
				pixels[i][j].g = 0;
				pixels[i][j].b = 0;
			}
		}
	}
}
void PpmPlane::negative(){
	changeCopy();

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixels[i][j].r = max - pixels[i][j].r;
			pixels[i][j].g = max - pixels[i][j].g;
			pixels[i][j].b = max - pixels[i][j].b;
		}
	}
	

}
void PpmPlane::collageHoris(Image* sec, const char* fileName) {


	char* formatNew = new char[strlen(format) + 1];
	size_t widthNew = sec->getWidth() + width;
	size_t heightNew = height;
	Pixel** outImage = new Pixel * [heightNew];
	for (int i = 0; i < heightNew; i++) {
		outImage[i] = new Pixel[widthNew];
	}
	Pixel** outImageCopy = new Pixel * [heightNew];
	for (int i = 0; i < heightNew; i++) {
		outImageCopy[i] = new Pixel[widthNew];
	}
	for (int i = 0; i < heightNew; i++) {
		int j = 0;
		for (j = 0; j < width; j++) {
			outImage[i][j].r = pixels[i][j].r;
			outImage[i][j].g = pixels[i][j].g;
			outImage[i][j].b = pixels[i][j].b;
		}
		int p = j;
		for (int m = 0; m < sec->getWidth(); m++, p++) {
			outImage[i][p].r = sec->getPixelTable()[i][m].r;
			outImage[i][p].g = sec->getPixelTable()[i][m].g;
			outImage[i][p].b = sec->getPixelTable()[i][m].b;
		}
	}

	PpmPlane* newObj = new PpmPlane(fileName, widthNew, heightNew, format,max, outImage, outImageCopy);
	newObj->Save();

}
void PpmPlane::collageVert(Image* sec, const char* fileName) {
	size_t widthNew = width;
	size_t heightNew = height + sec->getHeight();
	Pixel** outImage = new Pixel * [heightNew];
	for (int i = 0; i < heightNew; i++) {
		outImage[i] = new Pixel[widthNew];
	}
	Pixel** outImageCopy = new Pixel * [heightNew];
	for (int i = 0; i < heightNew; i++) {
		outImageCopy[i] = new Pixel[widthNew];
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			outImage[i][j].r = pixels[i][j].r;
			outImage[i][j].g = pixels[i][j].g;
			outImage[i][j].b = pixels[i][j].b;
		}
	}
	int p = 0;
	for (int i = height; i < heightNew; i++) {
		for (int j = 0; j < sec->getWidth(); j++) {
			outImage[i][j].r = sec->getPixelTable()[p][j].r;
			outImage[i][j].g = sec->getPixelTable()[p][j].g;
			outImage[i][j].b = sec->getPixelTable()[p][j].b;
		}
		p++;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < heightNew; i++) {
		for (int j = 0; j < widthNew; j++) {
			std::cout << outImage[i][j].r << " ";
		}
		std::cout << std::endl;
	}

	PpmPlane* newObj = new PpmPlane(fileName, widthNew, heightNew, format, max, outImage, outImageCopy);
	newObj->Save();

}