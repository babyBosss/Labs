import os
import sys
from PyQt5.QtWidgets import (QApplication, QMainWindow, QLabel, QAction, QMessageBox, QFileDialog,
                             QScrollArea, QSizePolicy, QRubberBand, QInputDialog)
from PyQt5.QtCore import Qt, QSize, QRect
from PyQt5.QtGui import QIcon, QPixmap, QImage, QPalette

icon_path = "icons"


class imageLabel(QLabel):
    # Класс для работы с изображением
    def __init__(self, parent, image=None):
        super().__init__(parent)
        self.parent = parent
        self.image = QImage()
        self.original_image = self.image.copy
        self.rubber_band = QRubberBand(QRubberBand.Rectangle, self)
        self.setSizePolicy(QSizePolicy.Ignored, QSizePolicy.Ignored)
        self.setScaledContents(True)

        # Загрузка изображения
        self.setPixmap(QPixmap().fromImage(self.image))
        self.setAlignment(Qt.AlignCenter)

    def open_image(self):
        # Открытие файла
        image_file, _ = QFileDialog.getOpenFileName(self, "Open Image",
                                                    "", "PNG Files (*.png);;JPG Files (*.jpeg *.jpg );;Bitmap Files (*.bmp);;\
                GIF Files (*.gif)")

        if image_file:
            self.parent.update_actions()
            self.image = QImage(image_file)
            self.original_image = self.image.copy()
            self.setPixmap(QPixmap().fromImage(self.image))
            self.resize(self.pixmap().size())
        else:
            QMessageBox.information(self, "Error",
                                    "Unable to open image.", QMessageBox.Ok)

    def save_image(self):
        # Сохранение изображения
        if not self.image.isNull():
            image_file, _ = QFileDialog.getSaveFileName(self, "Save Image",
                                                        "", "PNG Files (*.png);;JPG Files (*.jpeg *.jpg );;Bitmap Files (*.bmp);;\
                    GIF Files (*.gif)")

            if image_file and not self.image.isNull():
                self.image.save(image_file)
            else:
                QMessageBox.information(self, "Error",
                                        "Unable to save image.", QMessageBox.Ok)
        else:
            QMessageBox.information(self, "Empty Image",
                                    "There is no image to save.", QMessageBox.Ok)

    def revert_to_original(self):
        self.image = self.original_image
        self.setPixmap(QPixmap().fromImage(self.image))
        self.repaint()

    def median_filter(self):
        if not self.image.isNull():
            h = self.image.height()
            w = self.image.width()
            for y in range(1, h - 1):
                for x in range(1, w - 1):
                    cube = [(self.image.pixel(x - 1, y - 1)), (self.image.pixel(x, y - 1)),
                            (self.image.pixel(x + 1, y - 1)),
                            (self.image.pixel(x - 1, y)), (self.image.pixel(x, y)), (self.image.pixel(x + 1, y)),
                            (self.image.pixel(x - 1, y + 1)), (self.image.pixel(x, y + 1)),
                            (self.image.pixel(x + 1, y + 1))]
                    sorted_cube = sorted(cube)
                    new_value = sorted_cube[4]
                    if x == 1:
                        self.image.setPixel(x - 1, y, new_value)
                    if y == 1:
                        self.image.setPixel(x, y - 1, new_value)
                    if x == w - 1:
                        self.image.setPixel(x + 1, y, new_value)
                    if y == h - 1:
                        self.image.setPixel(x, y + 1, new_value)

                    self.image.setPixel(x, y, new_value)
        self.setPixmap(QPixmap().fromImage(self.image))
        self.repaint()
        print("Done")

    def show_rang_dialog(self):
        text, ok = QInputDialog.getText(self, 'Input Dialog', 'Введите коэффициент от 1 до 13:')
        if ok:
            try:
                self.rang_filter(int(text))
            except Exception as e:
                print("Введено неправильно значение", e)

    def rang_filter(self, R):
        if not self.image.isNull():
            h = self.image.height()
            w = self.image.width()
            for y in range(2, h - 2):
                for x in range(2, w - 2):
                    cube = [(self.image.pixel(x - 2, y - 2)), (self.image.pixel(x - 1, y - 2)),
                            (self.image.pixel(x, y - 2)), (self.image.pixel(x + 1, y - 2)),
                            (self.image.pixel(x + 2, y - 2)),
                            (self.image.pixel(x - 2, y - 1)), (self.image.pixel(x - 1, y - 1)),
                            (self.image.pixel(x, y - 1)), (self.image.pixel(x + 1, y - 1)),
                            (self.image.pixel(x + 2, y - 1)),
                            (self.image.pixel(x - 2, y - 0)), (self.image.pixel(x - 1, y - 0)),
                            (self.image.pixel(x, y - 0)), (self.image.pixel(x + 1, y - 0)),
                            (self.image.pixel(x + 2, y - 0)),
                            (self.image.pixel(x - 2, y + 1)), (self.image.pixel(x - 1, y + 1)),
                            (self.image.pixel(x, y + 1)), (self.image.pixel(x + 1, y + 1)),
                            (self.image.pixel(x + 2, y + 1)),
                            (self.image.pixel(x - 2, y + 2)), (self.image.pixel(x - 1, y + 2)),
                            (self.image.pixel(x, y + 2)), (self.image.pixel(x + 1, y + 2)),
                            (self.image.pixel(x + 2, y + 2)),
                            ]
                    k = R
                    l = len(cube) - k
                    sorted_cube = sorted(cube)
                    if abs(sorted_cube[k] - self.image.pixel(x, y)) < abs(sorted_cube[l] - self.image.pixel(x, y)):
                        new_value = sorted_cube[k]
                    else:
                        new_value = sorted_cube[l]

                    if x == 2:
                        self.image.setPixel(x - 1, y, new_value)
                        self.image.setPixel(x - 2, y, new_value)
                    if y == 2:
                        self.image.setPixel(x, y - 1, new_value)
                        self.image.setPixel(x, y - 2, new_value)
                    if x == w - 2:
                        self.image.setPixel(x + 1, y, new_value)
                        self.image.setPixel(x + 2, y, new_value)
                    if y == h - 2:
                        self.image.setPixel(x, y + 1, new_value)
                        self.image.setPixel(x, y + 2, new_value)
                    self.image.setPixel(x, y, new_value)
        self.setPixmap(QPixmap().fromImage(self.image))
        self.repaint()
        print("Done")

    def mousePressEvent(self, event):
        self.origin = event.pos()
        if not (self.rubber_band):
            self.rubber_band = QRubberBand(QRubberBand.Rectangle, self)
        self.rubber_band.setGeometry(QRect(self.origin, QSize()))
        self.rubber_band.show()
        print(self.rubber_band.x())
        print(self.rubber_band.y())


