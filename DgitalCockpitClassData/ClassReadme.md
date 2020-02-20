# **Digital Cockpit System of the Smart Vehicle IT System**
## 일반개요
   - What: Education Tutorial Class
   - When: 2020년 1월 중순부터 2월중순까지 1달간 12일 수업 및 실습
   - Where: HancomMDS in Pankyo(H-Tower)
   - Who: keepnext외 20여명(강사: 한양대학교 최문원교수)
   - Why: SmartCar 관련 지식배양 및 개발 전문가 과정을 통해서
   - How: 주어진 교육기간내 강의와 실습을 통해서 이해도를 향상시킴

# 프로젝트 전반 목차
## Cover
   - MainTitle:Development of the Digital Cockpit Solution for Smart Car
   - SubTitle: Education & Practice
 
## Contents:
   - Part 01. Overview
   - Part 02. Design Thining Process
   - Part 03. Project Management
   - Part 04. Software Development Engineering
   - Part 05. WrapUp
   - Part 10. Appendix[Eduation, Tutorial, Excersize]

### Part 1. Overview
Ch01. Megatrend
  1. Industry Review
  2. Smart Vehicle
  3. Digital Cockpit
Ch02. Background and Approach
  1. Needs
  2. Issues & Problem
  3. Solution

### Part 2. Design Thinking
Ch01 Empatize 
Ch02 Ideate
Ch03 Design
Ch04 
Ch05 Test

### Part 3. Project Management(PMBOK)
Ch01 Project Overview
Ch02 Project Scope
Ch03 Project Schedule
Ch04 Project Cost
Ch05 Project Quality
Ch06 Project Human Resource
Ch07 Project Communication
Ch08 Project Risk
Ch09 Project Procurement
Ch10 Project Statkeholders
Ch11 Project Integration


### Part 4. Software Engineering [Development]
Ch01
Ch02
Ch03
Ch04
Ch05 

### Part 5. Warp Up
Ch01 Summary & Review
Ch02 Conclutions
Ch03 Insights(Lessons learnt)
Ch04 Future Works

# 교육훈련 커리큘럼
   - 스마트카 전반개요(강의) 별도정리
   - 운영체제: Linux::[우분투] (강의) 별도정리
   - 프로그래밍언어::[C/CPP] (강의) 별도정리
   - 프레임워크: 소프트웨어GUI분야::[Qt] (강의) 별도정리
   - 프레임워크: 컴퓨터비전 분야::[OpenCV] (강의) 별도정리
   - 프레임워크: 병렬처리 분야::[Cuda] (강의) 별도정리

## 스마트카 전반개요(강의)


### Part 2. Education & Tutorial
Ch01 Overview
Ch02 Installation & Setup
Ch03 Main OS: Windows10
Ch04 Virtual Machine:JVM
Ch05 SubOS: Linux: Ubuntu
Ch06 C/C++ Programming
Ch07 Qt Programming, #Qt Creater
Ch08 Device Control Programming: Vnc viewer

## 스마트카 콕핏 개발(실습)
실습1 기능연습
	• 튜토리얼의 실습란에 해당하는 단위모듈 기능 구현해 보기
	• Work folder
실습2 통합연습
	• 작은 프로젝트 해보기
최종실습:

## 스마트카 디지털 콕핏 프로젝트(개발) 


## 실습환경구축
###작업 순서

1. 작업컴퓨터 환경파악
   • Hardware Infrastructure: Lab PC, Portable Notebook
	• Host OS: Windows 10
	• 가상화 가상머신(Virtual Machine): Virtual Box 5.1.38 
	• Guest OS: Linux Ubuntu 16.04
	• Editor: VS Code
	• Program Language: C/C++/
	• GUI Program: Qt5
   Image Processing: OpenCV 3.4 C++

- 하드웨어플랫폼: 조립형컴퓨터
- 소프트웨어운영체제: 윈도우10
- 리눅스사용환경이 필요하여 버추얼박스(Virtual box) 환경구축: VirtualBox install & setup

1. 리눅스 이미지 install & setup
- 전달받은 압축 파일 압축 풀기(리눅스 이미지)
- C:\cockpit\virtual\압축풀기
- C:\cockpit\virtual\Ubtu_64_1604\Ubtu_64_1604.vbox
  메모장으로 파일 열어서 아래 내용 삭제 (15, 16번째줄)
     <Image uuid="{ee~~~~ 부터 
              ubuntu-16.04.6-desktop-amd64.iso"/>까지

