import sqlite3
from datetime import datetime

class Database:
    def __init__(self, db_name="directories.db"):
        self.conn = sqlite3.connect(db_name)
        self.create_table()

    def create_table(self):
        self.conn.execute('''
            CREATE TABLE IF NOT EXISTS directories (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                path TEXT NOT NULL,
                created_at TEXT NOT NULL,
                comment TEXT
            )
        ''')
        self.conn.commit()

    def add_directory(self, path: str, comment: str = ""):
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        self.conn.execute(
            "INSERT INTO directories (path, created_at, comment) VALUES (?, ?, ?)",
            (path, timestamp, comment)
        )
        self.conn.commit()

    def get_all_directories(self):
        cursor = self.conn.execute("SELECT * FROM directories ORDER BY created_at DESC")
        return cursor.fetchall()

    def close(self):
        self.conn.close()