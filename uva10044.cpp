#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Author;

struct Paper {
    set<Author*> authors;
};

struct Author{
    int erdos_no;
    set<Paper*> papers;
};

void doCase(int);

int main(){
    int numberOfScenarios;
    cin >> numberOfScenarios;

    for(int i=0;i<numberOfScenarios;i++)
        doCase(i+1);

	return 0;
}

void doCase(int case_no){
    string line;

    int num_paper, num_req_author;
    cin >> num_paper >> num_req_author; getline(cin,line);

    Paper* papers[num_paper];
    vector<Author*> authors;

    vector<string> namelist;
    map<string,int> name2id_table;

    for(int paper_no=0;paper_no<num_paper;paper_no++){
        Paper* paper=new Paper();

        getline(cin,line);
        char cstr[line.size()+1];
        strcpy(cstr,line.c_str());
        char* pstr = strtok(cstr,":");

        string name;
        bool part_2=false;
        char* token=strtok(pstr,", ");
        while (token!=NULL){
            (name+=(part_2?", ":""))+=token;
            if(part_2){
                if(name2id_table.find(name)==name2id_table.end()){
                    Author* new_author=new Author();
                    new_author->erdos_no=-1;
                    new_author->papers.insert(paper);

                    paper->authors.insert(new_author);
                    name2id_table.insert(make_pair(name,authors.size()));
                    namelist.push_back(name);

                    authors.push_back(new_author);
                }else{
                    paper->authors.insert(authors[name2id_table.at(name)]);
                    authors.at(name2id_table.at(name))->papers.insert(paper);
                }
                name.clear();
            }
            part_2=!part_2;
            token=strtok(NULL,", ");
        }
        papers[paper_no]=paper;
    }

    int now_level=0;
    vector<Author*> thislevel, nextlevel;

    Author* ERDOS=authors[name2id_table.at("Erdos, P.")];
    ERDOS->erdos_no=0;
    nextlevel.push_back(ERDOS);

    while(nextlevel.size()>0){
        thislevel=nextlevel;
        nextlevel.clear();
        for(Author* rootauthor: thislevel){
            for(Paper* paper: rootauthor->papers){
                for(Author* subauthor: paper->authors){
                    if(subauthor->erdos_no!=-1)continue;
                    subauthor->erdos_no=now_level+1;
                    nextlevel.push_back(subauthor);
                }
            }
        }
        now_level++;
    }

    cout << "Scenario " << abs(case_no) << endl;
    for(int i=0;i<num_req_author;i++){
        int erdos_no=-1;
        getline(cin,line);
        map<string,int>::const_iterator ptrfind;
        if((ptrfind=name2id_table.find(line))!=name2id_table.end())
            erdos_no=(authors.at(ptrfind->second))->erdos_no;
        cout << line << " ";
        if(erdos_no!=-1){cout << erdos_no;}else{cout << "infinity";}
        cout << endl;
    }

    for(Paper* paper: papers)
        delete paper;
    for(Author* author: authors)
        delete author;
}
