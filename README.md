# Компиляция на Linux 
(проверено на g++)

```
mkdir build
cd build
cmake ..
make
./main ../examples/test_file.txt
```
# Компиляция на Windows

```
mkdir build
cd build
cmake ..
cmake --build .
Debug/main.exe ../examples/test_file.txt
```
В папке examples можно найти примеры входных данных, test_file.txt - пример из условия.
