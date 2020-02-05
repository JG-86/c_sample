// purpose: read a list of job listings from a file, search by position title or skill
// 
// input file format:  
// line with  position description 
// followed by line with number of skills desired
// followed by n lines, each listing a skill
// followed by a line with salary
// followed by company line
//
// This program first prompts the user for an input file name. 
// The user can then search for matching job listings via keyword skill or title
// Search is case-insensitive and will search for any string within the title or skill
// output is sorted alphabetically by title
//
//author: J Garcia

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <stdlib.h>
#include <string.h>
using namespace std;


// structs
struct Position
{
	char title[256];
	char skillNumChar[3];
	char skill[20][256];
	char salaryChar[256];
	char company[256];
	int  skillNum;
	int  salary;
};

struct Position_List
{
	Position input[20];
	
}	inputList,sortList;



struct Matches
{
	char title[256];
	char skill[20][256];
	char company[256];
	int  salary;
};

struct Match_List
{
	Matches outList[20];
	
}	outputList;

struct Skill_LowerCase
{
	char lower[20][256];
};


// function Prototypes
Position_List import_data (Position_List &inputList, ifstream& input,const char  *filename );
Position_List search_skill(Position_List inputList); 
Position_List sort_title  (Position_List &inputList);
Position_List search_title(Position_List inputList);

int 	 checkNumPositions  (Position_List inputList);
void 	 print_sortedList   (Position_List &inputList);
void 	 print_result_format();
void  	 menu			    (Position_List &inputList);

int main()
{
	ifstream input;
		
	// display Welcome and enter file name 
	cout << "" 											  << endl;
	cout << "Please enter the name of a file to search: " << endl;

	// Enter file name
	char filename[256];
	cin >> filename;
	
	// import data into inputList
	inputList = import_data(inputList, input, filename);
	
	// check how many jobs are in inputList
	int numPositions;
	numPositions = checkNumPositions(inputList);
	
	// Sort inputList by title
	sortList = sort_title(inputList);
	
	
	//PRINT SORTED LIST of inputs - uncomment to print full sorted list
	//print_sortedList(inputList);
	
	// PRINT MENU
	menu(inputList);	
	
	// print end of program message
	cout << "" << 			   endl;
	cout << "End of search"<<  endl;
	cout << "" <<  			   endl;

	return 0;
} 
//*** end of main ***//


// function to import data and write to inputList
Position_List import_data(Position_List &inputList, ifstream& input, const char *filename)
{
	
	input.open(filename);
	
	// if open fails, exit
	if(input.fail())
	{
		cout << "Input file: "    << filename << " does not exist." << endl;
		cout << "Program exiting."<< 								   endl;
		cout << ""				  << 			  			  		   endl;
		exit(1);
	}
	
	int i=0, length;
	char firstLine[256];
	
	do{
	char line[256];
	// getline temporary variable 'line'
	input.getline(line,256);
	
	int stringLength;
	stringLength = strlen(line);
		if(stringLength==0) break;
	
	
	// copy line to input[i].title
	strcpy(inputList.input[i].title,line);
	
	length = i;
	
	// get line after input title as a char, then convert to int
	input.getline(inputList.input[i].skillNumChar,3); 
	// convert skills to int
	inputList.input[i].skillNum = atoi(inputList.input[i].skillNumChar); 
	
	
	// use int skillNum to get next lines as skills
		for(int j=0; j < inputList.input[i].skillNum; j++)
		{
			input.getline(inputList.input[i].skill[j],256);
		}			
	
	// get next line and write to input[i].salary
	input.getline(inputList.input[i].salaryChar,256);
	inputList.input[i].salary = atoi(inputList.input[i].salaryChar);
	
	// get next line and write to input[i].title
	input.getline(inputList.input[i].company,256);
	
	i++;
	
	
	}while(!input.eof());	
	
	input.close();
	
	return inputList;
}


