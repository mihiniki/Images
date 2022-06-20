#include"ppm.h"
#include<cmath>
#include<iostream>
const int len = 6;
const int max_len = 2024;
Ppm::Ppm() :Image(), max(0) {}
Ppm::Ppm(const char* fileName, size_t width, size_t  height, const char* format, size_t max, Pixel** pixels, Pixel** copyPixels):Image(fileName, width, height,format,pixels, copyPixels) {
	this->max = max;
}
Ppm::Ppm(const char* fileName, size_t width, size_t height, Pixel** pixels, const char* format, size_t max, Pixel** copyPixels) : Image(fileName, width, height, pixels, format, copyPixels) {
	this->max = max;
}
void Ppm::saveAs(const char* newFile) {
	
	std::ofstream out(newFile);

	if (!out) {
		return;
	}
	out << format << '\n';
	//std::cout << format;
	out << width;
	out << ' ';
	out << height;
	out << '\n';
	out << max;
	out << '\n';
	//std::cout << width << " " << height;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			out << pixels[i][j].r << ' ';
			out << pixels[i][j].g << ' ';
			out << pixels[i][j].b << ' ';
			
		}
		
	}
	out.close();
}
void Ppm::Save()  {
	
	std::ofstream out(fileName);

	if (!out) {
		return;
	}
	out << format << '\n';
	//std::cout << format;
	out << width;
	out << ' ';
	out << height;
	out << '\n';
	out << max;
	out << '\n';
	//std::cout << width << " " << height;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				out<< pixels[i][j].r<<' ';
				out<< pixels[i][j].g<<' ';
				out<< pixels[i][j].b<<' ';
				//out << ' ';
			}
			//out << '\n';
		}
	out.close();
}
void Ppm::open() {
	std::ifstream in(fileName);
	std::cout << fileName;
	if (!in) {
		std::cout << "Error!";
		return;
	}
	char buffer[max_len];
	/*in.getline(buffer, 1024, '\n');
	format = new char[strlen(buffer) + 1];
	strcpy(format, buffer);
	std::cout << format;*/
	in.getline(buffer, len);
	format = new char[strlen(buffer) + 1];
	strcpy(format, buffer);
	std::cout<<std::endl;
	std::cout <<"format"<< format<<std::endl;
//	char buffer1[3][1024];
//	int counter = 0;
	char arr[len];
	int p = 0;
	in.getline(buffer,len);
	std::cout << std::endl;
	char arr1[len];
	int d = 0;
	for (int i = 0; buffer[i]!=' '; i++) {
		arr1[d++] = buffer[i];
	}
	arr1[d] = '\0';
	width = atoi(arr1);
	std::cout << "width " << width;

	for (int i = 0; i < strlen(buffer) + 1; i++) {
		
		if (buffer[i] == ' ') {
			int j = i + 1;
			while (j!=strlen(buffer)) {
				arr[p++] = buffer[j++];
				//std::cout << arr[p++];
			}
			arr[p] = '\0';
			break;
		}

		
	}
	height = atoi(arr);
	std::cout << std::endl;
	std::cout << "height " << height;
	//in >> width;
	//in >> height;
	//in >> max;
	
	in.getline(buffer, len);
	std::cout << buffer;
	max = atoi(buffer);
	//std::cout << std::endl;
	std::cout <<"max "<< max;
	in.getline(buffer, max_len);
	//std::cout << buffer;
	//std::cout << buffer;
	pixels = new Pixel * [height];
	for (int i = 0; i < height; i++) {
		pixels[i] = new Pixel[width];
	}

	/*copyPixels = new Pixel * [width];
	for (int i = 0; i < width; i++) {
		copyPixels[i] = new Pixel[height];
	}*/

	for (int i = 0; i <height; i++) {
		for (int j = 0; j < width; j++) {
			/* pixels[i][j].r = ;
			 pixels[i][j].g=;
			 pixels[i][j].b=;*/
		}
	}
	char arrBuf[len];
	int arrNew[max_len];
	
	int m = 0;
	std::cout << buffer<<std::endl;
	std::cout << strlen(buffer) + 1;
	for (int i = 0; i < strlen(buffer)+1; i++) {
		//std::cout << "In";
		if (i == 0 || buffer[i] == ' ') {
			int p = 0;
			int j = i + 1;
			if (i == 0) {
				j = i;
			}
			for (; ; j++) {
				if (buffer[j] == ' ' || buffer[j] == '\0') {
					break;
				}
				arrBuf[p++] = buffer[j];
				
			}
			arrBuf[p] = '\0';
			//std::cout << arrBuf;
			arrNew[m++] = atoi(arrBuf);
			//std::cout << arrNew[m++];
		}
		
	}

	//std::cout << "RAZMER" << "  " << m<<std::endl;
	/*for (int i = 0; i < m; i++) {
		std::cout << arrNew[i] << " ";
	}*/
	/*for (int i = 0; i < strlen(buffer) + 1; i++) {
		if(arr[])
		for (int j = 0; j < width; j++) {
			for (int m= 0; m < height; m++) {
				/* pixels[i][j].r = ;
				 pixels[i][j].g=;
				 pixels[i][j].b=;
			}
		}
	}*/
	int q = 0;
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			//std::cout << arrNew[q];
			 pixels[i][j].r = arrNew[q];
			 pixels[i][j].g = arrNew[q+1];
			 pixels[i][j].b = arrNew[q+2];
			 q += 3;
		}
	}
	
	copyHeight = height;
	copyWidth = width;
	copyPixels = new Pixel * [copyHeight];
	for (int i = 0; i < copyHeight; i++) {
		copyPixels[i] = new Pixel[copyWidth];
	}
	for (int i = 0; i < copyHeight; i++) {
		for (int j = 0; j < copyWidth; j++) {
			copyPixels[i][j].r = pixels[i][j].b;
			copyPixels[i][j].g = pixels[i][j].g;
			copyPixels[i][j].b = pixels[i][j].b;
		}
	}
	std::cout << "Successfully opened " << fileName;
	in.close();
}

