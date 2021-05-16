#include "sans16B_PL.h"

const uint8_t FontRSans16B_PL_Bitmap[] = {
	// @0 ' ' (2 pixels wide)
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //

	// @4 '!' (2 pixels wide)
	0b00010111, 0b11111000, //    # ########
	0b00010111, 0b11111000, //    # ########

	// @8 '"' (4 pixels wide)
	0b00000000, 0b01111000, //          ####
	0b00000000, 0b01111000, //          ####
	0b00000000, 0b01111000, //          ####
	0b00000000, 0b01111000, //          ####

	// @16 '#' (8 pixels wide)
	0b00000010, 0b00000000, //       #
	0b00011110, 0b01000000, //    ####  #
	0b00011111, 0b11000000, //    #######
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00000011, 0b11111000, //       #######
	0b00000010, 0b01111000, //       #  ####
	0b00000000, 0b01000000, //          #

	// @32 '$' (6 pixels wide)
	0b00001000, 0b11100000, //     #   ###
	0b00011001, 0b11110000, //    ##  #####
	0b00111111, 0b11111000, //   ###########
	0b00111111, 0b11111000, //   ###########
	0b00011111, 0b01110000, //    ##### ###
	0b00001110, 0b01100000, //     ###  ##

	// @44 '%' (11 pixels wide)
	0b00000000, 0b00110000, //           ##
	0b00001000, 0b01111000, //     #    ####
	0b00001100, 0b01001000, //     ##   #  #
	0b00000110, 0b01111000, //      ##  ####
	0b00000011, 0b00110000, //       ##  ##
	0b00000001, 0b10000000, //        ##
	0b00001100, 0b11000000, //     ##  ##
	0b00011110, 0b01100000, //    ####  ##
	0b00010010, 0b00110000, //    #  #   ##
	0b00011110, 0b00010000, //    ####    #
	0b00001100, 0b00000000, //     ##

	// @66 '&' (8 pixels wide)
	0b00001110, 0b00000000, //     ###
	0b00011111, 0b01110000, //    ##### ###
	0b00010001, 0b11111000, //    #   ######
	0b00010001, 0b10001000, //    #   ##   #
	0b00010111, 0b11111000, //    # ########
	0b00011110, 0b01110000, //    ####  ###
	0b00011100, 0b00000000, //    ###
	0b00010100, 0b00000000, //    # #

	// @82 ''' (2 pixels wide)
	0b00000000, 0b01111000, //          ####
	0b00000000, 0b01111000, //          ####

	// @86 '(' (4 pixels wide)
	0b00011111, 0b11000000, //    #######
	0b01111111, 0b11110000, //  ###########
	0b11100000, 0b00111000, // ###       ###
	0b10000000, 0b00001000, // #           #

	// @94 ')' (4 pixels wide)
	0b10000000, 0b00001000, // #           #
	0b11100000, 0b00111000, // ###       ###
	0b01111111, 0b11110000, //  ###########
	0b00011111, 0b11000000, //    #######

	// @102 '*' (6 pixels wide)
	0b00000000, 0b01010000, //          # #
	0b00000000, 0b01110000, //          ###
	0b00000000, 0b01111000, //          ####
	0b00000000, 0b01111000, //          ####
	0b00000000, 0b01110000, //          ###
	0b00000000, 0b01010000, //          # #

	// @114 '+' (6 pixels wide)
	0b00000001, 0b00000000, //        #
	0b00000001, 0b00000000, //        #
	0b00000111, 0b11000000, //      #####
	0b00000111, 0b11000000, //      #####
	0b00000001, 0b00000000, //        #
	0b00000001, 0b00000000, //        #

	// @126 ',' (3 pixels wide)
	0b00100000, 0b00000000, //   #
	0b00110000, 0b00000000, //   ##
	0b00010000, 0b00000000, //    #

	// @132 '-' (5 pixels wide)
	0b00000001, 0b00000000, //        #
	0b00000001, 0b00000000, //        #
	0b00000001, 0b00000000, //        #
	0b00000001, 0b00000000, //        #
	0b00000001, 0b00000000, //        #

	// @142 '.' (2 pixels wide)
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #

	// @146 '/' (5 pixels wide)
	0b01110000, 0b00000000, //  ###
	0b01111110, 0b00000000, //  ######
	0b00001111, 0b11000000, //     ######
	0b00000001, 0b11111000, //        ######
	0b00000000, 0b00111000, //           ###

	// @156 '0' (6 pixels wide)
	0b00001111, 0b11110000, //     ########
	0b00011111, 0b11111000, //    ##########
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00011111, 0b11111000, //    ##########
	0b00001111, 0b11110000, //     ########

	// @168 '1' (4 pixels wide)
	0b00000000, 0b00010000, //            #
	0b00000000, 0b00010000, //            #
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########

	// @176 '2' (6 pixels wide)
	0b00011100, 0b00110000, //    ###    ##
	0b00011110, 0b00111000, //    ####   ###
	0b00010011, 0b00001000, //    #  ##    #
	0b00010001, 0b10001000, //    #   ##   #
	0b00010000, 0b11111000, //    #    #####
	0b00010000, 0b01110000, //    #     ###

	// @188 '3' (6 pixels wide)
	0b00001000, 0b00010000, //     #      #
	0b00011000, 0b00011000, //    ##      ##
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00011111, 0b11111000, //    ##########
	0b00001111, 0b01110000, //     #### ###

	// @200 '4' (6 pixels wide)
	0b00000011, 0b00000000, //       ##
	0b00000011, 0b10000000, //       ###
	0b00000010, 0b11100000, //       # ###
	0b00000010, 0b01110000, //       #  ###
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########

	// @212 '5' (6 pixels wide)
	0b00001001, 0b11111000, //     #  ######
	0b00011001, 0b11111000, //    ##  ######
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00011111, 0b10001000, //    ######   #
	0b00001111, 0b00001000, //     ####    #

	// @224 '6' (6 pixels wide)
	0b00001111, 0b11110000, //     ########
	0b00011111, 0b11111000, //    ##########
	0b00010001, 0b10001000, //    #   ##   #
	0b00010000, 0b10001000, //    #    #   #
	0b00011111, 0b10011000, //    ######  ##
	0b00001111, 0b00010000, //     ####   #

	// @236 '7' (6 pixels wide)
	0b00000000, 0b00001000, //             #
	0b00011100, 0b00001000, //    ###      #
	0b00011111, 0b00001000, //    #####    #
	0b00000011, 0b11001000, //       ####  #
	0b00000000, 0b11111000, //         #####
	0b00000000, 0b00111000, //           ###

	// @248 '8' (6 pixels wide)
	0b00001111, 0b01110000, //     #### ###
	0b00011111, 0b11111000, //    ##########
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00011111, 0b11111000, //    ##########
	0b00001111, 0b01110000, //     #### ###

	// @260 '9' (6 pixels wide)
	0b00001000, 0b11110000, //     #   ####
	0b00011001, 0b11111000, //    ##  ######
	0b00010001, 0b00001000, //    #   #    #
	0b00010001, 0b10001000, //    #   ##   #
	0b00011111, 0b11111000, //    ##########
	0b00001111, 0b11110000, //     ########

	// @272 ':' (2 pixels wide)
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #

	// @276 ';' (3 pixels wide)
	0b00100000, 0b00000000, //   #
	0b00110000, 0b01000000, //   ##     #
	0b00010000, 0b01000000, //    #     #

	// @282 '<' (6 pixels wide)
	0b00000001, 0b00000000, //        #
	0b00000011, 0b10000000, //       ###
	0b00000111, 0b11000000, //      #####
	0b00001110, 0b11100000, //     ### ###
	0b00001100, 0b01100000, //     ##   ##
	0b00001000, 0b00100000, //     #     #

	// @294 '=' (6 pixels wide)
	0b00000010, 0b10000000, //       # #
	0b00000010, 0b10000000, //       # #
	0b00000010, 0b10000000, //       # #
	0b00000010, 0b10000000, //       # #
	0b00000010, 0b10000000, //       # #
	0b00000010, 0b10000000, //       # #

	// @306 '>' (6 pixels wide)
	0b00001000, 0b00100000, //     #     #
	0b00001100, 0b01100000, //     ##   ##
	0b00001110, 0b11100000, //     ### ###
	0b00000111, 0b11000000, //      #####
	0b00000011, 0b10000000, //       ###
	0b00000001, 0b00000000, //        #

	// @318 '?' (6 pixels wide)
	0b00000000, 0b00110000, //           ##
	0b00000000, 0b00111000, //           ###
	0b00010111, 0b00001000, //    # ###    #
	0b00010111, 0b10001000, //    # ####   #
	0b00000000, 0b11111000, //         #####
	0b00000000, 0b01110000, //          ###

	// @330 '@' (13 pixels wide)
	0b00000011, 0b11000000, //       ####
	0b00001111, 0b11110000, //     ########
	0b00011100, 0b00111000, //    ###    ###
	0b00010000, 0b00001000, //    #        #
	0b00110011, 0b10001100, //   ##  ###   ##
	0b00100111, 0b11000100, //   #  #####   #
	0b00100100, 0b01000100, //   #  #   #   #
	0b00100110, 0b01000100, //   #  ##  #   #
	0b00100111, 0b11001100, //   #  #####  ##
	0b00110101, 0b11001000, //   ## # ###  #
	0b00010100, 0b00111000, //    # #    ###
	0b00010111, 0b11110000, //    # #######
	0b00000011, 0b11000000, //       ####

	// @356 'A' (10 pixels wide)
	0b00011000, 0b00000000, //    ##
	0b00011110, 0b00000000, //    ####
	0b00000111, 0b10000000, //      ####
	0b00000011, 0b11100000, //       #####
	0b00000010, 0b01111000, //       #  ####
	0b00000010, 0b01111000, //       #  ####
	0b00000011, 0b11100000, //       #####
	0b00000111, 0b10000000, //      ####
	0b00011110, 0b00000000, //    ####
	0b00011000, 0b00000000, //    ##

	// @376 'B' (8 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00011111, 0b11111000, //    ##########
	0b00001111, 0b01110000, //     #### ###

	// @392 'C' (9 pixels wide)
	0b00000111, 0b11100000, //      ######
	0b00001111, 0b11110000, //     ########
	0b00011000, 0b00011000, //    ##      ##
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00011000, 0b00011000, //    ##      ##
	0b00001100, 0b00110000, //     ##    ##
	0b00000100, 0b00100000, //      #    #

	// @410 'D' (9 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00011000, 0b00011000, //    ##      ##
	0b00001111, 0b11110000, //     ########
	0b00000111, 0b11100000, //      ######

	// @428 'E' (8 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b00001000, //    #        #

	// @444 'F' (8 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00000000, 0b10001000, //         #   #
	0b00000000, 0b10001000, //         #   #
	0b00000000, 0b10001000, //         #   #
	0b00000000, 0b10001000, //         #   #
	0b00000000, 0b10001000, //         #   #
	0b00000000, 0b00001000, //             #

	// @460 'G' (9 pixels wide)
	0b00000111, 0b11100000, //      ######
	0b00001111, 0b11110000, //     ########
	0b00011000, 0b00011000, //    ##      ##
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00010001, 0b00001000, //    #   #    #
	0b00011001, 0b00011000, //    ##  #   ##
	0b00011111, 0b00110000, //    #####  ##
	0b00011111, 0b00100000, //    #####  #

	// @478 'H' (9 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00000000, 0b10000000, //         #
	0b00000000, 0b10000000, //         #
	0b00000000, 0b10000000, //         #
	0b00000000, 0b10000000, //         #
	0b00000000, 0b10000000, //         #
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########

	// @496 'I' (2 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########

	// @500 'J' (6 pixels wide)
	0b00001100, 0b00000000, //     ##
	0b00011100, 0b00000000, //    ###
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #
	0b00011111, 0b11111000, //    ##########
	0b00001111, 0b11111000, //     #########

	// @512 'K' (8 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00000001, 0b11000000, //        ###
	0b00000011, 0b01100000, //       ## ##
	0b00000110, 0b00110000, //      ##   ##
	0b00001100, 0b00011000, //     ##     ##
	0b00011000, 0b00001000, //    ##       #
	0b00010000, 0b00000000, //    #

	// @528 'L' (7 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #

	// @542 'M' (10 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00000001, 0b11100000, //        ####
	0b00000111, 0b10000000, //      ####
	0b00011110, 0b00000000, //    ####
	0b00011110, 0b00000000, //    ####
	0b00000111, 0b10000000, //      ####
	0b00000001, 0b11100000, //        ####
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########

	// @562 'N' (9 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00000000, 0b01110000, //          ###
	0b00000000, 0b11100000, //         ###
	0b00000001, 0b10000000, //        ##
	0b00000111, 0b00000000, //      ###
	0b00001110, 0b00000000, //     ###
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########

	// @580 'O' (9 pixels wide)
	0b00000111, 0b11100000, //      ######
	0b00001111, 0b11110000, //     ########
	0b00011000, 0b00011000, //    ##      ##
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00011000, 0b00011000, //    ##      ##
	0b00001111, 0b11110000, //     ########
	0b00000111, 0b11100000, //      ######

	// @598 'P' (9 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00000001, 0b00001000, //        #    #
	0b00000001, 0b00001000, //        #    #
	0b00000001, 0b00001000, //        #    #
	0b00000001, 0b00001000, //        #    #
	0b00000001, 0b10011000, //        ##  ##
	0b00000000, 0b11110000, //         ####
	0b00000000, 0b01100000, //          ##

	// @616 'Q' (9 pixels wide)
	0b00000111, 0b11100000, //      ######
	0b00001111, 0b11110000, //     ########
	0b00011000, 0b00011000, //    ##      ##
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00010100, 0b00001000, //    # #      #
	0b00011100, 0b00011000, //    ###     ##
	0b00011111, 0b11110000, //    #########
	0b00010111, 0b11100000, //    # ######

	// @634 'R' (10 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00000001, 0b00001000, //        #    #
	0b00000001, 0b00001000, //        #    #
	0b00000001, 0b00001000, //        #    #
	0b00000001, 0b00001000, //        #    #
	0b00000001, 0b10011000, //        ##  ##
	0b00001111, 0b11110000, //     ########
	0b00011110, 0b01100000, //    ####  ##
	0b00010000, 0b00000000, //    #

	// @654 'S' (8 pixels wide)
	0b00001100, 0b01110000, //     ##   ###
	0b00011100, 0b11111000, //    ###  #####
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010001, 0b10001000, //    #   ##   #
	0b00010001, 0b00001000, //    #   #    #
	0b00011111, 0b00111000, //    #####  ###
	0b00001110, 0b00110000, //     ###   ##

	// @670 'T' (10 pixels wide)
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00001000, //             #
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00001000, //             #

	// @690 'U' (9 pixels wide)
	0b00000111, 0b11111000, //      ########
	0b00001111, 0b11111000, //     #########
	0b00011000, 0b00000000, //    ##
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #
	0b00011000, 0b00000000, //    ##
	0b00001111, 0b11111000, //     #########
	0b00000111, 0b11111000, //      ########

	// @708 'V' (10 pixels wide)
	0b00000000, 0b00011000, //            ##
	0b00000000, 0b01111000, //          ####
	0b00000001, 0b11100000, //        ####
	0b00000111, 0b10000000, //      ####
	0b00011110, 0b00000000, //    ####
	0b00011110, 0b00000000, //    ####
	0b00000111, 0b10000000, //      ####
	0b00000001, 0b11100000, //        ####
	0b00000000, 0b01111000, //          ####
	0b00000000, 0b00011000, //            ##

	// @728 'W' (14 pixels wide)
	0b00000000, 0b00111000, //           ###
	0b00000000, 0b11111000, //         #####
	0b00000111, 0b11000000, //      #####
	0b00011111, 0b00000000, //    #####
	0b00011111, 0b00000000, //    #####
	0b00000111, 0b11000000, //      #####
	0b00000000, 0b11111000, //         #####
	0b00000000, 0b11111000, //         #####
	0b00000111, 0b11000000, //      #####
	0b00011111, 0b00000000, //    #####
	0b00011111, 0b00000000, //    #####
	0b00000111, 0b11000000, //      #####
	0b00000000, 0b11111000, //         #####
	0b00000000, 0b00111000, //           ###

	// @756 'X' (9 pixels wide)
	0b00011000, 0b00011000, //    ##      ##
	0b00011100, 0b00111000, //    ###    ###
	0b00000110, 0b01100000, //      ##  ##
	0b00000011, 0b11000000, //       ####
	0b00000001, 0b10000000, //        ##
	0b00000011, 0b11000000, //       ####
	0b00000110, 0b01100000, //      ##  ##
	0b00011100, 0b00111000, //    ###    ###
	0b00011000, 0b00011000, //    ##      ##

	// @774 'Y' (10 pixels wide)
	0b00000000, 0b00011000, //            ##
	0b00000000, 0b00111000, //           ###
	0b00000000, 0b01100000, //          ##
	0b00000000, 0b11000000, //         ##
	0b00011111, 0b10000000, //    ######
	0b00011111, 0b10000000, //    ######
	0b00000000, 0b11000000, //         ##
	0b00000000, 0b01100000, //          ##
	0b00000000, 0b00111000, //           ###
	0b00000000, 0b00011000, //            ##

	// @794 'Z' (7 pixels wide)
	0b00011000, 0b00001000, //    ##       #
	0b00011110, 0b00001000, //    ####     #
	0b00010111, 0b00001000, //    # ###    #
	0b00010001, 0b10001000, //    #   ##   #
	0b00010000, 0b11101000, //    #    ### #
	0b00010000, 0b01111000, //    #     ####
	0b00010000, 0b00011000, //    #       ##

	// @808 '[' (4 pixels wide)
	0b11111111, 0b11111000, // #############
	0b11111111, 0b11111000, // #############
	0b10000000, 0b00001000, // #           #
	0b10000000, 0b00001000, // #           #

	// @816 '\' (5 pixels wide)
	0b00000000, 0b00111000, //           ###
	0b00000001, 0b11111000, //        ######
	0b00001111, 0b11000000, //     ######
	0b01111110, 0b00000000, //  ######
	0b01110000, 0b00000000, //  ###

	// @826 ']' (4 pixels wide)
	0b10000000, 0b00001000, // #           #
	0b10000000, 0b00001000, // #           #
	0b11111111, 0b11111000, // #############
	0b11111111, 0b11111000, // #############

	// @834 '^' (6 pixels wide)
	0b00000000, 0b00010000, //            #
	0b00000000, 0b00011000, //            ##
	0b00000000, 0b00001100, //             ##
	0b00000000, 0b00001100, //             ##
	0b00000000, 0b00011000, //            ##
	0b00000000, 0b00010000, //            #

	// @846 '_' (8 pixels wide)
	0b01000000, 0b00000000, //  #
	0b01000000, 0b00000000, //  #
	0b01000000, 0b00000000, //  #
	0b01000000, 0b00000000, //  #
	0b01000000, 0b00000000, //  #
	0b01000000, 0b00000000, //  #
	0b01000000, 0b00000000, //  #
	0b01000000, 0b00000000, //  #

	// @862 '`' (3 pixels wide)
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00011000, //            ##
	0b00000000, 0b00010000, //            #

	// @868 'a' (8 pixels wide)
	0b00001110, 0b10000000, //     ### #
	0b00011111, 0b11000000, //    #######
	0b00010001, 0b01000000, //    #   # #
	0b00010001, 0b01000000, //    #   # #
	0b00010001, 0b01000000, //    #   # #
	0b00011111, 0b11000000, //    #######
	0b00011111, 0b10000000, //    ######
	0b00010000, 0b00000000, //    #

	// @884 'b' (7 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00011000, 0b11000000, //    ##   ##
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00011111, 0b11000000, //    #######
	0b00001111, 0b10000000, //     #####

	// @898 'c' (7 pixels wide)
	0b00001111, 0b10000000, //     #####
	0b00011111, 0b11000000, //    #######
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00011000, 0b11000000, //    ##   ##
	0b00001000, 0b10000000, //     #   #

	// @912 'd' (7 pixels wide)
	0b00001111, 0b10000000, //     #####
	0b00011111, 0b11000000, //    #######
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00011000, 0b11000000, //    ##   ##
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########

	// @926 'e' (7 pixels wide)
	0b00001111, 0b10000000, //     #####
	0b00011111, 0b11000000, //    #######
	0b00010010, 0b01000000, //    #  #  #
	0b00010010, 0b01000000, //    #  #  #
	0b00010010, 0b01000000, //    #  #  #
	0b00011011, 0b11000000, //    ## ####
	0b00001011, 0b10000000, //     # ###

	// @940 'f' (4 pixels wide)
	0b00000000, 0b01000000, //          #
	0b00011111, 0b11110000, //    #########
	0b00011111, 0b11111000, //    ##########
	0b00000000, 0b01001000, //          #  #

	// @948 'g' (7 pixels wide)
	0b00001111, 0b10000000, //     #####
	0b10011111, 0b11000000, // #  #######
	0b10010000, 0b01000000, // #  #     #
	0b10010000, 0b01000000, // #  #     #
	0b10011000, 0b11000000, // #  ##   ##
	0b11111111, 0b11000000, // ##########
	0b01111111, 0b11000000, //  #########

	// @962 'h' (6 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00000000, 0b11000000, //         ##
	0b00000000, 0b01000000, //          #
	0b00011111, 0b11000000, //    #######
	0b00011111, 0b10000000, //    ######

	// @974 'i' (2 pixels wide)
	0b00011111, 0b11001000, //    #######  #
	0b00011111, 0b11001000, //    #######  #

	// @978 'j' (3 pixels wide)
	0b10000000, 0b00000000, // #
	0b11111111, 0b11001000, // ##########  #
	0b01111111, 0b11001000, //  #########  #

	// @984 'k' (7 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00000011, 0b00000000, //       ##
	0b00000111, 0b10000000, //      ####
	0b00001100, 0b11000000, //     ##  ##
	0b00011000, 0b01000000, //    ##    #
	0b00010000, 0b00000000, //    #

	// @998 'l' (2 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########

	// @1002 'm' (10 pixels wide)
	0b00011111, 0b11000000, //    #######
	0b00011111, 0b11000000, //    #######
	0b00000000, 0b11000000, //         ##
	0b00000000, 0b01000000, //          #
	0b00011111, 0b11000000, //    #######
	0b00011111, 0b10000000, //    ######
	0b00000000, 0b11000000, //         ##
	0b00000000, 0b01000000, //          #
	0b00011111, 0b11000000, //    #######
	0b00011111, 0b10000000, //    ######

	// @1022 'n' (6 pixels wide)
	0b00011111, 0b11000000, //    #######
	0b00011111, 0b11000000, //    #######
	0b00000000, 0b11000000, //         ##
	0b00000000, 0b01000000, //          #
	0b00011111, 0b11000000, //    #######
	0b00011111, 0b10000000, //    ######

	// @1034 'o' (7 pixels wide)
	0b00001111, 0b10000000, //     #####
	0b00011111, 0b11000000, //    #######
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00011111, 0b11000000, //    #######
	0b00001111, 0b10000000, //     #####

	// @1048 'p' (7 pixels wide)
	0b11111111, 0b11000000, // ##########
	0b11111111, 0b11000000, // ##########
	0b00011000, 0b11000000, //    ##   ##
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00011111, 0b11000000, //    #######
	0b00001111, 0b10000000, //     #####

	// @1062 'q' (7 pixels wide)
	0b00001111, 0b10000000, //     #####
	0b00011111, 0b11000000, //    #######
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00011000, 0b11000000, //    ##   ##
	0b11111111, 0b11000000, // ##########
	0b11111111, 0b11000000, // ##########

	// @1076 'r' (4 pixels wide)
	0b00011111, 0b11000000, //    #######
	0b00011111, 0b11000000, //    #######
	0b00000000, 0b11000000, //         ##
	0b00000000, 0b01000000, //          #

	// @1084 's' (6 pixels wide)
	0b00001001, 0b10000000, //     #  ##
	0b00011011, 0b11000000, //    ## ####
	0b00010010, 0b01000000, //    #  #  #
	0b00010010, 0b01000000, //    #  #  #
	0b00011110, 0b11000000, //    #### ##
	0b00001100, 0b10000000, //     ##  #

	// @1096 't' (4 pixels wide)
	0b00000000, 0b01000000, //          #
	0b00001111, 0b11110000, //     ########
	0b00011111, 0b11110000, //    #########
	0b00010000, 0b01000000, //    #     #

	// @1104 'u' (6 pixels wide)
	0b00001111, 0b11000000, //     ######
	0b00011111, 0b11000000, //    #######
	0b00010000, 0b00000000, //    #
	0b00011000, 0b00000000, //    ##
	0b00011111, 0b11000000, //    #######
	0b00011111, 0b11000000, //    #######

	// @1116 'v' (8 pixels wide)
	0b00000000, 0b11000000, //         ##
	0b00000011, 0b11000000, //       ####
	0b00001111, 0b00000000, //     ####
	0b00011100, 0b00000000, //    ###
	0b00011100, 0b00000000, //    ###
	0b00001111, 0b00000000, //     ####
	0b00000011, 0b11000000, //       ####
	0b00000000, 0b11000000, //         ##

	// @1132 'w' (10 pixels wide)
	0b00000000, 0b11000000, //         ##
	0b00000111, 0b11000000, //      #####
	0b00011111, 0b00000000, //    #####
	0b00011111, 0b00000000, //    #####
	0b00000111, 0b11000000, //      #####
	0b00000111, 0b11000000, //      #####
	0b00011111, 0b00000000, //    #####
	0b00011111, 0b00000000, //    #####
	0b00000111, 0b11000000, //      #####
	0b00000000, 0b11000000, //         ##

	// @1152 'x' (7 pixels wide)
	0b00010000, 0b01000000, //    #     #
	0b00011000, 0b11000000, //    ##   ##
	0b00001111, 0b10000000, //     #####
	0b00000111, 0b00000000, //      ###
	0b00001111, 0b10000000, //     #####
	0b00011000, 0b11000000, //    ##   ##
	0b00010000, 0b01000000, //    #     #

	// @1166 'y' (8 pixels wide)
	0b10000000, 0b11000000, // #       ##
	0b10000011, 0b11000000, // #     ####
	0b11001111, 0b00000000, // ##  ####
	0b01111100, 0b00000000, //  #####
	0b00111100, 0b00000000, //   ####
	0b00001111, 0b00000000, //     ####
	0b00000011, 0b11000000, //       ####
	0b00000000, 0b11000000, //         ##

	// @1182 'z' (5 pixels wide)
	0b00011000, 0b01000000, //    ##    #
	0b00011110, 0b01000000, //    ####  #
	0b00010111, 0b01000000, //    # ### #
	0b00010001, 0b11000000, //    #   ###
	0b00010000, 0b11000000, //    #    ##

	// @1192 '{' (6 pixels wide)
	0b00000010, 0b00000000, //       #
	0b00000010, 0b00000000, //       #
	0b01111111, 0b11110000, //  ###########
	0b11111101, 0b11111000, // ###### ######
	0b10000000, 0b00001000, // #           #
	0b10000000, 0b00001000, // #           #

	// @1204 '|' (2 pixels wide)
	0b11111111, 0b11111000, // #############
	0b11111111, 0b11111000, // #############

	// @1208 '}' (6 pixels wide)
	0b10000000, 0b00001000, // #           #
	0b10000000, 0b00001000, // #           #
	0b11111101, 0b11111000, // ###### ######
	0b01111111, 0b11110000, //  ###########
	0b00000010, 0b00000000, //       #
	0b00000010, 0b00000000, //       #

	// @1220 '~' (8 pixels wide)
	0b00000000, 0b00110000, //           ##
	0b00000000, 0b00111000, //           ###
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00011000, //            ##
	0b00000000, 0b00110000, //           ##
	0b00000000, 0b00100000, //           #
	0b00000000, 0b00111000, //           ###
	0b00000000, 0b00011000, //            ##

	// @1236 '�' (9 pixels wide)
	0b00000111, 0b11100000, //      ######
	0b00001111, 0b11110000, //     ########
	0b00011000, 0b00011000, //    ##      ##
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001100, //    #        ##
	0b00010000, 0b00001110, //    #        ###
	0b00011000, 0b00011010, //    ##      ## #
	0b00001111, 0b11110000, //     ########
	0b00000111, 0b11100000, //      ######

	// @1254 '�' (7 pixels wide)
	0b00001111, 0b10000000, //     #####
	0b00011111, 0b11000000, //    #######
	0b00010000, 0b01010000, //    #     # #
	0b00010000, 0b01011000, //    #     # ##
	0b00010000, 0b01001000, //    #     #  #
	0b00011111, 0b11000000, //    #######
	0b00001111, 0b10000000, //     #####

	// @1268 '�' (10 pixels wide)
	0b00011000, 0b00000000, //    ##
	0b00011110, 0b00000000, //    ####
	0b00000111, 0b10000000, //      ####
	0b00000011, 0b11100000, //       #####
	0b00000010, 0b01111000, //       #  ####
	0b00000010, 0b01111000, //       #  ####
	0b01000011, 0b11100000, //  #    #####
	0b11100111, 0b10000000, // ###  ####
	0b10111110, 0b00000000, // # #####
	0b10011000, 0b00000000, // #  ##

	// @1288 '�' (8 pixels wide)
	0b00001110, 0b10000000, //     ### #
	0b00011111, 0b11000000, //    #######
	0b00010001, 0b01000000, //    #   # #
	0b00010001, 0b01000000, //    #   # #
	0b01010001, 0b01000000, //  # #   # #
	0b11111111, 0b11000000, // ##########
	0b10111111, 0b10000000, // # #######
	0b10010000, 0b00000000, // #  #

	// @1304 '�' (9 pixels wide)
	0b00000111, 0b11100000, //      ######
	0b00001111, 0b11110000, //     ########
	0b00011000, 0b00011000, //    ##      ##
	0b00010000, 0b00001100, //    #        ##
	0b00010000, 0b00001110, //    #        ###
	0b00010000, 0b00001010, //    #        # #
	0b00011000, 0b00011000, //    ##      ##
	0b00001100, 0b00110000, //     ##    ##
	0b00000100, 0b00100000, //      #    #

	// @1322 '�' (7 pixels wide)
	0b00001111, 0b10000000, //     #####
	0b00011111, 0b11000000, //    #######
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01010000, //    #     # #
	0b00010000, 0b01011000, //    #     # ##
	0b00011000, 0b11001000, //    ##   ##  #
	0b00001000, 0b10000000, //     #   #

	// @1336 '�' (8 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b01010000, 0b10001000, //  # #    #   #
	0b11110000, 0b10001000, // ####    #   #
	0b10110000, 0b10001000, // # ##    #   #
	0b10010000, 0b10001000, // #  #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b00001000, //    #        #

	// @1352 '�' (7 pixels wide)
	0b00001111, 0b10000000, //     #####
	0b01011111, 0b11000000, //  # #######
	0b11110010, 0b01000000, // ####  #  #
	0b10110010, 0b01000000, // # ##  #  #
	0b10010010, 0b01000000, // #  #  #  #
	0b00011011, 0b11000000, //    ## ####
	0b00001011, 0b10000000, //     # ###

	// @1366 '�' (8 pixels wide)
	0b00000010, 0b00000000, //       #
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00010000, 0b11000000, //    #    ##
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #

	// @1382 '�' (5 pixels wide)
	0b00000010, 0b00000000, //       #
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00000000, 0b11000000, //         ##
	0b00000000, 0b01000000, //          #

	// @1392 '�' (9 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########
	0b00000000, 0b01110000, //          ###
	0b00000000, 0b11100100, //         ###  #
	0b00000001, 0b10000110, //        ##    ##
	0b00000111, 0b00000010, //      ###      #
	0b00001110, 0b00000000, //     ###
	0b00011111, 0b11111000, //    ##########
	0b00011111, 0b11111000, //    ##########

	// @1410 '�' (6 pixels wide)
	0b00011111, 0b11000000, //    #######
	0b00011111, 0b11000000, //    #######
	0b00000000, 0b11010000, //         ## #
	0b00000000, 0b01011000, //          # ##
	0b00011111, 0b11001000, //    #######  #
	0b00011111, 0b10000000, //    ######

	// @1422 '�' (8 pixels wide)
	0b00001100, 0b01110000, //     ##   ###
	0b00011100, 0b11111000, //    ###  #####
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001100, //    #    #   ##
	0b00010001, 0b10001110, //    #   ##   ###
	0b00010001, 0b00001010, //    #   #    # #
	0b00011111, 0b00111000, //    #####  ###
	0b00001110, 0b00110000, //     ###   ##

	// @1438 '�' (6 pixels wide)
	0b00001001, 0b10000000, //     #  ##
	0b00011011, 0b11000000, //    ## ####
	0b00010010, 0b01010000, //    #  #  # #
	0b00010010, 0b01011000, //    #  #  # ##
	0b00011110, 0b11001000, //    #### ##  #
	0b00001100, 0b10000000, //     ##  #

	// @1450 '�' (7 pixels wide)
	0b00011000, 0b00001000, //    ##       #
	0b00011110, 0b00001000, //    ####     #
	0b00010111, 0b00001000, //    # ###    #
	0b00010001, 0b10001100, //    #   ##   ##
	0b00010000, 0b11101110, //    #    ### ###
	0b00010000, 0b01111010, //    #     #### #
	0b00010000, 0b00011000, //    #       ##

	// @1464 '�' (5 pixels wide)
	0b00011000, 0b01000000, //    ##    #
	0b00011110, 0b01010000, //    ####  # #
	0b00010111, 0b01011000, //    # ### # ##
	0b00010001, 0b11001000, //    #   ###  #
	0b00010000, 0b11000000, //    #    ##

	// @1474 '�' (7 pixels wide)
	0b00011000, 0b00001000, //    ##       #
	0b00011110, 0b00001000, //    ####     #
	0b00010111, 0b00001000, //    # ###    #
	0b00010001, 0b10001010, //    #   ##   # #
	0b00010000, 0b11101010, //    #    ### # #
	0b00010000, 0b01111000, //    #     ####
	0b00010000, 0b00011000, //    #       ##

	// @1488 '�' (5 pixels wide)
	0b00011000, 0b01000000, //    ##    #
	0b00011110, 0b01000000, //    ####  #
	0b00010111, 0b01010000, //    # ### # #
	0b00010001, 0b11010000, //    #   ### #
	0b00010000, 0b11000000, //    #    ##

	// @1498 bad char
	0b11111111, 0b11111111, // ################
	0b10000000, 0b00000001, // #              #
	0b10000000, 0b00000001, // #              #
	0b11111111, 0b11111111, // ################
};

