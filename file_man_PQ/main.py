import sys
from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QLabel, QLineEdit, QPushButton, QTextEdit, QFileDialog,
    QMessageBox, QTableWidget, QTableWidgetItem, QTabWidget
)
from PyQt6.QtCore import Qt
from file_operations import FileOperations
from database import Database


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Форма PyQT")
        self.setGeometry(100, 100, 1100, 750)
        
        self.file_ops = FileOperations()
        self.db = Database()
        
        self.init_ui()

    def init_ui(self):
        central = QWidget()
        self.setCentralWidget(central)
        main_layout = QVBoxLayout(central)
        
        tabs = QTabWidget()
        main_layout.addWidget(tabs)
        
        # Вкладка 1: Файловые операции
        tab_files = QWidget()
        tabs.addTab(tab_files, "Файловые операции")
        self.setup_file_tab(tab_files)
        
        # Вкладка 2: Директории + БД
        tab_dirs = QWidget()
        tabs.addTab(tab_dirs, "Директории + БД")
        self.setup_dirs_tab(tab_dirs)
        
        # Вкладка 3: Команды ОС
        tab_linux = QWidget()
        tabs.addTab(tab_linux, "Команды ОС (Linux/Windows)")
        self.setup_linux_tab(tab_linux)

    def setup_file_tab(self, parent):
        lay = QVBoxLayout(parent)
        
        # Исходный файл
        h1 = QHBoxLayout()
        self.src_edit = QLineEdit()
        btn_src = QPushButton("Выбрать файл/папку")
        btn_src.clicked.connect(self.choose_source)
        h1.addWidget(QLabel("Исходный:"))
        h1.addWidget(self.src_edit)
        h1.addWidget(btn_src)
        lay.addLayout(h1)
        
        # Целевой путь
        h2 = QHBoxLayout()
        self.dst_edit = QLineEdit()
        btn_dst = QPushButton("Выбрать цель")
        btn_dst.clicked.connect(self.choose_dest)
        h2.addWidget(QLabel("Цель:"))
        h2.addWidget(self.dst_edit)
        h2.addWidget(btn_dst)
        lay.addLayout(h2)
        
        # Кнопки
        btn_layout = QHBoxLayout()
        btn_copy = QPushButton("Копировать")
        btn_move = QPushButton("Переместить")
        btn_delete = QPushButton("Удалить")
        btn_create = QPushButton("Создать папку")
        
        btn_copy.clicked.connect(self.copy_file)
        btn_move.clicked.connect(self.move_file)
        btn_delete.clicked.connect(self.delete_file)
        btn_create.clicked.connect(self.create_dir)
        
        btn_layout.addWidget(btn_copy)
        btn_layout.addWidget(btn_move)
        btn_layout.addWidget(btn_delete)
        btn_layout.addWidget(btn_create)
        lay.addLayout(btn_layout)
        
        self.log_text = QTextEdit()
        self.log_text.setReadOnly(True)
        lay.addWidget(QLabel("Лог операций:"))
        lay.addWidget(self.log_text)

    def setup_dirs_tab(self, parent):
        lay = QVBoxLayout(parent)
        
        h = QHBoxLayout()
        self.dir_path = QLineEdit()
        btn_browse = QPushButton("Обзор")
        btn_browse.clicked.connect(self.browse_dir)
        btn_add = QPushButton("Создать и сохранить в БД")
        btn_add.clicked.connect(self.create_and_save_dir)
        
        h.addWidget(QLabel("Путь новой папки:"))
        h.addWidget(self.dir_path)
        h.addWidget(btn_browse)
        h.addWidget(btn_add)
        lay.addLayout(h)
        
        self.dir_comment = QLineEdit()
        self.dir_comment.setPlaceholderText("Комментарий (необязательно)")
        lay.addWidget(QLabel("Комментарий:"))
        lay.addWidget(self.dir_comment)
        
        self.table = QTableWidget(0, 4)
        self.table.setHorizontalHeaderLabels(["ID", "Путь", "Дата создания", "Комментарий"])
        self.table.horizontalHeader().setStretchLastSection(True)
        lay.addWidget(self.table)
        
        btn_refresh = QPushButton("Обновить список")
        btn_refresh.clicked.connect(self.load_directories)
        lay.addWidget(btn_refresh)
        
        self.load_directories()

    def setup_linux_tab(self, parent):
        lay = QVBoxLayout(parent)
        
        self.cmd_input = QLineEdit()
        self.cmd_input.setPlaceholderText("Введите команду: ls, dir, pwd, whoami, ipconfig и т.д.")
        lay.addWidget(QLabel("Команда ОС:"))
        lay.addWidget(self.cmd_input)
        
        btn_exec = QPushButton("Выполнить команду")
        btn_exec.clicked.connect(self.execute_command)
        lay.addWidget(btn_exec)
        
        self.cmd_output = QTextEdit()
        self.cmd_output.setReadOnly(True)
        lay.addWidget(QLabel("Результат выполнения:"))
        lay.addWidget(self.cmd_output)

    # ====================== Обработчики ======================

    def choose_source(self):
        path, _ = QFileDialog.getOpenFileName(self, "Выберите файл")
        if path:
            self.src_edit.setText(path)

    def choose_dest(self):
        path = QFileDialog.getExistingDirectory(self, "Выберите папку назначения")
        if path:
            self.dst_edit.setText(path)

    def copy_file(self):
        src = self.src_edit.text().strip()
        dst = self.dst_edit.text().strip()
        if not src or not dst:
            QMessageBox.warning(self, "Ошибка", "Укажите исходный и целевой путь!")
            return
        if self.file_ops.copy_file(src, dst):
            self.log("✅ Файл успешно скопирован")
        else:
            self.log("❌ Ошибка копирования")

    def move_file(self):
        src = self.src_edit.text().strip()
        dst = self.dst_edit.text().strip()
        if not src or not dst:
            QMessageBox.warning(self, "Ошибка", "Укажите пути!")
            return
        if self.file_ops.move_file(src, dst):
            self.log("✅ Файл успешно перемещён")
        else:
            self.log("❌ Ошибка перемещения")

    def delete_file(self):
        path = self.src_edit.text().strip()
        if not path:
            return
        if QMessageBox.question(self, "Подтверждение", f"Удалить {path}?") == QMessageBox.StandardButton.Yes:
            if self.file_ops.delete_file(path):
                self.log("✅ Успешно удалено")
            else:
                self.log("❌ Ошибка удаления")

    def create_dir(self):
        path = self.dst_edit.text().strip()
        if not path:
            return
        if self.file_ops.create_directory(path):
            self.log(f"✅ Директория создана: {path}")
        else:
            self.log("❌ Не удалось создать директорию")

    def create_and_save_dir(self):
        path = self.dir_path.text().strip()
        comment = self.dir_comment.text().strip()
        if not path:
            QMessageBox.warning(self, "Ошибка", "Введите путь!")
            return
        
        if self.file_ops.create_directory(path):
            self.db.add_directory(path, comment)
            self.log(f"✅ Директория создана и сохранена в БД")
            self.load_directories()
        else:
            self.log("❌ Не удалось создать директорию")

    def load_directories(self):
        dirs = self.db.get_all_directories()
        self.table.setRowCount(len(dirs))
        for row, data in enumerate(dirs):
            for col, value in enumerate(data):
                item = QTableWidgetItem(str(value))
                self.table.setItem(row, col, item)

    def browse_dir(self):
        path = QFileDialog.getExistingDirectory(self, "Выберите папку")
        if path:
            self.dir_path.setText(path)

    def execute_command(self):
        cmd = self.cmd_input.text().strip()
        if not cmd:
            return
        code, stdout, stderr = self.file_ops.execute_linux_command(cmd)
        output = f"Код возврата: {code}\n\n=== STDOUT ===\n{stdout}\n\n=== STDERR ===\n{stderr}"
        self.cmd_output.setText(output)

    def log(self, message: str):
        self.log_text.append(message)

    def closeEvent(self, event):
        self.db.close()
        event.accept()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())