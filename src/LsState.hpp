# define SEONSOR_INIT 15
# define NAVI_CONNECT 14
# define TAKE_OFF 13


class LsState
{
  LsState(unsigned int bitFlag);
  ~LsState();
private:
  volatile unsigned int flag;
public:
  void initBitFlag();
  bool isBitFlag(unsigned int n);
  void onBitFlag(unsigned int n);
  void offBitFlag(unsigned int n);
};

LsState::LsState(unsigned int bitFlag)
{
  flag = bitFlag;
  initBitFlag();
}

void LsState::initBitFlag()
{
  for(int i = 0; i < 15; i++)
  {
    offBitFlag(i);
  }
}

bool LsState::isBitFlag(unsigned int n)
{
  if (flag & (1 << n))
  {
    return true;
  }
  return false;
}

void LsState::onBitFlag(unsigned int n)
{
  flag |= (1 << n);
}

void LsState::offBitFlag(unsigned int n)
{
  flag &= ~(1 << n);
}
