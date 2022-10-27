# ![TOAST UI Editor](https://uicdn.toast.com/toastui/img/tui-editor-bi.png)

> Репозиторий для сохранения информации, кода, моделей, и прочего :space_invader:


## 🚩 Оглавление

- [Структура](#-📁 Структура папок)
- [Features](#-features)
- [Examples](#-examples)
- [Browser Support](#-browser-support)
- [Pull Request Steps](#-pull-request-steps)
- [Contributing](#-contributing)
- [TOAST UI Family](#-toast-ui-family)
- [Used By](#-used-by)
- [License](#-license)


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
    <td align="center"><a href="http://ivesvh.com"><img src="https://avatars0.githubusercontent.com/u/587016?v=3" width="100px;" alt="Ives van Hoorne"/><br /><sub><b>Ives van Hoorne</b></sub></a><br /><a href="#question-CompuIves" title="Answering Questions">💬</a> <a href="#blog-CompuIves" title="Blogposts">📝</a> <a href="https://github.com/codesandbox/codesandbox-client/issues?q=author%3ACompuIves" title="Bug reports">🐛</a> <a href="https://github.com/codesandbox/codesandbox-client/commits?author=CompuIves" title="Code">💻</a> <a href="#design-CompuIves" title="Design">🎨</a> <a href="https://github.com/codesandbox/codesandbox-client/commits?author=CompuIves" title="Documentation">📖</a> <a href="#example-CompuIves" title="Examples">💡</a> <a href="#infra-CompuIves" title="Infrastructure (Hosting, Build-Tools, etc)">🚇</a> <a href="#review-CompuIves" title="Reviewed Pull Requests">👀</a> <a href="https://github.com/codesandbox/codesandbox-client/commits?author=CompuIves" title="Tests">⚠️</a> <a href="#tool-CompuIves" title="Tools">🔧</a></td>
    <td align="center"><a href="http://donavon.com"><img src="https://avatars0.githubusercontent.com/u/887639?v=3" width="100px;" alt="Donavon West"/><br /><sub><b>Donavon West</b></sub></a><br /><a href="https://github.com/codesandbox/codesandbox-client/commits?author=donavon" title="Code">💻</a></td>
    <td align="center"><a href="http://www.jeffallen.io/"><img src="https://avatars0.githubusercontent.com/u/5266810?v=3" width="100px;" alt="Jeff Allen"/><br /><sub><b>Jeff Allen</b></sub></a><br /><a href="https://github.com/codesandbox/codesandbox-client/commits?author=vueu" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/bengummer"><img src="https://avatars0.githubusercontent.com/u/1089897?v=3" width="100px;" alt="Ben Gummer"/><br /><sub><b>Ben Gummer</b></sub></a><br /><a href="https://github.com/codesandbox/codesandbox-client/commits?author=bengummer" title="Code">💻</a></td>
    <td align="center"><a href="http://twitter.com/faceyspacey"><img src="https://avatars3.githubusercontent.com/u/154732?v=3" width="100px;" alt="James Gillmore"/><br /><sub><b>James Gillmore</b></sub></a><br /><a href="https://github.com/codesandbox/codesandbox-client/commits?author=faceyspacey" title="Code">💻</a> <a href="https://github.com/codesandbox/codesandbox-client/issues?q=author%3Afaceyspacey" title="Bug reports">🐛</a></td>
    <td align="center"><a href="https://github.com/viankakrisna"><img src="https://avatars1.githubusercontent.com/u/9636410?v=4" width="100px;" alt="Ade Viankakrisna Fadlil"/><br /><sub><b>Ade Viankakrisna Fadlil</b></sub></a><br /><a href="https://github.com/codesandbox/codesandbox-client/commits?author=viankakrisna" title="Code">💻</a></td>
    <td align="center"><a href="https://twitter.com/tushkiz"><img src="https://avatars1.githubusercontent.com/u/1854763?v=4" width="100px;" alt="Tushar Sonawane"/><br /><sub><b>Tushar Sonawane</b></sub></a><br /><a href="#question-Tushkiz" title="Answering Questions">💬</a> <a href="https://github.com/codesandbox/codesandbox-client/commits?author=Tushkiz" title="Code">💻</a> <a href="https://github.com/codesandbox/codesandbox-client/commits?author=Tushkiz" title="Documentation">📖</a> <a href="#ideas-Tushkiz" title="Ideas, Planning, & Feedback">🤔</a></td>
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
