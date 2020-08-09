#ifndef RUN_H
#define RUN_H

#include <QDateTime>

class Run {
public:
    Run(int, int, QString&, QDateTime&);

    /* Access methods */
    int getPlace();
    void setPlace(int place);
    int getTime();
    void setTime(int time);
    QString getUser();
    void setUser(const QString& user);
    QDateTime getSubmittedDate();
    void setSubmittedDate(const QDateTime& date);

private:
    /* Data members */
    int m_place;
    int m_time;
    QString m_user;
    QDateTime m_submittedDate;
};

#endif
