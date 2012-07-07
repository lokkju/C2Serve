/**

 Copyright (c) 2012, C2Serve (http://www.c2serve.eu)
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

#include "C2SRestResourceAPIDocumentHTMLBody.h"
#include "C2SRestResourceAPIDocumentHTML.h"
#include "C2SRestResourceAPIDocumentHTMLMethodOverview.h"
#include "C2SRestResourceDescription.h"

#include "StringUtils.h"

namespace c2s
{

  C2SRestResourceAPIDocumentHTMLBody::C2SRestResourceAPIDocumentHTMLBody( const C2SRestResourceDescription &descriptionOfRestResourceToCreateAPIDocumentFor )
    : m_descriptionOfRestResourceToCreateAPIDocumentFor( descriptionOfRestResourceToCreateAPIDocumentFor )
  {
    m_pHTMLRestMethodOverview = new C2SRestResourceAPIDocumentHTMLMethodOverview( m_descriptionOfRestResourceToCreateAPIDocumentFor );
  }

  C2SRestResourceAPIDocumentHTMLBody::~C2SRestResourceAPIDocumentHTMLBody()
  {
    delete m_pHTMLRestMethodOverview;
  }

  std::string C2SRestResourceAPIDocumentHTMLBody::toHTMLFormattedString() const
  {
    std::string sIndentWithSpaces = util::createIndentWithSpaces( C2SRestResourceAPIDocumentHTML::iIndentInSpaces );
    std::string sHTMLBodyAsString = sIndentWithSpaces + "<body>\n\n";
    sHTMLBodyAsString += sIndentWithSpaces + sIndentWithSpaces + "<div>\n\n";
    sHTMLBodyAsString += this->createHTMLFormattedStringForResourceOverviewWithIndentAsSpaces( 3 * C2SRestResourceAPIDocumentHTML::iIndentInSpaces );
    sHTMLBodyAsString += sIndentWithSpaces + sIndentWithSpaces + "</div>\n\n";
    sHTMLBodyAsString += sIndentWithSpaces + "</body>";
    return sHTMLBodyAsString;
  }

  std::string C2SRestResourceAPIDocumentHTMLBody::createHTMLFormattedStringForResourceOverviewWithIndentAsSpaces( unsigned int iIndentInSpaces ) const
  {
    std::string sIndent = util::createIndentWithSpaces( iIndentInSpaces );
    std::string sResourceOverviewAsHTMLFormattedString = sIndent + "<h1>Overview for Resource " + m_descriptionOfRestResourceToCreateAPIDocumentFor.sContextRoot + "</h1>\n\n";
    sResourceOverviewAsHTMLFormattedString += m_pHTMLRestMethodOverview->toHTMLFormattedStringWithIndentAsSpaces( iIndentInSpaces ) + "\n";
    return sResourceOverviewAsHTMLFormattedString;
  }

}
