#pragma once

void NetOrder2LocalOrder(TDTDevInfo& tDevInfo);						// �������򵽱������ת��,Ŀǰ���յ�����ֻ��TDTDevInfo����


// ��PID�����豸������
std::string BrdID2DeviceType(u32 dwDevTypeId);

void		SCHSLEEP(u32 dwMilliseconds);							// ����˯��