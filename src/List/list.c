#include "list.h"

uint16_t list_len = 0;

static STD_RETURN_t create_new_node(list_t **node, const user_t *const data);
static STD_RETURN_t delete_node(list_t *node, user_t *const data);
/**
 * @brief create a new newnode
 * @param node: the address to return the allocated node
 * @param data: pointer to the data
 * @return: STD_SUCCESS if success, STD_FAILED if fail
 */
static STD_RETURN_t create_new_node(list_t **node, const user_t *const data)
{
    STD_RETURN_t ret_status = STD_SUCCESS;

    if (NULL == node || NULL == data)
    {
        ret_status = STD_FAILED;
    }
    else
    {
        *node = malloc(sizeof(list_t));
        if (NULL != *node)
        {
            (*node)->data = malloc(sizeof(user_t));
            if (NULL != (*node)->data)
            {
                (*node)->data->card_holder_name = strdup(data->card_holder_name);
                (*node)->data->pan_number = strdup(data->pan_number);
                (*node)->data->expiration_date = strdup(data->expiration_date);
                (*node)->next = NULL;
                list_len++;
            }
            else
            {
                free(*node);
                *node = NULL;
                ret_status = STD_FAILED;
            }
        }
        else
        {
            ret_status = STD_FAILED;
        }
    }
    return (ret_status);
}
/**
 * @brief Deletes a node
 * @param node: the address to return the data which was stored in the node
 * @param addr: The address to return the deleted node
 * @return: STD_SUCCESS if success, STD_FAILED if fail
 */

 static STD_RETURN_t delete_node(list_t *node, user_t *const data)
{
    STD_RETURN_t ret_status = STD_SUCCESS;

    if (NULL == node)
    {
        ret_status = STD_FAILED;
    }
    else
    {
        if (NULL != data)
        {
            /* make a copy of the data to store into the node */
            memcpy (data, node->data, sizeof(user_t));
        }
        /* Clear the next pointer */
        node->next = NULL;
        /* free the allocated memory of the node */
        free(node->data);
        free(node);
        list_len--;
    }
    return (ret_status);
}
/**
 * @brief Appends a node to the list
 * @param head: the head of the list
 * @param user: The user data
 * @return: STD_SUCCESS if success, STD_FAILED if fail
 */
STD_RETURN_t append(list_t **head, user_t *user)
{
    STD_RETURN_t std_ret = STD_SUCCESS;
    list_t *newnode = NULL;
    list_t *temp = NULL;

    if (NULL == head || NULL == user)
    {
        std_ret = STD_FAILED;
    }
    else
    {
        std_ret = create_new_node(&newnode, user);
        if (STD_SUCCESS == std_ret)
        {
            if (NULL == *head)
            {
                *head = newnode;
            }
            else
            {
                temp = *head;
                while (NULL != temp->next)
                {
                    temp = temp->next;
                }
                temp->next = newnode;
            }
        }
    }
    return (std_ret);
}
/**
 * @brief Deletes the last node (tail)
 * @param head: the head of the list
 * @param user: The address to store the node data
 * @return: STD_SUCCESS if success, STD_FAILED if fail
 */
STD_RETURN_t delete_tail(list_t **head, user_t *user)
{
    STD_RETURN_t std_ret = STD_SUCCESS;
    list_t *temp = NULL, *prev = NULL;

    if (head == NULL || *head == NULL || user == NULL)
    {
        std_ret = STD_FAILED;
    }
    else
    {
        /* Only one node in the list */
        if (temp->next == NULL) 
        {
            memcpy(user, temp->data, sizeof(*user));
            free(temp->data);
            free(temp);
            *head = NULL;
        }
        else
        {
            while (temp->next != NULL)
            {
                prev = temp;
                temp = temp->next;
            }
            memcpy(user, temp->data, sizeof(*user));
            free(temp->data);
            free(temp);
            prev->next = NULL;
        }
    }
    return (std_ret);
}
/**
 * @brief Frees the entire list
 * @param head: the head of the list
 * @return: STD_SUCCESS if success, STD_FAILED if fail
 */
STD_RETURN_t free_list(list_t **head)
{
    STD_RETURN_t std_ret = STD_SUCCESS;
    list_t *node = NULL, *next = NULL;

    if (head == NULL || *head == NULL)
    {
        std_ret = STD_FAILED;
    }
    else
    {
        node = *head;
        while (node != NULL)
        {
            next = node->next;
            free(node->data);
            free(node);
            node = next;
        }
        *head = NULL;
    }
    return (std_ret);
}