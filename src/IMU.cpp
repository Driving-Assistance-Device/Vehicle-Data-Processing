#include "IMU.h"


Adafruit_MPU6050 mpu;

IMUData imuData;

// 상보 필터를 위한 변수
static unsigned long last_time = 0;

//--------------------------------------------------------------------------------

static void imuData_init()
{
  imuData.valid = false;
  imuData.accX = 0;
  imuData.accY = 0;
  imuData.accZ = 0;
  imuData.gyroX = 0;
  imuData.gyroY = 0;
  imuData.gyroZ = 0;
  imuData.angleX = 0;
  imuData.angleY = 0;
  imuData.angleZ = 0;
}


void IMU_init()
{
  imuData_init();

  Serial.println("------------------------------");
  Serial.println("Init IMU");
  Serial.println("------------------------------");

  // I2C 버스 시작
  Wire.begin(IMU_SDA, IMU_SCL);

  // MPU6050 센서 초기화
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // 센서 동작 범위 설정
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG); // << 여기가 수정된 부분입니다.
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  last_time = micros(); // 시간 초기화

}



void IMU_run()
{
  if (last_time == 0) return; // 초기화 전 실행 방지

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // 1. 원시 데이터 저장
  imuData.accX = a.acceleration.x;
  imuData.accY = a.acceleration.y;
  imuData.accZ = a.acceleration.z;
  imuData.gyroX = g.gyro.x;
  imuData.gyroY = g.gyro.y;
  imuData.gyroZ = g.gyro.z;

  // 2. 시간 변화량(dt) 계산
  unsigned long current_time = micros();
  float dt = (current_time - last_time) / 1000000.0; // 단위를 초로 변경
  last_time = current_time;

  // 3. 가속도 센서 값으로 각도 계산
  // atan2를 사용하여 더 안정적인 각도 계산 (X축, Y축 회전 기준)
  float accel_angle_y = atan2(a.acceleration.x, a.acceleration.z) * RAD_TO_DEG;
  float accel_angle_x = atan2(-a.acceleration.y, sqrt(a.acceleration.x * a.acceleration.x + a.acceleration.z * a.acceleration.z)) * RAD_TO_DEG;

  // 4. 상보 필터 적용
  // X축 각도 계산
  imuData.angleX = 0.98 * (imuData.angleX + g.gyro.x * dt) + 0.02 * accel_angle_x;
  // Y축 각도 계산
  imuData.angleY = 0.98 * (imuData.angleY + g.gyro.y * dt) + 0.02 * accel_angle_y;
  // Z축은 보통 자이로만으로 계산 (Yaw)
  imuData.angleZ += g.gyro.z * dt;

  imuData.valid = true;
}
