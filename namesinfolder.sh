#!/bin/bash

# Verificar si se proporciona un directorio como argumento
if [ -z "$1" ]; then
  echo "Por favor, proporciona un directorio como argumento."
  exit 1
fi

# Verificar si el directorio existe
if [ ! -d "$1" ]; then
  echo "El directorio no existe."
  exit 1
fi

# Usar find para obtener la ruta de todos los archivos en el directorio dado
find "$1" -type d | while read folder; do
  # Imprimir solo el nombre de la carpeta
  echo -n $folder " "
done
echo
