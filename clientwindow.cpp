#include "clientwindow.h"
#include "ui_clientwindow.h"
#include"mainwindow.h"
#include <QMessageBox>
#include <QStackedWidget>
#include <QListWidget>
#include <QDateTime>
#include<QTimer>
ClientWindow::~ClientWindow()
{
    delete ui;
}
ClientWindow::ClientWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientWindow)
{
    ui->setupUi(this);

    // Placeholder-e pentru campuri
    //ui->editTitleProject->setPlaceholderText("ex: Aplicatie web React...");
   // ui->descriereProiect->setPlaceholderText(
       // "Descrie proiectul tău:\n• Ce trebuie realizat\n• Tehnologii preferate\n• Deadline estimat"
        //);

    // Etichete pentru sectiuni (daca labelurile exista in .ui)
    // Stylizare suplimentara pentru listele de proiecte
    ui->listProiecteleMele->setStyleSheet(
        "QListWidget { border-radius: 10px; padding: 6px; }"
        "QListWidget::item { padding: 10px; border-radius: 6px; }"
        );

    ui->emailAplicanti->setStyleSheet(
        "QListWidget { border-radius: 10px; }"
        "QListWidget::item { padding: 10px; border-radius: 6px; }"
        );
    // Butoane colorate explicit
    ui->PostProject->setStyleSheet(
        "QPushButton { background: qlineargradient(x1:0,y1:0,x2:1,y2:0,"
        "stop:0 #4a5aff,stop:1 #6478ff); color:white; border:none; "
        "border-radius:10px; padding:10px 24px; font-weight:bold; font-size:14px; }"
        "QPushButton:hover { background: qlineargradient(x1:0,y1:0,x2:1,y2:0,"
        "stop:0 #5a6aff,stop:1 #7488ff); }"
        );


    //T07
    QTimer *refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout, this, [=]() {
        actualizeazaChatLive();
    });
    refreshTimer->start(1000);
    ui->editMesaj->setEnabled(false);
    ui->butonTrimite->setEnabled(false);
    //ui->editMesaj->setPlaceholderText("Selectează un contract pentru a discuta...");
}
//T03
void ClientWindow::on_PostProject_clicked()
{
    QString titlu = ui->editTitleProject->text();
    if(titlu.isEmpty())
    {
        QMessageBox::warning(this,"Atentie!","Numele proiectului nu a fost introdus!");
        return;
    }
    QString content=ui->descriereProiect->toPlainText();
    if(content.isEmpty())
    {
        QMessageBox::warning(this, "Atentie!", "Descrierea lipseste!");
        return;
    }

    //
    MainWindow *mainWin=qobject_cast<MainWindow*>(this->window());
    if(mainWin){
        Proiect p;
        p.titlu = titlu;
        p.descriere = content;
        p.emailProprietar = mainWin->currentUserEmail;

        mainWin->toateProiectele.append(p);

        incarcaProiecteProprii(QStringList());

        ui->editTitleProject->clear();
        ui->descriereProiect->clear();
    }

    QMessageBox::information(this, "Succes", "Anunțul tău a fost postat cu succes!");
}

void ClientWindow::on_LOGOUT_clicked()
{
    MainWindow* mainWin=qobject_cast<MainWindow*>(this->window());
    if(mainWin)
    {
        mainWin->findChild<QStackedWidget*>("pagini")->setCurrentWidget(mainWin->paginaLogin);
    }
}

void ClientWindow::setNumeClient(QString nume)
{
    ui->labelNume->setText("BINE AȚI VENIT, " + nume.toUpper());
}

void ClientWindow::incarcaProiecteProprii(QStringList toateProiectele) {
    ui->listProiecteleMele->clear();
    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());

    if(mainWin) {
        for(const auto &p : mainWin->toateProiectele) {
            if(p.emailProprietar == mainWin->currentUserEmail) {
                ui->listProiecteleMele->addItem(p.titlu);
            }
        }
    }
}

void ClientWindow::on_listProiecteleMele_itemClicked(QListWidgetItem *item)
{
    QString numeProiect = item->text();
    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());

    if(mainWin) {
        ui->emailAplicanti->clear();
        QList<AplicatieProiect> lista = mainWin->TabelAplicari.value(numeProiect);

        for(const auto &ap : lista) {
            ui->emailAplicanti->addItem(ap.emailFreelancer);
        }
    }
}

