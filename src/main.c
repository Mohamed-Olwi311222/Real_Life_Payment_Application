#include "main.h"


int main(void)
{
  user_t *user;
  
// load_data_from_file(list_t *head, const char *filename)
  get_card_details(&user);
  sign_in(user);
  printf("username is %s\n", user->card_holder_name);
  printf("pan number is %s\n", user->pan_number);
  printf("expiration number is %s\n", user->expiration_date);
  return (0);
}
