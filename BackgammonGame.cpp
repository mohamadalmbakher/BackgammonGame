//
// 
//			Student name : MOHAMAD ALMBAKHER
//			Student No   : 1306180164
//			Date		 : 30/05/2021
// 
// 
// 
//                                        BackgammonGame

//                                        Player X’s Side                                             |
//                                        --------->>>                                                |   Player X’s Goal is: G1 -> L1
//      |  0A  |  0B  |  0C  |  0D  |  0E  |  0F  |  0G  |  0H  |  0I  |  0J  |  0K  |  0L  |         |   Broken Flake of X :  E3  
//      -------------------------------------------------------------------------------------------   |
//      |  5Y  |      |      |      |  2X  |      |  5X  |      |      |      |      |  2Y  | 1       |
//      |      |      |      |      |      |      |      |      |      |      |      |      | 2       |   Dice No1 is : F3
//      |      |      |      |      | X BR | Di1  | Di2  | Y BR |X OR Y|      |      |      | 3       |   Dice No2 is : G3
//      |      |      |      |      |      |      |      |      |      |      |      |      | 4       |
//      |  5X  |      |      |      |  3Y  |      |  5Y  |      |      |      |      |  2X  | 5       |
//   -----------------------------------------------------------------------------------------------  |
//                                        Player Y’s Side                                             |   Player Y’s Goal is: G5 -> L5
//                                        --------->>>                                                |   Broken Flake of X :  H3 
//******************************************************************************************************************************************************


#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include<vector>


using namespace std;
using std::ifstream;
vector<string> tableStatringStatus;
vector < vector<string>> tabels;
vector <string> movmentVector;
vector <string> playLog;
vector <string> dicAndBrokFlakVector;
vector <string> stringForWritingTofile;
vector <string> stringForWritingLastStatusTofile;
int				flakTakenOutForX = 0;
int				flakTakenOutForY = 0;


string clearSpaceFromString(string ss) {
	string sTemp;
	for (int i = 0; i < ss.size(); i++)
	{
		if (ss[i] != ' ') {
			sTemp.push_back(ss[i]);
		}
	}
	return sTemp;
}
// This function check if the string is just int and request to enter again if the string contain a char
int enter_just_int(string str) {
	string temp;
	for (int i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]))
		{
			cout << "you enter a rong form. you enter just a number\n";
			cin >> temp;
			return enter_just_int(temp);
		}
	}
	return stoi(str);


}

string incDecStringByOne(string s, char op = '+') {
	string sDigitTemp, sCharTemp, resString;
	for (int k = 0; k < s.size(); k++)
	{

		if (isdigit(s[k]))
		{
			sDigitTemp.push_back(s[k]);
		}
		else {
			sCharTemp.push_back(s[k]);

		}

	}

	int intDigitTemp = stoi(sDigitTemp);
	if (op == '+')
	{
		intDigitTemp++;

	}
	else if (op == '-')
	{
		intDigitTemp--;

	}
	if (intDigitTemp == 0)
	{
		return "";
	}
	resString = to_string(intDigitTemp) + sCharTemp;
	return resString;
}

vector<string> tokenize(string s, string del = " ")
{
	vector<string> vString;
	string ss;
	int start = 7;
	int end = s.find(del) + 7;
	while (end != -1) {

		ss = s.substr(start, end - start);
		vString.push_back(ss);
		start = end + del.size();
		end = s.find(del, start);
	}

	return vString;
}
string getLastStatusFromFile(string fileName) {
	ifstream file;
	string line;
	string found = "";
	string str = "status";
	file.open(fileName);
	unsigned int currline = 0;
	while (getline(file, line)) {
		currline++;
		if (line.find(str, 0) != string::npos) {
			found = line;
		}
	}
	file.close();
	return found;
}

int translateIndexTodigit(string s) {
	int indexTemp = 0;
	switch (s[0])
	{
	case 'A':
	case 'a':
		indexTemp = 11;
		break;
	case 'B':
	case 'b':
		indexTemp = 10;
		break;
	case 'C':
	case 'c':
		indexTemp = 9;
		break;
	case 'D':
	case 'd':
		indexTemp = 8;
		break;
	case 'E':
	case 'e':
		indexTemp = 7;
		break;
	case 'F':
	case 'f':
		indexTemp = 6;
		break;
	case 'G':
	case 'g':
		indexTemp = 5;
		break;
	case 'H':
	case 'h':
		indexTemp = 4;
		break;
	case 'I':
	case 'i':
		indexTemp = 3;
		break;
	case 'J':
	case 'j':
		indexTemp = 2;
		break;
	case 'K':
	case 'k':
		indexTemp = 1;
		break;
	case 'L':
	case 'l':
		indexTemp = 0;
		break;
	default:
		break;
	}
	if (s[1] == '1') {
		indexTemp = indexTemp;
	}
	else
	{
		indexTemp = indexTemp + (11 - indexTemp) * 2 + 1;
	}
	return indexTemp;
}


void getDataFromFile(string fileName) {
	string lastStatus = getLastStatusFromFile(fileName);
	string playlogLine;
	ifstream indata;
	int num;
	indata.open(fileName);
	if (indata.is_open()) {
		string tp;
		while (getline(indata, tp)) {
			stringForWritingTofile.push_back(tp);

			if (tp.find(lastStatus) != std::string::npos) {

				stringForWritingLastStatusTofile.push_back(tp);
				for (int i = 0; i < 9; i++)
				{
					getline(indata, tp);
					stringForWritingTofile.push_back(tp);
					stringForWritingLastStatusTofile.push_back(tp);

					if (i == 0 || i == 1 || i == 7 || i == 8 || i == 3 || i == 5)
					{
						continue;
					}
					else if (i == 4)
					{
						dicAndBrokFlakVector = tokenize(tp, "|");

					}
					else {
						tabels.push_back(tokenize(tp, "|"));

					}
				}

			}

		}
		indata.close();
	}
	ifstream playLogFile;
	playLogFile.open("playlog.dat");
	while (getline(playLogFile, playlogLine))
	{
		playLog.push_back(playlogLine);

	}
}

