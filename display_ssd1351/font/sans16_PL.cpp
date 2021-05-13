#include "sans16_PL.h"

const uint8_t SSD1351_BitmapSans16_PL[] = {
	// @0 ' ' (2 pixels wide)
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //

	// @4 '!' (1 pixels wide)
	0b00111111, 0b11010000, //   ######## #

	// @6 '"' (3 pixels wide)
	0b00111100, 0b00000000, //   ####
	0b00000000, 0b00000000, //
	0b00111100, 0b00000000, //   ####

	// @12 '#' (7 pixels wide)
	0b00000000, 0b10000000, //         #
	0b00000100, 0b11110000, //      #  ####
	0b00000111, 0b10000000, //      ####
	0b00111100, 0b11110000, //   ####  ####
	0b00000111, 0b10000000, //      ####
	0b00111100, 0b10000000, //   ####  #
	0b00000100, 0b00000000, //      #

	// @26 '$' (5 pixels wide)
	0b00001110, 0b00100000, //     ###   #
	0b00010001, 0b00010000, //    #   #   #
	0b00111111, 0b11111000, //   ###########
	0b00010001, 0b00010000, //    #   #   #
	0b00001100, 0b11100000, //     ##  ###

	// @36 '%' (10 pixels wide)
	0b00011000, 0b00000000, //    ##
	0b00100100, 0b00100000, //   #  #    #
	0b00100100, 0b01000000, //   #  #   #
	0b00011000, 0b10000000, //    ##   #
	0b00000001, 0b00000000, //        #
	0b00000010, 0b00000000, //       #
	0b00000100, 0b01100000, //      #   ##
	0b00001000, 0b10010000, //     #   #  #
	0b00010000, 0b10010000, //    #    #  #
	0b00000000, 0b01100000, //          ##

	// @56 '&' (7 pixels wide)
	0b00000000, 0b11100000, //         ###
	0b00011101, 0b00010000, //    ### #   #
	0b00100010, 0b00010000, //   #   #    #
	0b00100011, 0b00010000, //   #   ##   #
	0b00011100, 0b11010000, //    ###  ## #
	0b00000000, 0b00100000, //           #
	0b00000000, 0b01010000, //          # #

	// @70 ''' (1 pixels wide)
	0b00111100, 0b00000000, //   ####

	// @72 '(' (3 pixels wide)
	0b00000111, 0b11110000, //      #######
	0b00011000, 0b00001100, //    ##       ##
	0b00100000, 0b00000010, //   #           #

	// @78 ')' (3 pixels wide)
	0b00100000, 0b00000010, //   #           #
	0b00011000, 0b00001100, //    ##       ##
	0b00000111, 0b11110000, //      #######

	// @84 '*' (5 pixels wide)
	0b00010100, 0b00000000, //    # #
	0b00001100, 0b00000000, //     ##
	0b00111000, 0b00000000, //   ###
	0b00001100, 0b00000000, //     ##
	0b00010100, 0b00000000, //    # #

	// @94 '+' (5 pixels wide)
	0b00000001, 0b00000000, //        #
	0b00000001, 0b00000000, //        #
	0b00000111, 0b11000000, //      #####
	0b00000001, 0b00000000, //        #
	0b00000001, 0b00000000, //        #

	// @104 ',' (2 pixels wide)
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00010000, //            #

	// @108 '-' (4 pixels wide)
	0b00000001, 0b00000000, //        #
	0b00000001, 0b00000000, //        #
	0b00000001, 0b00000000, //        #
	0b00000001, 0b00000000, //        #

	// @116 '.' (1 pixels wide)
	0b00000000, 0b00010000, //            #

	// @118 '/' (4 pixels wide)
	0b00000000, 0b00011100, //            ###
	0b00000000, 0b11100000, //         ###
	0b00000111, 0b00000000, //      ###
	0b00111000, 0b00000000, //   ###

	// @126 '0' (5 pixels wide)
	0b00011111, 0b11100000, //    ########
	0b00100000, 0b00010000, //   #        #
	0b00100000, 0b00010000, //   #        #
	0b00100000, 0b00010000, //   #        #
	0b00011111, 0b11100000, //    ########

	// @136 '1' (3 pixels wide)
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #
	0b00111111, 0b11110000, //   ##########

	// @142 '2' (5 pixels wide)
	0b00011000, 0b01110000, //    ##    ###
	0b00100000, 0b10010000, //   #     #  #
	0b00100001, 0b00010000, //   #    #   #
	0b00100010, 0b00010000, //   #   #    #
	0b00011100, 0b00010000, //    ###     #

	// @152 '3' (5 pixels wide)
	0b00010000, 0b00100000, //    #      #
	0b00100000, 0b00010000, //   #        #
	0b00100010, 0b00010000, //   #   #    #
	0b00100010, 0b00010000, //   #   #    #
	0b00011101, 0b11100000, //    ### ####

	// @162 '4' (5 pixels wide)
	0b00000001, 0b10000000, //        ##
	0b00000010, 0b10000000, //       # #
	0b00001100, 0b10000000, //     ##  #
	0b00010000, 0b10000000, //    #    #
	0b00111111, 0b11110000, //   ##########

	// @172 '5' (5 pixels wide)
	0b00111111, 0b00100000, //   ######  #
	0b00100010, 0b00010000, //   #   #    #
	0b00100010, 0b00010000, //   #   #    #
	0b00100010, 0b00010000, //   #   #    #
	0b00100001, 0b11100000, //   #    ####

	// @182 '6' (5 pixels wide)
	0b00011111, 0b11100000, //    ########
	0b00100001, 0b00010000, //   #    #   #
	0b00100010, 0b00010000, //   #   #    #
	0b00100010, 0b00010000, //   #   #    #
	0b00010001, 0b11100000, //    #   ####

	// @192 '7' (5 pixels wide)
	0b00100000, 0b00000000, //   #
	0b00100000, 0b01110000, //   #      ###
	0b00100001, 0b10000000, //   #    ##
	0b00100110, 0b00000000, //   #  ##
	0b00111000, 0b00000000, //   ###

	// @202 '8' (5 pixels wide)
	0b00011101, 0b11100000, //    ### ####
	0b00100010, 0b00010000, //   #   #    #
	0b00100010, 0b00010000, //   #   #    #
	0b00100010, 0b00010000, //   #   #    #
	0b00011101, 0b11100000, //    ### ####

	// @212 '9' (5 pixels wide)
	0b00011110, 0b00100000, //    ####   #
	0b00100001, 0b00010000, //   #    #   #
	0b00100001, 0b00010000, //   #    #   #
	0b00100010, 0b00010000, //   #   #    #
	0b00011111, 0b11100000, //    ########

	// @222 ':' (1 pixels wide)
	0b00000100, 0b00010000, //      #     #

	// @224 ';' (2 pixels wide)
	0b00000000, 0b00001000, //             #
	0b00000100, 0b00010000, //      #     #

	// @228 '<' (5 pixels wide)
	0b00000001, 0b00000000, //        #
	0b00000010, 0b10000000, //       # #
	0b00000100, 0b01000000, //      #   #
	0b00001000, 0b00100000, //     #     #
	0b00010000, 0b00010000, //    #       #

	// @238 '=' (5 pixels wide)
	0b00000010, 0b10000000, //       # #
	0b00000010, 0b10000000, //       # #
	0b00000010, 0b10000000, //       # #
	0b00000010, 0b10000000, //       # #
	0b00000010, 0b10000000, //       # #

	// @248 '>' (5 pixels wide)
	0b00010000, 0b00010000, //    #       #
	0b00001000, 0b00100000, //     #     #
	0b00000100, 0b01000000, //      #   #
	0b00000010, 0b10000000, //       # #
	0b00000001, 0b00000000, //        #

	// @258 '?' (5 pixels wide)
	0b00011000, 0b00000000, //    ##
	0b00100000, 0b00000000, //   #
	0b00100001, 0b11010000, //   #    ### #
	0b00100010, 0b00000000, //   #   #
	0b00011100, 0b00000000, //    ###

	// @268 '@' (12 pixels wide)
	0b00000111, 0b10000000, //      ####
	0b00011000, 0b01100000, //    ##    ##
	0b00100000, 0b00010000, //   #        #
	0b00100000, 0b00010000, //   #        #
	0b01000011, 0b10001000, //  #    ###   #
	0b01000100, 0b01001000, //  #   #   #  #
	0b01000100, 0b01001000, //  #   #   #  #
	0b01000100, 0b10001000, //  #   #  #   #
	0b00100111, 0b01001000, //   #  ### #  #
	0b00100000, 0b01010000, //   #      # #
	0b00011000, 0b01010000, //    ##    # #
	0b00000111, 0b10000000, //      ####

	// @292 'A' (9 pixels wide)
	0b00000000, 0b00110000, //           ##
	0b00000000, 0b11000000, //         ##
	0b00000011, 0b10000000, //       ###
	0b00001100, 0b10000000, //     ##  #
	0b00110000, 0b10000000, //   ##    #
	0b00001100, 0b10000000, //     ##  #
	0b00000011, 0b10000000, //       ###
	0b00000000, 0b11000000, //         ##
	0b00000000, 0b00110000, //           ##

	// @310 'B' (7 pixels wide)
	0b00111111, 0b11110000, //   ##########
	0b00100010, 0b00010000, //   #   #    #
	0b00100010, 0b00010000, //   #   #    #
	0b00100010, 0b00010000, //   #   #    #
	0b00100010, 0b00010000, //   #   #    #
	0b00100010, 0b00010000, //   #   #    #
	0b00011101, 0b11100000, //    ### ####

	// @324 'C' (8 pixels wide)
	0b00001111, 0b11000000, //     ######
	0b00010000, 0b00100000, //    #      #
	0b00100000, 0b00010000, //   #        #
	0b00100000, 0b00010000, //   #        #
	0b00100000, 0b00010000, //   #        #
	0b00100000, 0b00010000, //   #        #
	0b00010000, 0b00100000, //    #      #
	0b00001000, 0b01000000, //     #    #

	// @340 'D' (8 pixels wide)
	0b00111111, 0b11110000, //   ##########
	0b00100000, 0b00010000, //   #        #
	0b00100000, 0b00010000, //   #        #
	0b00100000, 0b00010000, //   #        #
	0b00100000, 0b00010000, //   #        #
	0b00100000, 0b00010000, //   #        #
	0b00010000, 0b00100000, //    #      #
	0b00001111, 0b11000000, //     ######

	// @356 'E' (7 pixels wide)
	0b00111111, 0b11110000, //   ##########
	0b00100010, 0b00010000, //   #   #    #
	0b00100010, 0b00010000, //   #   #    #
	0b00100010, 0b00010000, //   #   #    #
	0b00100010, 0b00010000, //   #   #    #
	0b00100010, 0b00010000, //   #   #    #
	0b00100000, 0b00010000, //   #        #

	// @370 'F' (7 pixels wide)
	0b00111111, 0b11110000, //   ##########
	0b00100010, 0b00000000, //   #   #
	0b00100010, 0b00000000, //   #   #
	0b00100010, 0b00000000, //   #   #
	0b00100010, 0b00000000, //   #   #
	0b00100010, 0b00000000, //   #   #
	0b00100000, 0b00000000, //   #

	// @384 'G' (8 pixels wide)
	0b00001111, 0b11000000, //     ######
	0b00010000, 0b00100000, //    #      #
	0b00100000, 0b00010000, //   #        #
	0b00100000, 0b00010000, //   #        #
	0b00100000, 0b00010000, //   #        #
	0b00100001, 0b00010000, //   #    #   #
	0b00010001, 0b00100000, //    #   #  #
	0b00001001, 0b11110000, //     #  #####

	// @400 'H' (8 pixels wide)
	0b00111111, 0b11110000, //   ##########
	0b00000010, 0b00000000, //       #
	0b00000010, 0b00000000, //       #
	0b00000010, 0b00000000, //       #
	0b00000010, 0b00000000, //       #
	0b00000010, 0b00000000, //       #
	0b00000010, 0b00000000, //       #
	0b00111111, 0b11110000, //   ##########

	// @416 'I' (1 pixels wide)
	0b00111111, 0b11110000, //   ##########

	// @418 'J' (5 pixels wide)
	0b00000000, 0b01100000, //          ##
	0b00000000, 0b00010000, //            #
	0b00000000, 0b00010000, //            #
	0b00000000, 0b00010000, //            #
	0b00111111, 0b11100000, //   #########

	// @428 'K' (7 pixels wide)
	0b00111111, 0b11110000, //   ##########
	0b00000010, 0b00000000, //       #
	0b00000101, 0b00000000, //      # #
	0b00001000, 0b10000000, //     #   #
	0b00010000, 0b01000000, //    #     #
	0b00100000, 0b00100000, //   #       #
	0b00000000, 0b00010000, //            #

	// @442 'L' (6 pixels wide)
	0b00111111, 0b11110000, //   ##########
	0b00000000, 0b00010000, //            #
	0b00000000, 0b00010000, //            #
	0b00000000, 0b00010000, //            #
	0b00000000, 0b00010000, //            #
	0b00000000, 0b00010000, //            #

	// @454 'M' (9 pixels wide)
	0b00111111, 0b11110000, //   ##########
	0b00001100, 0b00000000, //     ##
	0b00000011, 0b00000000, //       ##
	0b00000000, 0b11000000, //         ##
	0b00000000, 0b00110000, //           ##
	0b00000000, 0b11000000, //         ##
	0b00000011, 0b00000000, //       ##
	0b00001100, 0b00000000, //     ##
	0b00111111, 0b11110000, //   ##########

	// @472 'N' (8 pixels wide)
	0b00111111, 0b11110000, //   ##########
	0b00010000, 0b00000000, //    #
	0b00001100, 0b00000000, //     ##
	0b00000010, 0b00000000, //       #
	0b00000001, 0b00000000, //        #
	0b00000000, 0b11000000, //         ##
	0b00000000, 0b00100000, //           #
	0b00111111, 0b11110000, //   ##########

	// @488 'O' (8 pixels wide)
	0b00001111, 0b11000000, //     ######
	0b00010000, 0b00100000, //    #      #
	0b00100000, 0b00010000, //   #        #
	0b00100000, 0b00010000, //   #        #
	0b00100000, 0b00010000, //   #        #
	0b00100000, 0b00010000, //   #        #
	0b00010000, 0b00100000, //    #      #
	0b00001111, 0b11000000, //     ######

	// @504 'P' (8 pixels wide)
	0b00111111, 0b11110000, //   ##########
	0b00100001, 0b00000000, //   #    #
	0b00100001, 0b00000000, //   #    #
	0b00100001, 0b00000000, //   #    #
	0b00100001, 0b00000000, //   #    #
	0b00100001, 0b00000000, //   #    #
	0b00010010, 0b00000000, //    #  #
	0b00001100, 0b00000000, //     ##

	// @520 'Q' (8 pixels wide)
	0b00001111, 0b11000000, //     ######
	0b00010000, 0b00100000, //    #      #
	0b00100000, 0b00010000, //   #        #
	0b00100000, 0b00010000, //   #        #
	0b00100000, 0b00010000, //   #        #
	0b00100000, 0b01010000, //   #      # #
	0b00010000, 0b00100000, //    #      #
	0b00001111, 0b11010000, //     ###### #

	// @536 'R' (9 pixels wide)
	0b00111111, 0b11110000, //   ##########
	0b00100001, 0b00000000, //   #    #
	0b00100001, 0b00000000, //   #    #
	0b00100001, 0b00000000, //   #    #
	0b00100001, 0b00000000, //   #    #
	0b00100001, 0b00000000, //   #    #
	0b00010011, 0b00000000, //    #  ##
	0b00001100, 0b11100000, //     ##  ###
	0b00000000, 0b00010000, //            #

	// @554 'S' (7 pixels wide)
	0b00011100, 0b01100000, //    ###   ##
	0b00100010, 0b00010000, //   #   #    #
	0b00100010, 0b00010000, //   #   #    #
	0b00100010, 0b00010000, //   #   #    #
	0b00100001, 0b00010000, //   #    #   #
	0b00100001, 0b00010000, //   #    #   #
	0b00011000, 0b11100000, //    ##   ###

	// @568 'T' (9 pixels wide)
	0b00100000, 0b00000000, //   #
	0b00100000, 0b00000000, //   #
	0b00100000, 0b00000000, //   #
	0b00100000, 0b00000000, //   #
	0b00111111, 0b11110000, //   ##########
	0b00100000, 0b00000000, //   #
	0b00100000, 0b00000000, //   #
	0b00100000, 0b00000000, //   #
	0b00100000, 0b00000000, //   #

	// @586 'U' (8 pixels wide)
	0b00111111, 0b11000000, //   ########
	0b00000000, 0b00100000, //           #
	0b00000000, 0b00010000, //            #
	0b00000000, 0b00010000, //            #
	0b00000000, 0b00010000, //            #
	0b00000000, 0b00010000, //            #
	0b00000000, 0b00100000, //           #
	0b00111111, 0b11000000, //   ########

	// @602 'V' (9 pixels wide)
	0b00110000, 0b00000000, //   ##
	0b00001100, 0b00000000, //     ##
	0b00000011, 0b00000000, //       ##
	0b00000000, 0b11000000, //         ##
	0b00000000, 0b00110000, //           ##
	0b00000000, 0b11000000, //         ##
	0b00000011, 0b00000000, //       ##
	0b00001100, 0b00000000, //     ##
	0b00110000, 0b00000000, //   ##

	// @620 'W' (13 pixels wide)
	0b00111000, 0b00000000, //   ###
	0b00000110, 0b00000000, //      ##
	0b00000001, 0b11000000, //        ###
	0b00000000, 0b00110000, //           ##
	0b00000001, 0b11000000, //        ###
	0b00000110, 0b00000000, //      ##
	0b00111000, 0b00000000, //   ###
	0b00000110, 0b00000000, //      ##
	0b00000001, 0b11000000, //        ###
	0b00000000, 0b00110000, //           ##
	0b00000001, 0b11000000, //        ###
	0b00000110, 0b00000000, //      ##
	0b00111000, 0b00000000, //   ###

	// @646 'X' (8 pixels wide)
	0b00110000, 0b00110000, //   ##      ##
	0b00001000, 0b01000000, //     #    #
	0b00000100, 0b10000000, //      #  #
	0b00000011, 0b00000000, //       ##
	0b00000011, 0b00000000, //       ##
	0b00000100, 0b10000000, //      #  #
	0b00001000, 0b01000000, //     #    #
	0b00110000, 0b00110000, //   ##      ##

	// @662 'Y' (9 pixels wide)
	0b00110000, 0b00000000, //   ##
	0b00001000, 0b00000000, //     #
	0b00000100, 0b00000000, //      #
	0b00000010, 0b00000000, //       #
	0b00000001, 0b11110000, //        #####
	0b00000010, 0b00000000, //       #
	0b00000100, 0b00000000, //      #
	0b00001000, 0b00000000, //     #
	0b00110000, 0b00000000, //   ##

	// @680 'Z' (6 pixels wide)
	0b00100000, 0b00110000, //   #       ##
	0b00100000, 0b11010000, //   #     ## #
	0b00100001, 0b00010000, //   #    #   #
	0b00100010, 0b00010000, //   #   #    #
	0b00101100, 0b00010000, //   # ##     #
	0b00110000, 0b00010000, //   ##       #

	// @692 '[' (3 pixels wide)
	0b00111111, 0b11111110, //   #############
	0b00100000, 0b00000010, //   #           #
	0b00100000, 0b00000010, //   #           #

	// @698 '\' (4 pixels wide)
	0b00111000, 0b00000000, //   ###
	0b00000111, 0b00000000, //      ###
	0b00000000, 0b11100000, //         ###
	0b00000000, 0b00011100, //            ###

	// @706 ']' (3 pixels wide)
	0b00100000, 0b00000010, //   #           #
	0b00100000, 0b00000010, //   #           #
	0b00111111, 0b11111110, //   #############

	// @712 '^' (5 pixels wide)
	0b00010000, 0b00000000, //    #
	0b00100000, 0b00000000, //   #
	0b01000000, 0b00000000, //  #
	0b00100000, 0b00000000, //   #
	0b00010000, 0b00000000, //    #

	// @722 '_' (7 pixels wide)
	0b00000000, 0b00000100, //              #
	0b00000000, 0b00000100, //              #
	0b00000000, 0b00000100, //              #
	0b00000000, 0b00000100, //              #
	0b00000000, 0b00000100, //              #
	0b00000000, 0b00000100, //              #
	0b00000000, 0b00000100, //              #

	// @736 '`' (2 pixels wide)
	0b00100000, 0b00000000, //   #
	0b00010000, 0b00000000, //    #

	// @740 'a' (7 pixels wide)
	0b00000010, 0b11100000, //       # ###
	0b00000101, 0b00010000, //      # #   #
	0b00000101, 0b00010000, //      # #   #
	0b00000101, 0b00010000, //      # #   #
	0b00000101, 0b00010000, //      # #   #
	0b00000011, 0b11100000, //       #####
	0b00000000, 0b00010000, //            #

	// @754 'b' (6 pixels wide)
	0b00111111, 0b11110000, //   ##########
	0b00000010, 0b00100000, //       #   #
	0b00000100, 0b00010000, //      #     #
	0b00000100, 0b00010000, //      #     #
	0b00000100, 0b00010000, //      #     #
	0b00000011, 0b11100000, //       #####

	// @766 'c' (6 pixels wide)
	0b00000011, 0b11100000, //       #####
	0b00000100, 0b00010000, //      #     #
	0b00000100, 0b00010000, //      #     #
	0b00000100, 0b00010000, //      #     #
	0b00000100, 0b00010000, //      #     #
	0b00000010, 0b00100000, //       #   #

	// @778 'd' (6 pixels wide)
	0b00000011, 0b11100000, //       #####
	0b00000100, 0b00010000, //      #     #
	0b00000100, 0b00010000, //      #     #
	0b00000100, 0b00010000, //      #     #
	0b00000010, 0b00100000, //       #   #
	0b00111111, 0b11110000, //   ##########

	// @790 'e' (6 pixels wide)
	0b00000011, 0b11100000, //       #####
	0b00000100, 0b10010000, //      #  #  #
	0b00000100, 0b10010000, //      #  #  #
	0b00000100, 0b10010000, //      #  #  #
	0b00000100, 0b10010000, //      #  #  #
	0b00000011, 0b10100000, //       ### #

	// @802 'f' (3 pixels wide)
	0b00000100, 0b00000000, //      #
	0b00011111, 0b11110000, //    #########
	0b00100100, 0b00000000, //   #  #

	// @808 'g' (6 pixels wide)
	0b00000011, 0b11100000, //       #####
	0b00000100, 0b00010010, //      #     #  #
	0b00000100, 0b00010010, //      #     #  #
	0b00000100, 0b00010010, //      #     #  #
	0b00000010, 0b00100010, //       #   #   #
	0b00000111, 0b11111100, //      #########

	// @820 'h' (5 pixels wide)
	0b00111111, 0b11110000, //   ##########
	0b00000010, 0b00000000, //       #
	0b00000100, 0b00000000, //      #
	0b00000100, 0b00000000, //      #
	0b00000011, 0b11110000, //       ######

	// @830 'i' (1 pixels wide)
	0b00100111, 0b11110000, //   #  #######

	// @832 'j' (2 pixels wide)
	0b00000000, 0b00000010, //               #
	0b00100111, 0b11111100, //   #  #########

	// @836 'k' (6 pixels wide)
	0b00111111, 0b11110000, //   ##########
	0b00000000, 0b10000000, //         #
	0b00000001, 0b10000000, //        ##
	0b00000010, 0b01000000, //       #  #
	0b00000100, 0b00100000, //      #    #
	0b00000000, 0b00010000, //            #

	// @848 'l' (1 pixels wide)
	0b00111111, 0b11110000, //   ##########

	// @850 'm' (9 pixels wide)
	0b00000111, 0b11110000, //      #######
	0b00000010, 0b00000000, //       #
	0b00000100, 0b00000000, //      #
	0b00000100, 0b00000000, //      #
	0b00000011, 0b11110000, //       ######
	0b00000010, 0b00000000, //       #
	0b00000100, 0b00000000, //      #
	0b00000100, 0b00000000, //      #
	0b00000011, 0b11110000, //       ######

	// @868 'n' (5 pixels wide)
	0b00000111, 0b11110000, //      #######
	0b00000010, 0b00000000, //       #
	0b00000100, 0b00000000, //      #
	0b00000100, 0b00000000, //      #
	0b00000011, 0b11110000, //       ######

	// @878 'o' (6 pixels wide)
	0b00000011, 0b11100000, //       #####
	0b00000100, 0b00010000, //      #     #
	0b00000100, 0b00010000, //      #     #
	0b00000100, 0b00010000, //      #     #
	0b00000100, 0b00010000, //      #     #
	0b00000011, 0b11100000, //       #####

	// @890 'p' (6 pixels wide)
	0b00000111, 0b11111110, //      ##########
	0b00000010, 0b00100000, //       #   #
	0b00000100, 0b00010000, //      #     #
	0b00000100, 0b00010000, //      #     #
	0b00000100, 0b00010000, //      #     #
	0b00000011, 0b11100000, //       #####

	// @902 'q' (6 pixels wide)
	0b00000011, 0b11100000, //       #####
	0b00000100, 0b00010000, //      #     #
	0b00000100, 0b00010000, //      #     #
	0b00000100, 0b00010000, //      #     #
	0b00000010, 0b00100000, //       #   #
	0b00000111, 0b11111110, //      ##########

	// @914 'r' (3 pixels wide)
	0b00000111, 0b11110000, //      #######
	0b00000010, 0b00000000, //       #
	0b00000100, 0b00000000, //      #

	// @920 's' (5 pixels wide)
	0b00000011, 0b00100000, //       ##  #
	0b00000100, 0b10010000, //      #  #  #
	0b00000100, 0b10010000, //      #  #  #
	0b00000100, 0b10010000, //      #  #  #
	0b00000010, 0b01100000, //       #  ##

	// @930 't' (3 pixels wide)
	0b00000100, 0b00000000, //      #
	0b00011111, 0b11100000, //    ########
	0b00000100, 0b00010000, //      #     #

	// @936 'u' (5 pixels wide)
	0b00000111, 0b11100000, //      ######
	0b00000000, 0b00010000, //            #
	0b00000000, 0b00010000, //            #
	0b00000000, 0b00100000, //           #
	0b00000111, 0b11110000, //      #######

	// @946 'v' (7 pixels wide)
	0b00000110, 0b00000000, //      ##
	0b00000001, 0b10000000, //        ##
	0b00000000, 0b01100000, //          ##
	0b00000000, 0b00010000, //            #
	0b00000000, 0b01100000, //          ##
	0b00000001, 0b10000000, //        ##
	0b00000110, 0b00000000, //      ##

	// @960 'w' (9 pixels wide)
	0b00000110, 0b00000000, //      ##
	0b00000001, 0b11000000, //        ###
	0b00000000, 0b00110000, //           ##
	0b00000001, 0b11000000, //        ###
	0b00000110, 0b00000000, //      ##
	0b00000001, 0b11000000, //        ###
	0b00000000, 0b00110000, //           ##
	0b00000001, 0b11000000, //        ###
	0b00000110, 0b00000000, //      ##

	// @978 'x' (6 pixels wide)
	0b00000100, 0b00010000, //      #     #
	0b00000010, 0b00100000, //       #   #
	0b00000001, 0b11000000, //        ###
	0b00000001, 0b11000000, //        ###
	0b00000010, 0b00100000, //       #   #
	0b00000100, 0b00010000, //      #     #

	// @990 'y' (7 pixels wide)
	0b00000110, 0b00000010, //      ##       #
	0b00000001, 0b10000010, //        ##     #
	0b00000000, 0b01100100, //          ##  #
	0b00000000, 0b00011000, //            ##
	0b00000000, 0b01100000, //          ##
	0b00000001, 0b10000000, //        ##
	0b00000110, 0b00000000, //      ##

	// @1004 'z' (4 pixels wide)
	0b00000100, 0b00110000, //      #    ##
	0b00000100, 0b11010000, //      #  ## #
	0b00000101, 0b00010000, //      # #   #
	0b00000110, 0b00010000, //      ##    #

	// @1012 '{' (5 pixels wide)
	0b00000000, 0b10000000, //         #
	0b00000000, 0b10000000, //         #
	0b00011111, 0b01111100, //    ##### #####
	0b00100000, 0b00000010, //   #           #
	0b00100000, 0b00000010, //   #           #

	// @1022 '|' (1 pixels wide)
	0b00111111, 0b11111110, //   #############

	// @1024 '}' (5 pixels wide)
	0b00100000, 0b00000010, //   #           #
	0b00100000, 0b00000010, //   #           #
	0b00011111, 0b01111100, //    ##### #####
	0b00000000, 0b10000000, //         #
	0b00000000, 0b10000000, //         #

	// @1034 '~' (7 pixels wide)
	0b00011000, 0b00000000, //    ##
	0b00100000, 0b00000000, //   #
	0b00100000, 0b00000000, //   #
	0b00010000, 0b00000000, //    #
	0b00001000, 0b00000000, //     #
	0b00001000, 0b00000000, //     #
	0b00110000, 0b00000000, //   ##

	// @1048 '�' (8 pixels wide)
	0b00001111, 0b11000000, //     ######
	0b00010000, 0b00100000, //    #      #
	0b00100000, 0b00010000, //   #        #
	0b00100000, 0b00010000, //   #        #
	0b01100000, 0b00010000, //  ##        #
	0b10100000, 0b00010000, // # #        #
	0b00010000, 0b00100000, //    #      #
	0b00001111, 0b11000000, //     ######

	// @1064 '�' (6 pixels wide)
	0b00000011, 0b11100000, //       #####
	0b00000100, 0b00010000, //      #     #
	0b00010100, 0b00010000, //    # #     #
	0b00100100, 0b00010000, //   #  #     #
	0b00000100, 0b00010000, //      #     #
	0b00000011, 0b11100000, //       #####

	// @1076 '�' (9 pixels wide)
	0b00000000, 0b00110000, //           ##
	0b00000000, 0b11000000, //         ##
	0b00000011, 0b10000000, //       ###
	0b00001100, 0b10000000, //     ##  #
	0b00110000, 0b10000000, //   ##    #
	0b00001100, 0b10000000, //     ##  #
	0b00000011, 0b10000100, //       ###    #
	0b00000000, 0b11001010, //         ##  # #
	0b00000000, 0b00110010, //           ##  #

	// @1094 '�' (7 pixels wide)
	0b00000010, 0b11100000, //       # ###
	0b00000101, 0b00010000, //      # #   #
	0b00000101, 0b00010000, //      # #   #
	0b00000101, 0b00010000, //      # #   #
	0b00000101, 0b00010100, //      # #   # #
	0b00000011, 0b11101010, //       ##### # #
	0b00000000, 0b00010010, //            #  #

	// @1108 '�' (8 pixels wide)
	0b00001111, 0b11000000, //     ######
	0b00010000, 0b00100000, //    #      #
	0b00100000, 0b00010000, //   #        #
	0b01100000, 0b00010000, //  ##        #
	0b10100000, 0b00010000, // # #        #
	0b00100000, 0b00010000, //   #        #
	0b00010000, 0b00100000, //    #      #
	0b00001000, 0b01000000, //     #    #

	// @1124 '�' (6 pixels wide)
	0b00000011, 0b11100000, //       #####
	0b00000100, 0b00010000, //      #     #
	0b00000100, 0b00010000, //      #     #
	0b00010100, 0b00010000, //    # #     #
	0b00100100, 0b00010000, //   #  #     #
	0b00000010, 0b00100000, //       #   #

	// @1136 '�' (7 pixels wide)
	0b00111111, 0b11110000, //   ##########
	0b00100010, 0b00010000, //   #   #    #
	0b00100010, 0b00010100, //   #   #    # #
	0b00100010, 0b00011010, //   #   #    ## #
	0b00100010, 0b00010010, //   #   #    #  #
	0b00100010, 0b00010000, //   #   #    #
	0b00100000, 0b00010000, //   #        #

	// @1150 '�' (6 pixels wide)
	0b00000011, 0b11100000, //       #####
	0b00000100, 0b10010100, //      #  #  # #
	0b00000100, 0b10011010, //      #  #  ## #
	0b00000100, 0b10010010, //      #  #  #  #
	0b00000100, 0b10010000, //      #  #  #
	0b00000011, 0b10100000, //       ### #

	// @1162 '�' (7 pixels wide)
	0b00000000, 0b10000000, //         #
	0b00111111, 0b11110000, //   ##########
	0b00000010, 0b00010000, //       #    #
	0b00000100, 0b00010000, //      #     #
	0b00000000, 0b00010000, //            #
	0b00000000, 0b00010000, //            #
	0b00000000, 0b00010000, //            #

	// @1176 '�' (4 pixels wide)
	0b00000000, 0b10000000, //         #
	0b00111111, 0b11110000, //   ##########
	0b00000010, 0b00000000, //       #
	0b00000100, 0b00000000, //      #

	// @1184 '�' (8 pixels wide)
	0b00111111, 0b11110000, //   ##########
	0b00010000, 0b00000000, //    #
	0b00001100, 0b00000000, //     ##
	0b01000010, 0b00000000, //  #    #
	0b10000001, 0b00000000, // #      #
	0b00000000, 0b11000000, //         ##
	0b00000000, 0b00100000, //           #
	0b00111111, 0b11110000, //   ##########

	// @1200 '�' (5 pixels wide)
	0b00000111, 0b11110000, //      #######
	0b00000010, 0b00000000, //       #
	0b00010100, 0b00000000, //    # #
	0b00100100, 0b00000000, //   #  #
	0b00000011, 0b11110000, //       ######

	// @1210 '�' (7 pixels wide)
	0b00011100, 0b01100000, //    ###   ##
	0b00100010, 0b00010000, //   #   #    #
	0b00100010, 0b00010000, //   #   #    #
	0b01100010, 0b00010000, //  ##   #    #
	0b10100001, 0b00010000, // # #    #   #
	0b00100001, 0b00010000, //   #    #   #
	0b00011000, 0b11100000, //    ##   ###

	// @1224 '�' (5 pixels wide)
	0b00000011, 0b00100000, //       ##  #
	0b00000100, 0b10010000, //      #  #  #
	0b00010100, 0b10010000, //    # #  #  #
	0b00100100, 0b10010000, //   #  #  #  #
	0b00000010, 0b01100000, //       #  ##

	// @1234 '�' (6 pixels wide)
	0b00100000, 0b00110000, //   #       ##
	0b00100000, 0b11010000, //   #     ## #
	0b00100001, 0b00010000, //   #    #   #
	0b01100010, 0b00010000, //  ##   #    #
	0b10101100, 0b00010000, // # # ##     #
	0b00110000, 0b00010000, //   ##       #

	// @1246 '�' (4 pixels wide)
	0b00000100, 0b00110000, //      #    ##
	0b00010100, 0b11010000, //    # #  ## #
	0b00100101, 0b00010000, //   #  # #   #
	0b00000110, 0b00010000, //      ##    #

	// @1254 '�' (6 pixels wide)
	0b00100000, 0b00110000, //   #       ##
	0b00100000, 0b11010000, //   #     ## #
	0b00100001, 0b00010000, //   #    #   #
	0b10100010, 0b00010000, // # #   #    #
	0b00101100, 0b00010000, //   # ##     #
	0b00110000, 0b00010000, //   ##       #

	// @1266 '�' (4 pixels wide)
	0b00000100, 0b00110000, //      #    ##
	0b00000100, 0b11010000, //      #  ## #
	0b00010101, 0b00010000, //    # # #   #
	0b00000110, 0b00010000, //      ##    #

	// @1274 bad char
	0b11111111, 0b11111111, // ################
	0b10000000, 0b00000001, // #              #
	0b10000000, 0b00000001, // #              #
	0b11111111, 0b11111111, // ################

};

