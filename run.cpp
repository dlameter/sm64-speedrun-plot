#include "run.h"

Run::Run(int place, int time, QString user, QDateTime submittedDate): 
    m_place(place),
    m_time(time),
    m_user(user),
    m_submittedDate(submittedDate) {}
