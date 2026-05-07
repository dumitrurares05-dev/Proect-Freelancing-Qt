#ifndef USERDATE_H
#define USERDATE_H
#include <QString>

struct Utilizator {
    QString email;
    QString parola;
    QString rol;
    QString skilluriUtilizator;
    bool esteSuspendat = false; // Implicit, nimeni nu e suspendat
};

#endif // USERDATE_H
