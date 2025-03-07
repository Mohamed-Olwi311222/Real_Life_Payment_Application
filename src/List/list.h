/* 
 * File:   list.h
 * Author: Mohamed olwi
 *
 * Created: 2/3/2025 3:00:00 AM
 */
#ifndef LIST_H
#define LIST_H
/*----------------------------Header Files------------------------------------*/
#include "../std.h"
#include "../Input/input.h"
/*----------------------------Macros Declarations-----------------------------*/
/*----------------------------Data Types--------------------------------------*/

/**
 * struct node - A linked list nodes type
 * @data: The data to store in each node
 * @next: The pointer to the next node
 */
typedef struct node
{
  user_t *data;
  struct node *next;
} list_t;
/*----------------------------Function Prototypes-----------------------------*/
/**
 * @brief Appends a node to the list
 * @param head: the head of the list
 * @param user: The user data
 * @return: STD_SUCCESS if success, STD_FAILED if fail
 */
STD_RETURN_t append(list_t **head, user_t *user);
/**
 * @brief Frees the entire list
 * @param head: the head of the list
 * @return: STD_SUCCESS if success, STD_FAILED if fail
 */
STD_RETURN_t free_list(list_t **head);
#endif /* list.h */