/**

	Copyright (c) 2011, C2Serve (http://www.c2serve.eu)
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
	1. Redistributions of source code must retain the above copyright
	   notice, this list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright
	   notice, this list of conditions and the following disclaimer in the
	   documentation and/or other materials provided with the distribution.
	3. All advertising materials mentioning features or use of this software
	   must display the following acknowledgement: "This product includes software of the C2Serve project".
	4. Neither the name of the C2Serve project nor the
	   names of its contributors may be used to endorse or promote products
	   derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY C2SERVE ''AS IS'' AND ANY
	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL C2SERVE BE LIABLE FOR ANY
	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#ifndef C2SSOCKETLISTENER_H_
#define C2SSOCKETLISTENER_H_

#include "C2SSocketListenerSettings.h"
#include "C2SSocketException.h"

#include <list>

namespace c2s
{

  struct C2SSocketInfo;
  class C2SSocketAcceptHandler;
  class C2SDataHandlingInterface;
  class C2SLogInterface;

  class C2SSocketListenerException : public C2SSocketException
  {
  public:

    C2SSocketListenerException( const std::string &msg ) : C2SSocketException( msg ) {};

  };

  class C2SSocketListener
  {
  public:

    C2SSocketListener( const C2SSocketListenerSettings &settings , const C2SDataHandlingInterface &dataHandling , const C2SLogInterface &logInstance );

    virtual ~C2SSocketListener();

    void connect();

    void run();

    void connectAndRun();

    void interrupt();

    bool isListening() const;

  private:

    C2SSocketListener( const C2SSocketListener & );

    C2SSocketListener &operator=( const C2SSocketListener & );

    typedef std::list<C2SSocketAcceptHandler*> C2SSocketAcceptHandlerList;

    C2SSocketListenerSettings m_settings;

    const C2SDataHandlingInterface &m_dataHandling;

    C2SSocketAcceptHandlerList m_acceptHandlers;

    C2SSocketInfo *m_pSocketInfo;

    volatile bool m_bKeepRunning;

    bool m_bIsListening;

    const C2SLogInterface &m_logInstance;

#ifdef WINXX
    bool m_bIsWSACleanup;
#endif

  };

}

#endif /* C2SSOCKETLISTENER_H_ */