void Ppm::print() {
	//swap(height, width);
	std::cout << std::endl;
	std::cout << height << " " << width << std::endl;
	for (int i = 0; i <height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << pixels[i][j].r << " " << pixels[i][j].g << " " << pixels[i][j].b << " ";
			std::cout << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	//swap(height, width);
	for (int i = 0; i<copyHeight; i++) {
		for (int j = 0; j <copyWidth; j++) {
		std::cout << copyPixels[i][j].r << " " << copyPixels[i][j].g << " " << copyPixels[i][j].b << " ";
		std::cout << " ";
		}
	std::cout << std::endl;
	}
}
void Ppm::grayscale() {
	//std::cout<<"GRAY";
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
	
	//print();
}
void Ppm::monochrome() {
	//std::cout << "HERREEEEEEEEEEEEE!!!!!!!!!!!!!!!";
	changeCopy();
	size_t middleSum = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			middleSum += pixels[i][j].r;
			middleSum += pixels[i][j].g;
			middleSum += pixels[i][j].b;
		}
	}
	middleSum /= (height * width*3);
	//std::cout << middleSum;
	
	for (int i = 0; i < height; i++) {
		size_t middle = 0;
		for (int j = 0; j < width; j++) {
			middle+= pixels[i][j].r;
			middle+= pixels[i][j].g;
			middle+= pixels[i][j].b;
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
Image* Ppm::clone() {
	return new Ppm(*this);
}
void Ppm::swapPixels(Pixel& a, Pixel& b) {
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
/*109 109 108 115 115 114 99 104 102 118 116 116 77 74 74 82 79 79 121 121 120 121 119 119 27 24 26 92 97 95 88 85 85 121 119 119 91 95 93 113 113 112 30 27 29 119 117 117 77 74 74 82 79 79 127 127 126 122 120 120 29 27 28 31 28 30 135 135 134 128 126 126 93 98 96 114 114 113 91 88 88 131 129 129 112 112 111 81 78 78 110 108 108 131 129 129 29 27 28 32 29 31 113 111 111 134 132 132 96 100 98 170 170 169 115 113 113 139 137 137 0 0*/
void Ppm::undo() {
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
void Ppm::rotateRight() {
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
		for (int j = 0; j < height/2; j++) {
			swapPixels(pixels[i][j], pixels[i][index--]);
		}
	}
	swap(height, width);

	//writeToTextFile();
}
void Ppm::changeCopy() {
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
void Ppm::rotateLeft() {
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
	int m = copyHeight - 1;
	int p = copyWidth - 1;
	std::cout << p << " " << m << std::endl;
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
	//writeToTextFile();
}
void Ppm::negative() {
	changeCopy();

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixels[i][j].r = max - pixels[i][j].r;
			pixels[i][j].g = max - pixels[i][j].g;
			pixels[i][j].b = max - pixels[i][j].b;
		}
	}
	/*std::cout << std::endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << pixels[i][j].r << " " << pixels[i][j].g <<" "<< pixels[i][j].b<<" ";
			
		}
		std::cout << std::endl;
	}*/
}
void Ppm::collageHoris(Image* sec, const char* fileName) {


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

	Ppm* newObj = new Ppm(fileName, widthNew, heightNew, format, max, outImage, outImageCopy);
	newObj->Save();
}
void Ppm::collageVert(Image* sec, const char* fileName) {
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

	Ppm* newObj = new Ppm(fileName, widthNew, heightNew, format, max, outImage, outImageCopy);
	newObj->Save();

}