#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ROMAN_STRING (40)

#define F_DBG

typedef struct {
	int dec;
	char symb;
} DEC_TO_CHAT_TYPE;

int romToDec( char* roman);
int charToDec(char oneChar);
int decToRom(int dec, char** rom);

int main() 
{
	char testRoman[] = "XDIV"; // MCMX - 1910
	int convertRoman = romToDec( testRoman);
	char* romanChar = NULL;
	
	if (convertRoman < 0)
	{
		printf(" Roman:%s: is invalid (error(%i))\n", testRoman, convertRoman);
	}
	else
	{
		printf(" Roman:%s: converted to (%i)\n", testRoman, convertRoman);
	
		(void)decToRom( convertRoman, &romanChar);
		if (romanChar != NULL)
		{
			printf(" Decimal(%i) converted to roman:%s:\n", convertRoman, romanChar);
			free(romanChar);
		}
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
#ifdef F_DBG
				printf(" res(%i) intermid(%i)\n", res, intermid);
#endif
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

int decToRom(int dec, char** rom)
{
	int res = 0;
	int number = dec;
	char romanRes[MAX_ROMAN_STRING];
	int  romanIndex = 0;
	
	DEC_TO_CHAT_TYPE numMap[] = {
		{1000, 'M'}, 
		{ 500, 'D'},
		{ 100, 'C'},
		{  50, 'L'},
		{  10, 'X'},
		{   5, 'V'},
		{   1, 'I'}
	};
	int sizeMap = (int)(sizeof(numMap)/sizeof(DEC_TO_CHAT_TYPE));
	
	for (int i=0; i<sizeMap; i++)
	{
		int symNum = (int)(number / numMap[i].dec);
#ifdef F_DBG		
		printf(" (%i) (%i) (%i)\n", i, number, symNum);
#endif
		if (symNum != 0)
		{
			if (   (symNum == 4)
			    && ((i == 2) || (i == 4 ) || (i == 5) || (i == 6 )))
			{
				romanRes[romanIndex++] = numMap[i].symb;
				romanRes[romanIndex++] = numMap[i-1].symb;
				number = number - numMap[i-1].dec + numMap[i].dec;
			}
			else
			{
				for (int j=0; j<symNum; j++)
				{
					romanRes[romanIndex++] = numMap[i].symb;
					number = number - numMap[i].dec;
				}
			}
		}
	}
	
	*rom = (char*)malloc( (strlen(romanRes)+1)*sizeof(char));
	memcpy( *rom, romanRes, (strlen(romanRes)+1)*sizeof(char));
	
	return res;
}
