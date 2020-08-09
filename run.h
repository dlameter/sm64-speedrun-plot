#ifndef RUN_H
#define RUN_H

#include <QDateTime>

class Run {
public:
    Run(int place, int time, const QString& user, const QDateTime& submittedDate);

    /* Access methods */
    int getPlace();
    void setPlace(int place);
    int getTime();
    void setTime(int time);
    QString& getUser();
    const QString& getUser() const;
    void setUser(const QString& user);
    QDateTime& getSubmittedDate();
    const QDateTime& getSubmittedDate() const;
    void setSubmittedDate(const QDateTime& date);

private:
    /* Data members */
    int m_place;
    int m_time;
    QString m_user;
    QDateTime m_submittedDate;
};

#endif
