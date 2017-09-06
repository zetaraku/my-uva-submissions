#include <iostream>
#include <map>
#include <set>
#define undefined (-1)
using namespace std;

int uppest_linklevel[100];
int node_level[100];
set<int> neighbors[100];
set<int> cameraCity;

void DFS(int parent, int node, int level);

int main(){
	int k=0;
	while(true){
		int numberOfCities; cin >> numberOfCities;
		if(!numberOfCities)break;
		if(k)cout << endl;

		map<string,int> cityToNum;
		string cityNames[numberOfCities];

		fill(uppest_linklevel,uppest_linklevel+numberOfCities,undefined);
		fill(node_level,node_level+numberOfCities,undefined);
		for(int i=0;i<numberOfCities;i++)neighbors[i].clear();
		cameraCity.clear();

		for(int i=0;i<numberOfCities;i++){
			string name; cin >> name;
			cityNames[i]=name;
			cityToNum[name]=i;
		}

		int numberOfRoutes; cin >> numberOfRoutes;
		string name1, name2;
		for(int i=0;i<numberOfRoutes;i++){
			cin >> name1 >> name2;
			int id1=cityToNum.at(name1), id2=cityToNum.at(name2);
			neighbors[id1].insert(id2);
			neighbors[id2].insert(id1);
		}

		for(int i=0;i<numberOfCities;i++)
			if(node_level[i] == undefined)
				DFS(undefined,i,0);

		cout << "City map #" << ++k << ": " << cameraCity.size() << " camera(s) found" << endl;
		for(int n: cameraCity)
			cout << cityNames[n] << endl;
	}

	return 0;
}

void DFS(int parent, int node, int level){
	uppest_linklevel[node] = node_level[node] = level;
	int disabledChilds=0;
	int childCount=0;		//for root
	for(int child: neighbors[node]){		//for all neighbors
		if(child == parent){
			continue;						//skip parent
		}else if(node_level[child] == undefined){		//a child
			childCount++;					//count children for root
			DFS(node,child,level+1);
			uppest_linklevel[node]=min(uppest_linklevel[node],uppest_linklevel[child]);
			if(uppest_linklevel[child]>=node_level[node])		//a disabled child
				disabledChilds++;
		}else{									//a up-link or down-link
			uppest_linklevel[node]=min(uppest_linklevel[node],node_level[child]);
		}
	}
	if(parent==undefined&&childCount<=1)disabledChilds=0;	//root
	if(disabledChilds>0)cameraCity.insert(node);
}
