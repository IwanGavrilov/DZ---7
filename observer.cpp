#include "observer.h"


Subject::Subject() {
    observers = std::vector<Observer *>();
}

Subject::Subject(std::string sFile) {
    observers = std::vector<Observer *>();
    sFileName = sFile;
}

Subject::~Subject() {
}

// добаляю подписчиков
void Subject::Attach(Observer * newObserver) {
    observers.push_back(newObserver);
}

// задаю значение
void Subject::SetValue(std::queue <std::string> * _queue) {
    cmd_queue = _queue;
    Notify();
}

// измещаю подписчиков
void Subject::Notify() {
    for (Observer * currObs : observers) {
        currObs->Update();        
    }
}

// возвращаю имя файла лога
std::string Subject::GetLogFileName() {
    return sFileName;
}

// возвращаю очередь с данными
std::queue<std::string> * Subject::GetCmdQueue() {
    return cmd_queue;
}

// =========================================================================================

Observer::Observer(Subject * modif, std::string sFile) {
    ptrSubject = modif;
    loger = Loger(sFile);
}

void Observer::Update() {
    std::queue<std::string> * queue_data = ptrSubject->GetCmdQueue();
    if (queue_data->empty()) {
        // если очередь пуста, смысл что-то печатать
        return;
    }
    int idx = 0;
    std::string s_print = "bulk: ";

    for( ; !queue_data->empty(); queue_data->pop()) {
        s_print += queue_data->front() + ", ";
        idx++;
    }
    print_value((std::string) s_print);

    loger.AddRecord(s_print);

    s_print = "";
}

Observer::~Observer()
{
}
