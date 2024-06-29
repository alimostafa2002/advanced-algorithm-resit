#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;

class SpellChecker {
private:
    set<string> lexicon;

public:
    void addToLexicon(const string& word) {
        lexicon.insert(word);
    }

     vector<sstring> check(const string& word) {
        if (lexicon.find(word) != lexicon.end()) {
            return {word};
        }

        vector<string> suggestions;
        for (const string& correctWord : lexicon) {
            if (isPossibleTypo(word, correctWord)) {
                suggestions.push_back(correctWord);
            }
        }

        return suggestions;
    }

private:
    bool isPossibleTypo(const string& word, const string& correctWord) {
        if (word.size() == correctWord.size()) {
            return isSwapped(word, correctWord) || isInserted(word, correctWord) || isDeleted(word, correctWord) || isReplaced(word, correctWord);
        }
        else if (word.size() == correctWord.size() - 1) {
            return isInserted(word, correctWord);
        }
        else if (word.size() == correctWord.size() + 1) {
            return isDeleted(word, correctWord);
        }
        return false;
    }

    bool isSwapped(const string& word, const string& correctWord) {
        for (size_t i = 0; i < word.size() - 1; ++i) {
            if (word[i] == correctWord[i + 1] && word[i + 1] == correctWord[i]) {
                return true;
            }
        }
        return false;
    }

    bool isInserted(const string& word, const string& correctWord) {
        for (size_t i = 0; i < correctWord.size(); ++i) {
            if (word == correctWord.substr(0, i) + correctWord.substr(i + 1)) {
                return true;
            }
        }
        return false;
    }

    bool isDeleted(const string& word, const string& correctWord) {
        return isInserted(correctWord, word);
    }

    bool isReplaced(const string& word, const string& correctWord) {
        int mismatches = 0;
        for (size_t i = 0; i < word.size(); ++i) {
            if (word[i] != correctWord[i]) {
                ++mismatches;
            }
        }
        return mismatches == 1;
    }
};

int main() {
    SpellChecker spellChecker;
    spellChecker.addToLexicon("hello");
    spellChecker.addToLexicon("world");
    spellChecker.addToLexicon("goodbye");

    vector<std::string> suggestions = spellChecker.check("wolrd");
    for (const std::string& suggestion : suggestions) {
        cout << "Did you mean: " << suggestion << endl;
    }

    return 0;
}
