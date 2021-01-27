#pragma once
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <memory>
using namespace std;


string encode_base64(const string sourceData){
	const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	const char padding = '=';
	int padlen = 0;

	string result;
	result.resize((sourceData.size() + 2) / 3 * 4);
	char *temp_char = &result[0];

	int i = 0;
	
	while (i < sourceData.size()) {
		// encode 3 bytes at a time
		int chunk = 0;
		chunk = chunk | int(char(sourceData.data()[i++])) << 16;
		if (i == sourceData.size()) {
			padlen = 2;
		}
		else {
			chunk = chunk | int(char(sourceData.data()[i++])) << 8;
			if (i == sourceData.size())
				padlen = 1;
			else
				chunk = chunk | int(char(sourceData.data()[i++]));
		}

		// get 4 index number
		int c1 = (chunk & 0xfc0000) >> 18;
		int c2 = (chunk & 0x03f000) >> 12;
		int c3 = (chunk & 0x000fc0) >> 6;
		int c4 = (chunk & 0x00003f);
		*temp_char++ = alphabet[c1];
		*temp_char++ = alphabet[c2];

		if (padlen == 2) {
			*temp_char++ = padding;
			*temp_char++ = padding;
		}
		else if (padlen == 1){
			*temp_char++ = alphabet[c3];
			*temp_char++ = padding;
		}
		else {
			*temp_char++ = alphabet[c3];
			*temp_char++ = alphabet[c4];
		}
	}

	return result;
}

string decode_base64(const string sourceData) {
	string result;
	result.resize((sourceData.size() * 3) / 4);
	char *temp_char = &result[0];
	int i = 0;

	while (i < sourceData.size()) {
		// decode 4 bytes at a time
		int ch[4],num[4];
		for (int j = 0; j < 4; j++) {
			ch[j] = sourceData.at(i++);
		}

		for (int j = 0; j < 4; j++) {
			if (ch[j] >= 'A' && ch[j] <= 'Z')
				num[j] = ch[j] - 'A';
			else if (ch[j] >= 'a' && ch[j] <= 'z')
				num[j] = ch[j] - 'a' + 26;
			else if (ch[j] >= '0' && ch[j] <= '9')
				num[j] = ch[j] - '0' + 52;
			else if (ch[j] == '+')
				num[j] = 62;
			else if (ch[j] == '/')
				num[j] = 63;
			else
				num[j] = 0;
		}

		int chunk = 0;
		chunk = chunk | num[0] << 18;
		chunk = chunk | num[1] << 12;
		chunk = chunk | num[2] << 6;
		chunk = chunk | num[3];

		// get 3 ASCII number
		int c1 = (chunk & 0xff0000) >> 16;
		int c2 = (chunk & 0x00ff00) >> 8;
		int c3 = (chunk & 0x0000ff);
		*temp_char++ = char(c1);
		*temp_char++ = char(c2);
		*temp_char++ = char(c3);
	}
	return result;
}