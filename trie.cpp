// TRIE.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TRIE.h"

int _tmain(int argc, _TCHAR* argv[])
{
	TRIE t;
	t.CreateDictionary("..\\trie\\dictionary.txt");
	//string wordFormed="";
	//Vector <string> words;
	//int wordIndex=0;
	//words.resize(wordIndex+1);
	//t.GetWords(26,t.root,wordFormed,words,wordIndex);

	//for (int i=0;i<8;i++)
	//	cout<<words[i]<<endl;

	Vector <string> words=t.OutputAscending();
	for (int i=0;i<words.size();i++)
	{
		cout<<words[i]<<endl;
	}
	cout<<endl<<endl;
	words=t.OutputDescending();
	for (int i=0;i<words.size();i++)
	{
		cout<<words[i]<<endl;
	}
	cout<<endl<<t.FindWord("peck")<<endl;
	cout<<endl<<t.FindWord("list")<<endl;
	cout<<endl<<t.FindWord("listen")<<endl;
	cout<<endl<<t.FindWord("pecked")<<endl;


	cout<<t.FindMeaning("peck")<<endl;
	cout<<t.FindMeaning("pecked")<<endl;
	cout<<t.FindMeaning("piper")<<endl;
	cout<<t.FindMeaning("pipe")<<endl;

	for (int i=0;i<t.OutputSmaller(8).size();i++)
	{
		cout<<t.OutputSmaller(8)[i]<<endl;
	}
	cout<<endl<<endl;

	for (int i=0;i<t.OutputGreater(5).size();i++)
	{
		cout<<t.OutputGreater(5)[i]<<endl;
	}

	cout<<endl<<endl;

	for (int i=0;i<t.OutputSE(4).size();i++)
	{
		cout<<t.OutputSE(4)[i]<<endl;
	}
	cout<<endl;

	for (int i=0;i<t.OutputPrefix("peck").size();i++)
	{
		cout<<t.OutputPrefix("peck")[i]<<endl;
	}
	cout<<endl;
	for (int i=0;i<t.OutputSuffix("listen").size();i++)
	{
		cout<<t.OutputSuffix("listen")[i]<<endl;
	}
	cout<<endl<<endl;
	for (int i=0;i<t.OutputAnagrams("silent").size();i++)
	{
		cout<<t.OutputAnagrams("silent")[i]<<endl;
	}
	cout<<endl;
	for (int i=0;i<t.FindSynonyms("piper").size();i++)
	{
		cout<<t.FindSynonyms("piper")[i]<<endl;
	}
}
