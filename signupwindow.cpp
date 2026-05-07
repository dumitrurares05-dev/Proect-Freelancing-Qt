#include "signupwindow.h"
#include "ui_signupwindow.h"
#include "QMessageBox"
#include "mainwindow.h"
#include <QStackedWidget>
SignUpWindow::~SignUpWindow()
{
    delete ui;
}
SignUpWindow::SignUpWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignUpWindow)
{
    ui->setupUi(this);

    // 1. Configurări de bază
    //ui->editEmail->setPlaceholderText("Adresa ta de email");
    ui->editParola->setPlaceholderText("Minim 10 caractere");
    ui->editParola->setEchoMode(QLineEdit::Password);
    //ui->editConfirmare->setPlaceholderText("Repetă parola");
    ui->editConfirmare->setEchoMode(QLineEdit::Password);

    // Placeholder pentru skill-uri
    //ui->editSkilluriSignUp->setPlaceholderText("Ex: C++, Python, Design Grafic...");

    // 2. Ascundem elementele de skill-uri la început (default e CLIENT)
    ui->editSkilluriSignUp->hide();
    if(ui->labelSkilluri) ui->labelSkilluri->hide();

    // 3. CONEXIUNEA PENTRU AFIȘARE DINAMICĂ
    // Aceasta monitorizează când schimbi "CLIENT" cu "FREELANCER"
    connect(ui->comboRol, &QComboBox::currentTextChanged, this, [=](const QString &rol){
        bool esteFreelancer = (rol == "FREELANCER");

        ui->editSkilluriSignUp->setVisible(esteFreelancer);
        if(ui->labelSkilluri) {
            ui->labelSkilluri->setVisible(esteFreelancer);
        }
    });

    if(ui->comboRol->count() == 0) {
        ui->comboRol->addItems({"CLIENT", "FREELANCER"});
    }
}
//T01
//
void SignUpWindow::on_SignUp_clicked()
{
    QString email=ui->editEmail->text();
    QString p1=ui->editParola->text();
    QString p2=ui->editConfirmare->text();
    QString rol = ui->comboRol->currentText();
    if(p1!=p2)
    {
        QMessageBox::warning(this,"Eroare", "Parole introdusa incorect");
        return;
    }
    if (p1.length() < 10) {
        QMessageBox::warning(this, "Incomplet", "Minim 10 caractere la parola!");
        return;
    }
    QWidget *p = this;
    while(p)
    {
        MainWindow *mainWin=qobject_cast<MainWindow*>(p);
        if(mainWin){
            Utilizator nou;
            nou.email=email;
            nou.parola=p1;
            nou.rol=rol;

            if(rol == "FREELANCER") {
               nou.skilluriUtilizator = ui->editSkilluriSignUp->text();
            }
            mainWin->listaUtilizatori.append(nou);

             QMessageBox::information(this, "Succes", "Cont creat! Acum te poti loga.");

            QStackedWidget *stack = mainWin->findChild<QStackedWidget*>("pagini");
             if (stack) stack->setCurrentIndex(0);

             //
             mainWin->findChild<QStackedWidget*>("pagini")->setCurrentWidget(mainWin->paginaLogin);
             QMessageBox::information(this, "Succes", "Cont salvat!");
             return;
        }
       p = p->parentWidget();
    }

}

