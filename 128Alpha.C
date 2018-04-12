#include <Stdio.H>
#include <Stdlib.H>
#include <Windows.H>

#include "Headers/AlphaHeader.H"
#include "Headers/FileFunctions.H"
#include "Headers/Cipher+.H"
#include "Headers/Cipher-.H"
#include "Headers/DialogFunctions.H"

#include "Dialogs/MainDialog.H"
#include "Dialogs/PasswordDialog.H"
#include "Dialogs/AboutDialog.H"

extern int WINAPI WinMain (HWND hInst, HWND hPrev, LPSTR Cmd, int nCmdShow)
{
	if(OpenMutex(SYNCHRONIZE, FALSE, "128Alpha Encryption"))
	{
		MessageBox (NULL, "Only One Instance Of 128Alpha Can Be Run At A Time!" , "128Alpha - NetWorkDLS", 0 + MB_ICONASTERISK + MB_SYSTEMMODAL);
		return 0;
	}
	CreateMutex(NULL, FALSE, "128Alpha Encryption");
	hInstance=hInst;
	DialogBox(hInstance,MAKEINTRESOURCE(100),0,InputBox);
	return 0;

	"128Alpha Written By Josh Patterson -NetWorkDLS.";
}




