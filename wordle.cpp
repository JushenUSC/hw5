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


void wordleHelper(const std::string& in, std::string current, std::string floating, const std::set<std::string>& dict, std::set<std::string>& allValidWords, int numBlank);

std::set<std::string> wordle(const std::string& in, const std::string& floating, const std::set<std::string>& dict) {
    std::string current = "";
    std::set<std::string> allValidWords;
    int numBlank = 0;
    for (size_t i = 0; i < in.length(); i++) {
        if (in[i] == '-') numBlank++;
    }
    wordleHelper(in, current, floating, dict, allValidWords, numBlank);
    return allValidWords;
}

void wordleHelper(const std::string& in, std::string current, std::string floating, const std::set<std::string>& dict, std::set<std::string>& allValidWords, int numBlank) {
    if (current.length() == in.length()) {
        if (floating.empty() && dict.find(current) != dict.end()) {
            allValidWords.insert(current);
        }
        return;
    }

    int pos = current.length();
    if (in[pos] != '-') {
        wordleHelper(in, current + in[pos], floating, dict, allValidWords, numBlank);
    } else {
        for (size_t i = 0; i < floating.length(); i++) {
            char c = floating[i];
            std::string newFloating = floating;
            newFloating.erase(i, 1);
            wordleHelper(in, current + c, newFloating, dict, allValidWords, numBlank - 1);
        }
        if (floating.length() < (numBlank)) {
            for (size_t i = 0; i < alphabet.length(); i++) {
                char c = alphabet[i];
                if (floating.find(c) == std::string::npos) {
                    wordleHelper(in, current + c, floating, dict, allValidWords, numBlank - 1);
                }
            }
        }
    }
}