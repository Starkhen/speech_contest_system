#pragma once
#include <iostream>
#include <vector>
#include "speaker.h"
#include <map>
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>
using namespace std;
class speechManager
{
public:
	speechManager();
	~speechManager();
	void showMenu();
	void exitS();
	void init();
	void createSpeaker();
	void startSpeech();
	void draw();
	void contest();
	void showScore();
	void saveScore();
	void load();
	void showRecord();
	void clear();
	

public:
	vector<int>v1;//speakers
	vector<int>v2;//First round promotion
	vector<int>victory;//top three
	map<int, speaker> mSpeaker;
	int mRound;
	map<int, vector<string>> mRecord;
	bool isEmpty;
};