#include <QPalette>
#include <QColor>
#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QStyleFactory>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("Fusion"));

    // Paleta dark profesionala
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window,          QColor(18, 18, 24));
    darkPalette.setColor(QPalette::WindowText,      QColor(220, 220, 230));
    darkPalette.setColor(QPalette::Base,            QColor(28, 28, 36));
    darkPalette.setColor(QPalette::AlternateBase,   QColor(35, 35, 45));
    darkPalette.setColor(QPalette::ToolTipBase,     QColor(28, 28, 36));
    darkPalette.setColor(QPalette::ToolTipText,     QColor(220, 220, 230));
    darkPalette.setColor(QPalette::Text,            QColor(220, 220, 230));
    darkPalette.setColor(QPalette::Button,          QColor(40, 40, 55));
    darkPalette.setColor(QPalette::ButtonText,      QColor(220, 220, 230));
    darkPalette.setColor(QPalette::BrightText,      Qt::red);
    darkPalette.setColor(QPalette::Link,            QColor(100, 140, 255));
    darkPalette.setColor(QPalette::Highlight,       QColor(100, 140, 255));
    darkPalette.setColor(QPalette::HighlightedText, Qt::white);
    app.setPalette(darkPalette);

    app.setStyleSheet(R"(
        /* ── GLOBAL ─────────────────────────────── */
        QWidget {
            font-family: 'Segoe UI', 'Arial', sans-serif;
            font-size: 13px;
            color: #dcdce6;
            background-color: #12121a;
        }

        /* ── FERESTRE / PAGINI ───────────────────── */
        QMainWindow, QStackedWidget {
            background-color: #12121a;
        }

        /* ── LABELS ──────────────────────────────── */
        QLabel {
            color: #a0a0b8;
            font-size: 12px;
            font-weight: 500;
        }

        /* Label-ul de WELCOME (mare, sus) */
        QLabel#labelNume {
            color: #ffffff;
            font-size: 22px;
            font-weight: bold;
            padding: 10px 0px;
        }

        /* ── LINE EDIT ───────────────────────────── */
        QLineEdit {
            background-color: #1e1e2e;
            color: #e0e0f0;
            border: 1.5px solid #3a3a55;
            border-radius: 8px;
            padding: 8px 12px;
            font-size: 13px;
            selection-background-color: #6478ff;
        }
        QLineEdit:focus {
            border: 1.5px solid #6478ff;
            background-color: #22223a;
        }
        QLineEdit:hover {
            border: 1.5px solid #5060cc;
        }

        /* ── TEXT EDIT / PLAIN TEXT EDIT ─────────── */
        QTextEdit, QPlainTextEdit {
            background-color: #1e1e2e;
            color: #e0e0f0;
            border: 1.5px solid #3a3a55;
            border-radius: 8px;
            padding: 8px;
            font-size: 13px;
            selection-background-color: #6478ff;
        }
        QTextEdit:focus, QPlainTextEdit:focus {
            border: 1.5px solid #6478ff;
        }

        /* ── LIST WIDGET ─────────────────────────── */
        QListWidget {
            background-color: #1a1a2a;
            color: #d0d0e8;
            border: 1.5px solid #3a3a55;
            border-radius: 8px;
            padding: 4px;
            outline: none;
            font-size: 13px;
        }
        QListWidget::item {
            padding: 8px 12px;
            border-radius: 6px;
            margin: 2px 4px;
        }
        QListWidget::item:hover {
            background-color: #2a2a45;
            color: #ffffff;
        }
        QListWidget::item:selected {
            background-color: #3a4aaa;
            color: #ffffff;
            font-weight: bold;
        }

        /* ── COMBO BOX ───────────────────────────── */
        QComboBox {
            background-color: #1e1e2e;
            color: #e0e0f0;
            border: 1.5px solid #3a3a55;
            border-radius: 8px;
            padding: 7px 12px;
            font-size: 13px;
            min-width: 120px;
        }
        QComboBox:hover {
            border: 1.5px solid #5060cc;
        }
        QComboBox:focus {
            border: 1.5px solid #6478ff;
        }
        QComboBox::drop-down {
            border: none;
            width: 28px;
        }
        QComboBox::down-arrow {
            width: 14px;
            height: 14px;
        }
        QComboBox QAbstractItemView {
            background-color: #1e1e2e;
            color: #e0e0f0;
            border: 1px solid #3a3a55;
            border-radius: 6px;
            selection-background-color: #3a4aaa;
            padding: 4px;
        }

        /* ── BUTOANE GENERALE ────────────────────── */
        QPushButton {
            background-color: #2a2a42;
            color: #d0d0f0;
            border: 1.5px solid #4040668;
            border-radius: 8px;
            padding: 9px 20px;
            font-size: 13px;
            font-weight: 600;
            min-width: 90px;
        }
        QPushButton:hover {
            background-color: #35356a;
            color: #ffffff;
            border: 1.5px solid #6478ff;
        }
        QPushButton:pressed {
            background-color: #4a5aff;
            color: #ffffff;
        }
        QPushButton:disabled {
            background-color: #1e1e2e;
            color: #555570;
            border: 1.5px solid #2a2a3e;
        }

        /* ── BUTON PRINCIPAL (Login / SignUp / Post) ─ */
        QPushButton#butonLogin,
        QPushButton#SignUp,
        QPushButton#PostProject,
        QPushButton#ApplyButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                        stop:0 #4a5aff, stop:1 #6478ff);
            color: #ffffff;
            border: none;
            border-radius: 10px;
            padding: 11px 28px;
            font-size: 14px;
            font-weight: bold;
        }
        QPushButton#butonLogin:hover,
        QPushButton#SignUp:hover,
        QPushButton#PostProject:hover,
        QPushButton#ApplyButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                        stop:0 #5a6aff, stop:1 #7488ff);
        }

        /* ── BUTON ACCEPT (verde) ─────────────────── */
        QPushButton#ACCEPTOFFER,
        QPushButton#Approve_buton,
        QPushButton#UploadButon {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                        stop:0 #1a7a4a, stop:1 #22a060);
            color: #ffffff;
            border: none;
            border-radius: 8px;
            font-weight: bold;
        }
        QPushButton#ACCEPTOFFER:hover,
        QPushButton#Approve_buton:hover,
        QPushButton#UploadButon:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                        stop:0 #22a060, stop:1 #2acc78);
        }

        /* ── BUTON REFUSE/LOGOUT (rosu) ──────────── */
        QPushButton#REFUSEOFFER,
        QPushButton#RefuseWork_buton,
        QPushButton#LOGOUT {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                        stop:0 #7a1a1a, stop:1 #aa2222);
            color: #ffffff;
            border: none;
            border-radius: 8px;
            font-weight: bold;
        }
        QPushButton#REFUSEOFFER:hover,
        QPushButton#RefuseWork_buton:hover,
        QPushButton#LOGOUT:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                        stop:0 #aa2222, stop:1 #cc3333);
        }

        /* ── SCROLL BAR ──────────────────────────── */
        QScrollBar:vertical {
            background: #1a1a28;
            width: 8px;
            border-radius: 4px;
        }
        QScrollBar::handle:vertical {
            background: #4a4a70;
            border-radius: 4px;
            min-height: 30px;
        }
        QScrollBar::handle:vertical:hover {
            background: #6478ff;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px;
        }

        /* ── MESSAGE BOX ─────────────────────────── */
        QMessageBox {
            background-color: #1e1e2e;
        }
        QMessageBox QLabel {
            color: #dcdce6;
            font-size: 13px;
        }

        /* ── GROUP BOX (daca ai) ─────────────────── */
        QGroupBox {
            border: 1.5px solid #3a3a55;
            border-radius: 10px;
            margin-top: 14px;
            padding: 10px;
            font-weight: bold;
            color: #8888bb;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 12px;
            padding: 0 6px;
            color: #6478ff;
        }
    )");

    MainWindow window;
    window.setWindowTitle("FreelanceHub");
    window.resize(1280, 800);
    window.show();
    return app.exec();
}