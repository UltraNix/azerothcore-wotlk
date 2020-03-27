

#ifndef _TRANSACTION_H
#define _TRANSACTION_H

#include "SQLOperation.h"
#include "Optional.h"

#include <future>

//- Forward declare (don't include header to prevent circular includes)
class PreparedStatement;

/*! Transactions, high level class. */
class Transaction
{
    friend class TransactionTask;
    friend class MySQLConnection;

    template <typename T>
    friend class DatabaseWorkerPool;

    public:
        Transaction() : _cleanedUp(false) { }
        ~Transaction() { Cleanup(); }

        void Append(PreparedStatement* statement);
        void Append(const char* sql);
        void PAppend(const char* sql, ...);

        size_t GetSize() const { return m_queries.size(); }

    protected:
        void Cleanup();
        std::list<SQLElementData> m_queries;

    private:
        bool _cleanedUp;

};
typedef Trinity::AutoPtr<Transaction, ACE_Thread_Mutex> SQLTransaction;

using TransactionPromise = std::promise< bool >;
using TransactionResult = std::future< bool >;

/*! Low level class*/
class TransactionTask : public SQLOperation
{
    template <class T> friend class DatabaseWorkerPool;
    friend class DatabaseWorker;

    public:
        TransactionTask( SQLTransaction trans, Optional<TransactionPromise> promise = {} )
            : m_trans(trans)
            , m_promise( std::move( promise ) ) 
        { 
        };

    protected:
        bool                Execute();

        Optional<TransactionPromise>    m_promise;
        SQLTransaction                  m_trans;
};

#endif
