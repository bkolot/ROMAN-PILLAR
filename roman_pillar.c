#include <stdio.h>
#include <string.h>

typedef struct {
	int dec;
	char symb;
} DEC_TO_CHAT_TYPE;

/*
static DEC_TO_CHAT_TYPE numMap[] = {
	{   1, 'I'},
	{   5, 'V'},
    {  10, 'X'},
	{  50, 'L'},
	{ 100, 'C'},
    { 500, 'D'},
	{1000, 'M'}
};
static int sizeMap = (int)(sizeof(numMap)/sizeof(DEC_TO_CHAT_TYPE));
*/

int romToDec( char* roman);
int charToDec(char oneChar);

int main() 
{
	char testRoman[] = "XDIV";
	int convertRoman = romToDec( testRoman);
	
	if (convertRoman < 0)
	{
		printf(" Roman:%s: is invalid (error(%i))\n", testRoman, convertRoman);
	}
	else
	{
		printf(" Roman:%s: converted to (%i)\n", testRoman, convertRoman);
	}
	
	return 0;
}

int charToDec(char oneChar)
{
	int result = 0;
	
	switch (oneChar)
	{
		case 'I': result =    1; break;
		case 'V': result =    5; break;
		case 'X': result =   10; break;
		case 'L': result =   50; break;
		case 'C': result =  100; break;
		case 'D': result =  500; break;
		case 'M': result = 1000; break;
	}
	if (result == 0)
	{
//		Assert();
	}
	
	return result;
}

int romToDec( char* roman)
{
	int res = -1;
	int intermid = res;
	int romanLen = strlen(roman);
	
	if (romanLen > 0)
	{
		res = charToDec(roman[0]);
		intermid = res;
		if (romanLen > 1)
		{
			for (int i=1; ((i<romanLen) && (res>0)); i++)
			{
				printf(" res(%i) intermid(%i)\n", res, intermid);
				int thisNumber = charToDec(roman[i]);
				if (thisNumber > charToDec(roman[i-1]))
				{
					if (thisNumber > (res - intermid))
					{
						res = thisNumber - res;
						res = (res>0)?(res):(-2);
					}
					else
					{
						res = (res - intermid) + (thisNumber - intermid);
						res = (res>0)?(res):(-3);
					}
					intermid = 0;
				}
				else
				{
					if (thisNumber < charToDec(roman[i-1]))
					{
						intermid = thisNumber;
					}
					else
					{
						intermid = intermid + thisNumber;
					}
					res = res + thisNumber;
				}
			}
		}	
	}
	return res;
}
