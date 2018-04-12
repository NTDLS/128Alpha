@Echo Off

SET Filename=128Alpha

echo %Filename%

c:\lcc\bin\lrc %Filename%.Rc
c:\lcc\bin\lcc -O %Filename%.C
c:\lcc\bin\lcclnk -s -subsystem:windows /Out:%Filename%.exe *.obj *.res

del *.obj
del *.res
