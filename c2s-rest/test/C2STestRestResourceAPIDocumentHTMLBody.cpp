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

#include "C2STestRestResourceAPIDocumentHTMLBody.h"
#include "C2STestRestResourceDescription.h"
#include "C2STestRestFixture.h"

#include "C2SRestResourceAPIDocumentHTMLBody.h"

#include "FileUtils.h"

#include <boost/test/unit_test.hpp>

namespace c2s
{

  namespace test
  {

    C2STestRestResourceAPIDocumentHTMLBody::C2STestRestResourceAPIDocumentHTMLBody()
      : m_descriptionOfRestResource( C2STestRestResourceDescription::createRestResourceDescription() )
    {
    }

    C2STestRestResourceAPIDocumentHTMLBody::~C2STestRestResourceAPIDocumentHTMLBody()
    {
    }

    void C2STestRestResourceAPIDocumentHTMLBody::runTest()
    {
      C2STestRestResourceAPIDocumentHTMLBody testRestResourceAPIDocumentHTMLBody;
      testRestResourceAPIDocumentHTMLBody.readHTMLStringExpectedForAPIDocumentBody();
      testRestResourceAPIDocumentHTMLBody.checkHTMLStringCreatedFromAPIDocumentBody();
    }

    void C2STestRestResourceAPIDocumentHTMLBody::readHTMLStringExpectedForAPIDocumentBody()
    {
      std::string sLocationOfFileContainingExpectedHTMLBody = C2STestRestFixture::sPathToTestSourcesDirectory + "/c2s_test_expected_html_body";
      m_sHTMLStringExpectedForAPIDocumentBody = util::readFileToString( sLocationOfFileContainingExpectedHTMLBody );
    }

    void C2STestRestResourceAPIDocumentHTMLBody::checkHTMLStringCreatedFromAPIDocumentBody()
    {
      C2SRestResourceAPIDocumentHTMLBody resourceAPIDocumentHTMLBody( m_descriptionOfRestResource );
      std::string sHTMLBodyCreatedForResourceDescription = resourceAPIDocumentHTMLBody.toHTMLFormattedString();
      BOOST_MESSAGE( sHTMLBodyCreatedForResourceDescription );
      BOOST_CHECK( sHTMLBodyCreatedForResourceDescription == m_sHTMLStringExpectedForAPIDocumentBody );
    }

  }

}
