#pragma once
#include"Sessions.h"
#include<cstring>
class InterFase {
private:
	SessionCollect sessionsCollect;
	void chooseOperation();
	
public:
	void runSessions();
};