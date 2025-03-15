#include "ladder.h"
#include <algorithm>

void error(string word1, string word2, string msg){
    cout << "Error: word1:" << word1 << " and " << "word2:" << word2 << " " << msg << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int len1 = str1.size();
    int len2 = str2.size();
    //Rule: either same length or differ by at most one character
    if (abs(len1 - len2) > 1) return false;

    //all char to lower case
    string lower1 = str1, lower2 = str2;
    transform(lower1.begin(), lower1.end(), lower1.begin(), ::tolower);
    transform(lower2.begin(), lower2.end(), lower2.begin(), ::tolower);

    //same length
    if (len1 == len2) {
        int count = 0;
        for (int i = 0; i < len1; ++i) {
            if (lower1[i] != lower2[i]) {
                if (++count > d) return false;  // More than `d` edits, return early
            }
        }
        return count <= d;
    }

    //length off by 1
    if (len1 < len2) swap(lower1, lower2); //made lower always lower so I dont have to have double checks to reduce time
    int i = 0, j = 0, mismatch = 0;
    
    while (i < lower1.size() && j < lower2.size()) {
        if (lower1[i] != lower2[j]) {
            if (++mismatch > 1) return false;
            i++; //char longer str skip
        } else {
            i++; j++;
        }
    }

    return true; //one char skipped
}
bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (begin_word == end_word) return {};
    queue<vector<string>> lq;
    lq.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!lq.empty()) {
        vector<string> ladder = lq.front();
        lq.pop();
        string last_word = ladder.back();
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                visited.insert(word);
                vector<string> new_ladder = ladder; //copy constructor
                new_ladder.push_back(word);
                if (word == end_word){
                    // I think I may be reprocessing which causes an inf loop
                    // while (!lq.empty()) lq.pop();
                    return new_ladder;
                }
                lq.push(new_ladder);
            }
        }
    }
    return {};
}
void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found.\n";
    } 
    else {
        cout << "Word ladder found: ";
        for (const string& word : ladder) {
            cout << word << " ";
        }
        cout << "\n";
    }
}
void verify_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "The ladder is empty!" << endl;
        return;
    }

    for (size_t i = 1; i < ladder.size(); i++) {
        if (!is_adjacent(ladder[i - 1], ladder[i])) {
            cout << "Error: The words '" << ladder[i - 1] << "' and '" << ladder[i] << "' are not adjacent!" << endl;
            return;
        }
    }

    cout << "The word ladder is valid." << endl;
}