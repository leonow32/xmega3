#include "sans16_PL.h"

const uint8_t SH1106_BitmapSans16_PL[] = {
	// @0 ' ' (2 pixels wide)
	0b00000000, 0b00000000, //
	0b00000000, 0b00000000, //

	// @4 '!' (1 pixels wide)
	0b00010111, 0b11111000, //    # ########

	// @6 '"' (3 pixels wide)
	0b00000000, 0b01111000, //          ####
	0b00000000, 0b00000000, //
	0b00000000, 0b01111000, //          ####

	// @12 '#' (7 pixels wide)
	0b00000010, 0b00000000, //       #
	0b00011110, 0b01000000, //    ####  #
	0b00000011, 0b11000000, //       ####
	0b00011110, 0b01111000, //    ####  ####
	0b00000011, 0b11000000, //       ####
	0b00000010, 0b01111000, //       #  ####
	0b00000000, 0b01000000, //          #

	// @26 '$' (5 pixels wide)
	0b00001000, 0b11100000, //     #   ###
	0b00010001, 0b00010000, //    #   #   #
	0b00111111, 0b11111000, //   ###########
	0b00010001, 0b00010000, //    #   #   #
	0b00001110, 0b01100000, //     ###  ##

	// @36 '%' (10 pixels wide)
	0b00000000, 0b00110000, //           ##
	0b00001000, 0b01001000, //     #    #  #
	0b00000100, 0b01001000, //      #   #  #
	0b00000010, 0b00110000, //       #   ##
	0b00000001, 0b00000000, //        #
	0b00000000, 0b10000000, //         #
	0b00001100, 0b01000000, //     ##   #
	0b00010010, 0b00100000, //    #  #   #
	0b00010010, 0b00010000, //    #  #    #
	0b00001100, 0b00000000, //     ##

	// @56 '&' (7 pixels wide)
	0b00001110, 0b00000000, //     ###
	0b00010001, 0b01110000, //    #   # ###
	0b00010000, 0b10001000, //    #    #   #
	0b00010001, 0b10001000, //    #   ##   #
	0b00010110, 0b01110000, //    # ##  ###
	0b00001000, 0b00000000, //     #
	0b00010100, 0b00000000, //    # #

	// @70 ''' (1 pixels wide)
	0b00000000, 0b01111000, //          ####

	// @72 '(' (3 pixels wide)
	0b00011111, 0b11000000, //    #######
	0b01100000, 0b00110000, //  ##       ##
	0b10000000, 0b00001000, // #           #

	// @78 ')' (3 pixels wide)
	0b10000000, 0b00001000, // #           #
	0b01100000, 0b00110000, //  ##       ##
	0b00011111, 0b11000000, //    #######

	// @84 '*' (5 pixels wide)
	0b00000000, 0b01010000, //          # #
	0b00000000, 0b01100000, //          ##
	0b00000000, 0b00111000, //           ###
	0b00000000, 0b01100000, //          ##
	0b00000000, 0b01010000, //          # #

	// @94 '+' (5 pixels wide)
	0b00000001, 0b00000000, //        #
	0b00000001, 0b00000000, //        #
	0b00000111, 0b11000000, //      #####
	0b00000001, 0b00000000, //        #
	0b00000001, 0b00000000, //        #

	// @104 ',' (2 pixels wide)
	0b00100000, 0b00000000, //   #
	0b00010000, 0b00000000, //    #

	// @108 '-' (4 pixels wide)
	0b00000001, 0b00000000, //        #
	0b00000001, 0b00000000, //        #
	0b00000001, 0b00000000, //        #
	0b00000001, 0b00000000, //        #

	// @116 '.' (1 pixels wide)
	0b00010000, 0b00000000, //    #

	// @118 '/' (4 pixels wide)
	0b01110000, 0b00000000, //  ###
	0b00001110, 0b00000000, //     ###
	0b00000001, 0b11000000, //        ###
	0b00000000, 0b00111000, //           ###

	// @126 '0' (5 pixels wide)
	0b00001111, 0b11110000, //     ########
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00001111, 0b11110000, //     ########

	// @136 '1' (3 pixels wide)
	0b00000000, 0b00010000, //            #
	0b00000000, 0b00010000, //            #
	0b00011111, 0b11111000, //    ##########

	// @142 '2' (5 pixels wide)
	0b00011100, 0b00110000, //    ###    ##
	0b00010010, 0b00001000, //    #  #     #
	0b00010001, 0b00001000, //    #   #    #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b01110000, //    #     ###

	// @152 '3' (5 pixels wide)
	0b00001000, 0b00010000, //     #      #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00001111, 0b01110000, //     #### ###

	// @162 '4' (5 pixels wide)
	0b00000011, 0b00000000, //       ##
	0b00000010, 0b10000000, //       # #
	0b00000010, 0b01100000, //       #  ##
	0b00000010, 0b00010000, //       #    #
	0b00011111, 0b11111000, //    ##########

	// @172 '5' (5 pixels wide)
	0b00001001, 0b11111000, //     #  ######
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00001111, 0b00001000, //     ####    #

	// @182 '6' (5 pixels wide)
	0b00001111, 0b11110000, //     ########
	0b00010001, 0b00001000, //    #   #    #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00001111, 0b00010000, //     ####   #

	// @192 '7' (5 pixels wide)
	0b00000000, 0b00001000, //             #
	0b00011100, 0b00001000, //    ###      #
	0b00000011, 0b00001000, //       ##    #
	0b00000000, 0b11001000, //         ##  #
	0b00000000, 0b00111000, //           ###

	// @202 '8' (5 pixels wide)
	0b00001111, 0b01110000, //     #### ###
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00001111, 0b01110000, //     #### ###

	// @212 '9' (5 pixels wide)
	0b00001000, 0b11110000, //     #   ####
	0b00010001, 0b00001000, //    #   #    #
	0b00010001, 0b00001000, //    #   #    #
	0b00010000, 0b10001000, //    #    #   #
	0b00001111, 0b11110000, //     ########

	// @222 ':' (1 pixels wide)
	0b00010000, 0b01000000, //    #     #

	// @224 ';' (2 pixels wide)
	0b00100000, 0b00000000, //   #
	0b00010000, 0b01000000, //    #     #

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
	0b00000000, 0b00110000, //           ##
	0b00000000, 0b00001000, //             #
	0b00010111, 0b00001000, //    # ###    #
	0b00000000, 0b10001000, //         #   #
	0b00000000, 0b01110000, //          ###

	// @268 '@' (12 pixels wide)
	0b00000011, 0b11000000, //       ####
	0b00001100, 0b00110000, //     ##    ##
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00100011, 0b10000100, //   #   ###    #
	0b00100100, 0b01000100, //   #  #   #   #
	0b00100100, 0b01000100, //   #  #   #   #
	0b00100010, 0b01000100, //   #   #  #   #
	0b00100101, 0b11001000, //   #  # ###  #
	0b00010100, 0b00001000, //    # #      #
	0b00010100, 0b00110000, //    # #    ##
	0b00000011, 0b11000000, //       ####

	// @292 'A' (9 pixels wide)
	0b00011000, 0b00000000, //    ##
	0b00000110, 0b00000000, //      ##
	0b00000011, 0b10000000, //       ###
	0b00000010, 0b01100000, //       #  ##
	0b00000010, 0b00011000, //       #    ##
	0b00000010, 0b01100000, //       #  ##
	0b00000011, 0b10000000, //       ###
	0b00000110, 0b00000000, //      ##
	0b00011000, 0b00000000, //    ##

	// @310 'B' (7 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00001111, 0b01110000, //     #### ###

	// @324 'C' (8 pixels wide)
	0b00000111, 0b11100000, //      ######
	0b00001000, 0b00010000, //     #      #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00001000, 0b00010000, //     #      #
	0b00000100, 0b00100000, //      #    #

	// @340 'D' (8 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00001000, 0b00010000, //     #      #
	0b00000111, 0b11100000, //      ######

	// @356 'E' (7 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b00001000, //    #        #

	// @370 'F' (7 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00000000, 0b10001000, //         #   #
	0b00000000, 0b10001000, //         #   #
	0b00000000, 0b10001000, //         #   #
	0b00000000, 0b10001000, //         #   #
	0b00000000, 0b10001000, //         #   #
	0b00000000, 0b00001000, //             #

	// @384 'G' (8 pixels wide)
	0b00000111, 0b11100000, //      ######
	0b00001000, 0b00010000, //     #      #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00010001, 0b00001000, //    #   #    #
	0b00001001, 0b00010000, //     #  #   #
	0b00011111, 0b00100000, //    #####  #

	// @400 'H' (8 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00000000, 0b10000000, //         #
	0b00000000, 0b10000000, //         #
	0b00000000, 0b10000000, //         #
	0b00000000, 0b10000000, //         #
	0b00000000, 0b10000000, //         #
	0b00000000, 0b10000000, //         #
	0b00011111, 0b11111000, //    ##########

	// @416 'I' (1 pixels wide)
	0b00011111, 0b11111000, //    ##########

	// @418 'J' (5 pixels wide)
	0b00001100, 0b00000000, //     ##
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #
	0b00001111, 0b11111000, //     #########

	// @428 'K' (7 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00000000, 0b10000000, //         #
	0b00000001, 0b01000000, //        # #
	0b00000010, 0b00100000, //       #   #
	0b00000100, 0b00010000, //      #     #
	0b00001000, 0b00001000, //     #       #
	0b00010000, 0b00000000, //    #

	// @442 'L' (6 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #

	// @454 'M' (9 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00000000, 0b01100000, //          ##
	0b00000001, 0b10000000, //        ##
	0b00000110, 0b00000000, //      ##
	0b00011000, 0b00000000, //    ##
	0b00000110, 0b00000000, //      ##
	0b00000001, 0b10000000, //        ##
	0b00000000, 0b01100000, //          ##
	0b00011111, 0b11111000, //    ##########

	// @472 'N' (8 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00000000, 0b00010000, //            #
	0b00000000, 0b01100000, //          ##
	0b00000000, 0b10000000, //         #
	0b00000001, 0b00000000, //        #
	0b00000110, 0b00000000, //      ##
	0b00001000, 0b00000000, //     #
	0b00011111, 0b11111000, //    ##########

	// @488 'O' (8 pixels wide)
	0b00000111, 0b11100000, //      ######
	0b00001000, 0b00010000, //     #      #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00001000, 0b00010000, //     #      #
	0b00000111, 0b11100000, //      ######

	// @504 'P' (8 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00000001, 0b00001000, //        #    #
	0b00000001, 0b00001000, //        #    #
	0b00000001, 0b00001000, //        #    #
	0b00000001, 0b00001000, //        #    #
	0b00000001, 0b00001000, //        #    #
	0b00000000, 0b10010000, //         #  #
	0b00000000, 0b01100000, //          ##

	// @520 'Q' (8 pixels wide)
	0b00000111, 0b11100000, //      ######
	0b00001000, 0b00010000, //     #      #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00010100, 0b00001000, //    # #      #
	0b00001000, 0b00010000, //     #      #
	0b00010111, 0b11100000, //    # ######

	// @536 'R' (9 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00000001, 0b00001000, //        #    #
	0b00000001, 0b00001000, //        #    #
	0b00000001, 0b00001000, //        #    #
	0b00000001, 0b00001000, //        #    #
	0b00000001, 0b00001000, //        #    #
	0b00000001, 0b10010000, //        ##  #
	0b00001110, 0b01100000, //     ###  ##
	0b00010000, 0b00000000, //    #

	// @554 'S' (7 pixels wide)
	0b00001100, 0b01110000, //     ##   ###
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010001, 0b00001000, //    #   #    #
	0b00010001, 0b00001000, //    #   #    #
	0b00001110, 0b00110000, //     ###   ##

	// @568 'T' (9 pixels wide)
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00001000, //             #
	0b00011111, 0b11111000, //    ##########
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00001000, //             #

	// @586 'U' (8 pixels wide)
	0b00000111, 0b11111000, //      ########
	0b00001000, 0b00000000, //     #
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #
	0b00001000, 0b00000000, //     #
	0b00000111, 0b11111000, //      ########

	// @602 'V' (9 pixels wide)
	0b00000000, 0b00011000, //            ##
	0b00000000, 0b01100000, //          ##
	0b00000001, 0b10000000, //        ##
	0b00000110, 0b00000000, //      ##
	0b00011000, 0b00000000, //    ##
	0b00000110, 0b00000000, //      ##
	0b00000001, 0b10000000, //        ##
	0b00000000, 0b01100000, //          ##
	0b00000000, 0b00011000, //            ##

	// @620 'W' (13 pixels wide)
	0b00000000, 0b00111000, //           ###
	0b00000000, 0b11000000, //         ##
	0b00000111, 0b00000000, //      ###
	0b00011000, 0b00000000, //    ##
	0b00000111, 0b00000000, //      ###
	0b00000000, 0b11000000, //         ##
	0b00000000, 0b00111000, //           ###
	0b00000000, 0b11000000, //         ##
	0b00000111, 0b00000000, //      ###
	0b00011000, 0b00000000, //    ##
	0b00000111, 0b00000000, //      ###
	0b00000000, 0b11000000, //         ##
	0b00000000, 0b00111000, //           ###

	// @646 'X' (8 pixels wide)
	0b00011000, 0b00011000, //    ##      ##
	0b00000100, 0b00100000, //      #    #
	0b00000010, 0b01000000, //       #  #
	0b00000001, 0b10000000, //        ##
	0b00000001, 0b10000000, //        ##
	0b00000010, 0b01000000, //       #  #
	0b00000100, 0b00100000, //      #    #
	0b00011000, 0b00011000, //    ##      ##

	// @662 'Y' (9 pixels wide)
	0b00000000, 0b00011000, //            ##
	0b00000000, 0b00100000, //           #
	0b00000000, 0b01000000, //          #
	0b00000000, 0b10000000, //         #
	0b00011111, 0b00000000, //    #####
	0b00000000, 0b10000000, //         #
	0b00000000, 0b01000000, //          #
	0b00000000, 0b00100000, //           #
	0b00000000, 0b00011000, //            ##

	// @680 'Z' (6 pixels wide)
	0b00011000, 0b00001000, //    ##       #
	0b00010110, 0b00001000, //    # ##     #
	0b00010001, 0b00001000, //    #   #    #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b01101000, //    #     ## #
	0b00010000, 0b00011000, //    #       ##

	// @692 '[' (3 pixels wide)
	0b11111111, 0b11111000, // #############
	0b10000000, 0b00001000, // #           #
	0b10000000, 0b00001000, // #           #

	// @698 '\' (4 pixels wide)
	0b00000000, 0b00111000, //           ###
	0b00000001, 0b11000000, //        ###
	0b00001110, 0b00000000, //     ###
	0b01110000, 0b00000000, //  ###

	// @706 ']' (3 pixels wide)
	0b10000000, 0b00001000, // #           #
	0b10000000, 0b00001000, // #           #
	0b11111111, 0b11111000, // #############

	// @712 '^' (5 pixels wide)
	0b00000000, 0b00010000, //            #
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00000100, //              #
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00010000, //            #

	// @722 '_' (7 pixels wide)
	0b01000000, 0b00000000, //  #
	0b01000000, 0b00000000, //  #
	0b01000000, 0b00000000, //  #
	0b01000000, 0b00000000, //  #
	0b01000000, 0b00000000, //  #
	0b01000000, 0b00000000, //  #
	0b01000000, 0b00000000, //  #

	// @736 '`' (2 pixels wide)
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00010000, //            #

	// @740 'a' (7 pixels wide)
	0b00001110, 0b00000000, //     ###   
	0b00010001, 0b01000000, //    #   # #
	0b00010001, 0b01000000, //    #   # #
	0b00010001, 0b01000000, //    #   # #
	0b00010001, 0b01000000, //    #   # #
	0b00001111, 0b10000000, //     #####
	0b00010000, 0b00000000, //    #

	// @754 'b' (6 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00001000, 0b10000000, //     #   #
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00001111, 0b10000000, //     #####

	// @766 'c' (6 pixels wide)
	0b00001111, 0b10000000, //     #####
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00001000, 0b10000000, //     #   #

	// @778 'd' (6 pixels wide)
	0b00001111, 0b10000000, //     #####
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00001000, 0b10000000, //     #   #
	0b00011111, 0b11111000, //    ##########

	// @790 'e' (6 pixels wide)
	0b00001111, 0b10000000, //     #####
	0b00010010, 0b01000000, //    #  #  #
	0b00010010, 0b01000000, //    #  #  #
	0b00010010, 0b01000000, //    #  #  #
	0b00010010, 0b01000000, //    #  #  #
	0b00000011, 0b10000000, //       ###

	// @802 'f' (3 pixels wide)
	0b00000000, 0b01000000, //          #
	0b00011111, 0b11110000, //    #########
	0b00000000, 0b01001000, //          #  #

	// @808 'g' (6 pixels wide)
	0b00001111, 0b10000000, //     #####
	0b10010000, 0b01000000, // #  #     #
	0b10010000, 0b01000000, // #  #     #
	0b10010000, 0b01000000, // #  #     #
	0b10001000, 0b10000000, // #   #   #
	0b01111111, 0b11000000, //  #########

	// @820 'h' (5 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00000000, 0b10000000, //         #
	0b00000000, 0b01000000, //          #
	0b00000000, 0b01000000, //          #
	0b00011111, 0b10000000, //    ######

	// @830 'i' (1 pixels wide)
	0b00011111, 0b11001000, //    #######  #

	// @832 'j' (2 pixels wide)
	0b10000000, 0b00000000, // #
	0b01111111, 0b11001000, //  #########  #

	// @836 'k' (6 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00000010, 0b00000000, //       #
	0b00000011, 0b00000000, //       ##
	0b00000100, 0b10000000, //      #  #
	0b00001000, 0b01000000, //     #    #
	0b00010000, 0b00000000, //    #

	// @848 'l' (1 pixels wide)
	0b00011111, 0b11111000, //    ##########

	// @850 'm' (9 pixels wide)
	0b00011111, 0b11000000, //    #######
	0b00000000, 0b10000000, //         #
	0b00000000, 0b01000000, //          #
	0b00000000, 0b01000000, //          #
	0b00011111, 0b10000000, //    ######
	0b00000000, 0b10000000, //         #
	0b00000000, 0b01000000, //          #
	0b00000000, 0b01000000, //          #
	0b00011111, 0b10000000, //    ######

	// @868 'n' (5 pixels wide)
	0b00011111, 0b11000000, //    #######
	0b00000000, 0b10000000, //         #
	0b00000000, 0b01000000, //          #
	0b00000000, 0b01000000, //          #
	0b00011111, 0b10000000, //    ######

	// @878 'o' (6 pixels wide)
	0b00001111, 0b10000000, //     #####
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00001111, 0b10000000, //     #####

	// @890 'p' (6 pixels wide)
	0b11111111, 0b11000000, // ##########
	0b00001000, 0b10000000, //     #   #
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00001111, 0b10000000, //     #####

	// @902 'q' (6 pixels wide)
	0b00001111, 0b10000000, //     #####
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00001000, 0b10000000, //     #   #
	0b11111111, 0b11000000, // ##########

	// @914 'r' (3 pixels wide)
	0b00011111, 0b11000000, //    #######
	0b00000000, 0b10000000, //         #
	0b00000000, 0b01000000, //          #

	// @920 's' (5 pixels wide)
	0b00001001, 0b10000000, //     #  ##
	0b00010010, 0b01000000, //    #  #  #
	0b00010010, 0b01000000, //    #  #  #
	0b00010010, 0b01000000, //    #  #  #
	0b00001100, 0b10000000, //     ##  #

	// @930 't' (3 pixels wide)
	0b00000000, 0b01000000, //          #
	0b00001111, 0b11110000, //     ########
	0b00010000, 0b01000000, //    #     #

	// @936 'u' (5 pixels wide)
	0b00001111, 0b11000000, //     ######
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #
	0b00001000, 0b00000000, //     #
	0b00011111, 0b11000000, //    #######

	// @946 'v' (7 pixels wide)
	0b00000000, 0b11000000, //         ##
	0b00000011, 0b00000000, //       ##
	0b00001100, 0b00000000, //     ##
	0b00010000, 0b00000000, //    #
	0b00001100, 0b00000000, //     ##
	0b00000011, 0b00000000, //       ##
	0b00000000, 0b11000000, //         ##

	// @960 'w' (9 pixels wide)
	0b00000000, 0b11000000, //         ##
	0b00000111, 0b00000000, //      ###
	0b00011000, 0b00000000, //    ##
	0b00000111, 0b00000000, //      ###
	0b00000000, 0b11000000, //         ##
	0b00000111, 0b00000000, //      ###
	0b00011000, 0b00000000, //    ##
	0b00000111, 0b00000000, //      ###
	0b00000000, 0b11000000, //         ##

	// @978 'x' (6 pixels wide)
	0b00010000, 0b01000000, //    #     #
	0b00001000, 0b10000000, //     #   #
	0b00000111, 0b00000000, //      ###
	0b00000111, 0b00000000, //      ###
	0b00001000, 0b10000000, //     #   #
	0b00010000, 0b01000000, //    #     #

	// @990 'y' (7 pixels wide)
	0b10000000, 0b11000000, // #       ##
	0b10000011, 0b00000000, // #     ##
	0b01001100, 0b00000000, //  #  ##
	0b00110000, 0b00000000, //   ##
	0b00001100, 0b00000000, //     ##
	0b00000011, 0b00000000, //       ##
	0b00000000, 0b11000000, //         ##

	// @1004 'z' (4 pixels wide)
	0b00011000, 0b01000000, //    ##    #
	0b00010110, 0b01000000, //    # ##  #
	0b00010001, 0b01000000, //    #   # #
	0b00010000, 0b11000000, //    #    ##

	// @1012 '{' (5 pixels wide)
	0b00000010, 0b00000000, //       #
	0b00000010, 0b00000000, //       #
	0b01111101, 0b11110000, //  ##### #####
	0b10000000, 0b00001000, // #           #
	0b10000000, 0b00001000, // #           #

	// @1022 '|' (1 pixels wide)
	0b11111111, 0b11111000, // #############

	// @1024 '}' (5 pixels wide)
	0b10000000, 0b00001000, // #           #
	0b10000000, 0b00001000, // #           #
	0b01111101, 0b11110000, //  ##### #####
	0b00000010, 0b00000000, //       #
	0b00000010, 0b00000000, //       #

	// @1034 '~' (7 pixels wide)
	0b00000000, 0b00110000, //           ##
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00001000, //             #
	0b00000000, 0b00010000, //            #
	0b00000000, 0b00100000, //           #
	0b00000000, 0b00100000, //           #
	0b00000000, 0b00011000, //            ##

	// @1048 '?' (8 pixels wide)
	0b00000111, 0b11100000, //      ######
	0b00001000, 0b00010000, //     #      #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001100, //    #        ##
	0b00010000, 0b00001010, //    #        # #
	0b00001000, 0b00010000, //     #      #
	0b00000111, 0b11100000, //      ######

	// @1064 '?' (6 pixels wide)
	0b00001111, 0b10000000, //     #####
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01010000, //    #     # #
	0b00010000, 0b01001000, //    #     #  #
	0b00010000, 0b01000000, //    #     #
	0b00001111, 0b10000000, //     #####

	// @1076 '?' (9 pixels wide)
	0b00011000, 0b00000000, //    ##
	0b00000110, 0b00000000, //      ##
	0b00000011, 0b10000000, //       ###
	0b00000010, 0b01100000, //       #  ##
	0b00000010, 0b00011000, //       #    ##
	0b00000010, 0b01100000, //       #  ##
	0b01000011, 0b10000000, //  #    ###
	0b10100110, 0b00000000, // # #  ##
	0b10011000, 0b00000000, // #  ##

	// @1094 '?' (6 pixels wide)
	0b00001110, 0b00000000, //     ###   
	0b00010001, 0b01000000, //    #   # #
	0b00010001, 0b01000000, //    #   # #
	0b00010001, 0b01000000, //    #   # #
	0b01010001, 0b01000000, //  # #   # #
	0b10101111, 0b10000000, // # # #####
//	0b10010000, 0b00000000, // #  #

	// @1106'?' (8 pixels wide)
	0b00000111, 0b11100000, //      ######
	0b00001000, 0b00010000, //     #      #
	0b00010000, 0b00001000, //    #        #
	0b00010000, 0b00001100, //    #        ##
	0b00010000, 0b00001010, //    #        # #
	0b00010000, 0b00001000, //    #        #
	0b00001000, 0b00010000, //     #      #
	0b00000100, 0b00100000, //      #    #

	// @1122 '?' (6 pixels wide)
	0b00001111, 0b10000000, //     #####
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b01010000, //    #     # #
	0b00010000, 0b01001000, //    #     #  #
	0b00001000, 0b10000000, //     #   #

	// @1134 '?' (7 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00010000, 0b10001000, //    #    #   #
	0b01010000, 0b10001000, //  # #    #   #
	0b10110000, 0b10001000, // # ##    #   #
	0b10010000, 0b10001000, // #  #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b00001000, //    #        #

	// @1148 '?' (6 pixels wide)
	0b00001111, 0b10000000, //     #####
	0b01010010, 0b01000000, //  # #  #  #
	0b10110010, 0b01000000, // # ##  #  #
	0b10010010, 0b01000000, // #  #  #  #
	0b00010010, 0b01000000, //    #  #  #
	0b00000011, 0b10000000, //       ###
	 
	// @1160 '?' (7 pixels wide)
	0b00000010, 0b00000000, //       #
	0b00011111, 0b11111000, //    ##########
	0b00010000, 0b10000000, //    #    #
	0b00010000, 0b01000000, //    #     #
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #
	0b00010000, 0b00000000, //    #

	// @1174 '?' (3 pixels wide)
	0b00000010, 0b00000000, //       #
	0b00011111, 0b11111000, //    ##########
	0b00000000, 0b10000000, //         #

	// @1180 '?' (8 pixels wide)
	0b00011111, 0b11111000, //    ##########
	0b00000000, 0b00010000, //            #
	0b00000000, 0b01100000, //          ##
	0b00000000, 0b10000100, //         #    #
	0b00000001, 0b00000010, //        #      #
	0b00000110, 0b00000000, //      ##
	0b00001000, 0b00000000, //     #
	0b00011111, 0b11111000, //    ##########

	// @11960 '?' (5 pixels wide)
	0b00011111, 0b11000000, //    #######
	0b00000000, 0b10000000, //         #
	0b00000000, 0b01010000, //          # #
	0b00000000, 0b01001000, //          #  #
	0b00011111, 0b10000000, //    ######

	// @1206 '?' (7 pixels wide)
	0b00001100, 0b01110000, //     ##   ###
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001000, //    #    #   #
	0b00010000, 0b10001100, //    #    #   ##
	0b00010001, 0b00001010, //    #   #    # #
	0b00010001, 0b00001000, //    #   #    #
	0b00001110, 0b00110000, //     ###   ##

	// @1220 '?' (5 pixels wide)
	0b00001001, 0b10000000, //     #  ##
	0b00010010, 0b01000000, //    #  #  #
	0b00010010, 0b01010000, //    #  #  # #
	0b00010010, 0b01001000, //    #  #  #  #
	0b00001100, 0b10000000, //     ##  #

	// @1230 '?' (6 pixels wide)
	0b00011000, 0b00001000, //    ##       #
	0b00010110, 0b00001000, //    # ##     #
	0b00010001, 0b00001000, //    #   #    #
	0b00010000, 0b10001100, //    #    #   ##
	0b00010000, 0b01101010, //    #     ## # #
	0b00010000, 0b00011000, //    #       ##

	// @1242 '?' (4 pixels wide)
	0b00011000, 0b01000000, //    ##    #
	0b00010110, 0b01010000, //    # ##  # #
	0b00010001, 0b01001000, //    #   # #  #
	0b00010000, 0b11000000, //    #    ##

	// @1250 '?' (6 pixels wide)
	0b00011000, 0b00001000, //    ##       #
	0b00010110, 0b00001000, //    # ##     #
	0b00010001, 0b00001000, //    #   #    #
	0b00010000, 0b10001010, //    #    #   # #
	0b00010000, 0b01101000, //    #     ## #
	0b00010000, 0b00011000, //    #       ##

	// @1262 '?' (4 pixels wide)
	0b00011000, 0b01000000, //    ##    #
	0b00010110, 0b01000000, //    # ##  #
	0b00010001, 0b01010000, //    #   # # #
	0b00010000, 0b11000000, //    #    ##

	// @1270 bad char
	0b11111111, 0b11111111, // ################
	0b10000000, 0b00000001, // #              #
	0b10000000, 0b00000001, // #              #
	0b11111111, 0b11111111, // ################

};

