# !Almavending repo
> Репозиторий для сохранения информации, кода, моделей, и прочего :space_invader:


## 📖 Оглавление

- Структура папок
- Список модулей
- Установка ПО
- Список багов
- Список полезных ссылок
- Релизы
- Лицензия



## 📁 Структура папок

### ПО Вендинг сбер

| Name | Description |
| --- | --- |

| [`Commands`](https://github.com/nhn/tui.editor/tree/master/apps/editor) | Заготовка под Shell script для автоматизации |

### Arduino
Старые версии кода для разных контроллеров и разных машин с разными механиками, надо разобраться, чтот удалить

| Name | Description |
| --- | --- |
| New firmware arduino | [Возможно тут](https://reactjs.org/) будет ссылка на отдельный репозиторий |
| libraries | Папка с библиотеками для компиляции кода |
| Old code | Старые версии кода |
| PlatformIO project | Заготовка прошивки MK под Platformio, не компилируеться из-за новой версии GCC которая указыает на ошибку стандартной библиотеке Servo.h |


### Backup

| Name | Description |
| --- | --- |
| [old.zip | Старые бекапы с большим кол-вом файлов и вложенности(то что не синхронит GIT) + что-то еще |
| [Python_dev_old.zip | Одна их первых версий ПО для Raspberry Pi, простой Flask, роутинг, взаимодействие с MK посредством UART  |
| [Python_dev.zip | Актуальная версия Python app, с мини БД на JSON, интеграция с AQSI, [ссылка](https://github.com/1deam0nster/Python_dev) на отдельный актуальный репозиторий  |
| [`App PAX D200 Sber`](https://github.com/nhn/tui.editor/tree/master/apps/editor) | ПО для терминала Pax D200 для LINUX, ARM |
| [Control Panel Node | Веб приложения на Express Node для управления MK посредством Serial, так и не пригодилось(( |
| [app.py | Старое приложение на Python |
| [app_backup_code | Старое приложение на Python |
| [RPI4_image_alfa | Копия флешки для RPI4 |


### 3D Print Models

| Name | Description |
| --- | --- |
| [Cura | Проекты в куре |
| [Fusion Models | Исходники 3д моделей  |
| [G-Code | Файлы для 3д принтера  |


### Img

Коллекция сохраненок для разных модулей, датчиков, информация по распиновкам. Раздел в процессе наполнения...
<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tr>
    <td align="center"><img src="https://github.com/1deam0nster/Vending_materials/raw/main/Img/66860250-d6b82c00-ef5a-11e9-8897-1a4e9d7fdf21.jpg" width="100px;" alt="img"/></td>
    <td align="center"><img src="https://github.com/1deam0nster/Vending_materials/blob/main/Img/71jd0sZLUbL._SL1500_.jpg?raw=true" width="100px;" alt="img"/></td>
    <td align="center"><img src="https://github.com/1deam0nster/Vending_materials/blob/main/Img/3d.jpg?raw=true" width="100px;" alt="img"/></td>
    <td align="center"><img src="https://github.com/1deam0nster/Vending_materials/blob/main/Img/shema.jpg?raw=true" width="100px;" alt="img"/></td>
    <td align="center"></td>
    <td align="center"></td>
    <td align="center"></td>
  </tr>
</table>

<!-- markdownlint-enable -->
<!-- prettier-ignore-end -->
<!-- ALL-CONTRIBUTORS-LIST:END -->

### PCB
Экспорт проекта с ['EasyEDA']:(https://www.easyeda.com) 

##How to recover online project backup：
1、Via folder "online_projects_backup" find out the project as you want
2、Copy to desktop
3、Open the EasyEDA editor, via: Top meun - Open - EasyEDA
4、Select the 'sch' and 'pcb' folder's 'json' files to open, and then save to a new project
5、Saved and finish

### 📃 Python

| Name | Description |
| --- | --- |
| [`evotor`](https://github.com/1deam0nster/Vending_materials/tree/main/Python/Evotor) | Скрипт для отправки фискольных данных в Эвотор |
| [`bot.py`](https://github.com/1deam0nster/Vending_materials/blob/main/Python/bot.py) | Telegram bot для управления машиной |
| [`Aqsi`](https://github.com/1deam0nster/Vending_materials/blob/main/Python/Aqsi) | Aqsi код для фискализации, чека, оплаты |
| [`Python_dev`](https://github.com/1deam0nster/Vending_materials/blob/main/Python/Python_dev) | Основной код для Raspberry PI |


## 🔧 Список модулей на каждую часть

**Турель выдачи стаканчиков**
- Три кнопки с подтягивающими резисторами(3 ножки на MK)

**Турель с капсулами + кофемашина**
- Магнит
- Сенсор на землю(+ Реле)
- Два сервопривода
- Два концевика
- Шаговый двигатель(+ драйвер)
- Ir датчик присутствия капсулы

**Выдача сливок**
- Шаговый двигатель(+ драйвер)
- Два сервопривода
- Один концевик

**Выдача сахара**
- Один сервопривод

**Подача стакана под кофеварку и выдача клиенту**
- ?
- ?


## Установка ПО

Описание в процессе...

```sh
$ git clone https://github.com/{your-personal-repo}/tui.editor.git
$ npm install
$ npm run build toastmark
$ npm run test editor
```
## 🐛Список багов
- [ ] ...

### Примерный список задач

```
### Общие задачи
- [x] Собрать тестовый стенд для кофемашины
- [ ] Разработка ПО для микроконтроллера(для тестового стенда), выполнение полного цикла приготовления кофе на тестовом стенде в ручную с компа посредством ручного ввода 
- [ ] Разработка Flask приложения(для тестового стенда), выполнение полного цикла приготовления кофе, оплаты, загрузки, ребута, частично реализовать систему обслуживания
- [ ] Разработка платы PCB
- [ ] Собрать полную статистику сколько и каких всего материалов использованно для создания одной кофе машины, создать тут раздел
- [ ] Админ панель(обслуживание) или может пока обойтись кнопкой
- [ ] Выход в сеть, легкий удаленный доступ, объединение в одну сеть(хз проще всего наверное VPN)

### Разработка Flask приложения 
- [ ] Создание мини БД для учета(почти готово, надо сделать сохранение после перезапуска)
- [x] Роутинг страниц
- [x] Шаблоны для отображения(черновые, пока без дизайна)
- [ ] Подумать как будет храниться информация в БД, пока это только объект внутри программы, возможно можно сделать тупо хранение на флешке файлов JSON
- [x] Код для передачи g-code комманд MK 
- [ ] Дизайн всех страниц, сверстать, сделать шаблоны 
- [x] Отрефакторить предыдущие наработки, чтоб все было модульно и круто
- [ ] Добавить описание как это все запускать, добавить описание к ['репозиторию']:(https://github.com/1deam0nster/Python_dev) Python_dev
- [ ] Создать админ панель(обслуживание автомата для начала), отображение статистики продаж


### Разработка ПО для микроконтроллера
- [x] Прописать тестовые команды для отладки
- [ ] Продумать сколько команд нужно для приготовления кофе, разделить их на маленькие части для переиспользования кода, собрать основные команды 
- [X] Обратная связь с Raspberry PI
- [ ] Инициализация eeprom памяти для экстренных ситуаций(когда свет потух, знать местоположение турели, например)
- [ ] Режим обслуживания, сброс кол-ва капсул в ПЗУ(eeprom)
- [ ] Создать репозиторий для кода МК, а то заебало плодить кучу версий 


## Список не глобальных задач
- [x] Создать описание к данному репозиторию
- [ ] отрефакторить размещение и нэйминг
- [ ] Добавить ссылки на остальные репозитории в данный README
- [ ] Добавить папку 3d, разделить её на настройки принтера, 3д модели(Fusion360), g-code
- [ ] Добавить раздел список оборудования и конструкционных материалов(наполнить по окончанию стройки машины, если это возможно)
- [ ] Добавить к списку модулей таблицу с пинами для подключения
- [ ] Собрать все медия материалы для истории
```

## Список полезных ссылок
['Модель дисплея']:(https://www.waveshare.com/product/raspberry-pi/displays/lcd-oled/13.3inch-hdmi-lcd-h.htm)


## Список релизов

* 0.2.1
    * CHANGE: Update docs (module code remains unchanged)
* 0.2.0
    * CHANGE: Remove `setDefaultXYZ()`
    * ADD: Add `init()`
* 0.1.1
    * FIX: Crash when calling `baz()` (Thanks @GenerousContributorName!)
* 0.1.0
    * The first proper release
    * CHANGE: Rename `foo()` to `bar()`
* 0.0.1
    * Work in progress


## 📜 License

Закрытый проект и репозиторий идите все [нахуй](https://нахуй.ру) © [ReutaDmitry](https://reutadmitry.com).

[(Back to top)](##Оглавление)
