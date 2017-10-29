## Laboratory work VIII

Данная лабораторная работа посвещена изучению средств пакетирования на примере **CPack**

```ShellSession
$ open https://cmake.org/Wiki/CMake:CPackPackageGenerators
```

## Tasks

- [X] 1. Создать публичный репозиторий с названием **lab08** на сервисе **GitHub**
- [X] 2. Выполнить инструкцию учебного материала
- [X] 3. Ознакомиться со ссылками учебного материала
- [X] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial
Устанавливаем значения GITHUB_USERNAME и GITHUB_EMAIL, настраиваем текстовый редактор, определяем команду
```ShellSession
$ export GITHUB_USERNAME=YAKOVLENKO # Присваиваем значение переменной GITHUB_USERNAME
$ export GITHUB_EMAIL=*******************@yandex.ru # Присваиваем значение переменной GITHUB_EMAIL
$ alias edit=nano # Выбираем текстовый редактор 
$ alias gsed=sed # Указываем, что gsed выполняет то же самое, что и sed
```
Клонируем lab07 в lab08, работаем с lab08
```ShellSession
$ git clone https://github.com/${GITHUB_USERNAME}/lab07 lab08 # Клонируем материал из lab07 в lab08
$ cd lab08 # Переходим в папку lab08
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab08 # Соединяемся с сервером
```
Настраиваем пакеты (прописываем определенные значения в файл CMakeLists.txt) 
```ShellSession
$ gsed -i '/project(print)/a\
set(PRINT_VERSION_STRING "v${PRINT_VERSION}")
' CMakeLists.txt
$ gsed -i '/project(print)/a\
set(PRINT_VERSION \
\${PRINT_VERSION_MAJOR}.\${PRINT_VERSION_MINOR}.\${PRINT_VERSION_PATCH}.\${PRINT_VERSION_TWEAK})
' CMakeLists.txt
$ gsed -i '/project(print)/a\
set(PRINT_VERSION_TWEAK 0)
' CMakeLists.txt
$ gsed -i '/project(print)/a\
set(PRINT_VERSION_PATCH 0)
' CMakeLists.txt
$ gsed -i '/project(print)/a\ 
set(PRINT_VERSION_MINOR 1)
' CMakeLists.txt
$ gsed -i '/project(print)/a\ 
set(PRINT_VERSION_MAJOR 0)
' CMakeLists.txt
```
Добавляем данные
```ShellSession
$ touch DESCRIPTION && edit DESCRIPTION # Создаем и редактируем файл DESCRIPTION
$ touch ChangeLog.md # Создаем папку ChangeLog.md
$ DATE=`date +"%a %b %d %Y"` cat > ChangeLog.md <<EOF # Прописываем дату, данные, версию в ChangeLog.md
* ${DATE} ${GITHUB_USERNAME} <${GITHUB_EMAIL}> 0.1.0.0
- Initial RPM release
EOF
```
Подключаем библиотеки
```ShellSession
$ cat > CPackConfig.cmake <<EOF
include(InstallRequiredSystemLibraries)
EOF
```
Настраиваем пакеты
```ShellSession
$ cat >> CPackConfig.cmake <<EOF
set(CPACK_PACKAGE_CONTACT ${GITHUB_EMAIL})
set(CPACK_PACKAGE_VERSION_MAJOR \${PRINT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR \${PRINT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH \${PRINT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK \${PRINT_VERSION_TWEAK})
set(CPACK_PACKAGE_VERSION \${PRINT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_FILE \${CMAKE_CURRENT_SOURCE_DIR}/DESCRIPTION)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "static c++ library for printing")
EOF
```
Указываем пути к файлам LICENSE и README.md
```ShellSession
$ cat >> CPackConfig.cmake <<EOF

set(CPACK_RESOURCE_FILE_LICENSE \${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README \${CMAKE_CURRENT_SOURCE_DIR}/README.md)
EOF
```
Настраиваем пакеты: устанавливаем значения, прописываем путь до ChangeLog.md и делаем данный релиз RPM PACKAGE истиной
```ShellSession
$ cat >> CPackConfig.cmake <<EOF

set(CPACK_RPM_PACKAGE_NAME "print-devel")
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "print")
set(CPACK_RPM_PACKAGE_URL "https://github.com/${GITHUB_USERNAME}/lab07")
set(CPACK_RPM_CHANGELOG_FILE \${CMAKE_CURRENT_SOURCE_DIR}/ChangeLog.md)
set(CPACK_RPM_PACKAGE_RELEASE 1)
EOF
```
Настраиваем пакеты: устанавливаем значения, делаем данный релиз DEBIAN PACKAGE истиной
```ShellSession
$ cat >> CPackConfig.cmake <<EOF

set(CPACK_DEBIAN_PACKAGE_NAME "libprint-dev")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://${GITHUB_USERNAME}.github.io/lab07")
set(CPACK_DEBIAN_PACKAGE_PREDEPENDS "cmake >= 3.0")
set(CPACK_DEBIAN_PACKAGE_RELEASE 1)
EOF
```
Добавляем CPack
```ShellSession
$ cat >> CPackConfig.cmake <<EOF

include(CPack)
EOF
```
Добавляем CPackConfig.cmake
```ShellSession
$ cat >> CMakeLists.txt <<EOF

include(CPackConfig.cmake)
EOF
```
Меняем lab07 на lab08 в README.md
```ShellSession
$ gsed -i 's/lab07/lab08/g' README.md
```
Добавляем на сервер
```ShellSession
$ git add . # Выбираем всё
$ git commit -m"added cpack config" # Добавляем комментарий
$ git push origin master # Выкладываем на сервер
```
Соединяемся с travis
```ShellSession
$ travis login --auto # Авторизуемся
$ travis enable # Подключаем lab08 к travis
```
Настраиваем архиватор
```ShellSession
$ cmake -H. -B_build # Получаем информацию cMakeLists.txt
$ cmake --build _build # Создаем папку _build
$ cd _build # Переходим в папку _build
$ cpack -G "DEB" # Настраиваем архиватор DEB для ubuntu
$ cd .. # Выходим из папки
```
Архивируем
```ShellSession
$ cmake -H. -B_build -DCPACK_GENERATOR="DEB" # Задаеи архивирование в DEB
$ cmake --build _build --target package # Архивируем
```
Выводим дерево artifacts
```ShellSession
$ mkdir artifacts # Создаем папку artifacts
$ mv _build/*.deb artifacts # Переносим файлы .deb в artifacts
$ tree artifacts # Выводим дерево artifacts

artifacts
└── print-0.1.0.0-Linux.deb

```

## Report

```ShellSession
$ cd ~/workspace/labs/
$ export LAB_NUMBER=08
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gistup -m "lab${LAB_NUMBER}"
```

## Links

- [DMG](https://cmake.org/cmake/help/latest/module/CPackDMG.html)
- [DEB](https://cmake.org/cmake/help/latest/module/CPackDeb.html)
- [RPM](https://cmake.org/cmake/help/latest/module/CPackRPM.html)
- [NSIS](https://cmake.org/cmake/help/latest/module/CPackNSIS.html)

```
Copyright (c) 2017 Братья Вершинины
```
