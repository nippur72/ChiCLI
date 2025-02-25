// ********************************************************************************
//
// ChiCLI - Chiron's CLI for 8-Bit Commodore Computers
// (c) 2021 by: Chiron Bramberger
//
// ********************************************************************************
// ********************************************************************************
// chicli.h
// ********************************************************************************
// ********************************************************************************
// MACRO VARS
// ********************************************************************************
// ********************** ADJUST THESE WHEN RAM IS EXCEEDED ***********************
// This section is about trying to find the balance between 
// useabilty, performance and RAM usage.
// It's difficult to balance all three, so I am trying find a situation where
// disk transfer isn't so bad because of the buffer size, while command length
// argument length aren't so short that someone with lots of long file names and
// folder names can't do what they want to do.
// As well, I want enough aliases to be useful, while the length isn't so short 
// that you can't do certain longer commands.
// The hotleys have to support all 8 function keys to be useful, so you can't
// limit how many there are. However, you can limit their length as well, 
// but if it's too short, then you can barely so anythign useful.
// If I had to chose, I'd rather have a shorter alias than a shorter hotkey
// length. Using an alias is probably going to be simply making a shortcut for
// and existing command. Like alias l "list -s". Whereas, since a hotkey is like
// an executing macro of sorts, you need it to be long enough to take a longer
// parameter. For example: hotkey 7 "view-mem 56296 56303" if useful because we
// might want to view that chunk of memory easily and repeatedly because the
// that chunk of memory is constantly chaging.
// So overall, as I optimize other parts of the program, I can come back here 
// and trim out some room for either temporarily adding some debugging, or 
// because I need to make room for a new feature. Although that's now pretty
// tight as it is, and an overall overhaul is probably required to get more
// features packed into a C Programming based 8-bit 6502 based program.

// ************
// CURRENT VALUES
// ************
/*-------------16--20---25---30--------40--------50---55---60------------------80--------------------*/
#define MAX_COMMODORE_DOS_FILENAME 16 // Commodore DOS maximum length of filenames is 16 characters
#define MAX_ENTERED_KEYSTROKES 70     // Commodore 40 column machines let you input a max line length of 80 characters
#define MAX_LENGTH_COMMAND 70 	      // Commodore DOS maximum length of filenames is 16 characters, but we also want quotes around the string, so we add two characters for that // fuck it make it 40 
#define MAX_LENGTH_ARGS 40 		      // Commodore DOS maximum length of command string is 40 characters
/*-------------16--20---25---30--------40--------50---55---60------------------80--------------------*/
#define MAX_DISK_SECTOR_BUFFER 255    // This is the size of the buffer used when transfering data over the UIEC bus.
#define MAX_ALIASES 8    		      // This is the number of slots available for setting aliases. This takes up a lot of RAM!
#define MAX_ALIAS_LENGTH 35  	      // This is the number of characters in length any alias can be. This also takes up a lot of RAM!
#define MAX_HOTKEYS 8  			      // This is the number of slots available for setting hotkeys. You can't really change this without disabling certain function keys. This takes up a lot of RAM!
#define MAX_HOTKEY_LENGTH 35	      // This is the number of characters in length any hotkeys can be. This also takes up a lot of RAM!
/*-------------16--20---25---30--------40--------50---55---60------------------80--------------------*/
// 47
// // ****************************
// // LOWEST MEMORY SAVINGS VALUES
// // ****************************
// /*-------------16--20---25---30--------40--------50---55---60------------------80--------------------*/
// #define MAX_COMMODORE_DOS_FILENAME 16 // Commodore DOS maximum length of filenames is 16 characters
// #define MAX_ENTERED_KEYSTROKES 55     // Commodore 40 column machines let you input a max line length of 80 characters
// #define MAX_LENGTH_COMMAND 55 	      // Commodore DOS maximum length of filenames is 16 characters, but we also want quotes around the string, so we add two characters for that // fuck it make it 40 
// #define MAX_LENGTH_ARGS 25 		      // Commodore DOS maximum length of command string is 40 characters
// /*-------------16--20---25---30--------40--------50---55---60------------------80--------------------*/
// #define MAX_DISK_SECTOR_BUFFER 200    // This is the size of the buffer used when transfering data over the UIEC bus.
// #define MAX_ALIASES 6    		      // This is the number of slots available for setting aliases. This takes up a lot of RAM!
// #define MAX_ALIAS_LENGTH 25  	      // This is the number of characters in length any alias can be. This also takes up a lot of RAM!
// #define MAX_HOTKEYS 8  			      // This is the number of slots available for setting hotkeys. You can't really change this without disabling certain function keys. This takes up a lot of RAM!
// #define MAX_HOTKEY_LENGTH 25 	      // This is the number of characters in length any hotkeys can be. This also takes up a lot of RAM!
// /*-------------16--20---25---30--------40--------50---55---60------------------80--------------------*/





