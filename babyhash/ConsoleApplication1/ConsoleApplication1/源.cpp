#include<iostream>
#include<string>
#include<vector>
#include"md5.h"
using namespace std;
//string flag = "SBCTF{Bao!!!in_md5_AND_rc4}";
string key_md5 = "f27d71f53ae17679fb352baa5ea326db";
vector<unsigned char> encflag = { 0xc3,0x64,0x16,0xc4,0xc0,0xf6,0xe9,0x34,0x08,0x62,0x26,0xc1,0x0a,0x2c,0xff,0x9d,0x5d,0x81,0x3f,0xfc,0x62,0x39,0xd8,0x1a,0xb4,0x70,0x0a };

void check(char a)
{
	if (a < 'a' || a>'z')
	{
		cout << "Wrong format!" << endl;
		exit(0);
	}
}

void rc4_enc(unsigned char* S_table, unsigned char* T_table, unsigned char* arr, unsigned int len, unsigned char* k, unsigned int len_k,char* newflag)
{
	int len1 = len;
	int i, j = 0, tmp, key, index = 0;
	for (i = 0; i < 256; i++)
	{
		S_table[i] = i;
		T_table[i] = k[i % len_k];
	}
	for (i = 0; i < 256; i++)
	{
		j = (j + S_table[i] + T_table[i]) % 256;
		tmp = S_table[j];
		S_table[j] = S_table[i];
		S_table[i] = tmp;
	}
	i = 0;
	j = 0;
	while (len > 0)
	{
		i = (i + 1) % 256;
		j = (j + S_table[i]) % 256;
		tmp = S_table[j];
		S_table[j] = S_table[i];
		S_table[i] = tmp;
		key = (S_table[i] + S_table[j]) % 256;
		arr[index] = arr[index] ^ S_table[key];
		index++;
		len--;
	}

	strcpy_s(newflag, len1+1,(char*)arr);


}

int main() {
	string flag;
	string str2;
	string S(256, 'c');
	string T(256, 'c');

	cout << "Input your key" << endl;
	cin >> str2;
	if (str2.length() != 6)
	{
		cout << "Wrong size!" << endl;
		exit(0);
	}
	for (int i = 0;i < 6;i++)
	{
		check(str2[i]);
	}

	string str1 = "12345";
	string str3 = "67890";
	string key = str1 + str2 + str3;
	//cout << md5(key) << endl;
	if (md5(key) != key_md5)
	{
		cout << "Wrong key!" << endl;
	}
	cout << "Right key!" << endl;
	cout << "Input your flag" << endl;
	cin >> flag;
	unsigned char newflag[40];
	rc4_enc((unsigned char*)S.c_str(), (unsigned char*)T.c_str(), (unsigned char*)flag.c_str(), flag.length(), (unsigned char*)key.c_str(), key.length(),(char*)newflag);
	for (int i = 0;i < encflag.size();i++)
	{
		if (newflag[i] != encflag[i])
		{
			cout << "Wrong flag!" << endl;
			exit(0);
		}
	}
	cout << "Right flag!" << endl;
	return 0;
}