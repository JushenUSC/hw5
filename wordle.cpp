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


// Add prototypes of helper functions here
bool isValidWordle(const std::string& in, std::string& current, const std::string& floating, const std::set<std::string>& dict);
std::set<std::string> wordleHelper(const std::string& in, std::string& current, const std::string& floating, const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
	std::string current = "";
	return wordleHelper(in, current, floating, dict);

}

// Define any helper functions here

std::set<std::string> wordleHelper(const std::string& in, std::string& current, const std::string& floating, const std::set<std::string>& dict) {
	
	if (isValidWordle(in, current, floating, dict)) {
		std::set<std::string> validWord;
		validWord.insert(current);
		return validWord;
	}
	else {
		std::set<std::string> validWord;
		std::set<std::string> allValidWords;
		int pos = current.length();
		if (in[pos] != '-') {
			std::string newIn = in;
			newIn[pos] = '-';
			std::string newCurrent = current + in[pos];
			return wordleHelper(newIn, newCurrent, floating, dict);
		}
		else {
			// Open position ('-')
			std::set<std::string> allValidWords;
			for (int i = 0; i < 26; i++) {
				std::set<std::string> validWord = wordleHelper(in, current + alphabet[i], floating, dict);
				// Merge validWord into allValidWords
			}
			return allValidWords;
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
		if (/*current (not currentCopy) is a word in dict*/) {
			return true;
		}
	}
	return false;
};