// #define CURSOR_CHARACTER 230 // This is the checkerboard character 
#define CURSOR_CHARACTER 223 // This is the checkerboard character 

#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 25

#define SCREEN_RIGHT_EDGE SCREEN_WIDTH-1
#define SCREEN_LEFT_EDGE 0
#define SCREEN_BOTTOM_EDGE SCREEN_HEIGHT-1
#define SCREEN_TOP_EDGE 0

// the following if for type-prg functionality 
#define first_header_byte  				0 
#define second_header_byte 				1
#define first_basic_line_address_byte   2
#define second_basic_line_address_byte  3
#define first_basic_line_number_byte    4
#define second_basic_line_number_byte   5
#define body_bytes         				6
#define end_of_line_byte   				7
#define end_of_prg_byte    				8

unsigned char they_are_sure(void);
unsigned char convert_char(unsigned char char_to_convert) ;


// ********************************************************************************
// MACRO HELPER FUNCTIONS
// ********************************************************************************

// LOGIC HELPERS FUNCTIONS ********************************************************

#define true 1
#define TRUE 1
#define True 1
#define false 0
#define FALSE 0
#define False 0

// LOOP HELPERS FUNCTIONS ********************************************************

#define LOOP while(TRUE)
#define loop while(TRUE)

// MEMORY HELPERS FUNCTIONS *******************************************************

#define read_nibble_low(address) PEEK(address) & 0x0F



		// write - nibble1 and nibble2 are what gets written
		// char byte;
		// byte = (byte & 0xF0) | (nibble1 & 0xF); // write low quartet
		// byte = (byte & 0x0F) | ((nibble2 & 0xF) << 4); // write high quartet

		// read - input_b() is what gets read, and then the nibble is written to X and Y and Z 
		// X = input_b() & 0x0F; / bits 0 to 3
		// Y = input_b() >> 4; // bits 4 to 7
		// Z = (input_b() & 0x3C) >> 2; // bits 2 to 5 

// #define write_memory(address,val) (*(unsigned char*) (address) = (val)) // write_memory(0xD800, 0x12); // stores 0x12 at address 0xd800, useful for hardware registers
// #define read_memory(address)      (*(unsigned char*) (address))         // B = read_memory(0xD800);    // read a value from address 0xd800, into B, which should be a char palettes
// PEEK(0xD800) & 0x0F;

// In the jump table, no expressions are supported. The array index used in the goto must be a simple variable or a constant.
// Binary literals, a C++14 feature and a GCC C extension, are accepted. They can be disabled with the --standard option.

//             unsigned char foo = 0b101; // sets it to 5
            
// #define get_bit(data,y)   ( (data>>y) & 1 ) // Return Data.Y value - // uint8_t bit_2 = get_bit(number,2); // bit_2 = 1
// #define set_bit(data,y)   data |= (1 << y)  // Set Data.Y   to 1   - // set_bit(number,1); // number =  0x07 => 0b00000111 // bits are right to left so the right most bit is bit 0 
// #define clear_bit(data,y) data &= ~(1 << y) // Clear Data.Y to 0   - // clear_bit(number,2); // number =0x03 => 0b0000011
// #define bit_0 0
// #define bit_1 1
// #define bit_2 2
// #define bit_3 3
// #define bit_4 4
// #define bit_5 5
// #define bit_6 6
// #define bit_7 7

// #define write_memory(address,val) (*(unsigned char*) (address) = (val)) // write_memory(0xD800, 0x12); // stores 0x12 at address 0xd800, useful for hardware registers
// #define read_memory(address)      (*(unsigned char*) (address))         // B = read_memory(0xD800);    // read a value from address 0xd800, into B, which should be a char palettes






// ********************************************************************************
// MACRO FUNCTIONS
// ********************************************************************************

#define matching(testing_string,original_string) (strcmp(original_string,testing_string)==0)

#define display_title_text() printf("ChiCLI %s (c) 2021 Chiron Bramberger\n", VERSION)

#define display_description_text() printf("A CLI for Commodore Computers!\n")

#define wait_for_keypress() 			\
										\
	while(kbhit()) { /* flush buffer */	\
		cgetc();						\
	};/*end while*/						\
										\
	while(!kbhit()) {					\
		/*do nothing*/					\
	};/*end while*/ 					\
										\
//end macro func 


#define display_title_screen(has_ddd) \
	clrscr();					      \
	display_title_text();		      \
	sys_info(has_ddd);			      \
	pet_chirp();				      \
	puts("\nReady!");                 \
//end macro func 

// ********************************************************************************
// GENERAL FUNCTIONS
// ********************************************************************************

// void chi_gotox( signed int x_to_goto );  // these are debugging
// void chi_gotoy( signed int y_to_goto ); // these are debugging


// ********************************************************************************
// GENERIC PROMPTS FUNCTIONS 
// ********************************************************************************

// unsigned char they_are_sure(void);
// void hit_any_key(void); // this should be a MACRO function 







