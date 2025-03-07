/* 
 * File:   functions.h
 * Author: Mohamed olwi
 *
 * Created: 2/3/2025 3:00:00 AM
 */
#ifndef FUNCTIONS_H
#define	FUNCTIONS_H
/*----------------------------Header Files------------------------------------*/
#include "../std.h"
/*----------------------------Macros Declarations-----------------------------*/
#define MAX_NAME_SIZE                             (uint8_t)0x1E      /* Maximum size of the user's name (29 + NULL) */
#define MAX_PAN_SIZE                              (uint8_t)0x11      /* Maximum size of the user's pan number (16 + NULL) */
#define MAX_EXP_DATE_SIZE                         (uint8_t)0x05      /* Maximum size of the user's card expiration date (4 + NULL) */
/*----------------------------Data Types--------------------------------------*/

/**
 * struct user_t - A Struct to hold the user account
 * @card_holder_name: The name written on the user's card
 * @pan_number: The number written on the user*s card 
 * @expiration_date: The expiration date of the user's card
 */
typedef struct 
{
  char *card_holder_name;
  char *pan_number;
  char *expiration_date;
} user_t;
/*----------------------------Function Prototypes-----------------------------*/

/**
 * @brief: Get the User card details
 * @param user The address of type user_t to store the user's data
 * @return STD_SUCCESS if success otherwise STD_FAILED
 */
STD_RETURN_t get_card_details(user_t **user);
/**
 * @brief: Allocate memory for the given address with the corrosponding size
 * @param addr The address to allocate memory for
 * @param addr_size The size of the needed memory
 * @return STD_SUCCESS if success otherwise STD_FAILED
 */
STD_RETURN_t allocate_mem(void **addr, uint8_t addr_size);
STD_RETURN_t allocate_user_mem(user_t **user);
#endif	/* functions.h */