void insertMovmentVectorToLastStatus(vector<string> ss, vector<string> op) {
	string sTemp = "";
	vector<string> vTemp;
	sTemp += "      |";

	for (int i = 11; i >= 0; i--)
	{
		sTemp += "  ";

		if (ss[i] == "") {
			sTemp += "  ";

		}
		else
		{
			sTemp += ss[i];

		}
		sTemp += "  |";

	}
	sTemp += " 1  ";
	stringForWritingLastStatusTofile[3] = sTemp;
	sTemp = "";
	sTemp += "      |";

	for (int i = 12; i < ss.size(); i++)
	{
		sTemp += "  ";

		if (ss[i] == "") {
			sTemp += "  ";

		}
		else
		{
			sTemp += ss[i];

		}
		sTemp += "  |";

	}
	sTemp += " 5  ";
	stringForWritingLastStatusTofile[7] = sTemp;
	sTemp = "";
	sTemp += "      |";

	for (int k = 0; k < op.size(); k++)
	{



		sTemp += op[k];


		sTemp += "|";

	}
	sTemp += " 3  ";

	stringForWritingLastStatusTofile[5] = sTemp;

}

// transfer from vector of vector to vector of string 
// player X's goals is start of vector
// player Y's goals is end of vector
vector<string> transferToVector(vector <vector<string>> v) {
	string sTemp;
	vector<string> ss;
	for (int i = v[0].size() - 1; i >= 0; i--)
	{
		for (int k = 0; k < v[0][i].size(); k++)
		{
			if (v[0][i][k] == ' ') {
				continue;
			}
			else
			{
				sTemp.push_back(v[0][i][k]);
			}
		}
		ss.push_back(sTemp);
		sTemp = "";
	}
	for (int j = 0; j < v[1].size(); j++)
	{
		for (int k = 0; k < v[1][j].size(); k++)
		{
			if (v[1][j][k] == ' ') {
				continue;
			}
			else
			{
				sTemp.push_back(v[1][j][k]);
			}
		}
		ss.push_back(sTemp);
		sTemp = "";
	}
	return ss;
}
bool checkFlakIsThere(char player) {
	string sBrokFlakDigitTemp = "", sBrokFlakCharTemp = "";
	int i = 4;
	if (player == 'X')
	{
		i = 4;
	}
	else
	{
		i = 7;

	}
	for (int k = 0; k < dicAndBrokFlakVector[i].size(); k++)
	{

		if (isdigit(dicAndBrokFlakVector[i][k]))
		{
			sBrokFlakDigitTemp.push_back(dicAndBrokFlakVector[i][k]);
		}
		else {
			sBrokFlakCharTemp.push_back(dicAndBrokFlakVector[i][k]);

		}
	}
	if (stoi(sBrokFlakDigitTemp) > 0)
	{
		return true;
	}
	return false;
}

