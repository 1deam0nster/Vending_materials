import sqlite3 as sq
import os

with sq.connect("data.db") as con:
    cur = con.cursor()
    # cur.execute("""CREATE TABLE IF NOT EXISTS coffe(
    #     id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    #     name TEXT NOT NULL,
    #     descriptions TEXT nOT NULL,
    #     short_description TEXT NOT NULL,
    #     price INTEGER NOT NULL,
    #     value INTEGER NOT NULL,
    #     g_code TEXT NOT NULL,
    #     img_url TEXT NOT NULL,
    #     link_url TEXT NOT NULL,
    #     flavor TEXT NOT NULL,
    #     roasting TEXT NOT NULL,
    #     grain TEXT NOT NULL,
    #     country TEXT NOT NULL,
    #     intensity TEXT NOT NULL,
    #     brand TEXT NOT NULL
    #     )""")

    cur.execute("""CREATE TABLE IF NOT EXISTS stuff(
        id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
        name TEXT NOT NULL,
        price INTEGER NOT NULL,
        value INTEGER NOT NULL,
        g_code TEXT NOT NULL
        )""")