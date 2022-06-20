#include"Pgm.h"
const int def = 5;
const int big = 1024;
Pgm::Pgm() :Image(), max(0) {}
Pgm::Pgm(const char* fileName) : Image(fileName) {}
Pgm::Pgm(const char* fileName, size_t width, size_t  height, const char* format, size_t max, Pixel** pixels, Pixel** copyPixels) : Image(fileName, width, height, format, pixels, copyPixels) {
	this->max = max;
}
void Pgm::saveAs(const char* newFile) {
	std::ofstream out(newFile);
	if (!out) {
		return;
	}
	out << format << '\n';
	
	out << width;
	out << ' ';
	out << height;
	out << '\n';
	out << max;
	out << '\n';
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			out << pixels[i][j].r << ' ';
			
		}
		
	}
	out.close();
}
void Pgm::Save(){
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
			out << pixels[i][j].r << ' ';
			//out << ' ';
		}
		//out << '\n';
	}
	out.close();
}
void Pgm::open() {
	std::ifstream in(fileName);
	std::cout << fileName;
	if (!in) {
		std::cout << "Error!";
		return;
	}
	char buffer[big];
	
	in.getline(buffer, big);
	format = new char[strlen(buffer) + 1];
	strcpy(format, buffer);
	
	char arr[def];
	int p = 0;
	in.getline(buffer, big);
	char arr1[5];
	int d = 0;
	for (int i = 0; buffer[i] != ' '; i++) {
		arr1[d++] = buffer[i];
	}
	arr1[d] = '\0';
	width = atoi(arr1);
	std::cout << "width " << width;

	for (int i = 0; i < strlen(buffer) + 1; i++) {

		if (buffer[i] == ' ') {
			int j = i + 1;
			while (j != strlen(buffer)) {
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

	in.getline(buffer, def);
	//std::cout << buffer;
	max = atoi(buffer);
	//std::cout << std::endl;
	//std::cout << "max " << max;
	in.getline(buffer, big*2);
	//std::cout << buffer;
	pixels = new Pixel * [height];
	for (int i = 0; i < height; i++) {
		pixels[i] = new Pixel[width];
	}
	
	char arrBuf[def];
	int arrNew[big];

	int m = 0;
	//std::cout << buffer << std::endl;
	//std::cout << strlen(buffer) + 1;
	for (int i = 0; i < strlen(buffer) + 1; i++) {
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

	/*std::cout << "RAZMER" << "  " << m << std::endl;
	for (int i = 0; i < m; i++) {
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
			pixels[i][j].r = arrNew[q++];
			
		}
	}
	copyWidth = width;
	copyHeight = height;
	copyPixels = new Pixel * [copyHeight];
	for (int i = 0; i < copyHeight; i++) {
		copyPixels[i] = new Pixel[copyWidth];
	}
	for (int i = 0; i < copyHeight; i++) {
		for (int j = 0; j < copyWidth; j++) {
			copyPixels[i][j].r = pixels[i][j].r;
		}
	}
	

	/*for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << pixels[i][j].r << " ";
		}
		std::cout << '\n';
	}*/
	std::cout << "Successfully opened " << fileName<<'\n';
	in.close();
}
Image* Pgm::clone() {
	return new Pgm(*this);
}
void Pgm::changeCopy() {
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
	/*for (int i = 0; i < copyHeight; i++) {
		for (int j = 0; j < copyWidth; j++) {
			std::cout << copyPixels[i][j].r << " ";
		}
		std::cout << std::endl;
	}*/
}
void Pgm::undo(){
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
	/*std::cout << std::endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << pixels[i][j].r << " ";
		}
		std::cout << std::endl;
	}*/
	Save();
}
void Pgm::rotateRight() {
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
	std::cout << std::endl;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			pixels[i][j].r = copyPixels[j][i].r;
		}
	}
	
	std::cout << std::endl;
	
	std::cout << width << " " << height << std::endl;
	for (int i = 0; i < width; i++) {
		int ind = height - 1;
		for (int j = 0; j < height / 2; j++) {
			//std::cout<<pixels[i][j].r<<" "<<pixels[][]
			unsigned short buff = pixels[i][j].r;
			pixels[i][j].r = pixels[i][ind].r;
			 pixels[i][ind--].r=buff;
		}
	}
	/*for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			std::cout << pixels[i][j].r << " ";
		}
		std::cout << '\n';
	}*/
	swap(height, width);
	std::cout << std::endl;
	/*for (int i = 0; i < copyHeight; i++) {
		for (int j = 0; j <copyWidth ; j++) {
			std::cout << copyPixels[i][j].r << " ";
		}
		std::cout << '\n';
	}*/
	/*std::cout << std::endl;
	for (int i = 0; i <height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << pixels[i][j].r << " ";
		}
		std::cout << '\n';
	}*/
}
void Pgm::rotateLeft() {
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
	/*std::cout << std::endl;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			std::cout << pixels[i][j].r << " ";
		}
		std::cout << std::endl;
	}*/
	swap(width, height);
}
void Pgm::grayscale() {

}
void Pgm::monochrome() {
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
	/*std::cout << "NEW";
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << pixels[i][j].r << " ";
		}
		std::cout << std::endl;
	}*/
}
void Pgm::negative() {
	changeCopy();

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixels[i][j].r = max - pixels[i][j].r;
		}
	}
	
}
void Pgm::collageHoris(Image* sec, const char* fileName) {
	

	
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
			outImageCopy[i][j].r = pixels[i][j].r;
		}
		int p = j;
		for (int m = 0; m < sec->getWidth(); m++, p++) {
			outImage[i][p].r = sec->getPixelTable()[i][m].r;
		}
	}
	/*std::cout << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < heightNew; i++) {
		for (int j = 0; j < widthNew; j++) {
			std::cout << outImage[i][j].r << " ";
		}
		std::cout<<std::endl;
	}*/

	Pgm* newObj=new Pgm(fileName, widthNew, heightNew ,format, max, outImage, outImageCopy);
	newObj->Save();

}
void Pgm::collageVert(Image* sec, const char* fileName) {
	

	size_t widthNew = width;
	size_t heightNew = height+sec->getHeight();
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
	/*std::cout << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < heightNew; i++) {
		for (int j = 0; j < widthNew; j++) {
			std::cout << outImage[i][j].r << " ";
		}
		std::cout << std::endl;
	}*/

	Pgm* newObj = new Pgm(fileName, widthNew, heightNew, format, max, outImage, outImageCopy);
	newObj->Save();

	
}
//void Pgm::collageVert() {

//}