#include "util.h"
#include "DictionaryHashtable.h"

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
  auto temp = treeH.insert(word);
  return temp.second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
  if(treeH.find(word) == treeH.end()){
    return false;

  }
  else{
    return true;

  }
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){}
