#ifndef __HEADER__SOUND__
#define __HEADER__SOUND__
/*****************************************************************************/
enum enumSounds {
  soundBump = 0,
  soundHit,
  soundError,
  soundStep,
  soundChing,
  soundLevelUp
};
/*****************************************************************************/
class clsSound {
  public:
    clsSound();
    ~clsSound();

    void playMusic(void);
    void stopMusic(void);

    void playSound(int,int);

  protected:

  private:
};
/*****************************************************************************/
#endif // __HEADER__SOUND__
