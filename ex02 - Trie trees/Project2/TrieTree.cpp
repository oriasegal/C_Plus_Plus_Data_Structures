#include <iostream>
#include <string>
#include <list>
#include "TrieTree.h"
using namespace std;


TrieNode::TrieNode()
{
	this->endOfWord = false; //makes the endOfWord flag false as deafault
	for (int i = 0; i < 26; i++) //runs through the letters and makes all the pointers in the array to point at null
		this->sons[i] = nullptr;
	isLeaf = true;
}

//TrieNode* TrieNode::creatNode()
//{
//	TrieNode *P = new TrieNode; //creats a new node to return
//	P->endOfWord = false; //marks the endOfWord flaf as false as deafault
//
//	for (int i = 0; i < 26; i++) //runs through the array of letters in the new node and makes it all piont at null
//		P->sons[i] = NULL;
//
//	return P; //returns the node
//}

//bool TrieNode::isLastNode(TrieNode* root)
//{
//	for (int i = 0; i < 26; i++) //runs through all the array of letters in the root to see if he has any children
//		if (root->sons[i])
//			return 0; //if found a child returns 0
//	return 1; //if has no children returns 1
//}

//bool TrieNode::isEmpty(TrieNode* root)
//{
//	for (int i = 0; i < 26; i++) //runs trough all the letters' array
//	{
//		if (root->sons[i]) //if this node has sons at i
//			return false; //returns false because it's no empty
//	}
//	return true; //returns true because it has no children at any letter
//}

bool TrieNode:: del(string word)
{
	if (!search(word))
		return false;
	else
	{
		TrieNode* P = deleteWord(this, word, 0);
		return true;
	}
}

void TrieNode::addNewWord(string word)
{
	int index = 0;
	TrieNode* p = this;
	p->isLeaf = false;

	for (int i = 0; i < word.length(); i++) //runs through the word ans checks all the letters
	{
		if (word[i] <= 'Z' && word[i] >= 'A') //checks for capital letters
			index = word[i] - 'A';
		else if (word[i] <= 'z' && word[i] >= 'a') //checks for lowercase letters
			index = word[i] - 'a';

		if (!p->sons[index]) //if we don't have this letter in the list- in the trie tree
			p->sons[index] = new TrieNode(); //adding a new node with this letter
		
		p->isLeaf = false; //makes it as end of word (we don't know yet if tere will be more letters after
		p = p->sons[index]; //pionts to the next son
	}

	p->endOfWord = true; //marks the last letter as an end of a word

	for (int i = 0; i < 26; i++) //runs through the alpha beth to see how's not an end of a word and 'unmarks' it
		if (p->sons[i])
			p->isLeaf = false;
}

TrieNode* TrieNode::deleteWord(TrieNode* R, string word, int D)
{
	if (!R) //if the tree is empty- has no words in it
		return NULL;
	if (D == word.length()) //if we found the last letter of the word (after finding recursivly all the rest)
	{
		if (R->endOfWord) //if this is an end of a word but not a leaf- it's still a prefix for other words in the tree
			R->endOfWord = false; //we mark this letter as no longer being an end of any word in the tree
		if (R->isLeaf) //using the isEmpty function to see if this is a leaf and we need to erase it
		{
			delete(R); //deletes this root
			R = nullptr; //makes it to point at null because we deleted it's son with the erase function
		}
		return R; //got deleted as asked
	}

	int index = word[D] - 'a'; //turns the letter into an integer 
	R->sons[index] = deleteWord(R->sons[index],word, D+1); //calls the deleting function againg recursivly with the child

	if (R->isLeaf && R->endOfWord == false)
	{
		delete(R);
		R = nullptr;
	}

	return R;
}

bool TrieNode::search(string word)
{
	TrieNode* P = this; //creats a new node that will be used in this function
	int index = 0;

	for (int i = 0; i < word.length(); i++) //runs through the word 
	{
		index = word[i] - 'a'; //turns the letters into integers and saves in index
		if (!P->sons[index]) //if this isn't what we were looking for then return false- the word was not found
			return false;

		P = P->sons[index]; //moves to the next letter
	}
	return (P && P->endOfWord); //returns true only if the pointer is not pointing at null and also this is a letter that's marked as an end of a word in the tree - that means that the word was found
}

int TrieNode::printAutoSuggestions(const string word)
{
	TrieNode* P = this;
	int index = 0;

	for (int i = 0; i < word.length(); i++)
	{
		index = word[i] - 'a';

		if (!P->sons[index]) //if there is no word that starts with this prefix in the tree
			return 0;

		P = P->sons[index]; //moves to the next child
	}

	print(P, word);
	return 1;
}
void TrieNode::print(TrieNode* node, string word)
{
	if (node->endOfWord)
		cout << word << endl;

	if (node->isLeaf)
		return;

	for (int i = 0; i < 26; i++)
		if (node->sons[i])
		{
			word.push_back('a' + i);
			print(node->sons[i], word);
			word = word.substr(0, word.length() - 1);
		}
}

void TrieNode::suggestions(TrieNode* root, string prefix)
{
	if (root->endOfWord) //if there is a word with this prefix
		cout << prefix << endl; //prints the prefix

	if (root->isLeaf) //if it has no children
		return;

	for (int i = 0; i < 26; i++) //runs through the array of letters of this root sent
	{
		if (root->sons[i]) //if the sons[i] isn't empty
		{
			prefix.push_back(97 + i); //adds the rest of the word to the prefix to be printed later
			suggestions(root->sons[i], prefix); //sends the next letter to be chacked in this function recursivly
		}
	}
}