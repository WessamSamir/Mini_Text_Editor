#include "MiniText.h"

using namespace std;

MiniText::MiniText()
{
	Count = 0; 
}

MiniText::MiniText(int line, string in)
{
	numline = line;
	input = in;
}

// opinning the file
void MiniText::open()
{
	try
	{
		ifstream myfile;
		myfile.open("C:\\Users\\I SEvEN\\Desktop\\Test.txt");
		for (int i = 1; !(myfile.eof()); i++)
		{
			getline(myfile, input);
			if (input != "")
			{
				Lines[i] = input;
				Count++;
			}
		}
		myfile.close();
	}
	catch (exception e)
	{
		cout << "Can't open the file \n";
	}
}

// closing the file
void MiniText::close()
{
	ofstream myfile;
	myfile.clear();
	myfile.open("C:\\Users\\I SEvEN\\Desktop\\Test.txt");
	for (int i = 1; i <= Count; i++)
	{
		myfile << Lines[i] << endl;
	}
	myfile.close();
	Lines.clear();
}

void MiniText::add()
{
	Count++;
	cout << "Enter your string" << endl;
	cin.ignore();
	getline(cin, input);
	Lines[Count] = input;
	undostack.push({ 1,{Count,input} });
	cout << endl << "#####################################################################" << endl;
}

void MiniText::insert()
{

	cout << "Enter number of line" << endl;
	try
	{
		cin >> numline;
		if (cin.fail())
			throw "Invalid input";
		else if (Lines[numline].empty())
		{
			cout << "Enter your string" << endl;
			cin.ignore();
			getline(cin, input);
			Lines.at(numline) = input;
			Count = (Count + numline) - 1;
		}
		else
		{
			Count++;
			for (int i = Count; i > numline; i--)
			{
				Lines[i] = Lines[i - 1];
			}
			cout << "Enter your string" << endl;
			cin.ignore();
			getline(cin, input);
			Lines[numline] = input;
		}
		undostack.push({ 2,{numline,input} });
		cout << endl << "#####################################################################" << endl;
	}
	catch (const char* msg)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << msg << endl;
		cout << endl << "#####################################################################" << endl;
	}
}

void MiniText::Delete()
{
	cout << "Enter number of line" << endl;
	try
	{
		cin >> numline;
		if (cin.fail())
			throw "Invalid input";
		else
		{
			undostack.push({ 3,{numline,Lines[numline]} });
			if (numline <= Count)
			{
				for (int i = numline; i < Count; i++)
				{
					Lines[i] = Lines[i + 1];
				}
				Lines.erase(Count);
				Count--;
			}
			else if (numline == Count)
			{
				Lines.erase(Count);
				Count--;
			}
			else
				cout << "There is not  number of this line" << endl;
			cout << endl << "#####################################################################" << endl;
		}
		
	}
	catch (const char* msg)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << msg << endl;
		cout << endl << "#####################################################################" << endl;
	}
	
}

void MiniText::DeleteRange()
{
	int start, end;
	cout << "Enter the start of rang" << endl;
	cin.ignore();
	cin >> start;
	cout << "Enter  the end of rang" << endl;
	cin.ignore();
	cin >> end;
	 int startcount = start;
	 int countend = end + 1;
	 int range = Count - (end - start);
	if (start <= Count && end <= Count)
	{
		for (int i = startcount; i < range; i++)
		{
			undostack.push({ 7,{i,Lines[i]} });
			Lines[i] = Lines[countend];
			countend++;
		}
		for (int j = range; j != Count + 1; j++)
		{
			undostack.push({ 7,{j,Lines[j]} });
		}
		for (int i = range; i <= Count; i++)
		{
			Lines.erase(range);
			range++;
		}
		Count = Count - ((end - start)+1);
	}
	else
		cout << "This range is out of boundres";
	cout << endl << "#####################################################################" << endl;
}

void MiniText::update()
{
	cout << "Enter number of line" << endl;
	try
	{
		cin >> numline;
		if (cin.fail())
			throw "Invalid input";
		else if (numline <= Count)
		{
			undostack.push({ 4,{numline,Lines[numline]} });
			cout << "please, Enter your update" << endl;
			cin.ignore();
			getline(cin, input);
			Lines[numline] = input;
		}
		else
			cout << "There is not  number of this line" << endl;
		cout << endl << "#####################################################################" << endl;
	}
	catch (const char* msg)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << msg << endl;
		cout << endl << "#####################################################################" << endl;
	}
}

void MiniText::Find()
{
	string word;
	cout << "Enter your word to find" << endl;
	cin.ignore();
	getline(cin, word);
	queue<int>finds;
	string strlower, wordlower = word;

	for (int i = 0; i < word.size(); i++)
	{
		wordlower[i] = tolower(word[i]);
	}

	for (int i = 1; i <= Count; i++)
	{

		strlower = Lines[i];
		for (int i = 0; i < strlower.size(); i++)
		{
			strlower[i] = tolower(strlower[i]);
		}

		if (strlower.find(wordlower) != -1)
		{
			finds.push(i);
		}
	}

	if (finds.empty())
		cout << "This word does not  found in text" << endl;
	else
	{
		while (!finds.empty())
		{
			cout << "This word \"" << word << "\" is found in line number " << finds.front() << endl;
			finds.pop();
		}
	}
	cout << endl << "#####################################################################" << endl;
}

