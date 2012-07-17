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

#include "C2SRestResourceAPIDocumentHTMLMethodOverview.h"
#include "C2SRestResourceAPIDocumentHTML.h"
#include "C2SRestResourceDescription.h"

#include "StringUtils.h"

namespace c2s
{

  C2SRestResourceAPIDocumentHTMLMethodOverview::C2SRestResourceAPIDocumentHTMLMethodOverview( const C2SRestResourceDescription &restResourceDescription )
    : m_restResourceDescription( restResourceDescription )
  {
  }

  C2SRestResourceAPIDocumentHTMLMethodOverview::~C2SRestResourceAPIDocumentHTMLMethodOverview()
  {
  }

  std::string C2SRestResourceAPIDocumentHTMLMethodOverview::toHTMLFormattedStringWithIndentAsSpaces( unsigned int iIndentInSpaces ) const
  {
    std::string sIndentWithSpaces = util::createIndentWithSpaces( iIndentInSpaces );
    std::string sIndentWithSpacesForMethodURIs = util::createIndentWithSpaces( iIndentInSpaces + C2SRestResourceAPIDocumentHTML::iIndentInSpaces );
    std::string sMethodOverviewAsHTMLFormattedString = sIndentWithSpaces + "<ul>\n";
    C2SRestResourceDescription::const_iterator restMethodIt = m_restResourceDescription.begin();
    C2SRestResourceDescription::const_iterator restMethodEnd = m_restResourceDescription.end();
    for ( ; restMethodIt != restMethodEnd; ++restMethodIt )
      sMethodOverviewAsHTMLFormattedString += sIndentWithSpacesForMethodURIs + "<li>" + this->createURIStringForRestMethod( *restMethodIt ) + "</li>\n";
    sMethodOverviewAsHTMLFormattedString += sIndentWithSpaces + "</ul>\n";
    return sMethodOverviewAsHTMLFormattedString;
  }

  std::string C2SRestResourceAPIDocumentHTMLMethodOverview::createURIStringForRestMethod( const C2SRestMethodDescription &restMethodDescription ) const
  {
    std::string sMethodURI = "/";
    C2SRestMethodDescription::const_iterator pathSegmentIt = restMethodDescription.begin();
    C2SRestMethodDescription::const_iterator pathSegmentEnd = restMethodDescription.end();
    for ( ; pathSegmentIt != pathSegmentEnd; ++pathSegmentIt )
      sMethodURI += pathSegmentIt->sSegmentID + "/";
    return sMethodURI;
  }

}
