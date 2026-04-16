# Vai para o diretório do script
Set-Location $PSScriptRoot

# Volta para a raiz do projeto
Set-Location ..

Write-Host "Compilando..."

g++ *.pp -o output/executavel.exe

Write-Host "Concluído!"
