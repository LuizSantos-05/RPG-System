@echo off

REM Vai para o diretório do script

cd /d %~dp0

REM Volta para a raiz do projeto
cd ..

echo Compilando...

g++ *.cpp -o output\executavel.exe

echo Concluido!
pause