//T05
void ClientWindow::on_ACCEPTOFFER_clicked()
{
    QListWidgetItem *itProiect = ui->listProiecteleMele->currentItem();
    QListWidgetItem *itEmail = ui->emailAplicanti->currentItem();

    if(!itProiect || !itEmail) {
        QMessageBox::warning(this, "Atenție", "Selectează un proiect și un freelancer din liste!");
        return;
    }

    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());
    if(mainWin) {
        QString numeProiect = itProiect->text();
        QString emailFreelancer = itEmail->text();
        double pretFinal = 0;
        QList<AplicatieProiect> &aplicari = mainWin->TabelAplicari[numeProiect];
        for(const auto &ap : aplicari) {
            if(ap.emailFreelancer == emailFreelancer) {
                pretFinal = ap.pretOferit;
                break;
            }
        }
        Contract contractNou;
        contractNou.titluProiect = numeProiect;
        contractNou.emailClient = mainWin->currentUserEmail;
        contractNou.emailFreelancer = emailFreelancer;
        contractNou.pretFinal = pretFinal;
        contractNou.status = "Activ";

        mainWin->listaContracte.append(contractNou);
        mainWin->listaProjectsClient.removeAll(numeProiect);
        delete ui->listProiecteleMele->takeItem(ui->listProiecteleMele->currentRow());
        incarcaContracteActive();
        ui->emailAplicanti->clear();
        ui->pretFreelancer->setText("0 €");

        QMessageBox::information(this, "Contract Generat","Succes! Ai acceptat oferta.\n\n""Contract oficial între: " + mainWin->currentUserEmail + " și " + emailFreelancer + "\n" "Suma: " + QString::number(pretFinal) + " €");
    }
}


void ClientWindow::on_REFUSEOFFER_clicked()
{
    QListWidgetItem *itEmail = ui->emailAplicanti->currentItem();
    if(!itEmail) return;

    QString emailRefuzat = itEmail->text();
    QString titluP = ui->listProiecteleMele->currentItem()->text();
    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());

    if(mainWin) {
        auto &lista = mainWin->TabelAplicari[titluP];
        for(int i=0; i < lista.size(); ++i) {
            if(lista[i].emailFreelancer == emailRefuzat) {
                lista.removeAt(i);
                break;
            }
        }
        delete ui->emailAplicanti->takeItem(ui->emailAplicanti->currentRow());
        ui->pretFreelancer->setText("-");

        QMessageBox::warning(this, "Refuz", "Oferta lui " + emailRefuzat + " a fost respinsa.");
    }
}





void ClientWindow::on_emailAplicanti_itemClicked(QListWidgetItem *item)
{
    if(!item) return;

    // Folosim .trimmed() pentru a fi siguri că nu există spații goale la final
    QString emailSelectat = item->text().trimmed();

    if(!ui->listProiecteleMele->currentItem()) return;
    QString numeProiect = ui->listProiecteleMele->currentItem()->text();

    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());

    if(mainWin) {
        // Luăm lista de aplicări din tabelul central
        QList<AplicatieProiect> aplicari = mainWin->TabelAplicari.value(numeProiect);

        bool gasit = false;
        for(const auto &ap : aplicari) {
            // Comparăm ambele email-uri curățate de spații
            if(ap.emailFreelancer.trimmed() == emailSelectat) {
                ui->pretFreelancer->setText(QString::number(ap.pretOferit) + " €");
                gasit = true;
                break;
            }
        }

        if(!gasit) {
            ui->pretFreelancer->setText("0 €");
        }
    }
}


//T06

void ClientWindow::on_Approve_buton_clicked()
{
    QListWidgetItem *item = ui->listaContracteActive->currentItem();
    if(!item) return;

    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());
    QString textSelectat = item->text();

    if(mainWin){
        for(auto &c : mainWin->listaContracte)
        {
            if(textSelectat.startsWith(c.titluProiect))
            {
                if(c.livrabil.isEmpty()) {
                    QMessageBox::warning(this, "EROARE", "Freelancerul nu a livrat proiectul inca!");
                    return;
                }
                c.status = "Completed";
                QMessageBox::information(this, "Finalizare",
                                         "Ai validat proiectul!\nStatus: Completed\nLivrabil primit: " + c.livrabil);
                item->setBackground(Qt::green);
                return;
            }
        }
    }
}

