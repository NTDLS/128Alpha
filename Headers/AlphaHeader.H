//////////////////////////////////////////////////////////////////////

#define TitleCaption "128Alpha - NetWorkDLS"

extern int Error(char *);
extern int CharInt (char *);
extern char *IntChar (double );
extern char *Get_TempDirectory (void);

//////////////////////////////////////////////////////////////////////

extern char *Get_TempDirectory ()
{
	static char StrFunction [64][257];
	static int StrCnt;
	static char T [257];
	GetTempPath (256,T);
	if (++StrCnt==64) StrCnt = 0;
	sprintf(StrFunction[StrCnt],"%s",T);
	return StrFunction[StrCnt];
}

//////////////////////////////////////////////////////////////////////

extern char *IntChar (double d)
{
	static int   StrCnt;
	LPSTR StrFunc [16];
	if (++StrCnt==16) StrCnt = 0;
	if (StrFunc[StrCnt]) free (StrFunc[StrCnt]);
	StrFunc[StrCnt] = (char*) malloc (2048);
	memset (StrFunc[StrCnt],0,2048);
	sprintf(StrFunc[StrCnt],"% .16g",d);
	return StrFunc[StrCnt];
}

//////////////////////////////////////////////////////////////////////

extern int CharInt(char *string2convert)
{
	int i, lenght_string;
	int power;
	int tmp_number;
	char tmp_char;

	if (!string2convert)
	{
		string2convert = "0";
		Error("Char To Integer Conversion Error.");
	}
	lenght_string = strlen(string2convert);
	for(i = 0; i < (lenght_string / 2); i++)
	{
		tmp_char = string2convert[i];
		string2convert[i] = string2convert[lenght_string - 1 - i];
		string2convert[lenght_string - 1 - i] = tmp_char;
	}
	power = 1;
	i = 0;
	tmp_number = 0;
	while (string2convert[i] != '\0')
	{
		tmp_number += (string2convert[i] - '0') * power;
		power *= 10;
		i++;
	}
	return tmp_number;
}

//////////////////////////////////////////////////////////////////////

extern int Error(char *Message)
{
	MessageBox (GetActiveWindow(), Message ,TitleCaption,0 + MB_ICONHAND + MB_SYSTEMMODAL);
    exit(0);
    return 0;
}
