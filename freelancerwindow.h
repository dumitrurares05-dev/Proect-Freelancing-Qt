#ifndef FREELANCERWINDOW_H
#define FREELANCERWINDOW_H


#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class FreelancerWindow;
}
struct Mesaj;
class FreelancerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FreelancerWindow(QWidget *parent = nullptr);
    ~FreelancerWindow();

    void setNumeFreelancer(QString nume);

    void incarcaProiecteDisp(QStringList proiecte);

    void incarcaContracteActive();

    void afiseazaChat(const QList<Mesaj> &chat);

    void actualizeazaChatLive();
private slots:
    void on_ApplyButton_clicked();

    void on_LOGOUT_clicked();

    void JobDescription(QListWidgetItem *item);

    void on_listJOBS_itemClicked(QListWidgetItem *item);

    void on_FinishedProject_clicked();

    void on_UploadButon_clicked();

    void on_butonTrimite_clicked();

    void on_listContracteleMele_itemClicked(QListWidgetItem *item);

private:
    Ui::FreelancerWindow *ui;
};

#endif // FREELANCERWINDOW_H
