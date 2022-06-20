#include"PlainPbm.h"
const int format_def = 3;
const int buff_def = 5;
PlainPbm::PlainPbm() :Image() {}
PlainPbm::PlainPbm(const char* fileName) : Image(fileName) {}
PlainPbm::PlainPbm(const char* fileName, size_t width, size_t  height, const char* format, Pixel** pixels, Pixel** copyPixels) : Image(fileName, width, height, format, pixels, copyPixels) {}
Image* PlainPbm::clone() {
	return new PlainPbm(*this);
}
void PlainPbm::saveAs(const char* newFile) {
	std::ofstream out(newFile, std::ios::binary);
	if (!out) {
		return;
	}
	out << format << '\n';
	out << width << " " << height << '\n';

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			out.write((const char*)&pixels[i][j].r, sizeof(unsigned char));
		}
	}
	out.close();
}
void PlainPbm::open() {
	std::ifstream in(fileName, std::ios::binary);
	std::cout << fileName;
	std::cout << std::endl;
	if (!in) {
		std::cout << "Error!";
		return;
	}

	format = new char[format_def];
	in.read(format, format_def - 1);
	format[format_def - 1] = '\0';

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

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			in.read((char*)&pixels[i][j].r, sizeof(unsigned char));
		}
	}

	copyWidth = width;
	copyHeight = height;
	copyPixels = new Pixel * [height];
	for (int i = 0; i < height; i++) {
		copyPixels[i] = new Pixel[width];
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			copyPixels[i][j].r = pixels[i][j].r;
		}
	}
	in.close();
}
void PlainPbm::Save() {
	std::ofstream out(fileName, std::ios::binary);
	if (!out) {
		return;
	}
	out << format << '\n';
	out << width << " " << height << '\n';

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			out.write((const char*)&pixels[i][j].r, sizeof(unsigned char));
		}
	}
	out.close();
}
void PlainPbm::rotateRight() {
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
		}
	}
	for (int i = 0; i < width; i++) {
		int ind = height - 1;
		for (int j = 0; j < height / 2; j++) {
			unsigned short buff = pixels[i][j].r;
			pixels[i][j].r = pixels[i][ind].r;
			pixels[i][ind--].r = buff;
		}
	}
	std::cout << std::endl;;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			std::cout << pixels[i][j].r;
		}
		std::cout << std::endl;
	}
	swap(height, width);
}

void PlainPbm::rotateLeft() {
	changeCopy();

	for (int i = 0; i < height; i++) {
		delete[]pixels[i];
	}
	delete[]pixels;

	pixels = new Pixel * [width];
	for (int i = 0; i < width; i++) {
		pixels[i] = new Pixel[height];
	}
	//std::cout<<copyHeight
	//int m = copyHeight - 1;
	int p = copyWidth - 1;
	//std::cout << p << " " << m << std::endl;
	//std::cout << copyPixels[0][p].r;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			pixels[i][j].r = copyPixels[j][p].r;
		}
		p--;
	}
	std::cout << std::endl;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			std::cout << pixels[i][j].r << " ";
		}
		std::cout << std::endl;
	}
	swap(width, height);
}
void PlainPbm::changeCopy() {
	for (int i = 0; i < copyHeight; i++) {
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
		}
	}
}
void PlainPbm::undo() {
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
		}
	}
}
void PlainPbm::monochrome() {

}
void PlainPbm::grayscale() {
	changeCopy();
	const float r = 0.299F;
	const float g = 0.587F;
	const float b = 0.114F;


	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			pixels[i][j].r = pixels[i][j].r * r + pixels[i][j].g * g + pixels[i][j].b * b;
		}
	}
}
void PlainPbm::negative() {

}
void PlainPbm::collageHoris(Image* sec, const char* fileName) {


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
		}
		int p = j;
		for (int m = 0; m < sec->getWidth(); m++, p++) {
			outImage[i][p].r = sec->getPixelTable()[i][m].r;
		}
	}

	PlainPbm* newObj = new PlainPbm(fileName, widthNew, heightNew, format, outImage, outImageCopy);
	newObj->Save();

}

void PlainPbm::collageVert(Image* sec, const char* fileName) {
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
		}
	}
	int p = 0;
	for (int i = height; i < heightNew; i++) {
		for (int j = 0; j < sec->getWidth(); j++) {
			outImage[i][j].r = sec->getPixelTable()[p][j].r;
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

	PlainPbm* newObj = new PlainPbm(fileName, widthNew, heightNew, format, outImage, outImageCopy);
	newObj->Save();

}