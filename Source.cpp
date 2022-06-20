#include<iostream>
#include"PlanePpm.h"
#include"ppm.h"
#include"Image.h"
#include"Pbm.h"
#include"Pgm.h"
#include"Session.h"
#include"Sessions.h"
#include"UserInterface.h"
int main() {
	Pixel pixel1(0, 0, 255);
	
	Pixel** pixels = new Pixel*[10];
	for (int i = 0; i < 10; i++) {
		pixels[i] = new Pixel[5];
		for (int j = 0; j < 5; j++) {
			pixels[i][j] = pixel1;
		}
	}
	InterFase user;
	user.runSessions();
	//Ppm obj1("neshto.ppm", 10, 5, pixels,"P3", 255);
//	obj1.writeToTextFile();
	//Pgm obj1("sample.pgm");
	/*obj1.open();
	obj1.getFormat();
	obj1.monochrome();*/
	//Pgm obj2("sample.pgm");
	//obj2.open();
	/*Image* newDth = obj1.collageHoris(&obj2);
	std::cout << std::endl;
	std::cout << std::endl;
	newDth->open();
	//PpmPlane obj1("sample_640.ppm");
	//Ppm obj("neshto.ppm");
	
	/*Session sess;
	sess.addImage(&obj);
	sess.addImage(&obj1);
	std::cout << std::endl;
	std::cout << std::endl;
	sess.print();
	sess.monochrome();*/
	//sess.undo();
	std::cout << std::endl;
	std::cout << std::endl;
	//obj.print();
	//obj1.rotateRight();
	//std::cout << "NEW\n";
	//obj.grayscale();
	//obj.print();
	//obj.rotateLeft();
	//obj.print();
	//obj.writeToTextFile();
	//obj.rotateLeft();
	//obj.writeToTextFile();
	//obj.rotateLeft();
	//obj.writeToTextFile();
	//obj.monochrome();
	//obj.print();
	//obj.writeToTextFile();
	//obj.rotateLeft();
	//obj.writeToTextFile();
	//obj.undo();
	//obj.print();
	//obj.writeToTextFile();
	//obj.grayscale();
	//Pbm obj("sample.pbm");
	//obj.open();
	//obj.grayscale();
	Image** arri=new Image*[10];
	//arri[0]
	//Session sess(arri,1,0,10);
	//Session sess1(arri,2,0,10);
	//sess.addImage("simple.pgm");
	//sess.addImage("sample.pgm");
	//sess1.addImage("nishto.ppm");
	//sess1.addImage("simple.pgm");
	//sess.arri[0]
	std::cout << std::endl;
	/*for (int i = 0; i < 2; i++) {
		std::cout << sess.getImages()[i]->getFileName() << " ";
	}*/
	/*Session arr[2];
	arr[0] = sess;
	arr[1] = sess1;

	sess.collageVertical("sample.pgm", "simple.pgm", "kuche.pgm");
	std::cout << "count " << sess.getCount() << std::endl;;
	sess.monochrome();
	sess.Save();*/
	//sess.undo();
	/*SessionCollect obj(arr, 5, 2, 1, 2);
	for (int i = 0; i < 2; i++) {
		std::cout << arr[i].getCount();
		for (int j = 0; j < arr[i].getCount(); j++) {
			std::cout<<"TUK" << arr[i].getImages()[j]->getHeight();
		}
	}

	obj.load("neshto.ppm sample.pgm", 2);*/
	//obj.addImage("neshto.ppm");
	//obj.monochrome();
	//obj.load("neshto.ppm sample.pgm", 2);
	//sess.collageVertical()
}