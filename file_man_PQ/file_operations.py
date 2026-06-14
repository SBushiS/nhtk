import os
import shutil
from pathlib import Path
import subprocess

class FileOperations:
    """Класс для работы с файлами и директориями"""
    
    @staticmethod
    def create_directory(path: str) -> bool:
        try:
            Path(path).mkdir(parents=True, exist_ok=True)
            return True
        except Exception as e:
            print(f"Ошибка создания директории: {e}")
            return False

    @staticmethod
    def copy_file(src: str, dst: str) -> bool:
        try:
            shutil.copy2(src, dst)
            return True
        except Exception as e:
            print(f"Ошибка копирования: {e}")
            return False

    @staticmethod
    def move_file(src: str, dst: str) -> bool:
        try:
            shutil.move(src, dst)
            return True
        except Exception as e:
            print(f"Ошибка перемещения: {e}")
            return False

    @staticmethod
    def delete_file(path: str) -> bool:
        try:
            if os.path.isfile(path):
                os.remove(path)
            elif os.path.isdir(path):
                shutil.rmtree(path)
            return True
        except Exception as e:
            print(f"Ошибка удаления: {e}")
            return False

    @staticmethod
    def execute_linux_command(command: str) -> tuple:
        """Выполнение команд ОС"""
        try:
            result = subprocess.run(
                command, 
                shell=True, 
                capture_output=True, 
                text=True, 
                timeout=30
            )
            return result.returncode, result.stdout, result.stderr
        except Exception as e:
            return -1, "", str(e)