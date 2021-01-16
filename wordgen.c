#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define USAGE printf("Usage: %s <Word Length>\n" \
              "`\033[3mWord Length\033[0m` should be >0 and ≤%d\n\n" \
              "For example:\n\n" \
              "$ %s 8\n" \
              "  bacalhau\n", argv[0], MAX_WORDSIZE, argv[0])

#define MAX_WORDSIZE 512
#define CONS_COMB 35 // Amount of consonants combinations

// 20 consonants
const char consonants[] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'y', 'z'};
// 5 vowels
const char vowels[] = {'a', 'e', 'i', 'o', 'u'};
// 33 Allowed consonants combinations
const char allowed_conscomb[][2] = {
  "bl", "fr", "sc", "sq", "ck",
  "br", "gl", "sk", "st", "dg",
  "cl", "gr", "sl", "sw", "ng",
  "cr", "kn", "sm", "tr", "nk",
  "dr", "pl", "sn", "tw", "wh",
  "fl", "pr", "sp", "wr", "nh",
  "ch", "ph", "sh", "th", "lh"
};


// Check if a consonants combination IS NOT in `consonants_combinations` array
bool disall_ccomb(char a, char b){
  for(int i=0; i<CONS_COMB; i++){
    if(a == allowed_conscomb[i][0] && b == allowed_conscomb[i][1]){
      return false;
    }
  }
  return true;
}

char rndvowel(){ return vowels[rand()%5]; }
char rndcons(){ return consonants[rand()%20]; }

int main(int argc, char **argv){
  // Check if arguments are valid
  {
    if(argc!=2) goto WrongArgs;

    size_t arglen = strlen(argv[1]);

    for(int i=0; i<arglen; i++){
      if(!isdigit(argv[1][i])){
        goto WrongArgs;
      }
    }
  }

  int wordlen = atoi(argv[1]);
  if(wordlen<=0 || wordlen > MAX_WORDSIZE)
      goto WrongArgs;
  
  // Set random seed based on nsec (just to have a nice seed)
  {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    srand(ts.tv_nsec);
  }
  
  int i, fcons, fvowel;
  fcons = fvowel = 0;

  char word[MAX_WORDSIZE];
  word[wordlen-1] = 0;
  word[MAX_WORDSIZE] = 0;

  for(i=0; i<wordlen; i++){

    // There can only be two consecutive letters of the same type (consonants or vowels)
    // In case there are less than two consecutive letters of the same type, will be chosen a random letter (consonant or vowel)
    // If there are 2 consecutive consonants, a vowel is insert in the word

    if((fcons<2 && fvowel<2 && rand()%2) || fcons==2){ 
      word[i] = rndvowel();
      fvowel++;
      fcons = 0;

    } else {
      word[i] = rndcons();
      fcons++;
      fvowel = 0;
    }
    
    // There are two consecutive consonants :O
    if(fcons==2){

      // Check if a consonants combination is allowed
      // If the combination isn't allowed, a new one will be generated
      while(disall_ccomb(word[i-1], word[i])){
        word[i-1] = rndcons();
        word[i] = rndcons();
      }
    }
  }
  
  printf("%.*s\n", wordlen, word);
  // printf("%s\n", word);
  return 0;

WrongArgs:
  USAGE;
  return 127;
}
