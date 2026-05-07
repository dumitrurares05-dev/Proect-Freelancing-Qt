#include "freelancerwindow.h"
#include "ui_freelancerwindow.h"
#include <QMessageBox>
#include <QStackedWidget>
#include <QListWidget>
#include"mainwindow.h"
#include <QTimer>
FreelancerWindow::~FreelancerWindow()
{
    delete ui;
}
FreelancerWindow::FreelancerWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FreelancerWindow)
{
    ui->setupUi(this);
    connect(ui->listJOBS, &QListWidget::itemClicked, this, &FreelancerWindow::JobDescription);
    //ui->pretCerutInput->setPlaceholderText("ex: 500");
    ui->livrabilInput->setPlaceholderText(
        "Link GitHub / Google Drive / descriere livrabil..."
        );

    // Eticheta pret cu simbol euro integrat
    ui->pretCerutInput->setStyleSheet(
        "QLineEdit { padding-left: 8px; }"
        );

    // Lista de joburi mai vizibila
    ui->listJOBS->setStyleSheet(
        "QListWidget { border-radius: 10px; padding: 6px; }"
        "QListWidget::item { padding: 10px 14px; border-radius: 6px; }"
        "QListWidget::item:selected { background-color: #3a4aaa; color:white; }"
        );

    // Description readonly cu aspect diferit
    ui->Description->setReadOnly(true);
    ui->Description->setStyleSheet(
        "QPlainTextEdit { background-color: #16162a; color: #b0b0d0; "
        "border: 1.5px solid #3a3a55; border-radius: 10px; padding: 10px; }"
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
//T04
//
void FreelancerWindow::on_ApplyButton_clicked()
{
    QListWidgetItem *itemSelect=ui->listJOBS->currentItem();


    QString pretText = ui->pretCerutInput->text();
    if(itemSelect)
    {
        if(pretText.isEmpty()) {
            QMessageBox::warning(this, "Date incomplete", "Te rugăm să introduci skill-urile și prețul dorit!");
            return;
        }

        QString numeProiect = itemSelect->text();
        MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());

        if(mainWin) {
            // Creăm obiectul cu datele aplicației
            AplicatieProiect aplicatieNoua;
            aplicatieNoua.emailFreelancer = mainWin->currentUserEmail; // Trebuie să te asiguri că salvezi emailul la login
            aplicatieNoua.pretOferit = pretText.toDouble();

            // Salvăm în map-ul din MainWindow
            mainWin->TabelAplicari[numeProiect].append(aplicatieNoua);

            QMessageBox::information(this, "Succes", "Aplicația pentru '" + numeProiect + "' a fost trimisă!");

            // Curățăm câmpurile după aplicare
            ui->pretCerutInput->clear();
        }
    }
    else
    {
        QMessageBox::warning(this, "Atenție", "Nu a fost selectat niciun proiect!");
    }
}
//
void FreelancerWindow::on_LOGOUT_clicked()
{
    MainWindow*mainWin=qobject_cast<MainWindow*>(this->window());
    if(mainWin)
    {
        mainWin->findChild<QStackedWidget*>("pagini")->setCurrentWidget(mainWin->paginaLogin);
    }
}
void FreelancerWindow::setNumeFreelancer(QString nume)
{
    ui->labelNume->setText("BINE ATI VENIT, "+nume.toUpper());
}
//
void FreelancerWindow::incarcaProiecteDisp(QStringList proiecte)
{
    ui->listJOBS->clear();
    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());

    if(mainWin) {
        QString skilluriRaw;
        // 1. Găsim skill-urile freelancerului
        for(const auto &u : mainWin->listaUtilizatori) {
            if(u.email == mainWin->currentUserEmail) {
                skilluriRaw = u.skilluriUtilizator.toLower();
                break;
            }
        }

        // 2. Tăiem șirul de skill-uri în cuvinte separate (după virgulă sau spațiu)
        // Din "c++, qt, sql" obținem o listă: ["c++", "qt", "sql"]
        QStringList listaMeaDeSkilluri = skilluriRaw.split(QRegularExpression("[,\\s]+"), Qt::SkipEmptyParts);

        // 3. Verificăm fiecare proiect
        for(const auto &p : mainWin->toateProiectele) {
            QString descriereProiect = p.descriere.toLower();
            bool sePotriveste = false;

            if(listaMeaDeSkilluri.isEmpty()) {
                sePotriveste = true; // Dacă userul n-are skill-uri, vede tot
            } else {
                for(const QString &skill : listaMeaDeSkilluri) {
                    if(descriereProiect.contains(skill.trimmed())) {
                        sePotriveste = true;
                        break; // Am găsit măcar o potrivire, e suficient
                    }
                }
            }

            if(sePotriveste) {
                ui->listJOBS->addItem(p.titlu);
            }
        }
    }
}

//T08
void FreelancerWindow::JobDescription(QListWidgetItem *item)
{
    QString numeProiect = item->text();
    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());

    if(mainWin) {
        for(const auto &p : mainWin->toateProiectele) {
            if(p.titlu == numeProiect) {
                ui->Description->setPlainText(p.descriere);
                return;
            }
        }
        QString descriereVeche = mainWin->ContinutProiecte.value(numeProiect);
        ui->Description->setPlainText(descriereVeche);
    }
}


