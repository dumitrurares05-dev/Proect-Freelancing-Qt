#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "UserDate.h"
#include <QMainWindow>
#include "loginwindow.h"
#include "signupwindow.h"
#include "clientwindow.h"
#include"freelancerwindow.h"
#include<QMap>
#include<QDateTime>

struct AplicatieProiect {
    QString emailFreelancer;
    QString skilluri;
    double pretOferit;
};

struct Mesaj {
    QString expeditor;
    QString continut;
    QDateTime dataOra;
};
struct Contract {
    QString titluProiect;
    QString emailClient;
    QString emailFreelancer;
    double pretFinal;
    QString status;
    QString livrabil;
    QList<Mesaj> chat;
};
struct Proiect {
    QString titlu;
    QString emailProprietar;
    QString descriere;
};
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    QList<Utilizator> listaUtilizatori;

    LoginWindow *paginaLogin;
    SignUpWindow *paginaSignUp;

    ClientWindow* paginaClient;
    FreelancerWindow* paginaFreelancer;
//
    QStringList listaProjectsClient;//lista proiecte salvate
    QMap<QString,QString> ContinutProiecte;//continutul salvat

    QMap<QString, QList<AplicatieProiect>> TabelAplicari;
    QString currentUserEmail;

    QList<Contract> listaContracte;

    QList<Proiect> toateProiectele;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
