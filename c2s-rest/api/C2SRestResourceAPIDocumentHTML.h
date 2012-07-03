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

#ifndef C2SRESTRESOURCEAPIDOCUMENTHTML_H_
#define C2SRESTRESOURCEAPIDOCUMENTHTML_H_

#include "C2SHttpResponse.h"
#include "C2SHttpRequest.h"

#include <string>

namespace c2s
{
  struct C2SRestResourceDescription;
  class C2SRestResourceAPIDocumentHTMLHeader;

  class C2SRestResourceAPIDocumentHTML
  {
  public:

    C2SRestResourceAPIDocumentHTML( const std::string sHostURL , const C2SRestResourceDescription &resourceDescriptionToCreateAPIDocumentFor );

    C2SRestResourceAPIDocumentHTML( const C2SRestResourceDescription &resourceDescriptionToCreateAPIDocumentFor );

    virtual ~C2SRestResourceAPIDocumentHTML();

    std::string toHTMLFormattedString() const;

    C2SHttpResponse process( const C2SHttpRequest &request );

    static const unsigned int iIndentInSpaces;

  private:

    std::string createHtmlHeader();

    std::string createHtmlBody();

    std::string m_sHostURL;

    const C2SRestResourceDescription &m_resourceDescriptionToCreateAPIDocumentFor;

    C2SRestResourceAPIDocumentHTMLHeader *m_pAPIDocumentHTMLHeader;

  };

}

#endif /* C2SRESTRESOURCEAPIDOCUMENTHTML_H_ */
