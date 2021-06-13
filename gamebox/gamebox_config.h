#if COMPONENT_GAMEBOX
#ifndef GAMEBOX_CONFIG_H_
#define GAMEBOX_CONFIG_H_

// ========================================
// GameBox4809
// ========================================

#if PRODUCT_GAMEBOX4809
	
	// Keyboard pinout
	#define GB_KEY_PORT				PORTA
	#define GB_KEY_VPORT			VPORTA
	#define GB_KEY_UP				PIN6_bm
	#define GB_KEY_DOWN				PIN5_bm
	#define GB_KEY_LEFT				PIN4_bm
	#define GB_KEY_RIGHT			PIN7_bm
	#define GP_KEY_OK				PIN2_bm
	#define GB_KEY_ESCAPE			PIN1_bm
	#define GB_KEY_A				PIN0_bm
	#define GB_KEY_B				PIN3_bm
	#define GB_KEY_QUEUE_LENGTH		16
	
	#define GP_CONFIG_DONE
	
#endif

// ========================================
// Error handling
// ========================================

#ifndef GP_CONFIG_DONE
	#error "Missing config"
#endif

#endif /* GAMEBOX_CONFIG_H_ */
#endif
