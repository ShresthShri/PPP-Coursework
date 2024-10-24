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

bool is_complete(const char board[9][9]){
	for (int i=0; i < 9;i++ ){
		for (int j=0; j<9;j++){
			if ((board[i][j] <=  '0') && (board[i][j] > '9'))
				return true;
		}
	}
	return false;
}

bool make_move(const char* position, char digit, char board[9][9]){
	
	int row = position[0] - 'A'; // Assuming first character is a digit ('0'-'8')
  int col = position[1] - '0' ; // Assuming second character is a digit ('0'-'8')

  // Validate row and column indices for accessing the Sudoku board.
	if (row < 0 || row >= 9 || col < 0 || col >= 9 ){
		return false;}

  // Check if the cell is empty, if not then exit
	if (board[row][col] != '.'){
		return false;
	}

	// Check the 3 x 3 sector if you can make a move
	int startrow = (row  / 3) * 3;
	int startcol = (col / 3) * 3;
	for (int i = startrow; i < startrow + 3; i++){
		for(int j = startcol; j < startcol + 3; j++){
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


bool save_board(const char* filename , const char board[9][9]){
// Outputs the two dimensional character array board to file with name filename
// Return value should be true if file successfully written

ifstream in_stream;
ofstream out_stream;

in_stream.open(filename);
out_stream.open("copy_of_dat");

if (!out_stream){
	return false;
}

// Display board function - but convert the Cout to out_stream
out_stream << "    ";
  for (int r = 0; r < 9; r++) {
    out_stream << (char)('1' + r) << "   ";
  }
  out_stream  << '\n';
  
  for (int r = 0; r < 9; r++) {
    if (!(r % 3)) {
      out_stream << "  +===========+===========+===========+\n";
    } else {
      out_stream << "  +---+---+---+---+---+---+---+---+---+\n";
    }

	out_stream << (char)('A' + r) << " ";
    for (int i = 0; i < 9; i++) {
      out_stream << ((i % 3) ? ':' : '|') << " ";
      out_stream << ((board[r][i] == '.') ? ' ' : board[r][i]) << " ";
    }
    out_stream << "|\n";
  }
  
  out_stream << "  +===========+===========+===========+\n"; // Frame at the end

  out_stream.close();
  in_stream.close();

  return true;
}
// Wrapper function to ensure that the counter 
bool solve_board(char board[9][9]){
	int rec_counter = 0;
	return solve_board(board,rec_counter);
}

// Function to solve the Sudoku board using recursion
bool solve_board(char board[9][9], int &rec_counter){

	char position[3]; // Array to hold the current row and column
	position[2] = '\0'; // Insert the Null terminator at the end of the string
	
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

