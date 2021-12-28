# minishell
## Overview
![minishell](https://user-images.githubusercontent.com/60311340/147553101-57e3945e-dd0b-4c74-b273-67be6baedd57.gif)
---
## Index
- Redirection & Pipeline
- Broken Pipe
- BuiltIn Command
	- echo
	- env
	- export
	- unset
	- cd
	- history
- Shell variable
	- Double Quote
	- Single Quote
	- Back Slash
---
## Execution
```shell
make && make clean
./minishell
```
---
## Redirection & Pipeline
|Redirection|Pipeline|
:---------:|:--------:
|![redirection](https://user-images.githubusercontent.com/60311340/147553579-4eb6c9dd-85fd-4a59-a630-9e2e7a7464d3.gif)|![pipeline](https://user-images.githubusercontent.com/60311340/147553573-0d1aa8fd-cd0a-4e73-94de-5c78977a37c7.gif)|

### Broken Pipe
|zsh|minishell|
:---------:|:--------:
|![broken_pipe_zsh](https://user-images.githubusercontent.com/60311340/147553755-e6a6f4a0-0cca-4150-8444-a7ef7f6b9ceb.gif)|![broken_pipe_minishell](https://user-images.githubusercontent.com/60311340/147553766-90f78b18-977a-4d54-847d-b6a797707b11.gif)|

## BuiltIn Command
|command|implementation|
:------:|:------:
|echo|![echo](https://user-images.githubusercontent.com/60311340/147555091-1ec06ef6-796d-4536-b5f5-a4dd9b4ce534.gif)|
|cd

	- echo
	- env
	- export
	- unset
	- cd
	- history
## Shell Variable
|Special Character|Image|
:-----------:|:-----------:
|Double Quote|<img width="400" alt="doublequote" src="https://user-images.githubusercontent.com/60311340/147553969-785b813c-b518-4bdc-8cb1-573dd3670dc6.png">|
|Single Quote|<img width="400" alt="singlequote" src="https://user-images.githubusercontent.com/60311340/147553960-f6608f06-ca45-4270-8d78-57f8daf34afd.png">|
|Back Slash|<img width="400" alt="backslash" src="https://user-images.githubusercontent.com/60311340/147553920-8431ad0f-8d28-4b02-9b61-ea272adf060e.png">|
---

## git commit 규칙
```
[type] : 요약    -- 헤더

<내용>           -- 본문
```

### git commit type
- feat : 새로운 기능에 대한 커밋
- fix : 버그 수정에 대한 커밋
- build : 빌드 관련 파일 수정에 대한 커밋
- chore : 그 외 자잘한 수정에 대한 커밋
- ci : CI관련 설정 수정에 대한 커밋
- docs : 문서 수정에 대한 커밋
- style : 코드 스타일 혹은 포맷 등에 관한 커밋
- refactor :  코드 리팩토링에 대한 커밋
- test : 테스트 코드 수정에 대한 커밋

## 유용한  링크

### 정리글 모음(42 슬랙 글)
- [여러 minishell 자료 링크](https://42born2code.slack.com/archives/CU6MTFBNH/p1618270936120400) - <21.04.13 추가> 

### bash script 관련 (중요!!)
- [bash script](https://mug896.github.io/bash-shell/index.html) - <21.04.13 추가> 

### termios 관련
- [termios 구조체 사용 방법1](https://wiki.ubuntu-kr.org/index.php/Terminal_Programming)
- [termios 구조체 사용 방법2](http://neosrtos.com/docs/posix_api/termios.html)
- [termios 구조체 사용 방법3](https://blog.naver.com/PostView.nhn?blogId=vpas3000&logNo=70002387279) - <21.04.13 추가>

### termcap 관련
- [termcap library document](https://www.gnu.org/software/termutils/manual/termcap-1.3/html_mono/termcap.html)
- [termcap manual pages](https://nxmnpg.lemoda.net/3/tgoto)

#### Termcap 에서의 capability 관련
- [string capability](http://www.xevious7.com/linux/lpg_8_22_3.html)
- [num capability](http://www.xevious7.com/linux/lpg_8_22_2.html)
- [boolean capability](http://www.xevious7.com/linux/lpg_8_22_1.html)

### ESCAPE SEQUENCE 관련

#### ESCAPE TABLE
![escape table](https://cdn.discordapp.com/attachments/790600784110813264/830787115209719888/escape_table.png)

#### ESCAPE SEQUENCE LIST - (CSI 부분을 자세히 봐야한다)
- [escape code](https://en.wikipedia.org/wiki/ANSI_escape_code#Control_characters) - <21.04.13 추가>

## 확인해봐야 할 테스트 케이스(예외 케이스)
1. `< , >, >> 기호 좌측값은 공백없이 붙여야합니다. 그렇지 않으면 명령의 인수로 인식이 됩니다`
3. `명령 치환에는 redirection 을 적용할 수 없습니다.`
4. 명령어의 옵션은 여러번 와도 괜찮다.
```
echo -nnnnnnnnnnnn "hello"
=> hello$

** 다만 아래와 같은 경우는 다음과 같이 나온다.
echo -nnnnn -n-n-n-n-n "hello"
=> -n-n-n-n-n hello$
```
## 학습 내용
### 21.04.12(월)

1. `stty -a` : 현재 터미널의 정보를 알려준다.(terminal 형태에 대해 나옴)
![termanal description](https://cdn.discordapp.com/attachments/790600784110813264/831114938273366027/unknown.png)
2. `terminal_type = getenv("TERM")` : 현재 터미널 타입을 알려준다.
	- getenv 함수는 인자로 들어온 환경변수를 가져온다.
	- `echo $TERM` 을 해보면 나오는 결과가 terminal_type에 들어가는 string과 동일한 것을 알 수 있다.
3. `tgetent(buffer, terminal_type)` : terminal type을 두번째 인자로 넣어주고 받아올 buffer를 넣어주면 해당 터미널 타입의 description을 참조 할 수 있게 된다.
	- 즉, 이 터미널의 database라고 하는 것들을 사용할 수 있게 되는 것.
	- 보통 buffer에 NULL을 넣어준다. -> 이는 UNIX 에선 사용 불가. / GNU 라이브러리에서만 사용가능
		- GNU 에선 NULL 즉, 공간을 할당하지 않고 준다면 tgetent가 자동으로 할당한 후에 정보를 담는다.
		- 어디 주소에 담는지는 알 방법이 없으며, 따라서 free를 안해줘도 되고 해줘서도 안된다.
		- UNIX 라이브러리에선 사용자가 공간을 마련한 버퍼를 넘겨주어야 한다.
		- 얼만큼의 버퍼가 필요한지는 모르며 관습적으로 2048byte(enough buffer) 를 넘겨준다고 한다.
	- 이렇게 database를 담게 되면 나중에 `tgetflag`, `tgetnum`, `tgetstr` 등의 함수로 '조사' 할 수 있다고 한다.
4. `Capability 란?` : terminal description에 적혀있는 각각의 두글자 string들을 capability라고 한다.
	- tgetent 로 적절한 터미널 description을 가져오게 되면 capability의 값들을 가져올 수 있게 된다.
5. `int tgetflag(char *name)`
	- Param 
		- name : capability의 이름(두글자) 를 넣어주면 된다.
	- Return
		- 그 이름의 capability 가 존재 한다면 1, 아니라면 0을 반환한다.	
6. `int tgetnum(char *name)`
	- Param
		- name : 위와 동일
	- Return
		- 그 이름의 capability 가 존재한다면 해당 capability의 숫자값을 가져온다.
		- terminal description 에 안적혀 있다면 -1을 반환한다.
7. `char *tgetstr(char *name, char **area)`;
	- Param
		- name : 위와 동일
		- area : GNU에선 NULL을 넣어주어 내부적으로 malloc을 이용한 할당을 하여 정보를 name에 해당하는 capability의 값들을 저장할 수 있게 한다. UNIX라면 무조건 char * 에 공간을 할당해주어 &buffer 와 같이 넘겨주어 그 안에 값들을 저장할 수 있게 해야 한다. 
	- Return
		- capability의 값이 담긴 string을 넘겨준다.
		- 만약 capability 가 존재하지 않으면 null pointer를 넘겨준다.
8. "\033[6n" : 이 string을 출력하면 현재 커서 위치를 출력해준다.

### 21.04.13(화) 학습내용
0. termios 구조체
	- 이 구조체의 각 플래그는 비트값으로 되어있으며, 따라서 비트연산을 통해 비트값을 세팅해줄 수 있다.

1. 터미널 입력 모드
	- 정규모드(Canonical Mode)
		- 줄 단위로 터미널 입력을 처리하며, 줄 편집이 활성화되어 있다. 정규모드는 기본 입력 모드이다.
	- 비정규모드(Noncanonical Mode)
		- 줄 단위 편집이 아닌 문자 단위 편집 기능을 제공한다.
2. 예제
	- Enter 키 입력 없이 문자 입력과 동시에 옵션 값 출력하는 에제
		1. 입력모드 : 비정규모드(Noncanonical Mode)
		2. ~ECHO	: 입력버퍼의 내용을 바로 출력버퍼로 복사하는 ECHO 기능을 비활성화
```c
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

typedef enum {FALSE, TRUE} bool;

int getch(void)
{
	int ch;
	struct termios buf;
	struct termios save;

	tcgetattr(0, &save);
	buf = save;
	buf.c_lflag &= ~(ICANON|ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &buf);
	ch = getchar();
	tcsetattr(0, TCSAFLUSH, &save);

	return ch;
}

int main(int argc, char *argv[])
{
	char ch;
	bool exit;

	printf("Insert Option \n");

	do
	{
		ch = getch();

		if(ch == 'q')
			exit = FALSE;

		printf("ch = %c \n", ch);

	}
	while(exit);

	return 0;
}
출처: https://chipmaker.tistory.com/entry/터미널 [CHIPMAKER]
```
	- 위와 같이 기존 터미널의 설정을 저장해두었다가 Ctrl + C 등으로 새로운 터미널 설정을 적용한 작업들이 끝나면 기존 터미널의 설정들로 다시 설정을 세팅해주어야 한다.

### 21.04.14(수) 학습내용
1. shell 의 버퍼관리

|![shell의 버퍼관리](https://cdn.discordapp.com/attachments/790600784110813264/831784772870864906/IMG_0872.PNG)| ![shell에서 버퍼가 넘어갔을 때](https://cdn.discordapp.com/attachments/790600784110813264/831784764356165642/IMG_0873.PNG)|
|--|--|

2. history
- history 명령어를 통해 이전 command를 볼 수 있다.
	- 방향키 위, 아래키로 이 전 history와 후 history를 볼 수 있다.
	- ~/.bash_history 파일에 저장된다.
	- 정상적으로 exit이 되었을 때에만 history에 저장이 된다.
**내부 매커니즘**
```
1. 먼저 프로세스(shell) 내부에서 메모리에 저장시킨다.
2. 그 이후에 ~/.bash_hitory 파일에 저장한다.
```

### 21.04.17(토) 학습내용
1. 현재 터미널의 col값과 row값을 가져오는 방법
: [Get Terminal Width in C](https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c)

### 21.04.28(수) 학습내용
1. multi pipeline 의 구현 과정을 학습
	- [multi pipeline 참고자료1](https://stackoverflow.com/questions/916900/having-trouble-with-fork-pipe-dup2-and-exec-in-c/)
	- [multi pipeline 참고자료2](https://stackoverflow.com/questions/17630247/coding-multiple-pipe-in-c)

### 21.04.30(금) 학습내용
1. 멀티 파이프라인으로 구현을 위한 자료
	- [42 minishell 허용 함수 정리한 블로그](https://42kchoi.tistory.com/259)
	- [dup2 을 이용한 pipe 설명 중 가장 이해가 쉬웠던 설명들 및 여러 프로세스를 확인하기 위한 리눅스 명령어들을 알려준 블로그](https://codingdog.tistory.com/entry/%EB%A6%AC%EB%88%85%EC%8A%A4-dup2-%ED%95%A8%EC%88%98-%ED%8C%8C%EC%9D%BC-%EB%94%94%EC%8A%A4%ED%81%AC%EB%A6%BD%ED%84%B0%EB%A5%BC-%EB%B3%B5%EC%82%AC%ED%95%9C%EB%8B%A4)
