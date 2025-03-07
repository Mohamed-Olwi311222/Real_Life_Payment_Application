#include "management.h"

static const char *users_data_txt = "UserData/users.txt";
static const char *users_transactions_txt = "UserData/transactions.txt";
static list_t *users_data_list = NULL;
static list_t *users_transactions_list = NULL;

static STD_RETURN_t create_new_file(const user_t *const user, const char *filename);
static STD_RETURN_t check_account_details(FILE *fptr, const user_t *const user);
static STD_RETURN_t compare_data(const user_t *const user1, const user_t *const user2);
inline static STD_RETURN_t compare_strings(const char *const s1, const char *const s2);
static STD_RETURN_t search_list(list_t *head, user_t *user);
static void free_user_type(user_t *user);
/* Function to trim leading and trailing spaces */
#include <ctype.h>
void trim_spaces(char *str) {
  char *end;

  // Trim leading spaces
  while (isspace((unsigned char)*str)) str++;

  // Trim trailing spaces
  if (*str) {  // Ensure string is not empty
      end = str + strlen(str) - 1;
      while (end > str && isspace((unsigned char)*end)) end--;
      *(end + 1) = '\0';  // Null-terminate after last non-space character
  }
}
/**
 * @brief: Sign in with the user credentials
 * @param user The users data
 * @return STD_SUCCESS if success otherwise STD_FAILED
 */
STD_RETURN_t sign_in(user_t *user)
{
    STD_RETURN_t std_ret = STD_SUCCESS;

    if (NULL == user)
    {
        std_ret = STD_FAILED;
    }
    else
    {
       /* Load data from the file and save it in the users_data_list */
       std_ret = load_data_from_file(&users_data_list, users_data_txt);
       if (STD_SUCCESS == std_ret)
       {
            std_ret = search_list(users_data_list, user);
            if (std_ret == STD_SUCCESS)
            {
                printf("VALID!!!\n");
                //TODO: the data is valid 
            }
       }
    }
    return (std_ret);
}
static STD_RETURN_t search_list(list_t *head, user_t *user)
{
    STD_RETURN_t std_ret = STD_FAILED;
    list_t *temp = NULL;

    if (NULL == head || NULL == user)
    {
        std_ret = STD_FAILED;
    }
    else
    {
        temp = head;
        while (NULL != temp)
        {
            std_ret = compare_data(temp->data, user);
            if (STD_SUCCESS == std_ret)
            {
                break;
            }
            temp = temp->next;
        }
    }
    return (std_ret);
}
/**
 * @brief: Create a new file
 * @return STD_SUCCESS if success otherwise STD_FAILED
 */
static STD_RETURN_t create_new_file(const user_t *const user, const char *filename)
{
    STD_RETURN_t std_ret = STD_SUCCESS;
    FILE *fptr;

    /* file did not open so create a new file to store the users data */
    fptr = fopen(filename, "w");
    if (NULL != fptr)
    {
        if (NULL != user)
        {
            /* Close the file */
            printf("No Saved Users in the system, will save it now\n");
            /* output the user data in the file with left alignement */
            fprintf(fptr, "%-29s ,%-16s, %-4s\n", user->card_holder_name, user->pan_number, user->expiration_date);
        }

        fclose(fptr);
    }
    else
    {
        /* failed to create a new file */
        std_ret = STD_FAILED;
    }
    return (std_ret);
}
/**
 * @brief: Check account details and compare it with the given one
 * @param fptr The file pointer
 * @param user The user given details
 * @return STD_SUCCESS if success otherwise STD_FAILED
 */
static STD_RETURN_t check_account_details(FILE *fptr, const user_t *const user)
{
    STD_RETURN_t std_ret = STD_SUCCESS;
    uint8_t res = 0;
    user_t *temp_user = NULL;

    std_ret = allocate_user_mem(&temp_user);
    if (STD_SUCCESS == std_ret)
    {
        while (3 != res)
        {
            res = fscanf(fptr, "%29[^,]s %16[^,]s %4[^\n]s", temp_user->card_holder_name, temp_user->pan_number, temp_user->expiration_date);
            std_ret = compare_data(user, temp_user);
            if (STD_SUCCESS == std_ret)
            {
                /* User Data has been found */
                //TODO: DO something when the data is found
                break;
            }
        }
        free(temp_user->card_holder_name);
        free(temp_user->pan_number);
        free(temp_user->expiration_date);
    }
    return (std_ret);
}

/**
 * @brief: Compare 2 users with each other
 * @param user1 The first user
 * @param user2 The second user
 * @return STD_SUCCESS if success otherwise STD_FAILED
 */
static STD_RETURN_t compare_data(const user_t *const user1, const user_t *const user2)
{
    STD_RETURN_t std_ret = STD_FAILED;

    if (STD_SUCCESS == compare_strings(user1->card_holder_name, user2->card_holder_name) &&
    STD_SUCCESS == compare_strings(user1->pan_number, user2->pan_number) &&
    STD_SUCCESS == compare_strings(user1->expiration_date, user2->expiration_date))
    {
        std_ret = STD_SUCCESS;
    }
    return(std_ret);
}
/**
 * @brief: Compare 2 Strings with each other
 * @param s1 The first string
 * @param s2 The second string
 * @return STD_SUCCESS if success otherwise STD_FAILED
 */
inline static STD_RETURN_t compare_strings(const char *const s1, const char *const s2)
{
    STD_RETURN_t std_ret = STD_SUCCESS;

    if (0 != strcmp(s1, s2))
    {
        std_ret = STD_FAILED;
    }
    return (std_ret);
}

STD_RETURN_t load_data_from_file(list_t **head, const char *filename)
{
    STD_RETURN_t std_ret = STD_SUCCESS;
    FILE *fptr = NULL;
    char buffer[55];
    user_t *temp_user = NULL;

    if (NULL == filename)
    {
        std_ret = STD_FAILED;
    }
    else
    {
        fptr = fopen(filename, "r");
        if (NULL == fptr)
        {
            /* no file exists, create a new file */
            std_ret = create_new_file(NULL, users_data_txt);
            if (STD_FAILED == std_ret)
            {
                perror("Failed to create a new file\n");
            }
            /* Failed to read data as the file doesnt exist */
            std_ret = STD_FAILED;
        }
        else
        {
            std_ret = allocate_user_mem(&temp_user);
            if (STD_SUCCESS == std_ret)
            {
                /* Read the data from the file and store it in the list */
                while (NULL != fgets(buffer, sizeof(buffer), fptr))
                {
                    buffer[strcspn(buffer, "\r\n")] = '\0';
                    if (3 == sscanf(buffer, "%[^,], %[^,], %4s", 
                        temp_user->card_holder_name, temp_user->pan_number, temp_user->expiration_date))
                        {
                            trim_spaces(temp_user->card_holder_name);
                            trim_spaces(temp_user->pan_number);
                            trim_spaces(temp_user->expiration_date);
                            std_ret = append(head, temp_user);
                            if (STD_FAILED == std_ret)
                            {
                                free_list(head);
                                break;
                            }
                        }
                }
                free_user_type(temp_user);
            }
            fclose(fptr);
        }
    }
    return (std_ret);
}
static void free_user_type(user_t *user)
{
   if (NULL != user)
   {
        free(user->card_holder_name);
        free(user->pan_number);
        free(user->expiration_date);
        free(user);
   }
}