// function to sort Position_List by title
Position_List sort_title(Position_List &inputList )
{
	Position_List sorted;
	// run loop 40 times to sort fully
	for(int j=0; j<41; j++)
	{
		for (int i = 0; i < 20  ; i++)
		{
			char temp[256]     ;     // temp title
			int  tempSal	   ;     // temp Salary
			char tempCo[256]   ;     // temp company
			char tempSkill[20][256]; // temp skills
			int  tempSkillNum  ;	 // temp number of Skills for each input
			if(strncmp(inputList.input[i].title,  inputList.input[i+1].title, 3) > 0)
			{
				// copy [i] to temporary variables
				strcpy(temp   , inputList.input[i].title);
				strcpy(sorted.input[i].title   , inputList.input[i].title);
				strcpy(tempCo , inputList.input[i].company);
				tempSal       = inputList.input[i].salary;
				tempSkillNum  = inputList.input[i].skillNum;
				
				// copy [i] to temporary skills loop
				for(int k=0; k < 20; k++)
				{
					strcpy(tempSkill[k], inputList.input[i].skill[k]);
				}
								
				// copy [i+1]  to [i] variables
				strcpy(inputList.input[i].title  , inputList.input[i+1].title);
				strcpy(inputList.input[i].company, inputList.input[i+1].company);
				inputList.input[i].salary        = inputList.input[i+1].salary;
				inputList.input[i].skillNum      = inputList.input[i+1].skillNum;
				
				// copy Skills [i+1] to [i]
				for(int k=0; k < 20; k++)
				{
					strcpy(inputList.input[i].skill[k], inputList.input[i+1].skill[k]);
				}
				
				// copy temporary to [i+1]
				strcpy(inputList.input[i+1].title  , temp   );
				strcpy(inputList.input[i+1].company, tempCo );
				inputList.input[i+1].salary   = tempSal;
				inputList.input[i+1].skillNum = tempSkillNum;
				
				// copy tempSkills to [i+1]
				for(int k=0; k < 20; k++)
				{
					strcpy(inputList.input[i+1].skill[k], tempSkill[k]);
				}
			}
		}
	j++;
	}
	return sorted;
	
}

// function to search by title
Position_List search_title(Position_List inputList)
{
	char titleChoice[50];
	
	cout << "Enter title search criteria: " ;
	
	cin.getline(titleChoice,256);
	
	cout << ""<< endl;

	// CONVERT ENTERED TITLECHOICE TO LOWERCASE
	char titleChoice_lower[256];
	titleChoice_lower[0]='\0';
	char c;
	int i=0;
	while (titleChoice[i])
	{
		c = tolower(titleChoice[i]);
		strncat(titleChoice_lower, &c ,1);
		i++;
	}
	
	// loop through input titles
	int count=0;
	for(int k=0; k < 20; k++)
	{
		// CONVERT ALL TITLES TO LOWERCASE
		char title_lower[256];
		title_lower[0]='\0';
		char d;
		 i=0;
		 
		while (inputList.input[k].title[i])
		{
			d = tolower(inputList.input[k].title[i]);
			strncat(title_lower, &d ,1);
			i++;
		}
		
		
		// USE STRSTR ON LOWERCASE
		char *found;
		found = strstr(title_lower,titleChoice_lower); 
		if(found ) 
		{
			// counts number of matches
			count++; 	 
			
			// print result header only on first match
			if(count==1) 
			{
				print_result_format();
			}
				
			cout << setfill(' ') 
				<< left << setw(45) 
				<< inputList.input[k].title
				<< left << setw(3) << "$"
				<< left << setw(8) << inputList.input[k].salary 
				<< right << setw(40)
				<< inputList.input[k].company << endl;
				
			for(int m=0; m < inputList.input[k].skillNum; m++)
			{
				cout << "\t"
				 << inputList.input[k].skill[m] <<endl;
			}	
			
		}
		
	}
	
	// if no matches found
	if(count==0)
		{
			cout<<"No matches found."<<endl;
		}
}


