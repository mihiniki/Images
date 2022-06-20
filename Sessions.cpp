#include"Sessions.h"
const int def_cap=10;
const int null =0;
const int def_buff = 5;

SessionCollect::SessionCollect():sessions(new Session[def_cap]), currentSessId(0), nextSessId(null), count(null), capacity(def_cap){}
void SessionCollect::copy(Session* sessions, size_t capacity, size_t count, size_t currentSessId, size_t nextSessId) {
	this->sessions = new Session[capacity];
	for (int i = 0; i < count; i++) {
		this->sessions[i] = sessions[i];
	}

	this->capacity = capacity;
	this->count = count;

	this->currentSessId = currentSessId;
	this->nextSessId = nextSessId;
}

SessionCollect::SessionCollect(Session* sessions, size_t capacity, size_t count, size_t currentSessId, size_t nextSessId){
	copy(sessions, capacity, count, currentSessId, nextSessId);
}
SessionCollect& SessionCollect::operator=(SessionCollect const& other) {
	if (this != &other) {
		clear();
		copy(other.sessions, other.capacity, other.count, other.currentSessId, other.nextSessId);
	}
	return *this;
}
SessionCollect::SessionCollect(SessionCollect const& other) {
	copy(other.sessions, other.capacity, other.count, other.currentSessId, other.nextSessId);
}
SessionCollect::~SessionCollect() {
	clear();
}
void SessionCollect::clear() {
	delete[]sessions;
}
void SessionCollect::load(const char* files, size_t countImage) {
	currentSessId++;
	if (count < capacity) {
		sessions[count++] = Session(currentSessId);
	}
	std::cout << count;
	char** fileArr = new char*[countImage];
	int p = 0;
	for (int i = 0; i < strlen(files)+1; i++) {
		if (i == 0 || files[i] == ' ') {
			fileArr[p] = new char[strlen(files) + 1];
			int ind = 0;
			int j = i+1;
			if (i == 0) {
				j = i;
			}
			while (files[j] != ' ' && files[j] != '\0') {
				fileArr[p][ind++] = files[j++];
			}
			fileArr[p++][ind] = '\0';
		}
	}
	std::cout << "Open Session with ID " << currentSessId << ":\n";
	std::cout << countImage << '\n';
	//std::cout << count<<'\n';
	//std::cout << currentSessId << " " << sessions[i].getId();
	for (int i = 0; i < count; i++) {
		if (currentSessId == sessions[i].getId()) {
			for (int j = 0; j < countImage; j++) {
				//std::cout << "br";
				addImage(fileArr[j]);
			}
			std::cout<<sessions[i].getCount();
			break;
		}
	}

	//currentSessId++;
	delete[]fileArr;
}
void SessionCollect::switchSession(size_t id) {
	std::cout << "You switched on Session with ID" << id << "!\n";
	std::cout << "Name of theimages in the Session: ";
	for (int i = 0; i < count; i++) {
		if (id == sessions[i].getId()) {
			for (int j = 0; j < sessions[i].getCount(); j++) {
				std::cout << sessions[i].getImages()[j]->getFileName() << " ";
			}
			break;
		}
	}
	std::cout << std::endl;
	std::cout << "Panding transformations: ";
	for (int i = 0; i < count; i++) {
		if (id == sessions[i].getId()) {
			for (int j = 0; j < sessions[i].getCount(); j++) {
				 sessions[i].printtransformations();
			}
			break;
		}
	}
}
void SessionCollect::addImage(const char* fileName) {
	
	
	for (int i = 0; i < count; i++) {
		
		if (currentSessId == sessions[i].getId()) {
			
			sessions[i].addImage(fileName);
			break;
		}
	}
}
void SessionCollect::monochrome() {
	for (int i = 0; i < count; i++) {
		std::cout << currentSessId;
		if (currentSessId == sessions[i].getId()) {
			sessions[i].monochrome();
			break;
		}
	}
	//doYouWantToSave();
}
void SessionCollect::negative() {
	for (int i = 0; i < count; i++) {
		std::cout << currentSessId;
		if (currentSessId == sessions[i].getId()) {
			sessions[i].negative();
			break;
		}
	}
}
void SessionCollect::grayscale() {
	for (int i = 0; i < count; i++) {
		if (currentSessId == sessions[i].getId()) {
			sessions[i].grayScale();
			break;
		}
	}
	//doYouWantToSave();
}
void SessionCollect::rotate(const char* direction) {
	for (int i = 0; i < count; i++) {
		if (currentSessId == sessions[i].getId()) {
			sessions[i].rotate(direction);
			break;
		}
	}
	//doYouWantToSave();
}
void SessionCollect::undo() {
	for (int i = 0; i < count; i++) {
		if (currentSessId == sessions[i].getId()) {
			sessions[i].undo();
		}
	}
}
void SessionCollect::save() {
	for (int i = 0; i < count; i++) {
		if (currentSessId == sessions[i].getId()) {
			sessions[i].Save();
		}
	}
}
void SessionCollect::doYouWantToSave() {
	std::cout << "Do you want to save or to Save as?\n";
	char YesOrNo[def_buff];
	std::cin >> YesOrNo;

	if (strcmp("Yes", YesOrNo) == 0) {
		//std::cout << YesOrNo;
		std::cout << "Do you want to save?";
		std::cin >> YesOrNo;
		if (strcmp("Yes", YesOrNo) == 0) {
			save();
		}
		else {
			std::cout << "Do you want to save as?";
				if (strcmp("Yes", YesOrNo) == 0) {
					saveAs();
				}
		}
	}
	/*for (int i = 0; i < count; i++) {
		if (currentSessId == sessions[i].getId()) {
			std::cout<<sessions[i].getCount();
			break;
		}
	}*/
}
void SessionCollect::collage(const char* direction, const char* first, const char* sec, const char* fileName) {
	for (int i = 0; i < count; i++) {
		if (currentSessId == sessions[i].getId()) {
			if (strcmp(direction, "vertical")==0) {
				sessions[i].collageVertical(first,sec,fileName);
			}
			else if (strcmp(direction, "horizontal")) {
				sessions[i].collageHorrizontal(first, sec, fileName);
			}
		}
	}
}
void SessionCollect::sessionInfo() {
	for (int i = 0; i < count; i++) {
		if (currentSessId == sessions[i].getId()) {
			sessions[i].sessionInfo();
			break;
		}
	}
}
void SessionCollect::saveAs() {
	for (int i = 0; i < count; i++) {
		if (currentSessId == sessions[i].getId()) {
			sessions[i].SaveAs();
			break;
		}
	}
}
void SessionCollect::Help() {
	std::cout << "The folowing commands are supported: \n";
	std::cout << "load-> create a session\n";
	std::cout << "save-> save to current file\n";
	std::cout << "save as-> ask for each image where to save\n";
	std::cout << "switch session-> give information for searched session\n";
	std::cout << "session info->give information for current session\n";
	std::cout << "rotate->rotate images in sessiosn\n";
	std::cout << "monochorme, grayscale, negative-> change the color\n";
	std::cout << "rotate->rotate all images\n";
	std::cout << "collage->make collage from two images\n";
}