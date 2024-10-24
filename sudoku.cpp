#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <chrono>
#include <thread>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!\n";
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+\n";
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|\n";
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

// "=================== Question 1 ==================="

bool is_complete(const char board[9][9]){
	for (int i=0; i < 9;i++ ){
		for (int j=0; j<9;j++){
			if ((board[i][j] <=  '0') && (board[i][j] > '9'))
				return true;
		}
	}
	return false;
}

// "=================== Question 2 ==================="

bool make_move(const char* position, char digit, char board[9][9]){
	// Get row as a integer by subtracting the character value of 'A'
	int row = position[0] - 'A'; 
  // Get column as a integer by subtracting the character value of '0'
  int col = position[1] - '0' ;

  // Check if row and column indices are valid while in the sudoku board
	if (row < 0 || row >= 9 || col < 0 || col >= 9 ){
		return false;}

  // Check if the cell is empty, if not then exit
	if (board[row][col] != '.'){
		return false;
	}

	// Check the 3 x 3 sector if you can make a move with the digit 
  // Get the starting row and column for the 3 x 3 sector
	int startrow = (row  / 3) * 3;
  // Get the starting row and column for the 3 x 3 sector
	int startcol = (col / 3) * 3;

  // Loop through the 3 x 3 sector
	for (int i = startrow; i < startrow + 3; i++){
		for(int j = startcol; j < startcol + 3; j++){
      // Check if the digit is already in the row or column of the 3 x 3 sector
			if (board[i][j] == digit){
				return false;
			}
		}
	}

  // Check if digit is already in row or column
	for (int i = 0; i < 9; i++){
			if (board[row][i]==digit || board[i][col] == digit){
				return false;
			}
	}
	
  // Insert the digit into the row and column
	board[row][col] = digit;

	return true;
}

// "=================== Question 3 ==================="

bool save_board(const char* filename , const char board[9][9]){
// Outputs the two dimensional character array board to file with name filename
// Return value should be true if file successfully written

// Open the input and output streams for reading the file and writing the copy
ifstream in_stream;
ofstream out_stream;

// Open the file with the name filename
in_stream.open(filename);
out_stream.open("copy_of_dat");

// Check if the file was opened successfully if not then return false
if (!out_stream){
	return false;
}

// Save the board to the file
for (int row = 0; row < 9; ++row) {
    for (int col = 0; col < 9; ++col) {
        out_stream << board[row][col];
    }
    out_stream << '\n'; // Add a newline after each row
}

out_stream.close();
in_stream.close();

return true;
}

// "=================== Question 4 ==================="

// Wrapper function to ensure that the counter is reset and the board is solved
bool solve_board(char board[9][9]){

	int rec_counter = 0;

  // Call the recursive function to solve the board
	return solve_board(board,rec_counter);
}

// Function to solve the Sudoku board using recursion
bool solve_board(char board[9][9], int &rec_counter){

  // Array to hold the current row and column
	char position[3]; 

  // Insert the Null terminator at the end of the string
	position[2] = '\0'; 
	
	// Loop through each row from ('A' to 'I')
	for (char row = 'A'; row <= 'I'; row++){ 

		// Loop through each column ('0' to '8')
		for (char col = '0'; col <= '8'; col++){

			// Check if the current cell is empty (denoted by '.')
			if (board[row - 'A'][col - '0'] == '.'){

				// Store the current position of row and column
				position[0] = row;
				position[1] = col; 

				// Try placing digits '1' to '9' in the current cell
				for (char digit = '1'; digit <= '9'; digit++){ 

					// Check if the current digit is a valid move 
					if (make_move(position,digit,board)){ // Returns a boolean of true or false in terms of valid
						// Increment the recursive counter
            rec_counter++;
  
            // If the board is solved, return true
						if (solve_board(board,rec_counter)){

							return true;}

						// Else backtrack through the code by resetting the previous value to empty
						board[row - 'A'][col - '0'] = '.';
					}
				} // I no valid digit is found for the current cell, backtrack 

				return false;
			}
		}
	}
	// If all cells are filled correctly, return true thereby denoting solution found
	return true;
}

// "=================== Question 5 ==================="

// Function which calculates the time taken to solve the board using recursion
int calc_time(char board[9][9], int &rec_counter, bool &solved) {
    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();

    // Attempt to solve the board
    solved = solve_board(board, rec_counter);
    
    // Stop the timer
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration in milliseconds
    std::chrono::duration<double, std::milli> duration = end - start;

    // Return the time taken in milliseconds
    return static_cast<int>(duration.count());
}

