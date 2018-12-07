#include "stdall.h"
#include "publicfun.h"
#include "devtrackconst.h"
#include "nvrconst.h"
#ifdef WIN32

#else
#include <unistd.h>
#endif // WIN32


void NetOrder2LocalOrder(TDTDevInfo &tDevInfo)
{
	tDevInfo.dwBrdID = ntohl(tDevInfo.dwBrdID);
	tDevInfo.dwTickCount = ntohl(tDevInfo.dwTickCount);

	tDevInfo.tAddr.bDHCPServ = tDevInfo.tAddr.bDHCPServ;
	tDevInfo.tAddr.bDHCPOpen = tDevInfo.tAddr.bDHCPOpen;
	tDevInfo.tAddr.dwIpaddr = ntohl(tDevInfo.tAddr.dwIpaddr);
	tDevInfo.tAddr.dwNetmask = ntohl(tDevInfo.tAddr.dwNetmask);
	tDevInfo.tAddr.dwGateWay = ntohl(tDevInfo.tAddr.dwGateWay);

	tDevInfo.tRegPlat.dwRegIP = ntohl(tDevInfo.tRegPlat.dwRegIP);
	tDevInfo.tRegPlat.wRegPort = ntohs(tDevInfo.tRegPlat.wRegPort);
}

void SCHSLEEP(u32 dwMilliseconds)
{
#ifdef WIN32
	Sleep(dwMilliseconds);
#else
	usleep(dwMilliseconds * 1000);
#endif
}

