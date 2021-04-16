#include <stdio.h>
#include <termios.h>

struct termios old_settings;
int main()
{
    struct termios new_settings;
    char buf[80];
    tcgetattr(0, &old_settings);
    new_settings = old_settings;
    new_settings.c_lflag &= (~ISIG); // 특수문자 무시
    tcsetattr(0, TCSANOW, &new_settings);
    fgets(buf, 80, stdin);
    fputs(buf, stdout);
    tcsetattr(0, TCSANOW, &old_settings);
}
