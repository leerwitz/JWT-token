# Название проекта: Реализация jwt-token с использованием алгоритма шифрования RSA

# Содержание:
- [Краткое описание](#краткое-описание)
- [Использование](#использование) 
- [Местоположение проекта](#местоположение-проекта-в-репозитории)
- [Компиляция](#компиляция)
- [Создание jwt-token](#создание-jwt-token)
- [Проверка jwt-token](#проверка-jwt-token)
- [PRIVATE KEY](#begin-rsa-private-key)
- [PUBLIC KEY](#begin-public-key)
- [FAQ](#faq)

# <a id="title1">Краткое описание</a>:
    
В проекте есть две основные программы authorization_server.cpp и check_token.cpp  
    
authorization_server.cpp создает токен с помощью алгоритма шифрования Rsa  
    
check_token.cpp проверяет действителен ли токен, то есть были ли данные в нем изменения извне, а также не просрочен ли сам токен(прим. у токен действителен   некоторое конечное время с момента создания, в моем случае это время 5 минут (300 секунд))
    
Валидность токена означает что его отправитель это тот, кем он представился(данные токена не изменены никем извне), и сам токен был создан не позже его времени жизни

# <a id="title2">Использование</a>:

Для использования проекта вам понадобится компилятор для c++ и команда make для Makefile  g++ версии 7.2.0 или новее

Чтобы посмотреть версию компилятора на Linux(Ubuntu) введите следующую команду в терминале:  
`g++ --version`
    
Если у вас версия 7 или выше, всё в порядке.

Если версия ниже 7.0, то надо обновить компилятор.  Введите следующие 3 команды:  
\`
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt update
sudo apt-get install g++
\`

Перед установкой make проверьте, установлен ли он ужею Это можно сделать следующей командой:  
`make -version`
    
Если пакет make не установлен в Ubuntu по какой-либо причине, вы получите сообщение об ошибке.

Вы можете установить пакет make, набрав:  
`sudo apt install make`


Также потребуется скопировать репозиторий с моего github. Это можно сделать следующей командой:  
`git clone checkout -b week_4 git@github.com:leerwitz/CodeforcesTasks.git`

или скачать zip Архив репозитория CodeforcesTasks
![Скачать zip архив можно тут](images/image1.png)



# <a id="title3">Местоположение проекта в репозитории</a>: 
    
CodeforcesTasks/tasks/token

# <a id="title4">Компиляция</a>:
    
Введите в консоле следующие команды , находясь в папке token, для компиляции проекта:
`make`

или

`make all`
Для перекомпиляции:  
`make rebuild`
Для удаления выполняемых и object файлов:  
`make clean`


# <a id="title5">Создание jwt-token</a>:

Запустите исполняемый файл authorization_server в консоле. 
Это можно сделать следующей командой:  
`./authorization_server`  
## ВХОДНЫЕ ДАННЫЕ:

Введите 2 любые строки до 16 символов (они олицетворяет логин и пароль в проекте)  
Введите первое и второе числа вашего приватного ключа
## ВЫХОДНЫЕ ДАННЫЕ:

jwt-token ввиде зашифрованной строки 

# <a id="title6">Проверка jwt-token</a>:
    
Запустите исполняемый файл check_token в консоле. 
Это можно сделать следующей командой:
`./check_token`
## ВХОДНЫЕ ДАННЫЕ:

Введите ваш jwt-token  
Введите первое и второе числа вашего публичного ключа
## ВЫХОДНЫЕ ДАННЫЕ:
THE TOKEN IS VALID/INVALID


# <a id="title7">-----BEGIN RSA PRIVATE KEY-----</a>

## FIRST NUMBER:
3271039093029429167887059099288397733657868231136558426813518974522885616319100138001436698145763028731678001506776584590307907590632793156575565827901113

## SECOND NUMBER:           

3351951982485649274893506249551461531869841455148098344430890360930441007532050210730471885601707233153533137673307370903984057259642637399542161549046867

**-----END RSA PRIVATE KEY-----**

# <a id="title8">-----BEGIN PUBLIC KEY-----</a>

## FIRST NUMBER:
65537

## SECOND NUMBER:
3351951982485649274893506249551461531869841455148098344430890360930441007532050210730471885601707233153533137673307370903984057259642637399542161549046867

**-----END PUBLIC KEY-----**
# <a id="title9">FAQ</a>:
1. Приватный и публичный ключи имеют такой вид, тк в данной реализации не использовался никакой способо кодировки (по типу base 64)  
2. Если вы хотите использовать свои версии пуб. и прив. ключей, то для корректной работы программы требуется большой SECOND NUMBER у ключей размера около  256 бит и больше  
3. алгоритм создание публичного и приватного ключей для RSA можно посмотреть [тут](https://ru.wikipedia.org/wiki/RSA).  
