#include "console8x6.h"

const uint8_t SH1106_BitmapConsole8x6[]  =
{
	0b00000000, //
	0b00000000, //
	0b00000000, //  space
	0b00000000, //
	0b00000000, //

	0b00000000, //
	0b00000000, //
	0b01011111, //  # #####
	0b00000000, //
	0b00000000, //
	
	0b00000000, //
	0b00000111, //      ###
	0b00000000, //
	0b00000111, //      ###
	0b00000000, //
	
	0b00010100, //    # #
	0b01111111, //  #######
	0b00010100, //    # #
	0b01111111, //  #######
	0b00010100, //    # #
	
	0b00100100, //   #  #
	0b00101010, //   # # #
	0b01111111, //  #######
	0b00101010, //   # # #
	0b00010010, //    #  #
	
	0b00100011, //   #   ##
	0b00010011, //    #  ##
	0b00001000, //     #
	0b01100100, //  ##  #
	0b01100010, //  ##   #
	
	0b00110110, //   ## ##
	0b01001001, //  #  #  #
	0b01010101, //  # # # #
	0b00100010, //   #   #
	0b01010000, //  # #
	
	0b00000000, //
	0b00000101, //      # #
	0b00000011, //       ##
	0b00000000, //
	0b00000000, //
	
	0b00000000, //
	0b00011100, //    ###
	0b00100010, //   #   #
	0b01000001, //  #     #
	0b00000000, //
	
	0b00000000, //
	0b01000001, //  #     #
	0b00100010, //   #   #
	0b00011100, //    ###
	0b00000000, //
	
	0b00001000, //     #
	0b00101010, //   # # #
	0b00011100, //    ###
	0b00101010, //   # # #
	0b00001000, //     #
	
	0b00001000, //     #
	0b00001000, //     #
	0b00111110, //   #####
	0b00001000, //     #
	0b00001000, //     #
	
	0b00000000, //
	0b01010000, //  # #
	0b00110000, //   ##
	0b00000000, //
	0b00000000, //
	
	0b00001000, //     #
	0b00001000, //     #
	0b00001000, //     #
	0b00001000, //     #
	0b00001000, //     #
	
	0b00000000, //
	0b01100000, //  ##
	0b01100000, //  ##
	0b00000000, //
	0b00000000, //
	
	0b00100000, //   #
	0b00010000, //    #
	0b00001000, //     #
	0b00000100, //      #
	0b00000010, //       #
	
	0b00111110, //   #####
	0b01010001, //  # #   #
	0b01001001, //  #  #  #
	0b01000101, //  #   # #
	0b00111110, //   #####
	
	0b00000000, //
	0b01000010, //  #    #
	0b01111111, //  #######
	0b01000000, //  #
	0b00000000, //
	
	0b01000010, //  #    #
	0b01100001, //  ##    #
	0b01010001, //  # #   #
	0b01001001, //  #  #  #
	0b01000110, //  #   ##
	
	0b00100001, //   #    #
	0b01000001, //  #     #
	0b01000101, //  #   # #
	0b01001011, //  #  # ##
	0b00110001, //   ##   #
	
	0b00011000, //    ##
	0b00010100, //    # #
	0b00010010, //    #  #
	0b01111111, //  #######
	0b00010000, //    #
	
	0b00100111, //   #  ###
	0b01000101, //  #   # #
	0b01000101, //  #   # #
	0b01000101, //  #   # #
	0b00111001, //   ###  #
	
	0b00111100, //   ####
	0b01001010, //  #  # #
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b00110000, //   ##
	
	0b00000001, //        #
	0b01110001, //  ###   #
	0b00001001, //     #  #
	0b00000101, //      # #
	0b00000011, //       ##
	
	0b00110110, //   ## ##
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b00110110, //   ## ##
	
	0b00000110, //      ##
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b00101001, //   # #  #
	0b00011110, //    ####
	
	0b00000000, //
	0b00110110, //   ## ##
	0b00110110, //   ## ##
	0b00000000, //
	0b00000000, //
	
	0b00000000, //
	0b01010110, //  # # ##
	0b00110110, //   ## ##
	0b00000000, //
	0b00000000, //
	
	0b00000000, //
	0b00001000, //     #
	0b00010100, //    # #
	0b00100010, //   #   #
	0b01000001, //  #     #
	
	0b00010100, //    # #
	0b00010100, //    # #
	0b00010100, //    # #
	0b00010100, //    # #
	0b00010100, //    # #
	
	0b01000001, //  #     #
	0b00100010, //   #   #
	0b00010100, //    # #
	0b00001000, //     #
	0b00000000, //
	
	0b00000010, //       #
	0b00000001, //        #
	0b01010001, //  # #   #
	0b00001001, //     #  #
	0b00000110, //      ##
	
	0b00110010, //   ##  #
	0b01001001, //  #  #  #
	0b01111001, //  ####  #
	0b01000001, //  #     #
	0b00111110, //   #####
	
	0b01111110, //  ######
	0b00010001, //    #   #
	0b00010001, //    #   #
	0b00010001, //    #   #
	0b01111110, //  ######
	
	0b01111111, //  #######
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b00110110, //   ## ##
	
	0b00111110, //   #####
	0b01000001, //  #     #
	0b01000001, //  #     #
	0b01000001, //  #     #
	0b00100010, //   #   #
	
	0b01111111, //  #######
	0b01000001, //  #     #
	0b01000001, //  #     #
	0b00100010, //   #   #
	0b00011100, //    ###
	
	0b01111111, //  #######
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b01000001, //  #     #
	
	0b01111111, //  #######
	0b00001001, //     #  #
	0b00001001, //     #  #
	0b00000001, //        #
	0b00000001, //        #
	
	0b00111110, //   #####
	0b01000001, //  #     #
	0b01000001, //  #     #
	0b01010001, //  # #   #
	0b00110010, //   ##  #
	
	0b01111111, //  #######
	0b00001000, //     #
	0b00001000, //     #
	0b00001000, //     #
	0b01111111, //  #######
	
	0b00000000, //
	0b01000001, //  #     #
	0b01111111, //  #######
	0b01000001, //  #     #
	0b00000000, //
	
	0b00100000, //   #
	0b01000000, //  #
	0b01000001, //  #     #
	0b00111111, //   ######
	0b00000001, //        #
	
	0b01111111, //  #######
	0b00001000, //     #
	0b00010100, //    # #
	0b00100010, //   #   #
	0b01000001, //  #     #
	
	0b01111111, //  #######
	0b01000000, //  #
	0b01000000, //  #
	0b01000000, //  #
	0b01000000, //  #
	
	0b01111111, //  #######
	0b00000010, //       #
	0b00000100, //      #
	0b00000010, //       #
	0b01111111, //  #######
	
	0b01111111, //  #######
	0b00000100, //      #
	0b00001000, //     #
	0b00010000, //    #
	0b01111111, //  #######
	
	0b00111110, //   #####
	0b01000001, //  #     #
	0b01000001, //  #     #
	0b01000001, //  #     #
	0b00111110, //   #####
	
	0b01111111, //  #######
	0b00001001, //     #  #
	0b00001001, //     #  #
	0b00001001, //     #  #
	0b00000110, //      ##
	
	0b00111110, //   #####
	0b01000001, //  #     #
	0b01010001, //  # #   #
	0b00100001, //   #    #
	0b01011110, //  # ####
	
	0b01111111, //  #######
	0b00001001, //     #  #
	0b00011001, //    ##  #
	0b00101001, //   # #  #
	0b01000110, //  #   ##
	
	0b01000110, //  #   ##
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b00110001, //   ##   #
	
	0b00000001, //        #
	0b00000001, //        #
	0b01111111, //  #######
	0b00000001, //        #
	0b00000001, //        #
	
	0b00111111, //   ######
	0b01000000, //  #
	0b01000000, //  #
	0b01000000, //  #
	0b00111111, //   ######
	
	0b00011111, //    #####
	0b00100000, //   #
	0b01000000, //  #
	0b00100000, //   #
	0b00011111, //    #####
	
	0b01111111, //  #######
	0b00100000, //   #
	0b00011000, //    ##
	0b00100000, //   #
	0b01111111, //  #######
	
	0b01100011, //  ##   ##
	0b00010100, //    # #
	0b00001000, //     #
	0b00010100, //    # #
	0b01100011, //  ##   ##
	
	0b00000011, //       ##
	0b00000100, //      #
	0b01111000, //  ####
	0b00000100, //      #
	0b00000011, //       ##
	
	0b01100001, //  ##    #
	0b01010001, //  # #   #
	0b01001001, //  #  #  #
	0b01000101, //  #   # #
	0b01000011, //  #    ##
	
	0b00000000, //
	0b00000000, //
	0b01111111, //  #######
	0b01000001, //  #     #
	0b01000001, //  #     #
	
	0b00000010, //       #
	0b00000100, //      #
	0b00001000, //     #
	0b00010000, //    #
	0b00100000, //   #
	
	0b01000001, //  #     #
	0b01000001, //  #     #
	0b01111111, //  #######
	0b00000000, //
	0b00000000, //
	
	0b00000100, //      #
	0b00000010, //       #
	0b00000001, //        #
	0b00000010, //       #
	0b00000100, //      #
	
	0b01000000, //  #
	0b01000000, //  #
	0b01000000, //  #
	0b01000000, //  #
	0b01000000, //  #
	
	0b00000000, //
	0b00000001, //        #
	0b00000010, //       #
	0b00000100, //      #
	0b00000000, //
	
	0b00100000, //   #
	0b01010100, //  # # #
	0b01010100, //  # # #
	0b01010100, //  # # #
	0b01111000, //  ####
	
	0b01111111, //  #######
	0b01001000, //  #  #
	0b01000100, //  #   #
	0b01000100, //  #   #
	0b00111000, //   ###
	
	0b00111000, //   ###
	0b01000100, //  #   #
	0b01000100, //  #   #
	0b01000100, //  #   #
	0b00100000, //   #
	
	0b00111000, //   ###
	0b01000100, //  #   #
	0b01000100, //  #   #
	0b01001000, //  #  #
	0b01111111, //  #######
	
	0b00111000, //   ###
	0b01010100, //  # # #
	0b01010100, //  # # #
	0b01010100, //  # # #
	0b00011000, //    ##
	
	0b00001000, //     #
	0b01111110, //  ######
	0b00001001, //     #  #
	0b00000001, //        #
	0b00000010, //       #
	
	0b00001000, //     #
	0b00010100, //    # #
	0b01010100, //  # # #
	0b01010100, //  # # #
	0b00111100, //   ####
	
	0b01111111, //  #######
	0b00001000, //     #
	0b00000100, //      #
	0b00000100, //      #
	0b01111000, //  ####
	
	0b00000000, //
	0b01000100, //  #   #
	0b01111101, //  ##### #
	0b01000000, //  #
	0b00000000, //
	
	0b00100000, //   #
	0b01000000, //  #
	0b01000100, //  #   #
	0b00111101, //   #### #
	0b00000000, //
	
	0b00000000, //
	0b01111111, //  #######
	0b00010000, //    #
	0b00101000, //   # #
	0b01000100, //  #   #
	
	0b00000000, //
	0b01000001, //  #     #
	0b01111111, //  #######
	0b01000000, //  #
	0b00000000, //
	
	0b01111100, //  #####
	0b00000100, //      #
	0b00011000, //    ##
	0b00000100, //      #
	0b01111000, //  ####
	
	0b01111100, //  #####
	0b00001000, //     #
	0b00000100, //      #
	0b00000100, //      #
	0b01111000, //  ####
	
	0b00111000, //   ###
	0b01000100, //  #   #
	0b01000100, //  #   #
	0b01000100, //  #   #
	0b00111000, //   ###
	
	0b01111100, //  #####
	0b00010100, //    # #
	0b00010100, //    # #
	0b00010100, //    # #
	0b00001000, //     #
	
	0b00001000, //     #
	0b00010100, //    # #
	0b00010100, //    # #
	0b00011000, //    ##
	0b01111100, //  #####
	
	0b01111100, //  #####
	0b00001000, //     #
	0b00000100, //      #
	0b00000100, //      #
	0b00001000, //     #
	
	0b01001000, //  #  #
	0b01010100, //  # # #
	0b01010100, //  # # #
	0b01010100, //  # # #
	0b00100100, //   #  #
	
	0b00000100, //      #
	0b00111111, //   ######
	0b01000100, //  #   #
	0b01000000, //  #
	0b00100000, //   #
	
	0b00111100, //   ####
	0b01000000, //  #
	0b01000000, //  #
	0b00100000, //   #
	0b01111100, //  #####
	
	0b00011100, //    ###
	0b00100000, //   #
	0b01000000, //  #
	0b00100000, //   #
	0b00011100, //    ###
	
	0b00111100, //   ####
	0b01000000, //  #
	0b00110000, //   ##
	0b01000000, //  #
	0b00111100, //   ####
	
	0b01000100, //  #   #
	0b00101000, //   # #
	0b00010000, //    #
	0b00101000, //   # #
	0b01000100, //  #   #
	
	0b00001100, //     ##
	0b01010000, //  # #
	0b01010000, //  # #
	0b01010000, //  # #
	0b00111100, //   ####
	
	0b01000100, //  #   #
	0b01100100, //  ##  #
	0b01010100, //  # # #
	0b01001100, //  #  ##
	0b01000100, //  #   #
	
	0b00000000, //
	0b00001000, //     #
	0b00110110, //   ## ##
	0b01000001, //  #     #
	0b00000000, //
	
	0b00000000, //
	0b00000000, //
	0b01111111, //  #######
	0b00000000, //
	0b00000000, //
	
	0b00000000, //
	0b01000001, //  #     #
	0b00110110, //   ## ##
	0b00001000, //     #
	0b00000000, //

	0b00000010, //       #
	0b00000001, //        #
	0b00000010, //       #
	0b00000001, //        #
	0b00000000, //

	0b11111111, // ########
	0b10000001, // #      #
	0b10000001, // #      #
	0b10000001, // #      #
	0b11111111, // ########
};

const SH1106_FontDef_t SH1106_FontConsole8x6 = {
	.Height				=	1,
	.Width				=	5,
	.Spacing			=	1,
	.FirstChar			=	' ',
	.LastChar			=	127,
	.Descriptors		=	0,
	.Bitmaps			=	SH1106_BitmapConsole8x6,
};