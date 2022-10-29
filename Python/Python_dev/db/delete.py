import sqlite3 as sq

with sq.connect("data.db") as con:
    cur = con.cursor()
    cur.execute("""DROP TABLE coffe""")