3. 버추얼박스 환경 구축
- 버추얼박스에 기존 사용하던 OS가 있으면 제거 (주의 삭제 누른 후 '지우기만' 선택)
- 버추얼박스에 제공받은 리눅스우분투이미지 추가
  => 메뉴 > 머신 > 추가 > 해당 이미지 선택

4. 버추얼박스에 공유 폴더 설정 및 시스템 설정
- C:\cockpit\virtual\shared 생성 후 공유폴더 설정
- 해당이미지 선택 > 우측 마우스 클릭 > 설정
- 설정창에서 > 공유폴더 선택 > 폴더 지정 > 확인
- 설정창에서 > 시스템 선택 > 프로세서 > 2개 지정여부 확인
- 관리자모드에서 
- 공유폴더 등록명령어: sudo gpasswd -a class vboxsf

5. 가상 시스템 시작

## Smart Car System
[Remote Server 환경]
	• Source Control System(SCS), Version Control System(VCS): Git & Github 
Application Server: Local Server

[Application System] 
GPGPU
	• Windows 10
	• NVIDIA GPU/ Intel CPU
	• OpenCL1.2/CUDA9.0
Sensor System
	• Lidar
	• Supersonic
…Sensor System

- 실습을 위해서 자이트론사 자이카A2모델("카봇"이라 부르기로 함)을 활용함
- 카봇은 메인보드로 엔비디아 TX2 보드를 사용함
- 메인보드에 USB3 허브를 통해 다양한 디바이스들이 연동되어 있음
- **사용시 주의사항! 모터 rpm을 2000이하에서 사용, 주행 주의**

### 시스템 전원 인가 방법
1. 전원버튼 누르는 순서: 
파랑색, 붉은색, 초록색, 노란색 버튼 누르기
시스템별 버튼 색깔이나 구조가 다를 수 있음 

### 메인보드 연결설정
1. 원할한 원격제어를 위해 가상네트워크컴퓨터 환경 구축
   - 사용하는 pc에 vnc 설치
   - 주소 : https://www.realvnc.com/en/connect/download/viewer/
   - VNC 사용법 숙지 필요(관련 자료 참조)
  
2. 카봇에 모니터와 입력장치 연결
   - 사용하는 PC의 hdmi선을 카봇에 연결
   - 사용하는 PC의 키보드 연결

3. 모니터 출력 변경

4. 카못 화면에서 연결 ip확인
   - 로그인 계정 nvidia / 비번 nvidia
   - 터미널 열기 (윈도우키 > 터미널 실행)
   - 터미널 실행 후 ifconfig > 페이지 업버튼 (shift+pageup)
   - 192.168.101.x <- 번호 찾기
   
5. 사용 pc에서 vnc 실행
   - ip 입력 > 실행 > 192.168.101.x 접속 > 비번 nvidia > 접속완료
   - ip:192.168.101.11
6. 완료확인
   - 실습환경에 따라 추후 통신시 자신의 pc ip port <-> xycar ip port 로 통신함
7. 참고


### 작성중인 파일
- virtualbox가 서버가 되는 경우 virtualbox에서 포트 포워딩 설정필요
- ~/Desktop/class/xycar/lidar_sdk/rplidar_sdk-release-v1.11.0/sdk
- ~/Desktop/class/xycar/lidar_sdk/rplidar_sdk-release-v1.11.0/sdk/output/Linux/Release

### VNC화면에 카봇의 디바이스 찾아보는 명령어: 
- ls /dev/tty* 형태
- ./ultra_simple /dev/ttyUSB1

### 권한변경 (실행파일 있는 위치에서)
- chmod -f 0777 ultra_simple 
- ls -l 후 확인
- ./ultra_simple /dev/ttyUSB1

### 소켓 컴파일
- gcc -o client client.c -lpthread
- gcc -o serve+r server.c -lpthread

### 장치별 tty 명칭
1. 모터제어기
  - VESC Device, BLDC Motor; 192.168.101.11 port 9001
  - 모터제어기  ./bldc /dev/ttyACM(번호)
  - 소스코드 수정 및 컴파일
  - gcc -o main main.cpp
   
2. 초음파        ttyUSB(번호)
   - 1.2 USS Device, UltraSonicSensor; port 9002
   - ./uss /dev/ttyUSB1

