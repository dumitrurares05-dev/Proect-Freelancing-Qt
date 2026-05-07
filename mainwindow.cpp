#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "signupwindow.h"
#include"clientwindow.h"
#include"freelancerwindow.h"
#include <QMessageBox>
#include  "UserDate.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    paginaLogin=new LoginWindow(this);
    paginaSignUp= new SignUpWindow(this);
    paginaClient=new ClientWindow(this);
    paginaFreelancer=new FreelancerWindow(this);

    ui->pagini->addWidget(paginaLogin);
    ui->pagini->addWidget(paginaSignUp);
    ui->pagini->addWidget(paginaClient);
    ui->pagini->addWidget(paginaFreelancer);

    //T09
    Utilizator userRau;
    userRau.email = "banned@gmail.com";
    userRau.parola = "parola12345";
    userRau.rol = "CLIENT";
    userRau.esteSuspendat = true;

    listaUtilizatori.append(userRau);

    ui->pagini->setCurrentWidget(paginaLogin);
}

MainWindow::~MainWindow()
{
    delete ui;
}

