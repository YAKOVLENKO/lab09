[![Build Status](https://travis-ci.org/YAKOVLENKO/lab05.svg?branch=master)](https://travis-ci.org/YAKOVLENKO/lab05)
## Laboratory work V

Данная лабораторная работа посвещена изучению систем непрерывной интеграции на примере сервиса **Travis CI**

```ShellSession
$ open https://travis-ci.org
```

## Tasks

- [X] 1. Авторизоваться на сервисе **Travis CI** с использованием **GitHub** аккаунта
- [X] 2. Создать публичный репозиторий с названием **lab05** на сервисе **GitHub**
- [X] 3. Ознакомиться со ссылками учебного материала
- [X] 4. Включить интеграцию сервиса **Travis CI** с созданным репозиторием
- [X] 5. Получить токен для **Travis CLI** с правами **repo** и **user**
- [X] 6. Получить фрагмент вставки значка сервиса **Travis CI** в формате **Markdown**
- [X] 7. Установить [**Travis CLI**](https://github.com/travis-ci/travis.rb#installation)
- [X] 8. Выполнить инструкцию учебного материала
- [X] 9. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial
Присваиваем значения перменным GITHUB_USERNAME и GITHUB_TOKEN
```ShellSession
$ export GITHUB_USERNAME=YAKOVLENKO
$ export GITHUB_TOKEN=<полученный_токен>
```
Клонируем lab04 в lab05, переходим в lab05
```ShellSession
$ git clone https://github.com/${GITHUB_USERNAME}/lab04 lab05 #Клонируем
$ cd lab05 #Переходим в lab05
$ git remote remove origin 
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab05
```
Создаем .travis.yml и заполняем его
```ShellSession
$ cat > .travis.yml <<EOF
language: cpp
EOF
```

```ShellSession
$ cat >> .travis.yml <<EOF

script:
- cmake -H. -B_build -DCMAKE_INSTALL_PREFIX=_install
- cmake --build _build
- cmake --build _build --target install
EOF
```

```ShellSession
$ cat >> .travis.yml <<EOF

addons:
  apt:
    sources:
      - george-edison55-precise-backports
    packages:
      - cmake
      - cmake-data
EOF
```
Заходим в travis
```ShellSession
$ travis login --github-token ${GITHUB_TOKEN}
```
Включаем отображение предупреждений
```ShellSession
$ travis lint
```
Вставляем значок 
```ShellSession
$ ex -sc '1i|<фрагмент_вставки_значка>' -cx README.md
```
Выкладываем всё в репозиторий  
```ShellSession
$ git add .travis.yml # Добавляем файл для коммита
$ git add README.md # Добавляем файл для коммита
$ git commit -m"added CI" # Коммитим с комментарием "added CI"
$ git push origin master # Выкладываем в репозиторий на сервер
```
Работаем с travis
```ShellSession
$ travis lint #Отображаем предупреждения
$ travis accounts #Отображаем аккаунт
$ travis sync #Синхронизируемся
$ travis repos #Отображаем, какие репозитории доступны, а какие нет
$ travis enable #Подключаем проект
$ travis whatsup #Отоброжаем, что изменилось в проекте
$ travis branches #Отоброжаем обновленную версию проекта
$ travis history #Отоброжаем историю проекта
$ travis show #Отображаем проект
```

## Report

```ShellSession
$ cd ~/workspace/labs/
$ export LAB_NUMBER=05
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gistup -m "lab${LAB_NUMBER}"
```

## Links

- [Travis Client](https://github.com/travis-ci/travis.rb)
- [AppVeyour](https://www.appveyor.com/)
- [GitLab CI](https://about.gitlab.com/gitlab-ci/)

```
Copyright (c) 2017 Братья Вершинины
```
