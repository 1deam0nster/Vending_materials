# База дынных
### Действия с БД
Создание таблицы из консоли Python
```
py
from db.db import create_db
create_db()
```

Создание таблицы c помощью файла Python
```
python create.py
```

Удаление таблицы c помощью файла Python
```
python delete.py
```

### Описание табличных данных
| Название ячейки | Тип данных | Описание |
| --- | --- | --- |
| id |  INTEGER | Уникальное значение id |
| name | TEXT | Название кофе |
| descriptions | TEXT | Описание |
| short_description | TEXT | Короткое описание |
| value | INTEGER | Кол-во капсул |
| g-code | TEXT | Код для МК |
| img_url | TEXT | Ссылка на изображение |
| link_url | TEXT | Ссылка на страницу покупки |
