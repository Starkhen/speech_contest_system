#include "speechManager.h"

speechManager::speechManager()
{
	this->init();
	this->createSpeaker();
	this->load();
}

speechManager::~speechManager()
{
}

void speechManager::showMenu()
{
	cout << "*****************************************************************" << endl;
	cout << "*************  Welcome to join in the speech contest ************" << endl;
	cout << "*************  1.begin to contest  ******************************" << endl;
	cout << "*************  2.history  ***************************************" << endl;
	cout << "*************  3.clean the record  ******************************" << endl;
	cout << "*************  0.exit the program  ******************************" << endl;
	cout << "*****************************************************************" << endl;
	cout << endl;
}
void speechManager::exitS()
{
	cout << "Thanks" << endl;
	system("pause");
	exit(0);
}
void speechManager::init()
{
	this->v1.clear();
	this->v2.clear();
	this->victory.clear();
	this->mSpeaker.clear();
	this->mRound = 1;
	this->mRecord.clear();
}
void speechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "player";
		name += nameSeed[i];

		speaker sp;
		sp.mName = name;
		for (int j = 0; j < 2; j++)
		{
			sp.mScore[j] = 0;
		}
		this->v1.push_back(i + 10001);
		this->mSpeaker.insert(make_pair(i + 10001, sp));
	}
}
void speechManager::startSpeech()
{
	//first round
	//1.draw lots
	draw();
	//2.contest
	contest();
	//3.show the promotion
	showScore();
	//sencond round
	this->mRound++;
	//1.draw lots
	draw();
	//2.contest
	contest();
	//3.show the victory
	showScore();
	//4.save
	saveScore();//if you can not see ,Please refreash!
	//5.reset
	this->init();
	this->createSpeaker();
	this->load();
	cout << "THE CONTEST IS OVER!" << endl;
	this->mRound = 1;
	system("pause");
	system("cls");

}
void speechManager::draw()
{
	cout << "Round" << this->mRound << endl;
	cout << "**********************************" << endl;
	cout << "order:" << endl;
	if (this->mRound == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "**********************************" << endl;
	system("pause");
	cout << endl;
}
void speechManager::contest()
{
	cout << "round " << this->mRound << "begin" << endl;
	multimap<double, int, greater<int>> groupSocre;//temp,save the score and id
	int num = 0;
	vector<int>vSrc;//player
	if (this->mRound == 1)
	{
		vSrc = v1;
	}
	else
	{
		vSrc = v2;
	}
	for (vector<int>::iterator it = vSrc.begin(); it != vSrc.end(); it++)
	{
		num++;
		//getscore
		deque<double>d;
		//rand to get the score
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();

		this->mSpeaker[*it].mScore[this->mRound - 1] = avg;
		groupSocre.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "the" << num / 6 << "group" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupSocre.begin(); it != groupSocre.end(); it++)
			{
				cout << "id:" << it->second << "name:" << this->mSpeaker[it->second].mName << "score:" 
					<< this->mSpeaker[it->second].mScore[this->mRound - 1] << endl;
			}
			int count = 0;
			for (multimap<double, int, greater<int>>::iterator it = groupSocre.begin(); it != groupSocre.end() && count < 3; it++, count++)
			{
				if (this->mRound == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					victory.push_back((*it).second);
				}
			}
			groupSocre.clear();
			cout << endl;
		}
	}
	system("pause");
}
void speechManager::showScore()
{
	cout << this->mRound << "winner" << endl;
	vector<int>v;
	if (this->mRound == 1)
	{
		v = v2;
	}
	else
	{
		v = victory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "id:" << *it << "name:" << mSpeaker[*it].mName << "score:" << mSpeaker[*it].mScore[this->mRound - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->showMenu();
}

void speechManager::saveScore()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	if (!ofs.is_open())
	{
		cout << "OPEN FAILED!" << endl;
		return;
	}
	for (vector<int>::iterator it = victory.begin(); it != victory.end(); it++)
	{
		ofs << *it << "," << mSpeaker[*it].mScore[1] << ",";
		//cout << *it << "," << mSpeaker[*it].mScore[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "Save successfully!" << endl;
	this->isEmpty = false;
}

void speechManager::load()
{
	ifstream ifs("speech.csv", ios::in);
	if(!ifs.is_open())
	{
		this->isEmpty = true;
		cout << "The file is not exist" << endl;
		ifs.close();
		return;
	}
	
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "empty" << endl;
		this->isEmpty = true;
		ifs.close();
		return;
	}
	this->isEmpty = false;
	ifs.putback(ch);//put the char back
	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string>v;
		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string tmp = data.substr(start, pos - start);
			v.push_back(tmp);
			start = pos + 1;
		}
		this->mRecord.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}

void speechManager::showRecord()
{
	if (this->isEmpty)
	{
		cout << "empty or not exist" << endl;
	}
	for (int i = 0; i < this->mRecord.size(); i++)
	{
		cout << "the" << i + 1 << ":" << "1st:" << this->mRecord[i][0] << "score:" << this->mRecord[i][1] << " "
			<< "2nd:" << this->mRecord[i][2] << "score:" << this->mRecord[i][3] << " "
			<< "3rd:" << this->mRecord[i][4] << "score:" << this->mRecord[i][5] << " " << endl;


	}
	system("pause");
	system("cls");
}

void speechManager::clear()
{
	cout << "REALLY?1.y2.n" << endl;
	int choice;
	cin >> choice;
	if (choice == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		this->init();
		this->createSpeaker();
		this->load();
		cout << "FInish" << endl;
	}
	system("pause");
	system("cls");

}



void test(speechManager sm)
{
	for (map<int, speaker>::iterator it = sm.mSpeaker.begin(); it != sm.mSpeaker.end(); it++)
	{
		cout << "id" << it->first
			<< "name" << it->second.mName
			<< "score:" << it->second.mScore[0] << endl;
	}
}
void test00()
{
	ofstream ofs;
	ofs.open("test.txt", ios::out);

	ofs << "姓名：张三" << endl;
	ofs << "性别：男" << endl;
	ofs << "年龄：18" << endl;

	ofs.close();
}
int main()
{
	srand((unsigned int)time(NULL));
	speechManager sm;
	int choice = 0;
	//test00();
	//test(sm);
	while (true)
	{
		sm.showMenu();
		cout << "enter your choice:" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://begin to contest
			sm.startSpeech();
			break;
		case 2://2.history
			sm.showRecord();
			break;
		case 3://3.clean the record
			sm.clear();
			break;
		case 0://0.exit the program
			sm.exitS();
			break;
		default:
			system("cls");
			break;
		}
	}
	
	system("pause");
	return 0;
}
