#include "run.h"

Run::Run(int place, int time, const QString& user, const QDateTime& submittedDate): 
    m_place(place),
    m_time(time)
{
    m_user = QString(user);
    m_submittedDate = QDateTime(submittedDate);
}

int Run::getPlace() {
    return m_place;
}

void Run::setPlace(int place) {
    m_place = place;
}

int Run::getTime() {
    return m_time;
}

void Run::setTime(int time) {
    m_time = time;
}

QString& Run::getUser() {
    return m_user;
}

const QString& Run::getUser() const {
    return m_user;
}

void Run::setUser(const QString& user) {
    m_user = user;
}

QDateTime& Run::getSubmittedDate() {
    return m_submittedDate;
}

const QDateTime& Run::getSubmittedDate() const {
    return m_submittedDate;
}

void Run::setSubmittedDate(const QDateTime& date) {
    m_submittedDate = date;
}
