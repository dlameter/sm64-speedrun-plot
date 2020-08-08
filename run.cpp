#include "run.h"

Run::Run(int place, int time, QString user, QDateTime submittedDate): 
    m_place(place),
    m_time(time),
    m_user(user),
    m_submittedDate(submittedDate) {}

int Run::getPlace() {
    return m_place;
}

int Run::getTime() {
    return m_time;
}

QString Run::getUser() {
    return m_user;
}

QDateTime Run::getSubmittedDate() {
    return m_submittedDate;
}
