#pragma once
#include"Image.h"
#include"PlanePpm.h"
#include"ppm.h"
#include"PlainPgm.h"
#include"Pgm.h"
#include"PlainPbm.h"
#include"Pbm.h"
class Session {
	Image** images;
	size_t id;
	size_t count;
	size_t capacity;

	int* operations;
	size_t countOperations;
	size_t capacityOperations;

	void copy(Image** images, size_t id, size_t count, size_t capacity, int* operatirons, size_t countOperations, size_t capacityOperations);
	void clear();
	void resize();
	
public:
	Session();
	Session(size_t id);
	Session(Image** images, size_t id, size_t count, size_t capacity, int* operatirons, size_t countOperations, size_t capacityOperations);
	~Session();
	Session(Session const& other);
	Session& operator=(Session const& other);
	void print();
	void addImage(const char* fileName);
	void grayScale();
	void monochrome();
	void changeCopy();
	void doIHaveToSave();
	void undo();
	void Save();
	void SaveAs();
	void rotate(const char* direction);
	void negative();
	void rotateLeft();
	void rotateRight();
	void printtransformations();
	//void SaveAs(const char* newFileName);
	void sessionInfo();
	void collageVertical(const char* first, const char* sec, const char* fileName);
	void collageHorrizontal(const char* first, const char* sec, const char* fileName);
	void addToOperationArr(int number);
	void printDiffTypes(Image* first, Image* sec);
	size_t getId() const;
	size_t getCount() const;
	Image** getImages() const;
}; 
