/**
 * Copyright (c) 2012 - 2014 TideSDK contributors 
 * http://www.tidesdk.org
 * Includes modified sources under the Apache 2 License
 * Copyright (c) 2008 - 2012 Appcelerator Inc
 * Refer to LICENSE for details of distribution and use.
 **/

#ifndef _ASYNC_JOB_H_
#define _ASYNC_JOB_H_
#include <Poco/Thread.h>
#include <Poco/RunnableAdapter.h>

namespace tide
{
    class TIDE_API AsyncJob : public StaticBoundObject
    {
        public:
        /*
         * Create an AsyncJob and initialize its binding-layer properties.
         */
        AsyncJob(TiMethodRef job=0);

        /*
         * Destroy an AsyncJob and release its callbacks.
         */
        virtual ~AsyncJob();

        /*
         * Run an async job synchronously (on the same thread).
         */
        void Run();

        /*
         * Run an async job asynchronously (on the different thread).
         */
        void RunAsynchronously();

        /*
         * The target method of an asynchronous job execution. This does
         * whatever bookkeeping is necessary at the start of a new thread
         * and then calls Run().
         */
        void RunThreadTarget();

        /*
         * Cancel a job.
         */
        void Cancel();

        /**
         * The result of the execution of this job. On an execution
         * error and before the job is completed this will be Undefined;
         */
        ValueRef GetResult();

        /**
         * The progress of this job, which is a number in
         * the range [0, 1] where 1 represents fully complete
         */
        double GetProgress();

        /**
         * Set progress of this job, which is a number in
         * the range [0, 1] where 1 represents fully complete.
         * Calling this method will trigger progress callbacks
         * unless the second argument is false.
         */
        void SetProgress(double, bool callbacks = false);

        /**
         * A built-in progress changed callback. This will be called
         * in the same situations as TiMethod-style progress callbacks
         */
        virtual void OnProgressChanged() {}

        /**
         * Add a callback to be executed when the progress of
         * this job changes
         */
        void AddProgressCallback(TiMethodRef);

        /**
         * A built-in completion callback. This will be called  in the
         *  same situations as TiMethod-style completed callbacks
         */
        virtual void OnCompleted() {};

        /**
         * Add a callback to be executed when the progress of
         * this job changes
         */
        void AddCompletedCallback(TiMethodRef);

        /**
         * A built-in error callback. This will be called  in the
         *  same situations as TiMethod-style error callbacks
         */
        virtual void OnError(ValueException& e) {};

        /**
         * Add a callback to be when an error happes during the
         * course of this job, whether in the job itself or a callback
         * related to that job.
         */
        void AddErrorCallback(TiMethodRef);
        
        /**
         * Set arguments for this job.
         * This allows the job method to take in custom arguments
         */
        void SetArguments(ValueList args) { this->arguments = args; }

        /**
         * Get the arguments for this job.
         */
        ValueList& GetArguments() { return arguments; }
        
        protected:
        TiMethodRef job;
        ValueList arguments;
        double progress;
        bool completed;
        ValueRef result;
        bool hadError;
        bool cancelled;
        void Error(ValueException&);

        /*
         * Execute the "work" part of this async job. This is generally not
         * called directly, as it does not call any callbacks or necessarily
         * modify the progress -- Run or RunAsynchronously are better
         * choices. It can be overridden to create custom job types which
         * do something other than just execute a TiMethod.
         */
        virtual ValueRef Execute();

        void _Cancel(const ValueList&, ValueRef);
        void _GetProgress(const ValueList&, ValueRef);
        void _IsComplete(const ValueList& args, ValueRef result);

        private:
        std::vector<TiMethodRef> progressCallbacks;
        std::vector<TiMethodRef> completedCallbacks;
        std::vector<TiMethodRef> errorCallbacks;

        Poco::Thread* thread;
        Poco::RunnableAdapter<AsyncJob>* adapter;
        void DoCallback(TiMethodRef, bool reportErrors=false);
    };
}

#endif