3. 라이다        ttyUSB(번호)
   - Lidar Device; port 9004
   - lidar code 위치: SDK\APP\ultra_simple\이곳에 카피
	- 컴파일 방법: main.cpp 코드와 이름을 바꾼후 make
	- 명령어: gcc -o main main.cpp 하면 실행파일 main 생성
   - 실행위치: SDK\output\Linux\Release\
   - 실행방법: ./ultra_simple /dev/ttyUSB2
   - 소스코드 수정후 컴파일

   - 페인트툴을 사용하여 라이다 화면 구성하는 방법
      • 위젯상속
      • 함수구현
      • 위젯의 중점에 점 찍기(빨간색)
      • 중점에서 진행방향 선그리기(파란색)
      • 20cm선, 50co선, 100cm선
      • 양의 방향으로 1도씩 회전시킴
      - 라이다의 방향일치 시켜야 함

4. IMU           ttyACM(번호)
   - IMU Device, Inertial Measurement Unit; port 9003
   - imu.c
   - Source coding
      // socket/serial 관련 변수 선언
      // server socket 생성
      // server socket 바인딩
      // server socket listen
      // server socket accept

   - Qt에서 접속, 접속요청시 clientfd에 socket 할당
      // serial 연결 소스
      //7. 반복문 내부에 socket write 문 추가

   - 자세감지기 소스 imc.c는  serial_sample.c와 server.c 코드 참고하여 작성

   - 소스코드가 수정완료되면, 컴파일 gcc -o imu imu.c

   - imu device 실행명령
      - ./imu /dev/ttyUSB2
   - 디바이스 확인방법: 파란LED 켜지면 정상 동작
   - 실행화면 크기조절 방법
      xrandr --fb 1400x700
   Qt Creater에서 프로젝트 생성,
   ui Form 만들고
   코드와 연동한다음
   화면에서 ip(192.168.101.11)와 port(9003) 입력
   확인
   imu3d.c

5. 카메라
   - Video0 <- 장치가 1개
   - Camera Device; port 9005
      - ./camera /dev/video0
6. Digital Cluster
7. V2V Simulator
8. Application Project
   8.1 Management Dashboard

### VNC 화면 크기 변경
- xrandr --fb 1400x700
- ip:192.168.101.x
- virtualbox가 서버가 되는 경우 virtualbox에서 포트 포워딩 설정필요
- VNC
https://www.realvnc.com/en/connect/download/viewer/
- 참고소스
https://drive.google.com/open?id=1vS2Yih5ff1IIF81vPjscGERS2GiR6Amy


# System Programming
### opengl 위젯을 label 자식으로 넣기
- obj3d = new imu3d(ui->sensor);
  obj3d ->resize(ui->sensor->width(), ui->sensor->height());

### lidar 코드 위치
\\192.168.101.3\공유\3.전달코드\5.lidar소스코드_참고용

### xycar코드 위치 : SDK\APP\ultra_simple\이곳
- 컴파일 방법: main.cpp코드와 이름을 바꾼후 make
- 실행 위치: SDK\output\Linux\Release\
- 실행 방법 ./ultra_simple /dev/ttyUSB(번호)

## Project
- Qt Creater 통합개발툴에서 작업
- Project Creater: code/project/cockpit
- File and Directory Structure
   cockpit
   - cockpit.pro
   - Headers
      - bldc.h
      - imu.h
      - lidar.h
      - uss.h
      - camera.h
   - Sources
      - imu.cpp
      - imu3d.cpp
      - bldc.cpp
      - camera.cpp
      - uss.cpp
   - Form
      - bldc.ui
      - imu.ui
      - lidar.ui
      - camera.ui
      - uss.ui



# 교육소개
  - 교육과정명: 초연결 시대 미래자동차를 위한 디지털콕핏 기반의 차량 IT시스템
  - 교육목적: 미래자동차 R&D전문인력양성 교육교재
  - 교육후원: 한국전자종보통신산업진흥회 주관
  - 교육기간: 2020.1~2020.2(총 12일간 교육 + 실습프로젝트)
  - 교육목표: 초연결시대…
  - 임베디드 GUI 프로그래밍 및 멀티미디어 능력 배양

# Title: 1.1 자동차 구조 및 차량 시스템
Subtitle: 임베디드 GUI 프로그래밍 및 멀티미디어
Contents
	- Part 1. 최신 자동차 산업 트렌드
	- Part 2. 최신 자동차 첨단기술
	- Part 3. 자동차 구조
   - Part 4. 차량시스템

