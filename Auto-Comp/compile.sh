#!/bin/bash

# Vai para o diretório do script
cd "$(dirname "%0")"

# Volta para a raiz do projeto
cd ..

echo "Compilando..."

mkdir output -p

g++ *.cpp -o ./output/'Sistema Base'

if [ $? -eq 0 ]; then
	echo "Compilação realizada com sucesso!"
else
	echo "Erro na compilação."
fi
