#include "util.h"
#include "SuffixArray.h"

/**
 *  The class for a suffix array, represented as an int array
 *  storing the indices of the sorted suffixes.
 */
SuffixArray::SuffixArray(std::string word) : 
  word(word),
  suffixIdxs(new int[word.length()+1])
{
  buildSuffixArray(word);
}

/*
 * Helper method that constructs the suffix array derived from `word`
 * preferably using an efficient algorithm, such as the DC3 algorithm
 * (if you want the 5 points for efficiency, of course.)
 */
void SuffixArray::buildSuffixArray(std::string word){
  // TODO: Implement this method

  if(word == "") return;

  this->word = word;
  this->size = word.length();
//  this->temp[size];

  for(unsigned int i = 0; i < size; i++){
    temp[i] = word.substr(size - i - 1,i + 1);

  }

  string tempstr;
  for(int i = 0; i < size; i ++){
    for(int j = 0; j < size; j ++){
    	if(temp[i]<temp[j]){
    		tempstr = temp[i];
    		temp[i] = temp[j];
    		temp[j] = tempstr;
    	}
    }
  }

  for(int i = 0; i < size; i++)
        cout << temp[i] << " ";
    cout << endl;

//  suffixIdxs[size];
  for(int i = 0; i < size; i++){
    suffixIdxs[i] = size - temp[i].length();

  }

    for(int i = 0; i < size; i++)
        cout << suffixIdxs[i] << " ";
    cout << endl;

  return;
}

/* 
 * Return true if `pattern` exists in the word encoded by the suffix array,
 * false otherwise 
 */
bool SuffixArray::find(std::string pattern) const
{
  // TODO: Implement this method
  for(int i = 0; i < this->size; i++){
  	if(word.substr(i,pattern.length()) == pattern){
       return true;

  	}
  }
  return false;
}

/* Destructor */
SuffixArray::~SuffixArray(){
  delete [] this->suffixIdxs;
}