## Part 1. 최신 자동차 산업 트렌드
Ch01 자동차 산업의 트렌드 개요
	- 산업영역간의 융복합
	- 환경규제 영향력
	- 자동차 산업 수익구조 변화 예측
	- 현대차 미래사업 투자 계획
Ch02 자율주행
	- 자율주행시스템
	- 자율주행시스템의 레벨 정의
	- 자율주행시스템의 센서의 종류 및 수
Ch03 전동화
	- 전기구동시스템
	- 전동차 주요 부품 개념도
	- 젼기를 이용한 기계 제어
Ch04 커넥티비티
Ch05 자동차 인포테인먼트
Ch06 주행 안정성
Ch07 경량화
Ch08 기타

## Part 2. 최신 자동차 첨단기술(16)
Ch01 차량시스템 분야
	1. 기술01: 하이브리드 시스템(1)
	2. 기술02: 전기차, 연료전지차(2)
	3. 기술03: 전자제어장치(ECU) 및 협조제어(3)
	4. 기술04: 에코어시스트/ 에코드라이브(4)
Ch02 안전기술 분야
	1. 기술05: ABS, TCS, ESC, ESP(5)
	2. 기술06: 전방추돌알림(제동) 시스템(6)
	3. 기술07: 나이트비전 시스템(7)
	4. 기술08: 후방/ 후측방 차량 인식 시스템, ADAS(차선, 차간, 차속지원시스템)(8)
	5. 기술09: 디지털클러스트, 디지털콕핏(9)
	6. 기술10: 안전운전지원시스템(DSSS)(10)
Ch03 주행기술 분야
	1. 기술11: 4륜구동 및 에어 서스펜션+가변 댐퍼 관련(11)
	2. 기술12: 인휠모터(12)
Ch04 차체기술
	1. 기술13: CAN통신(13)
	2. 기술14: 능동형 스티어링(14)
	3. 기술15: 어라운드뷰(15)
	4. 기술16: OTA(16)

## Part 3. 자동차 구조
Ch01 내연기관 및 전기차의 개요
Ch02 내연기관 자동차의 기본구조
	• 엔진, 변속기, 동력전달장치, 바퀴
	• 내연기관 자동차의 동력 특징
		○ 엔진파워, 토크곡선/ 자동차 견인력을 발생시키기 위한 기어
Ch03 전기 자동차의 기본 구조
	• 모터, 감속기, 동력전달장치, 바퀴
	• 전기자동차의 동력 특징
		○ 모델S토크 곡선, 1단 감속기
	• 전기자동차의 주요 부품
		○ 전기차의 대표적인 구성요소

# Part 4. 차량시스템

# Ch01 차량용센서구성
- 자동차 전체
- ADAS 기능을 위한 센서
- 차량센서를 이용한 제어 흐름
- UseCase: ㅡMCU가 탑재된 제동제어 장치; 연구과제결과

# Ch02 차량통신시스템
- V2X 및 인프라 구성
- 차량통신시스템 구성(5G, HD급map, 양자암호통신기반 보안강화)

# C.h03 차량시스템
- 디지털콕핏 개요
○ 디지털콕핏(항공/ 철도/ 자동차/ 선박 등의 조종실)
○ 항공기 운전실 내부변화 이미지
○ 철도 운전실 내부 변화 이미지
○ 자동차 운전석 내부 변화 이미지
○ 자동차 내부 변화
- 타운송 수단과의 비교
○ 철도
§ 대차; 차량 하부 프레임(동력부)
§ 신호시스템; V2X 기반 자율(자동)주행


# Title: 1.2 미래자동차 관련 기술 동향
Subtitle: 임베디드 GUI 프로그래밍 및 멀티미디어
Contents:
	- Part 1. 국가산업발전전략
	- Part 2. 향후국가정책계획
	- Part 3. 지능형자동차 관련 핵심기술 선정 결과
	- Part 4. 지능형자동차 관련 생태계 구도 변화
	- Part 5. 자율주행 자동차의 상용화 시점 예측

## Part 1. 국가산업발전전략
	- 세계 미래차 산업동향과 전망
	- 글로벌 자동차 산업 및 주요국 동향
	- 국내 기술 경쟁력
## Part 2. 향후국가정책계획
	- 정책목표
	
## Part 3. 지능형자동차 관련 핵심기술 선정 결과
	- 산업기술평가관리원(2018)
	- IITP(2018)
	- 중소벤처기업부(2018)

