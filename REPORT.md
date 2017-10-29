## Laboratory work IX

Данная лабораторная работа посвещена изучению процесса создания пакета на примере **Github Release**

```ShellSession
$ open https://help.github.com/articles/creating-releases/
```

## Tasks

- [X] 1. Создать публичный репозиторий с названием **lab09** на сервисе **GitHub**
- [X] 2. Ознакомиться со ссылками учебного материала
- [X] 3. Получить токен для доступа к репозиториям сервиса **GitHub**
- [X] 4. Сгенерировать GPG ключ и добавить его к аккаунту сервиса **GitHub**
- [X] 5. Выполнить инструкцию учебного материала
- [X] 6. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial
Устанавливаем значения 
```ShellSession
$ export GITHUB_TOKEN=<полученный_токен> # Присваиваем значение переменной
$ export GITHUB_USERNAME=<имя_пользователя> # Присваиваем значение переменной
$ alias gsed=sed # Показываем, что одна команда делает то же самое, что и другая
```
Скачиваем набор команд
```ShellSession
$ cd ${GITHUB_USERNAME}/workspace # Переходив с свою рабочую папку
$ pushd .
$ source scripts/activate
$ go get github.com/aktau/github-release # Скачиваем
```
Готовимся к работе с файлами из предыдущей ЛР
```ShellSession
$ git clone https://github.com/${GITHUB_USERNAME}/lab08 projects/lab09 # Клонируем ЛР8 в ЛР9
$ cd projects/lab09 # Переходим в папку лабораторной работы 9
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab09 # Связываемся с сервером
```
Заменяем значения
```ShellSession
$ gsed -i 's/lab08/lab09/g' README.md # Заменяем lab08 на lab09
```
Работаем с архивацией
```ShellSession
$ cmake -H. -B_build -DCPACK_GENERATOR="TGZ" # Задаем архивирование в TGZ 
$ cmake --build _build --target package # Архивируем
```
Работаем с travis
```ShellSession
$ travis login --auto # Авторизуемся
$ travis enable # Связываем ЛР9 с travis
```
Обновляем
```ShellSession
$ git tag -s v0.1.0.0 # Подписываем
$ git tag -v v0.1.0.0 # Проверяем
$ git push origin master --tags # Выкладываем изменения
```
Работаем с информацией о релизе
```ShellSession
$ github-release --version # Узнаем версию github-release
$ github-release info -u ${GITHUB_USERNAME} -r lab09 # Узнаем версию ЛР9
$ github-release release \ # Вносим информацию о релизе
    --user ${GITHUB_USERNAME} \
    --repo lab09 \
    --tag v0.1.0.0 \
    --name "libprint" \
    --description "my first release"
```
Устанавливаем переменные, выкладываем изменения на сервер
```ShellSession
$ export PACKAGE_OS=`uname -s` PACKAGE_ARCH=`uname -m` # Устанавливаем переменные PACKAGE_OS и PACKAGE_ARCH
$ export PACKAGE_FILENAME=print-${PACKAGE_OS}-${PACKAGE_ARCH}.tar.gz # Работаем с переменной PACKAGE_FILENAME
$ github-release upload \ # Выкладываем изменения на сервер
    --user ${GITHUB_USERNAME} \
    --repo lab09 \
    --tag v0.1.0.0 \
    --name "${PACKAGE_FILENAME}" \
    --file _build/*.tar.gz
```
Работаем с файлами
```ShellSession
$ github-release info -u ${GITHUB_USERNAME} -r lab09 # Узнаем информацию о ЛР9
$ wget https://github.com/${GITHUB_USERNAME}/lab09/releases/download/v0.1.0.0/${PACKAGE_FILENAME} # Скачваем файл
$ tar -ztf ${PACKAGE_FILENAME} # Распаковываем файл
```

## Report

```ShellSession
$ popd
$ export LAB_NUMBER=09
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gistup -m "lab${LAB_NUMBER}"
```

## Links

- [Create Release](https://help.github.com/articles/creating-releases/)
- [Get GitHub Token](https://help.github.com/articles/creating-a-personal-access-token-for-the-command-line/)
- [Signing Commits](https://help.github.com/articles/signing-commits-with-gpg/)
- [Go Setup](http://www.golangbootcamp.com/book/get_setup)
- [github-release](https://github.com/aktau/github-release)

```
Copyright (c) 2017 Братья Вершинины
```
