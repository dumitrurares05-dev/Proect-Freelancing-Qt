#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include "mainwindow.h"
#include "UserDate.h"
#include <QStackedWidget>>
#include "clientwindow.h"
LoginWindow::~LoginWindow()
{
    delete ui;
}
LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    // ── Titlu vizual deasupra formularului ──
    // Pune acest label in .ui sau adauga-l programatic:
    //ui->editEmail->setPlaceholderText();
    ui->editParola->setPlaceholderText("Minim 10 caractere");
    ui->editParola->setEchoMode(QLineEdit::Password);

    // Seteaza textul butonului de login mai explicit
    ui->butonLogin->setText("  Autentificare");
    ui->GoToSignUp->setText("  Nu ai cont? Înregistrează-te");

    // Stilizare speciala pentru butonul de navigare
    ui->GoToSignUp->setStyleSheet(
        "QPushButton { background: transparent; color: #6478ff; "
        "border: 1px solid #6478ff; border-radius: 8px; "
        "padding: 9px 20px; font-size: 13px; }"
        "QPushButton:hover { background: #1a1a3e; color: #8898ff; }"
        );
}
//T01-T02
void LoginWindow::on_butonLogin_clicked()
{

    QString email =ui->editEmail->text();
    QString parola = ui->editParola->text();
    QString rol =ui->comboRol->currentText();

    if (email.isEmpty() || parola.isEmpty()) {
        QMessageBox::warning(this, "WARNING!","Te rugam sa completezi toate campurile!");
        return;
    }

    if(!email.contains("@")){
        QMessageBox::warning(this,"Format Gresit", "Te rugam să introduci un email valid!");
        return;
    }

    if(parola.length()<10)
    {
        QMessageBox::critical(this,"Parola prea scurta", "Parola trebuie să aiba cel putin 10 caractere.");
        return;
    }


    MainWindow *mainWin=qobject_cast<MainWindow*>(window());

    bool gasit =false;

    if(mainWin){

        for(const auto &u :mainWin->listaUtilizatori)
        {
            if(u.email==email&&u.parola==parola &&u.rol==rol)
            {   //T09
                if(u.esteSuspendat) {
                    QMessageBox::critical(this, "CONT SUSPENDAT","Accesul interzis! Acest cont a fost suspendat de un administrator.");
                    return;
                }
                gasit=true;
                mainWin->currentUserEmail = email;
                break;
            }
        }
    }
        if (gasit) {
        QMessageBox::information(this, "Succes", "Autentificare reusita!\nUtilizator: " + email + "\nRol: " + rol);

        QStackedWidget *stack=mainWin->findChild<QStackedWidget*>("pagini");

        mainWin->currentUserEmail = email;

        QString emailComplet = ui->editEmail->text();
        QString numeUser=emailComplet.split('@').at(0);
        numeUser[0]=numeUser[0].toUpper();

        if(stack)
            {
                if(rol=="CLIENT")
            {
                mainWin->paginaClient->setNumeClient(numeUser);
                mainWin->paginaClient->incarcaProiecteProprii(mainWin->listaProjectsClient);
                mainWin->paginaClient->incarcaContracteActive();
                stack->setCurrentWidget(mainWin->paginaClient);
            }
            else if(rol=="FREELANCER")
            {
                mainWin->paginaFreelancer->setNumeFreelancer(numeUser);

                mainWin->paginaFreelancer->incarcaProiecteDisp(QStringList());
                 mainWin->paginaFreelancer->incarcaContracteActive();
                stack->setCurrentWidget(mainWin->paginaFreelancer);
            }
        }
    } else {
        QMessageBox::critical(this, "Eroare", "Date incorecte sau cont inexistent!\nVerifică Email-ul, Parola și Rolul selectat.");
    }
}

//
void LoginWindow::on_GoToSignUp_clicked()
{
    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());
    if (mainWin) {
        QStackedWidget *stack = mainWin->findChild<QStackedWidget*>("pagini");
        if (stack) {
            stack->setCurrentWidget(mainWin->paginaSignUp);
        }
    }
}