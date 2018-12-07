#pragma once
#include <string>
using namespace std;

class CMD5
{
public:
	CMD5(void);
	~CMD5(void);

	static string HexToString(unsigned char* aby, int nNum);
	static u8* MD5String(const char* string, u8* szOut);
	static bool MD5Authen(char* szUser, char* szPwd, u8* abySecureCode, TDAuthen *ptAuthen); // 普通鉴权
	static bool SetNewPwd(char* szPwdIn, u8* abySecureCode, char* szPwdOut);
	static bool MD5AuthenSecure(u8* abySecureCode, TDAuthen *ptAuthen,char* abyMaster); // 安全码方式鉴权
};
