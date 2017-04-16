#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
ZetCode PyQt5 tutorial

In this example, we show how to emit a
signal.
"""

import sys
from PyQt5.QtCore import pyqtSignal, QObject
from PyQt5.QtWidgets import QMainWindow, QApplication

class Communication(QObject):
    closeApp = pyqtSignal()

class Example(QMainWindow):

    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.c = Communication()
        self.c.closeApp.connect(self.close)

        self.setGeometry(300, 300, 290, 150)
        self.setWindowTitle("Emit signal")
        self.show()

    def mousePressEvent(self, event):
        self.c.closeApp.emit()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
