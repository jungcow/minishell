# minishell

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

### termios 관련
- [termios 구조체 사용 방법1](https://wiki.ubuntu-kr.org/index.php/Terminal_Programming)
- [termios 구조체 사용 방법2](http://neosrtos.com/docs/posix_api/termios.html)

### termcap 관련
- [termcap library document](https://www.gnu.org/software/termutils/manual/termcap-1.3/html_mono/termcap.html)
- [termcap manual pages](https://nxmnpg.lemoda.net/3/tgoto)

#### Termcap 에서의 capability 관련
- [string capability](http://www.xevious7.com/linux/lpg_8_22_3.html)
- [num capability](http://www.xevious7.com/linux/lpg_8_22_2.html)
- [boolean capability](http://www.xevious7.com/linux/lpg_8_22_1.html)

#### ESCAPE TABLE
![escape table](https://cdn.discordapp.com/attachments/790600784110813264/830787115209719888/escape_table.png)

## 학습 내용
### 1. 21.04.12(월)

1. `stty -a` : 현재 터미널의 정보를 알려준다.(terminal description에 관해 나옴)
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
7. `char *tgetstr(char *name, char **area);
	- Param
		- name : 위와 동일
		- area : GNU에선 NULL을 넣어주어 내부적으로 malloc을 이용한 할당을 하여 정보를 name에 해당하는 capability의 값들을 저장할 수 있게 한다. UNIX라면 무조건 char * 에 공간을 할당해주어 &buffer 와 같이 넘겨주어 그 안에 값들을 저장할 수 있게 해야 한다. 
	- Return
		- capability의 값이 담긴 string을 넘겨준다.
		- 만약 capability 가 존재하지 않으면 null pointer를 넘겨준다.
8. "\033[6n" : 이 string을 출력하면 현재 커서 위치를 출력해준다.
