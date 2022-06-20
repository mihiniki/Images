#include"PlainPgm.h"
const int format_def = 3;
const int buff_def = 5;
PlainPgm::PlainPgm() :Image(), max(0) {}
PlainPgm::PlainPgm(const char* fileName):Image(fileName){}
PlainPgm::PlainPgm(const char* fileName, size_t width, size_t  height, const char* format, size_t max, Pixel** pixels, Pixel** copyPixels) : Image(fileName, width, height, format, pixels, copyPixels) {
	this->max = max;
}
Image* PlainPgm::clone() {
	return new PlainPgm(*this);
}
void PlainPgm::saveAs(const char* newFile) {
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
		}
	}
	out.close();
}
void PlainPgm::open() {
		//std::cout << 5;
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
		in >> buffer;
		max = atoi(buffer);
		std::cout << std::endl << max;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				in.read((char*)&pixels[i][j].r, sizeof(unsigned char));
			}
		}
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				std::cout << pixels[i][j].r << " ";
			}
			std::cout << std::endl;
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
void PlainPgm::Save() {
	std::ofstream out(fileName, std::ios::binary);
	if (!out) {
		return;
	}
	out << format << '\n';
	out << width << " " << height << '\n';
	out << max;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			out.write((const char*)&pixels[i][j].r, sizeof(unsigned char));
		}
	}
	out.close();
}
void PlainPgm::rotateRight() {
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
void PlainPgm::rotateLeft() {
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
void PlainPgm::changeCopy() {
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
void PlainPgm::undo() {
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
	Save();
}
void PlainPgm::grayscale() {

}
void PlainPgm::monochrome() {
	changeCopy();
	size_t middleSum = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			middleSum += pixels[i][j].r;
		}
	}
	middleSum /= (height * width);
	//std::cout << middleSum;

	for (int i = 0; i < height; i++) {
		//size_t middle = 0;
		for (int j = 0; j < width; j++) {

			if (pixels[i][j].r >= middleSum) {
				pixels[i][j].r = 255;
			}
			else {
				pixels[i][j].r = 0;
			}
		}
	}
}
void PlainPgm::negative() {
	changeCopy();

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixels[i][j].r = max - pixels[i][j].r;
		}
	}
}
void PlainPgm::collageHoris(Image* sec, const char* fileName) {


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

	PlainPgm* newObj = new PlainPgm(fileName, widthNew, heightNew, format,max, outImage, outImageCopy);
	newObj->Save();

}
void PlainPgm::collageVert(Image* sec, const char* fileName) {
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

	PlainPgm* newObj = new PlainPgm(fileName, widthNew, heightNew, format, max, outImage, outImageCopy);
	newObj->Save();

}