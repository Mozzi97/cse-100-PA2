#include "util.h"
#include "DictionaryBST.h"

#include <set>

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
  auto pair = tree.insert(word);
  
  return pair.second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
  if(tree.find(word) == tree.end()){
    return false;
  }
  else{
    return true;
  }
}

/* Destructor */
DictionaryBST::~DictionaryBST(){}
