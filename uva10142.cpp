#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <climits>

using namespace std;

struct Node {
    int data;
    Node *prev, *next;
};

void doCase();
void cleanup(vector<Node*>&);

int main(){
    int numberOfCase;
    cin >> numberOfCase;

    for(int i=0;i<numberOfCase;i++){
        doCase();
        if(i!=numberOfCase-1)
            cout << endl;
    }

	return 0;
}

void doCase(){
    string line;

    int numberOfCandidate;
    cin >> numberOfCandidate; getline(cin,line);

    string candidateNames[numberOfCandidate];
    for(int i=0;i<numberOfCandidate;i++)
        getline(cin,candidateNames[i]);

    vector<Node*> candidatePositionNodes[numberOfCandidate];
    vector<Node*> ballotHeads;

    while(getline(cin,line)){
        if(line.empty())break;

        istringstream ss(line);
        Node *listhead=new Node();
        Node *listtail=listhead;

        int no;
        while(ss >> no){
            Node* tmpn=new Node();
            tmpn->data=no-1;
            tmpn->next=NULL;
            tmpn->prev=listtail;
            listtail->next=tmpn;
            listtail=listtail->next;
            candidatePositionNodes[no-1].push_back(tmpn);
        }
        ballotHeads.push_back(listhead);
    }

    map<int,int> votecounts;
    for(int i=0;i<numberOfCandidate;i++)
        votecounts.insert(make_pair(i,0));

    while(true){
        for(Node* head: ballotHeads)
            votecounts.at(head->next->data)++;

        int min_votenum=INT_MAX;
        vector<int> min_ids;

        for(map<int,int>::const_iterator it=votecounts.begin();it!=votecounts.end();it++){
            if(it->second>ballotHeads.size()/2){
                cout << candidateNames[it->first] << endl;
                cleanup(ballotHeads);
                return;
            }
            if(it->second<min_votenum){
                min_ids.clear();
                min_votenum=it->second;
                min_ids.push_back(it->first);
            }else if(it->second==min_votenum){
                min_ids.push_back(it->first);
            }
        }

        if(min_ids.size()*min_votenum==ballotHeads.size()){
            for(int id: min_ids)
                cout << candidateNames[id] << endl;
            cleanup(ballotHeads);
            return;
        }

        for(int id: min_ids){
            for(Node* node: candidatePositionNodes[id]){
                node->prev->next=node->next;
                if(node->next!=NULL)node->next->prev=node->prev;
                delete node;
            }
            votecounts.erase(id);
        }

        for(map<int,int>::iterator it=votecounts.begin();it!=votecounts.end();it++)
            it->second=0;
    }
}

void cleanup(vector<Node*>& ballotHeads){
    for(Node* head: ballotHeads)
        while(head!=NULL){
            Node* next=head->next;
            delete head;
            head=next;
        }
}
