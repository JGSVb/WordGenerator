#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define CONS_COMB 35 // Amount of consonants combinations

#define RVOWEL vowels[rand() % 5]
#define RCONSONANT consonants[rand() % 20]

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



// Check if a consonants combination is NOT in `consonants_combinations` array
bool sla(char a, char b){
  for(int i=0; i<CONS_COMB; i++){
    if(a == allowed_conscomb[i][0] && b == allowed_conscomb[i][1]){
      return false;
    }
  }
  return true;
}

char rndvowel(){ return vowels[rand()%5]; }
char rndcons()){ return consonants[rand()%20]; }

// Converts a string to an unsigned integer
// I know I can use atoi but I want to do this from scratch

// -----------------------------
//
// Essa parte ainda não terminei
//
// -----------------------------
const char numbers[] = "0123456789";
unsigned int struint(char* string, int size){
  int i, k;
  unsigned int result = 0;

  for(i=0; i<size; i++){
    for(k=0; k<10; k++){
      
    }
  }
}

int main(int argc, char **argv){
  {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    srand(ts.tv_nsec);
  }
  
  int i, x, fcons, fvowel;
  bool ccallowed;

  fcons = fvowel = 0;
  char word[WORDLEN];

  for(i=0; i<WORDLEN; i++){

    // There can only be two consecutive letters of the same type (consonants or vowels)
    // In case of there are less than two consecutive consonants or vowels, will be chosen a random letter (consonant or vowel)
    // If there are 2 consecutive consonants, a vowel is insert in the word

    if((fcons<2 && fvowel<2 && rand()%2) || fcons==2){ 
      word[i] = rndvowel();
      // word[i] = RVOWEL;
      fvowel++;
      fcons = 0;
    } else {
      word[i] = rndcons();
      // word[i] = RCONSONANT;
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
        // word[i-1] = RCONSONANT;
        // word[i] = RCONSONANT;
      }
    }
  }
  
  printf("%s\n", word);
  return 0;
}
