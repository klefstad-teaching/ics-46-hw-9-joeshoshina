#include "ladder.h"

void error(string word1, string word2, string msg){
    cout << "word1:" << word1 << " is the same as " << "word2:" << word2 << "." << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int len1 = str1.size();
    int len2 = str2.size();
    //rule: either same or off by one
    if (abs(len1 - len2) > 1) return false;
    //same size, used tolower because it said to ignore letter case and saw word.txt had uppercases
    if (len1 == len2) {
        int count = 0;
        for (int i = 0; i < len1; ++i) {
            if (tolower(str1[i]) != tolower(str2[i])) ++count;
        }
        return count == 1;
    }
    //length off by 1 case (ex: car to cheat would be car → cat → chat → cheat, using insertion/deletion)
    if (len1 + 1 == len2) {
        //if delete forms word then adding would as well, I'll use substr to make str combo to compare if they equal
        // end param is how many char to include
        for (int i = 0; i < len2; ++i){
            string comp = str2.substr(0, i) + str2.substr(i + 1);
            if (comp == str1) return true;
        }
    }
    else if (len1 == len2 + 1) {
        for (int i = 0; i < len2; ++i){
            string comp = str1.substr(0, i) + str1.substr(i + 1);
            if (comp == str2) return true;
        }
    }
    return false;
}
bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    vector<string> stuff;
    return stuff;
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