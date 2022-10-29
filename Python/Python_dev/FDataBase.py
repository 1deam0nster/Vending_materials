import sqlite3
 
class FDataBase:
    def __init__(self, db):
        self.__db = db
        self.__cur = db.cursor()
 
    def getCoffe(self):
        sql = '''SELECT * FROM coffe'''
        try:
            self.__cur.execute(sql)
            res = self.__cur.fetchall()
            if res: return res
        except:
            print("Ошибка чтения из БД")
        return []

    def addCoffe(self, id, name, descriptions, short_description, price, value, g_code, img_url, link_url):
        try:
            self.__cur.execute("INSERT INTO coffe VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?)", (id, name, descriptions, short_description, price, value, g_code, img_url, link_url))
            self.__db.commit()
        except sqlite3.Error as e:
            print("Ошибка добавления статьи в БД "+str(e))
            return False
 
        return True

    def getSort(self, id_coffe):
        try:
            self.__cur.execute(f"SELECT name, descriptions FROM coffe WHERE id = {id_coffe} LIMIT 1")
            res = self.__cur.fetchone()
            if res:
                return res
        except sqlite3.Error as e:
            print("Ошибка получения статьи из БД "+str(e))
 
        return (False, False)

    def getById(self, id_coffe):
        try:
            self.__cur.execute(f"SELECT id, name, descriptions, short_description, price, value, g_code, img_url, link_url FROM coffe WHERE id = {id_coffe} LIMIT 1")
            res = self.__cur.fetchone()
            if res:
                return res
        except sqlite3.Error as e:
            print("Ошибка получения статьи из БД "+str(e))
 
        return (False, False, False, False, False, False, False, False)

    def updateCoffe(self, id_coffe, name, descriptions, short_description, price, value, g_code, img_url, link_url):
        try:
            self.__cur.execute(f"UPDATE coffe SET name='{name}', descriptions='{descriptions}', short_description='{short_description}', price='{price}', value='{value}', g_code='{g_code}', img_url='{img_url}', link_url='{link_url}' WHERE ROWID={id_coffe};")
            res = self.__cur.fetchone()
            if res:
                return res
        except sqlite3.Error as e:
            print("Ошибка получения статьи из БД "+str(e))
 
        return (False, False, False, False, False, False, False, False)