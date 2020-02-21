# 실습환경구축
##작업 순서

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

### 소켓 컴파일 방법
- gcc -o client client.c -lpthread
- gcc -o serve+r server.c -lpthread

## 장치별 tty 명칭
[XyCar 다운로드 20200214일 기준: 구글드라이버](https://drive.google.com/open?id=11yZHH6QINVS30-hSSnI-Y6y3b2rUwxUO)
[Motor, Cam 다운로드 링크: 구글드라이버](https://drive.google.com/open?id=13zR2H0Wrz0hDC5yp2G5j0MeoUhzwFWtg)
[VNC 다운로드: Realvnc 사이트](https://www.realvnc.com/en/connect/download/viewer/)
[참고소스: 구글드라이버](https://drive.google.com/open?id=1vS2Yih5ff1IIF81vPjscGERS2GiR6Amy)


[컴파일]
gcc -c main.c bldc_interface.c bldc_interface_uart.c buffer.c comm_uart.c crc.c packet.c timers.c
gcc -o main  main.o bldc_interface.o bldc_interface_uart.o buffer.o comm_uart.o crc.o packet.o timers.o -lrt ptrhead

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

