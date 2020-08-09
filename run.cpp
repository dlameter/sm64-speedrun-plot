#include "run.h"

Run::Run(int place, int time, QString& user, QDateTime& submittedDate): 
    m_place(place),
    m_time(time),
    m_user(user),
    m_submittedDate(submittedDate) 
{}

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

QString Run::getUser() {
    return m_user;
}

void Run::setUser(const QString& user) {
    m_user = user;
}

QDateTime Run::getSubmittedDate() {
    return m_submittedDate;
}

void Run::setSubmittedDate(const QDateTime& date) {
    m_submittedDate = date;
}
