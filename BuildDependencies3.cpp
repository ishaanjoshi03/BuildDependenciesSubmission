#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
using namespace std;

vector<list<string>> graph;
list<string> list_print;
queue<string> queue1;
map<string, set<string>> graph_map;
map<string, set<string>> graph_bfs;
map<string, set<string>> reverse_graph;
map<string, bool> check_map;
set<string> set_to_insert;
set<string> current_set;

int main() {
    std::ios::sync_with_stdio(false);
    // TAKING IN INPUT                                    <<<<<<<<<<<<-------------------------------
    string temp;
    int x = 0;
    cin >> x;
    string l1[x+1];
    for (int i = 0; i < x+1; i++) {
        getline(cin, l1[i]);
    }
    string s1;
    cin >> s1;


    // PUTTING INPUT INTO GRAPH                           <<<<<<<<<<<<-------------------------------
    string s2;
    int space = 0;
    string key;
    string value;
    // Adding Keys to Map
    for (int i = 0; i < x+1; i++) {
        s2 = l1[i];
        space = 0;
        for (int j = 0; j < s2.length(); j++) {
            if (s2[j] == ':') {
                key = l1[i].substr(0,j);
                set_to_insert.clear();
                pair <string, set<string>> pair_to_insert(key,set_to_insert);
                graph_map.insert(pair_to_insert);

                pair<string,bool> pair_to_add (key, false);
                check_map.insert(pair_to_add);
                if (s2.length()-1 > j) {space = j+1;}
                else {
                    break;
                }
            }
        }
    }

    for (int i = 0; i < x+1; i++) {
        s2 = l1[i];
        space = 0;
        for (int j = 0; j < s2.length(); j++) {
            if (s2[j] == ':') {
                value = l1[i].substr(0,j);
                if (s2.length()-1 > j) {space = j+1;}
                else {
                    break;
                }
            }
            if (s2[j] == ' ' && j != space) {
                key = l1[i].substr(space+1,j-space-1);
                graph_map.at(key).insert(value);
                if (s2.length()-1 > j) space = j;
                else {
                    break;
                }
            }
            if (j == s2.length()-1) {
                key = l1[i].substr(space+1);
                graph_map.at(key).insert(value);
            }
        }
    }


    // MAKING COPY OF GRAPH WITH ONLY DEPENDENT NODES (BFS)             <<<<<<<<<<<<<<<-----------------------------
    temp = s1;
    queue1.push(temp);
    while (!queue1.empty()) {
        temp = queue1.front();
        current_set = graph_map.at(temp);
        for (auto itr : current_set) {
            if (check_map.at(itr) == false) {
                queue1.push(itr);
                check_map.at(itr) = true;
            }
        }
        pair<string, set<string>> pair_to_add (temp,current_set);
     graph_bfs.insert(pair_to_add);
        queue1.pop();
    }

    // MAKING REVERSE GRAPH OF BFS GRAPH
    for (auto itr : graph_bfs) {
        current_set = itr.second;
        key = itr.first;
        set<string> set_to_add;
        for (auto itr2 : current_set) {
            set_to_add.clear();
            if (reverse_graph.find(itr2) == reverse_graph.end()) {
                pair<string, set<string>> pair_to_insert (itr2, set_to_add);
                reverse_graph.insert(pair_to_insert);
            }
            reverse_graph.at(itr2).insert(key);
        }
    }

    for (auto itr : check_map){
        check_map.at(itr.first) = false;
    }

    // RUNNING BFS FROM NODE IN GRAPH AS SET                    <<<<<<<<<<<<-------------------------------
    temp = s1;
    queue1.push(temp);
    while (!queue1.empty()) {
        temp = queue1.front();
        current_set = graph_bfs.at(temp);
        for (auto itr : current_set) {
            reverse_graph.at(itr).erase(temp);
            if (check_map.at(temp) == false && reverse_graph.at(itr).empty()) {
                queue1.push(itr);
            }
        }
        cout << temp << endl;
        queue1.pop();
    }

}
