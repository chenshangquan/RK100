#pragma once

void NetOrder2LocalOrder(TDTDevInfo& tDevInfo);						// 从网络序到本地序的转换,目前接收的数据只有TDTDevInfo类型


// 从PID解析设备类型名
std::string BrdID2DeviceType(u32 dwDevTypeId);

void		SCHSLEEP(u32 dwMilliseconds);							// 设置睡眠