#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";


// Add prototypes of helper functions here
void wordleHelper(const std::string& in, std::string& current, const std::string& floating, const std::set<std::string>& dict, std::set<std::string>& allValidWords);
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

void wordleHelper(const std::string& in, std::string& current, const std::string& floating, const std::set<std::string>& dict, std::set<std::string>& allValidWords) {
	if (isValidWordle(in, current, floating, dict)) {
		allValidWords.insert(current);
	}
	else {
		if (current == "") {
			return;
		}
		int pos = current.length();
		if (in[pos] != '-') {
			std::string newIn = in;
			newIn[pos] = '-';
			std::string newCurrent = current + in[pos];
			wordleHelper(newIn, newCurrent, floating, dict, allValidWords);
		}
		else {
			for (int i = 0; i < 26; i++) {
				current = current + alphabet[i];
				wordleHelper(in, current, floating, dict, allValidWords);
			}
		}
	}
}

bool isValidWordle(const std::string& in, std::string& current, const std::string& floating, const std::set<std::string>& dict) {
	std::string currentCopy = current;
	if (in.length() == currentCopy.length()) {
		for (int i = 0; i < floating.length(); i++) {
			if (currentCopy.find(floating[i]) != string::npos) {
				int index = currentCopy.find(floating[i]);
				currentCopy[index] = '-';
			}
			else {
				return false;
			}
		}
		std::set<std::string>::iterator it = dict.find(current);
		if (it != dict.end()) {
			return true;
		}
	}
	return false;
};