## Part 4. 지능형자동차 관련 생태계 구도 변화
	- 자동차 산업 생태계 변화
	- 안전수준 관련 국제 규격
	- 안전무결성

## Part 5. 자율주행 자동차의 상용화 시점 예측

# 1.3 차량 소프트웨어
(임베디드 GUI 프로그래밍 및 멀티미어)
## Part 1. 차량소프트웨어 주요 키워드
- 자동차에서 소프트웨어가 차지하는 원가비중의 상승

## Part 2. 차량 소프트웨어 구조
- 차량용 소프트웨어 분류
- 차량용 임베디드 소프트웨어 구조
- 차량용 임베디드 SW 발전 방향
- 대표적인 차량용 SW 플랫폼(예시)
- 차량용 SW 개발의 중요사항
- 참고: 소프트웨어 공학

# 1.4 임베디드 프로그래밍
(리눅스 시스템 프로그래밍: 임베디드 GUI 프로그래밍 및 멀티미디어)
## Part 1 Overview
1.4.1 파일처리: 시스템호출
1.4.2 파일처리: C 라이브러리
1.4.3 쉘과 프로세스
1.4.4 프로세스 제어
1.4.5 쓰레드(Thread)
1.4.6 메모리제어
1.4.7 시그널/ 파이프/ IPC
1.4.8 소켓 
## Part 2 실습
1
2
...

# 1.5 GUI 프로그래밍 + 멀티미디어
(임베디드 GUI 프로그래밍 및 멀티미디어)

# Part 1 Overview
• 1.5.1 QT 전반개요

# Part 2 QT 프로그래밍(기본)
• 1.5.2 Qt 기본 객체
• 1.5.3 Qt 기본 위젯
• 1.5.4 Qt 레이아웃
• 1.5.5 Qt 다이알로그
• 1.5.6 Qt 프로그래밍 기초

# Part 3 QT 프로그래밍(심화)
• 1.5.7 Qt 시그널/슬롯
• 1.5.8 Qt Graphics
• 1.5.9 Qt 프로세스/쓰레드
• 1.5.10 XML/JASON, 멀티미디어
• 1.5.11 네트워크


