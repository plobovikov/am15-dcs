# Лабораторная работа № 6

## REST service

Реализовать REST service с RESTful API для управления базой контактов.

Клиента можно писать на чем угодно и как угодно, единственное требование к клиенту - весь HTTP стек (запросы / ответы) должны ЛОГИРОВАТЬСЯ в файл, либо в консоль.

https://reqres.in/ - тестовый REST сервис, тут можно поиграться.

Требования к REST сервису:

На серваке БД с контактами (можно взять любую БД, можно даже сделать файловую БД на костылях, для взаимодействия с postgres есть плюсовая либа pqxx), каждый из контактов содержит следующие поля:

Id - Уникальный id  
Name - Имя  
Surname - Фамилия  
Address - Адрес  
PhoneNumbers - Список телефонов (телефон + тип Домашний / Рабочий)  
City - Город  
E-mail - Мыло, поддерживается только в версии 2!
Date - Дата рождения, поддерживается только в версии 2!

Необходимые API:
1. Регистрация.
```
GET /api/contect_rest/register?login=test_login?password=test_password HTTP/1.1

Допустимые ответы:

200 OK 
```
2. Логин.
Здесь клиент указывает поддерживаемые версии в заголовке Accept, клиент должен уметь работать с обеими версиями.
Сервер должен присылать данные в формате самой высокой поддерживаемой версии.
Т.е. если клиент в заголовке Accept указывает только версию 1 - сервер должен прислать данные в формате версии 1,
если же в заголовке Accept указаны обе версии, сервер должен присылать данные в формате версии 2.
```
GET /api/contect_rest/login?login=test_login?password=test_password HTTP/1.1
Accept: application/contact_rest-v1+json
Допустимые ответы:

200 OK, 404 Not Found

В ответе 200 OK сервер присылает токен + ссылки на все доступные ресурсы:
HTTP/1.1 200 OK
Content-Type: application/contact_rest-v1+json 

{
"accessToken" : "sample_token"
"links" : [
     {
        "get_contacts_uri" : "/api_v1/rest/get-contacts/"
        "method" : "GET"
     },
    {
       "update_contacts_uri" : "/api_v1/rest/update-contacts/"
        "method" : "PUT"
    },
    {
      "create_contacts_uri" : "/api_v1/rest/create-contacts/"
      "method" : "POST"
    },
    {
      "delete_contacts_uri" : "/api_v1/rest/delete-contacts/"
      "method" : "DELETE"
    }
]
}
```
Во все последующие запросы клиент должен включать полученный токен, иначе сервер должен присылать 401 Unauthorized.
Все запросы должны осуществляться исключительно по полученным ссылкам ( ссылки на ресурсы не должны быть захардкожены на клиенте).

3. Выгрузка контактов.
Опция 1 - поиск по номеру телефона или Имя + Фамилия
```
GET /api_v2/rest/get-contacts/ HTTP/1.1
Content-Type: application/contact_rest-v2+json 
Accept: application/contact_rest-v1+json;application/contact_rest-v2+json  
{
   "accessToken" : "test_token"
   "handle " : Phone Number / Name + Surname 
   "value" : 89063688792 
}

Допустимые ответы:
200 OK / 404 Not Found

В случае ответа 200 OK сервер присылает найденные контакты (их может быть несколько) в json:
(Не забываем, что в версии 2 будут дополнительные поля, в версии 1 их быть не должно!)
HTTP/1.1 200 OK
Content-Type: application/contact_rest-v2+json 
{
    "сontacts" : [
    {
        Id :   
        Name:
        Phones : []
        E-mail:
    },
]
}
```
Опция 2 - выгрузка контактов по их id.
```
GET /api_v1/rest/get-contacts/*id* HTTP/1.1

Допустимые ответы:
200 OK / 404 Not Found

Содержимое в ответе 200 ОК то же самое.
При отправке запроса без указания id, сервер должен присылать всю базу контактов.
```

4. Создание контактов.
```
POST /api_v2/rest/create-contacts/ HTTP/1.1
Content-Type: application/contact_rest-v2+json 
Accept: application/contact_rest-v2+json;application/contact_rest-v1+json 
{
   "accessToken" : "test_token"
}
В теле указывается json c создаваемым контактом.

Допустимые ответы:
201 OK

В теле ответа сервер должен присылать созданный контакт с назначенным ему уникальным id

```

5. Апдейт контактов.

```
POST /api_v2/rest/update-contacts/*id* HTTP/1.1
Content-Type: application/contact_rest-v2+json 
Accept: application/contact_rest-v2+json;application/contact_rest-v1+json 
{
   "accessToken" : "test_token"
   //далее указываются поля, которые мы хотим поменять у контакта с id = *id* (указывается в строке запроса)
}
В теле указывается json c создаваемым контактом.

Допустимые ответы:
200 OK

В теле ответа сервер должен присылать проапдейченный контакт с назначенным ему уникальным id

```

6. Удаление контактов.

```
POST /api_v2/rest/delete-contacts/*id* HTTP/1.1
Content-Type: application/contact_rest-v2+json 
Accept: application/contact_rest-v2+json;application/contact_rest-v1+json 
{
   "accessToken" : "test_token"
}

Допустимые ответы:
204 OK, 404 Not Found
```
