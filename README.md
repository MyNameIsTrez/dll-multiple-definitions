# dll multiple definitions

## Generate two dlls

`cc dll1.c -shared -o dll1.dll`
`cc dll2.c -shared -o dll2.dll`

## Use the dlls

On Linux:
`cc main_linux.c && ./a.out`

On Windows:
`cc main_windows.c && ./a.exe`
