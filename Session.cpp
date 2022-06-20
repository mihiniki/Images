#include"Session.h"
const int DEF_CAP = 10;
const int DEF_BOOL = 6;
const int DEF_FORM = 3;
const int DEF = 1024;
Session::Session():images(new Image* [DEF_CAP]), id(1), count(0), capacity(DEF_CAP), operations(new int[DEF_CAP]), capacityOperations(DEF_CAP), countOperations(0) {
}
Session::Session(size_t id) : images(new Image* [DEF_CAP]), count(0), capacity(DEF_CAP), operations(new int[DEF_CAP]), capacityOperations(DEF_CAP), countOperations(0) {
	this->id = id;
}
void Session::copy(Image** images, size_t id, size_t count, size_t capacity, int* operatirons, size_t countOperations, size_t capacityOperations) {
	this->count = count;
	this->capacity = capacity;
	this->id = id;

	this->images = new Image * [capacity];
	for (int i = 0; i < count; i++) {
		this->images[i] = images[i]->clone();
	}

	this->operations = new int[capacityOperations];
	for (int i = 0; i < countOperations; i++) {
		this->operations[i] = operations[i];
	}

	this->capacityOperations=capacityOperations;
	this->countOperations = countOperations;
}
void Session::clear() {
	for (int i = 0; i < count; i++) {
		delete images[i];
	}
	delete[]images;

	delete[]operations;
}

Session::Session(Image** images, size_t id, size_t count, size_t capacity, int* operations, size_t countOperations, size_t capacityOperations) {
	copy(images, id, count, capacity, operations, countOperations, capacityOperations);
}
Session& Session::operator=(Session const& other) {
	if (this != &other) {
		clear();
		copy(other.images, other.id, other.count, other.capacity, other.operations, other.countOperations, other.capacityOperations);
	}
	return *this;
}
Session::Session(Session const& other) {
	copy(other.images, other.id, other.count, other.capacity, other.operations, other.countOperations, other.capacityOperations);
}
Session::~Session() {
	clear();
}
char* readFrFileFormat(const char* fileName) {
	std::ifstream in(fileName);
	if (!in) {
		std::cout << "Error!\n";
	}
	char* buffer=new char[DEF_FORM];
	in.getline(buffer, DEF_FORM);
	in.close();
	return buffer;
}
void Session::resize() {
	Image** buffer = new Image * [capacity * 2];
	for (int i = 0; i < capacity; i++) {
		buffer[i] = images[i];
	}
	capacity *= 2;
	delete[]images;
	images = buffer;
}