# 1.6 PyQt5 for Windows
- 기본
- 실행예제로 익히기
- 동계산기 만들어 보기(엄노니 유튜브동영상)
- 향후 모든 출력물들을 Qt에 만들어서 출력하기
- 예제로 배우는 PyQt(예제중심으로 배우는 PyQt 프로그래밍 https://opentutorials.org/module/544/4998




# 영상처리 개요: 
# Ch09 Image Processing Programming

## 1. 영상처리개요

## 강의개요
○ 코드들은 Code내에 openCV 폴더에 있음
○ 만들때 환경을 이해하고 제한요인과 범위를 결정한 후 알고리즘 고려 필요
○ 환경, 데이터, 알고리즘 순으로 고려해야 함
○ 조명부터 확인하고 조건 설정

 
## 컴퓨터 비전 및 디지털 영상처리
§ 컴퓨터 비전
§ 디지털 영상 처리/ 디지털 신호 처리
§ 컴퓨터 비전 -> 인간의 시각

## 영상처리란

### 정의

### 영상처리 분야
□ 기하학적 변형, 
□ 화질개선
□ 복원
□ 영상데이터 압축
□ 객체인식

### 다양한 영상처리의 응용분야
□ 얼굴 검출 및 인식
□ 제스처 인식
□ 문자인식
□ 의료 영상분야
□ 공장자동화
□ 보안, 감시
□ 증강현실
□ 기타

### 응용예제
□ 얼굴검출예시 및 얼굴인식 기능
□ 지문/얼굴/홍채 인식
□ 차량번호 인식
□ 문자인식/ 바코드인식
□ 위성영상처리
□ Interactive Game
□ 모션인식 및 사물인식(Xbox Kinect)

### 최근기술발전 수준 및 응용확대 분야
□ 오락, 
□ 교통, 
□ 보안, 
□ 산업
□ 계산 사진학, 
□ 의료, 
□ 과학,
□ 농업, 
□ 군사, 
□ 모바일 등

### 응용 확대 예제
□ 공장자동화: 검사, 자동공정, 작업목표 인식 등
□ 지능형 감시 카메라
□ 자율주행자동차: 
® 차선 보행자 인식
® 스테레오 카메라(보쉬 사례)


## 컴퓨터 비전 시스템

### 컴퓨터 비전에서의 문제접근 방법
□ 인간시각 모사
□ 컴퓨터 비전의 한계

### 과학적 접근과 공학적 접근
□ 목표1: 인간의 시각 같은 인공시각을 만든다. 
□ 목표2: 한정된 범위에서 특정한 임무를 달성하는 인공시각을 만든다. 
□ 과학적 접근과 공학적 접근
□ 디지털 영상은 행렬과 특정값으로 구성되어 있음

### 컴퓨터 비전 시스템 설계 방법
□ 컴퓨터 비전 시스템 설계 과정
□ 문제이해단계
□ 데이터베이스 수집 단계
□ 알고리즘 설계와 구현
□ 성능평가
### 컴퓨터 비전 기술과 관련 인접 학문의 연계성
□ 상호협력이 강해지는 추세

## 디지털 영상처리
□ 방법
□ 장점
□ 단점
□ 영상 관련 학문 분야
□ 디지털 영상처리 기술의 세부분야
® 영상개선
® 영상복원
® 영상변환
® 영상분석
® 영상인식
® 영상압축
□ 디지털 영상처리 기술의 관련 예시
### 디지털 영상처리 관련 정보
□ 빛과 영상/ 카메라 구조
□ 카메라 구성
® 렌즈, 
® 조리개, 
® 셔텨스피드, 
® ISO
□ 3D 카메라
® 스테레오타입
### 영상처리 기초
□ 영상처리의 목적
□ 영상획득과 표현
□ 디지털 영상 
□ 디지털 영상의 표현
□ 디지털 영상의 표현: 
® 빛과 색
® 빛과 색, 색의 3속성(색상, 채도 밝기)
® 컬러모델
® 데이터포맷(디지털영상저장방법)

## 1. 영상처리 프로그램 환경(OpenCV)
		○ ㅇ

## 3. 영상처리-화소기반(영상처리 프로그래밍 기초)
		○ ㅇ
		
## 4. 영상처리-영역기반(영상처리 프로그래밍 기초)
		○ ㅇ

## 5. 영상처리-특징추출(영상처리 프로그래밍 응용)
		○ ㅇ


# CH10 V2X 프로그래밍

## 1. DB설정 및 웹서버 설정(커넥티드카 환경구축 및 웹서비스 연동)

○ ..

## 2. DB 기초

○ ..

## 3. WEP API

○ ..

## 4. V2V 안전주행 서비스

○ ..



# CH11 GP-GPU

## 1. 병렬컴퓨팅, OpenCL, GPGPU, CUDA
### 병렬컴퓨팅 개요

### OpenCL 개요
- 개요

### GPGPU 개요
- 개요

### CUDA
- 개요

## 2. OpenCL
### OpenCL 프로그래밍
### 개요
### 환경
### 구조
### 프로그래밍

## 3. CUDA

### nVidia GPU
○ CUDA(Computer Unified Device Architecture
○ NVIDIA GPU 세대별 특징
○ NVIDIA GPU 아키텍처
○ NVIDIA GPU Memory Hierachy

### CUDA 프로그래밍
○ CUDA Progrmming 개요
○ CUDA API 구조
○ CUDA Toolkit 설치
○ CUDA Hello World
○ CUDA Kernel Code 작성
○ CUDA Automatic Scalability
○ CUDA Streaming Multiprocessor
○ CUDA 이미지 픽셀처리
○ CUDA Thread 협력
○ CUDA Constant Memory
○ CUDA Texture Memory
○ Cuda Memoy 정리
○ CUDA 성능(실행시간) 측정방법
○ CUDA Atomic Operation
○ CUDA Page-locked Host Memory
○ CUDA Stream
○ CUDA정리	


# Ch12 IoT for Smart Home/Smart Building, 스마트홈프로젝트
## 1. 일반개요
### 개요
### 주요특징
### 주요사양
### 사용사례
### 응용분야
### 기타

## 2. 스마트홈 프로그래밍
○ 환경구축
○ 프로그래밍///

# Ch13. Solar Generator Controller for Smart Factory
발전소프로젝트

## 1. 일반개요
### 개요
### 주요특징
### 주요사양
### 사용사례
### 응용분야
### 기타

## 2. 제어기 프로그래밍
### 전체시스템 구조
### 집열시스템 제어
### 열에너지저장장치 제어
### 전기에너지저장장치 제어
### 열공급시스템 제어
### 스마트홈연동

## 3. 기타