const fontR_info_t FontRSans16B_PL_Descriptors[] = {
	{2, 0}, 		//
	{2, 4}, 		// !
	{4, 8}, 		// "
	{8, 16}, 		// #
	{6, 32}, 		// $
	{11, 44}, 		// %
	{8, 66}, 		// &
	{2, 82}, 		// '
	{4, 86}, 		// (
	{4, 94}, 		// )
	{6, 102}, 		// *
	{6, 114}, 		// +
	{3, 126}, 		// ,
	{5, 132}, 		// -
	{2, 142}, 		// .
	{5, 146}, 		// /
	{6, 156}, 		// 0
	{4, 168}, 		// 1
	{6, 176}, 		// 2
	{6, 188}, 		// 3
	{6, 200}, 		// 4
	{6, 212}, 		// 5
	{6, 224}, 		// 6
	{6, 236}, 		// 7
	{6, 248}, 		// 8
	{6, 260}, 		// 9
	{2, 272}, 		// :
	{3, 276}, 		// ;
	{6, 282}, 		// <
	{6, 294}, 		// =
	{6, 306}, 		// >
	{6, 318}, 		// ?
	{13, 330}, 		// @
	{10, 356}, 		// A
	{8, 376}, 		// B
	{9, 392}, 		// C
	{9, 410}, 		// D
	{8, 428}, 		// E
	{8, 444}, 		// F
	{9, 460}, 		// G
	{9, 478}, 		// H
	{2, 496}, 		// I
	{6, 500}, 		// J
	{8, 512}, 		// K
	{7, 528}, 		// L
	{10, 542}, 		// M
	{9, 562}, 		// N
	{9, 580}, 		// O
	{9, 598}, 		// P
	{9, 616}, 		// Q
	{10, 634}, 		// R
	{8, 654}, 		// S
	{10, 670}, 		// T
	{9, 690}, 		// U
	{10, 708}, 		// V
	{14, 728}, 		// W
	{9, 756}, 		// X
	{10, 774}, 		// Y
	{7, 794}, 		// Z
	{4, 808}, 		// [
	{5, 816}, 		// slash
	{4, 826}, 		// ]
	{6, 834}, 		// ^
	{8, 846}, 		// _
	{3, 862}, 		// `
	{8, 868}, 		// a
	{7, 884}, 		// b
	{7, 898}, 		// c
	{7, 912}, 		// d
	{7, 926}, 		// e
	{4, 940}, 		// f
	{7, 948}, 		// g
	{6, 962}, 		// h
	{2, 974}, 		// i
	{3, 978}, 		// j
	{7, 984}, 		// k
	{2, 998}, 		// l
	{10, 1002}, 	// m
	{6, 1022}, 		// n
	{7, 1034}, 		// o
	{7, 1048}, 		// p
	{7, 1062}, 		// q
	{4, 1076}, 		// r
	{6, 1084}, 		// s
	{4, 1096}, 		// t
	{6, 1104}, 		// u
	{8, 1116}, 		// v
	{10, 1132}, 	// w
	{7, 1152}, 		// x
	{8, 1166}, 		// y
	{5, 1182}, 		// z
	{6, 1192}, 		// {
	{2, 1204}, 		// |
	{6, 1208}, 		// }
	{8, 1220}, 		// ~
	{0, 0}, 		// 
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{8, 1422}, 		// �
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{7, 1450}, 		// �
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{6, 1438}, 		// �
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{5, 1464}, 		// �
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{8, 1366}, 		// �
	{0, 0}, 		// ?
	{10, 1268}, 	// �
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{7, 1474}, 		// �
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{5, 1382}, 		// �
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{8, 1288}, 		// �
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{5, 1488}, 		// �
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{9, 1304}, 		// �
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{8, 1336}, 		// �
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{9, 1392}, 		// �
	{0, 0}, 		// ?
	{9, 1236}, 		// �
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{7, 1322}, 		// �
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{7, 1352}, 		// �
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{0, 0}, 		// ?
	{6, 1410}, 		// �
	{0, 0}, 		// ?
	{7, 1254}, 		// �
	{4, 1498},		// bad char 244
};

const fontR_def_t FontRSans16B_PL = {
	.Height				=	2,
	.Width				=	0,
	.Spacing			=	1,
	.FirstChar			=	' ',
	.LastChar			=	244,
	.Descriptors		=	FontRSans16B_PL_Descriptors,
	.Bitmaps			=	FontRSans16B_PL_Bitmap,
};