int findSumOfFlakOfPlayer(char player) {
	int sumX = 0, sumY = 0;
	string sDigitTemp, sCharTemp;
	for (int i = 0; i < movmentVector.size(); i++)
	{
		sCharTemp = "";
		sDigitTemp = "";
		for (int j = 0; j < movmentVector[i].size(); j++)
		{
			if (isdigit(movmentVector[i][j]))
			{
				sDigitTemp.push_back(movmentVector[i][j]);
			}
			else
			{
				sCharTemp.push_back(movmentVector[i][j]);
			}
		}
		if (sCharTemp == "X")
		{
			sumX += stoi(sDigitTemp);
		}
		else if (sCharTemp == "Y")
		{
			sumY += stoi(sDigitTemp);

		}

	}
	if (player == 'X')
	{
		return sumX;
	}
	else
	{
		return sumY;
	}


}
bool checkIfAllflakesInGoal(char player) {
	int sumX = 0, sumY = 0;
	string sDigitTemp, sCharTemp;
	if (player == 'X')
	{
		for (int i = 0; i < 6; i++)
		{
			sCharTemp = "";
			sDigitTemp = "";
			for (int j = 0; j < movmentVector[i].size(); j++)
			{
				if (isdigit(movmentVector[i][j]))
				{
					sDigitTemp.push_back(movmentVector[i][j]);
				}
				else
				{
					sCharTemp.push_back(movmentVector[i][j]);
				}
			}
			if (sCharTemp == "X")
			{
				sumX += stoi(sDigitTemp);
			}

		}
		if (sumX + flakTakenOutForX == 15)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	else if (player == 'Y')
	{
		for (int i = 18; i < 24; i++)
		{
			sCharTemp = "";
			sDigitTemp = "";
			for (int j = 0; j < movmentVector[i].size(); j++)
			{
				if (isdigit(movmentVector[i][j]))
				{
					sDigitTemp.push_back(movmentVector[i][j]);
				}
				else
				{
					sCharTemp.push_back(movmentVector[i][j]);
				}
			}
			if (sCharTemp == "Y")
			{
				sumY += stoi(sDigitTemp);
			}

		}
		if (sumY + flakTakenOutForY == 15)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
bool checkIfAvailableMoveToIt(int index, string player) {
	string sGoalCharTemp = "", sGoalDigitTemp = "";
	string goalSlotValue = movmentVector[index];
	if (goalSlotValue == "")
	{
		return true;
	}
	for (int k = 0; k < goalSlotValue.size(); k++)
	{

		if (isdigit(goalSlotValue[k]))
		{
			sGoalDigitTemp.push_back(goalSlotValue[k]);
		}
		else {
			sGoalCharTemp.push_back(goalSlotValue[k]);

		}
	}

	if (sGoalCharTemp == player || (sGoalCharTemp != player && stoi(sGoalDigitTemp) <= 1))
	{
		return true;
	}
	else
	{
		return false;
	}

}
bool checkIfThereNotAvailableForPlayer(string player, vector <int> dices) {
	string sGoalCharTemp;
	int newIndex;
	for (int index = 0; index < movmentVector.size(); index++)
	{
		sGoalCharTemp = "";
		string goalSlotValue = movmentVector[index];
		for (int k = 0; k < goalSlotValue.size(); k++)
		{

			if (!isdigit(goalSlotValue[k]))
			{
				sGoalCharTemp.push_back(goalSlotValue[k]);
			}
		}
		if (sGoalCharTemp == player)
		{
			for (int i = 0; i < dices.size(); i++)
			{
				if (player == "X")
				{
					newIndex = index + dices[i];
				}
				else
				{
					newIndex = index - dices[i];
				}
				if (newIndex > 23 || newIndex < 0)
				{
					return false;
				}
				if (checkIfAvailableMoveToIt(newIndex, player))
				{
					return false;
				}

			}
		}
	}


	return true;
}
vector<int> removeItemFromVector(vector<int> v, int i) {
	vector<int>::iterator it;
	it = v.end();
	it--;
	v.erase(it);
	return v;
}

// This function is for play new turn 
// in this function we proccing all avilable movements for flaks on the playing area
bool playNewRound() {
	bool isFirstStatus = false;
	string sGoalDigitTemp = "", sGoalCharTemp = "", sSourceCharTemp = "", stringTemp = dicAndBrokFlakVector[8];
	int dic1, dic2;
	vector<int> dics;
	vector<int> dicsTemp;
	vector<int> dicsTocheck;
	int timesCount;

	string lastPlayerHasPlayed = "";
	for (int i = 0; i < stringTemp.size(); i++)
	{
		if (stringTemp[i] != ' ') {
			lastPlayerHasPlayed.push_back(stringTemp[i]);
		}


	}
	if (lastPlayerHasPlayed == "XY") {
	reGenerate:
		srand(time(0));
		dic1 = rand() % 7;
		while (dic1 == 0)
		{
			dic1 += rand() % 7;
		}
		dic2 = rand() % 7;
		while (dic2 == 0)
		{
			dic2 += rand() % 7;
		}
		playLog.push_back(to_string(dic1));
		playLog.push_back(to_string(dic2));
		if (dic1 > dic2)
		{
			lastPlayerHasPlayed = "YY";
			isFirstStatus = true;
		}
		else
		{
			lastPlayerHasPlayed = "XX";
			isFirstStatus = true;
		}
	}
	if (lastPlayerHasPlayed == "XX") {

		string slot = "";
		int slotIndex;
		cout << "Now the role of play for <<<<<<<< Player Y >>>>>>>> \n";
		if (!isFirstStatus)
		{
			srand(time(0));
			dic1 = rand() % 7;
			while (dic1 == 0)
			{
				dic1 += rand() % 7;
			}
			dic2 = rand() % 7;
			while (dic2 == 0)
			{
				dic2 += rand() % 7;
			}
		}
		isFirstStatus = false;
		playLog.push_back("Y " + to_string(dic1) + " " + to_string(dic2));
		dicAndBrokFlakVector[5] = "  0" + to_string(dic1) + "  ";
		dicAndBrokFlakVector[6] = "  0" + to_string(dic2) + "  ";
		dicAndBrokFlakVector[8] = "  YY  ";

		cout << "The resualte of dices are: " << dic1 << " and " << dic2 << "\n";
		if (dic1 == dic2)
		{
			dics.push_back(dic1);
			dics.push_back(dic2);
			dics.push_back(dic1);
			dics.push_back(dic2);
			timesCount = 4;
			cout << "The dices are equal => the <<<< player Y >>>> will play 4  times : \n";

		}
		else
		{
			dics.push_back(dic1);
			dics.push_back(dic2);
			timesCount = 2;
			cout << "The dices are not equal => the <<<< player Y >>>> will play 2  times : \n";

		}
		//dicsTocheck = dics;
		int i = 0;
		bool messageHasPrint = false;
		if (checkFlakIsThere('Y'))
		{
			if (!checkIfAvailableMoveToIt(dics[i] - 1, "Y") && !checkIfAvailableMoveToIt(dics[i + 1] - 1, "Y"))
			{
				cout << "Your round has sikiped becasue you can't play any flak in this round\n";
				return false;

			}
			else
			{

				cout << "There is flaks has broken you must to move them before. \n";
				slotIndex = -1;

				messageHasPrint = true;
			}

		}
		else
		{
			/*dicsTemp.clear();
			dicsTemp.push_back(dics[i]);
			if (checkIfThereNotAvailableForPlayer("Y", dicsTemp))
			{
				cout << "You can't play any flak with time: " + to_string(i + 1) + " [" + to_string(dics[i]) + "] " << endl;
				i++;

			}*/
			cout << "Please enter the source slot for the " << i + 1 << ". time dice== [" + to_string(dics[i]) + "] : \n";
			cout << "if you can't move any flak you can enter 0 to skip your turn and give the turn to other player \n\n";
		}
		while (i < timesCount)
		{
			sGoalDigitTemp = ""; sGoalCharTemp = ""; sSourceCharTemp = "";
			if (checkFlakIsThere('Y') && messageHasPrint == false)
			{
				cout << "There is flaks has broken you must to move them before. \n";
				slotIndex = -1;
			}
			if (!checkFlakIsThere('Y'))
			{
				/*dicsTemp.clear();
				dicsTemp.push_back(dics[i]);
				if (checkIfThereNotAvailableForPlayer("Y", dicsTemp))
				{
					cout << "You can't play any flak with time: " + to_string(i + 1) + " [" + to_string(dics[i]) + "] " << endl;
					i++;
				}*/
				cin >> slot;
				if (slot == "0")
				{
					return false;
				}
				slotIndex = translateIndexTodigit(slot);

				string sourceSlotValue = movmentVector[slotIndex];
				for (int k = 0; k < sourceSlotValue.size(); k++)
				{


					if (!isdigit(sourceSlotValue[k])) {
						sSourceCharTemp.push_back(sourceSlotValue[k]);

					}
				}
				if (slotIndex + dics[i] > 23 || sourceSlotValue == "" || sSourceCharTemp == "X")
				{



					bool canTakeOutFromLessSlot = true;
					for (int iSlot = 18; iSlot < slotIndex; iSlot++)
					{
						string otherSourceSlotValue = movmentVector[iSlot];
						string otherSSourceCharTemp = "";

						for (int kkk = 0; kkk < otherSourceSlotValue.size(); kkk++)
						{


							if (!isdigit(otherSourceSlotValue[kkk])) {
								otherSSourceCharTemp.push_back(otherSourceSlotValue[kkk]);
							}
						}
						if (otherSourceSlotValue != "" && otherSSourceCharTemp != "X")
						{
							canTakeOutFromLessSlot = false;
							break;
						}
					}






					if (slotIndex + dics[i] == 24 && checkIfAllflakesInGoal('Y') && sourceSlotValue != "")
					{
						movmentVector[slotIndex] = incDecStringByOne(movmentVector[slotIndex], '-');
						flakTakenOutForY++;
						insertMovmentVectorToLastStatus(movmentVector, dicAndBrokFlakVector);

						for (int v = 0; v < stringForWritingLastStatusTofile.size(); v++)
						{
							cout << stringForWritingLastStatusTofile[v] << endl;
						}
						//dicsTocheck.erase(dicsTocheck.begin() + i);

						i++;
						if (i < timesCount)
						{
							cout << "Please enter the source slot for the " << i + 1 << ". time dice== [" + to_string(dics[i]) + "]: \n";
							cout << "if you can't move any flak you can enter 0 to skip your turn and give the turn to other player \n\n";

						}
					}

					else if (slotIndex + dics[i] >= 24 && canTakeOutFromLessSlot)
					{
						int slotIndexTemp = slotIndex - 1;
						string otherSourceSlotValueToMove = movmentVector[slotIndexTemp];
						string otherSSourceCharTempToMove = "";
						for (int kkkkk = 0; kkkkk < otherSourceSlotValueToMove.size(); kkkkk++)
						{
							if (!isdigit(otherSourceSlotValueToMove[kkkkk])) {
								otherSSourceCharTempToMove.push_back(otherSourceSlotValueToMove[kkkkk]);

							}

						}
						while ((otherSourceSlotValueToMove == "" || otherSSourceCharTempToMove != "Y") && slotIndexTemp > 18)
						{
							slotIndexTemp--;
							otherSourceSlotValueToMove = movmentVector[slotIndexTemp];
							for (int kkkkk = 0; kkkkk < otherSourceSlotValueToMove.size(); kkkkk++)
							{


								if (!isdigit(otherSourceSlotValueToMove[kkkkk])) {
									otherSSourceCharTempToMove.push_back(otherSourceSlotValueToMove[kkkkk]);

								}
							}
						}
						if (slotIndexTemp == 18)
						{
							movmentVector[slotIndex] = incDecStringByOne(movmentVector[slotIndex], '-');
							flakTakenOutForY++;
							insertMovmentVectorToLastStatus(movmentVector, dicAndBrokFlakVector);

							for (int v = 0; v < stringForWritingLastStatusTofile.size(); v++)
							{
								cout << stringForWritingLastStatusTofile[v] << endl;
							}
							//dicsTocheck.erase(dicsTocheck.begin() + i);

							i++;
							if (i < timesCount)
							{
								cout << "Please enter the source slot for the " << i + 1 << ". time dice== [" + to_string(dics[i]) + "]: \n";
								cout << "if you can't move any flak you can enter 0 to skip your turn and give the turn to other player \n\n";

							}
						}
						else
						{
							cout << "You enter rong slot please reenter the source slot for the " << i + 1 << ". time dice== [" + to_string(dics[i]) + "]: \n";

						}
						continue;

					}



					else
					{
						cout << "You enter rong slot please reenter the source slot for the " << i + 1 << ". time dice== [" + to_string(dics[i]) + "]: \n";

					}
					continue;
				}
			}

			messageHasPrint = false;
			string goalSlotValue = movmentVector[slotIndex + dics[i]];
			for (int k = 0; k < goalSlotValue.size(); k++)
			{
				if (isdigit(goalSlotValue[k]))
				{
					sGoalDigitTemp.push_back(goalSlotValue[k]);
				}
				else {
					sGoalCharTemp.push_back(goalSlotValue[k]);

				}
			}
			if (goalSlotValue == "")
			{
				movmentVector[slotIndex + dics[i]] = "1Y";

				if (checkFlakIsThere('Y')) {
					if (incDecStringByOne(dicAndBrokFlakVector[7], '-') == "")
					{
						dicAndBrokFlakVector[7] = "  0Y  ";
					}
					else
					{
						dicAndBrokFlakVector[7] = "  " + incDecStringByOne(dicAndBrokFlakVector[7], '-') + "  ";

					}

				}
				else
				{
					movmentVector[slotIndex] = incDecStringByOne(movmentVector[slotIndex], '-');

				}
				i++;
				if (i < timesCount)
				{
					insertMovmentVectorToLastStatus(movmentVector, dicAndBrokFlakVector);

					for (int a = 0; a < stringForWritingLastStatusTofile.size(); a++)
					{
						cout << stringForWritingLastStatusTofile[a] << endl;
					}
					cout << "Please enter the source slot for the " << i + 1 << ". time dice== [" + to_string(dics[i]) + "]: \n";
					cout << "if you can't move any flak you can enter 0 to skip your turn and give the turn to other player \n\n";

				}
			}
			else if ((stoi(sGoalDigitTemp) > 1 && sGoalCharTemp == "X") || sSourceCharTemp == "X")
			{
				cout << "You enter rong slot please reenter the source slot for the " << i + 1 << ". time dice== [" + to_string(dics[i]) + "]: \n";

			}
			else
			{
				if (stoi(sGoalDigitTemp) == 1 && sGoalCharTemp == "X")
				{
					movmentVector[slotIndex + dics[i]] = "1Y";

					dicAndBrokFlakVector[4] = "  " + incDecStringByOne(clearSpaceFromString(dicAndBrokFlakVector[4]), '+') + "  ";
				}

				else
				{
					movmentVector[slotIndex + dics[i]] = incDecStringByOne(movmentVector[slotIndex + dics[i]], '+');

				}
				if (checkFlakIsThere('Y')) {
					if (incDecStringByOne(dicAndBrokFlakVector[7], '-') == "")
					{
						dicAndBrokFlakVector[7] = "  0Y  ";
					}
					else
					{
						dicAndBrokFlakVector[7] = "  " + incDecStringByOne(dicAndBrokFlakVector[7], '-') + "  ";

					}
				}
				else
				{
					movmentVector[slotIndex] = incDecStringByOne(movmentVector[slotIndex], '-');

				}

				i++;
				if (i < timesCount)
				{
					insertMovmentVectorToLastStatus(movmentVector, dicAndBrokFlakVector);

					for (int v = 0; v < stringForWritingLastStatusTofile.size(); v++)
					{
						cout << stringForWritingLastStatusTofile[v] << endl;
					}
					cout << "Please enter the source slot for the " << i + 1 << ". time dice== [" + to_string(dics[i]) + "]: \n";
					cout << "if you can't move any flak you can enter 0 to skip your turn and give the turn to other player \n\n";

				}
			}


		}



	}
	else if (lastPlayerHasPlayed == "YY") {

		string slot = "";
		int slotIndex;
		cout << "Now the role of play for <<<<<<<< Player X >>>>>>>>: \n\n";
		if (!isFirstStatus)
		{
			srand(time(0));
			dic1 = rand() % 7;
			while (dic1 == 0)
			{
				dic1 += rand() % 7;
			}
			dic2 = rand() % 7;
			while (dic2 == 0)
			{
				dic2 += rand() % 7;
			}
		}
		isFirstStatus = false;
		playLog.push_back("X " + to_string(dic1) + " " + to_string(dic2));
		dicAndBrokFlakVector[5] = "  0" + to_string(dic1) + "  ";
		dicAndBrokFlakVector[6] = "  0" + to_string(dic2) + "  ";
		dicAndBrokFlakVector[8] = "  XX  ";

		cout << "The resualte of dices are: " << dic1 << " and " << dic2 << "\n";
		if (dic1 == dic2)
		{
			dics.push_back(dic1);
			dics.push_back(dic2);
			dics.push_back(dic1);
			dics.push_back(dic2);

			timesCount = 4;
			cout << "The dices are equal => the <<<< player  X >>>> will play 4  times : \n";
		}
		else
		{
			dics.push_back(dic1);
			dics.push_back(dic2);
			timesCount = 2;
			cout << "The dices are not equal => the <<<< player  X >>>> will play 2  times : \n";

		}
		int i = 0;
		bool messageHasPrint = false;
		if (checkFlakIsThere('X'))
		{
			if (!checkIfAvailableMoveToIt(dics[i] - 1, "X") && !checkIfAvailableMoveToIt(dics[i + 1] - 1, "X"))
			{
				cout << "Your round has sikiped becasue you can't play any flak in this round\n";
				return false;

			}
			cout << "There is flaks has broken you must to move them before. \n";
			slotIndex = 24;

			messageHasPrint = true;
		}
		else
		{
			dicsTemp.clear();
			dicsTemp.push_back(dics[i]);
			if (checkIfThereNotAvailableForPlayer("X", dicsTemp))
			{
				cout << "You can't play any flak with time: " + to_string(i + 1) + " [" + to_string(dics[i]) + "] " << endl;
				i++;
				if (i >= timesCount)
				{
					cout << "Your round has ended becasue you can't play more flak in this round\n";
					return false;
				}
			}
			cout << "Please enter the source slot for the " << i + 1 << ". time dice== [" + to_string(dics[i]) + "]: \n";
			cout << "if you can't move any flak you can enter 0 to skip your turn and give the turn to other player \n\n";
		}
		while (i < timesCount)
		{
			sGoalDigitTemp = ""; sGoalCharTemp = ""; sSourceCharTemp = "";

			if (checkFlakIsThere('X') && messageHasPrint == false)
			{
				cout << "There is flaks has broken you must to move them before. \n";
				slotIndex = 24;
			}
			if (!checkFlakIsThere('X'))
			{
				dicsTemp.clear();
				dicsTemp.push_back(dics[i]);
				if (checkIfThereNotAvailableForPlayer("X", dicsTemp))
				{
					cout << "You can't play any flak with time: " + to_string(i + 1) + " [" + to_string(dics[i]) + "] " << endl;
					i++;
					if (i >= timesCount)
					{
						cout << "Your round has ended becasue you can't play more flak in this round\n";
						return false;
					}
				}
				cin >> slot;
				if (slot == "0")
				{
					return false;
				}
				slotIndex = translateIndexTodigit(slot);
				string sourceSlotValue = movmentVector[slotIndex];
				for (int k = 0; k < sourceSlotValue.size(); k++)
				{
					if (!isdigit(sourceSlotValue[k])) {
						sSourceCharTemp.push_back(sourceSlotValue[k]);

					}
				}
				if (slotIndex - dics[i] < 0 || sourceSlotValue == "" || sSourceCharTemp == "Y")
				{
					if (slotIndex - dics[i] <= -1 && checkIfAllflakesInGoal('X') && sourceSlotValue != "")
					{
						bool canTakeOutFromLessSlot = true;
						for (int iSlot = 5; iSlot > slotIndex; iSlot--)
						{
							string otherSourceSlotValue = movmentVector[iSlot];
							string otherSSourceCharTemp = "";

							for (int kkk = 0; kkk < otherSourceSlotValue.size(); kkk++)
							{


								if (!isdigit(otherSourceSlotValue[kkk])) {
									otherSSourceCharTemp.push_back(otherSourceSlotValue[kkk]);
								}
							}
							if (otherSourceSlotValue != "" && otherSSourceCharTemp != "Y")
							{
								canTakeOutFromLessSlot = false;
								break;
							}
						}


						if (slotIndex - dics[i] == -1 && checkIfAllflakesInGoal('X') && sourceSlotValue != "")
						{
							movmentVector[slotIndex] = incDecStringByOne(movmentVector[slotIndex], '-');
							flakTakenOutForX++;
							insertMovmentVectorToLastStatus(movmentVector, dicAndBrokFlakVector);

							for (int v = 0; v < stringForWritingLastStatusTofile.size(); v++)
							{
								cout << stringForWritingLastStatusTofile[v] << endl;
							}
							//dicsTocheck.erase(dicsTocheck.begin() + i);

							i++;
							if (i < timesCount)
							{
								cout << "Please enter the source slot for the " << i + 1 << ". time dice== [" + to_string(dics[i]) + "]: \n";
								cout << "if you can't move any flak you can enter 0 to skip your turn and give the turn to other player \n\n";

							}
						}


						else if (slotIndex - dics[i] <= -1 && canTakeOutFromLessSlot)
						{
							int slotIndexTemp = slotIndex + 1;
							string otherSourceSlotValueToMove = movmentVector[slotIndexTemp];
							string otherSSourceCharTempToMove = "";
							for (int kkkkk = 0; kkkkk < otherSourceSlotValueToMove.size(); kkkkk++)
							{
								if (!isdigit(otherSourceSlotValueToMove[kkkkk])) {
									otherSSourceCharTempToMove.push_back(otherSourceSlotValueToMove[kkkkk]);

								}

							}
							while ((otherSourceSlotValueToMove == "" || otherSSourceCharTempToMove != "X") && slotIndexTemp < 6)
							{
								slotIndexTemp++;
								otherSourceSlotValueToMove = movmentVector[slotIndexTemp];
								for (int kkkkk = 0; kkkkk < otherSourceSlotValueToMove.size(); kkkkk++)
								{


									if (!isdigit(otherSourceSlotValueToMove[kkkkk])) {
										otherSSourceCharTempToMove.push_back(otherSourceSlotValueToMove[kkkkk]);

									}
								}
							}
							if (slotIndexTemp == 6)
							{
								movmentVector[slotIndex] = incDecStringByOne(movmentVector[slotIndex], '-');
								flakTakenOutForX++;
								insertMovmentVectorToLastStatus(movmentVector, dicAndBrokFlakVector);

								for (int v = 0; v < stringForWritingLastStatusTofile.size(); v++)
								{
									cout << stringForWritingLastStatusTofile[v] << endl;
								}
								i++;
								if (i < timesCount)
								{
									cout << "Please enter the source slot for the " << i + 1 << ". time dice== [" + to_string(dics[i]) + "]: \n";
									cout << "if you can't move any flak you can enter 0 to skip your turn and give the turn to other player \n\n";
								}
							}
							else
							{
								cout << "You enter rong slot please reenter the source slot for the " << i + 1 << ". time dice== [" + to_string(dics[i]) + "]: \n";
								continue;
							}


						}
						else
						{
							cout << "You enter rong slot please reenter the source slot for the " << i + 1 << ". time dice== [" + to_string(dics[i]) + "]: \n";
							continue;
						}


					}
					else
					{
						cout << "You enter rong slot please reenter the source slot for the " << i + 1 << ". time dice== [" + to_string(dics[i]) + "]: \n";
					}
					continue;
				}
			}
			messageHasPrint = false;
			string goalSlotValue = movmentVector[slotIndex - dics[i]];
			for (int k = 0; k < goalSlotValue.size(); k++)
			{

				if (isdigit(goalSlotValue[k]))
				{
					sGoalDigitTemp.push_back(goalSlotValue[k]);
				}
				else {
					sGoalCharTemp.push_back(goalSlotValue[k]);

				}
			}
			if (goalSlotValue == "")
			{
				movmentVector[slotIndex - dics[i]] = "1X";

				if (checkFlakIsThere('X')) {
					if (incDecStringByOne(dicAndBrokFlakVector[4], '-') == "")
					{
						dicAndBrokFlakVector[4] = "  0X  ";
					}
					else
					{
						dicAndBrokFlakVector[4] = "  " + incDecStringByOne(dicAndBrokFlakVector[4], '-') + "  ";
					}
				}
				else
				{
					movmentVector[slotIndex] = incDecStringByOne(movmentVector[slotIndex], '-');
				}
				i++;
				if (i < timesCount)
				{
					insertMovmentVectorToLastStatus(movmentVector, dicAndBrokFlakVector);

					for (int v = 0; v < stringForWritingLastStatusTofile.size(); v++)
					{
						cout << stringForWritingLastStatusTofile[v] << endl;
					}
					cout << "Please enter the source slot for the " << i + 1 << ". time dice== [" + to_string(dics[i]) + "]: \n";
					cout << "if you can't move any flak you can enter 0 to skip your turn and give the turn to other player \n\n";
				}
			}
			else if ((stoi(sGoalDigitTemp) > 1 && sGoalCharTemp == "Y") || sSourceCharTemp == "Y")
			{
				cout << "You enter rong slot please reenter the source slot for the " << i + 1 << ". time  dice== [" + to_string(dics[i]) + "]: \n";
			}
			else
			{
				if (stoi(sGoalDigitTemp) == 1 && sGoalCharTemp == "Y")
				{
					movmentVector[slotIndex - dics[i]] = "1X";

					dicAndBrokFlakVector[7] = "  " + incDecStringByOne(clearSpaceFromString(dicAndBrokFlakVector[7]), '+') + "  ";
				}
				else
				{
					movmentVector[slotIndex - dics[i]] = incDecStringByOne(movmentVector[slotIndex - dics[i]], '+');
				}
				if (checkFlakIsThere('X')) {
					if (incDecStringByOne(dicAndBrokFlakVector[4], '-') == "")
					{
						dicAndBrokFlakVector[4] = "  0X  ";
					}
					else
					{
						dicAndBrokFlakVector[4] = "  " + incDecStringByOne(dicAndBrokFlakVector[4], '-') + "  ";

					}
				}
				else
				{
					movmentVector[slotIndex] = incDecStringByOne(movmentVector[slotIndex], '-');

				}
				i++;
				if (i < timesCount)
				{
					insertMovmentVectorToLastStatus(movmentVector, dicAndBrokFlakVector);

					for (int c = 0; c < stringForWritingLastStatusTofile.size(); c++)
					{
						cout << stringForWritingLastStatusTofile[c] << endl;
					}
					cout << "Please enter the source slot for the " << i + 1 << ". time dice== [" + to_string(dics[i]) + "]: \n";
					cout << "if you can't move any flak you can enter 0 to skip your turn and give the turn to other player \n\n";

				}
			}
		}
	}
	return true;
}


// add the new turn has been played to the vector of string that it will be added to file after each turn
void addNewStatusToStringFile() {
	string sTemp = "";
	for (int k = 0; k < stringForWritingLastStatusTofile[0].size(); k++)
	{

		if (isdigit(stringForWritingLastStatusTofile[0][k]))
		{
			sTemp.push_back(stringForWritingLastStatusTofile[0][k]);
		}
	}
	int iTemp = stoi(sTemp);
	string sTemp1 = to_string(iTemp);

	iTemp++;
	string sTemp2 = to_string(iTemp);
	char charTemp = ' ';
	for (int h = 0; h < sTemp2.size(); h++)
	{
		if (sTemp2.size() > sTemp1.size() && h == 0)
		{
			stringForWritingLastStatusTofile[0][6] = sTemp2[h];
		}
		else
		{
			charTemp = stringForWritingLastStatusTofile[0][6 + h];
			stringForWritingLastStatusTofile[0][6 + h] = sTemp2[h];

		}
		if (sTemp2.size() > sTemp1.size() && h == sTemp2.size() - 1) {
			stringForWritingLastStatusTofile[0].push_back(charTemp);
		}

	}
	for (int i = 0; i < stringForWritingLastStatusTofile.size(); i++)
	{

		stringForWritingTofile.push_back(stringForWritingLastStatusTofile[i]);
	}
}

// synchronization the vector of string with the table file
void addLastStatusToFile() {

	ofstream myfile;
	myfile.open("tabel.dat");


	//addNewStatusToStringFile();
	for (int i = 0; i < stringForWritingLastStatusTofile.size(); i++)
	{
		myfile << stringForWritingLastStatusTofile[i] + "\n";

	}
	myfile.close();
	ofstream playLogfile;
	playLogfile.open("playlog.dat");
	for (int j = 0; j < playLog.size(); j++)
	{
		playLogfile << playLog[j] + "\n";

	}
	playLogfile.close();

}
// create new game with set the starting status to table.dat file and clear the content of playlog.dat file
void createNewGame() {
	ofstream tabelfile;
	tabelfile.open("tabel.dat");
	stringForWritingLastStatusTofile.clear();
	stringForWritingTofile.clear();
	movmentVector.clear();
	playLog.clear();
	tabels.clear();
	for (int i = 0; i < tableStatringStatus.size(); i++)
	{
		tabelfile << tableStatringStatus[i] + "\n";

	}
	tabelfile.close();

	ofstream playlogfile;
	playlogfile.open("playlog.dat");
	playlogfile << "";
	playlogfile.close();

}



int main()
{
	tableStatringStatus.push_back("status0:");
	tableStatringStatus.push_back("      |  0A  |  0B  |  0C  |  0D  |  0E  |  0F  |  0G  |  0H  |  0I  |  0J  |  0K  |  0L  |");
	tableStatringStatus.push_back("     -------------------------------------------------------------------------------------------");
	tableStatringStatus.push_back("      |  5Y  |      |      |      |  2X  |      |  5X  |      |      |      |      |  2Y  | 1");
	tableStatringStatus.push_back("      |      |      |      |      |      |      |      |      |      |      |      |      | 2");
	tableStatringStatus.push_back("      |      |      |      |      |  0X  |  00  |  00  |  0Y  |  XY  |      |      |      | 3");
	tableStatringStatus.push_back("      |      |      |      |      |      |      |      |      |      |      |      |      | 4");
	tableStatringStatus.push_back("      |  5X  |      |      |      |  3Y  |      |  5Y  |      |      |      |      |  2X  | 5");
	tableStatringStatus.push_back("   -----------------------------------------------------------------------------------------------");
	tableStatringStatus.push_back("****************************************************************************************************");

	int op, opRound = 1, playTypeOp;
	string str1, strRound, playType;
	cout << "\n\n";
	cout << "Welcome to BackgammonGame\n";
	cout << "**********************************\n";
	// do while to show menu of option of the playing
	do
	{
		cout << "\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
		cout << "\nEnter Your Choice\n";
		cout << "\n";

		cout << "1. Play BackgammonGame\n";
		cout << "\n";
		cout << "0. Close Game\n";

		cin >> str1;
		op = enter_just_int(str1);

		if (op == 1) {
			int fileExist;
			ifstream ifile;
			ifile.open("tabel.dat");
			if (ifile) {
				fileExist = 1;
				ifile.close();
			}
			else {
				fileExist = 0;
			}

			if (fileExist == 1) {
				// show menu to choose of if the player wants to play the old game or create new game 

				cout << "\nThere is a old game do you want to load it or start new game\n";
				cout << "\n";
				cout << "1. Load the old game\n";
				cout << "\n";
				cout << "2. Start new game\n";

				cin >> playType;
				playTypeOp = enter_just_int(playType);
				if (playTypeOp == 1) {
					getDataFromFile("tabel.dat");
					movmentVector = transferToVector(tabels);
					insertMovmentVectorToLastStatus(movmentVector, dicAndBrokFlakVector);
					//addNewStatusToStringFile();
					int sumFlakX = findSumOfFlakOfPlayer('X');
					if (sumFlakX < 15)
					{
						flakTakenOutForX = 15 - sumFlakX;
					}

					int sumFlakY = findSumOfFlakOfPlayer('Y');
					if (sumFlakY < 15)
					{
						flakTakenOutForY = 15 - sumFlakY;
					}

					cout << "Load the old game has been done\n";
					cout << "The last status of the game is:\n";
					for (int i = 0; i < stringForWritingLastStatusTofile.size(); i++)
					{
						cout << stringForWritingLastStatusTofile[i] << endl;
					}

					// do while to show menu to choose if the player wants to play new turn or exit and save the game 

					do
					{

						if (opRound == 1) {
							if (flakTakenOutForX == 15)
							{
								cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
								cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
								cout << "\nCongratulations! <<<<<< player X >>>>>> has won in this game" << endl;
								cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
								cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
								cout << "Now the systim will create new game automatical do you want this? 1 [yes] || 0 [no]" << endl;
								cin >> strRound;
								int newGame;
								newGame = enter_just_int(strRound);
								if (newGame == 1)
								{
									opRound = 0;
									playTypeOp = 2;
									break;
								}
								else
								{
									opRound = 0;
									op = 0;
									break;
								}

							}
							if (flakTakenOutForY == 15)
							{
								cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
								cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
								cout << "\nCongratulations! <<<<<< player Y >>>>>> has won in this game" << endl;
								cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
								cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
								cout << "Now the systim will create new game automatical do you want this? 1 [yes] || 0 [no]" << endl;
								cin >> strRound;
								int newGame;
								newGame = enter_just_int(strRound);
								if (newGame == 1)
								{
									opRound = 0;
									playTypeOp = 2;
									break;
								}
								else
								{
									opRound = 0;
									op = 0;
									break;
								}



							}
							playNewRound();
							insertMovmentVectorToLastStatus(movmentVector, dicAndBrokFlakVector);
							addLastStatusToFile();
							for (int i = 0; i < stringForWritingLastStatusTofile.size(); i++)
							{
								cout << stringForWritingLastStatusTofile[i] << endl;
							}


						}

						cout << "\nDo you want to continue play press 1 to continue or 0 to save game and exit\n";
						cin >> strRound;
						opRound = enter_just_int(strRound);

					} while (opRound != 0);// 0 for exit



				}
				if (playTypeOp == 2)
				{
					// create new game and start the playing 
					createNewGame();
					getDataFromFile("tabel.dat");
					movmentVector = transferToVector(tabels);
					insertMovmentVectorToLastStatus(movmentVector, dicAndBrokFlakVector);
					int sumFlakX = findSumOfFlakOfPlayer('X');
					if (sumFlakX < 15)
					{
						flakTakenOutForX = 15 - sumFlakX;
					}

					int sumFlakY = findSumOfFlakOfPlayer('Y');
					if (sumFlakY < 15)
					{
						flakTakenOutForY = 15 - sumFlakY;
					}
					cout << "New game has been created\n";
					cout << "The first status of the new game is:\n";
					for (int i = 0; i < stringForWritingLastStatusTofile.size(); i++)
					{
						cout << stringForWritingLastStatusTofile[i] << endl;
					}
					opRound = 1;
					// do while to show menu to choose if the player wants to play new turn or exit and save the game 

					do
					{

						if (opRound == 1) {
							if (flakTakenOutForX == 15)
							{
								cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
								cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
								cout << "\nCongratulations! <<<<<< player X >>>>>> has won in this game" << endl;
								cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
								cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
								cout << "Now the systim will create new game automatical do you want this? 1 [yes] || 0 [no]" << endl;
								cin >> strRound;
								int newGame;
								newGame = enter_just_int(strRound);
								if (newGame == 1)
								{
									opRound = 0;
									playTypeOp = 2;
									break;
								}
								else
								{
									opRound = 0;
									op = 0;
									break;
								}

							}
							if (flakTakenOutForY == 15)
							{
								cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
								cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
								cout << "\nCongratulations! <<<<<< player Y >>>>>> has won in this game" << endl;
								cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
								cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
								cout << "Now the systim will create new game automatical do you want this? 1 [yes] || 0 [no]" << endl;
								cin >> strRound;
								int newGame;
								newGame = enter_just_int(strRound);
								if (newGame == 1)
								{
									opRound = 0;
									playTypeOp = 2;
									break;
								}
								else
								{
									opRound = 0;
									op = 0;
									break;
								}



							}
							playNewRound();
							insertMovmentVectorToLastStatus(movmentVector, dicAndBrokFlakVector);
							addLastStatusToFile();
							for (int i = 0; i < stringForWritingLastStatusTofile.size(); i++)
							{
								cout << stringForWritingLastStatusTofile[i] << endl;
							}

						}

						cout << "\nDo you want to continue play press 1 to continue or 0 to save game and exit\n";
						cin >> strRound;
						opRound = enter_just_int(strRound);

					} while (opRound != 0);

				}


			}

			else
			{
				int opCreate;
				cout << "\nThere is no any old game you must to want to create new game\n";
				cout << "\n if you want enter 1 or if you don't want enter 0";
				cin >> strRound;
				opCreate = enter_just_int(strRound);
				if (opCreate != 1)
				{
					continue;
				}
				createNewGame();
				getDataFromFile("tabel.dat");
				movmentVector = transferToVector(tabels);
				insertMovmentVectorToLastStatus(movmentVector, dicAndBrokFlakVector);
				cout << "New game has been created\n";
				cout << "The first status of the new game is:\n";
				for (int i = 0; i < stringForWritingLastStatusTofile.size(); i++)
				{
					cout << stringForWritingLastStatusTofile[i] << endl;
				}
				opRound = 1;
				do
				{

					if (opRound == 1) {
						if (flakTakenOutForX == 15)
						{
							cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
							cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
							cout << "\nCongratulations! <<<<<< player X >>>>>> has won in this game" << endl;
							cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
							cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
							cout << "Now the systim will create new game automatical do you want this? 1 [yes] || 0 [no]" << endl;
							cin >> strRound;
							int newGame;
							newGame = enter_just_int(strRound);
							if (newGame == 1)
							{
								opRound = 0;
								playTypeOp = 2;
								break;
							}
							else
							{
								opRound = 0;
								op = 0;
								break;
							}

						}
						if (flakTakenOutForY == 15)
						{
							cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
							cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
							cout << "\nCongratulations! <<<<<< player Y >>>>>> has won in this game" << endl;
							cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
							cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
							cout << "Now the systim will create new game automatical do you want this? 1 [yes] || 0 [no]" << endl;
							cin >> strRound;
							int newGame;
							newGame = enter_just_int(strRound);
							if (newGame == 1)
							{
								opRound = 0;
								playTypeOp = 2;
								break;
							}
							else
							{
								opRound = 0;
								op = 0;
								break;
							}



						}
						playNewRound();
						insertMovmentVectorToLastStatus(movmentVector, dicAndBrokFlakVector);
						addLastStatusToFile();
						for (int i = 0; i < stringForWritingLastStatusTofile.size(); i++)
						{
							cout << stringForWritingLastStatusTofile[i] << endl;
						}

					}

					cout << "\nDo you want to continue play press 1 to continue or 0 to save game and exit\n";
					cin >> strRound;
					opRound = enter_just_int(strRound);

				} while (opRound != 0);// 0 to exit

			}
		}

	} while (op != 0);// 0 to Exit.

}
// end main