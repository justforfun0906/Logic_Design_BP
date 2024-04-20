@echo off
REM run.bat
set /p executable="Enter the exe file path: "
set /p input_path="Enter the input path: "
set /p output_path="Enter the output path: "


REM Run the main executable with the provided arguments
@echo on
%executable% %input_path% %output_path%
pause
