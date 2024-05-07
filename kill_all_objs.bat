:: Because I, Nan R, cannot figure out how to make `make clean` work.
@echo off

:: Print every file that will be deleted, just in case.
FOR %%i IN (.\obj\*.o .\obj\*.d) DO echo:.\obj\%%~ni%%~xi

:: Count all the files therein while we're at it.
SET COUNT = 0
FOR %%i IN (.\obj\*.o .\obj\*.d) DO SET /A COUNT += 1

:: Ask if we really want to delete all those files.
SET CONFIRMATION = n
SET /P CONFIRMATION=Are you sure (y/[n])?

:: If the answer is __not__ 'y', program aborts and no one gets hurt.
IF /I "%CONFIRMATION%" NEQ "y" GOTO ABORT

:: Always use the same loop to avoid confusion.
echo:Deleted %COUNT% files.
FOR %%i IN (.\obj\*.o .\obj\*.d) DO del %%i
GOTO END

:: Tags
:ABORT
echo:Aborted
:END
EXIT
