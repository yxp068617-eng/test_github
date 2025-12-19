/********************************************************************************
** Form generated from reading UI file 'patientview.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTVIEW_H
#define UI_PATIENTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PatientView
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_Search;
    QPushButton *btSearch;
    QPushButton *btAdd;
    QPushButton *btDelete;
    QPushButton *btEdit;
    QTableView *tableView;

    void setupUi(QWidget *PatientView)
    {
        if (PatientView->objectName().isEmpty())
            PatientView->setObjectName(QString::fromUtf8("PatientView"));
        PatientView->resize(486, 300);
        layoutWidget = new QWidget(PatientView);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 10, 456, 224));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit_Search = new QLineEdit(layoutWidget);
        lineEdit_Search->setObjectName(QString::fromUtf8("lineEdit_Search"));

        horizontalLayout->addWidget(lineEdit_Search);

        btSearch = new QPushButton(layoutWidget);
        btSearch->setObjectName(QString::fromUtf8("btSearch"));

        horizontalLayout->addWidget(btSearch);

        btAdd = new QPushButton(layoutWidget);
        btAdd->setObjectName(QString::fromUtf8("btAdd"));

        horizontalLayout->addWidget(btAdd);

        btDelete = new QPushButton(layoutWidget);
        btDelete->setObjectName(QString::fromUtf8("btDelete"));

        horizontalLayout->addWidget(btDelete);

        btEdit = new QPushButton(layoutWidget);
        btEdit->setObjectName(QString::fromUtf8("btEdit"));

        horizontalLayout->addWidget(btEdit);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(layoutWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);


        retranslateUi(PatientView);

        QMetaObject::connectSlotsByName(PatientView);
    } // setupUi

    void retranslateUi(QWidget *PatientView)
    {
        PatientView->setWindowTitle(QApplication::translate("PatientView", "\347\227\205\344\272\272\347\256\241\347\220\206", nullptr));
        btSearch->setText(QApplication::translate("PatientView", "\346\237\245\346\211\276", nullptr));
        btAdd->setText(QApplication::translate("PatientView", "\346\267\273\345\212\240", nullptr));
        btDelete->setText(QApplication::translate("PatientView", "\345\210\240\351\231\244", nullptr));
        btEdit->setText(QApplication::translate("PatientView", "\344\277\256\346\224\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PatientView: public Ui_PatientView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTVIEW_H
