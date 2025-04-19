
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  char	**str;
  int	size = 1;

  str = malloc(sizeof(char *) * (size + 1));
  str[size] = NULL;
  str[0] = "jsafkj";
  printf("%s\n%s\n%s\n", str[0], str[1], str[2]);
  return (0);
}