void FreelancerWindow::incarcaContracteActive()
{

    ui->listContracteleMele->clear();
    ui->listChat->clear();  // ← ADD THIS
    ui->editMesaj->setEnabled(false);
    ui->butonTrimite->setEnabled(false);
    ui->editMesaj->setPlaceholderText("Selectează un contract pentru a discuta...");

    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());

    if(mainWin) {
        for(const auto &c : mainWin->listaContracte)
        {
            if(c.emailFreelancer == mainWin->currentUserEmail)
            {
                QListWidgetItem *item = new QListWidgetItem(c.titluProiect);
                if(c.status == "Completed") {
                    item->setBackground(Qt::green);
                }
                else if(c.status == "Rejected") {
                    item->setBackground(Qt::red);
                    item->setForeground(Qt::white);
                    item->setText(c.titluProiect + " - REJECTED");
                }
                else {
                    item->setBackground(Qt::white);
                }
                ui->listContracteleMele->addItem(item);
            }
        }
    }
}
void FreelancerWindow::on_listJOBS_itemClicked(QListWidgetItem *item)
{
    QString titluSelectat = item->text();

    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());

    if(mainWin) {
        for(const auto &p : mainWin->toateProiectele) {
            if(p.titlu == titluSelectat) {
                ui->Description->setPlainText(p.descriere);
                break;
            }
        }
    }
}



//T06
void FreelancerWindow::on_UploadButon_clicked()
{
    if(ui->livrabilInput->toPlainText().isEmpty()) {
        QMessageBox::warning(this, "Eroare", "Te rugam să scrii descrierea muncii sau link-ul inainte de upload!");
        return;
    }
    QMessageBox::information(this, "Upload", "Munca ta a fost incarcata cu succes!");
}

void FreelancerWindow::on_FinishedProject_clicked()
{
    QListWidgetItem *item = ui->listContracteleMele->currentItem();
    if(!item) {
        QMessageBox::warning(this, "EROARE", "Selectează contractul din listă!");
        return;
    }

    QString textComplet = item->text();
    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());

    if(mainWin) {
        for(auto &c : mainWin->listaContracte) {
           if(textComplet.startsWith(c.titluProiect) && c.emailFreelancer == mainWin->currentUserEmail) {
                c.livrabil = ui->livrabilInput->toPlainText();

                if(c.livrabil.isEmpty()) {
                    QMessageBox::warning(this, "EROARE", "Introduceți link-ul proiectului în casetă!");
                    return;
                }
                QMessageBox::information(this, "Succes", "Proiectul a fost trimis oficial către client!");
                break;
            }
        }
    }
}

//T07
void FreelancerWindow::afiseazaChat(const QList<Mesaj> &chat) {
    ui->listChat->clear();
    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());

    for(const auto &m : chat) {
        QListWidgetItem *item = new QListWidgetItem();

        if (m.expeditor.trimmed() == mainWin->currentUserEmail.trimmed()) {
            item->setText("Tu: " + m.continut);
            item->setTextAlignment(Qt::AlignRight);
        } else {
            item->setText("Client: " + m.continut); // Celălalt e mereu Clientul
            item->setTextAlignment(Qt::AlignLeft);
        }
        ui->listChat->addItem(item);
    }
    ui->listChat->scrollToBottom(); // Să vedem mereu ultimul mesaj
}
void FreelancerWindow::on_butonTrimite_clicked() {
    QString text = ui->editMesaj->text();
    if(text.isEmpty()) return;
    if(!ui->editMesaj->isEnabled()) return;

    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());
    QListWidgetItem *item = ui->listContracteleMele->currentItem();

    if(mainWin && item) {
        QString titluCurent = item->text();

        for(auto &c : mainWin->listaContracte) {
            if(c.titluProiect == titluCurent) {
                // MODIFICARE AICI: Nu mai declara "Mesaj m;" din nou!
                Mesaj m_nou;
                m_nou.expeditor = mainWin->currentUserEmail.trimmed();
                m_nou.continut = text;
                m_nou.dataOra = QDateTime::currentDateTime();

                c.chat.append(m_nou);
                ui->editMesaj->clear();
                afiseazaChat(c.chat);
                break;
            }
        }
    }
}
void FreelancerWindow::on_listContracteleMele_itemClicked(QListWidgetItem *item)
{
    ui->editMesaj->setEnabled(true);
    ui->butonTrimite->setEnabled(true);
    ui->editMesaj->setPlaceholderText("Scrie un mesaj către client...");

    // ── FIX: forțează re-randare imediată la click ──
    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());
    if(mainWin) {
        for(const auto &c : mainWin->listaContracte) {
            if(c.titluProiect == item->text()) {
                afiseazaChat(c.chat);  // ← renderează direct
                break;
            }
        }
    }
}
void FreelancerWindow::actualizeazaChatLive()
{
    MainWindow *mainWin = qobject_cast<MainWindow*>(this->window());
    QListWidgetItem *itemCurent = ui->listContracteleMele->currentItem();

    if(mainWin && itemCurent) {
        for(const auto &c : mainWin->listaContracte) {
            if(c.titluProiect == itemCurent->text()) {
                if(ui->listChat->count() != c.chat.size()) {
                    afiseazaChat(c.chat);
                } else if(!c.chat.isEmpty()) {
                    QString ultimAfisat = ui->listChat->item(
                                                          ui->listChat->count()-1)->text();
                    const Mesaj &ultim = c.chat.last();
                    bool esteAlMeu = ultim.expeditor.trimmed()
                                     == mainWin->currentUserEmail.trimmed();
                    QString asteptat = (esteAlMeu ? "Tu: " : "Client: ")
                                       + ultim.continut;
                    if(ultimAfisat != asteptat) {
                        afiseazaChat(c.chat);
                    }
                }
                break;
            }
        }
    }
}


