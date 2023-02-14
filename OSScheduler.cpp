#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;



//Authors: ALA' AYMAN MOHAMMAD RASHEED HADER,132911 + SEWAR MOHAMMAD TAYEL GARIBEH, 133460

int main()
{
	ifstream inFile("in.txt");
	string line;
	int N;
	vector<string>PName; //To store process Name
	vector <int> ArrTime, PTime, ArrTimeS, ArrTimeTEMP; //To store Arrive, processing times, Arrive time sorted,Arrive time sorted temporary ;

	if (inFile.is_open())
	{
		getline(inFile, line);
		N = stoi(line);

		int i = 0;
		while (getline(inFile, line))
		{
			string pname;
			int arrtime, ptime;
			stringstream sep(line);
			sep >> pname >> arrtime >> ptime;
			PName.push_back(pname);
			ArrTime.push_back(arrtime);
			PTime.push_back(ptime);
			ArrTimeS.push_back(ArrTime[i]);
			i++;
		}



		inFile.close();//close in.txt file



		ArrTimeTEMP = ArrTime;
		sort(ArrTimeS.begin(), ArrTimeS.end());



		ofstream store;
		store.open("out.txt");
		for (int i = 0; i < N; i++) // to print PName in order
		{
			for (int j = 0; j < N; j++) {
				if (ArrTimeS[i] == ArrTimeTEMP[j]) {
					store << PName[j];
					ArrTimeTEMP[j] = -1;
					break;
				}
			}
		}//END printing PName in order
		store << endl;

		ArrTimeTEMP = ArrTime;
		int Start_time, sumP = 0, EndTime;//start time,sum of old processing times and End Time

		for (int i = 0; i < N; i++) // loop for sorted array (ArrTimeS)
		{
			int j = 0;
			for (; j < N; j++) //loop to find index of the process in unsorted array (ArrTime)
			{
				if (ArrTimeS[i] == ArrTimeTEMP[j]) // found real index of the process.
				{
					ArrTimeTEMP[j] = -1;
					break;
				}
			}
			if (i == 0 || (ArrTime[j] - sumP > 0)) { //if it's the first process or there's a gap between processes
				Start_time = ArrTime[j];
			}
			else {
				Start_time = sumP;
			}
			sumP += PTime[j];
			store << PName[j] << ": (response=" << Start_time - ArrTime[j] << ", ";//Response Time
			EndTime = Start_time + PTime[j];
			store << "turnaround=" << EndTime - ArrTime[j] << ", ";//turnaround time
			store << "delay=" << EndTime - ArrTime[j] - PTime[j] << ")" << endl;//Delay Time
		}

		store.close();//close out.txt file




	} //END IF(inFile.is_open())




}//END main()
