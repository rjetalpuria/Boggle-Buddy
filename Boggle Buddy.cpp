#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;
//  B E A N     
//  O D O E     
//  O I Y S     
//  K A D A     
void fetchWords(char c, vector<string>* dict);
void checkWords(char c, int index, vector<string>* dict, vector<string>* words, const string letters);
bool canRemove(char c, string* l, int* index);
void removeDuplicates(vector<string>* l);
vector<string> merge(vector<string> left, vector<string> right);
vector<string> mergeSort(vector<string> m);
// 0  1  2  3
// 4  5  6  7 
// 8  9  10 11
// 12 13 14 15
vector<vector<int>> nextIndex = { {1,4,5}, {0,1,2,4,5,6}, {1,3,5,6,7}, {2,6,7},
  /* Shows what indexes a */    {0,1,5,8,9}, {0,1,2,4,6,8,9,10}, {1,2,3,5,7,9,10,11}, {2,3,6,10,11},
  /* current index can    */    {4,5,9,12,13}, {4,5,6,8,10,12,13,14}, {5,6,7,9,11,13,14,15}, {6,7,10,14,15},
  /* connect to.          */    {8,9,13}, {8,9,10,12,14}, {9,10,11,13,15}, {10,11,14} };

int main()
{
    string s;
    string letters;
    vector<string> dict;
    vector<string> words;

    cout << "Enter row 1: ";
    cin >> s;
    letters.append(s);
    cout << "Enter row 2: ";
    cin >> s;
    letters.append(s);
    cout << "Enter row 3: ";
    cin >> s;
    letters.append(s);
    cout << "Enter row 4: ";
    cin >> s;
    letters.append(s);
    
    for (unsigned int i = 0; i < letters.length(); ++i) {
        if (letters[i] >= 'A' and letters[i] <= 'Z') {
            letters[i] = letters[i] + ('a' - 'A');
        }
        else if (letters[i] >= 'a' and letters[i] <= 'z') {
            //Do Nothing: The character is perfect
        }
        else {
            cout << "One of the letters you entered is INVALID." << endl
                << "Try Again!" << endl << endl;
            //invalid = true;
            break;
        }
    }

    
    cout << endl << "Your Boggle Box:" << endl;
    cout << " |A  B  C  D" << endl;
    cout << "-+-----------" << endl;
    int k = 0;
    for (int i = 0; i < 4; ++i) {
        cout << i+1 << "|" ;
        for (int j = 0; j < 4; ++j) {
            if (letters[k] == 'q') {
                cout << letters[k];
                cout << letters[++k] << " ";
                letters.erase(letters.begin() + k);
                
            }
            else {
                cout << letters[k++] << "  ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < letters.length(); ++i) {
        char c = letters[i];
        dict.clear();
        fetchWords(c, &dict);
        checkWords(c, i, &dict, &words, letters);
    }
    removeDuplicates(&words);
    words = mergeSort(words);
    //words = vs;
    for (unsigned int i = 0; i < words.size(); ++i) {
        cout << setw(2) << i + 1 << ". " << setw(8) << words[i] << " " << endl;
    }

}

void fetchWords(char c, vector<string>* dict) {
    ifstream inFile;
    string fileName;
    fileName.push_back(c);
    fileName.append(".txt");
    inFile.open(fileName);
    string temp;
    while (inFile >> temp) {
        dict->push_back(temp);
    }
    inFile.close();
}

void checkWords(char c, int index, vector<string>* dict, vector<string>* words, const string letters) {
    //Try each word in dict and add to words it they work out
    for (unsigned int i = 0; i < dict->size(); ++i) {
        string w = dict->at(i);
        string l = letters;
        bool isWord = true;
        int ind = index;
        bool isQ = false;
        if (l[ind] == 'q') {
            isQ = true;
        }
        l[ind] = -1; //sets the first char index as "used"
        if (w.compare("queen") == 0) {
            cout << w << endl;
        }
        for (int j = 1; j < w.length(); ++j) {
            char ch = w[j];
            if (ch == 'q') {
                isQ = true;
            }
            if (isQ && ch == 'u') {
                isQ = false;
                continue;
            }
            if (!canRemove(ch, &l, &ind)) {
                isWord = false;
                break;
            }
        }
        if (isWord) {
            words->push_back(w);
        }
    }
}

bool canRemove(char c, string* l, int* index) {
    //change l[index] = -1; and index to the next index

    for (unsigned int i = 0; i < nextIndex[*index].size(); ++i) {
        int next = nextIndex[*index][i];
        if (l->at(next) == c) {
            l->at(next) = -1;
            *index = next;
            return true;
        }
    }
    //Can't find the letter
    return false;
}

void removeDuplicates(vector<string>* l) {
    for (unsigned int i = 0; i < l->size(); ++i) {
        for (unsigned int j = i + 1; j < l->size(); ++j) {
            if (l->at(j) == l->at(i)) {
                l->erase(l->begin() + j);
            }
        }
    }
}

vector<string> merge(vector<string> left, vector<string> right)
{
    vector<string> result;
    while (left.size() > 0 || right.size() > 0) {
        if (left.size() > 0 && right.size() > 0) {
            if (left.front().length() >= right.front().length()) {
                result.push_back(left.front());
                left.erase(left.begin());
            }
            else {
                result.push_back(right.front());
                right.erase(right.begin());
            }
        }
        else if (left.size() > 0) {
            for (int i = 0; i < left.size(); i++)
                result.push_back(left[i]);
            break;
        }
        else if (right.size() > 0) {
            for (int i = 0; i < right.size(); i++)
                result.push_back(right[i]);
            break;
        }
    }
    return result;
}

vector<string> mergeSort(vector<string> m)
{
    if (m.size() <= 1)
        return m;

    vector<string> left, right, result;
    int middle = (m.size() + 1) / 2;

    for (int i = 0; i < middle; i++) {
        left.push_back(m[i]);
    }

    for (int i = middle; i < m.size(); i++) {
        right.push_back(m[i]);
    }

    left = mergeSort(left);
    right = mergeSort(right);
    result = merge(left, right);

    return result;
}