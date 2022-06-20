#include"UserInterface.h"
const int def_buff = 1024;
const int small_buff = 10;
void InterFase::chooseOperation() {
	std::cout << "For monochrome manipulation, choose 0" << std::endl;
	std::cout << "For grayscale manipulation, choose 1"<<std::endl;
	std::cout << "For negative manipulation, choose 2" << std::endl;
	std::cout << "For rotation choose 3" << std::endl;
	std::cout << "To undo last manipulation choose 4" << std::endl;
	std::cout << "To add image choose 5" << std::endl;
	std::cout << "For making collage choose 6" << std::endl;
	std::cout << "If you want to save choose 7" << std::endl;
	std::cout << "If you want to Save As choose 8" << std::endl;
	std::cout << "If you want to Exit choose 9" << std::endl;
	std::cout << "If you want Session info choose 10" << std::endl;
	std::cout << "For switching session choose 11" << std::endl;
	std::cout << "If you want help choose 12" << std::endl;
	std::cout << "If you want open new Session choose 13" << std::endl;
}

void InterFase::runSessions() {
	char files[def_buff];
	size_t count;
	std::cin.getline(files, def_buff);
	std::cin >> count;
	sessionsCollect.load(files, count);

	int chooseOperations;
	bool statement = true;
	while (statement) {
		chooseOperation();
		std::cin >> chooseOperations;
		switch (chooseOperations)
		{
		case 0:
			sessionsCollect.monochrome();
			break;
		case 1:
			sessionsCollect.grayscale();
			break;

		case 2:
			sessionsCollect.negative();
			break;

		case 3:
			std::cin.get();
			char direction[small_buff];
			std::cin >> direction;
			sessionsCollect.rotate(direction);
			break;
		case 4:
			sessionsCollect.undo();
			break;
		case 5:
			std::cin.get();
			char fileImage[def_buff];
			std::cin.getline(fileImage, def_buff);
			sessionsCollect.addImage(fileImage);
			break;
		case 6:
			std::cin.get();
			char rotation[small_buff];
			char first[def_buff];
			char second[def_buff];
			char newFile[def_buff];
			std::cin.getline(first, def_buff);
			std::cin.getline(second, def_buff);
			std::cin >> rotation;
			std::cin.getline(newFile, def_buff);
			sessionsCollect.collage(first, second,rotation, newFile);
			break;
		case 7:
			sessionsCollect.save();
			break;
		case 8:
			sessionsCollect.saveAs();
			break;
		case 9:
			sessionsCollect.doYouWantToSave();
			statement = false;
			break;
		case 10:
			sessionsCollect.sessionInfo();
			break;
		case 11:
			int id;
			std::cin >> id;
			sessionsCollect.switchSession(id);
			break;
		case 12:
			//SessionCollect
			sessionsCollect.Help();
			break;
		case 13:
			std::cin.get();
			runSessions();
			break;
		}
	

	}
}