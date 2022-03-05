// HW2 - movies Search Program
//
// Ibrahim Khan
// 2/14/22
// CS 1337.010
//
// Purpose:
// A program that takes in a word search file
// and finds words hidden in an array of characters
//
// ChangeLog:
// 2/14/22 -
// read in file and excluded comments
//
// 2/15/22 -
// added a read in file system where comments and blank lines are
// both ignored
//
// 2/16/22 -
// read in file and stored values in variables, vectors , and arrays
//  - this was done by checking the characters on a line, and if it was a number
//    then the value would be stored in the row col variables. then the grid was
//    read right after, using a for loop to store the values of the gird into an
//    array. then the values of the movies were stored into a vector using the
//    pushback function
//  - I then outputted the values of the row and col to the user, as well as the
//    grid for the word search
//
// 2/17/22-
// - created a system in which the words are to be searched within the array
// - these are then outputted alongside there coordinates where they were found
// - as well as the direction in which they were found
//
// 2/18/22-
// - created a system where found words are stored in a vector, then this vector is compared
// to the list of words that are given. and with this we are able to output the words that are
// not found

// preprocessor directives
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <cstring>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>

// namespace standard
using namespace std;

// global variables
string fileName, line;
ifstream inFile;
vector<string> movies;
vector<string> found;
const int MAX_SIZE = 100;
char grid[MAX_SIZE][MAX_SIZE];
int row = 0;
int col = 0;

// For searching in all 8 direction
int rowDir[] =    { -1,    -1,   -1,    0,   0,    1,   1,    1  };
int colDir[] =    { -1,     0,    1,   -1,   1, -  1,   0,    1  };
string dir[] =    { "NW",  "N", "NE",  "W", "E", "SW", "S", "SE" };
int direction;

// function prototypes
void fileInstructions();
void checkFile();
void readFile(char grid[MAX_SIZE][MAX_SIZE]);
bool checkLetters(char grid[100][100], int xVal, int yVal, string movies);
void checkWords(char grid[MAX_SIZE][MAX_SIZE], string movies);
void outputWords();
void outputNonWords();


int main()
{
    fileInstructions();
	checkFile();
    readFile(grid);
    outputWords();
    outputNonWords();

    return 0;
}


// function that prompts user to enter the file name
// and stores it in a string variable fileName

void fileInstructions()
{
    // prompt the user to enter the file name
	cout << "Please enter the name of the file: ";
	cin >> fileName;
}

// function that opens the file, check if it is opened
// properly, and if not keeps prompting user until the
// proper file name is inputed or the user quits

void checkFile()
{
    // open the file with the given file name
	inFile.open(fileName);

    // while the function is not open, prompt the user
    // until the function opens or the user quits
	while (!inFile)
	{
	    // prompt the user to enter the file name
		cout << "The file entered does not exist or cant be found.\n";
		cout << "The file name used was: " << fileName << endl;
		cout << "Please enter a new file name or type quit to quit\n";
		cin >> fileName;

        // if the user enters quit, exit the code
		if (fileName == "quit" || fileName == "QUIT")
		{
		    break;
		}

		inFile.open(fileName);
	}

    // if the fileName is valid, output the new file name
	if (inFile)
    {
        cout << "--The new file name is: " << fileName << endl;
    }
}



// a function that reads in the file and takes the data and stores in the variables
// finds:
// The values of the row and col
// stores the values of the grid into a 2D array called grid
// stores the values of the movies into an array called movies

