## Laboratory work VII
[![Build Status](https://travis-ci.org/YAKOVLENKO/lab07.svg?branch=master)](https://travis-ci.org/YAKOVLENKO/lab07)
Данная лабораторная работа посвещена изучению систем документирования исходного кода на примере **Doxygen**

```ShellSession
$ open https://www.stack.nl/~dimitri/doxygen/manual/index.html
```

## Tasks

- [X] 1. Создать публичный репозиторий с названием **lab07** на сервисе **GitHub**
- [X] 2. Выполнить инструкцию учебного материала
- [X] 3. Ознакомиться со ссылками учебного материала
- [X] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial
Задаем значения переменным, выбираем редактор
```ShellSession
$ export GITHUB_USERNAME=YAKOVLENKO # Присваиваем переменной GITHUB_USERNAME значение YAKOVLENKO
$ alias edit=nano # Выбираем редактор nano
```
Копируем данные, связываемся с репозиторием на сервере
```ShellSession
$ git clone https://github.com/${GITHUB_USERNAME}/lab06 lab07 # Клонируем lab06 в lab07
$ cd lab07 # Переходим в lab07
$ git remote remove origin 
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab07 #Соединяемя с репозиторие на сервере
```
Создаем новую папку для doxygen
```ShellSession
$ mkdir docs # Создаем папку docs
$ doxygen -g docs/doxygen.conf # Добавляем в папку doxygen.conf
$ cat docs/doxygen.conf # Проверяем doxygen.conf
```
Изменяем doxygen.conf
```ShellSession
$ sed -i '' 's/\(PROJECT_NAME.*=\).*$/\1 print/g' docs/doxygen.conf # Даем имя проекту: print (PROJECT_NAME = print)
$ sed -i '' 's/\(EXAMPLE_PATH.*=\).*$/\1 examples/g' docs/doxygen.conf # Прописываем путь до example (EXAMPLE_PATH = examples)
$ sed -i '' 's/\(INCLUDE_PATH.*=\).*$/\1 examples/g' docs/doxygen.conf # Прописываем путь до include (INCLUDE_PATH = examples)
$ sed -i '' 's/\(INPUT *=\).*$/\1 README.md include/g' docs/doxygen.conf # Включаем README.md (INPUT = README.md include)
$ sed -i '' 's/\(USE_MDFILE_AS_MAINPAGE.*=\).*$/\1 README.md/g' docs/doxygen.conf # Назначаем README.md главной страницей (USE_MDFILE_AS_MAINPAGE = README.md)
$ sed -i '' 's/\(OUTPUT_DIRECTORY.*=\).*$/\1 docs/g' docs/doxygen.conf # Прописываем путь docs (OUTPUT_DIRECTORY = docs)
```
Заменяем одни значения другими  в README.md
```ShellSession
$ sed -i '' 's/lab06/lab07/g' README.md # Замена "lab06" на "lab07"
```
Редактирование print.hpp
```ShellSession
# документируем функции print 
$ edit include/print.hpp
```
Выкладываем изменения в репозиторий на сервере
```ShellSession
$ git add . # Выбираем все элементы
$ git commit -m"added doxygen.conf" # Добавляем комментарий
$ git push origin master # Выкладываем изменения
```
Соединяемся с travis
```ShellSession
$ travis login --auto # Заходим в travis
$ travis enable # Даем доступ к lab07
```
Работаем с docs, выкладываем изменения на сервер
```ShellSession
$ doxygen docs/doxygen.conf # Указываем путь до doxygen.conf
$ ls | grep "[^docs]" | xargs rm -rf # Фильтруем docs
$ mv docs/html/* . && rm -rf docs # # Переносим составляющие в html и удаляем docs
$ git checkout -b gh-pages # Создаем ветку gh-pages, переключаемся на нее
$ git add . # Выбираем все элементы
$ git commit -m"added documentation" # Комментируем
$ git push origin gh-pages # Выкладываем изменения на gh-pages
$ git checkout master # Возвращаемся на верку master
```
Работаем со снимками экрана и Google Disk
```ShellSession
$ mkdir artifacts && cd artifacts # Создаем папку artifacts и переходим в неё
$ import screenshot.png # Делаем снимок экрана
<Command>-T
$ open https://${GITHUB_USERNAME}.github.io/lab07/print_8hpp_source.html # Открываем страницу с print.hpp
$ gdrive upload screenshot.png # Загружаем снимок на Google Disk
$ SCREENSHOT_ID=`gdrive list | grep screenshot | awk '{ print $1; }'` # Задаем ID изображения
$ gdrive share ${SCREENSHOT_ID} --role reader --type user --email rusdevops@gmail.com # Разрешаем доступ (чтение) rusdevops@gmail.com
$ echo https://drive.google.com/open?id=${SCREENSHOT_ID} # Открываем изображение
```

## Report

```ShellSession
$ cd ~/workspace/labs/
$ export LAB_NUMBER=07
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gistup -m "lab${LAB_NUMBER}"
```

## Links

- [HTML](https://ru.wikipedia.org/wiki/HTML)
- [LAΤΕΧ](https://ru.wikipedia.org/wiki/LaTeX)
- [man](https://ru.wikipedia.org/wiki/Man_(%D0%BA%D0%BE%D0%BC%D0%B0%D0%BD%D0%B4%D0%B0_Unix))
- [CHM](https://ru.wikipedia.org/wiki/HTMLHelp)
- [PostScript](https://ru.wikipedia.org/wiki/PostScript)

```
Copyright (c) 2017 Братья Вершинины
```
