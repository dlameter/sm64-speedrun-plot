#ifndef RUN_H
#define RUN_H

#include <QDateTime>

class Run {
public:
    Run(int, int, QString, QDateTime);

    /* Access methods */
    int getPlace();
    int getTime();
    QString getUser();
    QDateTime getSubmittedDate();

private:
    /* Data members */
    int m_place;
    int m_time;
    QString m_user;
    QDateTime m_submittedDate;
};

#endif
