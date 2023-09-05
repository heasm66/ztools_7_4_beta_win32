Comments on this version (7/4 beta) for win32
=============================================

* The original source is downloaded from https://gitlab.com/russotto/ztools on 2023-09-04
* There as things in showverbs.c that seems to be in an unfinished state and I had to comment:
     Line 254-271
     Line 583
     Line 585-752
* Using win32-getopt.c and win32-getopt-h instead of getopt.c and getopt.h
* Compiles with Visual Studio 2022
* Needs _CRT_SECURE_NO_WARNINGS added to C/C++\Preprocessor\Preprocessor Definitions to compile
* Compiles to x86 (not x64)
* check.exe give virus warning in Norton when run if compiled to Debug (but not Release)
* Changed version number to 7/4 beta for txd and infodump (check and pix2gif are unchanged and still in 7/2)
* Changes to opcodes (see https://intfiction.org/t/txd-and-ztools/54720):
	The EXT opcodes print_unicode and check_unicode are defined for version 5-8
	The EXT opcode set_true_colour are defined for version 6 and version 5, 7-8 (different definitions).
	The EXT opcode buffer_screen is defined for version 6.
	The 2OP opcode throw is also definied for version 5, 7-8 (only defined for version 6 earlier).
	The 0OP opcode restart is defined as a RETURN-type, instead as earlier as a PLAIN-type.
* Added check for quit and restart in txd.c..decode_operands that sets their type to PLAIN if next address
  is not a valid entrypoint for a routine.
  
txd.c
=====
line 711-
	switch ((unsigned int)header.version) {
	case V5:
	case V7:
	case V8:
	switch (code) {
		caseline (0x0B, "PRINT_UNICODE",   NUMBER,   NIL,      NIL,      NIL,      NONE,   PLAIN);   //new in z-spec 1.1
		caseline (0x0C, "CHECK_UNICODE",   NUMBER,   NIL,      NIL,      NIL,      STORE,  PLAIN);   //new in z-spec 1.1
		caseline (0x0D, "SET_TRUE_COLOUR", NUMBER,   NUMBER,   NIL,      NIL,      NONE,   PLAIN);   //new in z-spec 1.1
	}
	case V6:
	switch (code) {
		caseline (0x0B, "PRINT_UNICODE",   NUMBER,   NIL,      NIL,      NIL,      NONE,   PLAIN);   //new in z-spec 1.1
		caseline (0x0C, "CHECK_UNICODE",   NUMBER,   NIL,      NIL,      NIL,      STORE,  PLAIN);   //new in z-spec 1.1
		caseline (0x0D, "SET_TRUE_COLOUR", NUMBER,   NUMBER,   NUMBER,   NIL,      NONE,   PLAIN);   //new in z-spec 1.1
		caseline (0x1D, "BUFFER_SCREEN",   LOW_ADDR, NIL,      NIL,      NIL,      NONE,   PLAIN);   //new in z-spec 1.1
	}
	}
		
line 802
	caseline (0x1C, "THROW",           ANYTHING, NUMBER,   NIL,      NIL,      NONE,   PLAIN);

line 921
	caseline (0x07, "RESTART",         NIL,      NIL,      NIL,      NIL,      NONE,   RETURN); // this should also be a RETURN-type

line 1092-
	if (!decode.first_pass) {
		if (opcode.opcode == 0xBA || opcode.opcode == 0xB7) {
			// QUIT or RESTART (should this be expanded to other RETURN-types?)
			// These are considered as RETURN-type if the next opcode is illegal, otherwise they are PLAIN.
			// If the next address is a valid routine start, it is also considered as RETURN.
			if
				((decode.pc - (unsigned long)story_scaler * header.strings_offset) % (decode.pc * code_scaler) == 0 && read_data_byte(decode.pc + 1) < 16) {
				// Valid entrypoint for routine, keep type as RETURN
				opcode.type = RETURN;
			}
			else {
				// TODO: Check if next byte is a bad opcode; if it is, don't set type to PLAIN
				opcode.type = PLAIN;
			}
		}
	}