void readFile(char grid[MAX_SIZE][MAX_SIZE])
{
    // while the file is read
    while (getline(inFile, line))
    {
        // if first char is #, reset loop
        if (line[0] == ('#'))
        {
            //comment line
            continue;
        }
        //if the line is empty, reset loop
        else if (line.empty())
        {
            //blank line
            continue;
        }

        // if the first char in the line is a number
        // do if statement

        if (isdigit(line[0]))
        {
            int index;

            // find the space between the values
            index = line.find(' ');

            // from the beginning to the space, record the value into row
            row = stoi(line.substr(0,index));

            // from the space onwards, record the value into col
            line = line.substr(index+1);
            col = stoi(line);

            // create an array grid now with the row and col
            //char grid[row][col];

            // create new string variable to store new lines
            string gridLine;

            // read in the line twice, to get rid of the movie title comment
            getline(inFile,gridLine);
            getline(inFile,gridLine);

            // output the number of rows and cols we found
            cout << "#Rows: " << row << ";" << " #Cols: " << col << endl;

            // store the values of the grid into the array and cout
            for(int x = 0; x < col; x++)
            {
                for(int y = 0; y < row; y++)
                {
                    // store each value first by row, increasing column by iteration
                    inFile >> grid[x][y];

                    // output the values of the row, increasing column by iteration
                    cout << grid[x][y];
                }
                // end the line after the row is read
                cout << endl;
            }

            // create new line for next data to be outputed

            cout << endl;

            // create a string movie, which will read each individual movie
            string movie;

            // while loop while the values are being read
            while (getline(inFile, movie))
            {
                // the values will only be read if the first char is not
                // a #(comment) and it is not an empty line
                if (movie[0] != ('#') && !(movie.empty()))
                {
                    // push back the read in string into movies vector
                    movies.push_back(movie);
                }
            }
        }
    }
}

// a function that takes in the vales within the vector, and compares it
// the individual values of the array. this is done by going from each and
// every char in the array, and if a value is matched, then searched in all
// 8 different directions. this is done until the word is found, or is not found

bool checkLetters(char grid[100][100], int xVal, int yVal, string movies)
{
    // get rid of the space in the vector to value to use for word search
    movies.erase(remove(movies.begin(), movies.end(), ' '), movies.end());

    // the grid value is not equal, return false
    if (grid[yVal][xVal] != movies[0])
    {
        return false;
    }

    // get the length of the vector value
    int movieLen = movies.length();

    // search in all 8 directions
    for (int dir = 0; dir < 8; dir++)
    {
        int k;
        int rd = yVal + rowDir[dir];
        int cd = xVal + colDir[dir];

        for (k = 1; k < movieLen; k++)
        {
            // if the value goes away from the word search list,
            // (negative, larger than the row/col values)
            // break
            if (rd >= row || rd < 0 || cd >= col || cd < 0)
            {
                break;
            }

            // if the new array value is not equal, break out of the loop and try again
            if (grid[rd][cd] != movies[k])
            {
                break;
            }

            // if a letter is found, add the last used direction to check again
            rd += rowDir[dir];
            cd += colDir[dir];

            // store direction for future output
            direction = dir;
        }

        // if the word is found and it matches the length, return true
        if (k == movieLen)
        {
            return true;
        }
    }
    // else return false
    return false;
}

void checkWords(char grid[MAX_SIZE][MAX_SIZE], string movies)
{
    // go through the vector and match in every value
    // from the array and output the ones that were true
    // from the previous function
    for (int y = 0; y < col; y++)
    {
        for (int x = 0; x < row; x++)
        {
            if (checkLetters(grid, x, y, movies))
            {
                cout << movies << " found at " << (y + 1) << ", " << (x + 1) << ": (direction = " << dir[direction] << ")" << endl;
                // store the found movies into a vector for future purposed when we are searching for non found words
                found.push_back(movies);
            }
        }

    }
}

// a function that creates a loop to output all of the vectors that are found
void outputWords()
{
    for (int count = 0; count < movies.size(); count++)
    {
        checkWords(grid, movies[count]);
    }
}
void outputNonWords()
{
    // separate counting variable
    int y = 0;

    // output which movies arent found
    cout << "\nCouldn't find the movies:\n";

    for (int x = 0; x < movies.size(); x++)
    {
        // if the movies are not equal
        if (movies[x] != found[y])
        {
            // output the movie that is not equal
            cout << movies[x] << endl;

            // add one more to the counting variable to allow for the movie list to catch up
            // to the list of the not found
            x++;
        }
        // add separate counting variable
        y++;
    }
}
