#pragma once 
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
template <typename T>
class Vector{
private:
	T *arr;
	int siz;
public:
	Vector(){
		arr=NULL;
		siz=0;
	}
	void resize(int newSize){
		T *tempArr=new T [siz];
		for (int i=0;i<siz;i++){
			tempArr[i]=arr[i];
		}
		delete [] arr;
		arr=new T [newSize];
		for (int i=0;i<siz;i++){
			arr[i]=tempArr[i];
		}
		siz=newSize;
		delete [] tempArr;
	}
	int size(){
		return this->siz;
	}
	T & operator [](int index){
		return arr[index];
	}
	Vector<T> & operator = (const Vector<T> & v){
		if (&v==this)
			return *this;
		delete [] this->arr;
		this->siz=v.siz;
		arr= new T [siz];

		for (int i=0;i<siz;i++)
			arr[i]=v.arr[i];
		return *this;
	}
};
class trieNode{
public:
	string meaning;
	Vector<string> synonyms;
	trieNode *nodeArray[26];
	bool isComplete;
	char value;
	trieNode(){
		meaning="";
		for (int i=0;i<26;i++){
			nodeArray[i]=NULL;
		}
		isComplete=false;
	}
};
class TRIE{
public:
	trieNode *root;
	TRIE(){
		root=new trieNode;
	}
	int getIndex(char alphabet){
		return (int(alphabet)-97);
	}
	bool insertWordInTree(string &word,ifstream &readFile){
		word+='\0';
		trieNode *currentLeaf=root;
		int i=1;
		while (word[i]!='\0'){
			int alphabetIndex=getIndex(word[i]);
			if(currentLeaf->nodeArray[alphabetIndex] == NULL) {
				currentLeaf->nodeArray[alphabetIndex]=new trieNode;
				currentLeaf->nodeArray[alphabetIndex]->value=word[i];
			}
			currentLeaf=currentLeaf->nodeArray[alphabetIndex];
			i++;
		}
		currentLeaf->isComplete=true;
		string line="";
		getline(readFile,line);
		currentLeaf->meaning=line.substr(2,line.length());

		i=0;
		while (true){
			line ="";
			getline(readFile,line);
			if (line[0]=='-' || readFile.eof()){
				word=line;
				break;
			}
			currentLeaf->synonyms.resize(i+1);
			currentLeaf->synonyms[i]=line;
			i++;
		}
		if (readFile.eof())
			return false;
		else
			return true;
	}
	void CreateDictionary(string path){
		ifstream readFile(path,std::ifstream::in);
		string line;
		if (readFile.is_open()){
			while (!readFile.eof()){
				line ="";
				getline(readFile,line);
				while (insertWordInTree(line,readFile));
			}
		}
	}
	void GetWords(int size,trieNode *root, string wordFormed, Vector<string> &words,int &wordIndex,Vector <string> &meanings, Vector<Vector<string>> &synonyms){
		if (!root->isComplete){
			int i=0;
			while (i<size){
				if (root->nodeArray[i]!=NULL){
					GetWords(size,root->nodeArray[i],wordFormed+root->nodeArray[i]->value,words,wordIndex,meanings,synonyms);
				}
				i++;
			}
		}
		else if (root->isComplete){
			wordIndex++;
			words.resize(wordIndex);
			meanings.resize(wordIndex);
			synonyms.resize(wordIndex);
			synonyms[wordIndex-1].resize(root->synonyms.size());
			words[wordIndex-1]=wordFormed;
			meanings[wordIndex-1]=root->meaning;
			synonyms[wordIndex-1]=root->synonyms;
			int i=0;
			while (i<size){
				if (root->nodeArray[i]!=NULL){
					GetWords(size,root->nodeArray[i],wordFormed+root->nodeArray[i]->value,words,wordIndex,meanings,synonyms);
				}
				i++;
			}
		}
	}
	Vector <string> GetWordsFinalArray(){
		string wordFormed="";
		Vector <string> words;
		Vector <string> meanings;
		Vector <Vector<string>> synonyms;
		int wordIndex=0;
		GetWords(26,root,wordFormed,words,wordIndex,meanings,synonyms);
		return words;
	}
	Vector <string> OutputAscending(){
		return GetWordsFinalArray();
	}
	Vector< string> OutputDescending(){
		Vector <string> words=GetWordsFinalArray();
		Vector <string> wordsInDescending;
		wordsInDescending.resize(words.size());
		for (int i=words.size()-1,j=0;i>=0;i--,j++){
			wordsInDescending[j]=words[i];
		}
		return wordsInDescending;
	}
	bool FindWord(string key){
		for (int i=0;i<GetWordsFinalArray().size();i++){
			if (GetWordsFinalArray()[i].compare(key)==0)
				return true;
		}
		return false;
	}
	Vector< string> FindSynonyms(string key){
		string wordFormed="";
		Vector <string> words;
		Vector <string> meanings;
		Vector <Vector<string>> synonyms;
		int wordIndex=0;
		GetWords(26,root,wordFormed,words,wordIndex,meanings,synonyms);
		for (int i=0;i<wordIndex;i++){
			if (words[i].compare(key)==0)
				return synonyms[i];
		}
	}
	string FindMeaning(string key){
		if (FindWord(key)){
		string wordFormed="";
		Vector <string> words;
		Vector <string> meanings;
		Vector <Vector<string>> synonyms;
		int wordIndex=0;
		words.resize(wordIndex+1);
		meanings.resize(wordIndex+1);
		GetWords(26,root,wordFormed,words,wordIndex,meanings,synonyms);
		for (int i=0;i<words.size();i++){
			if (words[i]==key)
				return meanings[i];
		}
		}
		else
			return "No Such Word Found";
	}
	Vector< string> OutputSmaller(int length){
		Vector<string> smallerWords;
		int count=0;
		for (int i=0;i<GetWordsFinalArray().size();i++){
			if (GetWordsFinalArray()[i].length()<length){
				count++;
			}
		}
		smallerWords.resize(count);
		for (int i=0,j=0;i<GetWordsFinalArray().size();i++){
			if (GetWordsFinalArray()[i].length()<length){
				smallerWords[j]=GetWordsFinalArray()[i];
				j++;
			}
		}
		return smallerWords;
	}
	Vector< string> OutputSE(int length){
		Vector<string> smallerOrEqualWords;
		int count=0;
		for (int i=0;i<GetWordsFinalArray().size();i++){
			if (GetWordsFinalArray()[i].length()<=length){
				count++;
			}
		}
		smallerOrEqualWords.resize(count);
		for (int i=0,j=0;i<GetWordsFinalArray().size();i++){
			if (GetWordsFinalArray()[i].length()<=length){
				smallerOrEqualWords[j]=GetWordsFinalArray()[i];
				j++;
			}
		}
		return smallerOrEqualWords;
	}
	Vector< string> OutputGreater(int length){
		Vector<string> greaterWords;
		int count=0;
		for (int i=0;i<GetWordsFinalArray().size();i++){
			if (GetWordsFinalArray()[i].length()>length){
				count++;
			}
		}
		greaterWords.resize(count);
		for (int i=0,j=0;i<GetWordsFinalArray().size();i++){
			if (GetWordsFinalArray()[i].length()>length){
				greaterWords[j]=GetWordsFinalArray()[i];
				j++;
			}
		}
		return greaterWords;
	}
	Vector< string> OutputPrefix(string prefix){
		Vector <string> prefixArray;
		int prefixArraySize=0;
		int sizeOfPrefix=prefix.length();
		for (int i=0;i<GetWordsFinalArray().size();i++){
			bool Flag=true;
			for (int j=0;j<sizeOfPrefix;j++){
				if (GetWordsFinalArray()[i][j]!=prefix[j]){
					Flag=false;
					break;
				}
			}
			if (Flag){
				prefixArraySize++;
				prefixArray.resize(prefixArraySize);
				prefixArray[prefixArraySize-1]=GetWordsFinalArray()[i];
			}
		}
		return prefixArray;
	}
	Vector< string> OutputSuffix(string suffix){
		Vector <string> suffixArray;
		int suffixArraySize=0;
		int sizeOfsuffix=suffix.length();
		for (int i=0;i<GetWordsFinalArray().size();i++){
			bool Flag=true;
			for (int j=sizeOfsuffix-1,k=GetWordsFinalArray()[i].length()-1;j>=0;j--,k--){
				if (GetWordsFinalArray()[i][k]!=suffix[j]){
					Flag=false;
					break;
				}
			}
			if (Flag){
				suffixArraySize++;
				suffixArray.resize(suffixArraySize);
				suffixArray[suffixArraySize-1]=GetWordsFinalArray()[i];
			}
		}
		return suffixArray;
	}
	Vector< string> OutputAnagrams(string key){
		Vector <string> anagramsArray;
		int anagramsArraySize=0;
		int anagramSize=key.length();
		for (int i=0;i<GetWordsFinalArray().size();i++){
			bool Flag=true;
			if (anagramSize!=GetWordsFinalArray()[i].length())
				Flag=false;
			else{
				if (key.compare(GetWordsFinalArray()[i])!=0){
				Flag=true;
				string tempWord=GetWordsFinalArray()[i];
				string tempKey=key;
				for (int j=1;j<anagramSize;j++){
					for (int k=0;k<anagramSize-j;k++){
						if (int(tempKey[k])>int(tempKey[k+1])){
							char temp=tempKey[k];
							tempKey[k]=tempKey[k+1];
							tempKey[k+1]=temp;
						}
						if (int(tempWord[k])>int(tempWord[k+1])){
							char tempWordChar=tempWord[k];
							tempWord[k]=tempWord[k+1];
							tempWord[k+1]=tempWordChar;
						}
					}
				}
				for (int j=0;j<anagramSize;j++){
					if (tempWord[j]!=tempKey[j]){
						Flag=false;
						break;
					}
				}
				if (Flag){
					anagramsArraySize++;
					anagramsArray.resize(anagramsArraySize);
					anagramsArray[anagramsArraySize-1]=GetWordsFinalArray()[i];
				}
			}
			}
		}
		return anagramsArray;
	}
};