const SSD1351_CharDef_t SSD1351_CharactersSans16_PL[] = {
	{2, 0}, 		//
	{1, 4}, 		// !
	{3, 6}, 		// "
	{7, 12}, 		// #
	{5, 26}, 		// $
	{10, 36}, 		// %
	{7, 56}, 		// &
	{1, 70}, 		// '
	{3, 72}, 		// (
	{3, 78}, 		// )
	{5, 84}, 		// *
	{5, 94}, 		// +
	{2, 104}, 		// ,
	{4, 108}, 		// -
	{1, 116}, 		// .
	{4, 118}, 		// /
	{5, 126}, 		// 0
	{3, 136}, 		// 1
	{5, 142}, 		// 2
	{5, 152}, 		// 3
	{5, 162}, 		// 4
	{5, 172}, 		// 5
	{5, 182}, 		// 6
	{5, 192}, 		// 7
	{5, 202}, 		// 8
	{5, 212}, 		// 9
	{1, 222}, 		// :
	{2, 224}, 		// ;
	{5, 228}, 		// <
	{5, 238}, 		// =
	{5, 248}, 		// >
	{5, 258}, 		// ?
	{12, 268}, 		// @
	{9, 292}, 		// A
	{7, 310}, 		// B
	{8, 324}, 		// C
	{8, 340}, 		// D
	{7, 356}, 		// E
	{7, 370}, 		// F
	{8, 384}, 		// G
	{8, 400}, 		// H
	{1, 416}, 		// I
	{5, 418}, 		// J
	{7, 428}, 		// K
	{6, 442}, 		// L
	{9, 454}, 		// M
	{8, 472}, 		// N
	{8, 488}, 		// O
	{8, 504}, 		// P
	{8, 520}, 		// Q
	{9, 536}, 		// R
	{7, 554}, 		// S
	{9, 568}, 		// T
	{8, 586}, 		// U
	{9, 602}, 		// V
	{13, 620}, 		// W
	{8, 646}, 		// X
	{9, 662}, 		// Y
	{6, 680}, 		// Z
	{3, 692}, 		// [
	{4, 698}, 		// slash
	{3, 706}, 		// ]
	{5, 712}, 		// ^
	{7, 722}, 		// _
	{2, 736}, 		// `
	{7, 740}, 		// a
	{6, 754}, 		// b
	{6, 766}, 		// c
	{6, 778}, 		// d
	{6, 790}, 		// e
	{3, 802}, 		// f
	{6, 808}, 		// g
	{5, 820}, 		// h
	{1, 830}, 		// i
	{2, 832}, 		// j
	{6, 836}, 		// k
	{1, 848}, 		// l
	{9, 850}, 		// m
	{5, 868}, 		// n
	{6, 878}, 		// o
	{6, 890}, 		// p
	{6, 902}, 		// q
	{3, 914}, 		// r
	{5, 920}, 		// s
	{3, 930}, 		// t
	{5, 936}, 		// u
	{7, 946}, 		// v
	{9, 960}, 		// w
	{6, 978}, 		// x
	{7, 990}, 		// y
	{4, 1004}, 		// z
	{5, 1012}, 		// {
	{1, 1022}, 		// |
	{5, 1024}, 		// }
	{7, 1034}, 		// ~
	{0, 0}, 		// 
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{7, 1210}, 		// �
	{0, 0}, 		//
	{0, 0}, 		//
	{6, 1234}, 		// �
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{5, 1224}, 		// �
	{0, 0}, 		//
	{0, 0}, 		//
	{4, 1246}, 		// �
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{7, 1162}, 		// �
	{0, 0}, 		//
	{9, 1076}, 		// �
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{6, 1254}, 		// �
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{4, 1176}, 		// �
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{7, 1094}, 		// �
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{4, 1266}, 		// �
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{8, 1108}, 		// �
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{7, 1136}, 		// �
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{8, 1184}, 		// �
	{0, 0}, 		//
	{8, 1048}, 		// �
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{6, 1124}, 		// �
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{6, 1150}, 		// �
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{0, 0}, 		//
	{5, 1200}, 		// �
	{0, 0}, 		//
	{6, 1064}, 		// �
	{4, 1270},		// bad char 244
};

const SSD1351_FontDef_t SSD1351_FontSans16_PL = {
	.Height				=	16,
	.Width				=	0,
	.Spacing			=	1,
	.FirstChar			=	' ',
	.LastChar			=	244,
	.Descriptors		=	SSD1351_CharactersSans16_PL,
	.Bitmaps			=	SSD1351_BitmapSans16_PL,
};