void ClientWindow::on_RefuseWork_buton_clicked()
{
    QListWidgetItem *item = ui->listaContracteActive->currentItem();
    if(!item) return;
    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());
    QString textSelectat = item->text();
    if(mainWin){
        for(auto &c : mainWin->listaContracte)
        {
            if(textSelectat.startsWith(c.titluProiect))
            {
                if(c.livrabil.isEmpty()) {
                    QMessageBox::warning(this, "EROARE", "Nu poti refuza ceva ce nu a fost înca livrat!");
                    return;
                }
                c.status = "Rejected";
                QMessageBox::critical(this, "Munca Respinsa",
                                      "Ai respins livrabilul. Freelancerul va vedea statusul 'Rejected' și trebuie să retransmita.");
                item->setBackground(Qt::red);
                item->setForeground(Qt::white);
                return;
            }
        }
    }
}

void ClientWindow::incarcaContracteActive()
{
    ui->listaContracteActive->clear();
    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());

    if(mainWin) {
        for(const auto &c : mainWin->listaContracte) {
            if(c.emailClient == mainWin->currentUserEmail) {
                ui->listaContracteActive->addItem(c.titluProiect);
            }
        }
    }
}

//T07
void ClientWindow::afiseazaChat(const QList<Mesaj> &chat) {
    ui->listChat->clear();
    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());
    if(!mainWin) return;

    for(int i = 0; i < chat.size(); ++i) {
        // Folosim indexarea directă pentru a evita problemele de tip const
        const Mesaj &m = chat.at(i);

        QListWidgetItem *item = new QListWidgetItem();

        if (m.expeditor.trimmed() == mainWin->currentUserEmail.trimmed()) {
            item->setText("Tu: " + m.continut);
            item->setTextAlignment(Qt::AlignRight);
        } else {
            item->setText("Freelancer: " + m.continut); // Celălalt e mereu Freelancerul
            item->setTextAlignment(Qt::AlignLeft);
        }
        ui->listChat->addItem(item);
    }
    ui->listChat->scrollToBottom();
}

void ClientWindow::on_butonTrimite_clicked()
{
    QString text = ui->editMesaj->text();
    if(text.isEmpty()) return;

    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());
    QListWidgetItem *item = ui->listaContracteActive->currentItem();

    if(mainWin && item) {
        QString titluProiect = item->text();
        for(auto &c : mainWin->listaContracte) {
            if(c.titluProiect == titluProiect) {
                Mesaj m;
                // MODIFICARE: trimmed() adăugat
                m.expeditor = mainWin->currentUserEmail.trimmed();
                m.continut = text;
                m.dataOra = QDateTime::currentDateTime();

                c.chat.append(m);
                ui->editMesaj->clear();
                afiseazaChat(c.chat);
                break;
            }
        }
    }
}

void ClientWindow::on_listaContracteActive_itemClicked(QListWidgetItem *item)
{
    if(!item) return;

    // 1. Activăm câmpurile de scris
    ui->editMesaj->setEnabled(true);
    ui->butonTrimite->setEnabled(true);
    ui->editMesaj->setPlaceholderText("Scrie un mesaj către freelancer...");

    // 2. Afișăm imediat conversația
    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());
    if(mainWin) {
        for(const auto &c : mainWin->listaContracte) {
            // Comparăm titlul din listă cu cel din baza de date
            if(c.titluProiect == item->text()) {
                afiseazaChat(c.chat);
                break;
            }
        }
    }
}

void ClientWindow::actualizeazaChatLive()
{
    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());
    QListWidgetItem *itemCurent = ui->listaContracteActive->currentItem();

    if(mainWin && itemCurent) {
        for(const auto &c : mainWin->listaContracte) {
            if(c.titluProiect == itemCurent->text()) {
                // ── FIX: compară și conținut, nu doar număr ──
                if(ui->listChat->count() != c.chat.size()) {
                    afiseazaChat(c.chat);
                } else if(!c.chat.isEmpty()) {
                    // Verifică dacă ultimul mesaj afisat e corect
                    QString ultimAfisat = ui->listChat->item(
                                                          ui->listChat->count()-1)->text();
                    const Mesaj &ultim = c.chat.last();
                    bool esteAlMeu = ultim.expeditor.trimmed()
                                      == mainWin->currentUserEmail.trimmed();
                    QString asteptat = (esteAlMeu ? "Tu: " : "Freelancer: ")
                                       + ultim.continut;
                    if(ultimAfisat != asteptat) {
                        afiseazaChat(c.chat); // perspectiva s-a schimbat
                    }
                }
                break;
            }
        }
    }
}

