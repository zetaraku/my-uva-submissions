#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <utility>
#define undefined (-1)
using namespace std;

int main(){
	int numberOfCases;
	cin >> numberOfCases;
	for(int k=0;k<numberOfCases;k++){
		int numberOfCities; cin >> numberOfCities;
		map<string,int> citiesToNums;
		string city;
		for(int i=0;i<numberOfCities;i++){
			cin >> city;
			citiesToNums[city]=i;
		}
		int numberOfTrains; cin >> numberOfTrains;

		int A=numberOfTrains*numberOfCities;
		int timetable[numberOfTrains][numberOfCities];			//stop times
		int lastStopCity[numberOfTrains][numberOfCities];		//linker
		bool achieved[numberOfTrains][numberOfCities];						//DP
		fill(*timetable,*timetable+A,undefined);
		fill(*lastStopCity,*lastStopCity+A,undefined);
		fill(*achieved,*achieved+A,false);
		vector<int> stopTrainsOfCity[numberOfCities];

		for(int trainnum=0;trainnum<numberOfTrains;trainnum++){
			int numberOfStops;
			cin >> numberOfStops;
			int lastcitynum=undefined;
			for(int j=0;j<numberOfStops;j++){
				int timestr; string cityname;
				cin >> timestr >> cityname;
				int citynum=citiesToNums.at(cityname);

				timetable[trainnum][citynum]=timestr;						//record the time table
				stopTrainsOfCity[citynum].push_back(trainnum);				//add the train to the list of the city
				if(lastcitynum!=undefined)
					lastStopCity[trainnum][citynum]=lastcitynum;			//record the back stop
				lastcitynum=citynum;
			}
		}

		int starttime; string startpoint, endpoint;
		cin >> starttime >> startpoint >> endpoint;
		int startno=citiesToNums.at(startpoint), endno=citiesToNums.at(endpoint);

		map< int,vector<int> > terminalTrainsOfTimes;
		for(int i=0;i<numberOfTrains;i++)
			if(timetable[i][endno]!=undefined)
				terminalTrainsOfTimes[timetable[i][endno]].push_back(i);

		stack< pair<int,int> > toProcess;
		set<int> beginTimes;

		int terminalTime=undefined;
		for(pair< int,vector<int> > p: terminalTrainsOfTimes){				//process from earlier to latter arrive time
			terminalTime=p.first;
			for(int t: p.second)
				toProcess.push(make_pair(t,endno));							//take every trains of this arrive time into process
			while(!toProcess.empty()){
				pair<int,int> p=toProcess.top(); toProcess.pop();
				int t=p.first, c=p.second;									//train,city
				achieved[t][c]=true;
				if(c==startno){												//beginning reached
					if(timetable[t][c]>=starttime)							//if the time is after the departing time
						beginTimes.insert(timetable[t][c]);
				}else{
					if(lastStopCity[t][c]!=undefined && !achieved[t][lastStopCity[t][c]])
						toProcess.push(make_pair(t,lastStopCity[t][c]));	//add the last stop
					for(int tt: stopTrainsOfCity[c])
						if(!achieved[tt][c] && timetable[tt][c]<=timetable[t][c])
							toProcess.push(make_pair(tt,c));				//add every transferable stop
				}
			}
			if(!beginTimes.empty())											//if any beginning reached
				break;
		}

		printf("Scenario %d\n",k+1);
		if(!beginTimes.empty()){
			printf("Departure %04d %s\n", *beginTimes.rbegin(), startpoint.c_str());
			printf("Arrival   %04d %s\n", terminalTime, endpoint.c_str());
		}else{
			printf("No connection\n");
		}
		putchar('\n');
	}

	return 0;
}
