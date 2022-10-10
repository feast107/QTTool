#ifndef TASK_H
#define TASK_H
#include <QObject>
#include <QFuture>
#include <functional>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <iostream>
using namespace std;

namespace QtTool{
    enum TaskStatus{
        Created  = 0x1,
        Started  = 0x2,
        Running  = 0x4,
        Paused   = 0x8,
        Finished = 0x10,
        Canceled = 0x20,
    };
    template<typename T>
    class Task{
            friend class Tasks;
        private:
            function<T()> method;
            QFuture<T> promise;
            volatile TaskStatus status;
            Task(const function<T()> & method,bool autoStart){ this->method=method;status = Created;
                                                               if(autoStart){Start();}}
        public:
            Task(const Task<T> & other){method = other.method;promise = other.promise;status = Created;}
            Task(const function<T()> & method){ this->method=method;status = Created;}
            ~Task(){
                Wait();
            }
            void Start(){
                if(Status() == Created){ promise = QtConcurrent::run(method); status = Started;}
            }
            TaskStatus Status()
            {
                if(status!=Created){
                    if(promise.isFinished()){ status = Finished; }
                    if(promise.isRunning()){ status = Running; }
                    if(promise.isStarted()){ status = Started; }
                    if(promise.isPaused()){ status = Paused; }
                    if(promise.isCanceled()){ status = Canceled; }
                }
                return status;
            }
            void Pause(){
                if (Status() == (Running|Started)){promise.pause();}
            }
            void Resume(){
                if (Status() == Paused){ promise.resume(); }
            }
            void Cancel(){
                if (Status() == (Running|Started)){ promise.cancel();}
            }
            void Wait() {
                if (Status() == (Running|Started)){promise.waitForFinished();}
            }
            T Result()const{
                return promise.result();
            }
            template<typename E>
            Task<E> ContinueWith(const function<E(T)> & next){
                return Task<E>([=](){
                    return next(Result());
                },true);
            }
            template<typename E>
            Task<E> ContinueWith(const function<E()> & next){
                return Task<E>([=](){
                    Wait();
                    return next();
                },true);
            }
    };
    template<>
    class Task<void>{
            friend class Tasks;
        private:
            function<void()> method;
            QFuture<void> promise;
            volatile TaskStatus status;
            Task(const function<void()> & method,bool autoStart){ this->method=method;status = Created;
                                                               if(autoStart){Start();}}
        public:
            Task(const Task<void> & other){method = other.method;promise = other.promise;status = Created;}
            Task(const function<void()> & method){ this->method=method;status = Created;}
            ~Task(){
                Wait();
            }
            void Start(){
                if(Status() == Created){ promise = QtConcurrent::run(method); status = Started;}
            }
            TaskStatus Status()
            {
                if(status!=Created){
                    if(promise.isFinished()){ status = Finished; }
                    if(promise.isRunning()){ status = Running; }
                    if(promise.isStarted()){ status = Started; }
                    if(promise.isPaused()){ status = Paused; }
                    if(promise.isCanceled()){ status = Canceled; }
                }
                return status;
            }
            void Pause(){
                if (Status() == (Running|Started)){promise.pause();}
            }
            void Resume(){
                if (Status() == Paused){ promise.resume(); }
            }
            void Cancel(){
                if (Status() == (Running|Started)){ promise.cancel();}
            }
            void Wait() {
                if (Status() == (Running|Started)){promise.waitForFinished();}
            }

            template<typename E>
            Task<E> ContinueWith(const function<E()> & next){
                return Task<E>([=](){
                    Wait();
                    return next();
                },true);
            }
    };

    class Tasks{
        public:
            template<typename T>
            static void WaitAll(const QList<Task<T>> & tasks)
            {
                for(Task<T> task:tasks){
                    task.Wait();
                }
            }
            template<typename T>
            static Task<T> Run(const function<T()> & method)
            {
                Task<T> t = Task<T>(method);
                t.Start();
                return t;
            }
    };
}

#endif // TASK_H
