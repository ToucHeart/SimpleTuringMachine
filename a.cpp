#include <iostream>
#include <string>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <map>
using namespace std;
int main()
{
    unordered_set<string> s;
    string a(1, 'a');
    multimap<string, int> m = {
        {"ads", 1},
        {"ads", 2},
        {"ads", 3},
        {"ads", 4},
    };
    auto beg = m.lower_bound("ads"), end = m.upper_bound("ads");
    int d = 5;
    m.insert(pair<string, int>{"ads", d});
    for (; beg != end; ++beg)
    {
        cout << beg->first << ' ' << beg->second << endl;
    }
    unordered_set<string> keys;
    auto it = keys.find("A");
    if (it == keys.end())
        cout << "failed";
    deque<string> e;
    e.push_front("ads");
    e.pop_front
}