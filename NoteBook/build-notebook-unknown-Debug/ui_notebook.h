/********************************************************************************
** Form generated from reading UI file 'notebook.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEBOOK_H
#define UI_NOTEBOOK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NoteBOOK
{
public:
    QAction *actionnew;
    QAction *actionopen;
    QAction *actionsave;
    QAction *actionsaveas;
    QAction *actionfind;
    QAction *actioninfo;
    QAction *actionreplace;
    QAction *actionfont;
    QAction *actionclose;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPlainTextEdit *textedit;
    QLabel *status;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *NoteBOOK)
    {
        if (NoteBOOK->objectName().isEmpty())
            NoteBOOK->setObjectName(QString::fromUtf8("NoteBOOK"));
        NoteBOOK->resize(1004, 659);
        actionnew = new QAction(NoteBOOK);
        actionnew->setObjectName(QString::fromUtf8("actionnew"));
        actionnew->setCheckable(false);
        actionnew->setChecked(false);
        actionopen = new QAction(NoteBOOK);
        actionopen->setObjectName(QString::fromUtf8("actionopen"));
        actionsave = new QAction(NoteBOOK);
        actionsave->setObjectName(QString::fromUtf8("actionsave"));
        actionsaveas = new QAction(NoteBOOK);
        actionsaveas->setObjectName(QString::fromUtf8("actionsaveas"));
        actionfind = new QAction(NoteBOOK);
        actionfind->setObjectName(QString::fromUtf8("actionfind"));
        actioninfo = new QAction(NoteBOOK);
        actioninfo->setObjectName(QString::fromUtf8("actioninfo"));
        actionreplace = new QAction(NoteBOOK);
        actionreplace->setObjectName(QString::fromUtf8("actionreplace"));
        actionfont = new QAction(NoteBOOK);
        actionfont->setObjectName(QString::fromUtf8("actionfont"));
        actionclose = new QAction(NoteBOOK);
        actionclose->setObjectName(QString::fromUtf8("actionclose"));
        centralWidget = new QWidget(NoteBOOK);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textedit = new QPlainTextEdit(centralWidget);
        textedit->setObjectName(QString::fromUtf8("textedit"));

        gridLayout->addWidget(textedit, 0, 0, 1, 1);

        status = new QLabel(centralWidget);
        status->setObjectName(QString::fromUtf8("status"));

        gridLayout->addWidget(status, 1, 0, 1, 1);

        NoteBOOK->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(NoteBOOK);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1004, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        NoteBOOK->setMenuBar(menuBar);
        statusBar = new QStatusBar(NoteBOOK);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        NoteBOOK->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menu->addAction(actionnew);
        menu->addAction(actionopen);
        menu->addAction(actionsave);
        menu->addAction(actionsaveas);
        menu->addSeparator();
        menu->addAction(actionclose);
        menu_2->addAction(actionfind);
        menu_2->addAction(actionreplace);
        menu_2->addAction(actionfont);
        menu_3->addAction(actioninfo);

        retranslateUi(NoteBOOK);

        QMetaObject::connectSlotsByName(NoteBOOK);
    } // setupUi

    void retranslateUi(QMainWindow *NoteBOOK)
    {
        NoteBOOK->setWindowTitle(QApplication::translate("NoteBOOK", "NoteBOOK", nullptr));
        actionnew->setText(QApplication::translate("NoteBOOK", "\346\226\260\345\273\272", nullptr));
#ifndef QT_NO_SHORTCUT
        actionnew->setShortcut(QApplication::translate("NoteBOOK", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
        actionopen->setText(QApplication::translate("NoteBOOK", "\346\211\223\345\274\200", nullptr));
#ifndef QT_NO_SHORTCUT
        actionopen->setShortcut(QApplication::translate("NoteBOOK", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionsave->setText(QApplication::translate("NoteBOOK", "\344\277\235\345\255\230", nullptr));
#ifndef QT_NO_SHORTCUT
        actionsave->setShortcut(QApplication::translate("NoteBOOK", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionsaveas->setText(QApplication::translate("NoteBOOK", "\345\217\246\345\255\230\344\270\272", nullptr));
        actionfind->setText(QApplication::translate("NoteBOOK", "\346\237\245\346\211\276", nullptr));
        actioninfo->setText(QApplication::translate("NoteBOOK", "\345\205\263\344\272\216", nullptr));
        actionreplace->setText(QApplication::translate("NoteBOOK", "\346\233\277\346\215\242", nullptr));
        actionfont->setText(QApplication::translate("NoteBOOK", "\345\255\227\344\275\223", nullptr));
        actionclose->setText(QApplication::translate("NoteBOOK", "\345\205\263\351\227\255", nullptr));
#ifndef QT_NO_SHORTCUT
        actionclose->setShortcut(QApplication::translate("NoteBOOK", "Ctrl+W", nullptr));
#endif // QT_NO_SHORTCUT
        status->setText(QApplication::translate("NoteBOOK", "TextLabel", nullptr));
        menu->setTitle(QApplication::translate("NoteBOOK", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QApplication::translate("NoteBOOK", "\347\274\226\350\276\221", nullptr));
        menu_3->setTitle(QApplication::translate("NoteBOOK", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NoteBOOK: public Ui_NoteBOOK {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEBOOK_H
