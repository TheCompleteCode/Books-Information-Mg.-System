void convertToLower(string & str) {
  for(int i=0; str[i]!='\0'; i++) {
    str[i] = static_cast<char>(tolower(str[i]));
  }
  return;
}

#include "BookNode.h"
#include "CategoryNode.h"
#include "BookList.h"
