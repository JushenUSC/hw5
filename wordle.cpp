#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <vector>
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";


// Add prototypes of helper functions here
void wordleHelper(const std::string& in, std::string current, const std::string& floating, const std::set<std::string>& dict, std::set<std::string>& allValidWords);
bool isValidWordle(const std::string& in, std::string& current, const std::string& floating, const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(const std::string& in, const std::string& floating, const std::set<std::string>& dict) {
    // Add your code here
	std::string current = "";
	std::set<std::string> allValidWords;
	wordleHelper(in, current, floating, dict, allValidWords);
	return allValidWords;
}

// Define any helper functions here

void wordleHelper(const std::string& in, std::string current, const std::string& floating, const std::set<std::string>& dict, std::set<std::string>& allValidWords) {
	if (current.length() == in.length()) {
		if (current == "") {
			return;
		}
        if (isValidWordle(in, current, floating, dict)) {
            allValidWords.insert(current);
        }
        return;
    }
	int pos = current.length();
	if (in[pos] != '-') {
		wordleHelper(in, current + in[pos], floating, dict, allValidWords);
	}
	else {
		for (int i = 0; i < 26; i++) {
			wordleHelper(in, current + alphabet[i], floating, dict, allValidWords);
		}
	}
}

bool isValidWordle(const std::string& in, std::string& current, const std::string& floating, const std::set<std::string>& dict) {
	if (in.length() != current.length()) {
        return false;
    }

    std::vector<int> freq(26, 0);
    for (char c : current) {
		int val = c - 'a';
        freq[val]++; 
    }
	int floatLength = floating.length();
	for (int i = 0; i < floatLength; i++) {
		char currChar = floating[i];
		int currVal = currChar - 'a';
		if (freq[currVal] > 0) {
			freq[currVal]--;
		}
		else {
			return false;
		}
	}

    return dict.find(current) != dict.end();
};