void MiniText::Replace()
{
	string word, replace;
	cout << "Enter the old word" << endl;
	cin.ignore();
	getline(cin, word);
	cout << "Enter the new word" << endl;
	cin >> replace;
	string strlower, wordlower = word;
	bool found = false;
	bool yes = true;

	for (int i = 0; i < word.size(); i++)
	{
		wordlower[i] = tolower(word[i]);
	}

	for (int i = 1; i <= Count; i++)
	{
		strlower = Lines[i];
		for (int i = 0; i < strlower.size(); i++)
		{
			strlower[i] = tolower(strlower[i]);
		}

		while (strlower.find(wordlower) != -1)
		{
			for (int j = 0; j < strlower.size(); j++)
			{
				if (strlower[j] == wordlower[0])
				{
					int k = j + 1, c = 1;
					while (c < wordlower.size())
					{
						if (strlower[k] != wordlower[c])
						{
							yes = false;
							break;
						}
						k++, c++;
					}
					if (yes)
					{
						strlower.replace(j, wordlower.size(), replace);
						Lines[i] = strlower;
						found = true;
						undostack.push({ 5,{i,word} });
						undostack.push({ 6,{i,replace} });
						break;
					}
					else
						yes = true;
				}
			}
		}
	}
	if (!found)
		cout << "The old word doesn’t  exist in text" << endl;
	cout << endl << "#####################################################################" << endl;
}

void MiniText::getLine()
{
	cout << "Enter number of line" << endl;
	try
	{
		cin >> numline;
		if (cin.fail())
			throw "Invalid input";
		else if (numline <= Count)
		{
			cout << Lines[numline] << endl;
		}
		else
			cout << "There is not  number of this line" << endl;
		cout << endl << "#####################################################################" << endl;
	}
	catch (const char* msg)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << msg << endl;
		cout << endl << "#####################################################################" << endl;
	}
}

void MiniText::show()
{
	for (int i = 1; i <= Count; i++)
	{
		cout << i << " " << Lines[i] << endl;
	}
	cout << endl << "#####################################################################" << endl;
}

void MiniText::undo()
{
	if (!undostack.empty())
	{
		if (undostack.top().first == 1)
		{
			Lines.erase(Count);
			Count--;
			undostack.pop();
		}
		else if (undostack.top().first == 2)
		{
			numline = undostack.top().second.first;
			if (Lines[numline - 1] == "" && numline - 1 != 0)
			{
				Lines.erase(numline);
				numline--;
				Count--;
				while (Lines[numline] == "")
				{
					Lines.erase(numline);
					numline--;
					Count--;
				}
			}
			else
			{
				for (int i = undostack.top().second.first; i < Count; i++)
				{
					Lines[i] = Lines[i + 1];
				}
				Lines.erase(Count);
				Count--;
			}
			undostack.pop();
		}
		else if (undostack.top().first == 3)
		{
			numline = undostack.top().second.first;
			if (numline == (Count + 1))
			{
				Lines[numline] = undostack.top().second.second;
			}
			else
			{
				for (int i = Count + 1; i > numline; i--)
				{
					Lines[i] = Lines[i - 1];
				}
				Lines[numline] = undostack.top().second.second;
				Count++;
			}
			undostack.pop();
		}
		else if (undostack.top().first == 4)
		{
			Lines[undostack.top().second.first] = undostack.top().second.second;
			undostack.pop();
		}
		else if (undostack.top().first == 6)
		{
			while (undostack.top().first == 6)
			{
				string word = undostack.top().second.second;
				undostack.pop();
				string replace = undostack.top().second.second;
				undostack.pop();
				string strlower, wordlower = word;
				bool yes = true;

				for (int i = 0; i < word.size(); i++)
				{
					wordlower[i] = tolower(word[i]);
				}

				for (int i = 1; i <= Count; i++)
				{
					strlower = Lines[i];
					for (int i = 0; i < strlower.size(); i++)
					{
						strlower[i] = tolower(strlower[i]);
					}

					while (strlower.find(wordlower) != -1)
					{
						for (int j = undostack.top().second.first; j < strlower.size(); j++)
						{
							if (strlower[j] == wordlower[0])
							{
								int k = j + 1, c = 1;
								while (c < wordlower.size())
								{
									if (strlower[k] != wordlower[c])
									{
										yes = false;
										break;
									}
									k++, c++;
								}
								if (yes)
								{
									strlower.replace(j, wordlower.size(), replace);
									Lines[i] = strlower;
									break;
								}
								else
									yes = true;
							}
						}
					}
				}
			}
		}
		else if (undostack.top().first == 7)
		{
			for (int i = 1; !(undostack.empty())&& undostack.top().first == 7; i++)
			{
				numline = undostack.top().second.first;
				Lines[numline] = undostack.top().second.second;
				undostack.pop();
				if (i >= Count)
					Count++;
			}
		}
		show();
	}
	else
	{
	cout << "The undostack is empty";
	}
	cout << endl << "#####################################################################" << endl;
}
