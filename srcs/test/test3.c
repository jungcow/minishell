#include <termcap.h>

int tputs(char *string, int nlines, int (*outufn)()); 
/*
**	string: 출력할 문자를 넣어야 한다.
**	nlines: 대개 명령어에 의해 지워지거나 움직여야 할 내용물들의 줄 수 이다.
**			cursor motion 명령어나 한 줄 안에서의 editing을 하는 명령어들은 nlines = 1 이다.
**			'al' (insert a line) 이나 'cd'(커서위치부터 화면의 끝까지 지우는) 같은 대부분의 명령어들은 nlines = [screen_height] - [현재 수직 위치] 이다.
**			'ic' and 'dc' 명령어들은 padding이 줄수가 아닌 character에 영향을 받기 때문에 문제가 생긴다. 하지만 nlines는 termcap에서 정의했듯 영향을 받는 coloumns가 아닌 row(lines)이기 때문에 또한 많은 프로그램들이 이 정의를 따르기 때문에 이러한 종속성을 변경할 순 없다. 따라서 'ic' and 'dc' 명령어는 nlines = 1 이다.
**			terminal control strings의 경우 몇몇 인자를 필요로 한다.
**			- cm(cursor motion) 같은 경우 cursor가 얼마나 움직여야 할지를 말해주지만, 이건 단순히 문자열이 될 순 없다. 따라서 어떻게 cursor position의 번호와 명령어 내의 어디에 넣을지 알려줘야 한다. -> 뭔 개소리야;;
**			
*/
int main(void)
{
	char		pc; // padding에 사용되는 문자이다. (대개 null character인것으로 이해했었다)
	short		ospeed; // padding 수를 계산 하기 위해 필요.


	char		*temp;

	temp = tgetstr("pc", NULL);
	pc = temp ? *temp : 0; // terminal descriptor 안의 'pc' capability를 가져올 수 있다.