std::string BrdID2DeviceType(u32 dwDevTypeId)
{
#ifdef WIN32
    u16 wHID = HIWORD(dwDevTypeId);
    u16 wPID = LOWORD(dwDevTypeId);
#else
    u16 wHID = dwDevTypeId >> 16 & 0xffff;
    u16 wPID = dwDevTypeId & 0xffff;
#endif // WIN32

	switch (wHID)
	{
	case HID_KDM2820_4:         return DEV_NVR2820_4;
	case HID_KDM2820_9:         return DEV_NVR2820_9;
	case HID_KDM2820_16:        return DEV_NVR2820_16;
	case HID_KDM2820E_9:        return DEV_NVR2820E_9;
	case HID_KDM2820E_16:       return DEV_NVR2820E_16;
	case HID_NVR2860:           return DEV_NVR2860;
	case HID_NVR2882:
	{
		if (wPID == PID_NVR2882_01 || wPID == PID_NVR2882_02 || wPID == PID_NVR2882_03)
		{
			return DEV_NVR2882;
		}
		else
		{
			return DEV_NVR2882;
		}
	}
	case HID_NVR201S:           return DEV_KDM201S;
	case HID_NVR2840:           return DEV_NVR2840;
	case HID_NVRD01:            return DEV_NVR_D01;
	case HID_NVR2820L:          return DEV_NVR2820L;
	case HID_NVR2880:			return DEV_NVR2880;
	case HID_NVR2820A:          return DEV_NVR2820A;
	case HID_NVR2820E4:			return DEV_NVR2820E4;
	case HID_NVR2820E4HD:		return DEV_NVR2820E4HD;
	case HID_KDM2510_D01F:
	{
		if (wPID == PID_D01F_KDM201)  return DEV_NVR201_D01F;
		else if (wPID == PID_D01F_KDM2510) return DEV_NVR2510_D01F;
		else
		{
			return DEV_KDM_D01F;
		}
	}
	case HID_KDM_D04F:
	{
		if (wPID == PID_D04F_KDM201) return DEV_KDM201_D04F;
		else if (wPID == PID_D04F_KDM2510) return DEV_KDM2510_D04F;
		else
		{
			return DEV_KDM_D04F;
		}
	}
	case HID_KDM2820EA:
	{
		if (wPID == 0xff)
			return DEV_NVR2820E_G;
	}
	return DEV_NVR2820EA;
	//
	case HID_NVR2820H16ND:		return DEV_NVR2820H_16ND;
		//
	case HID_KDM2860E:			return DEV_NVR2860E;
	case HID_KDM2860E16:		return DEV_NVR2860E16;
	case HID_KDM2860E32:		return DEV_NVR2860E32;
	case HID_KDM2860E48:		return DEV_NVR2860E48;
	case HID_KDM2860E64:		return DEV_NVR2860E64;
		//
	case HID_KDM1821_9:			return DEV_NVR1821_9HD;
	case HID_KDM1821_16:		return DEV_NVR1821_16HD;
	case HID_KDM1821_32:		return DEV_NVR1821_32HD;
		//
	case HID_KDM1822_9HD:		return DEV_NVR1822_9HD;
	case HID_KDM1822_16HD:		return DEV_NVR1822_16HD;
	case HID_KDM1822_32HD:		return DEV_NVR1822_32HD;
		//
	case HID_KDM1822_9ND:		return DEV_NVR1822_9ND;
	case HID_KDM1822_16ND:		return DEV_NVR1822_16ND;
	case HID_KDM1822_32ND:		return DEV_NVR1822_32ND;
		//
	case HID_KDM1822_4HDA:      return DEV_NVR1822_4HDA;
	case HID_KDM1822_9HDA:      return DEV_NVR1822_9HDA;
	case HID_KDM1822_16HDA:		return DEV_NVR1822_16HDA;
		//
	case HID_KDM1825_4HD:       return DEV_NVR1825_4HD;
	case HID_KDM1825_9HD:       return DEV_NVR1825_9HD;
	case HID_KDM1825_4HP:		return DEV_NVR1825_4HP;
	case HID_KDM1825_9HP:       return DEV_NVR1825_9HP;
	case HID_KDM1825_4HDA:		return DEV_NVR1825_4HDA;
	case HID_KDM1825_4HPA:      return DEV_NVR1825_4HPA;
		//
	case HID_NVR1821:           return DEV_NVR1821;
	case HID_NVR1821_1037:      return DEV_NVR1821V2;
	case HID_NVR1825:           return DEV_NVR1825;
	case HID_NVR1822:           return DEV_NVR1822;
	case HID_NVR2821H:          return DEV_NVR2821H;
	case HID_SVR282X_D02X_P_T:
	{
		switch (wPID)
		{
		case    PID_SVR2820_D02H_P_T: return DEV_SVR2820_D02H_P_T;
		case    PID_SVR2822_D02H_P_T: return DEV_SVR2822_D02H_P_T;
		case    PID_SVR2822_D02E_P_T: return DEV_SVR2822_D02E_P_T;
		}
	}
	break;
	case HID_SVR2922_D02E_P_T:
	{
		switch (wPID)
		{
		case	PID_SVR2922_D02E_P_T: return DEV_SVR2922_D02E_P_T;
		}
	}
	break;
	case HID_SVR2916_X04E_X:
	{
		switch (wPID)
		{
		case PID_SVR2916_D04E_N: return DEV_SVR2916_D04E_N;
		case PID_SVR2916_D04E_S: return DEV_SVR2916_D04E_S;
		case PID_SVR2916_B04E_N: return DEV_SVR2916_B04E_N;
		case PID_SVR2916_B04E_S: return DEV_SVR2916_B04E_S;
		case PID_SVR2916_D08E_N: return DEV_SVR2916_D08E_N;
		case PID_SVR2916_D08E_S: return DEV_SVR2916_D08E_S;
		case PID_SVR2916_B08E_N: return DEV_SVR2916_B08E_N;
		case PID_SVR2916_B08E_S: return DEV_SVR2916_B08E_S;
		}
	}
	break;
	case HID_SVR2726_N04X_X:
	{
		switch (wPID)
		{
		case PID_SVR2726_N04H_B:return DEV_SVR2726_N04H_B;
		case PID_SVR2726_N04H_M:return DEV_SVR2726_N04H_M;
		case PID_SVR2726_N04E_B:return DEV_SVR2726_N04E_B;
		case PID_SVR2726_N04E_M:return DEV_SVR2726_N04E_M;

		case PID_SVR2726_N04H_BV:return DEV_SVR2726_N04H_BV;
		case PID_SVR2726_N04H_MV:return DEV_SVR2726_N04H_MV;
		case PID_SVR2726_N04E_BV:return DEV_SVR2726_N04E_BV;
		case PID_SVR2726_N04E_MV:return DEV_SVR2726_N04E_MV;

		case PID_CVS_HD2_B:return DEV_CVS_HD2_B;
		case PID_CVS_HD2_M:return DEV_CVS_HD2_M;
		case PID_CVS_HD2E_B:return DEV_CVS_HD2E_B;
		case PID_CVS_HD2E_M:return DEV_CVS_HD2E_M;
		case PID_CVS_HD2_BV:return DEV_CVS_HD2_BV;
		case PID_CVS_HD2_MV:return DEV_CVS_HD2_MV;
		case PID_CVS_HD2E_BV:return DEV_CVS_HD2E_BV;
		case PID_CVS_HD2E_MV:return DEV_CVS_HD2E_MV;
		}
	}
	break;

	case HWID_NVR2860E_VERB_HD16:return DEV_NVR2860E_VERB;
	case HWID_NVR2860E_VERB_HD32:return DEV_NVR2860E_VERB;
	case HWID_NVR2860E_VERB_HD48:return DEV_NVR2860E_VERB;
	case HWID_NVR2860E_VERB_HD64:return DEV_NVR2860E_VERB;

	case HID_NVR1825_HD4:
		switch (wPID)
		{
		case  PID_NVR1825_VERB_4HD:	return DEV_NVR1825_4HD_VERB;
		case  PID_NVR1825_HD4: return DEV_NVR1825_HD4;
		}
	case HID_NVR1825_HDA4:
		switch (wPID)
		{
		case PID_NVR1825_HDA4: return DEV_NVR1825_HDA4;
		}
	case HID_NVR1825_HD9:
		switch (wPID)
		{
		case PID_NVR1825_HD9: return DEV_NVR1825_HD9;
		case PID_NVR1825_VERB_9HD:	return DEV_NVR1825_9HD_VERB;
		}
	case HID_NVR1825_HDA9:
		switch (wPID)
		{
		case PID_NVR1825_HDA9: return DEV_NVR1825_HDA9;
		}
	case HID_NVR1825_HD16:
		switch (wPID)
		{
		case PID_NVR1825_HD16: return DEV_NVR1825_HD16;
		case PID_NVR1825_VERB_16HD:	return DEV_NVR1825_16HD_VERB;
		}
	case HID_NVR1825_HD32:
		switch (wPID)
		{
		case PID_NVR1825_HD32: return DEV_NVR1825_HD32;
		}
	case HID_NVR1825_HDA16:
		switch (wPID)
		{
		case PID_NVR1825_HDA16: return DEV_NVR1825_HDA16;
		}
		return DEV_NVR1825_VB;

	case HID_NVR1822_HDA32:
		switch (wPID)
		{
		case PID_NVR1822_HDA32: return DEV_NVR1822_HDA32;
		case PID_NVR1822_VERB_32HDA: return DEV_NVR1822_32HDA_VERB;
		}
	case HID_NVR1822_HDA916:
		switch (wPID)
		{
		case PID_NVR1822_HDA9: return DEV_NVR1822_HDA9;
		case PID_NVR1822_HDA16: return DEV_NVR1822_HDA16;
		}
	case HID_NVR1822_HD91632:
		switch (wPID)
		{
		case PID_NVR1822_HD9: return DEV_NVR1822_HD9;
		case PID_NVR1822_HD16: return DEV_NVR1822_HD16;
		case PID_NVR1822_HD32: return DEV_NVR1822_HD32;
		}
		return DEV_NVR1822_VB;

	case HID_IPC2110_BN:return DEV_IPC2110_BN;
	case HID_IPC2150_BN:return DEV_IPC2150_BN;
	case HID_IPC113_DN:return DEV_IPC113_DN;
	case HID_IPC123_DN:return DEV_IPC123_DN;
	case HID_IPC123_EN:return DEV_IPC123_EN;
	case HID_SVR2812_D04:
		switch (wPID)
		{
		case  PID_SVR2812_D04:	return DEV_SVR2812_D04;
		case  PID_SVR2812_D04E: return DEV_SVR2812_D04E;
		}
		break;
	case HID_ATBOX_A:			return DEV_ATBOX_A;
	case HID_KDM201_CMIS:		return DEV_KDM201_CMIS;
	case HID_NVR2881_XHD:
		switch (wPID)
		{
		case PID_NVR2881_HD64:
		{
// 			if (IsDefMacro(EM_VERSION_CUSTOM_LG))
// 				return DEV_LRN8640N;
// 			else
 				return DEV_NVR2881_HDX;
		}
		default:	return DEV_NVR2881_HDX;
		}
	case HID_NVR2881_HDI:		return DEV_NVR2881_HDI;


	case HID_SVR2916_X04E_XX:
		switch (wPID)
		{
		case PID_SVR2916_D04E_NJ:return SVR2916_D04E_NJ;
		case PID_SVR2916_D04E_PJ:return SVR2916_D04E_PJ;
		case PID_SVR2916_D04E_SJ:return SVR2916_D04E_SJ;
		case PID_SVR2916_B04E_NJ:return SVR2916_B04E_NJ;
		case PID_SVR2916_B04E_PJ:return SVR2916_B04E_PJ;
		case PID_SVR2916_B04E_SJ:return SVR2916_B04E_SJ;
		}
		break;

	case HID_NVR1821_9HD_C:
		switch (wPID)
		{
		case PID_NVR1821_9HD_C: return DEV_NVR1821_9HD_C;
		case PID_NVR1821_16HD_C: return DEV_NVR1821_16HD_C;
		case PID_NVR1821_32HD_C: return DEV_NVR1821_32HD_C;
		case PID_NVR1821_64HD_C: return DEV_NVR1821_64HD_C;
		}
		break;

	case HID_NVR1821_9HDA_C:
		switch (wPID)
		{
		case PID_NVR1821_9HDA_C: return DEV_NVR1821_9HDA_C;
		case PID_NVR1821_16HDA_C: return DEV_NVR1821_16HDA_C;
		case PID_NVR1821_32HDA_C: return DEV_NVR1821_32HDA_C;
		}
		break;

	case HID_NVR2822_HD:
		switch (wPID)
		{
		case PID_NVR2822_9HD: return DEV_NVR2822_9HD;
		case PID_NVR2822_16HD: return DEV_NVR2822_16HD;
		case PID_NVR2822_32HD: return DEV_NVR2822_32HD;
		}
		break;

	case HID_NVR2822_HDA:
		switch (wPID)
		{
		case PID_NVR2822_9HDA: return DEV_NVR2822_9HDA;
		case PID_NVR2822_16HDA: return DEV_NVR2822_16HDA;
		case PID_NVR2822_32HDA: return DEV_NVR2822_32HDA;
		}
		break;

	case HID_NVR2821H_HL:
		switch (wPID)
		{
		case PID_NVR2821H_9HL: return DEV_NVR2821H_9HL;
		case PID_NVR2821H_16HL: return DEV_NVR2821H_16HL;
		case PID_NVR2821H_32HL: return DEV_NVR2821H_32HL;
		case PID_NVR2821H_64HL: return DEV_NVR2821H_64HL;
		}
		break;

	default:                    break;
	}

	switch (wPID)
	{
	case    PID_NVR2820:        return  DEV_NVR2820;
	case    PID_NVR2860:        return  DEV_NVR2860;
	case    PID_NVR2820_4:      return  DEV_NVR2820_4;
	case    PID_NVR2820_9:      return  DEV_NVR2820_9;
	case    PID_NVR2820_16:     return  DEV_NVR2820_16;
	case    PID_NVR2820E_9:     return  DEV_NVR2820E_9;
	case    PID_NVR2820E_16:    return  DEV_NVR2820E_16;
	case    PID_KDM2130:        return  DEV_KDM2130;
	case    PID_KDM2700:        return  DEV_KDM2700;
	case    PID_KDM2701:        return  DEV_KDM2701;
	case    PID_KDM2131:        return  DEV_KDM2131;
	case    PID_KDM2122:        return  DEV_KDM2122;
	case    PID_KDM2122N:       return  DEV_KDM2122N;
	case    PID_KDM2123:        return  DEV_KDM2123;
	case    PID_KDM2310:        return  DEV_KDM2310;
	case    PID_KDM2311:        return  DEV_KDM2311;
	case    PID_IPA100:         return  DEV_IPA100;
	case    PID_IPA101:         return  DEV_IPA101;
	case    PID_IPM100:         return  DEV_IPM100;
	case    PID_IPM101:         return  DEV_IPM101;
	case    PID_IPC201:         return  DEV_IPC201;
	case    PID_IPC300:         return  DEV_IPC300;
	case    PID_IPC301:         return  DEV_IPC301;
	case    PID_IPA102:         return  DEV_IPA102;
	case    PID_IPC100:         return  DEV_IPC100;
	case    PID_IPC302:         return  DEV_IPC302;
	case    PID_IPC200:         return  DEV_IPC200;
	case    PID_IPC202:         return  DEV_IPC202;
	case    PID_IPC400:         return  DEV_IPC400;
	case    PID_IPA100A:        return  DEV_IPA100A;
	case    PID_IPA100AL:       return  DEV_IPA100AL;
	case    PID_IPA102L:        return  DEV_IPA102L;
	case    PID_IPM100A:        return  DEV_IPM100A;
	case    PID_NVR2820E_9D:    return  DEV_NVR2820E_9D;
	case    PID_NVR2820E_16D:   return  DEV_NVR2820E_16D;
	case    PID_KDM201S:        return  DEV_KDM201S;
	case    PID_IPC120:         return  DEV_IPC120;
	case    PID_IPC130:         return  DEV_IPC130;
	case    PID_IPC220:         return  DEV_IPC220;
	case    PID_IPC230:         return  DEV_IPC230;
	case    PID_KDM201S_C04E:   return  DEV_KDM201S_C04E;
	case    PID_IPC201L:        return  DEV_IPC201L;
	case    PID_IPC302P_W:      return  DEV_IPC302P_W;
	case    PID_IPC302PL:       return  DEV_IPC302PL;
	case    PID_IPC302PL_W:     return  DEV_IPC302PL_W;
	case    PID_IPC110M:        return  DEV_IPC110M;
	case    PID_IPC212M:        return  DEV_IPC212M;
	case    PID_IPC810M:        return  DEV_IPC810M;
	case    PID_IPC410M:        return  DEV_IPC410M;
	case    PID_IPC812:         return  DEV_IPC812;
	case    PID_NVR_D01:        return  DEV_NVR_D01;
	case    PID_IPC510:         return  DEV_IPC510;
	case    PID_IPC412:         return  DEV_IPC412;
	case    PID_IPC211:         return  DEV_IPC211;
	case    PID_IPC112:         return  DEV_IPC112;
	case    PID_IPC210:         return  DEV_IPC210;
	case    PID_IPC812C:        return  DEV_IPC812C;
	case    PID_IPC510A:        return  DEV_IPC510A;
	case    PID_IPC412A:        return  DEV_IPC412A;
	case	PID_NVR2820L:       return  DEV_NVR2820L;
	case    PID_IPC512:			return  DEV_IPC512;
	case    PID_IPC412T:        return  DEV_IPC412T;
	case    PID_IPC212A:        return  DEV_IPC212A;
	case	PID_IPC420:         return  DEV_IPC420;
	case    PID_IPC310:         return  DEV_IPC310;
	case	PID_KDMC01h:        return  DEV_KDMC01H;
	case    PID_SVR2810_D:      return	DEV_SVR2810_D;
	case    PID_SVR2810_B:      return  DEV_SVR2810_B;
	case    PID_SVR2810_D04:	return  DEV_SVR2810_D04;
	case    PID_SVR2810_B04:	return  DEV_SVR2810_B04;
	case    PID_SVR2810E_D04:   return  DEV_SVR2810E_D04;
	case    PID_SVR2810E_B04:   return  DEV_SVR2810E_B04;
	case    PID_SVR2810_D08:    return  DEV_SVR2810_D08;
	case    PID_SVR2910_D16:    return  DEV_SVR2910_D16;
	case    PID_SVR2910_B16:    return  DEV_SVR2910_B16;
	case    PID_SVR2910_D16V:	return  DEV_SVR2910_D16V;
	case    PID_SVR2910_B16V:	return  DEV_SVR2910_B16V;
	case    PID_SVR2910E_D16:	return  DEV_SVR2910E_D16;
	case    PID_SVR2910E_B16:	return  DEV_SVR2910E_B16;
	case    PID_SVR2910E_D16V:	return  DEV_SVR2910E_D16V;
	case    PID_SVR2910E_B16V:	return  DEV_SVR2910E_B16V;
	case    PID_SVR29ES_M001:	return  DEV_SVR29ES_M001;
	case    PID_SVR29ES_D01G:	return  DEV_SVR29ES_D01G;
	case    PID_SVR29ES_C01H:	return  DEV_SVR29ES_C01H;
	case    PID_SVR2720_H09E:   return  DEV_SVR2720_H09E;
	case    PID_SVR27ES_M001:   return  DEV_SVR27ES_M001;
	case    PID_SVR27ES_C01H:   return  DEV_SVR27ES_C01H;
	case    PID_SVR27ES_D01G:   return  DEV_SVR27ES_D01G;
	case    PID_SVR2812_D04E:   return  DEV_SVR2812_D04E;
	case    PID_SVR2720_H04:    return  DEV_SVR2720_H04;
	case    PID_SVR2816_D04H_N: return  DEV_SVR2816_D04H_N;
	case    PID_SVR2816_D04H_P: return  DEV_SVR2816_D04H_P;
	case    PID_SVR2816_D04H_S: return  DEV_SVR2816_D04H_S;
	case    PID_SVR2816_D04E_N: return  DEV_SVR2816_D04E_N;
	case    PID_SVR2816_D04E_P: return  DEV_SVR2816_D04E_P;
	case    PID_SVR2816_D04E_S: return  DEV_SVR2816_D04E_S;
	case    PID_SVR2816_B04E_N: return  DEV_SVR2816_B04E_N;
	case    PID_SVR2816_B04E_P: return  DEV_SVR2816_B04E_P;
	case    PID_SVR2816_B04E_S: return  DEV_SVR2816_B04E_S;
	case    PID_IPC412_A:         return  DEV_IPC412_A;
	case    PID_IPC413_A:       return  DEV_IPC413_A;
	case    PID_IPC320_A:       return  DEV_IPC320_A;
	case    PID_IPC400P_A:      return  DEV_IPC400P_A;
	case    PID_IPC512_A:       return  DEV_IPC512_A;
	case    PID_IPC521_A:       return  DEV_IPC521_A;
	case    PID_IPC511_A:       return  DEV_IPC511_A;
	case    PID_IPC423_A:       return  DEV_IPC423_A;
	case    PID_IPC822_A:       return  DEV_IPC822_A;
	case    PID_IPC420_A:		return  DEV_IPC420_A;
	case    PID_IPC420_B:       return  DEV_IPC420_B;
	case    PID_IPC223:			return  DEV_IPC223;
	case    PID_IPC412_B:       return  DEV_IPC412_B;
	case    PID_IPC413_B:       return  DEV_IPC413_B;
	case    PID_IPC423_B:       return  DEV_IPC423_B;
	case    PID_IPC120_L:       return  DEV_IPC120_L;
	case    PID_IPC112E_L:      return  DEV_IPC112E_L;
	case    PID_IPC211E_L:      return  DEV_IPC211E_L;
	case    PID_IPC221_L:       return  DEV_IPC221_L;
	case    PID_IPC223_C0:      return  DEV_IPC223_C0;
	case    PID_IPC120_P:       return  DEV_IPC120_P;
	case    PID_IPC112E_P:      return  DEV_IPC112E_P;
	case    PID_IPC812_A_X20:   return  DEV_IPC812_A_X20;
	case    PID_IPC112E:        return  DEV_IPC112E;
	case    PID_IPC212A_BO:     return  DEV_IPC212A_BO;
	case    PID_IPC212E:        return  DEV_IPC212E;
	case    PID_IPC221:         return  DEV_IPC221;
	case    PID_HDC420_A:       return  DEV_HDC420_A;
	case    PID_HDC420_B:       return  DEV_HDC420_B;
	case    PID_IPC232_A:       return  DEV_IPC232_A;
	case    PID_IPC213_A:       return  DEV_IPC213_A;
	case    PID_IPC216_A:       return  DEV_IPC216_A;
	case    PID_LC110_A:        return  DEV_LC110_A;
	case    PID_LC210_A1:       return  DEV_LC210_A1;
	case    PID_LC211_A0:       return  DEV_LC211_A0;
	case    PID_IPC214_A:       return  DEV_IPC214_A;
	case    PID_IPC120_A:       return  DEV_IPC120_A;
	case    PID_LC413_B:        return  DEV_LC413_B;
	case    PID_LC412_B:        return  DEV_LC412_B;
	case    PID_LC420_B:        return  DEV_LC420_B;
	case    PID_LC423_B:        return  DEV_LC423_B;
	case    PID_LC120_AN:       return  DEV_LC120_AN;
	case    PID_LC2200_AN:      return  DEV_LC2200_AN;
	case    PID_LC2200_BN:      return  DEV_LC2200_BN;
	case    PID_LC2240_AN:      return  DEV_LC2240_AN;
	case    PID_KDMC02H_SDI_KDM2412_C02H_SDI: return DEV_KDMC02H_SDI_KDM2412_C02H_SDI;
	case    PID_SVR2820_D02H_P:  return DEV_SVR2820_D02H_P;
	case    PID_SVR2822_D02H_P:  return DEV_SVR2822_D02H_P;
	case    PID_Mbox4_HD2:       return DEV_Mbox4_HD2;
	case    PID_Mbox4_HD2E:      return DEV_Mbox4_HD2E;
	case    PID_AIC_950_C01H:    return DEV_AIC_950_C01H;
	case    PID_AIC_950_M001:    return DEV_AIC_950_M001;
	case    PID_D01F_KDM201:     return DEV_NVR201_D01F;
	case    PID_D01F_KDM2510:    return DEV_NVR2510_D01F;
	case    PID_HDC8118_N0:      return DEV_HDC8118_N0;
	case    PID_IPC120_B:        return DEV_IPC120_B;
	case    PID_IPC112_B:        return DEV_IPC112_B;
	case    PID_IPC2230_AS:      return DEV_IPC2230_AS;
	case    PID_IPC2230_AN:      return DEV_IPC2230_AN;
	case    PID_IPC213_AS:       return DEV_IPC213_AS;
	case    PID_IPC2250_AN:      return DEV_IPC2250_AN;
	case    PID_IPC2150_AN:      return DEV_IPC2150_AN;
	case    PID_IPC123_AN:       return DEV_IPC123_AN;
	case    PID_IPC123_AS:       return DEV_IPC123_AS;
	case    PID_IPC113_AN:       return DEV_IPC113_AN;
	case    PID_SC1:             return DEV_SC1;
	case    PID_LC2150:          return DEV_LC2150;
	case    PID_LC2250:          return DEV_LC2250;
	case    PID_LC2110:          return DEV_LC2110;
	case    PID_LC2210:          return DEV_LC2210;
	case    PID_IPC2251:         return DEV_IPC2251;
	case    PID_IPC2151:         return DEV_IPC2151;
	case    PID_IPC625_A_C:      return DEV_IPC625_A_C;
	case    PID_IPC625_D_S:      return DEV_IPC625_D_S;
	case    PID_SVR2822_D02E_P:   return DEV_SVR2822_D02E_P;
	case    PID_SVR2820_D02E_P:   return DEV_SVR2820_D02E_P;
	case    PID_SVR2820_D02H_P_T: return DEV_SVR2820_D02H_P_T;
	case    PID_SVR2822_D02H_P_T: return DEV_SVR2822_D02H_P_T;
	case    PID_SVR2822_D02E_P_T: return DEV_SVR2822_D02E_P_T;
	case    PID_SVR2922_D02E_P_T: return DEV_SVR2922_D02E_P_T;

	case	PID_SVR2916_D04E_N: return DEV_SVR2916_D04E_N;
	case	PID_SVR2916_D04E_S: return DEV_SVR2916_D04E_S;
	case	PID_SVR2916_B04E_N: return DEV_SVR2916_B04E_N;
	case	PID_SVR2916_B04E_S: return DEV_SVR2916_B04E_S;
	case	PID_SVR2916_D08E_N: return DEV_SVR2916_D08E_N;
	case	PID_SVR2916_D08E_S: return DEV_SVR2916_D08E_S;
	case	PID_SVR2916_B08E_N: return DEV_SVR2916_B08E_N;
	case	PID_SVR2916_B08E_S: return DEV_SVR2916_B08E_S;

	case	PID_SVR2726_N04H_B: return DEV_SVR2726_N04H_B;
	case	PID_SVR2726_N04H_M: return DEV_SVR2726_N04H_M;
	case	PID_SVR2726_N04E_B: return DEV_SVR2726_N04E_B;
	case	PID_SVR2726_N04E_M: return DEV_SVR2726_N04E_M;

	case	PID_NVR2860E_VERB_HD16:return DEV_NVR2860E_VERB;
	case	PID_NVR2860E_VERB_HD32:return DEV_NVR2860E_VERB;
	case	PID_NVR2860E_VERB_HD48:return DEV_NVR2860E_VERB;
	case	PID_NVR2860E_VERB_HD64:return DEV_NVR2860E_VERB;

	case	PID_SVR2726_N04H_BV:return DEV_SVR2726_N04H_BV;
	case	PID_SVR2726_N04H_MV:return DEV_SVR2726_N04H_MV;
	case	PID_SVR2726_N04E_BV:return DEV_SVR2726_N04E_BV;
	case	PID_SVR2726_N04E_MV:return DEV_SVR2726_N04E_MV;

	case	PID_CVS_HD2_B:return DEV_CVS_HD2_B;
	case	PID_CVS_HD2_M:return DEV_CVS_HD2_M;
	case	PID_CVS_HD2E_B:return DEV_CVS_HD2E_B;
	case	PID_CVS_HD2E_M:return DEV_CVS_HD2E_M;
	case	PID_CVS_HD2_BV:return DEV_CVS_HD2_BV;
	case	PID_CVS_HD2_MV:return DEV_CVS_HD2_MV;
	case	PID_CVS_HD2E_BV:return DEV_CVS_HD2E_BV;
	case	PID_CVS_HD2E_MV:return DEV_CVS_HD2E_MV;

	case	PID_NVR1825_HD16_32:return DEV_NVR1825_VB;
		//case	PID_NVR1825_HD32	:return DEV_NVR1825_VB;
	case	PID_NVR1825_HD49:return DEV_NVR1825_VB;
	case	PID_NVR1825_HDA49:return DEV_NVR1825_VB;
	case	PID_NVR1822_HD91632:return DEV_NVR1822_VB;
	case	PID_NVR1822_HDA91632:return DEV_NVR1822_VB;
	case	PID_SVR2812_D04:return DEV_SVR2812_D04;
	case	PID_IPC2110_BN:return DEV_IPC2110_BN;
	case	PID_IPC2150_BN:return DEV_IPC2150_BN;
	case	PID_IPC113_DN:return DEV_IPC113_DN;
	case	PID_IPC123_DN:return DEV_IPC123_DN;
	case	PID_IPC123_EN:return DEV_IPC123_EN;
	case	PID_IPC2152_AN:return DEV_IPC2152_AN;
	case	PID_IPC2252_AN:return DEV_IPC2252_AN;
	case	PID_IPC2110_AN:return DEV_IPC2110_AN;
	case	PID_IPC2210_AN:return DEV_IPC2210_AN;
	case	PID_IPC2131_DN_IR:
	case	PID_IPC2131_DN_L:
		return DEV_IPC2131_DN;
	case	PID_IPC2231_DN_IR:
	case	PID_IPC2231_DN_L:
		return DEV_IPC2231_DN;
	case	PID_IPC2231_EN_L:return DEV_IPC2131_EN;
	case		PID_HDC_217IP:return DEV_HDC_217IP;
	case	PID_ATBOX_A:return DEV_ATBOX_A;
	case	PID_KDM201_CMIS:return DEV_KDM201S_C04E;

	case    PID_NVR2881_HD32:	return DEV_NVR2881_HDX;
	case    PID_NVR2881_HD64:	return DEV_NVR2881_HDX;
	case    PID_NVR2881_HD128:	return DEV_NVR2881_HDX;

	case    PID_NVR2881_HDI32:	return DEV_NVR2881_HDI;
	case    PID_NVR2881_HDI64:	return DEV_NVR2881_HDI;
	case    PID_NVR2881_HDI128:	return DEV_NVR2881_HDI;

	case	PID_SVR2916_D04E_NJ:return SVR2916_D04E_NJ;
	case	PID_SVR2916_D04E_PJ:return SVR2916_D04E_PJ;
	case	PID_SVR2916_D04E_SJ:return SVR2916_D04E_SJ;
	case	PID_SVR2916_B04E_NJ:return SVR2916_B04E_NJ;
	case	PID_SVR2916_B04E_PJ:return SVR2916_B04E_PJ;
	case	PID_SVR2916_B04E_SJ:return SVR2916_B04E_SJ;

	default:                    break;
	}

	if (wHID == 0x0125)
		return std::string("SVR2810/SVR2820E"); //ºÊ»›¿œ∞Ê±æSVR

	return std::string("unknowdev");
}
