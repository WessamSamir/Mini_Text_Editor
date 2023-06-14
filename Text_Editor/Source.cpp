#include <iostream>
#include <limits>
#include "MiniText.h"

using namespace std;

int main()
{
	MiniText text;

	text.open();
	while (true)
	{
		int choice;
		cout << "choose number from these : " << endl;
		cout << " 1. add line" << endl;
		cout << " 2. insert line" << endl;
		cout << " 3. delete line" << endl;
		cout << " 4. delete range" << endl;
		cout << " 5. update line" << endl;
		cout << " 6. find word" << endl;
		cout << " 7. replace word" << endl;
		cout << " 8. get line" << endl;
		cout << " 9. show all lines" << endl;
		cout << " 10. undo last operation" << endl;
		cout << " 11. exit " << endl;
		cout << endl << "#####################################################################" << endl;
		try
		{
			cin >> choice;
			if (cin.fail())
				throw "Invalid input ";
			else if (choice == 1)
				text.add();
			else if (choice == 2)
				text.insert();
			else if (choice == 3)
				text.Delete();
			else if (choice == 4)
				text.DeleteRange();
			else if (choice == 5)
				text.update();
			else if (choice == 6)
				text.Find();
			else if (choice == 7)
				text.Replace();
			else if (choice == 8)
				text.getLine();
			else if (choice == 9)
				text.show();
			else if (choice == 10)
				text.undo();
			else if (choice == 11)
			{
				text.close();
				exit(0);
				//break;
			} 
			else 
				throw "Invalid input ";
		}
		catch (const char* msg)
		{
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cout << msg << endl;
			cout << "Please check your choice \n";
			cout << endl << "#####################################################################" << endl;
		}
		
	}
}

