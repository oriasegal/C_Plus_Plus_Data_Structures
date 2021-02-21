#pragma once
#include <iostream>
#include <string>
#include <list>
using namespace std;

class TrieNode
{
public:
	TrieNode *sons[26]; //an array with 26 spaces for 26 letters in the english alphabet
	bool endOfWord; //will be marked as T if this prefix is also a word it self
	bool isLeaf; //will be marked as T if this node is a leaf
	TrieNode(); //constructor
	
	//TrieNode* creatNode(); //creats a new node in the tree
	//bool isLastNode(TrieNode* root); //checks if this node hase children or not- helps other functions
	//bool isEmpty(TrieNode* root); //checks if this node is empty- helps other functions
	bool del(string word);
	bool isEnd(TrieNode* root) { return root->endOfWord != false; } //checks if this letter, this node is a leaf

	//void insertRecursively(TrieNode* node, string wrd, int i);

	void addNewWord(string word); //adds a new word to the tree
	TrieNode* deleteWord(TrieNode* root, string word, int D = 0); //deletes a word fron the list in the tree, returns true if got deleted
	bool search(string word); //searcher for a word in the tree and returns T if it was found and F if it wasn't
	int printAutoSuggestions(const string prefix); //gets a string ad a prefix in the tree and prints out all the options for this prefix plus the number of options 
	void suggestions(TrieNode* root, string prefix); //used to help the printAotoSuggestions function 
	void print(TrieNode* root, string word);
};
