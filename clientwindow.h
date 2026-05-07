#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <QString>
#include <QListWidgetItem>
namespace Ui {
class ClientWindow;
}
    struct Mesaj;
class ClientWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();
    void setNumeClient(QString nume);

    void incarcaProiecteProprii(QStringList toateProiectele);

    void incarcaContracteActive();

    void afiseazaChat(const QList<Mesaj> &chat);

    void actualizeazaChatLive();

private slots:
    void on_PostProject_clicked();

    void on_LOGOUT_clicked();

    void on_ACCEPTOFFER_clicked();

    void on_REFUSEOFFER_clicked();

    void on_listProiecteleMele_itemClicked(QListWidgetItem *item);

    void on_emailAplicanti_itemClicked(QListWidgetItem *item);

    void on_Approve_buton_clicked();
    void on_RefuseWork_buton_clicked();

    void on_butonTrimite_clicked();

    void on_listaContracteActive_itemClicked(QListWidgetItem *item);

private:
    Ui::ClientWindow *ui;
};

#endif // CLIENTWINDOW_H
