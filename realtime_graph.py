import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import matplotlib.pyplot as plt

# Firebase 서비스 계정 키 파일 경로
cred = credentials.Certificate("envmeasure-bcf3c-firebase-adminsdk-elykz-7a1faf0926.json")

# Firebase 앱 초기화 실시간버전
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://envmeasure-bcf3c-default-rtdb.firebaseio.com/'
})

# 변수명과 참조를 매핑
ref_dict = {
    'temperature': db.reference('temperature'),
    'pressure': db.reference('pressure'),
    'altitude': db.reference('altitude'),
    'PM1_0': db.reference('PM1_0'),
    'PM2_5': db.reference('PM2_5'),
    'PM10': db.reference('PM10'),
}

# 변수명과 단위를 매핑
unit_dict = {
    'temperature': '°C',
    'pressure': 'hPa',
    'altitude': 'm',
    'PM1_0': 'µg/m³',
    'PM2_5': 'µg/m³',
    'PM10': 'µg/m³',
}

# 각 데이터별 키값 리스트 참조
keys_list = list(ref_dict.keys())
# 그래프 제목 폰트
title_font = {
    'fontsize': 10,
    'fontweight': 'bold'
}
# 그래프 창 생성
plt.figure(figsize=(10, 15))

# 각 변수에 대한 그래프 생성
lines = []
for i, (key, ref) in enumerate(ref_dict.items()):
    lines.append(plt.subplot(len(ref_dict)//2, 2, i+1).plot([], [], label=key)[0])
    plt.title(keys_list[i], fontdict=title_font, loc='left')
    plt.ylabel(unit_dict[key])  # y축 라벨 추가
    # plt.subplot(len(ref_dict)//2, 2, i+1).legend()

# 그래프 창 전체화면
manager = plt.get_current_fig_manager()
manager.full_screen_toggle()
plt.ion()
plt.show()

# 현재 열려 있는 그래프 창이 하나라도 있으면 True
while plt.get_fignums():
    # 각 변수의 데이터를 가져옴
    data = []
    for ref in ref_dict.values():
        all_data = [float(value) for value in ref.get().values()]
        data.append(all_data[-17200:])  # 마지막 17200개의 데이터만 선택

    # 그래프 업데이트
    for i in range(len(ref_dict)):
        lines[i].set_ydata(data[i])
        lines[i].set_xdata(range(len(data[i])))
        plt.subplot(len(ref_dict)//2, 2, i+1).relim()
        plt.subplot(len(ref_dict)//2, 2, i+1).autoscale_view()

    plt.draw()
    plt.pause(1)
