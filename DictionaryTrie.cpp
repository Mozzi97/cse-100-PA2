#include "util.h"
#include "DictionaryTrie.h"
#include <queue>
#include <vector>

//using namespace std;

Node::Node(){
//Node *MSTNode = new Node();
  endofword = false;
  freq = 0;
  currPart = "";
  for(int i = 0; i < ALPHABET; i++){
    alphabet[i] = NULL;
  }
}

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){
  root = NULL;


}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  if(word == ""){
    return false;

  }
  Node *curr = root;
  unsigned int index = -1;

    if(root == NULL){
      root = new Node();
      curr = root;
    }

  for(unsigned int i = 0; i<word.length();i++){
    index = word[i] - 'a';
    //check if index should be a space
    if(word[i] == ' '){
       index = ALPHABET-1;
    }
    else if (index >= ALPHABET) {//check if it is not a-z
       return false;
    }

    if(curr->alphabet[index] == NULL){

        next = new Node();
        next->currPart = word.substr(0,i+1);
        curr->alphabet[index] = next;
    }
    curr = curr->alphabet[index];

    
  }

  if(!curr->endofword){

    curr->endofword = true;
    curr->freq = freq;
    return true;
  }
  else{
    if(freq>curr->freq){
      curr->freq = freq;
    }
    return false;
  }
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  if(root == NULL) {
    return false;
  }
 

  Node *curr = root;
  unsigned int index = -1;

  for(unsigned int i = 0; i<word.length();i++){
    index = word[i] - 'a';
    //check if index should be a space
    if(word[i] == ' '){
       if(curr->alphabet[ALPHABET-1]){
         curr = curr->alphabet[ALPHABET-1];
         continue;
       }
       else{
         return false;
       }
    }
    else if (index >= ALPHABET) {//check if it is not a-z
       return false;
    }
    if(curr->alphabet[index] == NULL){
       return false;
     }

    curr = curr->alphabet[index];

    
  }

  if (curr->endofword){
    cout<<curr->currPart << endl;
    return true;

  }
  else{

    return false;
  }

  
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;
  std::vector<Node*> tempVector;
  if(prefix == ""){
    cout << "Invalid Input. Please retry with correct input" << endl;
    return words;
  }


  if(root == NULL) {
    return words;
  }
 

  Node *curr = root;
  unsigned int index = -1;

  for(unsigned int i = 0; i<prefix.length();i++){
    index = prefix[i] - 'a';
    //check if index should be a space
    if(prefix[i] == ' '){
       if(curr->alphabet[ALPHABET-1]){
         curr = curr->alphabet[ALPHABET-1];
         continue;
       }
       else{
         return words;
       }
    }
    else if (index >= ALPHABET) {//check if it is not a-z
       return words;
    }
    if(curr->alphabet[index] == NULL){
       return words;
     }

    curr = curr->alphabet[index];

   }

  std::queue<Node*> nodeQueue;
  //Check if curr node
  
  Node *temp = curr;
  nodeQueue.push(temp);
  while(!nodeQueue.empty()){
    if(temp->endofword == true) {
      tempVector.push_back(temp);
    }
    temp = nodeQueue.front();
    nodeQueue.pop();
    for(unsigned int i = 0; i<ALPHABET;i++){
      if(temp->alphabet[i] != NULL) {
        nodeQueue.push(temp->alphabet[i]);
      }
    }
    temp = nodeQueue.front();
    //Now check for endofword and pop queue
  }

  index = -1;
  unsigned int maxFreq = tempVector.at(0)->freq;


  while(!tempVector.empty() && words.size() < num_completions){
    for(unsigned int i = 0; i < tempVector.size(); i++){
      if(tempVector.at(i)->freq >= maxFreq){
         maxFreq = tempVector.at(i)->freq;
         temp = tempVector.at(i);
         index = i;
      }
    }
    words.push_back(temp->currPart); 
    tempVector.erase(tempVector.begin() + index);
    maxFreq = 0;
  }


  return words;
}

/*
 * Return the most similar word of equal length to the query, based
 * on their Hamming distance. 
 * In case of ties, return the word with the highest frequency (you may
 * assume there will always be one should a tie happen.)
 * In case there isn't any word of equal length to the query in the
 * trie, return an empty string.
 */
std::string DictionaryTrie::checkSpelling(std::string query)
{
 
  std::vector<std::string> words;
  std::vector<Node*> tempVector;
  if(query == ""){
    return "";
  }

  if(root == NULL) {
    return "";
  }

  //find every node in tree
  std::queue<Node*> nodeQueue;
  
  Node *temp = root;
  nodeQueue.push(temp);
  while(!nodeQueue.empty()){
    if(temp->currPart.length() == query.length() && temp->endofword) {
      tempVector.push_back(temp);
    }
    temp = nodeQueue.front();
    nodeQueue.pop();
    for(unsigned int i = 0; i<ALPHABET;i++){
      if(temp->alphabet[i] != NULL) {
        nodeQueue.push(temp->alphabet[i]);
      }
    }
    temp = nodeQueue.front();
    //Now check for endofword and pop queue
  }


/*
  for(unsigned i = 0; i < tempVector.size(); i++){
    cout << tempVector.at(i)->currPart << endl;
  }
*/

  // if there is no string with the same length
  if(tempVector.empty()){
    return "";
  }
  //initialize variables
  int minHD = 0;
  Node * minNode;
  //recording the initial hamming distance to the first node in the tempVector
  for(unsigned int i = 0; i < query.length(); i++) {
    if(query.at(i) != tempVector.at(0)->currPart.at(i)) {
      minHD++;
    }
  }
  minNode = tempVector.at(0);//initialize minNode

  //Now we'll find the proper node that contained the string we want to return
  for(unsigned int v = 1; v < tempVector.size() ; v++) {
    int HD = 0; //initialize HD every time in the loop
    for(unsigned int i = 0; i < query.length(); i++) {
      if(query.at(i) != tempVector.at(v)->currPart.at(i)) {
        HD++;
      }
    }
    if(minHD > HD) {
      //set hamming distance to HD variable, update minNode
      minHD = HD;
      minNode = tempVector.at(v);
    }
    else if (minHD == HD) {
      //compare the minNode and tempVector.at(v)'s frequency
      if(minNode->freq < tempVector.at(v)->freq)
        minNode = tempVector.at(v); //update minNode
    }
    if (minHD == 0) {
      break;
    }
  }

  return minNode->currPart;
}










/* Destructor */
DictionaryTrie::~DictionaryTrie(){
  DictionaryTrie::deleteAll(root);
}

void DictionaryTrie::deleteAll(Node* root){

  if (root == NULL) return;

  for(int i = 0; i< ALPHABET ; i++){
    if(root->alphabet[i] != NULL){
      deleteAll(root->alphabet[i]);
    }
  }

      delete root;

}