const SH1106_CharDef_t SH1106_CharactersSans16_PL[] = {
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
	{7, 1206}, 		// ?
	{0, 0}, 		// 
	{0, 0}, 		// 
	{6, 1230}, 		// ?
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
	{5, 1220}, 		// ?
	{0, 0}, 		// 
	{0, 0}, 		// 
	{4, 1242}, 		// ?
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{7, 1160}, 		// ?
	{0, 0}, 		// 
	{9, 1076}, 		// ?
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{6, 1250}, 		// ?
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{3, 1174}, 		// ?
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{6, 1094}, 		// ?
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{4, 1262}, 		// ?
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{8, 1106}, 		// ?
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{7, 1134}, 		// ?
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{8, 1180}, 		// ?
	{0, 0}, 		// 
	{8, 1046}, 		// ?
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
	{6, 1122}, 		// ?
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{6, 1148}, 		// ?
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{0, 0}, 		// 
	{5, 1196}, 		// ?
	{0, 0}, 		// 
	{6, 1062}, 		// ?
	{4, 1270},		// bad char 244
};

const SH1106_FontDef_t SH1106_FontSans16_PL = {
	.Height				=	2,
	.Width				=	0,
	.Spacing			=	1,
	.FirstChar			=	' ',
	.LastChar			=	244,
	.Descriptors		=	SH1106_CharactersSans16_PL,
	.Bitmaps			=	SH1106_BitmapSans16_PL,
};