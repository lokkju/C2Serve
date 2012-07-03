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

#include "C2SRestResourceAPIDocumentHTML.h"
#include "C2SRestResourceAPIDocumentHTMLHeader.h"
#include "C2SRestResourceDescription.h"

namespace c2s
{
  const unsigned int C2SRestResourceAPIDocumentHTML::iIndentInSpaces = 2;

  C2SRestResourceAPIDocumentHTML::C2SRestResourceAPIDocumentHTML( const std::string sHostURL , const C2SRestResourceDescription &resourceDescriptionToCreateAPIDocumentFor )
    : m_sHostURL( sHostURL ),
      m_resourceDescriptionToCreateAPIDocumentFor( resourceDescriptionToCreateAPIDocumentFor ),
      m_pAPIDocumentHTMLHeader( C2SRestResourceAPIDocumentHTMLHeader::createDefaultDescriptionHeader() )
  {
  }

  C2SRestResourceAPIDocumentHTML::C2SRestResourceAPIDocumentHTML( const C2SRestResourceDescription &resourceDescriptionToCreateAPIDocumentFor )
    : m_sHostURL( "localhost" ),
      m_resourceDescriptionToCreateAPIDocumentFor( resourceDescriptionToCreateAPIDocumentFor ),
      m_pAPIDocumentHTMLHeader( C2SRestResourceAPIDocumentHTMLHeader::createDefaultDescriptionHeader() )
  {

  }

  C2SRestResourceAPIDocumentHTML::~C2SRestResourceAPIDocumentHTML()
  {
    delete m_pAPIDocumentHTMLHeader;
  }

  std::string C2SRestResourceAPIDocumentHTML::toHTMLFormattedString() const
  {
    std::string sAPIDocumentAsHTMLFormattedString = "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n";
    sAPIDocumentAsHTMLFormattedString += "<html>\n\n";
    sAPIDocumentAsHTMLFormattedString += m_pAPIDocumentHTMLHeader->toHTMLFormattedString() + "\n\n";
    sAPIDocumentAsHTMLFormattedString += "</html>\n";
    return sAPIDocumentAsHTMLFormattedString;
  }

  C2SHttpResponse C2SRestResourceAPIDocumentHTML::process( const C2SHttpRequest & )
  {
    std::string sContent = "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n";
    sContent += "<html>";

    sContent += this->createHtmlHeader();
    sContent += this->createHtmlBody();

    sContent += "</html>";

    C2SHttpResponseHeader responseHeader( OK );
    responseHeader.Fields.setContentType( C2SHttpMediaType::text__html );
    responseHeader.Fields.setContentLength( sContent.size() );
    C2SHttpResponse response( responseHeader );
    char *data = new char[ sContent.size() ];
    std::memcpy( data , sContent.c_str() , sContent.size() );
    response.setEntity( new C2SHttpEntity( data , sContent.size() , true ) );
    return response;
  }

  std::string C2SRestResourceAPIDocumentHTML::createHtmlHeader()
  {
    std::string sHeader;

    sHeader += "<header>";
    sHeader += "</header>";

    return sHeader;
  }

  std::string C2SRestResourceAPIDocumentHTML::createHtmlBody()
  {
    std::string sBody;

    sBody += "<body>";

    sBody += "http://" + m_sHostURL + ":" + "PORT" + "/" + m_resourceDescriptionToCreateAPIDocumentFor.sContextRoot;

    sBody += "</body>";

    return sBody;
  }

}
