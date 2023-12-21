# 실내 환경 측정기
### 진행 기간 : 2023년 12월 10일 ~ 12월 18일

## 사용 기술
+ <img src="https://img.shields.io/badge/Arduino-00979D?style=flat-square&logo=Arduino&logoColor=white"/> - 
Environmental measurement sensor control and Wi-Fi connection
+ <img src="https://img.shields.io/badge/Firebase-FFCA28?style=flat-square&logo=Firebase&logoColor=white"/> – Realtime Database
+ <img src ="https://img.shields.io/badge/Python-3776AB?style=flat-square&logo=Python&logoColor=white"/> - Raspberry Pi Programming Language
+ <img src="https://img.shields.io/badge/Raspberry Pi-A22846?style=flat-square&logo=Raspberry Pi&logoColor=white"/> - Touch Display(with Wi-Fi)

## 프로젝트 설명
+ 실내 환경 데이터를 측정하는 센서를 인터넷과 연결하여 센싱한 데이터를 그래프 구조로 출력하는 프로젝트
+ 센서를 인터넷과 연결하는 아두이노 ESP8266을 사용
+ 센서는 온도, 대기압 센서인 BMP280과 미세먼지 센서인 PMS7003을 사용
+ 라즈베리 파이에서 실시간으로 데이터가 갱신되며 그래프 형태로 환경 변화 추정 가능
+ 실시간 데이터베이스인 Firebase를 활용

---
## 핵심 기능 설명

<img src ="https://github.com/Mellowball/environmental-measuring-instrument/blob/main/readme_img/0.png"/>
<img src ="https://github.com/Mellowball/environmental-measuring-instrument/blob/main/readme_img/1.png"/>
<img src ="https://github.com/Mellowball/environmental-measuring-instrument/blob/main/readme_img/2-1.png"/>
<img src ="https://github.com/Mellowball/environmental-measuring-instrument/blob/main/readme_img/2-2.png"/>
<img src ="https://github.com/Mellowball/environmental-measuring-instrument/blob/main/readme_img/2-3.png"/>
<img src ="https://github.com/Mellowball/environmental-measuring-instrument/blob/main/readme_img/2-4.png"/>
<img src ="https://github.com/Mellowball/environmental-measuring-instrument/blob/main/readme_img/2-5.png"/>
<img src ="https://github.com/Mellowball/environmental-measuring-instrument/blob/main/readme_img/3.png"/>
<img src ="https://github.com/Mellowball/environmental-measuring-instrument/blob/main/readme_img/4-1.png"/>
<img src ="https://github.com/Mellowball/environmental-measuring-instrument/blob/main/readme_img/4-2.png"/>

## 실제 구현 뷰

### 센서 및 아두이노 정상 동작 확인
<img src ="https://github.com/Mellowball/environmental-measuring-instrument/blob/main/readme_img/arduino.gif"/>

### 실시간 데이터 수신 및 그래프 출력 확인
<img src ="https://github.com/Mellowball/environmental-measuring-instrument/blob/main/readme_img/raspi.gif"/>  
