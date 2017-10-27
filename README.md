## Laboratory work VI

Данная лабораторная работа посвещена изучению фреймворков для тестирования на примере **Catch**

```ShellSession
$ open https://github.com/philsquared/Catch
```

## Tasks

- [X] 1. Создать публичный репозиторий с названием **lab08** на сервисе **GitHub**
- [X] 2. Выполнить инструкцию учебного материала
- [X] 3. Ознакомиться со ссылками учебного материала
- [X] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial
Указываем значение переменной GITHUB_USERNAME
```ShellSession
$ export GITHUB_USERNAME=YAKOVLENKO
```
Копируем файлы из lab05 в lab08, соединяемся с репозиторием на сервисе
```ShellSession
$ git clone https://github.com/${GITHUB_USERNAME}/lab05 lab08 #Копируем файлы из lab05 в lab08
$ cd lab08 #Переходим в репозиторий
$ git remote remove origin 
	#Соединяемся с репозиторием на сервисе
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab08 
```
Создаем папку tests и заполняем ее
```ShellSession
$ mkdir tests #Создаем папку tests
	#Скачиваем файл с данного источнка
$ wget https://github.com/philsquared/Catch/releases/download/v1.9.3/catch.hpp -O tests/catch.hpp 
$ cat > tests/main.cpp <<EOF #Создаем новый файл
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
EOF
```
Создаем тесты
```ShellSession
$ sed -i '' '/option(BUILD_EXAMPLES "Build examples" OFF)/a\
option(BUILD_TESTS "Build tests" OFF)
' CMakeLists.txt
$ cat >> CMakeLists.txt <<EOF

if(BUILD_TESTS)
	enable_testing() #Включаем тестирование для текущего директория
	file(GLOB \${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
	add_executable(check \${\${PROJECT_NAME}_TEST_SOURCES})
	target_link_libraries(check \${PROJECT_NAME} \${DEPENDS_LIBRARIES})
	add_test(NAME check COMMAND check "-s" "-r" "compact" "--use-colour" "yes") 
	# Задаем параметры теста:
	# -s - Отображаем успешное выполнение
	# -r compact - Выводим в определенном формате
endif()
EOF
```

```ShellSession
$ cat >> tests/test1.cpp <<EOF
#include "catch.hpp"
#include <print.hpp>

TEST_CASE("output values should match input values", "[file]") {
  std::string text = "hello";
  std::ofstream out("file.txt");
  
  print(text, out);
  out.close();
  
  std::string result;
  std::ifstream in("file.txt");
  in >> result;
  
  REQUIRE(result == text);
}
EOF
```
Запускаем CMake, через него работаем с CMakeLists.txt
```ShellSession
$ cmake -H. -B_build -DCMAKE_INSTALL_PREFIX=_install -DBUILD_TESTS=ON
$ cmake --build _build
$ cmake --build _build --target test #Запускаем test (тестовые файлы)
## Running tests...
## Test project /home/user1/lab08/_build
##    Start 1: check
## 1/1 Test #1: check ............................   Passed    0.00 sec
##
## 100% tests passed, 0 tests failed out of 1
##
## Total Test time (real) =   0.01 sec


```
Редактируем README.md и .travis.yml
```ShellSession
$ sed -i '' 's/lab05/lab08/g' README.md #Заменяем lab05 на lab08
$ sed -i '' 's/\(DCMAKE_INSTALL_PREFIX=_install\)/\1 -DBUILD_TESTS=ON/' .travis.yml #Заменяем одну строку на другу.
$ sed -i '' '/cmake --build _build --target install/a\
- cmake --build _build --target test
' .travis.yml
```
Проверка travis
```ShellSession
$ travis lint
```
Выкладываем файлы
```ShellSession
$ git add .
$ git commit -m"added tests"
$ git push origin master
```
Активируем проект в travis
```ShellSession
$ travis login --auto
$ travis enable
```
Создаем скриншот и помещаем его в созданную папку artifacts
```ShellSession
$ mkdir artifacts #Создание папки
$ screencapture -T 20 artifacts/screenshot.jpg
<Command>-T 
$ open https://github.com/${GITHUB_USERNAME}/lab08
```

## Report

```ShellSession
$ cd ~/workspace/labs/
$ export LAB_NUMBER=06
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gistup -m "lab${LAB_NUMBER}"
```

## Links

- [Boost.Tests](http://www.boost.org/doc/libs/1_63_0/libs/test/doc/html/)
- [Google Test](https://github.com/google/googletest)

```
Copyright (c) 2017 Братья Вершинины
```