void Session::addToOperationArr(int number) {
	if (countOperations < capacityOperations) {

		operations[countOperations++] = number;
	}
}
void Session::addImage(const char* fileName) {
	
	addToOperationArr(6);
	char* format = readFrFileFormat(fileName);
	
	if (count == capacity) {
		resize();
	}
	if (strcmp(format, "P6")==0) {
		Image* newObj = new PpmPlane(fileName);
		newObj->open();
		images[count++] = newObj->clone();
	}
	else if (strcmp(format, "P3")==0) {
		Image* newObj = new Ppm(fileName);
		newObj->open();
		images[count++] = newObj->clone();
	}
	else if (strcmp(format, "P2")==0) {
		Image* newObj = new Pgm(fileName);
		newObj->open();
		images[count++] = newObj->clone();
	}
	else if (strcmp(format, "P5")==0) {
		Image* newObj = new PlainPgm(fileName);
		newObj->open();
		images[count++] = newObj->clone();
	}
	else if (strcmp(format, "P1")==0) {
		Image* newObj = new Pbm(fileName);
		newObj->open();
		images[count++] = newObj->clone();
	}
	else if (strcmp(format, "P4")==0) {
		Image* newObj = new PlainPbm(fileName);
		newObj->open();
		images[count++] = newObj->clone();
	}
	std::cout << "Image" << " " << fileName << " added\n";
	
	delete[]format;
	
	
}
void Session::undo() {
	//std::cout << "IN";
	for (int i = 0; i < count; i++) {
		images[i]->undo();
	}
}
void Session::changeCopy() {
	for (int i = 0; i < count; i++) {
		images[i]->changeCopy();
	}
}
void  Session::doIHaveToSave() {
	std::cout << "Do you want to save?\n";
	char YesOrNo[DEF_BOOL];
	std::cin >> YesOrNo;

	if (strcmp("Yes", YesOrNo) == 0) {
		std::cout << YesOrNo;
		Save();
	}
}
void Session::grayScale() {
	//changeCopy();
	addToOperationArr(1);
	for (int i = 0; i < count; i++) {
		images[i]->grayscale();
	}
	
	//doIHaveToSave();
}
void Session::monochrome() {
	//changeCopy();
	addToOperationArr(1);
	std::cout << std::endl << count;
	for (int i = 0; i < count; i++) {
		std::cout << i;
		//images[i]->open();
		//std::cout << "kuche\n";
		std::cout << images[i]->getFormat() << std::endl;
		std::cout << std::endl;
		images[i]->monochrome();
		//images[i]->writeToTextFile();
	}
	//doIHaveToSave();
}
void Session::Save() {
	for (int i = 0; i < count; i++) {
		images[i]->Save();
	}
}
void Session::rotateLeft() {
	addToOperationArr(3);
	for (int i = 0; i < count; i++) {
		images[i]->rotateLeft();
	}
}
void Session::rotateRight() {
	addToOperationArr(4);
	for (int i = 0; i < count; i++) {
		images[i]->rotateRight();
	}
}
void Session::rotate(const char* direction) {
	
	if (strcmp(direction, "Left")==0) {
		rotateLeft();
	}
	else if (strcmp(direction, "Right") == 0) {
		rotateRight();
	}
	else {
		std::cout << "Error!";
	}
}
void Session::negative() {
	addToOperationArr(2);
	for (int i = 0; i < count; i++) {
		images[i]->negative();
	}
}
void Session::print() {
	for (int i = 0; i < count; i++) {
		std::cout << images[i]->getFileName() << " ";
	}
	std::cout << std::endl;
}
void Session::collageHorrizontal(const char* first, const char* sec, const char* fileName) {
	//std::cout << "COLLAGE" << '\n';
	for (int i = 0; i < count; i++) {
		if (strcmp(images[i]->getFileName(), first) == 0) {
			
			for (int j = 0; j < count; j++) {
				if (strcmp(images[j]->getFileName(), sec)==0) {
					//std::cout<<2
					images[i]->collageHoris(images[j], fileName);
					if (count == capacity) {
						//resize();
					}
					std::cout << fileName;
					addImage(fileName);
					break;
				}
			}
			break;
		}
	}
	//Image* newElement=first->collageHoris(sec, fileName);
	//newElement->writeToTextFile();
	/*Image*
	addImage(fileName);
	
	char* format = new char[strlen(first->getFormat()) + 1];
	size_t width = first->getWidth() + sec->getWidth();
	size_t height = first->getHeight();
	Pixel** outImage = new Pixel * [height];
	for (int i = 0; i < height; i++) {
		outImage[i] = new Pixel[width];
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < first->getWidth(); i++) {
			outImage[i][j].r = first->getPixelTable()[i][j].r;
			outImage[i][j].g = first->getPixelTable()[i][j].g;
			outImage[i][j].b = first->getPixelTable()[i][j].b;
		}
	}

	
	size_t copyHeight = height;
	size_t copyWidth = width;
	
	Pixel** outImageCopy = new Pixel * [height];
	for (int i = 0; i < height; i++) {
		outImage[i] = new Pixel[width];
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < first->getWidth(); i++) {
			outImage[i][j].r = first->getPixelTable()[i][j].r;
			outImage[i][j].g = first->getPixelTable()[i][j].g;
			outImage[i][j].b = first->getPixelTable()[i][j].b;
		}
	}*/
}
void Session::collageVertical(const char* first, const char* sec, const char* fileName) {
	//std::cout << "COLLAGE" << '\n';
	for (int i = 0; i < count; i++) {
		if (strcmp(images[i]->getFileName(), first) == 0) {
			
			for (int j = 0; j < count; j++) {
				if (strcmp(images[j]->getFileName(), sec) == 0) {
					//std::cout<<2
					images[i]->collageVert(images[j], fileName);
					if (strcmp(images[i]->getFormat(), images[j]->getFormat()) != 0) {
						std::cout << "Cannot make a collage from different types! (.";
						printDiffTypes(images[i], images[j]);
						break;
					}
					if (count == capacity) {
						//resize();
					}
					std::cout << fileName;
					addImage(fileName);
					break;
				}
			}
			break;
		}
	}
}
void Session::printtransformations() {
	for (int i = 0; i < countOperations; i++) {
		if (operations[i] == 1) {
			std::cout << ", grayscale";
		}
		else if (operations[i] == 2) {
			std::cout << ", negative";
		}
		else if (operations[i] == 0) {
			std::cout << ", monochrome";
		}
		else if (operations[i] == 3) {
			std::cout << ", rotate left";
		}
		else if (operations[i] == 4) {
			std::cout << ", rotate right";
		}
	}
}
void Session::printDiffTypes(Image* first, Image* sec) {
	char buff[DEF_BOOL];
	for (int i = 0; i<strlen(first->getFileName()) + 1; ++i){
		if (first->getFileName()[i] == '.') {
			int p = 0;
			int j = i;
			while (first->getFileName()[j] != '\0') {
				buff[p++] = first->getFileName()[j++];
			}
		}
	}
	std::cout << buff << " ";
	for (int i = 0; i < strlen(sec->getFileName()) + 1; ++i) {
		if (sec->getFileName()[i] == '.') {
			int p = 0;
			int j = i;
			while (sec->getFileName()[j] != '\0') {
				buff[p++] = sec->getFileName()[j++];
			}
		}
	}
	std::cout << buff;
}
void Session::sessionInfo() {
	std::cout << "Name of images in the session: ";
	print();
	std::cout << "Pending transformations: ";
	printtransformations();
}
size_t Session::getId() const {
	return id;
}
Image** Session::getImages() const {
	return images;
}
size_t Session::getCount() const {
	return count;
}
void Session::SaveAs() {
	char buffer[DEF];
	for (int i = 0; i < count; i++ ) {
		std::cin.getline(buffer, DEF);
		images[i]->saveAs(buffer);
	}
}
//void Session::addImaage