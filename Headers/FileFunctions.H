static char F[2048];
int   StrCnt;
LPSTR StrFunc [16];


extern char * curdir (void);
extern int OpenFileDialog (HWND, char *, char *, char *, char *, char *, int );



extern char *curdir (void)
{
	if (++StrCnt==16) StrCnt = 0;
	if (StrFunc[StrCnt]) free (StrFunc[StrCnt]);
	StrFunc[StrCnt] = (char*) malloc (2048);
	memset (StrFunc[StrCnt],0,2048);
	GetCurrentDirectory (1024,StrFunc[StrCnt]);
	return StrFunc[StrCnt];
}

extern int OpenFileDialog (HWND hWnd, char *zCaption, char *zFilespec, char *zInitialDir, char *zFilter, char *zDefExtension, int Flags)
{
	static  OPENFILENAME  ofn;
	static char File[2048];
	static char FileTitle[2048];
	static char Filter[2048];
	static char InitialDir[2048];
	static char Title[2048];
	static char DefExt[2048];
	static int RetFlg;
	if(strlen(zInitialDir)==0)
	{
		sprintf(InitialDir,"%s",curdir());
	}
	sprintf(Filter,"%s",zFilter);
	sprintf(InitialDir,"%s",zInitialDir);
	sprintf(File,"%s",zFilespec);
	sprintf(DefExt,"%s",zDefExtension);
	sprintf(Title,"%s",zCaption);
	ofn.lStructSize=sizeof(ofn);
	ofn.hwndOwner=hWnd;
	ofn.lpstrFilter=Filter;
	ofn.nFilterIndex=1;
	ofn.lpstrFile=File;
	ofn.nMaxFile=sizeof(File);
	ofn.lpstrFileTitle=FileTitle;
	ofn.nMaxFileTitle=sizeof(FileTitle);
	ofn.lpstrInitialDir=InitialDir;
	ofn.Flags=Flags;
	ofn.lpstrDefExt=DefExt;
	ofn.Flags = 527372;
	if(strlen(Title)>0)
	{
		ofn.lpstrTitle=Title;
	}
	RetFlg=GetOpenFileName(&ofn);
	sprintf(zFilespec,"%s",File);
	Flags=ofn.Flags;
	return RetFlg;
}


