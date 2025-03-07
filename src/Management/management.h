/* 
 * File:   management.h
 * Author: Mohamed olwi
 *
 * Created: 2/3/2025 3:00:00 AM
 */
#ifndef MANAGEMENT_H
#define MANAGEMENT_H
/*----------------------------Header Files------------------------------------*/
#include "../Input/input.h"
#include "../std.h"
#include "../List/list.h"
/*----------------------------Macros Declarations-----------------------------*/

/*----------------------------Data Types--------------------------------------*/

/*----------------------------Function Prototypes-----------------------------*/

/**
 * @brief: Sign in with the user credentials
 * @param user The users data
 * @return STD_SUCCESS if success otherwise STD_FAILED
 */
STD_RETURN_t sign_in(user_t *user);
STD_RETURN_t load_data_from_file(list_t **head, const char *filename);
#endif /* management.h */