#define _CRT_SECURE_NO_DEPRECATE
#define MAX_ARRAY 20
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include<stdio.h>
#include<string>

using namespace std;

struct Person
{
	int id;
	string name;
	string address;

}; typedef struct Person Person;

void printArray(Person people[], int n);
void swap(Person *a, Person *b);
void sortAscending(Person people[], int n);
void printInfo(Person people[], int n);
void fillPersonArray(Person people[], string buff[], int index);
void printHistory(Person history[], int count);

int main()
{
	/*These variables are used to read in the text file and stores it into an array of strings */
	string buff[100];
	string filename = "a1.txt";
	Person people[MAX_ARRAY];
	string lastname_input;

	/*These variables are created to add a person into the records*/
	int count = 0;
	int num_people = 6;
	int flag = 1;
	char YorN;

	/*These variables are made for the search algorithm*/
	string result;
	int count_places = 0;
	bool flag_2 = true;
	bool outer_flag = true;
	char answer;

	Person history[MAX_ARRAY];
	int count_search_people = 0;

	/* This is block of code is to read in the data file */
	ifstream myfile(filename.c_str());

	if (myfile.is_open() == true)
	{
		while (getline(myfile, buff[count]))
		{
			count++;
		}
		myfile.close();
	}

	cout << endl << endl;

	int index = 0;


	fillPersonArray(people, buff, index);
	sortAscending(people, num_people);  // algorithm that sorts id in ascending order

/*print out existing members in the list and in ascending order */
	cout << "\nPerson's Information: \n\n";
	printInfo(people, num_people);

	cout << "Do you want to add a person to the list? 'y' or 'n'\n";

	// below is ask for user input of name, address and id then stores it into database
	while (flag == 1)
	{

		cin >> YorN;

		if (YorN == 'y')
		{
			cin.ignore(1000, '\n');

			cout << "Please enter Last and First name: " << endl << endl;
			getline(cin, people[num_people].name);
			cout << "\n";

			cout << "Please enter Address: " << endl << endl;
			getline(cin, people[num_people].address);
			cout << "\n";

			cout << "Please enter ID: ";
			cin >> people[num_people].id;
			cout << "\n";

			num_people++; // updates number of people in the list
		}

		if (YorN == 'n')
		{
			flag = 0;
		}

		cout << "Any other people to add ? 'y' or 'n'" << endl << endl;


	}

	// this is the algorithm that searches for people based on entered last name
	while (outer_flag == true)
	{
		cin.ignore(1000, '\n');
		cout << " Please type in a last name to search a person: \n";
		getline(cin, lastname_input);
		cout << "\n";

		for (int i = 0; i < num_people; i++)
		{
			while (flag_2 == true)  // finds how long the the last name is before it hits comma
			{
				if (people[i].name[count_places] == ' ')
				{
					flag_2 = false;
				}
				count_places++;
			}
			result = people[i].name.substr(0, count_places - 1);

			if (lastname_input.compare(result) == 0)
			{
				cout << "\n\nMatch Found! ";
				cout << "\n" << people[i].name;
				cout << "\nID: " << people[i].id;
				cout << "\n" << people[i].address << "\n";

				history[count_search_people].id = people[i].id;
				history[count_search_people].address = people[i].address;
				history[count_search_people].name = people[i].name;

				count_search_people++;
			}

			count_places = 0;  // reset counter
			flag_2 = true;  // reset flag
		}

		cout << "\nDo you want to search a new person: 'y' or 'n' ";
		scanf("%c", &answer);

		if (answer == 'n')
		{
			outer_flag = false;
		}

	}

	// prints out the history of people the user has searched and found
	printHistory(history, count_search_people);

	system("PAUSE");

	return 0;

}

// function that prints history
void printHistory(Person history[], int count)
{
	cout << "\nPEOPLE YOU HAVE SEARCHED AND FOUND ON THIS DATABASE: " << endl;
	cout << "____________________________________________________________";
	printInfo(history, count);

}

// function that fills the structures from read list
void fillPersonArray(Person people[], string buff[], int index)
{
	for (int i = 0; i < MAX_ARRAY; i++)
	{

		people[i].name = buff[index];

		stringstream geek(buff[index + 1]);
		geek >> people[i].id;

		people[i].address = buff[index + 2];

		index = index + 4;
	}
}

void printArray(Person people[], int n) //helper function
{
	for (int i = 0; i < n; i++)
	{
		cout << "\npeople[" << i << "].name: " << people[i].name;
		cout << "\npeople[" << i << "].id: " << people[i].id;
		cout << "\npeople[" << i << "].address: " << people[i].address;
		cout << "\n\n";
	}
}

void printInfo(Person people[], int n) // prints the list of people in correct format
{

	for (int i = 0; i < n; i++)
	{
		cout << "\n" << people[i].name;
		cout << "\nID: " << people[i].id;
		cout << "\n" << people[i].address;

		cout << "\n\n";
	}
}

void swap(Person *a, Person *b)  // swap function
{
	Person temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void sortAscending(Person people[], int n)  // sorting function that sorts id in ascending order
{
	for (int i = 1; i < n; i++)    // sort in ascending order
	{
		for (int j = 1; j < n; j++)
		{
			if (people[i].id < people[j - 1].id)
			{
				swap(&people[i], &people[j - 1]);
			}
		}
	}
}

