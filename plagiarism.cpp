#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <string>
#include <algorithm>

using namespace std;

// Function to clean a word: remove punctuation and convert to lowercase
string cleanWord(string word) {
    word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    return word;
}

// Read file and store unique cleaned words in a set
unordered_set<string> getWordsFromFile(const string& filename) {
    unordered_set<string> words;
    ifstream file(filename);
    string line, word;

    while (getline(file, line)) {
        stringstream ss(line);
        while (ss >> word) {  // FIXED: 'ss > word' → 'ss >> word'
            word = cleanWord(word);
            if (!word.empty())
                words.insert(word);
        }
    }

    return words;
}

// Calculate Jaccard Similarity
double jaccardSimilarity(const unordered_set<string>& set1, const unordered_set<string>& set2) {
    int intersection = 0;
    for (const string& word : set1) {  // FIXED: 'set 1' → 'set1'
        if (set2.count(word)) {
            intersection++;
        }
    }

    int union_size = set1.size() + set2.size() - intersection;
    if (union_size == 0) return 0.0;  // Prevent division by zero
    return static_cast<double>(intersection) / union_size;
}

int main() {
    string file1 = "file.txt";
    string file2 = "file2.txt";
    ofstream out1(file1);
    out1<<"this is the content of c++.";
    out1.close();
    ofstream out2(file2);
    out2<<"the magic of c++";
    out2.close();
    auto words1 = getWordsFromFile(file1);
    auto words2 = getWordsFromFile(file2);

    double similarity = jaccardSimilarity(words1, words2) * 100;

    cout << "Plagiarism Similarity: " << similarity << "%\n";

    if (similarity > 50.0) {  // FIXED: 500 → 50.0 (percentage check)
        cout << "Potential plagiarism detected!" << endl;
    } else {
        cout << "No significant plagiarism detected." << endl;
    }

    return 0;
}