class PhotoEditorGUI(QMainWindow):

    def __init__(self):
        super().__init__()
        self.initializeUI()
        self.image = QImage()

    def initializeUI(self):
        self.setMinimumSize(300, 200)
        self.setWindowTitle("Photo Editor")
        self.showMaximized()
        self.create_main_label()
        self.create_menu()
        self.show()

    def create_menu(self):
        self.open_act = QAction(QIcon(os.path.join(icon_path, "open.png")), 'Open...', self)
        self.open_act.setShortcut('Ctrl+O')
        self.open_act.triggered.connect(self.image_label.open_image)

        self.save_act = QAction(QIcon(os.path.join(icon_path, "save.png")), "Save...", self)
        self.save_act.setShortcut('Ctrl+S')
        self.save_act.triggered.connect(self.image_label.save_image)
        self.save_act.setEnabled(False)

        self.revert_act = QAction("Revert to Original", self)
        self.revert_act.triggered.connect(self.image_label.revert_to_original)
        self.revert_act.setEnabled(False)

        self.median_act = QAction("Add median filter", self)
        self.median_act.triggered.connect(self.image_label.median_filter)
        self.median_act.setEnabled(False)

        self.rang_act = QAction("Add rang filter", self)
        self.rang_act.triggered.connect(self.image_label.show_rang_dialog)
        self.rang_act.setEnabled(False)

        # Create menubar
        menu_bar = self.menuBar()
        menu_bar.setNativeMenuBar(False)

        # Create file menu and add actions
        file_menu = menu_bar.addMenu('File')
        file_menu.addAction(self.open_act)
        file_menu.addSeparator()
        file_menu.addAction(self.save_act)

        edit_menu = menu_bar.addMenu('Edit')
        edit_menu.addAction(self.revert_act)
        edit_menu = menu_bar.addMenu('Median filter')
        edit_menu.addAction(self.median_act)
        edit_menu = menu_bar.addMenu('Rang filter')
        edit_menu.addAction(self.rang_act)

    def create_main_label(self):
        self.image_label = imageLabel(self)
        self.image_label.resize(self.image_label.pixmap().size())
        self.scroll_area = QScrollArea()
        self.scroll_area.setBackgroundRole(QPalette.Dark)
        self.scroll_area.setAlignment(Qt.AlignCenter)
        self.scroll_area.setWidget(self.image_label)
        self.setCentralWidget(self.scroll_area)

    def update_actions(self):
        self.save_act.setEnabled(True)
        self.revert_act.setEnabled(True)
        self.median_act.setEnabled(True)
        self.rang_act.setEnabled(True)

    def keyPressEvent(self, event):
        if event.key() == Qt.Key_Escape:
            self.close()
        if event.key() == Qt.Key_F1:
            if self.isMaximized():
                self.showNormal()
            else:
                self.showMaximized()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    app.setAttribute(Qt.AA_DontShowIconsInMenus, True)
    window = PhotoEditorGUI()
    sys.exit(app.exec_())