// function to search entered skill 
Position_List search_skill(Position_List inputList)
{
	// create struct for lower case skills
	Skill_LowerCase skill_lowerCase[20];
	
	char skillChoice[256];
	cout << "Enter skill search criteria: ";
	
	cin.getline(skillChoice,256);
	cout << "" << endl;
	
	char input_matchTitle[10][256];
	char input_matchCompany[10][256];
	char input_matchSkills[10][256];
	int  input_matchSalary[10];
	

	// CONVERT SKILLCHOICE TO LOWER
	char skillChoice_lower[256];
	skillChoice_lower[0]='\0';
	char c;
	int i=0;
	while (skillChoice[i])
	{
		c = tolower(skillChoice[i]);
		strncat(skillChoice_lower, &c ,1);
		i++;
	}
		
	// initialize skill_lower first char as null skill TO LOWER
	char skill_lower[20][256];
	for(int i=0;i<20;i++)
	{
		skill_lower[i][0]='\0';
	
		for(int j=0;j<20;j++)
		{
			skill_lowerCase[i].lower[j][0] = '\0';
		}	
	}
	
	// CONVERT ALL SKILLS TO LOWER CASE
	//loop through inputs
	int count = 0;
	for(int i=0;i<20;i++)
	{
		// loop through each skill within each input
		for(int j=0;j<20;j++)
		{
			int k=0;
			char d;
			while(inputList.input[i].skill[j][k])
			{
				d = tolower(inputList.input[i].skill[j][k]);
				strncat(skill_lowerCase[i].lower[j],&d,1);
				k++;
			}
		}
			
		// USE STRSTR WITH LOWERCASE to find substring
		char *found2;
		// loop through each skill within each input
		for(int j=0;j<20;j++)
		{
			// find substring skillChoice within each skill 
			found2 = strstr(skill_lowerCase[i].lower[j], skillChoice_lower);
			
			if(found2)
			{
				count++;
				
				// print table header only on first match
				if(count==1) 
				{
					print_result_format();
				}
						
			// print out input title, salary, company
			cout << setfill(' ') 
				 << left << setw(45) 
				 << inputList.input[i].title
				 << left << setw(3) << "$"
				 << left << setw(8) << inputList.input[i].salary 
				 << right << setw(40)
				 << inputList.input[i].company << endl;
			
				// loop to print all skills within input
				for(int m=0; m < inputList.input[i].skillNum; m++)
					{
						cout << "\t"
							 << inputList.input[i].skill[m] << endl;
					}	
			break;				
			}
			
		}
	}
	
	// if no matches found
	if(count==0)
		{
			cout << "No matches found." << endl;
		}
	
}


// function to check number of inputs in inputList
int checkNumPositions(Position_List inputList)
{
	int length;
	for(int i=0; i<20; i++)
		{
			if(inputList.input[i].title[0]=='\0')
			break;
			length = i;
		}
		if(length==0)
		{	
		cout << "No job listings in this file. Enter a file with job listings."<<endl;
		cout << "Program exiting."											   <<endl;
		cout << ""															   <<endl;
		exit(1);
		}	
	
	return length;
}	

// function to print results format
void print_result_format()
{
	// SET FORMAT FOR OUTPUT
	cout << setfill(' ') 
	<< left  << setw(45) << "Position Title" 
	<< left  << setw(8)  << "Salary" 
	<< right << setw(40) << "Company"        << endl;
				
	cout << setfill('-') << setw(100)<< ""   << endl;
}
	

	

//function to display menu
void menu( Position_List &inputList )
{
		int choice;
	
	do{
		cout << "" 							  << endl;
		cout << "1 Search for jobs by skill"  << endl;
		cout << "2 Search for jobs by title"  << endl;
		cout << "3 Quit"					  << endl;
		cout << "Option> " 					  		 ;
		
		cin  >> choice;
		// TO ALLOW GETLINE FOR CHAR INPUT
		cin.get();	
			
		if(choice < 1 )
		{
			cout<< "not a valid choice, try again"<< endl;
		}
		else if(choice>3)
		{
			cout<<"not a valid choice, try again" << endl;
		}
	
		 
	// use choice to decide which search option
		switch(choice)
		{
			case 1: 
					search_skill(inputList);
					break;
				
			case 2: 
					search_title(inputList);
					break;
				
		}
		
	}while(choice!=3);
	
}

// function to print sorted list
void print_sortedList(Position_List &inputList)
{
	cout << "sorted list: "<<endl;
	for(int i=0; i <= 10; i++)
	{
		cout<< "job[" << i << "] : " << inputList.input[i].title << endl;
		cout<< "company: " << inputList.input[i].company 		 << endl;
		cout<< "salary : " << inputList.input[i].salary 	     << endl;
		for(int k=0; k< inputList.input[i].skillNum; k++)
		{
			cout<< "skills : " << inputList.input[i].skill[k]    << endl;
		}
		cout << "" << 											    endl;
	}
}	
