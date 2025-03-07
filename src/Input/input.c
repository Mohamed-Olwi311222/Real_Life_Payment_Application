#include "input.h"
static STD_RETURN_t get_card_name(user_t *const user);
static STD_RETURN_t get_card_number(user_t *const user);
static STD_RETURN_t get_card_expiration_date(user_t *const user);

/**
 * @brief: Get the User card details
 * @param user The address of type user_t to store the user's data
 * @return STD_SUCCESS if success otherwise STD_FAILED
 */
STD_RETURN_t get_card_details(user_t **user)
{
  STD_RETURN_t std_ret = STD_SUCCESS;

  std_ret = allocate_user_mem(user);
  if (STD_SUCCESS == std_ret)
  {
      std_ret = get_card_name(*user);
      if (STD_SUCCESS == std_ret)
      {
        std_ret = get_card_number(*user);
        if (STD_SUCCESS == std_ret)
        {
            std_ret = get_card_expiration_date(*user);
        }
      }
  }
  return (std_ret);
}

/**
 * @brief: Get the card name of the user using dynamic memory allocation
 * @param user The address of type user_t to store the user's data
 * @return STD_SUCCESS if success otherwise STD_FAILED
 */
static STD_RETURN_t get_card_name(user_t *const user)
{
  STD_RETURN_t std_ret = STD_SUCCESS;

  printf("Enter Card Holder name: ");
  /* fgets instead of scanf to avoid buffer overflow */
  fgets(user->card_holder_name, sizeof(char) * MAX_NAME_SIZE, stdin);
  /* Set the last character to null instead of newline character*/
  user->card_holder_name[strcspn(user->card_holder_name, "\n")] = '\0';
  printf("\n");
  return (std_ret);
}
/**
 * @brief: Get the pan number of the user using dynamic memory allocation
 * @param user The address of type user_t to store the user's data
 * @return STD_SUCCESS if success otherwise STD_FAILED
 */
static STD_RETURN_t get_card_number(user_t *const user)
{
  STD_RETURN_t std_ret = STD_SUCCESS;

  printf("Enter Card Pan number: ");
  /* fgets instead of scanf to avoid buffer overflow */
  fgets(user->pan_number, sizeof(char) * MAX_PAN_SIZE, stdin);
  /* Set the last character to null instead of newline character*/
  user->pan_number[strcspn(user->pan_number, "\n")] = '\0';
  printf("\n");
  return (std_ret);
}
/**
 * @brief: Get the expiration date of the user's card
 * @param user The address of type user_t to store the user's data
 * @return STD_SUCCESS if success otherwise STD_FAILED
 */
static STD_RETURN_t get_card_expiration_date(user_t *const user)
{
  STD_RETURN_t std_ret = STD_SUCCESS;

  printf("Enter Expiration date (in form of MMYY): ");
  fgets(user->expiration_date, sizeof(char) * MAX_EXP_DATE_SIZE, stdin);
  user->expiration_date[strcspn(user->expiration_date, "\n")] = '\0';
  printf("\n");

  return (std_ret);
}
/**
 * @brief: Allocate memory for the given address with the corrosponding size
 * @param addr The address to allocate memory for
 * @param addr_size The size of the needed memory
 * @return STD_SUCCESS if success otherwise STD_FAILED
 */
STD_RETURN_t allocate_mem(void **addr, uint8_t addr_size)
{
    STD_RETURN_t std_ret = STD_SUCCESS;

    *addr = malloc(addr_size);
    if (NULL == *addr)
    {
      std_ret = STD_FAILED;
    }
    return (std_ret);
}
STD_RETURN_t allocate_user_mem(user_t **user)
{
    STD_RETURN_t std_ret = STD_SUCCESS;

    std_ret = allocate_mem((void **)&(*user), sizeof(user_t));
    if (STD_SUCCESS == std_ret)
    {
      std_ret = allocate_mem((void **)&((*user)->card_holder_name), sizeof(char) * MAX_NAME_SIZE);
      if (STD_SUCCESS == std_ret)
      {
          std_ret = allocate_mem((void **)&((*user)->expiration_date), sizeof(char) * MAX_EXP_DATE_SIZE);
          if (STD_FAILED == std_ret)
          {
            free((*user)->card_holder_name);
          }
          else
          {
              std_ret = allocate_mem((void **)&((*user)->pan_number), sizeof(char) * MAX_PAN_SIZE);
              if (STD_FAILED == std_ret)
              {
                  free((*user)->card_holder_name);
                  free((*user)->expiration_date);
              }
          }
      }
    }
    // Handle memory allocation failures
    if (STD_FAILED == std_ret && NULL != *user)
    {
        free(*user);
        *user = NULL;
    }
    return (std_ret);
}
