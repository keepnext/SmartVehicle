#Digital Cockpit System of the Smart Vehicle IT System
## 일반개요
- What: Education Tutorial Class
- When: 2020년 1월 중순부터 2월중순까지 1달간 12일 수업 및 실습
- Where: HancomMDS in Pankyo(H-Tower)
- Who: keepnext외 20여명(강사: 한양대학교 최문원교수)
- Why: SmartCar 관련 지식배양 및 개발 전문가 과정을 통해서
- How: 주어진 교육기간내 강의와 실습을 통해서 이해도를 향상시킴

# 교육과정 전반 목차
## 스마트카 전반개요(강의)



## 스마트카 콕핏 개발(실습)



## 스마트카 디지털 콕핏 프로젝트(개발) 


## 실습환경구축
###작업 순서

1. 작업컴퓨터 환경파악
- 하드웨어플랫폼: 조립형컴퓨터
- 소프트웨어운영체제: 윈도우10
- 리눅스사용환경이 필요하여 버추얼박스(Virtual box) 환경구축: VirtualBox install & setup

2. 리눅스 이미지 install & setup
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

----------------------------------------------------------------

## Smart Car System
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

### VNC화면에 카봇의 디바이스 찾아보는 명령여: 
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
- 모터제어기     ttyACM(번호)
- IMU           ttyACM(번호)
- 라이다        ttyUSB(번호)
- 초음파        ttyUSB(번호)
- 카메라        Video0 <- 장치가 1개

### VNC 화면 크기 변경
- xrandr --fb 1400x700

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









