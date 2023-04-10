@echo off
FOR /F "usebackq delims== tokens=1,2" %%a IN ("src/vosk.config.ini") DO SET %%a=%%b
rem source src/vosk.config.ini
rem ##------------------------------------------
echo ------------------------------------------
echo Start Vosk
echo ------------------------------------------
python src/client.py -u ws://localhost:%SERVER_PORT%
