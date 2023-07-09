/*
  ビット演算を用いたフラグ処理の勉強
  参考>>https://qiita.com/drken/items/7c6ff2aa4d8fce1c9361

  C言語におけるビット演算子
      & AND   
      | OR
      ^ XOR
      ~ NOT
      << 左シフト    値が2倍になることを意味する
      >> 右シフト    値が1/2倍になることを意味する
*/

#include <stdio.h>

#define TRUE 1
#define False 0


unsigned int voiceFlag;

void printBitFlag(unsigned int bitFlag)
{
    // n番目のbitの状態を確認するにはnビットシフトしてから最下位bitを取り出せばよい
    unsigned int nflag = 0;
    for(int i = 15; i > 0; i--){
        nflag = (bitFlag >> i) & 1;
        printf("%d", nflag);
    }
    printf("\n");
}

int isBitFlag(unsigned int bitFlag, unsigned int n)
{
  if (bitFlag & (1 << n))
  {
    return TRUE;
  }
  return False;
}

void onBitFlag(unsigned int bitFlag, unsigned int n)
{
  bitFlag |= (1 << n);
}

void offBitFlag(unsigned int bitFlag, unsigned int n)
{
  bitFlag &= ~(1 << n);
}

void initBitFlag(unsigned int bitFlag)
{
  for(int i = 0; i < 15; i++)
  {
    offBitFlag(bitFlag, i);
  }
}