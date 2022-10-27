# ![TOAST UI Editor](https://uicdn.toast.com/toastui/img/tui-editor-bi.png)

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


```txt
.
├── ПО Вендинг Сбер
│   ├── ПО Вендинг Сбер
│   │   ├── LINUX-копия
│   │   └── LINUX_ARM-копия
│   └── commands
├── Arduino
│   ├── libraries
│   ├── LINUX-копия
│   └── ...куча не нужных бекапов, надо подчистить
├── Backup
│   ├── old.zip
│   ├── Python_dev_old.zip
│   └── Python_dev.zip
├── Control Panel Node
│   ├── ...
│   └── ...
├── Img
│   ├── ...
│   └── ...
├── MK
│   ├── ...
│   └── ...
├── Python
│   ├── evotor
│   │   ├── ...
│   │   └── ...
│   ├── Stuff
│   │   ├── ...
│   │   └── ...
│   ├── app_buckup_code.py
│   ├── app.py
│   └── bot.py
```

### ПО Вендинг сбер

| Name | Description |
| --- | --- |
| [`ПО Вендинг сбер`](https://github.com/nhn/tui.editor/tree/master/apps/editor) | ПО для терминала Pax D200 для LINUX, ARM |
| [`Commands`](https://github.com/nhn/tui.editor/tree/master/apps/editor) | Заготовка под Shell script для автоматизации |

### Arduino
Старые версии кода для разных контроллеров и разных машин с разными механиками, надо разобраться, чтот удалить

| Name | Description |
| --- | --- |
| [`New firmware arduino`](https://github.com/nhn/tui.editor/tree/master/apps/react-editor) | [Возможно тут](https://reactjs.org/) будет ссылка на отдельный репозиторий |
| [`libraries`](https://github.com/nhn/tui.editor/tree/master/apps/vue-editor) | Папка с библиотеками для компиляции кода |
| Все остальное | Старые версии кода |


### Backup

| Name | Description |
| --- | --- |
| [old.zip | Старые бекапы с большим кол-вом файлов и вложенности(то что не синхронит GIT) + что-то еще |
| [Python_dev_old.zip | Одна их первых версий ПО для Raspberry Pi, простой Flask, роутинг, взаимодействие с MK посредством UART  |
| [Python_dev.zip | Актуальная версия Python app, с мини БД на JSON, интеграция с AQSI, [ссылка](https://github.com/1deam0nster/Python_dev) на отдельный актуальный репозиторий  |
| [`@toast-ui/editor-plugin-color-syntax`](https://github.com/nhn/tui.editor/tree/master/plugins/color-syntax) | Plugin to color editing text |
| [`@toast-ui/editor-plugin-table-merged-cell`](https://github.com/nhn/tui.editor/tree/master/plugins/table-merged-cell) | Plugin to merge table columns |
| [`@toast-ui/editor-plugin-uml`](https://github.com/nhn/tui.editor/tree/master/plugins/uml) | Plugin to render UML |


### Controll Panel Node

Веб приложения на Express Node для управления MK посредством Serial, так и не пригодилось((

### Img

Коллекция сохраненок для разных модулей, датчиков, информация по распиновкам. Раздел в процессе наполнения...
<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tr>
    <td align="center"><img src="https://github.com/1deam0nster/Vending_materials/raw/main/Img/66860250-d6b82c00-ef5a-11e9-8897-1a4e9d7fdf21.jpg" width="100px;" alt="img"/></td>
    <td align="center"><img src="https://github.com/1deam0nster/Vending_materials/blob/main/Img/71jd0sZLUbL._SL1500_.jpg?raw=true" width="100px;" alt="img"/></td>
    <td align="center"></td>
    <td align="center"></td>
    <td align="center"></td>
    <td align="center"></td>
    <td align="center"></td>
  </tr>
</table>

<!-- markdownlint-enable -->
<!-- prettier-ignore-end -->
<!-- ALL-CONTRIBUTORS-LIST:END -->

### MK

Заготовка прошивки MK под Platformio, не компилируеться из-за новой версии GCC которая указыает на ошибку стандартной библиотеке Servo.h

### PCB
Экспорт проекта с ['EasyEDA'] (https://www.easyeda.com) 

##How to recover online project backup：
1、Via folder "online_projects_backup" find out the project as you want
2、Copy to desktop
3、Open the EasyEDA editor, via: Top meun - Open - EasyEDA
4、Select the 'sch' and 'pcb' folder's 'json' files to open, and then save to a new project
5、Saved and finish

### 📃 Python
Надо добавить AQSI код


| Name | Description |
| --- | --- |
| [`evotor`](https://github.com/1deam0nster/Vending_materials/tree/main/Python/evotor) | Скрипт для отправки фискольных данных в Эвотор |
| [`app_backup_code.py`](https://github.com/1deam0nster/Vending_materials/blob/main/Python/app_backup_code.py) | Понятно из названия, код старинный по парадигме функционального прграммирования без ООП |
| [`app.py`](https://github.com/1deam0nster/Vending_materials/blob/main/Python/app.py) | Бэкап на всякий случай с ООП 😀 |
| [`bot.py`](https://github.com/1deam0nster/Vending_materials/blob/main/Python/bot.py) | Telegram bot для управления машиной |



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

## Список полезных ссылок

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
