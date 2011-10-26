/*
 * threadbase.h
 *
 *  Created on: 18.10.2009
 *      Author: gack
 */

#ifndef THREAD_H_
#define THREAD_H_

#include "ThreadDefines.h"
#include "ThreadException.h"
#include "Lock.h"

#ifdef USE_BOOST_THREADS
#include <boost/thread.hpp>
#endif

#ifdef USE_POSIX_THREADS
#include <pthread.h>
#endif

#include <assert.h>

namespace g
{
  namespace thread
  {

    template <class Runnable>
    class Thread
    {
    public:

      Thread( Runnable *runnable )
        : m_runnable( runnable ),
          m_pMutex( new Mutex ),
          m_bDestroyMutex( true )
#ifdef USE_POSIX_THREADS
          , m_pthread( 0 )
#endif
      {};

      Thread()
        : m_runnable( NULL ),
          m_pMutex( new Mutex ),
          m_bDestroyMutex( true )
#ifdef USE_POSIX_THREADS
          , m_pthread( 0 )
#endif
      {};

      void set( Runnable &runnable ) { m_runnable = &runnable; }

      virtual ~Thread()
      {
#ifdef USE_POSIX_THREADS
        if ( m_pthread )
          pthread_detach( m_pthread );
#endif
        if ( m_bDestroyMutex )
          delete m_pMutex;
      };

      inline void start();

#ifdef USE_BOOST_THREADS

      void operator()();

      Thread( const Thread &t );

#endif

    private:

      void run();

      Thread &operator=( const Thread &t );

      Runnable *m_runnable;

      Mutex *m_pMutex;

      bool m_bDestroyMutex;

#ifdef USE_POSIX_THREADS

      Thread( const Thread &t );

      void operator()();

      static void *run( void *data );

      pthread_t m_pthread;

#endif //USE_POSIX_THREADS

    };

    template <class Runnable>
    Thread<Runnable>::Thread( const Thread &t )
      : m_runnable( t.m_runnable ),
        m_pMutex( t.m_pMutex ),
        m_bDestroyMutex( false )
    {}

    template <class Runnable>
    inline void Thread<Runnable>::run()
    {
#ifdef USE_BOOST_THREADS
      Lock lock( m_pMutex );
#endif

      assert( m_runnable != NULL );
      m_runnable->run();
    }

    template <class Runnable>
    inline void Thread<Runnable>::operator()()
    {
      this->run();
    }

#ifdef USE_POSIX_THREADS

    template <class Runnable>
    void *Thread<Runnable>::run( void *data )
    {
      Thread *pThread = reinterpret_cast<Thread*>( data );

      {
        Lock lock( pThread->m_pMutex );

        pThread->run();
      }

      pthread_exit( NULL );
    }

    template <class Runnable>
    inline void Thread<Runnable>::start()
    {
      if ( m_pthread )
      {
        Lock lock( m_pMutex );

        int status = pthread_detach( m_pthread );
        if ( status )
          throw ThreadException( "Thread::start: Cannot detach thread" );
      }

      int status = pthread_create( &m_pthread , NULL , Thread::run , (void *) this );
      if ( status )
        throw ThreadException( "Thread::start: Cannot create thread" );
    }

#endif //USE_POSIX_THREADS

#ifdef USE_BOOST_THREADS

    template <class Runnable>
    inline void Thread<Runnable>::start()
    {
      Lock lock( m_pMutex );

      boost::thread athread( *this );
    }

#endif //USE_BOOST_THREADS

  }
}


#endif /* THREAD_H_ */
