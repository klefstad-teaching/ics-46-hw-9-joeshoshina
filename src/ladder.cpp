#include "ladder.h"
#include <algorithm>

void error(string word1, string word2, string msg){
    cout << "Error: word1:" << word1 << " and " << "word2:" << word2 << " " << msg << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int len1 = str1.size();
    int len2 = str2.size();

    //converted the str to lower because my initial code would fail for case 2 otherwise
    string lower1 = str1;
    string lower2 = str2;
    transform(lower1.begin(), lower1.end(), lower1.begin(), ::tolower);
    transform(lower2.begin(), lower2.end(), lower2.begin(), ::tolower);

    //Rule: either same length or differ by at most one character
    if (abs(len1 - len2) > 1) return false;

    //same length
    if (len1 == len2) {
        int count = 0;
        for (int i = 0; i < len1; ++i) {
            if (lower1[i] != lower2[i]) ++count;
            if (count > d) return false;
        }
        return count <= d;
    }
    //length off by 1
    if (len1 + 1 == len2) {
        for (int i = 0; i < len2; ++i) { // Loop must go up to len2 to check last char
            string comp = lower2.substr(0, i) + lower2.substr(i + 1);
            if (comp == lower1) return true;
        }
    } 
    else if (len1 == len2 + 1) {
        for (int i = 0; i < len1; ++i) { // Loop must go up to len1 to check last char
            string comp = lower1.substr(0, i) + lower1.substr(i + 1);
            if (comp == lower2) return true;
        }
    }
    return false;
}
bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if(begin_word == end_word){ 
        vector<string> ret;
        ret.push_back(begin_word);
        return ret;
    }

    queue<vector<string>> ladders;
    set<string> visited;
    ladders.push({begin_word});
    visited.insert(begin_word);

    while (!ladders.empty()) {
        int level_size = ladders.size();

        for (int i = 0; i < level_size; ++i) {
            vector<string> current_ladder = ladders.front();
            ladders.pop();
            string last_word = current_ladder.back();

            for (const string& word : word_list) {
                if (is_adjacent(last_word, word) && (visited.find(word) == visited.end())) {
                    if (word == end_word) {
                        current_ladder.push_back(word);
                        return current_ladder;
                    }

                    visited.insert(word);
                    vector<string> new_ladder = current_ladder;
                    new_ladder.push_back(word);
                    ladders.push(new_ladder);
                }
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