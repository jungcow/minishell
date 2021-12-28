# minishell
## Overview
![minishell](https://user-images.githubusercontent.com/60311340/147553101-57e3945e-dd0b-4c74-b273-67be6baedd57.gif)
---
## Index
- [Execution](#execution)
- [Redirection and Pipeline](#redirection-and-pipeline)
- [Broken Pipe](#broken-pipe)
- [BuiltIn Command](#buildin-command)
	- [echo](#1echo)
	- [env](#2env)
	- [export](#3export)
	- [unset](#4unset)
	- [cd](#5cd)
	- [history](#6history)
- [Shell variable](#shell-variable)
	- [Double Quote](#double-quote)
	- [Single Quote](#single-quote)
	- [Back Slash](#back-slash)
- [Documentation](#documentation)
---
## Execution
```shell
make && make clean
./minishell
```
---
## Redirection and Pipeline
|Redirection|Pipeline|
:---------:|:--------:
|![redirection](https://user-images.githubusercontent.com/60311340/147553579-4eb6c9dd-85fd-4a59-a630-9e2e7a7464d3.gif)|![pipeline](https://user-images.githubusercontent.com/60311340/147553573-0d1aa8fd-cd0a-4e73-94de-5c78977a37c7.gif)|

### Broken Pipe
|zsh|minishell|
:---------:|:--------:
|![broken_pipe_zsh](https://user-images.githubusercontent.com/60311340/147553755-e6a6f4a0-0cca-4150-8444-a7ef7f6b9ceb.gif)|![broken_pipe_minishell](https://user-images.githubusercontent.com/60311340/147553766-90f78b18-977a-4d54-847d-b6a797707b11.gif)|

## BuiltIn Command
#### 1.echo
![echo](https://user-images.githubusercontent.com/60311340/147555091-1ec06ef6-796d-4536-b5f5-a4dd9b4ce534.gif)
#### 2.cd
![cd](https://user-images.githubusercontent.com/60311340/147555665-976f4f33-fa03-4dff-894f-b51752572dcc.gif)
#### 3.env
#### 4.export
#### 5.unset
<img width="600" alt="unset-var" src="https://user-images.githubusercontent.com/60311340/147556155-5f78616d-d153-4127-be03-24b6fd778193.png">

#### 6.history
![history](https://user-images.githubusercontent.com/60311340/147556306-47771946-cce1-4d61-b250-2f65254137e1.gif)

---
## Shell Variable
|Special Character|Image|
:-----------:|:-----------:
|Double Quote|<img width="400" alt="doublequote" src="https://user-images.githubusercontent.com/60311340/147553969-785b813c-b518-4bdc-8cb1-573dd3670dc6.png">|
|Single Quote|<img width="400" alt="singlequote" src="https://user-images.githubusercontent.com/60311340/147553960-f6608f06-ca45-4270-8d78-57f8daf34afd.png">|
|Back Slash|<img width="400" alt="backslash" src="https://user-images.githubusercontent.com/60311340/147553920-8431ad0f-8d28-4b02-9b61-ea272adf060e.png">|
---

## Documentation
1. [termios 구조체 사용 방법](https://github.com/jungcow/42Cursus/wiki/20210411(%EC%9D%BC))
2. [termcap 과 escape sequence](https://github.com/jungcow/42Cursus/wiki/20210412(%EC%9B%94))
3. [termios를 통한 terminal mode 설정](https://github.com/jungcow/42Cursus/wiki/20210413(%ED%99%94))
4. [shell의 버퍼관리와 유용한 escape sequence](https://github.com/jungcow/42Cursus/wiki/20210414(%EC%88%98))
5. [history 구현1](https://github.com/jungcow/42Cursus/wiki/20210416(%EA%B8%88))
6. [history 구현2 - cursor](https://github.com/jungcow/42Cursus/wiki/20210418(%EC%9D%BC))
7. [history 구현3 - termcap capability 적용](https://github.com/jungcow/42Cursus/wiki/20210419(%EC%9B%94))
8. [history 구현4 - history line editing](https://github.com/jungcow/42Cursus/wiki/20210420(%ED%99%94))
9. [history 구현5 - termcap의 문제점 발견](https://github.com/jungcow/42Cursus/wiki/20210423(%EA%B8%88))
10. [pipeline 구현1 - fork, exec, waitpid 학습](https://github.com/jungcow/42Cursus/wiki/20210426(%EC%9B%94))
11. [pipeline 구현2 - 실습](https://github.com/jungcow/42Cursus/wiki/20210427(%ED%99%94))
12. [pipeline 구현3 - pipe, dup2 학습](https://github.com/jungcow/42Cursus/wiki/20210428(%EC%88%98))
