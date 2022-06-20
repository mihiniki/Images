#pragma once
#include"Session.h"
class SessionCollect {
	Session* sessions;
	size_t currentSessId;
	size_t nextSessId;
	size_t capacity;
	size_t count;

	void copy(Session* sessions, size_t capacity, size_t count, size_t currentSessId, size_t nextSessId);
	void clear();
public:
	SessionCollect();
	
	SessionCollect(Session* sessions, size_t capacity, size_t count, size_t currentSessId, size_t nextSessId);
	SessionCollect(SessionCollect const& other);
	SessionCollect& operator=(SessionCollect const& other);
	~SessionCollect();

	void load(const char* files, size_t count);
	void switchSession(size_t id);
	void sessionInfo();
	void addImage(const char* fileName);
	void monochrome();
	void grayscale();
	void negative();
	void rotate(const char* direction);
	void undo();
	void save();
	void collage(const char* direction, const char* first, const char* sec, const char* fileName);
	void saveAs();
	void Help();
	void doYouWantToSave();
};